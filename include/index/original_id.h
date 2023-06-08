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
 @file order.h
 @brief Define the vertex ordering predicate APIs
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GRIN_INCLUDE_INDEX_ORIGINAL_ID_H_
#define GRIN_INCLUDE_INDEX_ORIGINAL_ID_H_

/**
 * @brief Get the datatype of original id of the graph
 * @param GRIN_GRAPH The graph
 * @return The datatype of the original id of the graph
*/
GRIN_DATATYPE grin_get_vertex_original_id_datatype(GRIN_GRAPH);

#ifdef GRIN_ENABLE_VERTEX_ORIGINAL_ID_OF_INT64
/**
 * @brief Get the int64 original id of a vertex
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX The vertex
 * @return The int64 original id of the vertex
*/
long long int grin_get_vertex_original_id_of_int64(GRIN_GRAPH, GRIN_VERTEX);

/**
 * @brief Get the vertex by original id. 
 * Different from pk_of_int64, the original id is unique over all vertex types.
 * @param GRIN_GRAPH The graph
 * @param id The original id of the vertex
 * @return The vertex
*/
GRIN_VERTEX grin_get_vertex_by_original_id_of_int64(GRIN_GRAPH, long long int id);
#endif

#ifdef GRIN_ENABLE_VERTEX_ORIGINAL_ID_OF_STRING
const char* grin_get_vertex_original_id_of_string(GRIN_GRAPH, GRIN_VERTEX);

GRIN_VERTEX grin_get_vertex_by_original_id_of_string(GRIN_GRAPH, const char*);
#endif


#endif // GRIN_INCLUDE_INDEX_ORIGINAL_ID_H_

#ifdef __cplusplus
}
#endif