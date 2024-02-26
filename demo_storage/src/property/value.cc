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

#include "src/predefine.h"
// GRIN headers
#include "common/error.h"
#include "property/value.h"

#define __grin_check_vertex_property(v, vp, x)                    \
  grin_error_code = NO_ERROR;                                     \
  auto vtype0 = DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(v);  \
  auto vtype1 = DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(vp); \
  if (vtype0 != vtype1) {                                         \
    grin_error_code = INVALID_VALUE;                              \
    return x;                                                     \
  }

#define __grin_check_edge_property(e, ep, x)                      \
  grin_error_code = NO_ERROR;                                     \
  auto etype0 = DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(e);  \
  auto etype1 = DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(ep); \
  if (etype0 != etype1) {                                         \
    grin_error_code = INVALID_VALUE;                              \
    return x;                                                     \
  }

#if defined(GRIN_WITH_VERTEX_PROPERTY) && \
    defined(GRIN_TRAIT_PROPERTY_VALUE_OF_FLOAT_ARRAY)
void grin_destroy_vertex_property_value_of_float_array(GRIN_GRAPH g,
                                                       const float* value,
                                                       size_t length) {
  return;
}

const float* grin_get_vertex_property_value_of_float_array(
    GRIN_GRAPH g, GRIN_VERTEX v, GRIN_VERTEX_PROPERTY vp, size_t* length) {
  __grin_check_vertex_property(v, vp, NULL);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetVertexProperty(vp);
  auto& _v = _g->GetVertex(v);
  *length = _v.GetProperty<const std::vector<float>&>(property.name_).size();
  return _v.GetProperty<const std::vector<float>&>(property.name_).data();
}
#endif

#ifdef GRIN_WITH_VERTEX_PROPERTY
void grin_destroy_vertex_property_value_of_string(GRIN_GRAPH v,
                                                  const char* value) {
  return;
}

int grin_get_vertex_property_value_of_int32(GRIN_GRAPH g, GRIN_VERTEX v,
                                            GRIN_VERTEX_PROPERTY vp) {
  __grin_check_vertex_property(v, vp, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetVertexProperty(vp);
  auto& _v = _g->GetVertex(v);
  return _v.GetProperty<int32_t>(property.name_);
}

unsigned int grin_get_vertex_property_value_of_uint32(GRIN_GRAPH g,  // NOLINT
                                                      GRIN_VERTEX v,
                                                      GRIN_VERTEX_PROPERTY vp) {
  __grin_check_vertex_property(v, vp, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetVertexProperty(vp);
  auto& _v = _g->GetVertex(v);
  return _v.GetProperty<uint32_t>(property.name_);
}

long long int grin_get_vertex_property_value_of_int64(GRIN_GRAPH g,  // NOLINT
                                                      GRIN_VERTEX v,
                                                      GRIN_VERTEX_PROPERTY vp) {
  __grin_check_vertex_property(v, vp, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetVertexProperty(vp);
  auto& _v = _g->GetVertex(v);
  return _v.GetProperty<int64_t>(property.name_);
}

unsigned long long int grin_get_vertex_property_value_of_uint64(  // NOLINT
    GRIN_GRAPH g, GRIN_VERTEX v, GRIN_VERTEX_PROPERTY vp) {
  __grin_check_vertex_property(v, vp, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetVertexProperty(vp);
  auto& _v = _g->GetVertex(v);
  return _v.GetProperty<uint64_t>(property.name_);
}

float grin_get_vertex_property_value_of_float(GRIN_GRAPH g, GRIN_VERTEX v,
                                              GRIN_VERTEX_PROPERTY vp) {
  __grin_check_vertex_property(v, vp, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetVertexProperty(vp);
  auto& _v = _g->GetVertex(v);
  return _v.GetProperty<float>(property.name_);
}

double grin_get_vertex_property_value_of_double(GRIN_GRAPH g, GRIN_VERTEX v,
                                                GRIN_VERTEX_PROPERTY vp) {
  __grin_check_vertex_property(v, vp, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetVertexProperty(vp);
  auto& _v = _g->GetVertex(v);
  return _v.GetProperty<double>(property.name_);
}

const char* grin_get_vertex_property_value_of_string(GRIN_GRAPH g,
                                                     GRIN_VERTEX v,
                                                     GRIN_VERTEX_PROPERTY vp) {
  __grin_check_vertex_property(v, vp, NULL);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetVertexProperty(vp);
  auto& _v = _g->GetVertex(v);
  return _v.GetProperty<const std::string&>(property.name_).c_str();
}

int grin_get_vertex_property_value_of_date32(GRIN_GRAPH g, GRIN_VERTEX v,
                                             GRIN_VERTEX_PROPERTY vp) {
  __grin_check_vertex_property(v, vp, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetVertexProperty(vp);
  auto& _v = _g->GetVertex(v);
  return _v.GetProperty<int32_t>(property.name_);
}

int grin_get_vertex_property_value_of_time32(GRIN_GRAPH g, GRIN_VERTEX v,
                                             GRIN_VERTEX_PROPERTY vp) {
  __grin_check_vertex_property(v, vp, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetVertexProperty(vp);
  auto& _v = _g->GetVertex(v);
  return _v.GetProperty<int32_t>(property.name_);
}

long long int grin_get_vertex_property_value_of_timestamp64(  // NOLINT
    GRIN_GRAPH g, GRIN_VERTEX v, GRIN_VERTEX_PROPERTY vp) {
  __grin_check_vertex_property(v, vp, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetVertexProperty(vp);
  auto& _v = _g->GetVertex(v);
  return _v.GetProperty<int64_t>(property.name_);
}
#endif

#if defined(GRIN_WITH_VERTEX_PROPERTY) && defined(GRIN_TRAIT_CONST_VALUE_PTR)
const void* grin_get_vertex_property_value(GRIN_GRAPH g, GRIN_VERTEX v,
                                           GRIN_VERTEX_PROPERTY vp) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  __grin_check_vertex_property(v, vp, NULL);
  auto& _v = _g->GetVertex(v);
  auto& property = _g->GetVertexProperty(vp);
  auto& name = property.name_;
  auto& type = property.datatype_;
  switch (type) {
  case GRIN_DATATYPE::Int32:
    return &_v.GetProperty<const int32_t&>(name);
  case GRIN_DATATYPE::UInt32:
    return &_v.GetProperty<const uint32_t&>(name);
  case GRIN_DATATYPE::Int64:
    return &_v.GetProperty<const int64_t&>(name);
  case GRIN_DATATYPE::UInt64:
    return &_v.GetProperty<const uint64_t&>(name);
  case GRIN_DATATYPE::Float:
    return &_v.GetProperty<const float&>(name);
  case GRIN_DATATYPE::Double:
    return &_v.GetProperty<const double&>(name);
  case GRIN_DATATYPE::String:
    return _v.GetProperty<const std::string&>(name).c_str();
  case GRIN_DATATYPE::Date32:
    return &_v.GetProperty<const int32_t&>(name);
  case GRIN_DATATYPE::Time32:
    return &_v.GetProperty<const int32_t&>(name);
  case GRIN_DATATYPE::Timestamp64:
    return &_v.GetProperty<const int64_t&>(name);
  default:
    return NULL;
  }
  return NULL;
}
#endif

#if defined(GRIN_WITH_EDGE_PROPERTY) && \
    defined(GRIN_TRAIT_PROPERTY_VALUE_OF_FLOAT_ARRAY)
void grin_destroy_edge_property_value_of_float_array(GRIN_GRAPH g,
                                                     const float* value,
                                                     size_t length) {
  return;
}

const float* grin_get_edge_property_value_of_float_array(GRIN_GRAPH g,
                                                         GRIN_EDGE e,
                                                         GRIN_EDGE_PROPERTY ep,
                                                         size_t* length) {
  __grin_check_edge_property(e, ep, NULL);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetEdgeProperty(ep);
  auto& _e = _g->GetEdge(e);
  *length = _e.GetProperty<const std::vector<float>&>(property.name_).size();
  return _e.GetProperty<const std::vector<float>&>(property.name_).data();
}
#endif

#ifdef GRIN_WITH_EDGE_PROPERTY
void grin_destroy_edge_property_value_of_string(GRIN_GRAPH g,
                                                const char* value) {
  return;
}

int grin_get_edge_property_value_of_int32(GRIN_GRAPH g, GRIN_EDGE e,
                                          GRIN_EDGE_PROPERTY ep) {
  __grin_check_edge_property(e, ep, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetEdgeProperty(ep);
  auto& _e = _g->GetEdge(e);
  return _e.GetProperty<int32_t>(property.name_);
}

unsigned int grin_get_edge_property_value_of_uint32(GRIN_GRAPH g,  // NOLINT
                                                    GRIN_EDGE e,
                                                    GRIN_EDGE_PROPERTY ep) {
  __grin_check_edge_property(e, ep, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetEdgeProperty(ep);
  auto& _e = _g->GetEdge(e);
  return _e.GetProperty<uint32_t>(property.name_);
}

long long int grin_get_edge_property_value_of_int64(GRIN_GRAPH g,  //  NOLINT
                                                    GRIN_EDGE e,
                                                    GRIN_EDGE_PROPERTY ep) {
  __grin_check_edge_property(e, ep, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetEdgeProperty(ep);
  auto& _e = _g->GetEdge(e);
  return _e.GetProperty<int64_t>(property.name_);
}

unsigned long long int grin_get_edge_property_value_of_uint64(  // NOLINT
    GRIN_GRAPH g, GRIN_EDGE e, GRIN_EDGE_PROPERTY ep) {
  __grin_check_edge_property(e, ep, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetEdgeProperty(ep);
  auto& _e = _g->GetEdge(e);
  return _e.GetProperty<uint64_t>(property.name_);
}

float grin_get_edge_property_value_of_float(GRIN_GRAPH g, GRIN_EDGE e,
                                            GRIN_EDGE_PROPERTY ep) {
  __grin_check_edge_property(e, ep, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetEdgeProperty(ep);
  auto& _e = _g->GetEdge(e);
  return _e.GetProperty<float>(property.name_);
}

double grin_get_edge_property_value_of_double(GRIN_GRAPH g, GRIN_EDGE e,
                                              GRIN_EDGE_PROPERTY ep) {
  __grin_check_edge_property(e, ep, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetEdgeProperty(ep);
  auto& _e = _g->GetEdge(e);
  return _e.GetProperty<double>(property.name_);
}

const char* grin_get_edge_property_value_of_string(GRIN_GRAPH g, GRIN_EDGE e,
                                                   GRIN_EDGE_PROPERTY ep) {
  __grin_check_edge_property(e, ep, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetEdgeProperty(ep);
  auto& _e = _g->GetEdge(e);
  return _e.GetProperty<const std::string&>(property.name_).c_str();
}

int grin_get_edge_property_value_of_date32(GRIN_GRAPH g, GRIN_EDGE e,
                                           GRIN_EDGE_PROPERTY ep) {
  __grin_check_edge_property(e, ep, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetEdgeProperty(ep);
  auto& _e = _g->GetEdge(e);
  return _e.GetProperty<int32_t>(property.name_);
}

int grin_get_edge_property_value_of_time32(GRIN_GRAPH g, GRIN_EDGE e,
                                           GRIN_EDGE_PROPERTY ep) {
  __grin_check_edge_property(e, ep, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetEdgeProperty(ep);
  auto& _e = _g->GetEdge(e);
  return _e.GetProperty<int32_t>(property.name_);
}

long long int grin_get_edge_property_value_of_timestamp64(  // NOLINT
    GRIN_GRAPH g, GRIN_EDGE e, GRIN_EDGE_PROPERTY ep) {
  __grin_check_edge_property(e, ep, 0);
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetEdgeProperty(ep);
  auto& _e = _g->GetEdge(e);
  return _e.GetProperty<int64_t>(property.name_);
}
#endif

#if defined(GRIN_WITH_EDGE_PROPERTY) && defined(GRIN_TRAIT_CONST_VALUE_PTR)
const void* grin_get_edge_property_value(GRIN_GRAPH g, GRIN_EDGE e,
                                         GRIN_EDGE_PROPERTY ep) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  __grin_check_edge_property(e, ep, NULL);
  auto& _e = _g->GetEdge(e);
  auto& property = _g->GetEdgeProperty(ep);
  auto& name = property.name_;
  auto& type = property.datatype_;
  switch (type) {
  case GRIN_DATATYPE::Int32:
    return &_e.GetProperty<const int32_t&>(name);
  case GRIN_DATATYPE::UInt32:
    return &_e.GetProperty<const uint32_t&>(name);
  case GRIN_DATATYPE::Int64:
    return &_e.GetProperty<const int64_t&>(name);
  case GRIN_DATATYPE::UInt64:
    return &_e.GetProperty<const uint64_t&>(name);
  case GRIN_DATATYPE::Float:
    return &_e.GetProperty<const float&>(name);
  case GRIN_DATATYPE::Double:
    return &_e.GetProperty<const double&>(name);
  case GRIN_DATATYPE::String:
    return _e.GetProperty<const std::string&>(name).c_str();
  case GRIN_DATATYPE::Date32:
    return &_e.GetProperty<const int32_t&>(name);
  case GRIN_DATATYPE::Time32:
    return &_e.GetProperty<const int32_t&>(name);
  case GRIN_DATATYPE::Timestamp64:
    return &_e.GetProperty<const int64_t&>(name);
  default:
    return NULL;
  }
  return NULL;
}
#endif
