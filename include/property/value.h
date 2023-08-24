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
 @file value.h
 @brief Define the property value related APIs
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GRIN_INCLUDE_PROPERTY_VALUE_H_
#define GRIN_INCLUDE_PROPERTY_VALUE_H_


#ifdef GRIN_WITH_VERTEX_PROPERTY
void grin_destroy_vertex_property_value_of_string(GRIN_GRAPH, const char*);

void grin_destroy_vertex_property_value_of_float_array(GRIN_GRAPH, const float*, size_t);

/**
 * @brief Get the value of int32, given a vertex and a vertex property.
 * The user should make sure the vertex property is of datatype int32.
 * The return int has no predefined invalid value.
 * User should use ``grin_get_last_error_code()`` to check if the API call
 * is successful.
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX The vertex
 * @param GRIN_VERTEX_PROPERTY The vertex property
 * @return The value of the property
*/
int grin_get_vertex_property_value_of_int32(GRIN_GRAPH, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

/**
 * @brief Get the value of uint32, given a vertex and a vertex property.
 * The user should make sure the vertex property is of datatype uint32.
 * The return int has no predefined invalid value.
 * User should use ``grin_get_last_error_code()`` to check if the API call
 * is successful.
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX The vertex
 * @param GRIN_VERTEX_PROPERTY The vertex property
 * @return The value of the property
*/
unsigned int grin_get_vertex_property_value_of_uint32(GRIN_GRAPH, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

/**
 * @brief Get the value of int64, given a vertex and a vertex property.
 * The user should make sure the vertex property is of datatype int64.
 * The return int has no predefined invalid value.
 * User should use ``grin_get_last_error_code()`` to check if the API call
 * is successful.
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX The vertex
 * @param GRIN_VERTEX_PROPERTY The vertex property
 * @return The value of the property
*/
long long int grin_get_vertex_property_value_of_int64(GRIN_GRAPH, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

/**
 * @brief Get the value of uint64, given a vertex and a vertex property.
 * The user should make sure the vertex property is of datatype uint64.
 * The return int has no predefined invalid value.
 * User should use ``grin_get_last_error_code()`` to check if the API call
 * is successful.
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX The vertex
 * @param GRIN_VERTEX_PROPERTY The vertex property
 * @return The value of the property
*/
unsigned long long int grin_get_vertex_property_value_of_uint64(GRIN_GRAPH, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

/**
 * @brief Get the value of float, given a vertex and a vertex property.
 * The user should make sure the vertex property is of datatype float.
 * The return int has no predefined invalid value.
 * User should use ``grin_get_last_error_code()`` to check if the API call
 * is successful.
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX The vertex
 * @param GRIN_VERTEX_PROPERTY The vertex property
 * @return The value of the property
*/
float grin_get_vertex_property_value_of_float(GRIN_GRAPH, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

/**
 * @brief Get the value of double, given a vertex and a vertex property.
 * The user should make sure the vertex property is of datatype double.
 * The return int has no predefined invalid value.
 * User should use ``grin_get_last_error_code()`` to check if the API call
 * is successful.
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX The vertex
 * @param GRIN_VERTEX_PROPERTY The vertex property
 * @return The value of the property
*/
double grin_get_vertex_property_value_of_double(GRIN_GRAPH, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

/**
 * @brief Get the value of string, given a vertex and a vertex property.
 * The user should make sure the vertex property is of datatype string.
 * The return int has no predefined invalid value.
 * User should use ``grin_get_last_error_code()`` to check if the API call
 * is successful.
 * Note that the returned string should be explicitly freed by the user, 
 * by calling API ``grin_destroy_vertex_property_value_of_string``.
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX The vertex
 * @param GRIN_VERTEX_PROPERTY The vertex property
 * @return The value of the property
*/
const char* grin_get_vertex_property_value_of_string(GRIN_GRAPH, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

/**
 * @brief Get the value of int32, given a vertex and a vertex property.
 * The user should make sure the vertex property is of datatype date32.
 * The return int has no predefined invalid value.
 * User should use ``grin_get_last_error_code()`` to check if the API call
 * is successful.
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX The vertex
 * @param GRIN_VERTEX_PROPERTY The vertex property
 * @return The value of the property
*/
int grin_get_vertex_property_value_of_date32(GRIN_GRAPH, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

/**
 * @brief Get the value of int32, given a vertex and a vertex property.
 * The user should make sure the vertex property is of datatype time32.
 * The return int has no predefined invalid value.
 * User should use ``grin_get_last_error_code()`` to check if the API call
 * is successful.
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX The vertex
 * @param GRIN_VERTEX_PROPERTY The vertex property
 * @return The value of the property
*/
int grin_get_vertex_property_value_of_time32(GRIN_GRAPH, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

/**
 * @brief Get the value of int64, given a vertex and a vertex property.
 * The user should make sure the vertex property is of datatype timestamp64.
 * The return int has no predefined invalid value.
 * User should use ``grin_get_last_error_code()`` to check if the API call
 * is successful.
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX The vertex
 * @param GRIN_VERTEX_PROPERTY The vertex property
 * @return The value of the property
*/
long long int grin_get_vertex_property_value_of_timestamp64(GRIN_GRAPH, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

/**
 * @brief Get the vertex value of a float array as a float pointer.
 * The user should make sure the vertex property is of datatype float array.
 * The return is NULL if the value is invalid.
 * Note that the returned float pointer should be explicitly freed by the user,
 * by calling API ``grin_destroy_float_array_value``.
*/
const float* grin_get_vertex_property_value_of_float_array(GRIN_GRAPH, GRIN_VERTEX, GRIN_VERTEX_PROPERTY, size_t*);
#endif

#if defined(GRIN_WITH_VERTEX_PROPERTY) && defined(GRIN_TRAIT_CONST_VALUE_PTR)
const void* grin_get_vertex_property_value(GRIN_GRAPH, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);
#endif


#ifdef GRIN_WITH_EDGE_PROPERTY
void grin_destroy_edge_property_value_of_string(GRIN_GRAPH, const char*);

void grin_destroy_edge_property_value_of_float_array(GRIN_GRAPH, const float*, size_t);

GRIN_DATATYPE grin_get_edge_property_datatype(GRIN_GRAPH, GRIN_EDGE_PROPERTY);

int grin_get_edge_property_value_of_int32(GRIN_GRAPH, GRIN_EDGE, GRIN_EDGE_PROPERTY);

unsigned int grin_get_edge_property_value_of_uint32(GRIN_GRAPH, GRIN_EDGE, GRIN_EDGE_PROPERTY);

long long int grin_get_edge_property_value_of_int64(GRIN_GRAPH, GRIN_EDGE, GRIN_EDGE_PROPERTY);

unsigned long long int grin_get_edge_property_value_of_uint64(GRIN_GRAPH, GRIN_EDGE, GRIN_EDGE_PROPERTY);

float grin_get_edge_property_value_of_float(GRIN_GRAPH, GRIN_EDGE, GRIN_EDGE_PROPERTY);

double grin_get_edge_property_value_of_double(GRIN_GRAPH, GRIN_EDGE, GRIN_EDGE_PROPERTY);

const char* grin_get_edge_property_value_of_string(GRIN_GRAPH, GRIN_EDGE, GRIN_EDGE_PROPERTY);

int grin_get_edge_property_value_of_date32(GRIN_GRAPH, GRIN_EDGE, GRIN_EDGE_PROPERTY);

int grin_get_edge_property_value_of_time32(GRIN_GRAPH, GRIN_EDGE, GRIN_EDGE_PROPERTY);

long long int grin_get_edge_property_value_of_timestamp64(GRIN_GRAPH, GRIN_EDGE, GRIN_EDGE_PROPERTY);

const float* grin_get_edge_property_value_of_float_array(GRIN_GRAPH, GRIN_EDGE, GRIN_EDGE_PROPERTY, size_t*);
#endif

#if defined(GRIN_WITH_EDGE_PROPERTY) && defined(GRIN_TRAIT_CONST_VALUE_PTR)
const void* grin_get_edge_property_value(GRIN_GRAPH, GRIN_EDGE, GRIN_EDGE_PROPERTY);
#endif

#endif  // GRIN_INCLUDE_PROPERTY_VALUE_H_

#ifdef __cplusplus
}
#endif