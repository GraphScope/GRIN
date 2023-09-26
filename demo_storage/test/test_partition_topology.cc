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
#include "index/order.h"
#include "partition/partition.h"
#include "partition/reference.h"
#include "partition/topology.h"
#include "property/topology.h"
#include "property/type.h"
#include "topology/adjacentlist.h"
#include "topology/edgelist.h"
#include "topology/structure.h"
#include "topology/vertexlist.h"

void check_vertex_list(GRIN_GRAPH g, GRIN_VERTEX_LIST vl) {
  // check vertex list
  auto vl_size = grin_get_vertex_list_size(g, vl);
  auto vl_iter = grin_get_vertex_list_begin(g, vl);
  for (auto i = 0; i < vl_size; ++i) {
    auto v0 = grin_get_vertex_from_list(g, vl, i);
    ASSERT(grin_is_vertex_list_end(g, vl_iter) == false);
    auto v1 = grin_get_vertex_from_iter(g, vl_iter);
    ASSERT(grin_equal_vertex(g, v0, v1) == true);
    grin_get_next_vertex_list_iter(g, vl_iter);
    // destroy vertex
    grin_destroy_vertex(g, v0);
    grin_destroy_vertex(g, v1);
  }
  ASSERT(grin_is_vertex_list_end(g, vl_iter) == true);
  // destroy vertex list iter
  grin_destroy_vertex_list_iter(g, vl_iter);

  std::cout << "(Correct) check vertex list succeed" << std::endl;

  // test vertex order in list
  if (vl_size >= 2) {
    size_t idx0 = 0, idx1 = 1;
    auto v0 = grin_get_vertex_from_list(g, vl, idx0);
    auto v1 = grin_get_vertex_from_list(g, vl, idx1);
    ASSERT(grin_smaller_vertex(g, v0, v1) == true);
    ASSERT(grin_smaller_vertex(g, v1, v0) == false);
    size_t pos0 = grin_get_position_of_vertex_from_sorted_list(g, vl, v0);
    size_t pos1 = grin_get_position_of_vertex_from_sorted_list(g, vl, v1);
    ASSERT(pos0 == idx0);
    ASSERT(pos1 == idx1);

    // destroy vertex
    grin_destroy_vertex(g, v0);
    grin_destroy_vertex(g, v1);

    std::cout << "(Correct) check vertex order succeed" << std::endl;
  }
}

void test_vertex_list(GRIN_PARTITIONED_GRAPH pg, GRIN_GRAPH graph) {
  std::cout << "\n== test vertex list ==" << std::endl;
  // get vertex list
  auto type = grin_get_vertex_type_by_name(graph, "person");
  auto vertex_list = grin_get_vertex_list_by_type(graph, type);
  auto vertex_list_size = grin_get_vertex_list_size(graph, vertex_list);
  std::cout << "vertex list for \"person\", size = " << vertex_list_size
            << std::endl;

  // select master
  auto master_vertex_list =
      grin_get_vertex_list_by_type_select_master(graph, type);
  auto master_vertex_list_size =
      grin_get_vertex_list_size(graph, master_vertex_list);
  std::cout << "master vertex list size = " << master_vertex_list_size
            << std::endl;
  check_vertex_list(graph, master_vertex_list);

  // select mirror
  auto mirror_vertex_list =
      grin_get_vertex_list_by_type_select_mirror(graph, type);
  auto mirror_vertex_list_size =
      grin_get_vertex_list_size(graph, mirror_vertex_list);
  std::cout << "mirror vertex list size = " << mirror_vertex_list_size
            << std::endl;
  check_vertex_list(graph, mirror_vertex_list);

  // check vertex number
  ASSERT(vertex_list_size == master_vertex_list_size + mirror_vertex_list_size);

  // select by partition
  auto partition1 = grin_get_partition_by_id(pg, 1);
  auto vertex_list1 =
      grin_get_vertex_list_by_type_select_partition(graph, type, partition1);
  auto vertex_list1_size = grin_get_vertex_list_size(graph, vertex_list1);
  std::cout << "vertex list size of partition 1 = " << vertex_list1_size
            << std::endl;
  check_vertex_list(graph, vertex_list1);

  // destroy
  grin_destroy_partition(graph, partition1);
  grin_destroy_vertex_list(graph, vertex_list);
  grin_destroy_vertex_list(graph, master_vertex_list);
  grin_destroy_vertex_list(graph, mirror_vertex_list);
  grin_destroy_vertex_list(graph, vertex_list1);
  grin_destroy_vertex_type(graph, type);
}

void check_edge_list(GRIN_GRAPH graph, GRIN_EDGE_LIST edge_list) {
  // check edge list
  auto el_size = grin_get_edge_list_size(graph, edge_list);
  auto el_iter = grin_get_edge_list_begin(graph, edge_list);
  for (auto i = 0; i < el_size; ++i) {
    auto e0 = grin_get_edge_from_list(graph, edge_list, i);
    ASSERT(grin_is_edge_list_end(graph, el_iter) == false);
    auto e1 = grin_get_edge_from_iter(graph, el_iter);
    grin_get_next_edge_list_iter(graph, el_iter);
    auto v0_1 = grin_get_src_vertex_from_edge(graph, e0);
    auto v0_2 = grin_get_dst_vertex_from_edge(graph, e0);
    auto v1_1 = grin_get_src_vertex_from_edge(graph, e1);
    auto v1_2 = grin_get_dst_vertex_from_edge(graph, e1);
    ASSERT(grin_equal_vertex(graph, v0_1, v1_1) == true);
    ASSERT(grin_equal_vertex(graph, v0_2, v1_2) == true);
    // destroy vertex
    grin_destroy_vertex(graph, v0_1);
    grin_destroy_vertex(graph, v0_2);
    grin_destroy_vertex(graph, v1_1);
    grin_destroy_vertex(graph, v1_2);
    // destroy edge
    grin_destroy_edge(graph, e0);
    grin_destroy_edge(graph, e1);
  }

  ASSERT(grin_is_edge_list_end(graph, el_iter) == true);
  // destroy edge list iter
  grin_destroy_edge_list_iter(graph, el_iter);

  std::cout << "(Correct) check edge list succeed" << std::endl;
}

void test_edge_list(GRIN_PARTITIONED_GRAPH pg, GRIN_GRAPH graph) {
  std::cout << "\n== test edge list ==" << std::endl;
  // get edge list
  auto type = grin_get_edge_type_by_name(graph, "created");
  auto edge_list = grin_get_edge_list_by_type(graph, type);
  auto edge_list_size = grin_get_edge_list_size(graph, edge_list);
  std::cout << "edge list for \"created\", size = " << edge_list_size
            << std::endl;

  // select master
  auto master_edge_list = grin_get_edge_list_by_type_select_master(graph, type);
  auto master_edge_list_size = grin_get_edge_list_size(graph, master_edge_list);
  std::cout << "master edge list size = " << master_edge_list_size << std::endl;
  check_edge_list(graph, master_edge_list);

  // select mirror
  auto mirror_edge_list = grin_get_edge_list_by_type_select_mirror(graph, type);
  auto mirror_edge_list_size = grin_get_edge_list_size(graph, mirror_edge_list);
  std::cout << "mirror edge list size = " << mirror_edge_list_size << std::endl;
  check_edge_list(graph, mirror_edge_list);

  // check edge number
  ASSERT(edge_list_size == master_edge_list_size + mirror_edge_list_size);

  // select by partition
  auto partition1 = grin_get_partition_by_id(pg, 1);
  auto edge_list1 =
      grin_get_edge_list_by_type_select_partition(graph, type, partition1);
  auto edge_list1_size = grin_get_edge_list_size(graph, edge_list1);
  std::cout << "edge list size of partition 1 = " << edge_list1_size
            << std::endl;
  check_edge_list(graph, edge_list1);

  // destroy
  grin_destroy_partition(graph, partition1);
  grin_destroy_edge_list(graph, edge_list);
  grin_destroy_edge_list(graph, master_edge_list);
  grin_destroy_edge_list(graph, mirror_edge_list);
  grin_destroy_edge_list(graph, edge_list1);
  grin_destroy_edge_type(graph, type);
}

void check_adjacency_list(GRIN_GRAPH graph, GRIN_ADJACENT_LIST adj_list) {
  // check adjacency list
  auto al_size = grin_get_adjacent_list_size(graph, adj_list);
  auto al_iter = grin_get_adjacent_list_begin(graph, adj_list);
  for (auto i = 0; i < al_size; ++i) {
    auto e0 = grin_get_edge_from_adjacent_list(graph, adj_list, i);
    auto nbr0 = grin_get_neighbor_from_adjacent_list(graph, adj_list, i);
    ASSERT(grin_is_adjacent_list_end(graph, al_iter) == false);
    auto e1 = grin_get_edge_from_adjacent_list_iter(graph, al_iter);
    auto nbr1 = grin_get_neighbor_from_adjacent_list_iter(graph, al_iter);
    grin_get_next_adjacent_list_iter(graph, al_iter);
    auto v0_1 = grin_get_src_vertex_from_edge(graph, e0);
    auto v0_2 = grin_get_dst_vertex_from_edge(graph, e0);
    auto v1_1 = grin_get_src_vertex_from_edge(graph, e1);
    auto v1_2 = grin_get_dst_vertex_from_edge(graph, e1);
    ASSERT(grin_equal_vertex(graph, v0_1, v1_1) == true);
    ASSERT(grin_equal_vertex(graph, v0_2, v1_2) == true);
    ASSERT(grin_equal_vertex(graph, nbr0, nbr1) == true);
    // destroy vertex
    grin_destroy_vertex(graph, v0_1);
    grin_destroy_vertex(graph, v0_2);
    grin_destroy_vertex(graph, v1_1);
    grin_destroy_vertex(graph, v1_2);
    grin_destroy_vertex(graph, nbr0);
    grin_destroy_vertex(graph, nbr1);
    // destroy edge
    grin_destroy_edge(graph, e0);
    grin_destroy_edge(graph, e1);
  }

  ASSERT(grin_is_adjacent_list_end(graph, al_iter) == true);
  // destroy adjacency list iter
  grin_destroy_adjacent_list_iter(graph, al_iter);

  std::cout << "(Correct) check adjacency list succeed" << std::endl;
}

void test_adjacency_list(GRIN_PARTITIONED_GRAPH pg, GRIN_GRAPH graph,
                         GRIN_VERTEX vertex, GRIN_DIRECTION dir) {
  std::cout << "\n== test adjacency list: ";
  if (dir == GRIN_DIRECTION::IN)
    std::cout << "IN  ==" << std::endl;
  else if (dir == GRIN_DIRECTION::OUT)
    std::cout << "OUT  ==" << std::endl;
  else
    std::cout << "BOTH  ==" << std::endl;

  // get adjacency list
  auto edge_type = grin_get_edge_type_by_name(graph, "knows");
  auto adj_list =
      grin_get_adjacent_list_by_edge_type(graph, dir, vertex, edge_type);
  auto al_size = grin_get_adjacent_list_size(graph, adj_list);
  std::cout << "adjacency list of \"knows\" for vertex #3, size = " << al_size
            << std::endl;

  // select master
  auto master_adj_list =
      grin_get_adjacent_list_by_edge_type_select_master_neighbor(
          graph, dir, vertex, edge_type);
  auto master_al_size = grin_get_adjacent_list_size(graph, master_adj_list);
  std::cout << "master adjacency list size = " << master_al_size << std::endl;
  check_adjacency_list(graph, master_adj_list);

  // select mirror
  auto mirror_adj_list =
      grin_get_adjacent_list_by_edge_type_select_mirror_neighbor(
          graph, dir, vertex, edge_type);
  auto mirror_al_size = grin_get_adjacent_list_size(graph, mirror_adj_list);
  std::cout << "mirror adjacency list size = " << mirror_al_size << std::endl;
  check_adjacency_list(graph, mirror_adj_list);

  // check adjacency list size
  ASSERT(al_size == master_al_size + mirror_al_size);

  // select by partition
  auto partition1 = grin_get_partition_by_id(pg, 2);
  auto adj_list2 =
      grin_get_adjacent_list_by_edge_type_select_partition_neighbor(
          graph, dir, vertex, edge_type, partition1);
  auto adj_list2_size = grin_get_adjacent_list_size(graph, adj_list2);
  std::cout << "adjacency list size of partition 2 = " << adj_list2_size
            << std::endl;
  check_adjacency_list(graph, adj_list2);

  // destroy
  grin_destroy_partition(graph, partition1);
  grin_destroy_adjacent_list(graph, adj_list);
  grin_destroy_adjacent_list(graph, master_adj_list);
  grin_destroy_adjacent_list(graph, mirror_adj_list);
  grin_destroy_adjacent_list(graph, adj_list2);
  grin_destroy_edge_type(graph, edge_type);
}

void test_partition_topology(GRIN_PARTITIONED_GRAPH pg, unsigned n) {
  std::cout << "\n++++ test partition: topology ++++" << std::endl;

  // check partition number
  ASSERT(pg != GRIN_NULL_GRAPH);
  auto partition_num = grin_get_total_partitions_number(pg);
  ASSERT(partition_num == n);

  // local partitions
  auto partition_list = grin_get_local_partition_list(pg);
  ASSERT(partition_list != GRIN_NULL_PARTITION_LIST);
  auto partition_list_size = grin_get_partition_list_size(pg, partition_list);
  ASSERT(partition_list_size == 1);

  for (auto idx = 0; idx < partition_list_size; ++idx) {
    auto partition_id = grin_get_partition_from_list(pg, partition_list, idx);
    std::cout << "partition id = " << partition_id << std::endl;
    // create a local graph
    auto partition = grin_get_partition_by_id(pg, partition_id);
    auto graph = grin_get_local_graph_by_partition(pg, partition);

    // get vertex
    auto vtype = grin_get_vertex_type_by_name(graph, "person");
    auto vertex_list = grin_get_vertex_list_by_type(graph, vtype);
    auto vertex = grin_get_vertex_from_list(graph, vertex_list, 3);

    // test
    test_vertex_list(pg, graph);
    test_edge_list(pg, graph);
    test_adjacency_list(pg, graph, vertex, GRIN_DIRECTION::IN);
    test_adjacency_list(pg, graph, vertex, GRIN_DIRECTION::OUT);
    test_adjacency_list(pg, graph, vertex, GRIN_DIRECTION::BOTH);

    // destroy
    grin_destroy_vertex_type(graph, vtype);
    grin_destroy_vertex_list(graph, vertex_list);
    grin_destroy_vertex(graph, vertex);
    grin_destroy_partition(pg, partition);
    grin_destroy_graph(graph);
  }

  grin_destroy_partition_list(pg, partition_list);
  std::cout << "\n---- test partition: topology completed ----" << std::endl;
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
  test_partition_topology(pg, partition_num);

  // destroy partitioned graph
  grin_destroy_partitioned_graph(pg);

  return 0;
}
