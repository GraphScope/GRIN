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

#ifndef STORAGE_STORAGE_H_
#define STORAGE_STORAGE_H_

#include <any>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#define DEMO_STORAGE_NAMESPACE demo_storage_namespace

namespace DEMO_STORAGE_NAMESPACE {
// gid related functions
int64_t get_id_from_gid(const int64_t gid);
uint32_t get_type_id_from_gid(const int64_t gid);
int64_t generate_gid_from_type_id_and_id(uint32_t type_id, int64_t id);

typedef enum {
  ONE_TO_ONE = 0,
  ONE_TO_MANY = 1,
  MANY_TO_ONE = 2,
  MANY_TO_MANY = 3
} VEV_RELATION_TYPE;

struct Property {
  std::string name_;
  GRIN_DATATYPE datatype_;
  bool is_primary_;
  Property(std::string name, GRIN_DATATYPE datatype, bool is_primary = false)
      : name_(name), datatype_(datatype), is_primary_(is_primary) {}
};

class Vertex {
 public:
  // default constructor
  Vertex() : type_id_(GRIN_NULL_VERTEX_TYPE), id_(-1) {
    oid_type_ = GRIN_DATATYPE::Undefined;
    vdata_type_ = GRIN_DATATYPE::Undefined;
  }

  // construct vertex with type and id in type, without oid
  explicit Vertex(uint32_t type_id, int64_t id = -1)
      : type_id_(type_id), id_(id) {
    oid_type_ = GRIN_DATATYPE::Undefined;
    vdata_type_ = GRIN_DATATYPE::Undefined;
  }

  // construct vertex with type, oid, and id in type
  Vertex(uint32_t type_id, GRIN_DATATYPE oid_type, const std::any& oid,
         int64_t id = -1)
      : type_id_(type_id), id_(id), oid_type_(oid_type), oid_(oid) {
    vdata_type_ = GRIN_DATATYPE::Undefined;
  }

 public:
  // get methods
  uint32_t GetTypeId() const noexcept { return type_id_; }
  int64_t GetId() const noexcept { return id_; }
  int64_t GetGid() const noexcept {
    return generate_gid_from_type_id_and_id(type_id_, id_);
  }

  GRIN_DATATYPE GetOidType() const noexcept { return oid_type_; }
  template <typename T>
  T GetOid() const {
    return std::any_cast<T>(oid_);
  }

  GRIN_DATATYPE GetVDataType() const noexcept { return vdata_type_; }
  template <typename T>
  T GetVData() const {
    return std::any_cast<T>(vdata_);
  }

  template <typename T>
  T GetProperty(const std::string& property_name) const {
    auto it = property_values_.find(property_name);
    return std::any_cast<T>(it->second);
  }

  std::any GetPropertyAny(const std::string& property_name) const {
    auto it = property_values_.find(property_name);
    return it->second;
  }

  const std::set<std::string>& GetLabels() const noexcept { return labels_; }
  bool HasLabel(const std::string& label) const noexcept {
    return labels_.find(label) != labels_.end();
  }

  // set methods
  void SetId(const int64_t id) noexcept { id_ = id; }

  void SetVData(const GRIN_DATATYPE vdata_type,
                const std::any& vdata) noexcept {
    vdata_type_ = vdata_type;
    vdata_ = vdata;
  }

  void AddProperty(const std::string property_name,
                   const std::any& property_value) noexcept {
    property_values_.insert(std::make_pair(property_name, property_value));
  }

  void AddLabel(const std::string& label) noexcept { labels_.insert(label); }

 private:
  uint32_t type_id_;
  int64_t id_;
  GRIN_DATATYPE oid_type_;
  std::any oid_;
  GRIN_DATATYPE vdata_type_;
  std::any vdata_;
  std::map<std::string, std::any> property_values_;
  std::set<std::string> labels_;
};

class Edge {
 public:
  // default constructor
  Edge() : type_id_(GRIN_NULL_EDGE_TYPE), source_(-1), dest_(-1), id_(-1) {
    edata_type_ = GRIN_DATATYPE::Undefined;
  }
  // construct edge with type, gid of source & dest vertex, and id in type
  Edge(uint32_t type_id, int64_t source, int64_t dest, int64_t id = -1)
      : type_id_(type_id), source_(source), dest_(dest), id_(id) {
    edata_type_ = GRIN_DATATYPE::Undefined;
  }

 public:
  // get methods
  uint32_t GetTypeId() const noexcept { return type_id_; }
  int64_t GetSource() const noexcept { return source_; }
  int64_t GetDest() const noexcept { return dest_; }
  int64_t GetId() const noexcept { return id_; }
  int64_t GetGid() const noexcept {
    return generate_gid_from_type_id_and_id(type_id_, id_);
  }

  GRIN_DATATYPE GetEDataType() const noexcept { return edata_type_; }
  template <typename T>
  T GetEData() const {
    return std::any_cast<T>(edata_);
  }

  template <typename T>
  T GetProperty(const std::string& property_name) const {
    auto it = property_values_.find(property_name);
    return std::any_cast<T>(it->second);
  }

  std::any GetPropertyAny(const std::string& property_name) const {
    auto it = property_values_.find(property_name);
    return it->second;
  }

  const std::set<std::string>& GetLabels() const noexcept { return labels_; }
  bool HasLabel(const std::string& label) const noexcept {
    return labels_.find(label) != labels_.end();
  }

  // set methods
  void SetId(const int64_t id) noexcept { id_ = id; }

  void SetEData(const GRIN_DATATYPE edata_type,
                const std::any& edata) noexcept {
    edata_type_ = edata_type;
    edata_ = edata;
  }

  void AddProperty(const std::string property_name,
                   const std::any& property_value) noexcept {
    property_values_.insert(std::make_pair(property_name, property_value));
  }

  void AddLabel(const std::string& label) noexcept { labels_.insert(label); }

 private:
  uint32_t type_id_;
  int64_t source_, dest_;
  int64_t id_;
  GRIN_DATATYPE edata_type_;
  std::any edata_;
  std::map<std::string, std::any> property_values_;
  std::set<std::string> labels_;
};

class Graph {
 public:
  // construct graph
  Graph(std::string graph_name, uint32_t partition_num = 1,
        uint32_t partition_id = 0, bool is_directed = true)
      : graph_name_(graph_name),
        partition_num_(partition_num),
        partition_id_(partition_id),
        is_directed_(is_directed) {}

 public:
  // get methods
  // get meta
  const std::string& GetName() const noexcept { return graph_name_; }
  bool IsDirected() const noexcept { return is_directed_; }
  uint32_t GetPartitionNum() const noexcept { return partition_num_; }
  uint32_t GetPartitionId() const noexcept { return partition_id_; }

  // get types
  size_t GetVertexTypeNum() const noexcept { return vertex_types_.size(); }
  size_t GetEdgeTypeNum() const noexcept { return edge_types_.size(); }
  size_t GetVertexEdgeVertexTypeNum() const noexcept {
    return vev_types_.size();
  }
  const std::vector<std::string>& GetVertexTypes() const noexcept {
    return vertex_types_;
  }
  const std::vector<std::string>& GetEdgeTypes() const noexcept {
    return edge_types_;
  }
  const std::string& GetVertexTypeName(uint32_t type_id) const noexcept {
    return vertex_types_[type_id];
  }
  const std::string& GetEdgeTypeName(uint32_t type_id) const noexcept {
    return edge_types_[type_id];
  }
  const std::vector<
      std::pair<std::tuple<uint32_t, uint32_t, uint32_t>, VEV_RELATION_TYPE>>&
  GetVertexEdgeVertexTypes() const noexcept {
    return vev_types_;
  }
  int32_t GetVertexTypeId(const std::string& vertex_type) const noexcept {
    if (vertex_type_2_id_.find(vertex_type) == vertex_type_2_id_.end()) {
      return -1;
    }
    return vertex_type_2_id_.at(vertex_type);
  }
  int32_t GetEdgeTypeId(const std::string& edge_type) const noexcept {
    if (edge_type_2_id_.find(edge_type) == edge_type_2_id_.end()) {
      return -1;
    }
    return edge_type_2_id_.at(edge_type);
  }

  // get properties
  size_t GetVertexPropertyNum(uint32_t type_id) const noexcept {
    if (type_id >= vertex_properties_.size()) {
      return 0;
    }
    return vertex_properties_[type_id].size();
  }
  size_t GetEdgePropertyNum(uint32_t type_id) const noexcept {
    if (type_id >= edge_properties_.size()) {
      return 0;
    }
    return edge_properties_[type_id].size();
  }
  const std::string& GetVertexPropertyName(uint32_t type_id,
                                           uint32_t property_id) const
      noexcept {
    return vertex_properties_[type_id][property_id].name_;
  }
  const std::string& GetEdgePropertyName(uint32_t type_id,
                                         uint32_t property_id) const noexcept {
    return edge_properties_[type_id][property_id].name_;
  }
  const Property& GetVertexProperty(int64_t gid) const noexcept {
    auto type_id = get_type_id_from_gid(gid);
    auto property_id = get_id_from_gid(gid);
    return vertex_properties_[type_id][property_id];
  }
  const Property& GetEdgeProperty(int64_t gid) const noexcept {
    auto type_id = get_type_id_from_gid(gid);
    auto property_id = get_id_from_gid(gid);
    return edge_properties_[type_id][property_id];
  }
  const std::vector<Property>& GetVertexProperties(uint32_t type_id) const
      noexcept {
    return vertex_properties_[type_id];
  }
  const std::vector<Property>& GetEdgeProperties(uint32_t type_id) const
      noexcept {
    return edge_properties_[type_id];
  }
  int32_t GetVertexPropertyId(uint32_t vtype, std::string name) const noexcept {
    if (vertex_property_2_id_[vtype].find(name) ==
        vertex_property_2_id_[vtype].end()) {
      return -1;
    }
    return vertex_property_2_id_[vtype].at(name);
  }
  int32_t GetEdgePropertyId(uint32_t etype, std::string name) const noexcept {
    if (edge_property_2_id_[etype].find(name) ==
        edge_property_2_id_[etype].end()) {
      return -1;
    }
    return edge_property_2_id_[etype].at(name);
  }

  // get vertex & edge number
  size_t GetVertexNum(uint32_t type_id) const noexcept {
    if (type_id >= vertices_.size()) {
      return 0;
    }
    return vertices_[type_id].size();
  }
  size_t GetEdgeNum(uint32_t type_id) const noexcept {
    if (type_id >= edges_.size()) {
      return 0;
    }
    return edges_[type_id].size();
  }
  size_t GetPartitionedVertexNum(uint32_t type_id, uint32_t partition_id) const
      noexcept {
    size_t num = GetVertexNum(type_id);
    size_t res = num / partition_num_;
    if (partition_id < num % partition_num_) {
      res++;
    }
    return res;
  }
  size_t GetPartitionedEdgeNum(uint32_t type_id, uint32_t partition_id) const
      noexcept {
    size_t num = GetEdgeNum(type_id);
    size_t res = num / partition_num_;
    if (partition_id < num % partition_num_) {
      res++;
    }
    return res;
  }

  // get vertices, edges, and adjacent lists
  const Vertex& GetVertex(int64_t gid) const {
    uint32_t type_id = get_type_id_from_gid(gid);
    int64_t id = get_id_from_gid(gid);
    return vertices_[type_id][id];
  }
  const Edge& GetEdge(int64_t gid) const {
    uint32_t type_id = get_type_id_from_gid(gid);
    int64_t id = get_id_from_gid(gid);
    return edges_[type_id][id];
  }
  const std::vector<Vertex>& GetVertices(uint32_t type_id) const {
    return vertices_[type_id];
  }
  const std::vector<Edge>& GetEdges(uint32_t type_id) const {
    return edges_[type_id];
  }
  size_t GetAdjacentListSize(uint32_t vtype_id, int64_t vid, uint32_t etype_id,
                             uint32_t partition_id, GRIN_DIRECTION dir) {
    size_t size = 0;
    auto key = std::make_tuple(vtype_id, vid, etype_id, partition_id);
    if (!is_directed_ || dir == GRIN_DIRECTION::BOTH) {
      if (both_adj_list_.find(key) != both_adj_list_.end()) {
        size = both_adj_list_.at(key).size();
      }
    }
    if (dir == GRIN_DIRECTION::IN) {
      if (in_adj_list_.find(key) != in_adj_list_.end()) {
        size = in_adj_list_.at(key).size();
      }
    }
    if (dir == GRIN_DIRECTION::OUT) {
      if (out_adj_list_.find(key) != out_adj_list_.end()) {
        size = out_adj_list_.at(key).size();
      }
    }
    return size;
  }
  const std::vector<int64_t>& GetAdjacentList(uint32_t vtype_id, int64_t vid,
                                              uint32_t etype_id,
                                              uint32_t partition_id,
                                              GRIN_DIRECTION dir) {
    auto key = std::make_tuple(vtype_id, vid, etype_id, partition_id);
    if (!is_directed_ || dir == GRIN_DIRECTION::BOTH) {
      if (both_adj_list_.find(key) != both_adj_list_.end()) {
        return both_adj_list_.at(key);
      }
    }
    if (dir == GRIN_DIRECTION::IN) {
      if (in_adj_list_.find(key) != in_adj_list_.end()) {
        return in_adj_list_.at(key);
      }
    }
    if (dir == GRIN_DIRECTION::OUT) {
      if (out_adj_list_.find(key) != out_adj_list_.end()) {
        return out_adj_list_.at(key);
      }
    }
    return empty_adj_list_;
  }

 public:
  // gid & oid related functions
  int64_t GetGidFromOidOfInt64(int64_t oid) const noexcept {
    if (oid_int64_2_gid_.find(oid) != oid_int64_2_gid_.end()) {
      return oid_int64_2_gid_.at(oid);
    }
    return -1;
  }
  int64_t GetGidFromOidOfString(std::string oid) const noexcept {
    if (oid_string_2_gid_.find(oid) != oid_string_2_gid_.end()) {
      return oid_string_2_gid_.at(oid);
    }
    return -1;
  }
  int64_t GetGidFromOid(const std::any& oid) const {
    if (oid.type() == typeid(int64_t)) {
      return GetGidFromOidOfInt64(std::any_cast<int64_t>(oid));
    } else if (oid.type() == typeid(std::string)) {
      return GetGidFromOidOfString(std::any_cast<std::string>(oid));
    }
    return -1;
  }
  Edge ConstructEdgeFromVertexOid(uint32_t type_id, const std::any& source_oid,
                                  const std::any& dest_oid,
                                  int64_t edge_id = -1) const {
    int64_t source_gid = GetGidFromOid(source_oid);
    int64_t dest_gid = GetGidFromOid(dest_oid);
    return Edge(type_id, source_gid, dest_gid, edge_id);
  }

 public:
  // partition related functions
  uint32_t GetMasterPartitionIdFromVertexGid(const int64_t gid) const noexcept {
    return gid % partition_num_;
  }
  uint32_t GetMasterPartitionIdFromEdgeGid(const int64_t gid) const noexcept {
    return gid % partition_num_;
  }
  uint32_t GetMasterPartitionIdForVertex(const Vertex& vertex) const noexcept {
    return vertex.GetId() % partition_num_;
  }
  uint32_t GetMasterPartitionIdForEdge(const Edge& edge) const noexcept {
    return edge.GetId() % partition_num_;
  }

 public:
  // build graph methods
  // add types
  void AddVertexType(const std::string& vertex_type) noexcept {
    if (vertex_type_2_id_.find(vertex_type) == vertex_type_2_id_.end()) {
      vertex_type_2_id_[vertex_type] = vertex_types_.size();
      vertex_types_.push_back(vertex_type);
    }
  }
  void AddEdgeType(const std::string& edge_type) noexcept {
    if (edge_type_2_id_.find(edge_type) == edge_type_2_id_.end()) {
      edge_type_2_id_[edge_type] = edge_types_.size();
      edge_types_.push_back(edge_type);
    }
  }
  void AddVEVType(const std::string& src_type, const std::string& edge_type,
                  const std::string& dest_type,
                  const VEV_RELATION_TYPE vev_relation_type) noexcept {
    AddVertexType(src_type);
    AddVertexType(dest_type);
    AddEdgeType(edge_type);
    auto edge_type_id = GetEdgeTypeId(edge_type);
    auto src_type_id = GetVertexTypeId(src_type);
    auto dest_type_id = GetVertexTypeId(dest_type);
    vev_types_.push_back(
        std::make_pair(std::make_tuple(src_type_id, edge_type_id, dest_type_id),
                       vev_relation_type));
  }

  // add properties
  void AddVertexProperty(const std::string& vertex_type,
                         const Property& property) noexcept {
    uint32_t type_id = vertex_type_2_id_[vertex_type];
    if (vertex_properties_.size() <= type_id) {
      vertex_properties_.resize(type_id + 1);
      vertex_property_2_id_.resize(type_id + 1);
    }
    if (vertex_property_2_id_[type_id].find(property.name_) ==
        vertex_property_2_id_[type_id].end()) {
      vertex_property_2_id_[type_id][property.name_] =
          vertex_properties_[type_id].size();
      vertex_properties_[type_id].push_back(property);
    }
  }
  void AddEdgeProperty(const std::string& edge_type,
                       const Property& property) noexcept {
    uint32_t type_id = edge_type_2_id_[edge_type];
    if (edge_properties_.size() <= type_id) {
      edge_properties_.resize(type_id + 1);
      edge_property_2_id_.resize(type_id + 1);
    }
    if (edge_property_2_id_[type_id].find(property.name_) ==
        edge_property_2_id_[type_id].end()) {
      edge_property_2_id_[type_id][property.name_] =
          edge_properties_[type_id].size();
      edge_properties_[type_id].push_back(property);
    }
  }

  // add vertices and edges
  void AddVertex(Vertex& vertex) noexcept;  // NOLINT
  void AddEdge(Edge& edge) noexcept;        // NOLINT

 private:
  // meta
  std::string graph_name_;
  uint32_t partition_num_, partition_id_;
  bool is_directed_;
  // schema
  std::vector<std::string> vertex_types_, edge_types_;
  std::map<std::string, uint32_t> vertex_type_2_id_, edge_type_2_id_;
  std::vector<
      std::pair<std::tuple<uint32_t, uint32_t, uint32_t>, VEV_RELATION_TYPE>>
      vev_types_;
  std::vector<std::vector<Property>> vertex_properties_, edge_properties_;
  std::vector<std::map<std::string, uint32_t>> vertex_property_2_id_,
      edge_property_2_id_;
  // vertices and edges
  std::vector<std::vector<Vertex>> vertices_;
  std::vector<std::vector<Edge>> edges_;
  // adj_list_[(vtype, vid, partition_id)] = vector of global eid for edges
  std::map<std::tuple<uint32_t, int64_t, uint32_t, uint32_t>,
           std::vector<int64_t>>
      in_adj_list_, out_adj_list_, both_adj_list_;
  std::vector<int64_t> empty_adj_list_;
  // oid to gid
  std::map<int64_t, int64_t> oid_int64_2_gid_;
  std::map<std::string, int64_t> oid_string_2_gid_;
};

class DemoStorage {
 public:
  DemoStorage() = default;
  ~DemoStorage() {
    for (auto& graph : graphs_) {
      delete graph.second;
    }
  }

 public:
  Graph* GetGraph(const std::string& graph_name, uint32_t partition_num,
                  uint32_t partition_id) noexcept {
    auto tuple = std::make_tuple(graph_name, partition_num, partition_id);
    if (graphs_.find(tuple) != graphs_.end()) {
      return graphs_.at(tuple);
    }
    return NULL;
  }

  void PutGraph(const std::string& graph_name, uint32_t partition_num,
                uint32_t partition_id, Graph* graph) noexcept {
    auto tuple = std::make_tuple(graph_name, partition_num, partition_id);
    if (graphs_.find(tuple) != graphs_.end()) {
      delete graphs_.at(tuple);
    }
    graphs_[tuple] = graph;
  }

  void RemoveGraph(const std::string& graph_name, uint32_t partition_num,
                   uint32_t partition_id) noexcept {
    auto tuple = std::make_tuple(graph_name, partition_num, partition_id);
    if (graphs_.find(tuple) != graphs_.end()) {
      delete graphs_.at(tuple);
      graphs_.erase(tuple);
    }
  }

  void Clear() noexcept {
    for (auto& graph : graphs_) {
      delete graph.second;
    }
    graphs_.clear();
  }

 public:
  // method for loading an example graph: modern_graph
  void LoadModernGraph(const std::string& name, uint32_t partition_num = 1,
                       uint32_t partition_id = 0) noexcept {
    Graph* graph = load_modern_graph(name, partition_num, partition_id);
    graphs_[std::make_tuple(graph->GetName(), partition_num, partition_id)] =
        graph;
  }

 private:
  Graph* load_modern_graph(const std::string& name, uint32_t partition_num,
                           uint32_t partition_id);

 private:
  // graphs_[graph_name][partition_num][partition_id] = pointer of graph
  std::map<std::tuple<std::string, uint32_t, uint32_t>, Graph*> graphs_;
};

extern DemoStorage demo_storage;

}  // namespace DEMO_STORAGE_NAMESPACE

#endif  // STORAGE_STORAGE_H_
