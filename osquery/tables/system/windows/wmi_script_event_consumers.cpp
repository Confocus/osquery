/*
 *  Copyright (c) 2014-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#include <sstream>
#include <string>

#include <stdlib.h>

#include <osquery/core.h>
#include <osquery/filesystem.h>
#include <osquery/logger.h>
#include <osquery/tables.h>

#include "osquery/core/conversions.h"
#include "osquery/tables/system/windows/wmi.h"

namespace osquery {
namespace tables {

QueryData genScriptConsumers(QueryContext& context) {
  QueryData results_data;
  std::stringstream ss;
  ss << "SELECT * FROM ActiveScriptEventConsumer";

  WmiRequest request(ss.str(), L"ROOT\\Subscription");
  if (request.getStatus().ok()) {
    std::vector<WmiResultItem>& results = request.results();
    for (const auto& result : results) {
      Row r;

      result.GetString("ScriptText", r["script_text"]);
      result.GetString("ScriptFileName", r["script_file_name"]);
      result.GetString("ScriptingEngine", r["scripting_engine"]);
      result.GetString("Name", r["name"]);
      result.GetString("__CLASS", r["class"]);
      result.GetString("__RELPATH", r["relative_path"]);
      results_data.push_back(r);
    }
  }

  return results_data;
}
}
}