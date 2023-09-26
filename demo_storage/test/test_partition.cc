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

#include <iostream>

// predefine for GRIN
#include "../predefine.h"
// storage headers
#include "storage/loadmoderngraph.h"
// test config headers
#include "test/config.h"
// GRIN headers
#include "partition/partition.h"
#include "topology/structure.h"

void test_partition_partition(GRIN_PARTITIONED_GRAPH pg, unsigned n) {
  std::cout << "\n++++ test partition: partition ++++" << std::endl;

  // check partition number
  ASSERT(pg != GRIN_NULL_GRAPH);
  auto partition_num = grin_get_total_partitions_number(pg);
  ASSERT(partition_num == n);
  std::cout << "partition number = " << partition_num << std::endl;

  // check partition list
  auto partition_list = grin_get_local_partition_list(pg);
  ASSERT(partition_list != GRIN_NULL_PARTITION_LIST);
  auto partition_list_size = grin_get_partition_list_size(pg, partition_list);
  ASSERT(partition_list_size == 1);
  std::cout << "local partition number = " << partition_list_size << std::endl;

  // check create new partition list
  auto new_partition_list = grin_create_partition_list(pg);
  ASSERT(new_partition_list != GRIN_NULL_PARTITION_LIST);
  for (auto i = 0; i < partition_list_size; ++i) {
    // get & insert partition
    auto partition = grin_get_partition_from_list(pg, partition_list, i);
    auto status =
        grin_insert_partition_to_list(pg, new_partition_list, partition);
    ASSERT(status == true);
    // check & destroy partition
    auto partition_from_new_list =
        grin_get_partition_from_list(pg, new_partition_list, i);
    ASSERT(grin_equal_partition(pg, partition, partition_from_new_list) ==
           true);
    grin_destroy_partition(pg, partition);
    grin_destroy_partition(pg, partition_from_new_list);
  }
  ASSERT(grin_get_partition_list_size(pg, new_partition_list) ==
         partition_list_size);
  grin_destroy_partition_list(pg, new_partition_list);

  // check partition id
  auto partition_a = grin_get_partition_from_list(pg, partition_list, 0);
  auto id = grin_get_partition_id(pg, partition_a);
  auto partition_b = grin_get_partition_by_id(pg, id);
  ASSERT(grin_equal_partition(pg, partition_a, partition_b) == true);
  grin_destroy_partition(pg, partition_a);
  grin_destroy_partition(pg, partition_b);

  // check get local graph
  for (auto i = 0; i < partition_list_size; ++i) {
    // get local graph from partition
    auto partition = grin_get_partition_from_list(pg, partition_list, i);
    auto info = grin_get_partition_info(pg, partition);
    std::cout << "info of local partition " << i << std::endl;
    std::cout << "    " << static_cast<const char*>(info) << std::endl;
    auto graph = grin_get_local_graph_by_partition(pg, partition);
    ASSERT(graph != GRIN_NULL_GRAPH);
    // destroy
    grin_destroy_partition(pg, partition);
    grin_destroy_graph(graph);
  }

  // destroy
  grin_destroy_partition_list(pg, partition_list);
  std::cout << "---- test partition: partition completed ----" << std::endl;
}

int main() {
  // load graph
  uint32_t partition_num = 4;
  uint32_t partition_id = 0;
  std::cout << "load modern graph, partition_num = " << partition_num
            << ", partition_id = " << partition_id << std::endl;
  std::string graph_name = "modern_graph";
  char* graph_name_str = new char[graph_name.size() + 1];
  snprintf(graph_name_str, graph_name.size() + 1, "%s", graph_name.c_str());
  demo_storage_load_modern_graph(graph_name_str, partition_num, partition_id);
  delete[] graph_name_str;

  // get grin graph
  std::string uri = "demo_storage://" + graph_name +
                    "?partition_num=" + std::to_string(partition_num);
  std::cout << "get grin graph from uri: " << uri << std::endl;
  char* uri_str = new char[uri.size() + 1];
  snprintf(uri_str, uri.size() + 1, "%s", uri.c_str());
  GRIN_PARTITIONED_GRAPH pg = grin_get_partitioned_graph_from_storage(uri_str);
  delete[] uri_str;

  // test partitioned graph
  test_partition_partition(pg, partition_num);

  // destroy partitioned graph
  grin_destroy_partitioned_graph(pg);

  return 0;
}
