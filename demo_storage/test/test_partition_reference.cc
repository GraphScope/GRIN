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
#include "partition/reference.h"
#include "property/topology.h"
#include "property/type.h"
#include "topology/edgelist.h"
#include "topology/structure.h"
#include "topology/vertexlist.h"

void test_vertex_ref(GRIN_PARTITIONED_GRAPH pg, GRIN_GRAPH graph,
                     GRIN_VERTEX v) {
  std::cout << "\n== test vertex ref ==" << std::endl;

  // check vertex ref
  auto vr = grin_get_vertex_ref_by_vertex(graph, v);
  auto v_from_vr = grin_get_vertex_from_vertex_ref(graph, vr);
  ASSERT(grin_equal_vertex(graph, v, v_from_vr) == true);

  // serialize & deserialize vertex ref
  auto msg = grin_serialize_vertex_ref(graph, vr);
  std::cout << "serialized vertex ref = " << msg << std::endl;
  auto vr_from_msg = grin_deserialize_to_vertex_ref(graph, msg);
  auto v_from_vr_from_msg = grin_get_vertex_from_vertex_ref(graph, vr_from_msg);
  ASSERT(grin_equal_vertex(graph, v, v_from_vr_from_msg) == true);

  // serialize & deserialize vertex ref as int64
  auto int64_msg = grin_serialize_vertex_ref_as_int64(graph, vr);
  std::cout << "serialized vertex ref as int64 = " << int64_msg << std::endl;
  auto vr_from_int64_msg =
      grin_deserialize_int64_to_vertex_ref(graph, int64_msg);
  auto v_from_vr_from_int64_msg =
      grin_get_vertex_from_vertex_ref(graph, vr_from_int64_msg);
  ASSERT(grin_equal_vertex(graph, v, v_from_vr_from_int64_msg) == true);

  // check master or mirror
  auto is_master = grin_is_master_vertex(graph, v);
  auto is_mirror = grin_is_mirror_vertex(graph, v);
  ASSERT((is_master || is_mirror) && !(is_master && is_mirror));
  if (is_master) {
    std::cout << "vertex is master, ";
  } else {
    std::cout << "vertex is mirror, ";
  }
  // get master partition id
  auto master_partition = grin_get_master_partition_from_vertex_ref(graph, vr);
  auto master_partition_id = grin_get_partition_id(pg, master_partition);
  std::cout << "master partition id = " << master_partition_id << std::endl;
  // get mirror_partition_list
  if (is_master) {
    ASSERT(grin_get_mirror_vertex_mirror_partition_list(graph, v) ==
           GRIN_NULL_PARTITION_LIST);
    auto partition_list =
        grin_get_master_vertex_mirror_partition_list(graph, v);

    std::cout << "mirror partition ids = ";
    auto partition_list_size = grin_get_partition_list_size(pg, partition_list);
    for (auto i = 0; i < partition_list_size; ++i) {
      auto partition = grin_get_partition_from_list(pg, partition_list, i);
      auto partition_id = grin_get_partition_id(pg, partition);
      std::cout << " " << partition_id;
      grin_destroy_partition(pg, partition);
    }
    std::cout << std::endl;

    grin_destroy_partition_list(pg, partition_list);

  } else {
    ASSERT(grin_get_master_vertex_mirror_partition_list(graph, v) ==
           GRIN_NULL_PARTITION_LIST);
    auto partition_list =
        grin_get_mirror_vertex_mirror_partition_list(graph, v);

    std::cout << "mirror partition ids = ";
    auto partition_list_size = grin_get_partition_list_size(pg, partition_list);
    for (auto i = 0; i < partition_list_size; ++i) {
      auto partition = grin_get_partition_from_list(pg, partition_list, i);
      auto partition_id = grin_get_partition_id(pg, partition);
      std::cout << " " << partition_id;
      grin_destroy_partition(pg, partition);
    }
    std::cout << std::endl;

    grin_destroy_partition_list(pg, partition_list);
  }

  // destroy
  grin_destroy_partition(graph, master_partition);
  grin_destroy_vertex(graph, v_from_vr);
  grin_destroy_vertex(graph, v_from_vr_from_msg);
  grin_destroy_vertex(graph, v_from_vr_from_int64_msg);
  grin_destroy_vertex_ref(graph, vr);
  grin_destroy_vertex_ref(graph, vr_from_msg);
  grin_destroy_vertex_ref(graph, vr_from_int64_msg);
  grin_destroy_serialized_vertex_ref(graph, msg);
}

void test_edge_ref(GRIN_PARTITIONED_GRAPH pg, GRIN_GRAPH graph, GRIN_EDGE e) {
  std::cout << "\n== test edge ref ==" << std::endl;

  // check edge ref
  auto er = grin_get_vertex_ref_by_vertex(graph, e);
  auto e_from_er = grin_get_vertex_from_vertex_ref(graph, er);
  ASSERT(grin_equal_vertex(graph, e, e_from_er) == true);

  // serialize & deserialize edge ref
  auto msg = grin_serialize_vertex_ref(graph, er);
  std::cout << "serialized edge ref = " << msg << std::endl;
  auto er_from_msg = grin_deserialize_to_vertex_ref(graph, msg);
  auto e_from_er_from_msg = grin_get_vertex_from_vertex_ref(graph, er_from_msg);
  ASSERT(grin_equal_vertex(graph, e, e_from_er_from_msg) == true);

  // check master or mirror
  auto is_master = grin_is_master_vertex(graph, e);
  auto is_mirror = grin_is_mirror_vertex(graph, e);
  ASSERT((is_master || is_mirror) && !(is_master && is_mirror));
  if (is_master) {
    std::cout << "edge is master, ";
  } else {
    std::cout << "edgeis mirror, ";
  }
  // get master partition id
  auto master_partition = grin_get_master_partition_from_edge_ref(graph, er);
  auto master_partition_id = grin_get_partition_id(pg, master_partition);
  std::cout << "master partition id = " << master_partition_id << std::endl;
  // get mirror_partition_list
  if (is_master) {
    ASSERT(grin_get_mirror_edge_mirror_partition_list(graph, e) ==
           GRIN_NULL_PARTITION_LIST);
    auto partition_list = grin_get_master_edge_mirror_partition_list(graph, e);

    std::cout << "mirror partition ids = ";
    auto partition_list_size = grin_get_partition_list_size(pg, partition_list);
    for (auto i = 0; i < partition_list_size; ++i) {
      auto partition = grin_get_partition_from_list(pg, partition_list, i);
      auto partition_id = grin_get_partition_id(pg, partition);
      std::cout << " " << partition_id;
      grin_destroy_partition(pg, partition);
    }
    std::cout << std::endl;

    grin_destroy_partition_list(pg, partition_list);

  } else {
    ASSERT(grin_get_master_edge_mirror_partition_list(graph, e) ==
           GRIN_NULL_PARTITION_LIST);
    auto partition_list = grin_get_mirror_edge_mirror_partition_list(graph, e);

    std::cout << "mirror partition ids = ";
    auto partition_list_size = grin_get_partition_list_size(pg, partition_list);
    for (auto i = 0; i < partition_list_size; ++i) {
      auto partition = grin_get_partition_from_list(pg, partition_list, i);
      auto partition_id = grin_get_partition_id(pg, partition);
      std::cout << " " << partition_id;
      grin_destroy_partition(pg, partition);
    }
    std::cout << std::endl;

    grin_destroy_partition_list(pg, partition_list);
  }

  // destroy
  grin_destroy_partition(graph, master_partition);
  grin_destroy_vertex(graph, e_from_er);
  grin_destroy_vertex(graph, e_from_er_from_msg);
  grin_destroy_vertex_ref(graph, er);
  grin_destroy_vertex_ref(graph, er_from_msg);
  grin_destroy_serialized_vertex_ref(graph, msg);
}

void test_partition_reference(GRIN_PARTITIONED_GRAPH pg, unsigned n) {
  std::cout << "\n++++ test partition: reference ++++" << std::endl;

  // check partition number
  ASSERT(pg != GRIN_NULL_GRAPH);
  auto partition_num = grin_get_total_partitions_number(pg);
  ASSERT(partition_num == n);

  // create a local graph
  auto partition0 = grin_get_partition_by_id(pg, 0);
  auto graph = grin_get_local_graph_by_partition(pg, partition0);

  // test vertex ref
  auto vtype = grin_get_vertex_type_by_id(graph, 0);
  auto vertex_list = grin_get_vertex_list_by_type(graph, vtype);
  // get vertex 0 & test
  if (grin_get_vertex_list_size(graph, vertex_list) > 0) {
    auto v = grin_get_vertex_from_list(graph, vertex_list, 0);
    test_vertex_ref(pg, graph, v);
    grin_destroy_vertex(graph, v);
  }
  // get vertex 1 & test
  if (grin_get_vertex_list_size(graph, vertex_list) > 1) {
    auto v = grin_get_vertex_from_list(graph, vertex_list, 1);
    test_vertex_ref(pg, graph, v);
    grin_destroy_vertex(graph, v);
  }

  // test edge ref
  auto etype = grin_get_edge_type_by_id(graph, 0);
  auto edge_list = grin_get_edge_list_by_type(graph, etype);
  // get edge 0 & test
  if (grin_get_edge_list_size(graph, edge_list) > 0) {
    auto e = grin_get_edge_from_list(graph, edge_list, 0);
    test_edge_ref(pg, graph, e);
    grin_destroy_edge(graph, e);
  }
  // get edge 1 & test
  if (grin_get_edge_list_size(graph, edge_list) > 1) {
    auto e = grin_get_edge_from_list(graph, edge_list, 1);
    test_edge_ref(pg, graph, e);
    grin_destroy_edge(graph, e);
  }

  // destroy
  grin_destroy_partition(graph, partition0);
  grin_destroy_graph(graph);
  grin_destroy_vertex_list(graph, vertex_list);
  grin_destroy_vertex_type(graph, vtype);
  grin_destroy_edge_list(graph, edge_list);
  grin_destroy_edge_type(graph, etype);

  std::cout << "---- test partition: reference completed ----" << std::endl;
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
  test_partition_reference(pg, partition_num);

  // destroy partitioned graph
  grin_destroy_partitioned_graph(pg);

  return 0;
}
