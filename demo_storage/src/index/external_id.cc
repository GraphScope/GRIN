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

#include "src/predefine.h"
// GRIN headers
#include "index/external_id.h"

#ifdef GRIN_ENABLE_VERTEX_EXTERNAL_ID_OF_INT64
GRIN_VERTEX grin_get_vertex_by_external_id_of_int64(
    GRIN_GRAPH g, long long int id) {  // NOLINT
  return id;
}

long long int grin_get_vertex_external_id_of_int64(GRIN_GRAPH g,  // NOLINT
                                                   GRIN_VERTEX v) {
  return v;
}
#endif

#ifdef GRIN_ENABLE_VERTEX_EXTERNAL_ID_OF_STRING
void grin_destroy_vertex_external_id_of_string(GRIN_GRAPH g, const char* id) {
  delete[] id;
}

GRIN_VERTEX grin_get_vertex_by_external_id_of_string(GRIN_GRAPH g,
                                                     const char* id) {
  return std::stoi(std::string(id));
}

const char* grin_get_vertex_external_id_of_string(GRIN_GRAPH g, GRIN_VERTEX v) {
  std::string std = std::to_string(v);
  char* id = new char[std.length() + 1];
  snprintf(id, std.length() + 1, "%s", std.c_str());
  return id;
}
#endif
