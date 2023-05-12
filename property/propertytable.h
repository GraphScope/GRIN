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
 @file propertytable.h
 @brief Define the property table related APIs
*/

#ifndef GRIN_INCLUDE_PROPERTY_PROPERTY_TABLE_H_
#define GRIN_INCLUDE_PROPERTY_PROPERTY_TABLE_H_

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

#ifdef GRIN_ENABLE_VERTEX_PROPERTY_TABLE
/**
 * @brief destroy vertex property table
 * @param GRIN_VERTEX_PROPERTY_TABLE vertex property table
 */
void grin_destroy_vertex_property_table(GRIN_GRAPH, GRIN_VERTEX_PROPERTY_TABLE);

/**
 * @brief get the vertex property table of a certain vertex type
 * No matter column or row store strategy is used in the storage,
 * GRIN recommends to first get the property table of the vertex type,
 * and then fetch values(rows) by vertex and property(list). However,
 * GRIN does provide direct row fetching API when GRIN_ASSUME_COLUMN_STORE_FOR_VERTEX_PROPERTY
 * is NOT set.
 * @param GRIN_GRAPH the graph
 * @param GRIN_VERTEX_TYPE the vertex type
 */
GRIN_VERTEX_PROPERTY_TABLE grin_get_vertex_property_table_by_type(GRIN_GRAPH, GRIN_VERTEX_TYPE);

int grin_get_int32_from_vertex_property_table(GRIN_GRAPH, GRIN_VERTEX_PROPERTY_TABLE, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

unsigned int grin_get_uint32_from_vertex_property_table(GRIN_GRAPH, GRIN_VERTEX_PROPERTY_TABLE, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

long long int grin_get_int64_from_vertex_property_table(GRIN_GRAPH, GRIN_VERTEX_PROPERTY_TABLE, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

unsigned long long int grin_get_uint64_from_vertex_property_table(GRIN_GRAPH, GRIN_VERTEX_PROPERTY_TABLE, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

float grin_get_float_from_vertex_property_table(GRIN_GRAPH, GRIN_VERTEX_PROPERTY_TABLE, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

double grin_get_double_from_vertex_property_table(GRIN_GRAPH, GRIN_VERTEX_PROPERTY_TABLE, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

const char* grin_get_string_from_vertex_property_table(GRIN_GRAPH, GRIN_VERTEX_PROPERTY_TABLE, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

int grin_get_date32_from_vertex_property_table(GRIN_GRAPH, GRIN_VERTEX_PROPERTY_TABLE, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

int grin_get_time32_from_vertex_property_table(GRIN_GRAPH, GRIN_VERTEX_PROPERTY_TABLE, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

long long int grin_get_timestamp64_from_vertex_property_table(GRIN_GRAPH, GRIN_VERTEX_PROPERTY_TABLE, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);
#endif

#if defined(GRIN_ENABLE_VERTEX_PROPERTY_TABLE) && defined(GRIN_TRAIT_CONST_VALUE_PTR)
/**
 * @brief get vertex property value from table as a const void*, callers don't have to
 * destroy the returned value pointer since they are handled by the storage
 * @param GRIN_VERTEX_PROPERTY_TABLE vertex property table
 * @param GRIN_VERTEX the vertex which is the row index
 * @param GRIN_VERTEX_PROPERTY the vertex property which is the column index
 * @return can be casted to the property data type by the caller
 */
const void* grin_get_value_from_vertex_property_table(GRIN_GRAPH, GRIN_VERTEX_PROPERTY_TABLE, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);
#endif

#if defined(GRIN_ENABLE_VERTEX_PROPERTY_TABLE) && defined(GRIN_ENABLE_ROW)
/**
 * @brief get vertex row from table
 * @param GRIN_VERTEX_PROPERTY_TABLE vertex property table
 * @param GRIN_VERTEX the vertex which is the row index
 * @param GRIN_VERTEX_PROPERTY_LIST the vertex property list as columns
 */
GRIN_ROW grin_get_row_from_vertex_property_table(GRIN_GRAPH, GRIN_VERTEX_PROPERTY_TABLE, GRIN_VERTEX, GRIN_VERTEX_PROPERTY_LIST);
#endif

#if !defined(GRIN_ASSUME_COLUMN_STORE_FOR_VERTEX_PROPERTY) && defined(GRIN_ENABLE_ROW)
/**
 * @brief get vertex row directly from the graph, this API only works for row store system
 * @param GRIN_GRAPH the graph
 * @param GRIN_VERTEX the vertex which is the row index
 * @param GRIN_VERTEX_PROPERTY_LIST the vertex property list as columns
 */
GRIN_ROW grin_get_vertex_row(GRIN_GRAPH, GRIN_VERTEX, GRIN_VERTEX_PROPERTY_LIST);
#endif

#ifdef GRIN_ENABLE_EDGE_PROPERTY_TABLE
/**
 * @brief destroy edge property table
 * @param GRIN_EDGE_PROPERTY_TABLE edge property table
 */
void grin_destroy_edge_property_table(GRIN_GRAPH, GRIN_EDGE_PROPERTY_TABLE);

/**
 * @brief get the edge property table of a certain edge type
 * No matter column or row store strategy is used in the storage,
 * GRIN recommends to first get the property table of the edge type,
 * and then fetch values(rows) by edge and property(list). However,
 * GRIN does provide direct row fetching API when GRIN_ASSUME_COLUMN_STORE_FOR_EDGE_PROPERTY
 * is NOT set.
 * @param GRIN_GRAPH the graph
 * @param GRIN_EDGE_TYPE the edge type
 */
GRIN_EDGE_PROPERTY_TABLE grin_get_edge_property_table_by_type(GRIN_GRAPH, GRIN_EDGE_TYPE);

int grin_get_int32_from_edge_property_table(GRIN_GRAPH, GRIN_EDGE_PROPERTY_TABLE, GRIN_EDGE, GRIN_EDGE_PROPERTY);

unsigned int grin_get_uint32_from_edge_property_table(GRIN_GRAPH, GRIN_EDGE_PROPERTY_TABLE, GRIN_EDGE, GRIN_EDGE_PROPERTY);

long long int grin_get_int64_from_edge_property_table(GRIN_GRAPH, GRIN_EDGE_PROPERTY_TABLE, GRIN_EDGE, GRIN_EDGE_PROPERTY);

unsigned long long int grin_get_uint64_from_edge_property_table(GRIN_GRAPH, GRIN_EDGE_PROPERTY_TABLE, GRIN_EDGE, GRIN_EDGE_PROPERTY);

float grin_get_float_from_edge_property_table(GRIN_GRAPH, GRIN_EDGE_PROPERTY_TABLE, GRIN_EDGE, GRIN_EDGE_PROPERTY);

double grin_get_double_from_edge_property_table(GRIN_GRAPH, GRIN_EDGE_PROPERTY_TABLE, GRIN_EDGE, GRIN_EDGE_PROPERTY);

const char* grin_get_string_from_edge_property_table(GRIN_GRAPH, GRIN_EDGE_PROPERTY_TABLE, GRIN_EDGE, GRIN_EDGE_PROPERTY);

int grin_get_date32_from_edge_property_table(GRIN_GRAPH, GRIN_EDGE_PROPERTY_TABLE, GRIN_EDGE, GRIN_EDGE_PROPERTY);

int grin_get_time32_from_edge_property_table(GRIN_GRAPH, GRIN_EDGE_PROPERTY_TABLE, GRIN_EDGE, GRIN_EDGE_PROPERTY);

long long int grin_get_timestamp64_from_edge_property_table(GRIN_GRAPH, GRIN_EDGE_PROPERTY_TABLE, GRIN_EDGE, GRIN_EDGE_PROPERTY);
#endif

#if defined(GRIN_ENABLE_EDGE_PROPERTY_TABLE) && defined(GRIN_TRAIT_CONST_VALUE_PTR)
/**
 * @brief get edge property value from table as a const void*, callers don't have to
 * destroy the returned value pointer since they are handled by the storage
 * @param GRIN_EDGE_PROPERTY_TABLE edge property table
 * @param GRIN_EDGE the edge which is the row index
 * @param GRIN_EDGE_PROPERTY the edge property which is the column index
 * @return can be casted to the property data type by the caller
 */
const void* grin_get_value_from_edge_property_table(GRIN_GRAPH, GRIN_EDGE_PROPERTY_TABLE, GRIN_EDGE, GRIN_EDGE_PROPERTY);
#endif

#if defined(GRIN_ENABLE_EDGE_PROPERTY_TABLE) && defined(GRIN_ENABLE_ROW)
/**
 * @brief get edge row from table
 * @param GRIN_EDGE_PROPERTY_TABLE edge property table
 * @param GRIN_EDGE the edge which is the row index
 * @param GRIN_EDGE_PROPERTY_LIST the edge property list as columns
 */
GRIN_ROW grin_get_row_from_edge_property_table(GRIN_GRAPH, GRIN_EDGE_PROPERTY_TABLE, GRIN_EDGE, GRIN_EDGE_PROPERTY_LIST);
#endif

#if !defined(GRIN_ASSUME_COLUMN_STORE_FOR_EDGE_PROPERTY) && defined(GRIN_ENABLE_ROW)
/**
 * @brief get edge row directly from the graph, this API only works for row store system
 * @param GRIN_GRAPH the graph
 * @param GRIN_EDGE the edge which is the row index
 * @param GRIN_EDGE_PROPERTY_LIST the edge property list as columns
 */
GRIN_ROW grin_get_edge_row(GRIN_GRAPH, GRIN_EDGE, GRIN_EDGE_PROPERTY_LIST);
#endif

#endif  // GRIN_INCLUDE_PROPERTY_PROPERTY_TABLE_H_