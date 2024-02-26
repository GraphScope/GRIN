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
#include "index/internal_id.h"
#include "index/label.h"
#include "index/order.h"
#include "property/label.h"
#include "property/topology.h"
#include "property/type.h"
#include "topology/edgelist.h"
#include "topology/structure.h"
#include "topology/vertexlist.h"

void test_vertex_label(GRIN_GRAPH graph) {
  std::cout << "\n++++ test index: vertex label ++++" << std::endl;
  auto vertex_label_list = grin_get_vertex_label_list(graph);
  auto vertex_label_list_size =
      grin_get_label_list_size(graph, vertex_label_list);
  std::cout << "vertex label list size: " << vertex_label_list_size
            << std::endl;

  for (size_t i = 0; i < vertex_label_list_size; ++i) {
    auto vertex_label = grin_get_label_from_list(graph, vertex_label_list, i);
    auto vertex_label_name = grin_get_label_name(graph, vertex_label);
    std::cout << "vertex label name: " << vertex_label_name << std::endl;
    auto vertex_label_2 = grin_get_label_by_name(graph, vertex_label_name);
    ASSERT(vertex_label == vertex_label_2);

    // get vertex types by label
    auto vertex_type_list =
        grin_get_vertex_type_list_by_label(graph, vertex_label);
    auto vertex_type_list_size =
        grin_get_label_list_size(graph, vertex_type_list);
    std::cout << "vertex type list size for this label: "
              << vertex_type_list_size << std::endl;

    // destroy
    grin_destroy_label(graph, vertex_label);
    grin_destroy_label(graph, vertex_label_2);
    grin_destroy_vertex_type_list(graph, vertex_type_list);
  }

  // destroy vertex label list
  grin_destroy_label_list(graph, vertex_label_list);

  auto vertex_type = grin_get_vertex_type_by_name(graph, "person");
  auto vertex_list = grin_get_vertex_list_by_type(graph, vertex_type);
  auto vertex = grin_get_vertex_from_list(graph, vertex_list, 0);
  auto label_list = grin_get_label_list_by_vertex(graph, vertex);
  auto label_list_size = grin_get_label_list_size(graph, label_list);
  std::cout << "label list size for vertex person #0: " << label_list_size
            << std::endl;

  for (size_t i = 0; i < label_list_size; ++i) {
    auto label = grin_get_label_from_list(graph, label_list, i);
    auto label_name = grin_get_label_name(graph, label);
    std::cout << "label name: " << label_name << std::endl;
    grin_destroy_label(graph, label);
  }

  // get vertex label list by type
  auto label_list_2 = grin_get_label_list_by_vertex_type(graph, vertex_type);
  auto label_list_size_2 = grin_get_label_list_size(graph, label_list_2);
  std::cout << "label list size for vertex type #0: " << label_list_size_2
            << std::endl;

  // get vertex list by label
  auto label = grin_get_label_by_name(graph, "v_label_0");
  auto vertex_list_2 =
      grin_get_vertex_list_by_type_by_label(graph, vertex_type, label);
  auto vertex_list_size = grin_get_vertex_list_size(graph, vertex_list_2);
  std::cout << "vertex list size for v_label_0 of type #0: " << vertex_list_size
            << std::endl;

  // check array & iterator
  auto iter = grin_get_vertex_list_begin(graph, vertex_list_2);
  for (size_t i = 0; i < vertex_list_size; ++i) {
    ASSERT(!grin_is_vertex_list_end(graph, iter));
    auto vertex = grin_get_vertex_from_list(graph, vertex_list_2, i);
    auto vertex2 = grin_get_vertex_from_iter(graph, iter);
    ASSERT(vertex == vertex2);
    auto id = grin_get_vertex_internal_id_by_type(graph, vertex_type, vertex);
    std::cout << "vertex internal id: " << id << std::endl;
    // check order
    auto pos = grin_get_position_of_vertex_from_sorted_list(
        graph, vertex_list_2, vertex);
    ASSERT(pos == i);
    // get next & destroy
    grin_get_next_vertex_list_iter(graph, iter);
    grin_destroy_vertex(graph, vertex);
    grin_destroy_vertex(graph, vertex2);
  }
  ASSERT(grin_is_vertex_list_end(graph, iter));
  grin_destroy_vertex_list_iter(graph, iter);
  std::cout << "check array & iterator done" << std::endl;

  // destroy
  grin_destroy_label(graph, label);
  grin_destroy_label_list(graph, label_list);
  grin_destroy_label_list(graph, label_list_2);
  grin_destroy_vertex(graph, vertex);
  grin_destroy_vertex_list(graph, vertex_list);
  grin_destroy_vertex_type(graph, vertex_type);
  grin_destroy_vertex_list(graph, vertex_list_2);
}

void test_edge_label(GRIN_GRAPH graph) {
  std::cout << "\n++++ test index: edge label ++++" << std::endl;
  auto edge_label_list = grin_get_edge_label_list(graph);
  auto edge_label_list_size = grin_get_label_list_size(graph, edge_label_list);
  std::cout << "edge label list size: " << edge_label_list_size << std::endl;

  for (size_t i = 0; i < edge_label_list_size; ++i) {
    auto edge_label = grin_get_label_from_list(graph, edge_label_list, i);
    auto edge_label_name = grin_get_label_name(graph, edge_label);
    std::cout << "edge label name: " << edge_label_name << std::endl;
    auto edge_label_2 = grin_get_label_by_name(graph, edge_label_name);
    ASSERT(edge_label == edge_label_2);

    // get vertex types by label
    auto edge_type_list = grin_get_edge_type_list_by_label(graph, edge_label);
    auto edge_type_list_size = grin_get_label_list_size(graph, edge_type_list);
    std::cout << "edge type list size for this label: " << edge_type_list_size
              << std::endl;

    // destroy
    grin_destroy_label(graph, edge_label);
    grin_destroy_label(graph, edge_label_2);
    grin_destroy_vertex_type_list(graph, edge_type_list);
  }

  // destroy edge label list
  grin_destroy_label_list(graph, edge_label_list);

  auto edge_type = grin_get_edge_type_by_name(graph, "knows");
  auto edge_list = grin_get_edge_list_by_type(graph, edge_type);
  auto edge = grin_get_edge_from_list(graph, edge_list, 0);
  auto label_list = grin_get_label_list_by_edge(graph, edge);
  auto label_list_size = grin_get_label_list_size(graph, label_list);
  std::cout << "label list size for edge knows #0: " << label_list_size
            << std::endl;

  for (size_t i = 0; i < label_list_size; ++i) {
    auto label = grin_get_label_from_list(graph, label_list, i);
    auto label_name = grin_get_label_name(graph, label);
    std::cout << "label name: " << label_name << std::endl;
    grin_destroy_label(graph, label);
  }

  // get edge label list by type
  auto label_list_2 = grin_get_label_list_by_edge_type(graph, edge_type);
  auto label_list_size_2 = grin_get_label_list_size(graph, label_list_2);
  std::cout << "label list size for edge type #0: " << label_list_size_2
            << std::endl;

  // get edge list by label
  auto label = grin_get_label_by_name(graph, "e_label_0");
  auto edge_list_2 =
      grin_get_edge_list_by_type_by_label(graph, edge_type, label);
  auto edge_list_size = grin_get_edge_list_size(graph, edge_list_2);
  std::cout << "edge list size for e_label_0 of type #0: " << edge_list_size
            << std::endl;

  // check array & iterator
  auto iter = grin_get_edge_list_begin(graph, edge_list_2);
  for (size_t i = 0; i < edge_list_size; ++i) {
    ASSERT(!grin_is_edge_list_end(graph, iter));
    auto edge = grin_get_edge_from_list(graph, edge_list_2, i);
    auto edge2 = grin_get_edge_from_iter(graph, iter);
    ASSERT(edge == edge2);
    std::cout << "edge " << i << std::endl;
    // get next & destroy
    grin_destroy_edge(graph, edge);
    grin_destroy_edge(graph, edge2);
    grin_get_next_edge_list_iter(graph, iter);
  }
  ASSERT(grin_is_edge_list_end(graph, iter));
  grin_destroy_edge_list_iter(graph, iter);
  std::cout << "check array & iterator done" << std::endl;

  // destroy
  grin_destroy_label(graph, label);
  grin_destroy_label_list(graph, label_list);
  grin_destroy_label_list(graph, label_list_2);
  grin_destroy_edge(graph, edge);
  grin_destroy_edge_list(graph, edge_list);
  grin_destroy_edge_type(graph, edge_type);
  grin_destroy_edge_list(graph, edge_list_2);
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

  // test vertex label
  test_vertex_label(graph);

  // test edge label
  test_edge_label(graph);

  // destroy graph
  grin_destroy_graph(graph);

  return 0;
}
