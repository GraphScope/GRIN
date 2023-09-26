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
#include "property/type.h"

#ifdef GRIN_WITH_VERTEX_PROPERTY
// Vertex type
bool grin_equal_vertex_type(GRIN_GRAPH g, GRIN_VERTEX_TYPE vtype1,
                            GRIN_VERTEX_TYPE vtype2) {
  return vtype1 == vtype2;
}

GRIN_VERTEX_TYPE grin_get_vertex_type(GRIN_GRAPH g, GRIN_VERTEX v) {
  return DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(v);
}

void grin_destroy_vertex_type(GRIN_GRAPH g, GRIN_VERTEX_TYPE vtype) { return; }

// Vertex type list
GRIN_VERTEX_TYPE_LIST grin_get_vertex_type_list(GRIN_GRAPH g) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto vtl = new GRIN_VERTEX_TYPE_LIST_T();
  auto num = _g->GetVertexTypeNum();
  for (auto i = 0; i < num; i++)
    vtl->push_back(i);
  return vtl;
}

void grin_destroy_vertex_type_list(GRIN_GRAPH g, GRIN_VERTEX_TYPE_LIST vtl) {
  auto _vtl = static_cast<GRIN_VERTEX_TYPE_LIST_T*>(vtl);
  delete _vtl;
}

GRIN_VERTEX_TYPE_LIST grin_create_vertex_type_list(GRIN_GRAPH g) {
  auto vtl = new GRIN_VERTEX_TYPE_LIST_T();
  return vtl;
}

bool grin_insert_vertex_type_to_list(GRIN_GRAPH g, GRIN_VERTEX_TYPE_LIST vtl,
                                     GRIN_VERTEX_TYPE vtype) {
  auto _vtl = static_cast<GRIN_VERTEX_TYPE_LIST_T*>(vtl);
  _vtl->push_back(vtype);
  return true;
}

size_t grin_get_vertex_type_list_size(GRIN_GRAPH g, GRIN_VERTEX_TYPE_LIST vtl) {
  auto _vtl = static_cast<GRIN_VERTEX_TYPE_LIST_T*>(vtl);
  return _vtl->size();
}

GRIN_VERTEX_TYPE grin_get_vertex_type_from_list(GRIN_GRAPH g,
                                                GRIN_VERTEX_TYPE_LIST vtl,
                                                size_t idx) {
  auto _vtl = static_cast<GRIN_VERTEX_TYPE_LIST_T*>(vtl);
  if (idx >= _vtl->size())
    return GRIN_NULL_VERTEX_TYPE;
  return (*_vtl)[idx];
}
#endif

#ifdef GRIN_WITH_VERTEX_TYPE_NAME
const char* grin_get_vertex_type_name(GRIN_GRAPH g, GRIN_VERTEX_TYPE vtype) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  if (vtype >= _g->GetVertexTypeNum())
    return NULL;
  return _g->GetVertexTypeName(vtype).c_str();
}

GRIN_VERTEX_TYPE grin_get_vertex_type_by_name(GRIN_GRAPH g, const char* name) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto type_id = _g->GetVertexTypeId(std::string(name));
  if (type_id == -1)
    return GRIN_NULL_VERTEX_TYPE;
  return type_id;
}
#endif

#ifdef GRIN_TRAIT_NATURAL_ID_FOR_VERTEX_TYPE
GRIN_VERTEX_TYPE_ID grin_get_vertex_type_id(GRIN_GRAPH g,
                                            GRIN_VERTEX_TYPE vtype) {
  return vtype;
}

GRIN_VERTEX_TYPE grin_get_vertex_type_by_id(GRIN_GRAPH g,
                                            GRIN_VERTEX_TYPE_ID vti) {
  return vti;
}
#endif

#ifdef GRIN_WITH_EDGE_PROPERTY
// Edge type
bool grin_equal_edge_type(GRIN_GRAPH g, GRIN_EDGE_TYPE etype1,
                          GRIN_EDGE_TYPE etype2) {
  return etype1 == etype2;
}

GRIN_EDGE_TYPE grin_get_edge_type(GRIN_GRAPH g, GRIN_EDGE e) {
  return DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(e);
}

void grin_destroy_edge_type(GRIN_GRAPH g, GRIN_EDGE_TYPE etype) { return; }

// Edge type list
GRIN_EDGE_TYPE_LIST grin_get_edge_type_list(GRIN_GRAPH g) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto etl = new GRIN_EDGE_TYPE_LIST_T();
  auto num = _g->GetEdgeTypeNum();
  for (auto i = 0; i < num; i++)
    etl->push_back(i);
  return etl;
}

void grin_destroy_edge_type_list(GRIN_GRAPH g, GRIN_EDGE_TYPE_LIST etl) {
  auto _etl = static_cast<GRIN_EDGE_TYPE_LIST_T*>(etl);
  delete _etl;
}

GRIN_EDGE_TYPE_LIST grin_create_edge_type_list(GRIN_GRAPH g) {
  auto etl = new GRIN_EDGE_TYPE_LIST_T();
  return etl;
}

bool grin_insert_edge_type_to_list(GRIN_GRAPH g, GRIN_EDGE_TYPE_LIST etl,
                                   GRIN_EDGE_TYPE etype) {
  auto _etl = static_cast<GRIN_EDGE_TYPE_LIST_T*>(etl);
  _etl->push_back(etype);
  return true;
}

size_t grin_get_edge_type_list_size(GRIN_GRAPH g, GRIN_EDGE_TYPE_LIST etl) {
  auto _etl = static_cast<GRIN_EDGE_TYPE_LIST_T*>(etl);
  return _etl->size();
}

GRIN_EDGE_TYPE grin_get_edge_type_from_list(GRIN_GRAPH g,
                                            GRIN_EDGE_TYPE_LIST etl,
                                            size_t idx) {
  auto _etl = static_cast<GRIN_EDGE_TYPE_LIST_T*>(etl);
  if (idx >= _etl->size())
    return GRIN_NULL_EDGE_TYPE;
  return (*_etl)[idx];
}
#endif

#ifdef GRIN_WITH_EDGE_TYPE_NAME
const char* grin_get_edge_type_name(GRIN_GRAPH g, GRIN_EDGE_TYPE etype) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  if (etype >= _g->GetEdgeTypeNum())
    return NULL;
  return _g->GetEdgeTypeName(etype).c_str();
}

GRIN_EDGE_TYPE grin_get_edge_type_by_name(GRIN_GRAPH g, const char* name) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto type_id = _g->GetEdgeTypeId(std::string(name));
  if (type_id == -1)
    return GRIN_NULL_EDGE_TYPE;
  return type_id;
}
#endif

#ifdef GRIN_TRAIT_NATURAL_ID_FOR_EDGE_TYPE
GRIN_EDGE_TYPE_ID grin_get_edge_type_id(GRIN_GRAPH g, GRIN_EDGE_TYPE etype) {
  return etype;
}

GRIN_EDGE_TYPE grin_get_edge_type_by_id(GRIN_GRAPH g, GRIN_EDGE_TYPE_ID eti) {
  return eti;
}
#endif

#if defined(GRIN_WITH_VERTEX_PROPERTY) && defined(GRIN_WITH_EDGE_PROPERTY)
GRIN_VERTEX_TYPE_LIST grin_get_src_types_by_edge_type(GRIN_GRAPH g,
                                                      GRIN_EDGE_TYPE etype) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto vtl = new GRIN_VERTEX_TYPE_LIST_T();
  auto& vev_types = _g->GetVertexEdgeVertexTypes();
  for (auto& [vev_type, relation_type] : vev_types) {
    if (std::get<1>(vev_type) == etype) {
      vtl->push_back(std::get<0>(vev_type));
    }
  }
  return vtl;
}

GRIN_VERTEX_TYPE_LIST grin_get_dst_types_by_edge_type(GRIN_GRAPH g,
                                                      GRIN_EDGE_TYPE etype) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto vtl = new GRIN_VERTEX_TYPE_LIST_T();
  auto& vev_types = _g->GetVertexEdgeVertexTypes();
  for (auto& [vev_type, relation_type] : vev_types) {
    if (std::get<1>(vev_type) == etype) {
      vtl->push_back(std::get<2>(vev_type));
    }
  }
  return vtl;
}

GRIN_EDGE_TYPE_LIST
grin_get_edge_types_by_vertex_type_pair(GRIN_GRAPH g, GRIN_VERTEX_TYPE vtype1,
                                        GRIN_VERTEX_TYPE vtype2) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto etl = new GRIN_EDGE_TYPE_LIST_T();
  auto& vev_types = _g->GetVertexEdgeVertexTypes();
  for (auto& [vev_type, relation_type] : vev_types) {
    if (std::get<0>(vev_type) == vtype1 && std::get<2>(vev_type) == vtype2) {
      etl->push_back(std::get<1>(vev_type));
    }
  }
  return etl;
}
#endif
