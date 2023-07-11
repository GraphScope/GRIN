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

// predefine for GRIN
#include "../predefine.h"
// storage headers
#include "storage/loadmoderngraph.h"
#include "storage/storage.h"

#define DEMO_STORAGE_NAMESPACE demo_storage_namespace

void demo_storage_load_modern_graph(const char* graph_name,
                                    unsigned partition_num,
                                    unsigned partition_id) {
  using DEMO_STORAGE_NAMESPACE::demo_storage;
  demo_storage.LoadModernGraph(graph_name, partition_num, partition_id);
}
