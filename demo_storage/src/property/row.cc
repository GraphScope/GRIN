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
#include "property/row.h"

#define __grin_check_row(_r, x)      \
  grin_error_code = NO_ERROR;        \
  if (idx >= _r->size()) {           \
    grin_error_code = INVALID_VALUE; \
    return x;                        \
  }

#if defined(GRIN_ENABLE_ROW) && \
    defined(GRIN_TRAIT_PROPERTY_VALUE_OF_FLOAT_ARRAY)
void grin_destroy_row_value_of_float_array(GRIN_GRAPH, const float*, size_t);

const float* grin_get_float_array_from_row(GRIN_GRAPH, GRIN_ROW, size_t,
                                           size_t*);

bool grin_insert_float_array_to_row(GRIN_GRAPH, GRIN_ROW, const float*, size_t);
#endif

#ifdef GRIN_ENABLE_ROW
void grin_destroy_row(GRIN_GRAPH g, GRIN_ROW r) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  delete _r;
}

void grin_destroy_row_value_of_string(GRIN_GRAPH g, const char* value) {
  return;
}

int grin_get_int32_from_row(GRIN_GRAPH g, GRIN_ROW r, size_t idx) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  __grin_check_row(_r, 0);
  return std::any_cast<int32_t>((*_r)[idx]);
}

unsigned int grin_get_uint32_from_row(GRIN_GRAPH g, GRIN_ROW r, size_t idx) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  __grin_check_row(_r, 0);
  return std::any_cast<uint32_t>((*_r)[idx]);
}

long long int grin_get_int64_from_row(GRIN_GRAPH g,  // NOLINT
                                      GRIN_ROW r, size_t idx) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  __grin_check_row(_r, 0);
  return std::any_cast<int64_t>((*_r)[idx]);
}

unsigned long long int grin_get_uint64_from_row(GRIN_GRAPH g,  // NOLINT
                                                GRIN_ROW r, size_t idx) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  __grin_check_row(_r, 0);
  return std::any_cast<uint64_t>((*_r)[idx]);
}

float grin_get_float_from_row(GRIN_GRAPH g, GRIN_ROW r, size_t idx) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  __grin_check_row(_r, 0);
  return std::any_cast<float>((*_r)[idx]);
}

double grin_get_double_from_row(GRIN_GRAPH g, GRIN_ROW r, size_t idx) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  __grin_check_row(_r, 0);
  return std::any_cast<double>((*_r)[idx]);
}

const char* grin_get_string_from_row(GRIN_GRAPH g, GRIN_ROW r, size_t idx) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  __grin_check_row(_r, NULL);
  return std::any_cast<const std::string&>((*_r)[idx]).c_str();
}

int grin_get_date32_from_row(GRIN_GRAPH g, GRIN_ROW r, size_t idx) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  __grin_check_row(_r, 0);
  return std::any_cast<int32_t>((*_r)[idx]);
}

int grin_get_time32_from_row(GRIN_GRAPH g, GRIN_ROW r, size_t idx) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  __grin_check_row(_r, 0);
  return std::any_cast<int32_t>((*_r)[idx]);
}

long long int grin_get_timestamp64_from_row(GRIN_GRAPH g, GRIN_ROW r,  // NOLINT
                                            size_t idx) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  __grin_check_row(_r, 0);
  return std::any_cast<int64_t>((*_r)[idx]);
}

GRIN_ROW grin_create_row(GRIN_GRAPH g) {
  auto r = new GRIN_ROW_T();
  return r;
}

bool grin_insert_int32_to_row(GRIN_GRAPH g, GRIN_ROW r, int value) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  _r->push_back(value);
  return true;
}

bool grin_insert_uint32_to_row(GRIN_GRAPH g, GRIN_ROW r, unsigned int value) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  _r->push_back(value);
  return true;
}

bool grin_insert_int64_to_row(GRIN_GRAPH g, GRIN_ROW r,
                              long long int value) {  // NOLINT
  auto _r = static_cast<GRIN_ROW_T*>(r);
  _r->push_back(value);
  return true;
}

bool grin_insert_uint64_to_row(GRIN_GRAPH g, GRIN_ROW r,
                               unsigned long long int value) {  // NOLINT
  auto _r = static_cast<GRIN_ROW_T*>(r);
  _r->push_back(value);
  return true;
}

bool grin_insert_float_to_row(GRIN_GRAPH g, GRIN_ROW r, float value) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  _r->push_back(value);
  return true;
}

bool grin_insert_double_to_row(GRIN_GRAPH g, GRIN_ROW r, double value) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  _r->push_back(value);
  return true;
}

bool grin_insert_string_to_row(GRIN_GRAPH g, GRIN_ROW r, const char* value) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  _r->push_back(std::string(value));
  return true;
}

bool grin_insert_date32_to_row(GRIN_GRAPH g, GRIN_ROW r, int value) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  _r->push_back(value);
  return true;
}

bool grin_insert_time32_to_row(GRIN_GRAPH g, GRIN_ROW r, int value) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  _r->push_back(value);
  return true;
}

bool grin_insert_timestamp64_to_row(GRIN_GRAPH g, GRIN_ROW r,
                                    long long int value) {  // NOLINT
  auto _r = static_cast<GRIN_ROW_T*>(r);
  _r->push_back(value);
  return true;
}
#endif

#if defined(GRIN_ENABLE_ROW) && defined(GRIN_TRAIT_CONST_VALUE_PTR)
const void* grin_get_value_from_row(GRIN_GRAPH g, GRIN_ROW r,
                                    GRIN_DATATYPE type, size_t idx) {
  auto _r = static_cast<GRIN_ROW_T*>(r);
  __grin_check_row(_r, NULL);
  switch (type) {
  case GRIN_DATATYPE::Int32:
    return &std::any_cast<const int32_t&>((*_r)[idx]);
  case GRIN_DATATYPE::UInt32:
    return &std::any_cast<const uint32_t&>((*_r)[idx]);
  case GRIN_DATATYPE::Int64:
    return &std::any_cast<const int64_t&>((*_r)[idx]);
  case GRIN_DATATYPE::UInt64:
    return &std::any_cast<const uint64_t&>((*_r)[idx]);
  case GRIN_DATATYPE::Float:
    return &std::any_cast<const float&>((*_r)[idx]);
  case GRIN_DATATYPE::Double:
    return &std::any_cast<const double&>((*_r)[idx]);
  case GRIN_DATATYPE::String:
    return std::any_cast<const std::string&>((*_r)[idx]).c_str();
  case GRIN_DATATYPE::Date32:
    return &std::any_cast<const int32_t&>((*_r)[idx]);
  case GRIN_DATATYPE::Time32:
    return &std::any_cast<const int32_t&>((*_r)[idx]);
  case GRIN_DATATYPE::Timestamp64:
    return &std::any_cast<const int64_t&>((*_r)[idx]);
  default:
    return NULL;
  }
  return NULL;
}
#endif

#if defined(GRIN_WITH_VERTEX_PROPERTY) && defined(GRIN_ENABLE_ROW)
GRIN_ROW grin_get_vertex_row(GRIN_GRAPH g, GRIN_VERTEX v) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto r = new GRIN_ROW_T();
  auto vtype = DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(v);
  auto _v = _g->GetVertex(v);
  auto& properties = _g->GetVertexProperties(vtype);
  for (auto& property : properties) {
    r->push_back(_v.GetPropertyAny(property.name_));
  }
  return r;
}
#endif

#if defined(GRIN_WITH_EDGE_PROPERTY) && defined(GRIN_ENABLE_ROW)
GRIN_ROW grin_get_edge_row(GRIN_GRAPH g, GRIN_EDGE e) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto r = new GRIN_ROW_T();
  auto etype = DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(e);
  auto _e = _g->GetEdge(e);
  auto& properties = _g->GetEdgeProperties(etype);
  for (auto& property : properties) {
    r->push_back(_e.GetPropertyAny(property.name_));
  }
  return r;
}
#endif
