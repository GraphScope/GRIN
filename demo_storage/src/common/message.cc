/** Copyright 2020 Alibaba Group Holding Limited.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <glog/logging.h>
#include <google/protobuf/util/json_util.h>

#include "../predefine.h"
#include "common/message.h"
#include "graph.pb.h"
#include "partition/partition.h"
#include "property/primarykey.h"
#include "property/property.h"
#include "property/propertylist.h"
#include "property/type.h"

void grin_destroy_graph_schema_msg(const char* s) { delete[] s; }

const char* grin_get_graph_schema_msg(const char* uri) {
  // TODO: implement the function
  std::string msg = "demo storage: " + std::string(uri);

  int len = msg.length() + 1;
  char* out = new char[len];
  snprintf(out, len, "%s", msg.c_str());
  return out;
}