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
 @file label.h
 @brief Define the label related APIs
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GRIN_INCLUDE_INDEX_LABEL_H_
#define GRIN_INCLUDE_INDEX_LABEL_H_

#ifdef GRIN_WITH_VERTEX_LABEL
/**
 * @brief get the label list for vertices in the graph
 * @param GRIN_GRAPH the graph
 * @return the label list for vertices
*/
GRIN_LABEL_LIST grin_get_vertex_label_list(GRIN_GRAPH);
#endif

#if defined(GRIN_WITH_VERTEX_LABEL) && !defined(GRIN_ENABLE_SCHEMA)
/**
 * @brief get the vertex list by label
 * @param GRIN_GRAPH the graph
 * @param GRIN_LABEL the label
 * @return the vertex list
*/
GRIN_VERTEX_LIST grin_get_vertex_list_by_label(GRIN_GRAPH, GRIN_LABEL);
#endif

#if defined(GRIN_WITH_VERTEX_LABEL) && defined(GRIN_ENABLE_SCHEMA)
/**
 * @brief get the vertex list by type and label
 * @param GRIN_GRAPH the graph
 * @param GRIN_VERTEX_TYPE the vertex type
 * @param GRIN_LABEL the label
 * @return the vertex list
*/
GRIN_VERTEX_LIST grin_get_vertex_list_by_type_by_label(GRIN_GRAPH, GRIN_VERTEX_TYPE, GRIN_LABEL);
#endif


#ifdef GRIN_WITH_EDGE_LABEL
/**
 * @brief get the label list for edges in the graph
 * @param GRIN_GRAPH the graph
 * @return the label list for edges
*/
GRIN_LABEL_LIST grin_get_edge_label_list(GRIN_GRAPH);
#endif

#if defined(GRIN_WITH_EDGE_LABEL) && !defined(GRIN_ENABLE_SCHEMA)
/**
 * @brief get the edge list by label
 * @param GRIN_GRAPH the graph
 * @param GRIN_LABEL the label
 * @return the edge list
*/
GRIN_EDGE_LIST grin_get_edge_list_by_label(GRIN_GRAPH, GRIN_LABEL);
#endif

#if defined(GRIN_WITH_EDGE_LABEL) && defined(GRIN_ENABLE_SCHEMA)
/**
 * @brief get the edge list by type and label
 * @param GRIN_GRAPH the graph
 * @param GRIN_EDGE_TYPE the edge type
 * @param GRIN_LABEL the label
 * @return the edge list
*/
GRIN_EDGE_LIST grin_get_edge_list_by_type_by_label(GRIN_GRAPH, GRIN_EDGE_TYPE, GRIN_LABEL);
#endif

#endif // GRIN_INCLUDE_INDEX_LABEL_H_

#ifdef __cplusplus
}
#endif