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
 * @brief get the vertex list by label
 * @param GRIN_GRAPH the graph
 * @param label_name the label name
*/
GRIN_VERTEX_TYPE_LIST grin_get_vertex_types_by_label(GRIN_GRAPH, const char*);
#endif

#ifdef GRIN_WITH_EDGE_LABEL
/**
 * @brief get the edge list by label
 * @param GRIN_GRAPH the graph
 * @param label_name the label name
*/
GRIN_EDGE_TYPE_LIST grin_get_edge_types_by_label(GRIN_GRAPH, const char*);
#endif

#endif // GRIN_INCLUDE_INDEX_LABEL_H_

#ifdef __cplusplus
}
#endif