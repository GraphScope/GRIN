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
 * @file predefine.h
 * @brief Pre-defined macros for storage features.
 * The macros are divided into several sections such as topology,
 * partition, and so on.
 * In each section, the first part lists all available macros, and
 * undefines all macros by default.
 * After that is the MOST IMPORTANT part for storage implementors, 
 * i.e., the storage enable area.
 * Storage implementors should Turn-ON (i.e., define) the specific 
 * macros in this area based the features of the storage.
 * The final part is the rule part to handle dependencies between 
 * macros which should not be edited.
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GRIN_INCLUDE_PREDEFINE_H_
#define GRIN_INCLUDE_PREDEFINE_H_

#include <stdbool.h>
#include <stddef.h>

/// Enumerates the directions of edges with respect to a certain vertex
typedef enum {
  IN = 0,     ///< incoming
  OUT = 1,    ///< outgoing
  BOTH = 2,   ///< incoming & outgoing
} GRIN_DIRECTION;

/// Enumerates the datatype supported in the storage
typedef enum {
  Undefined = 0,      ///< other unknown types
  Int32 = 1,          ///< int
  UInt32 = 2,         ///< unsigned int
  Int64 = 3,          ///< long int
  UInt64 = 4,         ///< unsigned long int
  Float = 5,          ///< float
  Double = 6,         ///< double
  String = 7,         ///< string
  Date32 = 8,         ///< date
  Time32 = 9,         ///< Time32
  Timestamp64 = 10,   ///< Timestamp
} GRIN_DATATYPE;

/// Enumerates the error codes of grin
typedef enum {
  NO_ERROR = 0,              ///< success
  UNKNOWN_ERROR = 1,         ///< unknown error
  INVALID_VALUE = 2,         ///< invalid value
  UNKNOWN_DATATYPE = 3,      ///< unknown datatype
} GRIN_ERROR_CODE;

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


#ifndef GRIN_DOXYGEN_SKIP
// GRIN_DEFAULT_DISABLE
#undef GRIN_ASSUME_HAS_DIRECTED_GRAPH
#undef GRIN_ASSUME_HAS_UNDIRECTED_GRAPH
#undef GRIN_ASSUME_HAS_MULTI_EDGE_GRAPH
#undef GRIN_WITH_VERTEX_DATA
#undef GRIN_WITH_EDGE_DATA
#undef GRIN_ENABLE_VERTEX_LIST
#undef GRIN_ENABLE_VERTEX_LIST_ARRAY
#undef GRIN_ENABLE_VERTEX_LIST_ITERATOR
#undef GRIN_ENABLE_EDGE_LIST
#undef GRIN_ENABLE_EDGE_LIST_ARRAY
#undef GRIN_ENABLE_EDGE_LIST_ITERATOR
#undef GRIN_ENABLE_ADJACENT_LIST
#undef GRIN_ENABLE_ADJACENT_LIST_ARRAY
#undef GRIN_ENABLE_ADJACENT_LIST_ITERATOR
// GRIN_END

// GRIN_STORAGE_ENABLE
// [IMPORTANT] Enable all the features of the storage here
// GRIN_END

// GRIN_FEATURE_DEPENDENCY
// GRIN_END

#endif  // GRIN_DOXYGEN_SKIP
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



/** @name PartitionStrategyMacros
 * @brief Macros to define partition strategy assumptions, a partition strategy
 * can be seen as a combination of detail partition assumptions which are defined after
 * the strategies. Please refer to the documents for strategy details.
*/
///@{
/** @ingroup PartitionStrategyMacros
 * @brief The storage ONLY uses all-replicate partition strategy. This means the
 * storage's replicate the graph among all partitions.
*/
#define GRIN_ASSUME_ALL_REPLICATE_PARTITION

/** @ingroup PartitionStrategyMacros
 * @brief The storage ONLY uses edge-cut partition strategy. This means the
 * storage's entire partition strategy complies with edge-cut strategy
 * definition in GRIN.
*/
#define GRIN_ASSUME_EDGE_CUT_PARTITION

/** @ingroup PartitionStrategyMacros
 * @brief The storage ONLY uses edge-cut partition & edges only follow src strategy.
 * This means the storage's entire partition strategy complies with edge-cut strategy
 * definition in GRIN, and edges are partitioned to the partition of the source vertex.
*/
#define GRIN_ASSUME_EDGE_CUT_FOLLOW_SRC_PARTITION


/** @ingroup PartitionStrategyMacros
 * @brief The storage ONLY uses edge-cut partition & edges only follow dst strategy.
 * This means the storage's entire partition strategy complies with edge-cut strategy
 * definition in GRIN, and edges are partitioned to the partition of the destination vertex.
*/
#define GRIN_ASSUME_EDGE_CUT_FOLLOW_DST_PARTITION


/** @ingroup PartitionStrategyMacros
 * @brief The storage ONLY uses vertex-cut partition strategy. This means the
 * storage's entire partition strategy complies with vertex-cut strategy
 * definition in GRIN.
*/
#define GRIN_ASSUME_VERTEX_CUT_PARTITION
///@}

/** @name PartitionAssumptionMacros
 * @brief Macros to define detailed partition assumptions with respect to the
 * concept of local complete. Please refer to the documents for the meaning of
 * local complete.
*/
///@{
/** @ingroup PartitionAssumptionMacros
 * @brief Assume the vertex data are only stored together with master vertices.
*/
#define GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_VERTEX_DATA

/** @ingroup PartitionAssumptionMacros
 * @brief Assume the vertex data are replicated on both master and mirror vertices.
*/
#define GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_VERTEX_DATA

/** @ingroup PartitionAssumptionMacros
 * @brief Assume the edge data are only stored together with master edges.
*/
#define GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_EDGE_DATA

/** @ingroup PartitionAssumptionMacros
 * @brief Assume the edge data are replicated on both master and mirror edges.
*/
#define GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_EDGE_DATA
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

#ifndef GRIN_DOXYGEN_SKIP
// GRIN_DEFAULT_DISABLE
#undef GRIN_ENABLE_GRAPH_PARTITION
#undef GRIN_TRAIT_NATURAL_ID_FOR_PARTITION
#undef GRIN_ENABLE_VERTEX_REF
#undef GRIN_TRAIT_FAST_VERTEX_REF
#undef GRIN_ENABLE_EDGE_REF
#undef GRIN_ASSUME_ALL_REPLICATE_PARTITION
#undef GRIN_ASSUME_EDGE_CUT_PARTITION
#undef GRIN_ASSUME_EDGE_CUT_FOLLOW_SRC_PARTITION
#undef GRIN_ASSUME_EDGE_CUT_FOLLOW_DST_PARTITION
#undef GRIN_ASSUME_VERTEX_CUT_PARTITION
#undef GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_VERTEX_DATA
#undef GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_VERTEX_DATA
#undef GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_EDGE_DATA
#undef GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_EDGE_DATA
#undef GRIN_TRAIT_MASTER_VERTEX_MIRROR_PARTITION_LIST
#undef GRIN_TRAIT_MIRROR_VERTEX_MIRROR_PARTITION_LIST
#undef GRIN_TRAIT_MASTER_EDGE_MIRROR_PARTITION_LIST
#undef GRIN_TRAIT_MIRROR_EDGE_MIRROR_PARTITION_LIST
#undef GRIN_TRAIT_SELECT_MASTER_FOR_VERTEX_LIST
#undef GRIN_TRAIT_SELECT_PARTITION_FOR_VERTEX_LIST
#undef GRIN_TRAIT_SELECT_MASTER_FOR_EDGE_LIST
#undef GRIN_TRAIT_SELECT_PARTITION_FOR_EDGE_LIST
#undef GRIN_TRAIT_SELECT_MASTER_NEIGHBOR_FOR_ADJACENT_LIST
#undef GRIN_TRAIT_SELECT_NEIGHBOR_PARTITION_FOR_ADJACENT_LIST
// GRIN_END

// GRIN_STORAGE_ENABLE
// [IMPORTANT] Enable all the features of the storage here
// GRIN_END

// GRIN_FEATURE_DEPENDENCY
#ifdef GRIN_ASSUME_ALL_REPLICATE_PARTITION
#define GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_VERTEX_DATA
#define GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_EDGE_DATA
#endif

#ifdef GRIN_ASSUME_EDGE_CUT_PARTITION
#define GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_VERTEX_DATA
#define GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_EDGE_DATA
#endif

#ifdef GRIN_ASSUME_EDGE_CUT_FOLLOW_SRC_PARTITION
#define GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_VERTEX_DATA
#define GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_EDGE_DATA
#endif

#ifdef GRIN_ASSUME_EDGE_CUT_FOLLOW_DST_PARTITION
#define GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_VERTEX_DATA
#define GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_EDGE_DATA
#endif

#ifdef GRIN_ASSUME_VERTEX_CUT_PARTITION
#define GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_VERTEX_DATA
#define GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_EDGE_DATA
#define GRIN_TRAIT_MASTER_VERTEX_MIRROR_PARTITION_LIST
#endif
// GRIN_END

#endif // GRIN_DOXY_SKIP
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
 * @brief There are primary keys for vertices, and the primary key is only
 * a single integer.
*/
#define GRIN_ENABLE_VERTEX_PK_OF_INT64

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
 * @brief There are primary keys for edges, and the primary key is only
 * a single integer.
*/
#define GRIN_ENABLE_EDGE_PK_OF_INT64

/** @ingroup PropertyMacros
 * @brief The storage provides natural number IDs for properties bound to
 * a certain edge type.
 * It follows the design of natural ID trait in GRIN.
*/
#define GRIN_TRAIT_NATURAL_ID_FOR_EDGE_PROPERTY
///@}

/** @name TraitFilterTypeMacros
 * @brief Macros of traits to filter vertex/edge type for
 * structures like vertex list and adjacent list.
 */
///@{
/** @ingroup TraitFilterTypeMacros
 * @brief The storage provides specific relationship description for each
 * vertex-edge-vertex type traid. This means further optimizations can be
 * applied by the callers for vev traid under certain relationships, such as
 * one-to-one, one-to-many, or many-to-one.
*/
#define GRIN_TRAIT_SPECIFIC_VEV_RELATION
///@}


/** @name PropetyAssumptionMacros
 * @brief Macros of assumptions for property local complete, and particularly define
 * the by type local complete assumptions for hybrid partiton strategy.
 */
///@{
/** @ingroup PropetyAssumptionMacros
 * @brief Assume full property values of a vertex are ONLY stored with master vertices.
*/
#define GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_VERTEX_PROPERTY

/** @ingroup PropetyAssumptionMacros
 * @brief Assume full property values of a vertex are replicated with master and mirror vertices.
*/
#define GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_VERTEX_PROPERTY

/** @ingroup PropetyAssumptionMacros
 * @brief Assume full property values of a vertex are split among master and mirror vertices.
*/
#define GRIN_ASSUME_SPLIT_MASTER_MIRROR_PARTITION_FOR_VERTEX_PROPERTY

/** @ingroup PropetyAssumptionMacros
 * @brief Assume full property values of an edge are ONLY stored with master edges.
*/
#define GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_EDGE_PROPERTY

/** @ingroup PropetyAssumptionMacros
 * @brief Assume full property values of an edge are replicated with master and mirror edges.
*/
#define GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_EDGE_PROPERTY

/** @ingroup PropetyAssumptionMacros
 * @brief Assume full property values of an edge are split among master and mirror edges.
*/
#define GRIN_ASSUME_SPLIT_MASTER_MIRROR_PARTITION_FOR_EDGE_PROPERTY
///@}

#ifndef GRIN_DOXYGEN_SKIP
// GRIN_DEFAULT_DISABLE
#undef GRIN_ENABLE_ROW
#undef GRIN_TRAIT_CONST_VALUE_PTR
#undef GRIN_WITH_VERTEX_PROPERTY
#undef GRIN_WITH_VERTEX_PROPERTY_NAME
#undef GRIN_WITH_VERTEX_TYPE_NAME
#undef GRIN_TRAIT_NATURAL_ID_FOR_VERTEX_TYPE
#undef GRIN_ENABLE_VERTEX_PRIMARY_KEYS
#undef GRIN_ENABLE_VERTEX_PK_OF_INT64
#undef GRIN_TRAIT_NATURAL_ID_FOR_VERTEX_PROPERTY
#undef GRIN_WITH_EDGE_PROPERTY
#undef GRIN_WITH_EDGE_PROPERTY_NAME
#undef GRIN_WITH_EDGE_TYPE_NAME
#undef GRIN_TRAIT_NATURAL_ID_FOR_EDGE_TYPE
#undef GRIN_ENABLE_EDGE_PRIMARY_KEYS
#undef GRIN_ENABLE_EDGE_PK_OF_INT64
#undef GRIN_TRAIT_NATURAL_ID_FOR_EDGE_PROPERTY
#undef GRIN_TRAIT_SPECIFIC_VEV_RELATION
#undef GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_VERTEX_PROPERTY
#undef GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_VERTEX_PROPERTY
#undef GRIN_ASSUME_SPLIT_MASTER_MIRROR_PARTITION_FOR_VERTEX_PROPERTY
#undef GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_EDGE_PROPERTY
#undef GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_EDGE_PROPERTY
#undef GRIN_ASSUME_SPLIT_MASTER_MIRROR_PARTITION_FOR_EDGE_PROPERTY
// GRIN_END

// GRIN_STORAGE_ENABLE
// [IMPORTANT] Enable all the features of the storage here
// GRIN_END

// GRIN_FEATURE_DEPENDENCY
#ifdef GRIN_ASSUME_ALL_REPLICATE_PARTITION
#define GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_VERTEX_PROPERTY
#define GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_EDGE_PROPERTY
#endif

#ifdef GRIN_ASSUME_EDGE_CUT_PARTITION
#define GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_VERTEX_PROPERTY
#define GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_EDGE_PROPERTY
#endif

#ifdef GRIN_ASSUME_EDGE_CUT_FOLLOW_SRC_PARTITION
#define GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_VERTEX_PROPERTY
#define GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_EDGE_PROPERTY
#endif

#ifdef GRIN_ASSUME_EDGE_CUT_FOLLOW_DST_PARTITION
#define GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_VERTEX_PROPERTY
#define GRIN_ASSUME_MASTER_ONLY_PARTITION_FOR_EDGE_PROPERTY
#endif

#ifdef GRIN_ASSUME_VERTEX_CUT_PARTITION
#define GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_VERTEX_PROPERTY
#define GRIN_ASSUME_REPLICATE_MASTER_MIRROR_PARTITION_FOR_EDGE_PROPERTY
#endif

#ifdef GRIN_ENABLE_VERTEX_PRIMARY_KEYS
#define GRIN_ENABLE_ROW
#endif

#ifdef GRIN_ENABLE_EDGE_PRIMARY_KEYS
#define GRIN_ENABLE_ROW
#endif
// GRIN_END

#endif // GRIN_DOXY_SKIP
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

/** @name IndexOIDMacros
 * @brief Macros for original ID features
 */
///@{
/** @ingroup IndexOIDMacros
 * @brief There is a unique original ID of type int64 for each vertex.
 * This facilitates queries starting from a specific vertex,
 * since users can get the vertex handle directly using its original ID.
 */
#define GRIN_ENABLE_VERTEX_ORIGINAL_ID_OF_INT64

/** @ingroup IndexOIDMacros
 * @brief There is a unique original ID of type string for each vertex.
 * This facilitates queries starting from a specific vertex,
 * since users can get the vertex handle directly using its original ID.
 */
#define GRIN_ENABLE_VERTEX_ORIGINAL_ID_OF_STRING
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

#ifndef GRIN_DOXYGEN_SKIP
// GRIN_DEFAULT_DISABLE
#undef GRIN_WITH_VERTEX_LABEL
#undef GRIN_WITH_EDGE_LABEL
#undef GRIN_ASSUME_ALL_VERTEX_LIST_SORTED
#undef GRIN_ENABLE_VERTEX_ORIGINAL_ID_OF_INT64
#undef GRIN_ENABLE_VERTEX_ORIGINAL_ID_OF_STRING
#undef GRIN_ENABLE_VERTEX_PK_INDEX
#undef GRIN_ENABLE_EDGE_PK_INDEX
// GRIN_END

// GRIN_STORAGE_ENABLE
// [IMPORTANT] Enable all the features of the storage here
// GRIN_END

// GRIN_FEATURE_DEPENDENCY
// GRIN_END

#endif  // GRIN_DOXYGEN_SKIP
/* End of Section 4 */

/** @name NullValues
 * Macros for Null(invalid) values
 */
///@{
/** @brief Null graph (invalid return value) */
#define GRIN_NULL_GRAPH NULL
/** @brief Non-existing vertex (invalid return value) */
#define GRIN_NULL_VERTEX NULL
/** @brief Non-existing edge (invalid return value) */
#define GRIN_NULL_EDGE NULL
/** @brief Null list of any kind (invalid return value) */
#define GRIN_NULL_LIST NULL
/** @brief Null list iterator of any kind (invalid return value) */
#define GRIN_NULL_LIST_ITERATOR NULL
/** @brief Non-existing partition (invalid return value) */
#define GRIN_NULL_PARTITION NULL
/** @brief Null vertex reference (invalid return value) */
#define GRIN_NULL_VERTEX_REF NULL
/** @brief Null edge reference (invalid return value) */
#define GRIN_NULL_EDGE_REF NULL
/** @brief Non-existing vertex type (invalid return value) */
#define GRIN_NULL_VERTEX_TYPE NULL
/** @brief Non-existing edge type (invalid return value) */
#define GRIN_NULL_EDGE_TYPE NULL
/** @brief Non-existing vertex property (invalid return value) */
#define GRIN_NULL_VERTEX_PROPERTY NULL
/** @brief Non-existing vertex property (invalid return value) */
#define GRIN_NULL_EDGE_PROPERTY NULL
/** @brief Null row (invalid return value) */
#define GRIN_NULL_ROW NULL
/** @brief Null natural id of any kind (invalid return value) */
#define GRIN_NULL_NATURAL_ID (unsigned)~0
/** @brief Null size (invalid return value) */
#define GRIN_NULL_SIZE (unsigned)~0
/** @breif Null name (invalid return value) */
#define GRIN_NULL_NAME NULL
///@}


/* Define the handles using typedef */
typedef void* GRIN_GRAPH;
typedef void* GRIN_VERTEX;
typedef void* GRIN_EDGE;

#ifdef GRIN_WITH_VERTEX_DATA
typedef void* GRIN_VERTEX_DATA;
#endif

#ifdef GRIN_ENABLE_VERTEX_LIST
typedef void* GRIN_VERTEX_LIST;
#endif

#ifdef GRIN_ENABLE_VERTEX_LIST_ITERATOR
typedef void* GRIN_VERTEX_LIST_ITERATOR;
#endif

#ifdef GRIN_ENABLE_ADJACENT_LIST
typedef void* GRIN_ADJACENT_LIST;
#endif

#ifdef GRIN_ENABLE_ADJACENT_LIST_ITERATOR
typedef void* GRIN_ADJACENT_LIST_ITERATOR;
#endif

#ifdef GRIN_WITH_EDGE_DATA
typedef void* GRIN_EDGE_DATA;
#endif

#ifdef GRIN_ENABLE_EDGE_LIST
typedef void* GRIN_EDGE_LIST;
#endif

#ifdef GRIN_ENABLE_EDGE_LIST_ITERATOR
typedef void* GRIN_EDGE_LIST_ITERATOR;
#endif

#ifdef GRIN_ENABLE_GRAPH_PARTITION
typedef void* GRIN_PARTITIONED_GRAPH;
typedef void* GRIN_PARTITION;
typedef void* GRIN_PARTITION_LIST;
#endif

#ifdef GRIN_TRAIT_NATURAL_ID_FOR_PARTITION
typedef unsigned GRIN_PARTITION_ID;
#endif

#ifdef GRIN_ENABLE_VERTEX_REF
typedef void* GRIN_VERTEX_REF;
#endif

#ifdef GRIN_ENABLE_EDGE_REF
typedef void* GRIN_EDGE_REF;
#endif


#ifdef GRIN_WITH_VERTEX_PROPERTY
typedef void* GRIN_VERTEX_TYPE;
typedef void* GRIN_VERTEX_TYPE_LIST;
typedef void* GRIN_VERTEX_PROPERTY;
typedef void* GRIN_VERTEX_PROPERTY_LIST;
#endif

#ifdef GRIN_TRAIT_NATURAL_ID_FOR_VERTEX_TYPE
typedef unsigned GRIN_VERTEX_TYPE_ID;
#endif

#ifdef GRIN_TRAIT_NATURAL_ID_FOR_VERTEX_PROPERTY
typedef unsigned GRIN_VERTEX_PROPERTY_ID;
#endif

#ifdef GRIN_WITH_EDGE_PROPERTY
typedef void* GRIN_EDGE_TYPE;
typedef void* GRIN_EDGE_TYPE_LIST;
typedef void* GRIN_VEV_TYPE;
typedef void* GRIN_VEV_TYPE_LIST;
typedef void* GRIN_EDGE_PROPERTY;
typedef void* GRIN_EDGE_PROPERTY_LIST;
#endif

#ifdef GRIN_TRAIT_NATURAL_ID_FOR_EDGE_TYPE
typedef unsigned GRIN_EDGE_TYPE_ID;
#endif

#ifdef GRIN_TRAIT_NATURAL_ID_FOR_EDGE_PROPERTY
typedef unsigned GRIN_EDGE_PROPERTY_ID;
#endif

#ifdef GRIN_ENABLE_ROW
typedef void* GRIN_ROW;
#endif

#if defined(GRIN_WITH_VERTEX_LABEL) || defined(GRIN_WITH_EDGE_LABEL)
typedef void* GRIN_LABEL;
typedef void* GRIN_LABEL_LIST;
#endif

#endif  // GRIN_INCLUDE_PREDEFINE_H_

#ifdef __cplusplus
}
#endif