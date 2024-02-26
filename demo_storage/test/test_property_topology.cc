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
#include "property/topology.h"
#include "property/type.h"
#include "topology/adjacentlist.h"
#include "topology/edgelist.h"
#include "topology/structure.h"
#include "topology/vertexlist.h"

void test_property_topology_vertex(GRIN_GRAPH graph) {
  std::cout << "\n++++ test property: topology (vertex) ++++" << std::endl;

  // get vertex type list
  auto vertex_type_list = grin_get_vertex_type_list(graph);
  size_t n = grin_get_vertex_type_list_size(graph, vertex_type_list);
  std::cout << "size of vertex type list = " << n << std::endl;

  for (auto i = 0; i < n; i++) {
    std::cout << "\n== vertex type " << i << ": ==" << std::endl;

    // get vertex type from vertex type list
    auto vertex_type =
        grin_get_vertex_type_from_list(graph, vertex_type_list, i);
    auto name = grin_get_vertex_type_name(graph, vertex_type);
    size_t m = grin_get_vertex_num_by_type(graph, vertex_type);
    std::cout << "name of vertex type " << i << ": " << name << std::endl;
    std::cout << "vertex num of vertex type " << i << " = " << m << std::endl;

    // select vertex list
    auto select_vertex_list = grin_get_vertex_list_by_type(graph, vertex_type);
    std::cout << "size of vertex list of vertex type " << i << " = "
              << grin_get_vertex_list_size(graph, select_vertex_list)
              << std::endl;
    ASSERT(grin_get_vertex_list_size(graph, select_vertex_list) == m);

    // destroy
    grin_destroy_vertex_type(graph, vertex_type);
    grin_destroy_vertex_list(graph, select_vertex_list);
  }

  // destroy
  grin_destroy_vertex_type_list(graph, vertex_type_list);

  std::cout << "---- test property: topology (vertex) completed ----"
            << std::endl;
}

void test_property_topology_edge(GRIN_GRAPH graph) {
  std::cout << "\n++++ test property: topology (edge) ++++" << std::endl;

  // get edge type list
  auto edge_type_list = grin_get_edge_type_list(graph);
  size_t n = grin_get_edge_type_list_size(graph, edge_type_list);
  std::cout << "size of edge type list = " << n << std::endl;

  for (auto i = 0; i < n; i++) {
    std::cout << "\n== edge type " << i << ": ==" << std::endl;

    // get edge type from edge type list
    auto edge_type = grin_get_edge_type_from_list(graph, edge_type_list, i);
    size_t m = grin_get_edge_num_by_type(graph, edge_type);
    std::cout << "edge num of edge type " << i << " = " << m << std::endl;
    auto name = grin_get_edge_type_name(graph, edge_type);
    std::cout << "name of edge type " << i << ": " << name << std::endl;

    // select edge list
    auto select_edge_list = grin_get_edge_list_by_type(graph, edge_type);
    auto it = grin_get_edge_list_begin(graph, select_edge_list);
    auto count = 0;
    while (grin_is_edge_list_end(graph, it) == false) {
      grin_get_next_edge_list_iter(graph, it);
      count++;
    }
    ASSERT(count == m);
    std::cout << "size of edge list of edge type " << i << " = " << m
              << std::endl;

    // destroy
    grin_destroy_edge_list_iter(graph, it);
    grin_destroy_edge_list(graph, select_edge_list);
    grin_destroy_edge_type(graph, edge_type);
  }

  // destroy
  grin_destroy_edge_type_list(graph, edge_type_list);

  std::cout << "---- test property: topology (edge) completed ----"
            << std::endl;
}

void test_property_topology_adj_list(GRIN_GRAPH graph) {
  std::cout << "\n++++ test property: topology (adj_list) ++++" << std::endl;

  // get edge type list
  auto edge_type_list = grin_get_edge_type_list(graph);
  size_t ne = grin_get_edge_type_list_size(graph, edge_type_list);
  std::cout << "size of edge type list = " << ne << std::endl;

  // get vertex type list
  auto vertex_type_list = grin_get_vertex_type_list(graph);
  size_t nv = grin_get_vertex_type_list_size(graph, vertex_type_list);
  std::cout << "size of vertex type list = " << nv << std::endl;

  // get vertex
  auto vtype = grin_get_vertex_type_by_id(graph, 0);
  auto vertex_list = grin_get_vertex_list_by_type(graph, vtype);
  auto v = grin_get_vertex_from_list(graph, vertex_list, 3);

  // get adj list of vertex
  for (auto i = 0; i < ne; i++) {
    std::cout << "\n== edge type " << i << ": ==" << std::endl;

    // get edge type from edge type list
    auto edge_type = grin_get_edge_type_from_list(graph, edge_type_list, i);

    // get adj list by edge type
    auto select_adj_list = grin_get_adjacent_list_by_edge_type(
        graph, GRIN_DIRECTION::BOTH, v, edge_type);
    auto adj_list_it = grin_get_adjacent_list_begin(graph, select_adj_list);
    auto adj_list_size = 0;
    while (grin_is_adjacent_list_end(graph, adj_list_it) == false) {
      grin_get_next_adjacent_list_iter(graph, adj_list_it);
      adj_list_size++;
    }
    std::cout << "adj list size (BOTH) of edge type " << i
              << " for vertex #3 = " << adj_list_size << std::endl;

    // destroy
    grin_destroy_adjacent_list_iter(graph, adj_list_it);
    grin_destroy_adjacent_list(graph, select_adj_list);
    grin_destroy_edge_type(graph, edge_type);
  }

  // destroy
  grin_destroy_vertex_list(graph, vertex_list);
  grin_destroy_vertex_type(graph, vtype);
  grin_destroy_vertex_type_list(graph, vertex_type_list);
  grin_destroy_edge_type_list(graph, edge_type_list);

  std::cout << "---- test property: topology (adj_list) completed ----"
            << std::endl;
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

  // test property topology (vertex)
  test_property_topology_vertex(graph);

  // test property topology (edge)
  test_property_topology_edge(graph);

  // test property topology (adj_list)
  test_property_topology_adj_list(graph);

  // destroy graph
  grin_destroy_graph(graph);

  return 0;
}
