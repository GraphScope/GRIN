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
 * @file features.h
 * @brief This file lists ALL the pre-defined macros for storage features,
 * and it should NOT be included by users.
 * Users should use the predefine.h of the specific storage.
 * The macros are organized into several sections such as topology,
 * partition, and so on.
 * Storage implementors should Turn-ON (i.e., define) the specific
 * macros in their predefine.h based the features of the storage.
*/

/* Section 1: Toplogy */

/** @name TopologyMacros
 * @brief Macros for basic graph topology features
 */
///@{
/** @ingroup TopologyMacros
 * @brief The storage supports directed graphs.
 */
#define GRIN_ASSUME_HAS_DIRECTED_GRAPH

/** @ingroup TopologyMacros
 * @brief The storage supports undirected graphs.
 */
#define GRIN_ASSUME_HAS_UNDIRECTED_GRAPH

/** @ingroup TopologyMacros
 * @brief The storage supports multiple edges between a pair of vertices.
 */
#define GRIN_ASSUME_HAS_MULTI_EDGE_GRAPH

/** @ingroup TopologyMacros
 * @brief There is data on vertex. E.g., the PageRank value of a vertex.
 */
#define GRIN_WITH_VERTEX_DATA

/** @ingroup TopologyMacros
 * @brief There is data on edge. E.g., the weight of an edge.
*/
#define GRIN_WITH_EDGE_DATA

/** @ingroup TopologyMacros
 * @brief Enable the vertex list structure.
 * It follows the design for Topology Lists.
*/
#define GRIN_ENABLE_VERTEX_LIST

/** @ingroup TopologyMacros
 * @brief Enable the vertex list array-style retrieval.
*/
#define GRIN_ENABLE_VERTEX_LIST_ARRAY

/** @ingroup TopologyMacros
 * @brief Enable the vertex list iterator.
*/
#define GRIN_ENABLE_VERTEX_LIST_ITERATOR

/** @ingroup TopologyMacros
 * @brief Enable the edge list structure. 
 * It follows the design for Topology Lists.
*/
#define GRIN_ENABLE_EDGE_LIST

/** @ingroup TopologyMacros
 * @brief Enable the edge list array-style retrieval.
*/
#define GRIN_ENABLE_EDGE_LIST_ARRAY

/** @ingroup TopologyMacros
 * @brief Enable the edge list iterator.
*/
#define GRIN_ENABLE_EDGE_LIST_ITERATOR

/** @ingroup TopologyMacros
 * @brief Enable the adjacent list structure.
 * It follows the design for Topology Lists.
*/
#define GRIN_ENABLE_ADJACENT_LIST

/** @ingroup TopologyMacros
 * @brief Enable the adjacent list array-style retrieval.
*/
#define GRIN_ENABLE_ADJACENT_LIST_ARRAY

/** @ingroup TopologyMacros
 * @brief Enable the adjacent list iterator.
*/
#define GRIN_ENABLE_ADJACENT_LIST_ITERATOR
///@}

/* End of Section 1 */

/* Section 2. Partition */

/** @name PartitionMacros
 * @brief Macros for partitioned graph features
 */
///@{
/** @ingroup PartitionMacros
 * @brief Enable partitioned graph. A partitioned graph usually contains
 * several fragments (i.e., local graphs) that are distributedly stored
 * in a cluster. In GRIN, GRIN_GRAPH represents to a single fragment that can
 * be locally accessed.
 */
#define GRIN_ENABLE_GRAPH_PARTITION

/** @ingroup PartitionMacros
 * @brief The storage uses edge-cut partition strategy.
*/
#define GRIN_ASSUME_EDGE_CUT_PARTITION

/** @ingroup PartitionMacros
 * @brief The storage uses vertex-cut partition strategy.
*/
#define GRIN_ASSUME_VERTEX_CUT_PARTITION

/** @ingroup PartitionMacros
 * @brief The storage uses edge-cut partition with static vertices.
*/
#define GRIN_ASSUME_WITH_UNIVERSAL_VERTICES

/** @ingroup PartitionMacros
 * @brief The storage provides natural number IDs for partitions.
 * It follows the design of natural number ID trait in GRIN.
*/
#define GRIN_TRAIT_NATURAL_ID_FOR_PARTITION

/** @ingroup PartitionMacros
 * @brief The storage provides reference of vertex that can be
 * recognized in other partitions where the vertex also appears.
*/
#define GRIN_ENABLE_VERTEX_REF

/** @ingroup PartitionMacros
 * @brief The storage provides fast reference of vertex, which means
 * the vertex ref can be serialized into a int64 using 
 * grin_serialize_vertex_ref_as_int64
*/
#define GRIN_TRAIT_FAST_VERTEX_REF

/** @ingroup PartitionMacros
 * @brief The storage provides reference of edge that can be
 * recognized in other partitions where the edge also appears.
*/
#define GRIN_ENABLE_EDGE_REF
///@}

/** @name TraitMirrorPartitionMacros
 * @brief Macros for storage that provides the partition list where the mirror
 * vertices are located. This trait is usually enabled by storages using vertex-cut
 * partition strategy.
*/
///@{
/** @ingroup TraitMirrorPartitionMacros
 * @brief The storage provides the partition list where the mirror
 * vertices are located of a local master vertex.
*/
#define GRIN_TRAIT_MASTER_VERTEX_MIRROR_PARTITION_LIST

/** @ingroup TraitMirrorPartitionMacros
 * @brief The storage provides the partition list where the mirror
 * vertices are located of a local mirror vertex
*/
#define GRIN_TRAIT_MIRROR_VERTEX_MIRROR_PARTITION_LIST

/** @ingroup TraitMirrorPartitionMacros
 * @brief The storage provides the partition list where the mirror
 * edges are located of a local master edge
*/
#define GRIN_TRAIT_MASTER_EDGE_MIRROR_PARTITION_LIST

/** @ingroup TraitMirrorPartitionMacros
 * @brief The storage provides the partition list where the mirror
 * edges are located of a local mirror edge
*/
#define GRIN_TRAIT_MIRROR_EDGE_MIRROR_PARTITION_LIST
///@}

/** @name TraitFilterMacros
 * @brief Macros for storage that provides filtering ability of partitions for 
 * topology lists. This trait is usually enabled for efficient graph traversal.
*/
///@{
/** @ingroup TraitFilterMacros
 * @brief The storage provides master vertex filtering for vertex list.
 * This means suffix ``_select_master`` or ``_select_mirror`` can be added to a
 * ``grin_get_vertex_list`` API to get a master-only or mirror-only vertex list.
 * For example, ``grin_get_vertex_list_by_type_select_mirror`` returns
 * a vertex list of a given type with mirror vertices only.
*/
#define GRIN_TRAIT_SELECT_MASTER_FOR_VERTEX_LIST

/** @ingroup TraitFilterMacros
 * @brief The storage provides per partition vertex filtering for vertex list.
 * The suffix is ``_select_partition``.
*/
#define GRIN_TRAIT_SELECT_PARTITION_FOR_VERTEX_LIST

/** @ingroup TraitFilterMacros
 * @brief The storage provides master edge filtering for edge list.
 * The suffixes ``_select_master`` and ``_select_mirror`` 
 * are the same as vertex list.
*/
#define GRIN_TRAIT_SELECT_MASTER_FOR_EDGE_LIST

/** @ingroup TraitFilterMacros
 * @brief The storage provides per partition edge filtering for edge list.
 * The suffix is ``_select_partition``.
*/
#define GRIN_TRAIT_SELECT_PARTITION_FOR_EDGE_LIST

/** @ingroup TraitFilterMacros
 * @brief The storage provides master neighbor filtering for adjacent list.
 * The suffixes are ``_select_master_neighbor`` and ``_select_mirror_neighbor``.
*/
#define GRIN_TRAIT_SELECT_MASTER_NEIGHBOR_FOR_ADJACENT_LIST

/** @ingroup TraitFilterMacros
 * @brief The storage provides per partition neighbor filtering for adjacent list.
 * The suffix is ``_select_neighbor_partition``.
*/
#define GRIN_TRAIT_SELECT_NEIGHBOR_PARTITION_FOR_ADJACENT_LIST
///@}

/* End of Section 2 */

/* Section 3. Property */

/** @name PropertyMacros
 * @brief Macros for basic property graph features
 */
///@{
/** @ingroup PropertyMacros
 * @brief Enable the pure value structure Row
*/
#define GRIN_ENABLE_ROW

/** @ingroup PropertyMacros
 * @brief This trait is used to indicate the storage can return a pointer to the
 * value of a property. However, this trait is going to be deprecated, because
 * it is too complex to use related APIs in the computing side.
*/
#define GRIN_TRAIT_CONST_VALUE_PTR

/** @ingroup PropertyMacros
 * @brief The graph has vertex properties, meaning it is a property graph.
*/
#define GRIN_WITH_VERTEX_PROPERTY

/** @ingroup PropertyMacros
 * @brief There are property names for vertex properties. 
 * The relationship between property name and properties is one-to-many, 
 * because properties bound to different vertex types are distinguished 
 * even they may share the same property name.
*/
#define GRIN_WITH_VERTEX_PROPERTY_NAME

/** @ingroup PropertyMacros
 * @brief There are unique names for each vertex type.
*/
#define GRIN_WITH_VERTEX_TYPE_NAME

/** @ingroup PropertyMacros
 * @brief The storage provides natural number IDs for vertex types.
 * It follows the design of natural ID trait in GRIN.
*/
#define GRIN_TRAIT_NATURAL_ID_FOR_VERTEX_TYPE

/** @ingroup PropertyMacros
 * @brief There are primary keys for vertices. 
 * Consider each vertex type as a table in relational database, where
 * the properties are the columns of the table.
 * The storage supports setting a subset of the properties as the primary keys,
 * meaning that each vertex of a certain type has its unique property values 
 * on the primary keys.
*/
#define GRIN_ENABLE_VERTEX_PRIMARY_KEYS

/** @ingroup PropertyMacros
 * @brief The storage provides natural number IDs for properties bound to
 * a certain vertex type.
 * It follows the design of natural ID trait in GRIN.
*/
#define GRIN_TRAIT_NATURAL_ID_FOR_VERTEX_PROPERTY

/** @ingroup PropertyMacros
 * @brief The graph has edge properties, meaning it is a property graph.
*/
#define GRIN_WITH_EDGE_PROPERTY

/** @ingroup PropertyMacros
 * @brief There are property names for edge properties. 
 * The relationship between property name and properties is one-to-many, 
 * because properties bound to different edge types are distinguished 
 * even they may share the same property name.
*/
#define GRIN_WITH_EDGE_PROPERTY_NAME

/** @ingroup PropertyMacros
 * @brief There are unique names for each edge type.
*/
#define GRIN_WITH_EDGE_TYPE_NAME

/** @ingroup PropertyMacros
 * @brief The storage provides natural number IDs for edge types.
 * It follows the design of natural ID trait in GRIN.
*/
#define GRIN_TRAIT_NATURAL_ID_FOR_EDGE_TYPE

/** @ingroup PropertyMacros
 * @brief There are primary keys for edges. 
 * Consider each edge type as a table in relational database, where
 * the properties are the columns of the table.
 * The storage supports setting a subset of the properties as the primary keys,
 * meaning that each edge of a certain type has its unique property values 
 * on the primary keys.
*/
#define GRIN_ENABLE_EDGE_PRIMARY_KEYS

/** @ingroup PropertyMacros
 * @brief The storage provides natural number IDs for properties bound to
 * a certain edge type.
 * It follows the design of natural ID trait in GRIN.
*/
#define GRIN_TRAIT_NATURAL_ID_FOR_EDGE_PROPERTY
///@}

/* End of Section 3 */

/* Section 4. Index */
/** @name IndexLabelMacros
 * @brief Macros for label features
 */
///@{
/** @ingroup IndexLabelMacros
 * @brief Enable vertex label on graph.
*/
#define GRIN_WITH_VERTEX_LABEL

/** @ingroup IndexLabelMacros
 * @brief Enable edge label on graph.
*/
#define GRIN_WITH_EDGE_LABEL
///@}

/** @name IndexOrderMacros
 * @brief Macros for ordering features.
 */
///@{
/** @ingroup IndexOrderMacros
 * @brief assume all vertex list are sorted.
 * We will expend the assumption to support master/mirror or
 * by type in the future if needed.
*/
#define GRIN_ASSUME_ALL_VERTEX_LIST_SORTED
///@}

/** @name IndexInternalIDMacros
 * @brief Macros for internal ID indexing features
 */
///@{
/** @ingroup IndexInternalIDMacros
 * @brief There is a unique internal ID of type int64 for each vertex,
 * and most importantly the internal ID has a range.
 */
#define GRIN_ENABLE_VERTEX_INTERNAL_ID_INDEX
///@}

/** @name IndexExternalIDMacros
 * @brief Macros for external ID indexing features
 */
///@{
/** @ingroup IndexExternalIDMacros
 * @brief There is a unique external ID of type int64 for each vertex,
 * e.g., the original ID of a vertex in GNN datasets.
 */
#define GRIN_ENABLE_VERTEX_EXTERNAL_ID_OF_INT64

/** @ingroup IndexExternalIDMacros
 * @brief There is a unique external ID of type string for each vertex,
 * e.g., the IRI of a vertex in RDF datasets.
 */
#define GRIN_ENABLE_VERTEX_EXTERNAL_ID_OF_STRING
///@}

/** @name IndexPKMacros
 * @brief Macros for pk indexing features
 */
///@{
/** @ingroup IndexPKMacros
 * @brief Enable vertex indexing on primary keys, meaning that
 * users can get a vertex handle using its primary key(s) value(s).
 */
#define GRIN_ENABLE_VERTEX_PK_INDEX

/** @ingroup IndexPKMacros
 * @brief Enable edge indexing on primary keys, meaning that
 * users can get an edge handle using its primary key(s) value(s).
 */
#define GRIN_ENABLE_EDGE_PK_INDEX
///@}

/* End of Section 4 */

/* Section 5. Common */

/** @name CommonMacros
 * @brief Macros for common features
 */
///@{
/** @ingroup CommonMacros
 * @brief The storage supports loose schema, meaning that
 * some vertices or edges may belong to none of the vertex types or edge types
 * in the schema respectively.
*/
#define GRIN_TRAIT_LOOSE_SCHEMA
///@}

/* End of Section 4 */
