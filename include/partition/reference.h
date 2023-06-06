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
 @file reference.h
 @brief Define the reference related APIs
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GRIN_INCLUDE_PARTITION_REFERENCE_H_
#define GRIN_INCLUDE_PARTITION_REFERENCE_H_


// Vertex ref refers to the same vertex referred in other partitions,
// while edge ref is likewise. Both can be serialized to const char* for
// message transporting and deserialized on the other end.
#ifdef GRIN_ENABLE_VERTEX_REF
GRIN_VERTEX_REF grin_get_vertex_ref_by_vertex(GRIN_GRAPH, GRIN_VERTEX);

void grin_destroy_vertex_ref(GRIN_GRAPH, GRIN_VERTEX_REF);

/**
 * @brief get the local vertex from the vertex ref
 * if the vertex ref is not regconized, a null vertex is returned
 * @param GRIN_GRAPH the graph
 * @param GRIN_VERTEX_REF the vertex ref
 */
GRIN_VERTEX grin_get_vertex_from_vertex_ref(GRIN_GRAPH, GRIN_VERTEX_REF);

/**
 * @brief get the master partition of a vertex ref.
 * Some storage can still provide the master partition of the vertex ref,
 * even if the vertex ref can NOT be recognized locally.
 * @param GRIN_GRAPH the graph
 * @param GRIN_VERTEX_REF the vertex ref
 */
GRIN_PARTITION grin_get_master_partition_from_vertex_ref(GRIN_GRAPH, GRIN_VERTEX_REF);

const char* grin_serialize_vertex_ref(GRIN_GRAPH, GRIN_VERTEX_REF);

void grin_destroy_serialized_vertex_ref(GRIN_GRAPH, const char*);

GRIN_VERTEX_REF grin_deserialize_to_vertex_ref(GRIN_GRAPH, const char*);

bool grin_is_master_vertex(GRIN_GRAPH, GRIN_VERTEX);

bool grin_is_mirror_vertex(GRIN_GRAPH, GRIN_VERTEX);
#endif

#ifdef GRIN_TRAIT_FAST_VERTEX_REF
long long int grin_serialize_vertex_ref_as_int64(GRIN_GRAPH, GRIN_VERTEX_REF);

GRIN_VERTEX_REF grin_deserialize_int64_to_vertex_ref(GRIN_GRAPH, long long int);
#endif

#ifdef GRIN_TRAIT_MASTER_VERTEX_MIRROR_PARTITION_LIST
GRIN_PARTITION_LIST grin_get_master_vertex_mirror_partition_list(GRIN_GRAPH, GRIN_VERTEX);
#endif

#ifdef GRIN_TRAIT_MIRROR_VERTEX_MIRROR_PARTITION_LIST
GRIN_PARTITION_LIST grin_get_mirror_vertex_mirror_partition_list(GRIN_GRAPH, GRIN_VERTEX);
#endif

#ifdef GRIN_ENABLE_EDGE_REF
GRIN_EDGE_REF grin_get_edge_ref_by_edge(GRIN_GRAPH, GRIN_EDGE);

void grin_destroy_edge_ref(GRIN_GRAPH, GRIN_EDGE_REF);

GRIN_EDGE grin_get_edge_from_edge_ref(GRIN_GRAPH, GRIN_EDGE_REF);

GRIN_PARTITION grin_get_master_partition_from_edge_ref(GRIN_GRAPH, GRIN_EDGE_REF);

const char* grin_serialize_edge_ref(GRIN_GRAPH, GRIN_EDGE_REF);

void grin_destroy_serialized_edge_ref(GRIN_GRAPH, GRIN_EDGE_REF);

GRIN_EDGE_REF grin_deserialize_to_edge_ref(GRIN_GRAPH, const char*);

bool grin_is_master_edge(GRIN_GRAPH, GRIN_EDGE);

bool grin_is_mirror_edge(GRIN_GRAPH, GRIN_EDGE);
#endif

#ifdef GRIN_TRAIT_MASTER_EDGE_MIRROR_PARTITION_LIST
GRIN_PARTITION_LIST grin_get_master_edge_mirror_partition_list(GRIN_GRAPH, GRIN_EDGE);
#endif

#ifdef GRIN_TRAIT_MIRROR_EDGE_MIRROR_PARTITION_LIST
GRIN_PARTITION_LIST grin_get_mirror_edge_mirror_partition_list(GRIN_GRAPH, GRIN_EDGE);
#endif

#endif  // GRIN_INCLUDE_PARTITION_REFERENCE_H_

#ifdef __cplusplus
}
#endif
