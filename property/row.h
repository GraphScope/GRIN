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
 @file row.h
 @brief Define the row related APIs
*/

#ifndef GRIN_INCLUDE_PROPERTY_ROW_H_
#define GRIN_INCLUDE_PROPERTY_ROW_H_

#include "../../predefine.h"

void grin_destroy_string_value(GRIN_GRAPH, const char*);

/** @name GRIN_ROW
 * GRIN_ROW works as the pure value array for the properties of a vertex or an edge.
 * In general, you can think of GRIN_ROW as an array of void*, where each void* points to
 * the value of a property. GRIN assumes the user already knows the corresponding
 * property list beforehead, so that she/he knows how to cast the void* into the
 * property's data type.
 */
///@{
#ifdef GRIN_ENABLE_ROW
void grin_destroy_row(GRIN_GRAPH, GRIN_ROW);

int grin_get_int32_from_row(GRIN_GRAPH, GRIN_ROW, size_t);

unsigned int grin_get_uint32_from_row(GRIN_GRAPH, GRIN_ROW, size_t);

long long int grin_get_int64_from_row(GRIN_GRAPH, GRIN_ROW, size_t);

unsigned long long int grin_get_uint64_from_row(GRIN_GRAPH, GRIN_ROW, size_t);

float grin_get_float_from_row(GRIN_GRAPH, GRIN_ROW, size_t);

double grin_get_double_from_row(GRIN_GRAPH, GRIN_ROW, size_t);

const char* grin_get_string_from_row(GRIN_GRAPH, GRIN_ROW, size_t);

int grin_get_date32_from_row(GRIN_GRAPH, GRIN_ROW, size_t);

int grin_get_time32_from_row(GRIN_GRAPH, GRIN_ROW, size_t);

long long int grin_get_timestamp64_from_row(GRIN_GRAPH, GRIN_ROW, size_t);

/** @brief create a row, usually to get vertex/edge by primary keys */
GRIN_ROW grin_create_row(GRIN_GRAPH);

bool grin_insert_int32_to_row(GRIN_GRAPH, GRIN_ROW, int);

bool grin_insert_uint32_to_row(GRIN_GRAPH, GRIN_ROW, unsigned int);

bool grin_insert_int64_to_row(GRIN_GRAPH, GRIN_ROW, long long int);

bool grin_insert_uint64_to_row(GRIN_GRAPH, GRIN_ROW, unsigned long long int);

bool grin_insert_float_to_row(GRIN_GRAPH, GRIN_ROW, float);

bool grin_insert_double_to_row(GRIN_GRAPH, GRIN_ROW, double);

bool grin_insert_string_to_row(GRIN_GRAPH, GRIN_ROW, const char*);

bool grin_insert_date32_to_row(GRIN_GRAPH, GRIN_ROW, int);

bool grin_insert_time32_to_row(GRIN_GRAPH, GRIN_ROW, int);

bool grin_insert_timestamp64_to_row(GRIN_GRAPH, GRIN_ROW, long long int);
#endif

#if defined(GRIN_ENABLE_ROW) && defined(GRIN_TRAIT_CONST_VALUE_PTR)
/** @brief the value of a property from row by its position in row */
const void* grin_get_value_from_row(GRIN_GRAPH, GRIN_ROW, GRIN_DATATYPE, size_t);
#endif
///@}

#if defined(GRIN_WITH_VERTEX_PROPERTY) && defined(GRIN_ENABLE_ROW)
/**
 * @brief get vertex row directly from the graph, this API only works for row store system
 * @param GRIN_GRAPH the graph
 * @param GRIN_VERTEX the vertex which is the row index
 * @param GRIN_VERTEX_PROPERTY_LIST the vertex property list as columns
 */
GRIN_ROW grin_get_vertex_row(GRIN_GRAPH, GRIN_VERTEX);
#endif


#if defined(GRIN_WITH_EDGE_PROPERTY) && defined(GRIN_ENABLE_ROW)
/**
 * @brief get edge row directly from the graph, this API only works for row store system
 * @param GRIN_GRAPH the graph
 * @param GRIN_EDGE the edge which is the row index
 * @param GRIN_EDGE_PROPERTY_LIST the edge property list as columns
 */
GRIN_ROW grin_get_edge_row(GRIN_GRAPH, GRIN_EDGE);
#endif

#endif  // GRIN_INCLUDE_PROPERTY_ROW_H_