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
 @file internal_id.h
 @brief Define the internal ID related APIs
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GRIN_INCLUDE_INDEX_EXTERNAL_ID_H_
#define GRIN_INCLUDE_INDEX_EXTERNAL_ID_H_

#ifdef GRIN_ENABLE_VERTEX_EXTERNAL_ID_OF_INT64
/**
 * @brief Get the vertex by external id of int64.
 * @param GRIN_GRAPH The graph
 * @param id The external id of int64
 * @return The vertex
*/
GRIN_VERTEX grin_get_vertex_by_external_id_of_int64(GRIN_GRAPH, long long int id);

/**
 * @brief Get the external id of int64 of a vertex
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX The vertex
 * @return The external id of int64 of the vertex
*/
long long int grin_get_vertex_external_id_of_int64(GRIN_GRAPH, GRIN_VERTEX);
#endif

#ifdef GRIN_ENABLE_VERTEX_EXTERNAL_ID_OF_STRING
/**
 * @brief Get the vertex by external id of string.
 * @param GRIN_GRAPH The graph
 * @param id The external id of string
 * @return The vertex
*/
GRIN_VERTEX grin_get_vertex_by_external_id_of_string(GRIN_GRAPH, const char* id);

/**
 * @brief Get the external id of string of a vertex
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX The vertex
 * @return The external id of string of the vertex
*/
const char* grin_get_vertex_external_id_of_string(GRIN_GRAPH, GRIN_VERTEX);
#endif

#endif // GRIN_INCLUDE_INDEX_EXTERNAL_ID_H_

#ifdef __cplusplus
}
#endif