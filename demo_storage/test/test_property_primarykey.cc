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
#include "property/primarykey.h"
#include "property/property.h"
#include "property/propertylist.h"
#include "property/row.h"
#include "property/topology.h"
#include "property/type.h"
#include "property/value.h"
#include "topology/edgelist.h"
#include "topology/structure.h"
#include "topology/vertexlist.h"

void test_vertex_property_primarykey(GRIN_GRAPH graph) {
  std::cout << "\n++++ test property: primarykey (vertex) ++++" << std::endl;

  // get vertex types with primary key
  auto primary_vertex_type_list =
      grin_get_vertex_types_with_primary_keys(graph);
  size_t n = grin_get_vertex_type_list_size(graph, primary_vertex_type_list);
  std::cout << "number of vertex types with primary keys: " << n << std::endl;

  for (auto idx = 0; idx < n; ++idx) {
    // get vertex type
    auto vertex_type =
        grin_get_vertex_type_from_list(graph, primary_vertex_type_list, idx);
    std::cout << "\n---- test vertex type with primary key: "
              << grin_get_vertex_type_name(graph, vertex_type) << " ----"
              << std::endl;

    // get the property list for primary key
    auto property_list =
        grin_get_primary_keys_by_vertex_type(graph, vertex_type);
    std::cout << "size of property list for primary key: "
              << grin_get_vertex_property_list_size(graph, property_list)
              << std::endl;

    // get row of primary keys for vertex A
    std::cout << "get row of primary keys for vertex #0" << std::endl;

    auto vertex_list = grin_get_vertex_list_by_type(graph, vertex_type);
    auto vertex = grin_get_vertex_from_list(graph, vertex_list, 0);
    auto row = grin_get_vertex_primary_keys_row(graph, vertex);

    auto property_list_size =
        grin_get_vertex_property_list_size(graph, property_list);
    for (auto i = 0; i < property_list_size; ++i) {
      auto property =
          grin_get_vertex_property_from_list(graph, property_list, i);
      ASSERT(grin_get_vertex_property_datatype(graph, property) ==
             GRIN_DATATYPE::Int64);
      auto value =
          grin_get_vertex_property_value_of_int64(graph, vertex, property);
      auto value_in_row = grin_get_int64_from_row(graph, row, i);
      ASSERT(value == value_in_row);
      std::cout << "primary key: "
                << grin_get_vertex_property_name(graph, vertex_type, property)
                << ", value: " << value << std::endl;
      grin_destroy_vertex_property(graph, property);
    }

    // destroy
    grin_destroy_vertex_property_list(graph, property_list);
    grin_destroy_vertex_type(graph, vertex_type);
    grin_destroy_vertex_list(graph, vertex_list);
    grin_destroy_vertex(graph, vertex);
    grin_destroy_row(graph, row);
  }
  // destroy vertex type list
  grin_destroy_vertex_type_list(graph, primary_vertex_type_list);

  std::cout << "---- test property: primarykey (vertex) completed ----"
            << std::endl;
}

void test_edge_property_primarykey(GRIN_GRAPH graph) {
  std::cout << "\n++++ test property: primarykey (edge) ++++" << std::endl;

  // get edge types with primary key
  auto primary_edge_type_list = grin_get_edge_types_with_primary_keys(graph);
  size_t n = grin_get_edge_type_list_size(graph, primary_edge_type_list);
  std::cout << "number of edge types with primary keys: " << n << std::endl;

  for (auto idx = 0; idx < n; ++idx) {
    // get edge type
    auto edge_type =
        grin_get_edge_type_from_list(graph, primary_edge_type_list, idx);
    std::cout << "\n---- test edge type with primary key: "
              << grin_get_edge_type_name(graph, edge_type) << " ----"
              << std::endl;

    // get the property list for primary key
    auto property_list = grin_get_primary_keys_by_edge_type(graph, edge_type);
    std::cout << "size of property list for primary key: "
              << grin_get_edge_property_list_size(graph, property_list)
              << std::endl;

    // get row of primary keys for edge A
    std::cout << "get row of primary keys for edge #0" << std::endl;

    auto edge_list = grin_get_edge_list_by_type(graph, edge_type);
    auto edge = grin_get_edge_from_list(graph, edge_list, 0);
    auto row = grin_get_edge_primary_keys_row(graph, edge);

    auto property_list_size =
        grin_get_edge_property_list_size(graph, property_list);
    for (auto i = 0; i < property_list_size; ++i) {
      auto property = grin_get_edge_property_from_list(graph, property_list, i);
      ASSERT(grin_get_edge_property_datatype(graph, property) ==
             GRIN_DATATYPE::Int64);
      auto value = grin_get_edge_property_value_of_int64(graph, edge, property);
      auto value_in_row = grin_get_int64_from_row(graph, row, i);
      ASSERT(value == value_in_row);
      std::cout << "primary key: "
                << grin_get_edge_property_name(graph, edge_type, property)
                << ", value: " << value << std::endl;
      grin_destroy_edge_property(graph, property);
    }

    // destroy
    grin_destroy_edge_property_list(graph, property_list);
    grin_destroy_edge_type(graph, edge_type);
    grin_destroy_edge_list(graph, edge_list);
    grin_destroy_edge(graph, edge);
    grin_destroy_row(graph, row);
  }
  // destroy edge type list
  grin_destroy_edge_type_list(graph, primary_edge_type_list);

  std::cout << "---- test property: primarykey (edge) completed ----"
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

  // test property primary key
  test_vertex_property_primarykey(graph);
  test_edge_property_primarykey(graph);

  // destroy graph
  grin_destroy_graph(graph);

  return 0;
}
