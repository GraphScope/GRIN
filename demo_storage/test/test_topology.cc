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
#include <string>

// predefine for GRIN
#include "../predefine.h"
// storage headers
#include "storage/loadmoderngraph.h"
// test config headers
#include "test/config.h"
// GRIN headers
#include "property/topology.h"
#include "property/type.h"
#include "topology/adjacentlist.h"
#include "topology/edgelist.h"
#include "topology/structure.h"
#include "topology/vertexlist.h"

void test_topology_structure(GRIN_GRAPH graph) {
  std::cout << "\n++++ test topology: structure ++++" << std::endl;

  std::cout << "is directed: " << grin_is_directed(graph) << std::endl;

  std::cout << "is multigraph: " << grin_is_multigraph(graph) << std::endl;

  std::cout << "---- test topology: structure ----" << std::endl;
}

void test_topology_vertexlist(GRIN_GRAPH graph) {
  std::cout << "\n++++ test topology: vertexlist ++++" << std::endl;
  // get vertex list
  auto vtype = grin_get_vertex_type_by_name(graph, "person");
  auto vertex_list = grin_get_vertex_list_by_type(graph, vtype);

  // test vertex list array
  auto n = grin_get_vertex_list_size(graph, vertex_list);
  std::cout << "vertex list size = " << n << std::endl;
  auto v0 = grin_get_vertex_from_list(graph, vertex_list, 0);
  auto v1 = grin_get_vertex_from_list(graph, vertex_list, 1);
  auto v2 = grin_get_vertex_from_list(graph, vertex_list, 100000000);
  ASSERT(grin_equal_vertex(graph, v0, v0) == true);
  ASSERT(grin_equal_vertex(graph, v0, v1) == false);
  ASSERT(v2 == GRIN_NULL_VERTEX);

  grin_destroy_vertex(graph, v0);
  grin_destroy_vertex(graph, v1);

  // test vertex list iterator
  auto it = grin_get_vertex_list_begin(graph, vertex_list);
  auto count = 0;
  while (grin_is_vertex_list_end(graph, it) == false) {
    auto v = grin_get_vertex_from_iter(graph, it);
    // methods on vertex
    auto vdata_type = grin_get_vertex_data_datatype(graph, v);
    auto vdata = grin_get_vertex_data_value(graph, v);
    if (vdata_type == GRIN_DATATYPE::Int64)
      std::cout << "data of \"person\" vertex #" << count << " = "
                << *static_cast<const int64_t*>(vdata) << std::endl;
    if (vdata_type == GRIN_DATATYPE::String)
      std::cout << "data of \"person\" vertex #" << count << " = "
                << static_cast<const char*>(vdata) << std::endl;
    grin_destroy_vertex(graph, v);
    grin_get_next_vertex_list_iter(graph, it);
    count++;
  }
  ASSERT(count == n);
  grin_destroy_vertex_list_iter(graph, it);

  // destroy vertex list
  grin_destroy_vertex_list(graph, vertex_list);
  grin_destroy_vertex_type(graph, vtype);

  std::cout << "---- test topology: vertexlist ----" << std::endl;
}

void test_topology_edgelist(GRIN_GRAPH graph) {
  std::cout << "\n++++ test topology: edgelist ++++" << std::endl;
  // get edge list
  auto etype = grin_get_edge_type_by_name(graph, "knows");
  auto edge_list = grin_get_edge_list_by_type(graph, etype);

  // test edge list array
  auto n = grin_get_edge_list_size(graph, edge_list);
  std::cout << "edge list size = " << n << std::endl;
  auto e0 = grin_get_edge_from_list(graph, edge_list, 0);
  auto e1 = grin_get_edge_from_list(graph, edge_list, 1);
  auto e2 = grin_get_edge_from_list(graph, edge_list, 100000000);
  ASSERT(e2 == GRIN_NULL_EDGE);

  grin_destroy_vertex(graph, e0);
  grin_destroy_vertex(graph, e1);

  // test edge list iterator
  auto it = grin_get_edge_list_begin(graph, edge_list);
  auto count = 0;
  while (grin_is_edge_list_end(graph, it) == false) {
    // methods on edge
    auto e = grin_get_edge_from_iter(graph, it);
    auto v1 = grin_get_src_vertex_from_edge(graph, e);
    auto v2 = grin_get_dst_vertex_from_edge(graph, e);
    auto edata_type = grin_get_edge_data_datatype(graph, e);
    auto edata = grin_get_edge_data_value(graph, e);
    if (edata_type == GRIN_DATATYPE::Double)
      std::cout << "data of \"knows\" edge #" << count << " = "
                << *static_cast<const double*>(edata) << std::endl;

    grin_destroy_vertex(graph, v1);
    grin_destroy_vertex(graph, v2);
    grin_destroy_edge(graph, e);
    grin_get_next_edge_list_iter(graph, it);
    count++;
  }
  std::cout << "edge list size = " << count << std::endl;
  grin_destroy_edge_list_iter(graph, it);

  // destroy edge list
  grin_destroy_edge_list(graph, edge_list);
  grin_destroy_edge_type(graph, etype);

  std::cout << "---- test topology: edgelist -----" << std::endl;
}

void test_topology_adjlist(GRIN_GRAPH graph, GRIN_DIRECTION direction) {
  std::cout << "test topology: adjlist ";
  if (direction == GRIN_DIRECTION::IN)
    std::cout << "IN" << std::endl;
  else if (direction == GRIN_DIRECTION::OUT)
    std::cout << "OUT" << std::endl;
  else
    std::cout << "BOTH" << std::endl;
  // get adj list
  auto vtype = grin_get_vertex_type_by_name(graph, "person");
  auto vertex_list = grin_get_vertex_list_by_type(graph, vtype);
  auto etype = grin_get_edge_type_by_name(graph, "knows");
  auto v = grin_get_vertex_from_list(graph, vertex_list, 3);
  auto adj_list =
      grin_get_adjacent_list_by_edge_type(graph, direction, v, etype);
  auto n = grin_get_adjacent_list_size(graph, adj_list);

  // iterate adj list
  auto it = grin_get_adjacent_list_begin(graph, adj_list);
  auto count = 0;
  while (grin_is_adjacent_list_end(graph, it) == false) {
    // iterator
    auto e = grin_get_edge_from_adjacent_list_iter(graph, it);
    auto v1 = grin_get_src_vertex_from_edge(graph, e);
    auto v2 = grin_get_dst_vertex_from_edge(graph, e);
    auto nbr = grin_get_neighbor_from_adjacent_list_iter(graph, it);
    // array
    auto e_ = grin_get_edge_from_adjacent_list(graph, adj_list, count);
    auto v1_ = grin_get_src_vertex_from_edge(graph, e_);
    auto v2_ = grin_get_dst_vertex_from_edge(graph, e_);
    auto nbr_ = grin_get_neighbor_from_adjacent_list(graph, adj_list, count);

    // check src & dst
    ASSERT(grin_equal_vertex(graph, v1, v1_) == true);
    ASSERT(grin_equal_vertex(graph, v2, v2_) == true);
    ASSERT(grin_equal_vertex(graph, v2, v) == true &&
               grin_equal_vertex(graph, v1, nbr) == true ||
           grin_equal_vertex(graph, v1, v) == true &&
               grin_equal_vertex(graph, v2, nbr) == true);

    grin_destroy_vertex(graph, v1);
    grin_destroy_vertex(graph, v2);
    grin_destroy_vertex(graph, nbr);
    grin_destroy_edge(graph, e);
    grin_destroy_vertex(graph, v1_);
    grin_destroy_vertex(graph, v2_);
    grin_destroy_vertex(graph, nbr_);
    grin_destroy_edge(graph, e_);
    grin_get_next_adjacent_list_iter(graph, it);
    count++;
  }
  ASSERT(count == n);
  std::cout << "adj list size of \"person\" vertex #3 = " << count << std::endl;
  grin_destroy_adjacent_list_iter(graph, it);

  // destory
  grin_destroy_vertex(graph, v);
  grin_destroy_vertex_list(graph, vertex_list);
  grin_destroy_vertex_type(graph, vtype);
  grin_destroy_edge_type(graph, etype);
  grin_destroy_adjacent_list(graph, adj_list);
}

void test_topology_adjlist(GRIN_GRAPH graph) {
  std::cout << "\n++++ test topology: adjlist ++++" << std::endl;

  test_topology_adjlist(graph, GRIN_DIRECTION::IN);

  test_topology_adjlist(graph, GRIN_DIRECTION::OUT);

  test_topology_adjlist(graph, GRIN_DIRECTION::BOTH);

  std::cout << "---- test topology: adjlist ----" << std::endl;
}

int main() {
  // load graph
  std::cout << "load modern graph" << std::endl;
  std::string graph_name = "modern_graph";
  char* graph_name_str = new char[graph_name.size() + 1];
  snprintf(graph_name_str, graph_name.size() + 1, "%s", graph_name.c_str());
  demo_storage_load_modern_graph(graph_name_str, 1, 0);
  delete[] graph_name_str;

  // get grin graph
  std::string uri = "demo_storage://" + graph_name;
  std::cout << "get grin graph from uri: " << uri << std::endl;
  char* uri_str = new char[uri.size() + 1];
  snprintf(uri_str, uri.size() + 1, "%s", uri.c_str());
  GRIN_GRAPH graph = grin_get_graph_from_storage(uri_str);
  delete[] uri_str;

  // test topology structure
  test_topology_structure(graph);

  // test topology vertexlist
  test_topology_vertexlist(graph);

  // test topology edgelist
  test_topology_edgelist(graph);

  // test topology adjlist
  test_topology_adjlist(graph);

  // destroy graph
  grin_destroy_graph(graph);

  return 0;
}
