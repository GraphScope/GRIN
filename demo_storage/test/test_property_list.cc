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
#include "property/property.h"
#include "property/propertylist.h"
#include "property/type.h"
#include "topology/edgelist.h"
#include "topology/structure.h"
#include "topology/vertexlist.h"

void test_vertex_property(GRIN_GRAPH graph, GRIN_VERTEX_PROPERTY property,
                          GRIN_VERTEX_TYPE vertex_type) {
  // get property name
  auto name = grin_get_vertex_property_name(graph, vertex_type, property);
  std::cout << "name of vertex property: " << name << std::endl;

  // get property data type
  auto data_type = grin_get_vertex_property_datatype(graph, property);
  std::cout << "data type of vertex property: " << data_type << std::endl;

  // get vertex type from property
  auto vertex_type2 = grin_get_vertex_type_from_property(graph, property);
  ASSERT(grin_equal_vertex_type(graph, vertex_type, vertex_type2) == true);

  // get vertex property by name
  auto property2 = grin_get_vertex_property_by_name(graph, vertex_type, name);
  ASSERT(grin_equal_vertex_property(graph, property, property2) == true);

  // get vertex property by id
  auto id = grin_get_vertex_property_id(graph, vertex_type, property);
  auto property3 = grin_get_vertex_property_by_id(graph, vertex_type, id);
  ASSERT(grin_equal_vertex_property(graph, property, property3) == true);

  // get vertex properties by name
  auto property_list = grin_get_vertex_properties_by_name(graph, name);
  auto n = grin_get_vertex_property_list_size(graph, property_list);
  std::cout << "number of vertex properties with this name: " << n << std::endl;

  // destroy
  grin_destroy_vertex_property(graph, property2);
  grin_destroy_vertex_property(graph, property3);
  grin_destroy_vertex_type(graph, vertex_type2);
  grin_destroy_vertex_property_list(graph, property_list);
}

void test_vertex_property_list(GRIN_GRAPH graph) {
  std::cout << "\n++++ test property: property list (vertex) ++++" << std::endl;

  auto vertex_type_list = grin_get_vertex_type_list(graph);
  for (auto i = 0; i < grin_get_vertex_type_list_size(graph, vertex_type_list);
       i++) {
    // get property list from vertex type
    auto vertex_type =
        grin_get_vertex_type_from_list(graph, vertex_type_list, i);
    auto property_list =
        grin_get_vertex_property_list_by_type(graph, vertex_type);
    size_t n = grin_get_vertex_property_list_size(graph, property_list);

    std::cout << "\n==== test property: property (vertex) ++++" << std::endl;
    std::cout << "size of property list of vtype " << i << ": " << n
              << std::endl;

    // create property list
    auto new_property_list = grin_create_vertex_property_list(graph);

    for (auto i = 0; i < n; i++) {
      // get property from property list
      auto property =
          grin_get_vertex_property_from_list(graph, property_list, i);
      // test methods on property
      test_vertex_property(graph, property, vertex_type);
      // insert property to property list
      auto status = grin_insert_vertex_property_to_list(
          graph, new_property_list, property);
      ASSERT(status == true);
      // destroy property
      grin_destroy_vertex_property(graph, property);
    }

    // compare size
    ASSERT(grin_get_vertex_property_list_size(graph, new_property_list) == n);

    // destroy
    grin_destroy_vertex_type(graph, vertex_type);
    grin_destroy_vertex_property_list(graph, property_list);
    grin_destroy_vertex_property_list(graph, new_property_list);
  }

  // destroy
  grin_destroy_vertex_type_list(graph, vertex_type_list);

  std::cout << "---- test property: property list (vertex) completed ----"
            << std::endl;
}

void test_edge_property(GRIN_GRAPH graph, GRIN_EDGE_PROPERTY property,
                        GRIN_EDGE_TYPE edge_type) {
  // get property name
  auto name = grin_get_edge_property_name(graph, edge_type, property);
  std::cout << "name of edge property: " << name << std::endl;

  // get property data type
  auto data_type = grin_get_edge_property_datatype(graph, property);
  std::cout << "data type of edge property: " << data_type << std::endl;

  // get edge type from property
  auto edge_type2 = grin_get_edge_type_from_property(graph, property);
  ASSERT(grin_equal_edge_type(graph, edge_type, edge_type2) == true);

  // get edge property by name
  auto property2 = grin_get_edge_property_by_name(graph, edge_type, name);
  ASSERT(grin_equal_edge_property(graph, property, property2) == true);

  // get edge property by id
  auto id = grin_get_edge_property_id(graph, edge_type, property);
  auto property3 = grin_get_edge_property_by_id(graph, edge_type, id);
  ASSERT(grin_equal_edge_property(graph, property, property3) == true);

  // get edge properties by name
  auto property_list = grin_get_edge_properties_by_name(graph, name);
  auto n = grin_get_edge_property_list_size(graph, property_list);
  std::cout << "number of edge properties with this name: " << n << std::endl;

  // destroy
  grin_destroy_edge_type(graph, edge_type2);
  grin_destroy_edge_property(graph, property2);
  grin_destroy_edge_property(graph, property3);
  grin_destroy_edge_property_list(graph, property_list);
}

void test_edge_property_list(GRIN_GRAPH graph) {
  std::cout << "\n++++ test property: property list (edge) ++++" << std::endl;

  auto edge_type_list = grin_get_edge_type_list(graph);
  for (auto i = 0; i < grin_get_edge_type_list_size(graph, edge_type_list);
       i++) {
    // get property list from edge type
    auto edge_type = grin_get_edge_type_from_list(graph, edge_type_list, i);
    auto property_list = grin_get_edge_property_list_by_type(graph, edge_type);
    size_t n = grin_get_edge_property_list_size(graph, property_list);

    std::cout << "\n==== test property: property (edge) ++++" << std::endl;
    std::cout << "size of property list of etype " << i << ": " << n
              << std::endl;

    // create property list
    auto new_property_list = grin_create_edge_property_list(graph);

    for (auto i = 0; i < n; i++) {
      // get property from property list
      auto property = grin_get_edge_property_from_list(graph, property_list, i);
      // test methods on property
      test_edge_property(graph, property, edge_type);
      // insert property to property list
      auto status =
          grin_insert_edge_property_to_list(graph, new_property_list, property);
      ASSERT(status == true);
      // destroy property
      grin_destroy_edge_property(graph, property);
    }

    // compare size
    ASSERT(grin_get_edge_property_list_size(graph, new_property_list) == n);

    // destroy
    grin_destroy_edge_type(graph, edge_type);
    grin_destroy_edge_property_list(graph, property_list);
    grin_destroy_edge_property_list(graph, new_property_list);
  }

  // destroy
  grin_destroy_edge_type_list(graph, edge_type_list);

  std::cout << "---- test property: property list (edge) completed ----"
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

  // test vertex property list
  test_vertex_property_list(graph);

  // test edge property list
  test_edge_property_list(graph);

  // destroy graph
  grin_destroy_graph(graph);

  return 0;
}
