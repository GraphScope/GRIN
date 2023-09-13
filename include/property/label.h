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

#ifndef GRIN_INCLUDE_PROPERTY_LABEL_H_
#define GRIN_INCLUDE_PROPERTY_LABEL_H_

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

void grin_destroy_label(GRIN_GRAPH, GRIN_LABEL);

void grin_destroy_label_list(GRIN_GRAPH, GRIN_LABEL_LIST);
#endif

#ifdef GRIN_WITH_VERTEX_LABEL
/**
 * @brief get all the labels of a vertex as a label list
 * @param GRIN_GRAPH the graph
 * @param GRIN_VERTEX the vertex
 * @return the label list
*/
GRIN_LABEL_LIST grin_get_label_list_by_vertex(GRIN_GRAPH, GRIN_VERTEX);
#endif

#if defined(GRIN_WITH_VERTEX_LABEL) && defined(GRIN_ENABLE_SCHEMA)
/**
 * @brief get all the vertex types that might have the label
 * @param GRIN_GRAPH the graph
 * @param GRIN_LABEL the label
 * @return the vertex type list
*/
GRIN_VERTEX_TYPE_LIST grin_get_vertex_type_list_by_label(GRIN_GRAPH, GRIN_LABEL);

/**
 * @brief get the candidate label list by vertex type
 * @param GRIN_GRAPH the graph
 * @param GRIN_VERTEX_TYPE the vertex type
 * @return the label list
*/
GRIN_LABEL_LIST grin_get_label_list_by_vertex_type(GRIN_GRAPH, GRIN_VERTEX_TYPE);
#endif


#ifdef GRIN_WITH_EDGE_LABEL
/**
 * @brief get all the labels of an edge as a label list
 * @param GRIN_GRAPH the graph
 * @param GRIN_EDGE the edge
 * @return the label list
*/
GRIN_LABEL_LIST grin_get_label_list_by_edge(GRIN_GRAPH, GRIN_EDGE);
#endif

#if defined(GRIN_WITH_EDGE_LABEL) && defined(GRIN_ENABLE_SCHEMA)
/**
 * @brief get all the edge types that might have the label
 * @param GRIN_GRAPH the graph
 * @param GRIN_LABEL the label
 * @return the edge type list
*/
GRIN_EDGE_TYPE_LIST grin_get_edge_type_list_by_label(GRIN_GRAPH, GRIN_LABEL);

/**
 * @brief get the candidate label list by edge type
 * @param GRIN_GRAPH the graph
 * @param GRIN_EDGE_TYPE the edge type
 * @return the label list
*/
GRIN_LABEL_LIST grin_get_label_list_by_edge_type(GRIN_GRAPH, GRIN_EDGE_TYPE);
#endif

#endif  // GRIN_INCLUDE_PROPERTY_LABEL_H_

#ifdef __cplusplus
}
#endif