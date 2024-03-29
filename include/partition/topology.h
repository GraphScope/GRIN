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

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GRIN_INCLUDE_PARTITION_TOPOLOGY_H_
#define GRIN_INCLUDE_PARTITION_TOPOLOGY_H_

#include "common/enum_types.h"

#if defined(GRIN_TRAIT_SELECT_MASTER_FOR_VERTEX_LIST) && !defined(GRIN_ENABLE_SCHEMA)
/**
 * @brief Get the vertex list of the graph with master vertices only.
 * This API is only available when schema is not enabled.
 * @param GRIN_GRAPH The graph.
 * @return The vertex list of master vertices only.
*/
GRIN_VERTEX_LIST grin_get_vertex_list_select_master(GRIN_GRAPH);

/**
 * @brief Get the vertex list of the graph with mirror vertices only.
 * This API is only available when schema is not enabled.
 * @param GRIN_GRAPH The graph.
 * @return The vertex list of mirror vertices only.
*/
GRIN_VERTEX_LIST grin_get_vertex_list_select_mirror(GRIN_GRAPH);
#endif

#if defined(GRIN_TRAIT_SELECT_MASTER_FOR_VERTEX_LIST) && defined(GRIN_ENABLE_SCHEMA)
/**
 * @brief Get the vertex list of a given type with master vertices only.
 * This API is only available when schema is enabled.
 * @param GRIN_GRAPH The graph.
 * @param GRIN_VERTEX_TYPE The vertex type.
 * @return The vertex list of master vertices only.
*/
GRIN_VERTEX_LIST grin_get_vertex_list_by_type_select_master(GRIN_GRAPH, GRIN_VERTEX_TYPE);

/**
 * @brief Get the vertex list of a given type with mirror vertices only.
 * This API is only available when schema is enabled.
 * @param GRIN_GRAPH The graph.
 * @param GRIN_VERTEX_TYPE The vertex type.
 * @return The vertex list of mirror vertices only.
*/
GRIN_VERTEX_LIST grin_get_vertex_list_by_type_select_mirror(GRIN_GRAPH, GRIN_VERTEX_TYPE);
#endif


#if defined(GRIN_TRAIT_SELECT_PARTITION_FOR_VERTEX_LIST) && !defined(GRIN_ENABLE_SCHEMA)
GRIN_VERTEX_LIST grin_get_vertex_list_select_partition(GRIN_GRAPH, GRIN_PARTITION);
#endif

#if defined(GRIN_TRAIT_SELECT_PARTITION_FOR_VERTEX_LIST) && defined(GRIN_ENABLE_SCHEMA)
GRIN_VERTEX_LIST grin_get_vertex_list_by_type_select_partition(GRIN_GRAPH, GRIN_VERTEX_TYPE, GRIN_PARTITION);
#endif


#if defined(GRIN_TRAIT_SELECT_MASTER_FOR_EDGE_LIST) && !defined(GRIN_ENABLE_SCHEMA)
GRIN_EDGE_LIST grin_get_edge_list_select_master(GRIN_GRAPH);

GRIN_EDGE_LIST grin_get_edge_list_select_mirror(GRIN_GRAPH);
#endif

#if defined(GRIN_TRAIT_SELECT_MASTER_FOR_EDGE_LIST) && defined(GRIN_ENABLE_SCHEMA)
GRIN_EDGE_LIST grin_get_edge_list_by_type_select_master(GRIN_GRAPH, GRIN_EDGE_TYPE);

GRIN_EDGE_LIST grin_get_edge_list_by_type_select_mirror(GRIN_GRAPH, GRIN_EDGE_TYPE);
#endif


#if defined(GRIN_TRAIT_SELECT_PARTITION_FOR_EDGE_LIST) && !defined(GRIN_ENABLE_SCHEMA)
GRIN_EDGE_LIST grin_get_edge_list_select_partition(GRIN_GRAPH, GRIN_PARTITION);
#endif

#if defined(GRIN_TRAIT_SELECT_PARTITION_FOR_EDGE_LIST) && defined(GRIN_ENABLE_SCHEMA)
GRIN_EDGE_LIST grin_get_edge_list_by_type_select_partition(GRIN_GRAPH, GRIN_EDGE_TYPE, GRIN_PARTITION);
#endif


#if defined(GRIN_TRAIT_SELECT_MASTER_NEIGHBOR_FOR_ADJACENT_LIST) && !defined(GRIN_ENABLE_SCHEMA)
GRIN_ADJACENT_LIST grin_get_adjacent_list_select_master_neighbor(GRIN_GRAPH, GRIN_DIRECTION, GRIN_VERTEX);

GRIN_ADJACENT_LIST grin_get_adjacent_list_select_mirror_neighbor(GRIN_GRAPH, GRIN_DIRECTION, GRIN_VERTEX);
#endif

#if defined(GRIN_TRAIT_SELECT_MASTER_NEIGHBOR_FOR_ADJACENT_LIST) && defined(GRIN_ENABLE_SCHEMA)
GRIN_ADJACENT_LIST grin_get_adjacent_list_by_edge_type_select_master_neighbor(GRIN_GRAPH, GRIN_DIRECTION, GRIN_VERTEX, GRIN_EDGE_TYPE);

GRIN_ADJACENT_LIST grin_get_adjacent_list_by_edge_type_select_mirror_neighbor(GRIN_GRAPH, GRIN_DIRECTION, GRIN_VERTEX, GRIN_EDGE_TYPE);
#endif


#if defined(GRIN_TRAIT_SELECT_NEIGHBOR_PARTITION_FOR_ADJACENT_LIST) && !defined(GRIN_ENABLE_SCHEMA)
GRIN_ADJACENT_LIST grin_get_adjacent_list_select_partition_neighbor(GRIN_GRAPH, GRIN_DIRECTION, GRIN_VERTEX, GRIN_PARTITION);
#endif

#if defined(GRIN_TRAIT_SELECT_NEIGHBOR_PARTITION_FOR_ADJACENT_LIST) && defined(GRIN_ENABLE_SCHEMA)
GRIN_ADJACENT_LIST grin_get_adjacent_list_by_edge_type_select_partition_neighbor(GRIN_GRAPH, GRIN_DIRECTION, GRIN_VERTEX, GRIN_EDGE_TYPE, GRIN_PARTITION);
#endif

// Universal Vertices
#if defined(GRIN_ASSUME_WITH_UNIVERSAL_VERTICES) && defined(GRIN_ENABLE_SCHEMA)
GRIN_VERTEX_TYPE_LIST grin_get_vertex_type_list_select_universal(GRIN_GRAPH);

GRIN_VERTEX_TYPE_LIST grin_get_vertex_type_list_select_non_universal(GRIN_GRAPH);

bool grin_is_vertex_type_unisversal(GRIN_GRAPH, GRIN_VERTEX_TYPE);
#endif

#if defined(GRIN_ASSUME_WITH_UNIVERSAL_VERTICES) && !defined(GRIN_ENABLE_SCHEMA) && defined(GRIN_ENABLE_VERTEX_LIST)
GRIN_VERTEX_LIST grin_get_vertex_list_select_universal(GRIN_GRAPH);

GRIN_VERTEX_LIST grin_get_vertex_list_select_non_universal(GRIN_GRAPH);
#endif

#if defined(GRIN_ASSUME_WITH_UNIVERSAL_VERTICES) && !defined(GRIN_ENABLE_SCHEMA) && defined(GRIN_ENABLE_EDGE_LIST) 
GRIN_EDGE_LIST grin_get_edge_list_select_universal(GRIN_GRAPH);

GRIN_EDGE_LIST grin_get_edge_list_select_non_universal(GRIN_GRAPH);
#endif


#if defined(GRIN_ASSUME_WITH_UNIVERSAL_VERTICES) && !defined(GRIN_ENABLE_SCHEMA) && defined(GRIN_ENABLE_ADJACENT_LIST)
GRIN_ADJACENT_LIST grin_get_adjacent_list_select_universal_neighbor(GRIN_GRAPH, GRIN_DIRECTION, GRIN_VERTEX);

GRIN_ADJACENT_LIST grin_get_adjacent_list_select_non_universal_neighbor(GRIN_GRAPH, GRIN_DIRECTION, GRIN_VERTEX);
#endif


#endif // GRIN_INCLUDE_PARTITION_TOPOLOGY_H_

#ifdef __cplusplus
}
#endif