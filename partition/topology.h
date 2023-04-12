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
 @file partition/topology.h
 @brief Define the topoloy related APIs under partitioned graph
*/

#ifndef GRIN_INCLUDE_PARTITION_TOPOLOGY_H_
#define GRIN_INCLUDE_PARTITION_TOPOLOGY_H_

#include "../../predefine.h"

#ifdef GRIN_ENABLE_GRAPH_PARTITION
size_t grin_get_total_vertex_num(GRIN_PARTITIONED_GRAPH);

size_t grin_get_total_edge_num(GRIN_PARTITIONED_GRAPH);
#endif

#ifdef GRIN_TRAIT_SELECT_MASTER_FOR_VERTEX_LIST
GRIN_VERTEX_LIST grin_select_master_for_vertex_list(GRIN_GRAPH, GRIN_VERTEX_LIST);

GRIN_VERTEX_LIST grin_select_mirror_for_vertex_list(GRIN_GRAPH, GRIN_VERTEX_LIST);
#endif


#ifdef GRIN_TRAIT_SELECT_PARTITION_FOR_VERTEX_LIST
GRIN_VERTEX_LIST grin_select_partition_for_vertex_list(GRIN_GRAPH, GRIN_PARTITION, GRIN_VERTEX_LIST);
#endif



#ifdef GRIN_TRAIT_SELECT_MASTER_FOR_EDGE_LIST
GRIN_EDGE_LIST grin_select_master_for_edge_list(GRIN_GRAPH, GRIN_EDGE_LIST);

GRIN_EDGE_LIST grin_select_mirror_for_edge_list(GRIN_GRAPH, GRIN_EDGE_LIST);
#endif


#ifdef GRIN_TRAIT_SELECT_PARTITION_FOR_EDGE_LIST
GRIN_EDGE_LIST grin_select_partition_for_edge_list(GRIN_GRAPH, GRIN_PARTITION, GRIN_EDGE_LIST);
#endif


#ifdef GRIN_TRAIT_SELECT_MASTER_NEIGHBOR_FOR_ADJACENT_LIST
GRIN_ADJACENT_LIST grin_select_master_neighbor_for_adjacent_list(GRIN_GRAPH, GRIN_ADJACENT_LIST);

GRIN_ADJACENT_LIST grin_select_mirror_neighbor_for_adjacent_list(GRIN_GRAPH, GRIN_ADJACENT_LIST);
#endif

#ifdef GRIN_TRAIT_SELECT_NEIGHBOR_PARTITION_FOR_ADJACENT_LIST
GRIN_ADJACENT_LIST grin_select_neighbor_partition_for_adjacent_list(GRIN_GRAPH, GRIN_ADJACENT_LIST);
#endif


#endif // GRIN_INCLUDE_PARTITION_TOPOLOGY_H_