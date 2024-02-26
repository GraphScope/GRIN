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

#if !defined(GRIN_ENABLE_SCHEMA) && defined(GRIN_WITH_VERTEX_PROPERTY)
GRIN_VERTEX_PROPERTY_LIST grin_get_vertex_property_list(GRIN_GRAPH,
                                                        GRIN_VERTEX);

const char* grin_get_vertex_property_name(GRIN_GRAPH, GRIN_VERTEX,
                                          GRIN_VERTEX_PROPERTY);

GRIN_VERTEX_PROPERTY grin_get_vertex_property_by_name(GRIN_GRAPH, GRIN_VERTEX,
                                                      const char* name);
#endif

#if defined(GRIN_ENABLE_SCHEMA) && defined(GRIN_WITH_VERTEX_PROPERTY)
GRIN_VERTEX_PROPERTY_LIST grin_get_vertex_property_list_by_type(
    GRIN_GRAPH g, GRIN_VERTEX_TYPE vtype) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  if (vtype >= _g->GetVertexTypeNum())
    return GRIN_NULL_VERTEX_PROPERTY_LIST;
  auto vpl = new GRIN_VERTEX_PROPERTY_LIST_T();
  auto n = _g->GetVertexPropertyNum(vtype);
  for (auto i = 0; i < n; ++i) {
    auto vp =
        DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(vtype, i);
    vpl->push_back(vp);
  }
  return vpl;
}

GRIN_VERTEX_TYPE grin_get_vertex_type_from_property(GRIN_GRAPH g,
                                                    GRIN_VERTEX_PROPERTY vp) {
  return DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(vp);
}

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

GRIN_VERTEX_PROPERTY grin_get_vertex_property_by_id(
    GRIN_GRAPH g, GRIN_VERTEX_TYPE vtype, GRIN_VERTEX_PROPERTY_ID id) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  if (vtype >= 0 & vtype < _g->GetVertexTypeNum() && id >= 0 &&
      id < _g->GetVertexPropertyNum(vtype)) {
    return DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(vtype, id);
  } else {
    return GRIN_NULL_VERTEX_PROPERTY;
  }
}

GRIN_VERTEX_PROPERTY_ID grin_get_vertex_property_id(GRIN_GRAPH g,
                                                    GRIN_VERTEX_TYPE vtype,
                                                    GRIN_VERTEX_PROPERTY vp) {
  return DEMO_STORAGE_NAMESPACE::get_id_from_gid(vp);
}
#endif

#if !defined(GRIN_ENABLE_SCHEMA) && defined(GRIN_WITH_EDGE_PROPERTY)
GRIN_EDGE_PROPERTY_LIST grin_get_edge_property_list(GRIN_GRAPH, GRIN_EDGE);

const char* grin_get_edge_property_name(GRIN_GRAPH, GRIN_EDGE,
                                        GRIN_EDGE_PROPERTY);

GRIN_EDGE_PROPERTY grin_get_edge_property_by_name(GRIN_GRAPH, GRIN_EDGE,
                                                  const char* name);
#endif

#if defined(GRIN_ENABLE_SCHEMA) && defined(GRIN_WITH_EDGE_PROPERTY)
GRIN_EDGE_PROPERTY_LIST grin_get_edge_property_list_by_type(
    GRIN_GRAPH g, GRIN_EDGE_TYPE etype) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  if (etype >= _g->GetEdgeTypeNum())
    return GRIN_NULL_VERTEX_PROPERTY_LIST;
  auto epl = new GRIN_EDGE_PROPERTY_LIST_T();
  auto n = _g->GetEdgePropertyNum(etype);
  for (auto i = 0; i < n; ++i) {
    auto ep =
        DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(etype, i);
    epl->push_back(ep);
  }
  return epl;
}

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

GRIN_EDGE_TYPE grin_get_edge_type_from_property(GRIN_GRAPH g,
                                                GRIN_EDGE_PROPERTY ep) {
  return DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(ep);
}

GRIN_EDGE_PROPERTY grin_get_edge_property_by_id(GRIN_GRAPH g,
                                                GRIN_EDGE_TYPE etype,
                                                GRIN_EDGE_PROPERTY_ID id) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  if (etype >= 0 && etype < _g->GetEdgeTypeNum() && id >= 0 &&
      id < _g->GetEdgePropertyNum(etype)) {
    return DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(etype, id);
  } else {
    return GRIN_NULL_EDGE_PROPERTY;
  }
}

GRIN_EDGE_PROPERTY_ID grin_get_edge_property_id(GRIN_GRAPH g,
                                                GRIN_EDGE_TYPE etype,
                                                GRIN_EDGE_PROPERTY ep) {
  return DEMO_STORAGE_NAMESPACE::get_id_from_gid(ep);
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
#endif
