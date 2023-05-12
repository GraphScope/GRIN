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

#ifndef GRIN_INCLUDE_TOPOLOGY_STRUCTURE_H_
#define GRIN_INCLUDE_TOPOLOGY_STRUCTURE_H_

#include "../../predefine.h"

GRIN_GRAPH grin_get_graph_from_storage(int, char**);

void grin_destroy_graph(GRIN_GRAPH);

// Graph
#if defined(GRIN_ASSUME_HAS_DIRECTED_GRAPH) && defined(GRIN_ASSUME_HAS_UNDIRECTED_GRAPH)
bool grin_is_directed(GRIN_GRAPH);
#endif

#ifdef GRIN_ASSUME_HAS_MULTI_EDGE_GRAPH
bool grin_is_multigraph(GRIN_GRAPH);
#endif

size_t grin_get_vertex_num(GRIN_GRAPH);

size_t grin_get_edge_num(GRIN_GRAPH);


// Vertex
void grin_destroy_vertex(GRIN_GRAPH, GRIN_VERTEX);

bool grin_equal_vertex(GRIN_GRAPH, GRIN_VERTEX, GRIN_VERTEX);

// Data
#ifdef GRIN_WITH_VERTEX_DATA
GRIN_DATATYPE grin_get_vertex_data_datatype(GRIN_GRAPH, GRIN_VERTEX);

const void* grin_get_vertex_data_value(GRIN_GRAPH, GRIN_VERTEX);
#endif

// Edge
void grin_destroy_edge(GRIN_GRAPH, GRIN_EDGE);

GRIN_VERTEX grin_get_src_vertex_from_edge(GRIN_GRAPH, GRIN_EDGE);

GRIN_VERTEX grin_get_dst_vertex_from_edge(GRIN_GRAPH, GRIN_EDGE);

#ifdef GRIN_WITH_EDGE_DATA
GRIN_DATATYPE grin_get_edge_data_datatype(GRIN_GRAPH, GRIN_EDGE);

const void* grin_get_edge_data_value(GRIN_GRAPH, GRIN_EDGE);
#endif

#endif  // GRIN_INCLUDE_TOPOLOGY_STRUCTURE_H_
