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
#include "index/pk.h"
#include "property/primarykey.h"
#include "property/property.h"
#include "property/propertylist.h"
#include "property/row.h"

#if defined(GRIN_ENABLE_VERTEX_PK_INDEX) && \
    defined(GRIN_ENABLE_VERTEX_PRIMARY_KEYS)

GRIN_VERTEX grin_get_vertex_by_primary_keys_row(GRIN_GRAPH g,
                                                GRIN_VERTEX_TYPE vtype,
                                                GRIN_ROW r) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _r = static_cast<GRIN_ROW_T*>(r);
  auto property_list = grin_get_primary_keys_by_vertex_type(g, vtype);
  if (property_list == GRIN_NULL_VERTEX_PROPERTY_LIST ||
      grin_get_vertex_property_list_size(g, property_list) != _r->size()) {
    return GRIN_NULL_VERTEX;
  }
  auto vertex_num = _g->GetVertexNum(vtype);
  for (auto i = 0; i < vertex_num; ++i) {
    auto v = DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(vtype, i);
    auto row = grin_get_vertex_primary_keys_row(g, v);
    if (row == GRIN_NULL_ROW) {
      continue;
    }
    auto _row = static_cast<GRIN_ROW_T*>(row);
    if (_row->size() != _r->size()) {
      grin_destroy_row(g, row);
      continue;
    }
    bool is_same = true;
    for (auto j = 0; j < _row->size(); ++j) {
      auto property = grin_get_vertex_property_from_list(g, property_list, j);
      auto type = grin_get_vertex_property_datatype(g, property);
      auto value1 = grin_get_value_from_row(g, r, type, j);
      auto value2 = grin_get_value_from_row(g, row, type, j);
      if (value1 == NULL || value2 == NULL) {
        is_same = false;
        break;
      }
      switch (type) {
      case GRIN_DATATYPE::Int32:
        if (*static_cast<const int32_t*>(value1) !=
            *static_cast<const int32_t*>(value2)) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::UInt32:
        if (*static_cast<const uint32_t*>(value1) !=
            *static_cast<const uint32_t*>(value2)) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::Int64:
        if (*static_cast<const int64_t*>(value1) !=
            *static_cast<const int64_t*>(value2)) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::UInt64:
        if (*static_cast<const uint64_t*>(value1) !=
            *static_cast<const uint64_t*>(value2)) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::Float:
        if (*static_cast<const float*>(value1) !=
            *static_cast<const float*>(value2)) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::Double:
        if (*static_cast<const double*>(value1) !=
            *static_cast<const double*>(value2)) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::String:
        if (strcmp(static_cast<const char*>(value1),
                   static_cast<const char*>(value2)) != 0) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::Date32:
        if (*static_cast<const int32_t*>(value1) !=
            *static_cast<const int32_t*>(value2)) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::Time32:
        if (*static_cast<const int32_t*>(value1) !=
            *static_cast<const int32_t*>(value2)) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::Timestamp64:
        if (*static_cast<const int64_t*>(value1) !=
            *static_cast<const int64_t*>(value2)) {
          is_same = false;
        }
        break;
      default:
        is_same = false;
      }
    }
    grin_destroy_row(g, row);
    if (is_same) {
      return v;
    }
  }
  return GRIN_NULL_VERTEX;
}
#endif

#if defined(GRIN_ENABLE_EDGE_PK_INDEX) && defined(GRIN_ENABLE_EDGE_PRIMARY_KEYS)
GRIN_EDGE grin_get_edge_by_primary_keys_row(GRIN_GRAPH g, GRIN_EDGE_TYPE etype,
                                            GRIN_ROW r) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _r = static_cast<GRIN_ROW_T*>(r);
  auto property_list = grin_get_primary_keys_by_edge_type(g, etype);
  if (property_list == GRIN_NULL_EDGE_PROPERTY_LIST ||
      grin_get_edge_property_list_size(g, property_list) != _r->size()) {
    return GRIN_NULL_EDGE;
  }
  auto edge_num = _g->GetEdgeNum(etype);
  for (auto i = 0; i < edge_num; i++) {
    auto e = DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(etype, i);
    auto row = grin_get_edge_primary_keys_row(g, e);
    if (row == GRIN_NULL_ROW) {
      continue;
    }
    auto _row = static_cast<GRIN_ROW_T*>(row);
    if (_row->size() != _r->size()) {
      grin_destroy_row(g, row);
      continue;
    }
    bool is_same = true;
    for (auto j = 0; j < _row->size(); ++j) {
      auto property = grin_get_edge_property_from_list(g, property_list, j);
      auto type = grin_get_edge_property_datatype(g, property);
      auto value1 = grin_get_value_from_row(g, r, type, j);
      auto value2 = grin_get_value_from_row(g, row, type, j);
      if (value1 == NULL || value2 == NULL) {
        is_same = false;
        break;
      }
      switch (type) {
      case GRIN_DATATYPE::Int32:
        if (*static_cast<const int32_t*>(value1) !=
            *static_cast<const int32_t*>(value2)) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::UInt32:
        if (*static_cast<const uint32_t*>(value1) !=
            *static_cast<const uint32_t*>(value2)) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::Int64:
        if (*static_cast<const int64_t*>(value1) !=
            *static_cast<const int64_t*>(value2)) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::UInt64:
        if (*static_cast<const uint64_t*>(value1) !=
            *static_cast<const uint64_t*>(value2)) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::Float:
        if (*static_cast<const float*>(value1) !=
            *static_cast<const float*>(value2)) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::Double:
        if (*static_cast<const double*>(value1) !=
            *static_cast<const double*>(value2)) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::String:
        if (strcmp(static_cast<const char*>(value1),
                   static_cast<const char*>(value2)) != 0) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::Date32:
        if (*static_cast<const int32_t*>(value1) !=
            *static_cast<const int32_t*>(value2)) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::Time32:
        if (*static_cast<const int32_t*>(value1) !=
            *static_cast<const int32_t*>(value2)) {
          is_same = false;
        }
        break;
      case GRIN_DATATYPE::Timestamp64:
        if (*static_cast<const int64_t*>(value1) !=
            *static_cast<const int64_t*>(value2)) {
          is_same = false;
        }
        break;
      default:
        is_same = false;
      }
    }
    grin_destroy_row(g, row);
    if (is_same) {
      return e;
    }
  }
  return GRIN_NULL_EDGE;
}
#endif
