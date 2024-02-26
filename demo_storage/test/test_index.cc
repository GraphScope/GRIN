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
#include "index/external_id.h"
#include "index/internal_id.h"
#include "index/order.h"
#include "index/pk.h"
#include "property/primarykey.h"
#include "property/topology.h"
#include "property/type.h"
#include "topology/structure.h"
#include "topology/vertexlist.h"

void test_index_order(GRIN_GRAPH graph) {
  std::cout << "\n++++ test index: order ++++" << std::endl;

  std::cout << "test vertex order" << std::endl;
  auto vtype = grin_get_vertex_type_by_id(graph, 0);
  auto vertex_list = grin_get_vertex_list_by_type(graph, vtype);
  size_t idx0 = 0, idx1 = 1;
  auto v0 = grin_get_vertex_from_list(graph, vertex_list, idx0);
  auto v1 = grin_get_vertex_from_list(graph, vertex_list, idx1);
  ASSERT(grin_smaller_vertex(graph, v0, v1) == true);
  ASSERT(grin_smaller_vertex(graph, v1, v0) == false);

  std::cout << "test get position of vertex from sorted list" << std::endl;
  size_t pos0 =
      grin_get_position_of_vertex_from_sorted_list(graph, vertex_list, v0);
  size_t pos1 =
      grin_get_position_of_vertex_from_sorted_list(graph, vertex_list, v1);
  ASSERT(pos0 == idx0);
  ASSERT(pos1 == idx1);

  // destroy
  grin_destroy_vertex(graph, v0);
  grin_destroy_vertex(graph, v1);
  grin_destroy_vertex_list(graph, vertex_list);
  grin_destroy_vertex_type(graph, vtype);

  std::cout << "---- test index: order completed ----" << std::endl;
}

void test_internal_id(GRIN_GRAPH graph) {
  std::cout << "\n++++ test index: internal id ++++" << std::endl;

  std::cout << "test vertex internal id" << std::endl;
  auto vtype = grin_get_vertex_type_by_id(graph, 0);
  auto vertex_list = grin_get_vertex_list_by_type(graph, vtype);
  size_t idx0 = 0, idx1 = 1;
  auto v0 = grin_get_vertex_from_list(graph, vertex_list, idx0);
  auto v1 = grin_get_vertex_from_list(graph, vertex_list, idx1);

  // get internal id of vertex
  auto id0 = grin_get_vertex_internal_id_by_type(graph, vtype, v0);
  auto id1 = grin_get_vertex_internal_id_by_type(graph, vtype, v1);
  std::cout << "internal id of v0 = " << id0 << std::endl;
  std::cout << "internal id of v1 = " << id1 << std::endl;

  // get vertex by internal id
  auto v0_from_id = grin_get_vertex_by_internal_id_by_type(graph, vtype, id0);
  auto v1_from_id = grin_get_vertex_by_internal_id_by_type(graph, vtype, id1);
  ASSERT(grin_equal_vertex(graph, v0, v0_from_id) == true);
  ASSERT(grin_equal_vertex(graph, v1, v1_from_id) == true);

  auto lower_bound =
      grin_get_vertex_internal_id_lower_bound_by_type(graph, vtype);
  std::cout << "lower bound of internal id = " << lower_bound << std::endl;
  auto upper_bound =
      grin_get_vertex_internal_id_upper_bound_by_type(graph, vtype);
  std::cout << "upper bound of internal id = " << upper_bound << std::endl;

  // destroy
  grin_destroy_vertex(graph, v0);
  grin_destroy_vertex(graph, v1);
  grin_destroy_vertex(graph, v0_from_id);
  grin_destroy_vertex(graph, v1_from_id);
  grin_destroy_vertex_list(graph, vertex_list);
  grin_destroy_vertex_type(graph, vtype);

  std::cout << "---- test index: internal id completed ----" << std::endl;
}

void test_external_id(GRIN_GRAPH graph) {
  std::cout << "\n++++ test index: external id ++++" << std::endl;

  std::cout << "test vertex external id: int64" << std::endl;
  auto vtype = grin_get_vertex_type_by_id(graph, 0);
  auto vertex_list = grin_get_vertex_list_by_type(graph, vtype);
  size_t idx0 = 0, idx1 = 1;
  auto v0 = grin_get_vertex_from_list(graph, vertex_list, idx0);
  auto v1 = grin_get_vertex_from_list(graph, vertex_list, idx1);

  // get external id of int64
  auto id0 = grin_get_vertex_external_id_of_int64(graph, v0);
  auto id1 = grin_get_vertex_external_id_of_int64(graph, v1);
  std::cout << "external id of v0 = " << id0 << std::endl;
  std::cout << "external id of v1 = " << id1 << std::endl;

  // get vertex by external id
  auto v0_from_id = grin_get_vertex_by_external_id_of_int64(graph, id0);
  auto v1_from_id = grin_get_vertex_by_external_id_of_int64(graph, id1);
  ASSERT(grin_equal_vertex(graph, v0, v0_from_id) == true);
  ASSERT(grin_equal_vertex(graph, v1, v1_from_id) == true);

  std::cout << "test vertex external id: string" << std::endl;
  // get external id of string
  auto id0_str = grin_get_vertex_external_id_of_string(graph, v0);
  auto id1_str = grin_get_vertex_external_id_of_string(graph, v1);
  std::cout << "external id of v0 = " << id0_str << std::endl;
  std::cout << "external id of v1 = " << id1_str << std::endl;

  // get vertex by external id
  auto v0_from_id_str =
      grin_get_vertex_by_external_id_of_string(graph, id0_str);
  auto v1_from_id_str =
      grin_get_vertex_by_external_id_of_string(graph, id1_str);
  ASSERT(grin_equal_vertex(graph, v0, v0_from_id_str) == true);
  ASSERT(grin_equal_vertex(graph, v1, v1_from_id_str) == true);

  // destroy string id
  grin_destroy_vertex_external_id_of_string(graph, id0_str);
  grin_destroy_vertex_external_id_of_string(graph, id1_str);

  // destroy
  grin_destroy_vertex(graph, v0);
  grin_destroy_vertex(graph, v1);
  grin_destroy_vertex(graph, v0_from_id);
  grin_destroy_vertex(graph, v1_from_id);
  grin_destroy_vertex(graph, v0_from_id_str);
  grin_destroy_vertex(graph, v1_from_id_str);
  grin_destroy_vertex_list(graph, vertex_list);
  grin_destroy_vertex_type(graph, vtype);

  std::cout << "---- test index: internal id completed ----" << std::endl;
}

void test_pk(GRIN_GRAPH graph) {
  std::cout << "\n++++ test index: pk ++++" << std::endl;

  auto vertex_type = grin_get_vertex_type_by_id(graph, 0);
  auto vertex_list = grin_get_vertex_list_by_type(graph, vertex_type);
  auto v0 = grin_get_vertex_from_list(graph, vertex_list, 0);
  auto row = grin_get_vertex_primary_keys_row(graph, v0);
  auto v1 = grin_get_vertex_by_primary_keys_row(graph, vertex_type, row);
  ASSERT(grin_equal_vertex(graph, v0, v1) == true);
  std::cout << "vertex from pk is equal to the original vertex" << std::endl;

  std::cout << "----  test index: pk completed ----" << std::endl;
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

  // test index order
  test_index_order(graph);

  // test internal id
  test_internal_id(graph);

  // test external id
  test_external_id(graph);

  // test pk
  test_pk(graph);

  // destroy graph
  grin_destroy_graph(graph);

  return 0;
}
