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

#if defined(GRIN_WITH_VERTEX_LABEL) || defined(GRIN_WITH_EDGE_LABEL)
/**
 * @brief get label list size
 * @param GRIN_GRAPH the graph
 * @param GRIN_LABEL_LIST the label list
 * @return the label list size
*/
size_t grin_get_label_list_size(GRIN_GRAPH, GRIN_LABEL_LIST);

/**
 * @brief get the label from the label list by index
 * @param GRIN_GRAPH the graph
 * @param GRIN_LABEL_LIST the label list
 * @param index the index
*/
GRIN_LABEL grin_get_label_from_list(GRIN_GRAPH, GRIN_LABEL_LIST, size_t);

/** 
 * @brief get the label by name
 * @param GRIN_GRAPH the graph
 * @param label_name the label name
 * @return the label
*/
GRIN_LABEL grin_get_label_by_name(GRIN_GRAPH, const char*);

/**
 * @brief get the label name
 * @param GRIN_GRAPH the graph
 * @param GRIN_LABEL the label
 * @return the label name
*/
const char* grin_get_label_name(GRIN_GRAPH, GRIN_LABEL);
#endif

#ifdef GRIN_WITH_VERTEX_LABEL
/**
 * @brief get the label list for vertices in the graph
 * @param GRIN_GRAPH the graph
 * @return the label list for vertices
*/
GRIN_LABEL_LIST grin_get_vertex_label_list(GRIN_GRAPH);

/**
 * @brief get all the labels of a vertex as a label list
 * @param GRIN_GRAPH the graph
 * @param GRIN_VERTEX the vertex
 * @return the label list
*/
GRIN_LABEL_LIST grin_get_label_list_by_vertex(GRIN_GRAPH, GRIN_VERTEX);
#endif

#if defined(GRIN_WITH_VERTEX_LABEL) && !defined(GRIN_WITH_VERTEX_PROPERTY)
/**
 * @brief get the vertex list by label
 * @param GRIN_GRAPH the graph
 * @param GRIN_LABEL the label
 * @return the vertex list
*/
GRIN_VERTEX_LIST grin_get_vertex_list_by_label(GRIN_GRAPH, GRIN_LABEL);
#endif

#if defined(GRIN_WITH_VERTEX_LABEL) && defined(GRIN_WITH_VERTEX_PROPERTY)
/**
 * @brief get the vertex list by label
 * @param GRIN_GRAPH the graph
 * @param GRIN_VERTEX_TYPE the vertex type
 * @param GRIN_LABEL the label
 * @return the vertex list
*/
GRIN_VERTEX_LIST grin_get_vertex_list_by_type_by_label(GRIN_GRAPH, GRIN_VERTEX_TYPE, GRIN_LABEL);

/**
 * @brief get all the vertex types that might have the label
 * @param GRIN_GRAPH the graph
 * @param GRIN_LABEL the label
 * @return the vertex type list
*/
GRIN_VERTEX_TYPE_LIST grin_get_vertex_types_by_label(GRIN_GRAPH, GRIN_LABEL);
#endif


#ifdef GRIN_WITH_EDGE_LABEL
/**
 * @brief get the label list for edges in the graph
 * @param GRIN_GRAPH the graph
 * @return the label list for edges
*/
GRIN_LABEL_LIST grin_get_edge_label_list(GRIN_GRAPH);

/**
 * @brief get all the labels of an edge as a label list
 * @param GRIN_GRAPH the graph
 * @param GRIN_EDGE the edge
 * @return the label list
*/
GRIN_LABEL_LIST grin_get_label_list_by_edge(GRIN_GRAPH, GRIN_EDGE);
#endif

#if defined(GRIN_WITH_EDGE_LABEL) && !defined(GRIN_WITH_EDGE_PROPERTY)
/**
 * @brief get the edge list by label
 * @param GRIN_GRAPH the graph
 * @param GRIN_LABEL the label
 * @return the edge list
*/
GRIN_EDGE_LIST grin_get_edge_list_by_label(GRIN_GRAPH, GRIN_LABEL);
#endif

#if defined(GRIN_WITH_EDGE_LABEL) && defined(GRIN_WITH_EDGE_PROPERTY)
/**
 * @brief get the edge list by label
 * @param GRIN_GRAPH the graph
 * @param GRIN_EDGE_TYPE the edge type
 * @param GRIN_LABEL the label
 * @return the edge list
*/
GRIN_EDGE_LIST grin_get_edge_list_by_type_by_label(GRIN_GRAPH, GRIN_EDGE_TYPE, GRIN_LABEL);

/**
 * @brief get all the edge types that might have the label
 * @param GRIN_GRAPH the graph
 * @param GRIN_LABEL the label
 * @return the edge type list
*/
GRIN_EDGE_TYPE_LIST grin_get_edge_types_by_label(GRIN_GRAPH, GRIN_LABEL);
#endif

#endif // GRIN_INCLUDE_INDEX_LABEL_H_

#ifdef __cplusplus
}
#endif