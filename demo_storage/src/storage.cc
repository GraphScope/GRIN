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

#include "src/storage.h"

namespace DEMO_STORAGE_NAMESPACE {
DemoStorage demo_storage;

int64_t get_id_from_gid(const int64_t gid) { return (gid & 0xFFFFF); }

uint32_t get_type_id_from_gid(const int64_t gid) {
  return static_cast<uint32_t>(gid >> 20);
}

int64_t generate_gid_from_type_id_and_id(uint32_t type_id, int64_t id) {
  return (static_cast<int64_t>(type_id) << 20) | id;
}

void Graph::AddVertex(Vertex& vertex) noexcept {  // NOLINT
  uint32_t type_id = vertex.GetTypeId();
  if (vertices_.size() <= type_id) {
    vertices_.resize(type_id + 1);
  }
  if (vertex.GetId() == -1) {
    vertex.SetId(vertices_[type_id].size());
  }
  if (vertices_[type_id].size() <= vertex.GetId()) {
    vertices_[type_id].resize(vertex.GetId() + 1);
  }
  vertices_[type_id][vertex.GetId()] = vertex;
  int64_t gid = generate_gid_from_type_id_and_id(type_id, vertex.GetId());
  if (vertex.GetOidType() == GRIN_DATATYPE::Int64) {
    int64_t oid = vertex.GetOid<int64_t>();
    oid_int64_2_gid_[oid] = gid;
  } else if (vertex.GetOidType() == GRIN_DATATYPE::String) {
    std::string oid = vertex.GetOid<std::string>();
    oid_string_2_gid_[oid] = gid;
  }
}

void Graph::AddEdge(Edge& edge) noexcept {  // NOLINT
  uint32_t type_id = edge.GetTypeId();
  if (edges_.size() <= type_id) {
    edges_.resize(type_id + 1);
  }
  if (edge.GetId() == -1) {
    edge.SetId(edges_[type_id].size());
  }
  if (edges_[type_id].size() <= edge.GetId()) {
    edges_[type_id].resize(edge.GetId() + 1);
  }
  edges_[type_id][edge.GetId()] = edge;

  int64_t source = edge.GetSource(), dest = edge.GetDest();
  uint32_t source_type_id = get_type_id_from_gid(source),
           dest_type_id = get_type_id_from_gid(dest);
  int64_t source_id = get_id_from_gid(source), dest_id = get_id_from_gid(dest);
  uint32_t source_partition_id = GetMasterPartitionIdFromVertexGid(source),
           dest_partition_id = GetMasterPartitionIdFromVertexGid(dest);

  both_adj_list_[std::make_tuple(source_type_id, source_id, type_id,
                                 dest_partition_id)]
      .push_back(edge.GetId());
  both_adj_list_[std::make_tuple(dest_type_id, dest_id, type_id,
                                 source_partition_id)]
      .push_back(edge.GetId());

  if (is_directed_) {
    in_adj_list_[std::make_tuple(dest_type_id, dest_id, type_id,
                                 source_partition_id)]
        .push_back(edge.GetId());
    out_adj_list_[std::make_tuple(source_type_id, source_id, type_id,
                                  dest_partition_id)]
        .push_back(edge.GetId());
  }
}

Graph* DemoStorage::load_modern_graph(const std::string& name,
                                      uint32_t partition_num,
                                      uint32_t partition_id) {
  Graph* graph = new Graph(name, partition_num, partition_id, true);

  // add vertex type
  graph->AddVertexType("person");
  graph->AddVertexType("software");
  // add edge type
  graph->AddEdgeType("knows");
  graph->AddEdgeType("created");
  // add VEV type
  graph->AddVEVType("person", "knows", "person", MANY_TO_MANY);
  graph->AddVEVType("person", "created", "software", ONE_TO_MANY);

  // add vertex property
  Property vp_0_0("id", GRIN_DATATYPE::Int64, true);
  Property vp_0_1("name", GRIN_DATATYPE::String, false);
  Property vp_0_2("age", GRIN_DATATYPE::Int64, false);
  graph->AddVertexProperty("person", vp_0_0);
  graph->AddVertexProperty("person", vp_0_1);
  graph->AddVertexProperty("person", vp_0_2);
  Property vp_1_0("id", GRIN_DATATYPE::Int64, true);
  Property vp_1_1("name", GRIN_DATATYPE::String, false);
  Property vp_1_2("lang", GRIN_DATATYPE::String, false);
  graph->AddVertexProperty("software", vp_1_0);
  graph->AddVertexProperty("software", vp_1_1);
  graph->AddVertexProperty("software", vp_1_2);

  // add edge property
  Property ep_x_0("weight", GRIN_DATATYPE::Double, false);
  graph->AddEdgeProperty("knows", ep_x_0);
  graph->AddEdgeProperty("created", ep_x_0);

  // add vertex
  std::vector<int64_t> v_0_id = {2, 6, 4, 1};
  std::vector<std::string> v_0_name = {"vadas", "peter", "josh", "marko"};
  std::vector<int64_t> v_0_age = {27, 35, 32, 29};
  std::vector<int64_t> v_1_id = {3, 5};
  std::vector<std::string> v_1_name = {"lop", "ripple"};
  std::vector<std::string> v_1_lang = {"java", "java"};
  for (int64_t i = 0; i < 4; i++) {
    Vertex v(0, GRIN_DATATYPE::Int64, v_0_id[i], i);
    v.SetVData(GRIN_DATATYPE::Int64, v_0_id[i]);
    v.AddProperty("id", v_0_id[i]);
    v.AddProperty("name", v_0_name[i]);
    v.AddProperty("age", v_0_age[i]);
    v.AddLabel("person");
    graph->AddVertex(v);
  }
  for (int64_t i = 0; i < 2; i++) {
    Vertex v(1, GRIN_DATATYPE::Int64, v_1_id[i], i);
    v.SetVData(GRIN_DATATYPE::String, v_1_name[i]);
    v.AddProperty("id", v_1_id[i]);
    v.AddProperty("name", v_1_name[i]);
    v.AddProperty("lang", v_1_lang[i]);
    v.AddLabel("software");
    graph->AddVertex(v);
  }

  // add edge
  std::vector<int64_t> e_0_src = {1, 1};
  std::vector<int64_t> e_0_dst = {2, 4};
  std::vector<double> e_0_weight = {0.5, 1.0};
  std::vector<int64_t> e_1_src = {1, 4, 4, 6};
  std::vector<int64_t> e_1_dst = {3, 5, 3, 3};
  std::vector<double> e_1_weight = {0.4, 1.0, 0.4, 0.2};
  for (int64_t i = 0; i < 2; i++) {
    Edge e = graph->ConstructEdgeFromVertexOid(0, e_0_src[i], e_0_dst[i], i);
    e.SetEData(GRIN_DATATYPE::Double, e_0_weight[i]);
    e.AddProperty("weight", e_0_weight[i]);
    e.AddLabel("knows");
    graph->AddEdge(e);
  }
  for (int64_t i = 0; i < 4; i++) {
    Edge e = graph->ConstructEdgeFromVertexOid(1, e_1_src[i], e_1_dst[i], i);
    e.SetEData(GRIN_DATATYPE::Double, e_1_weight[i]);
    e.AddProperty("weight", e_1_weight[i]);
    e.AddLabel("created");
    graph->AddEdge(e);
  }

  // return
  return graph;
}

}  // namespace DEMO_STORAGE_NAMESPACE
