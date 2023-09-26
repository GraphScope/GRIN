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
#include "property/primarykey.h"

#ifdef GRIN_ENABLE_VERTEX_PRIMARY_KEYS
GRIN_VERTEX_TYPE_LIST grin_get_vertex_types_with_primary_keys(GRIN_GRAPH g) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto vtl = new GRIN_VERTEX_TYPE_LIST_T();
  auto vtype_num = _g->GetVertexTypeNum();
  for (auto i = 0; i < vtype_num; i++) {
    auto& properties = _g->GetVertexProperties(i);
    for (auto& property : properties) {
      if (property.is_primary_) {
        vtl->push_back(i);
        break;
      }
    }
  }
  return vtl;
}

GRIN_VERTEX_PROPERTY_LIST grin_get_primary_keys_by_vertex_type(
    GRIN_GRAPH g, GRIN_VERTEX_TYPE vtype) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto vpl = new GRIN_VERTEX_PROPERTY_LIST_T();
  auto& properties = _g->GetVertexProperties(vtype);
  for (auto i = 0; i < properties.size(); i++) {
    auto& property = properties[i];
    if (property.is_primary_) {
      vpl->push_back(
          DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(vtype, i));
    }
  }
  return vpl;
}

GRIN_ROW grin_get_vertex_primary_keys_row(GRIN_GRAPH g, GRIN_VERTEX v) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& _v = _g->GetVertex(v);
  auto vtype = DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(v);
  auto& properties = _g->GetVertexProperties(vtype);
  auto row = new GRIN_ROW_T();
  for (auto i = 0; i < properties.size(); i++) {
    auto& property = properties[i];
    if (property.is_primary_) {
      row->push_back(_v.GetPropertyAny(property.name_));
    }
  }
  return row;
}
#endif

#ifdef GRIN_ENABLE_EDGE_PRIMARY_KEYS
GRIN_EDGE_TYPE_LIST grin_get_edge_types_with_primary_keys(GRIN_GRAPH g) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto etl = new GRIN_EDGE_TYPE_LIST_T();
  auto etype_num = _g->GetEdgeTypeNum();
  for (auto i = 0; i < etype_num; i++) {
    auto& properties = _g->GetEdgeProperties(i);
    for (auto& property : properties) {
      if (property.is_primary_) {
        etl->push_back(i);
        break;
      }
    }
  }
  return etl;
}

GRIN_EDGE_PROPERTY_LIST grin_get_primary_keys_by_edge_type(
    GRIN_GRAPH g, GRIN_EDGE_TYPE etype) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto epl = new GRIN_EDGE_PROPERTY_LIST_T();
  auto& properties = _g->GetEdgeProperties(etype);
  for (auto i = 0; i < properties.size(); i++) {
    auto& property = properties[i];
    if (property.is_primary_) {
      epl->push_back(
          DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(etype, i));
    }
  }
  return epl;
}

GRIN_ROW grin_get_edge_primary_keys_row(GRIN_GRAPH g, GRIN_EDGE e) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& _e = _g->GetEdge(e);
  auto etype = DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(e);
  auto& properties = _g->GetEdgeProperties(etype);
  auto row = new GRIN_ROW_T();
  for (auto i = 0; i < properties.size(); i++) {
    auto& property = properties[i];
    if (property.is_primary_) {
      row->push_back(_e.GetPropertyAny(property.name_));
    }
  }
  return row;
}
#endif
