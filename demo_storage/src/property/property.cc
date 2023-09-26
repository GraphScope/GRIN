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
#include "property/property.h"

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

void grin_destroy_string_value(GRIN_GRAPH g, const char* value) { return; }

#ifdef GRIN_WITH_VERTEX_PROPERTY_NAME
const char* grin_get_vertex_property_name(GRIN_GRAPH g, GRIN_VERTEX_TYPE vtype,
                                          GRIN_VERTEX_PROPERTY vp) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  if (vtype >= _g->GetVertexTypeNum())
    return nullptr;
  auto vp_id = DEMO_STORAGE_NAMESPACE::get_id_from_gid(vp);
  return _g->GetVertexPropertyName(vtype, vp_id).c_str();
}

GRIN_VERTEX_PROPERTY grin_get_vertex_property_by_name(GRIN_GRAPH g,
                                                      GRIN_VERTEX_TYPE vtype,
                                                      const char* name) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  if (vtype >= _g->GetVertexTypeNum())
    return GRIN_NULL_VERTEX_PROPERTY;
  auto vp_id = _g->GetVertexPropertyId(vtype, name);
  if (vp_id == -1)
    return GRIN_NULL_VERTEX_PROPERTY;
  return DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(vtype, vp_id);
}

GRIN_VERTEX_PROPERTY_LIST grin_get_vertex_properties_by_name(GRIN_GRAPH g,
                                                             const char* name) {
  auto vpl = new GRIN_VERTEX_PROPERTY_LIST_T();
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  for (unsigned i = 0; i < _g->GetVertexTypeNum(); ++i) {
    auto vp_id = _g->GetVertexPropertyId(i, name);
    if (vp_id != -1)
      vpl->push_back(
          DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(i, vp_id));
  }
  if (vpl->size() == 0) {
    delete vpl;
    return GRIN_NULL_VERTEX_PROPERTY_LIST;
  }
  return vpl;
}
#endif

#ifdef GRIN_WITH_EDGE_PROPERTY_NAME
const char* grin_get_edge_property_name(GRIN_GRAPH g, GRIN_EDGE_TYPE etype,
                                        GRIN_EDGE_PROPERTY ep) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  if (etype >= _g->GetEdgeTypeNum())
    return nullptr;
  auto ep_id = DEMO_STORAGE_NAMESPACE::get_id_from_gid(ep);
  return _g->GetEdgePropertyName(etype, ep_id).c_str();
}

GRIN_EDGE_PROPERTY grin_get_edge_property_by_name(GRIN_GRAPH g,
                                                  GRIN_EDGE_TYPE etype,
                                                  const char* name) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  if (etype >= _g->GetEdgeTypeNum())
    return GRIN_NULL_EDGE_PROPERTY;
  auto ep_id = _g->GetEdgePropertyId(etype, name);
  if (ep_id == -1)
    return GRIN_NULL_EDGE_PROPERTY;
  return DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(etype, ep_id);
}

GRIN_EDGE_PROPERTY_LIST grin_get_edge_properties_by_name(GRIN_GRAPH g,
                                                         const char* name) {
  auto epl = new GRIN_EDGE_PROPERTY_LIST_T();
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  for (unsigned i = 0; i < _g->GetEdgeTypeNum(); ++i) {
    auto ep_id = _g->GetEdgePropertyId(i, name);
    if (ep_id != -1)
      epl->push_back(
          DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(i, ep_id));
  }
  if (epl->size() == 0) {
    delete epl;
    return GRIN_NULL_EDGE_PROPERTY_LIST;
  }
  return epl;
}
#endif

#ifdef GRIN_WITH_VERTEX_PROPERTY
bool grin_equal_vertex_property(GRIN_GRAPH g, GRIN_VERTEX_PROPERTY vp1,
                                GRIN_VERTEX_PROPERTY vp2) {
  return vp1 == vp2;
}

void grin_destroy_vertex_property(GRIN_GRAPH g, GRIN_VERTEX_PROPERTY vp) {
  return;
}

GRIN_DATATYPE grin_get_vertex_property_datatype(GRIN_GRAPH g,
                                                GRIN_VERTEX_PROPERTY vp) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetVertexProperty(vp);
  return property.datatype_;
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

GRIN_VERTEX_TYPE grin_get_vertex_type_from_property(GRIN_GRAPH g,
                                                    GRIN_VERTEX_PROPERTY vp) {
  return DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(vp);
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

#ifdef GRIN_WITH_EDGE_PROPERTY
bool grin_equal_edge_property(GRIN_GRAPH g, GRIN_EDGE_PROPERTY ep1,
                              GRIN_EDGE_PROPERTY ep2) {
  return ep1 == ep2;
}

void grin_destroy_edge_property(GRIN_GRAPH g, GRIN_EDGE_PROPERTY ep) { return; }

GRIN_DATATYPE grin_get_edge_property_datatype(GRIN_GRAPH g,
                                              GRIN_EDGE_PROPERTY ep) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& property = _g->GetEdgeProperty(ep);
  return property.datatype_;
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

GRIN_EDGE_TYPE grin_get_edge_type_from_property(GRIN_GRAPH g,
                                                GRIN_EDGE_PROPERTY ep) {
  return DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(ep);
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
