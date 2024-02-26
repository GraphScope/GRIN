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

#include "src/predefine.h"
// GRIN headers
#include "partition/topology.h"

#if defined(GRIN_TRAIT_SELECT_MASTER_FOR_VERTEX_LIST) && \
    !defined(GRIN_ENABLE_SCHEMA)
GRIN_VERTEX_LIST grin_get_vertex_list_select_master(GRIN_GRAPH);

GRIN_VERTEX_LIST grin_get_vertex_list_select_mirror(GRIN_GRAPH);
#endif

#if defined(GRIN_TRAIT_SELECT_MASTER_FOR_VERTEX_LIST) && \
    defined(GRIN_ENABLE_SCHEMA)
GRIN_VERTEX_LIST grin_get_vertex_list_by_type_select_master(
    GRIN_GRAPH g, GRIN_VERTEX_TYPE vtype) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  return new GRIN_VERTEX_LIST_T(vtype, ONE_PARTITION, _g->GetPartitionId());
}

GRIN_VERTEX_LIST grin_get_vertex_list_by_type_select_mirror(
    GRIN_GRAPH g, GRIN_VERTEX_TYPE vtype) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  return new GRIN_VERTEX_LIST_T(vtype, ALL_BUT_ONE_PARTITION,
                                _g->GetPartitionId());
}
#endif

#if defined(GRIN_TRAIT_SELECT_PARTITION_FOR_VERTEX_LIST) && \
    !defined(GRIN_WITH_VERTEX_PROPERTY)
GRIN_VERTEX_LIST grin_get_vertex_list_select_partition(GRIN_GRAPH,
                                                       GRIN_PARTITION);
#endif

#if defined(GRIN_TRAIT_SELECT_PARTITION_FOR_VERTEX_LIST) && \
    defined(GRIN_ENABLE_SCHEMA)
GRIN_VERTEX_LIST grin_get_vertex_list_by_type_select_partition(
    GRIN_GRAPH g, GRIN_VERTEX_TYPE vtype, GRIN_PARTITION p) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  if (p >= _g->GetPartitionNum()) {
    return GRIN_NULL_VERTEX_LIST;
  }
  return new GRIN_VERTEX_LIST_T(vtype, ONE_PARTITION, p);
}
#endif

#if defined(GRIN_TRAIT_SELECT_MASTER_FOR_EDGE_LIST) && \
    !defined(GRIN_ENABLE_SCHEMA)
GRIN_EDGE_LIST grin_get_edge_list_select_master(GRIN_GRAPH);

GRIN_EDGE_LIST grin_get_edge_list_select_mirror(GRIN_GRAPH);
#endif

#if defined(GRIN_TRAIT_SELECT_MASTER_FOR_EDGE_LIST) && \
    defined(GRIN_ENABLE_SCHEMA)
GRIN_EDGE_LIST grin_get_edge_list_by_type_select_master(GRIN_GRAPH g,
                                                        GRIN_EDGE_TYPE etype) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  return new GRIN_EDGE_LIST_T(etype, ONE_PARTITION, _g->GetPartitionId());
}

GRIN_EDGE_LIST grin_get_edge_list_by_type_select_mirror(GRIN_GRAPH g,
                                                        GRIN_EDGE_TYPE etype) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  return new GRIN_EDGE_LIST_T(etype, ALL_BUT_ONE_PARTITION,
                              _g->GetPartitionId());
}
#endif

#if defined(GRIN_TRAIT_SELECT_PARTITION_FOR_EDGE_LIST) && \
    !defined(GRIN_ENABLE_SCHEMA)
GRIN_EDGE_LIST grin_get_edge_list_select_partition(GRIN_GRAPH, GRIN_PARTITION);
#endif

#if defined(GRIN_TRAIT_SELECT_PARTITION_FOR_EDGE_LIST) && \
    defined(GRIN_ENABLE_SCHEMA)
GRIN_EDGE_LIST grin_get_edge_list_by_type_select_partition(GRIN_GRAPH g,
                                                           GRIN_EDGE_TYPE etype,
                                                           GRIN_PARTITION p) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  if (p >= _g->GetPartitionNum()) {
    return GRIN_NULL_EDGE_LIST;
  }
  return new GRIN_EDGE_LIST_T(etype, ONE_PARTITION, p);
}
#endif

#if defined(GRIN_TRAIT_SELECT_MASTER_NEIGHBOR_FOR_ADJACENT_LIST) && \
    !defined(GRIN_ENABLE_SCHEMA)
GRIN_ADJACENT_LIST grin_get_adjacent_list_select_master_neighbor(GRIN_GRAPH,
                                                                 GRIN_DIRECTION,
                                                                 GRIN_VERTEX);

GRIN_ADJACENT_LIST grin_get_adjacent_list_select_mirror_neighbor(GRIN_GRAPH,
                                                                 GRIN_DIRECTION,
                                                                 GRIN_VERTEX);
#endif

#if defined(GRIN_TRAIT_SELECT_MASTER_NEIGHBOR_FOR_ADJACENT_LIST) && \
    defined(GRIN_ENABLE_SCHEMA)
GRIN_ADJACENT_LIST grin_get_adjacent_list_by_edge_type_select_master_neighbor(
    GRIN_GRAPH g, GRIN_DIRECTION d, GRIN_VERTEX v, GRIN_EDGE_TYPE etype) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto vtype = DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(v);
  auto vid = DEMO_STORAGE_NAMESPACE::get_id_from_gid(v);
  return new GRIN_ADJACENT_LIST_T(vtype, vid, d, etype, ONE_PARTITION,
                                  _g->GetPartitionId());
}

GRIN_ADJACENT_LIST grin_get_adjacent_list_by_edge_type_select_mirror_neighbor(
    GRIN_GRAPH g, GRIN_DIRECTION d, GRIN_VERTEX v, GRIN_EDGE_TYPE etype) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto vtype = DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(v);
  auto vid = DEMO_STORAGE_NAMESPACE::get_id_from_gid(v);
  return new GRIN_ADJACENT_LIST_T(vtype, vid, d, etype, ALL_BUT_ONE_PARTITION,
                                  _g->GetPartitionId());
}
#endif

#if defined(GRIN_TRAIT_SELECT_NEIGHBOR_PARTITION_FOR_ADJACENT_LIST) && \
    !defined(GRIN_WITH_VERTEX_PROPERTY)
GRIN_ADJACENT_LIST grin_get_adjacent_list_select_partition_neighbor(
    GRIN_GRAPH, GRIN_DIRECTION, GRIN_VERTEX, GRIN_PARTITION);
#endif

#if defined(GRIN_TRAIT_SELECT_NEIGHBOR_PARTITION_FOR_ADJACENT_LIST) && \
    defined(GRIN_ENABLE_SCHEMA)
GRIN_ADJACENT_LIST
grin_get_adjacent_list_by_edge_type_select_partition_neighbor(
    GRIN_GRAPH g, GRIN_DIRECTION d, GRIN_VERTEX v, GRIN_EDGE_TYPE etype,
    GRIN_PARTITION p) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  if (p >= _g->GetPartitionNum()) {
    return GRIN_NULL_ADJACENT_LIST;
  }
  auto vtype = DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(v);
  auto vid = DEMO_STORAGE_NAMESPACE::get_id_from_gid(v);
  return new GRIN_ADJACENT_LIST_T(vtype, vid, d, etype, ONE_PARTITION, p);
}
#endif

#if defined(GRIN_ASSUME_WITH_UNIVERSAL_VERTICES) && defined(GRIN_ENABLE_SCHEMA)
GRIN_VERTEX_TYPE_LIST grin_get_vertex_type_list_select_universal(GRIN_GRAPH);

GRIN_VERTEX_TYPE_LIST grin_get_vertex_type_list_select_non_universal(
    GRIN_GRAPH);

bool grin_is_vertex_type_unisversal(GRIN_GRAPH, GRIN_VERTEX_TYPE);
#endif

#if defined(GRIN_ASSUME_WITH_UNIVERSAL_VERTICES) && \
    !defined(GRIN_ENABLE_SCHEMA) && defined(GRIN_ENABLE_VERTEX_LIST)
GRIN_VERTEX_LIST grin_get_vertex_list_select_universal(GRIN_GRAPH);

GRIN_VERTEX_LIST grin_get_vertex_list_select_non_universal(GRIN_GRAPH);
#endif

#if defined(GRIN_ASSUME_WITH_UNIVERSAL_VERTICES) && \
    !defined(GRIN_ENABLE_SCHEMA) && defined(GRIN_ENABLE_EDGE_LIST)
GRIN_EDGE_LIST grin_get_edge_list_select_universal(GRIN_GRAPH);

GRIN_EDGE_LIST grin_get_edge_list_select_non_universal(GRIN_GRAPH);
#endif

#if defined(GRIN_ASSUME_WITH_UNIVERSAL_VERTICES) && \
    !defined(GRIN_ENABLE_SCHEMA) && defined(GRIN_ENABLE_ADJACENT_LIST)
GRIN_ADJACENT_LIST grin_get_adjacent_list_select_universal_neighbor(
    GRIN_GRAPH, GRIN_DIRECTION, GRIN_VERTEX);

GRIN_ADJACENT_LIST grin_get_adjacent_list_select_non_universal_neighbor(
    GRIN_GRAPH, GRIN_DIRECTION, GRIN_VERTEX);
#endif
