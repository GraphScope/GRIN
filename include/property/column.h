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

/**
 @file column.h
 @brief Define the column related APIs
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GRIN_INCLUDE_PROPERTY_COLUMN_H_
#define GRIN_INCLUDE_PROPERTY_COLUMN_H_

#include "common/enum_types.h"

#if defined(GRIN_ENABLE_COLUMN) && defined(GRIN_ENABLE_VERTEX_INTERNAL_ID_INDEX)
const int* grin_get_vertex_property_column_of_int32(GRIN_GRAPH, GRIN_VERTEX_PROPERTY, size_t* row_num);

const float* grin_get_vertex_property_column_of_float(GRIN_GRAPH, GRIN_VERTEX_PROPERTY, size_t* row_num);

const char* grin_get_vertex_property_column_of_string(GRIN_GRAPH, GRIN_VERTEX_PROPERTY, size_t* row_num); //seperated by \0

const float* grin_get_vertex_property_column_of_float_array(GRIN_GRAPH, GRIN_VERTEX_PROPERTY, size_t* row_num, size_t* length); // assume fixed length

typedef struct{const char* data, size_t size} GrinString;

#endif


#endif  // GRIN_INCLUDE_PROPERTY_COLUMN_H_

#ifdef __cplusplus
}
#endif