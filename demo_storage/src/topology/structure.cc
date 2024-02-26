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

#include <string>

#include "src/predefine.h"
#include "storage/storage.h"
// GRIN headers
#include "topology/structure.h"

GRIN_GRAPH grin_get_graph_from_storage(const char* uri) {
  if (uri == NULL)
    return GRIN_NULL_GRAPH;
  using DEMO_STORAGE_NAMESPACE::demo_storage;
  std::string path(uri);
  std::string prefix = "demo_storage://";
  if (path.find(prefix) == 0) {
    std::string name = path.substr(prefix.size());
    return demo_storage.GetGraph(name, 1, 0);
  } else {
    return GRIN_NULL_GRAPH;
  }
}

void grin_destroy_graph(GRIN_GRAPH g) { return; }

// Graph
#if defined(GRIN_ASSUME_HAS_DIRECTED_GRAPH) && \
    defined(GRIN_ASSUME_HAS_UNDIRECTED_GRAPH)
bool grin_is_directed(GRIN_GRAPH g) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  return _g->IsDirected();
}
#endif

#ifdef GRIN_ASSUME_HAS_MULTI_EDGE_GRAPH
bool grin_is_multigraph(GRIN_GRAPH) { return true; }
#endif

#ifndef GRIN_ENABLE_SCHEMA
size_t grin_get_vertex_num(GRIN_GRAPH);

size_t grin_get_edge_num(GRIN_GRAPH);
#endif

// Vertex
void grin_destroy_vertex(GRIN_GRAPH g, GRIN_VERTEX v) { return; }

bool grin_equal_vertex(GRIN_GRAPH g, GRIN_VERTEX v1, GRIN_VERTEX v2) {
  return v1 == v2;
}

// Data
#ifdef GRIN_WITH_VERTEX_DATA
GRIN_DATATYPE grin_get_vertex_data_datatype(GRIN_GRAPH g, GRIN_VERTEX v) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& _v = _g->GetVertex(v);
  return _v.GetVDataType();
}

const void* grin_get_vertex_data_value(GRIN_GRAPH g, GRIN_VERTEX v) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& _v = _g->GetVertex(v);
  auto type = _v.GetVDataType();
  switch (type) {
  case GRIN_DATATYPE::Int32:
    return &_v.GetVData<const int32_t&>();
  case GRIN_DATATYPE::UInt32:
    return &_v.GetVData<const uint32_t&>();
  case GRIN_DATATYPE::Int64:
    return &_v.GetVData<const int64_t&>();
  case GRIN_DATATYPE::UInt64:
    return &_v.GetVData<const uint64_t&>();
  case GRIN_DATATYPE::Float:
    return &_v.GetVData<const float&>();
  case GRIN_DATATYPE::Double:
    return &_v.GetVData<const double&>();
  case GRIN_DATATYPE::String:
    return _v.GetVData<const std::string&>().c_str();
  case GRIN_DATATYPE::Date32:
    return &_v.GetVData<const int32_t&>();
  case GRIN_DATATYPE::Time32:
    return &_v.GetVData<const int32_t&>();
  case GRIN_DATATYPE::Timestamp64:
    return &_v.GetVData<const int64_t&>();
  default:
    return GRIN_NULL_VERTEX_DATA;
  }
  return GRIN_NULL_VERTEX_DATA;
}
#endif

// Edge
void grin_destroy_edge(GRIN_GRAPH g, GRIN_EDGE e) { return; }

GRIN_VERTEX grin_get_src_vertex_from_edge(GRIN_GRAPH g, GRIN_EDGE e) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& _e = _g->GetEdge(e);
  return _e.GetSource();
}

GRIN_VERTEX grin_get_dst_vertex_from_edge(GRIN_GRAPH g, GRIN_EDGE e) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& _e = _g->GetEdge(e);
  return _e.GetDest();
}

#ifdef GRIN_WITH_EDGE_DATA
GRIN_DATATYPE grin_get_edge_data_datatype(GRIN_GRAPH g, GRIN_EDGE e) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& _e = _g->GetEdge(e);
  return _e.GetEDataType();
}

const void* grin_get_edge_data_value(GRIN_GRAPH g, GRIN_EDGE e) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& _e = _g->GetEdge(e);
  auto type = _e.GetEDataType();
  switch (type) {
  case GRIN_DATATYPE::Int32:
    return &_e.GetEData<const int32_t&>();
  case GRIN_DATATYPE::UInt32:
    return &_e.GetEData<const uint32_t&>();
  case GRIN_DATATYPE::Int64:
    return &_e.GetEData<const int64_t&>();
  case GRIN_DATATYPE::UInt64:
    return &_e.GetEData<const uint64_t&>();
  case GRIN_DATATYPE::Float:
    return &_e.GetEData<const float&>();
  case GRIN_DATATYPE::Double:
    return &_e.GetEData<const double&>();
  case GRIN_DATATYPE::String:
    return _e.GetEData<const std::string&>().c_str();
  case GRIN_DATATYPE::Date32:
    return &_e.GetEData<const int32_t&>();
  case GRIN_DATATYPE::Time32:
    return &_e.GetEData<const int32_t&>();
  case GRIN_DATATYPE::Timestamp64:
    return &_e.GetEData<const int64_t&>();
  default:
    return GRIN_NULL_EDGE_DATA;
  }
  return GRIN_NULL_EDGE_DATA;
}
#endif
