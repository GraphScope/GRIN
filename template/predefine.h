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
 * @brief This template file consists of four parts:
 * 1. The predefined enumerate types of GRIN, which should NOT be modified.
 * 2. The supported macros which should be specified by storage implementors
 * based on storage features.
 * 3. The typedefs of the enabled handles. This should be specified by storage.
 * 4. The corresponding null values of the enabled handles. This should be
 * specified by storage.
 */

#ifndef GRIN_PREDEFINE_H_
#define GRIN_PREDEFINE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

/* 1. Define supported macros based on storage features */
// Topology
#define GRIN_ASSUME_HAS_DIRECTED_GRAPH
#define GRIN_ASSUME_HAS_UNDIRECTED_GRAPH
#define GRIN_ASSUME_HAS_MULTI_EDGE_GRAPH
#define GRIN_WITH_VERTEX_DATA
#define GRIN_WITH_EDGE_DATA
#define GRIN_ENABLE_VERTEX_LIST
#define GRIN_ENABLE_VERTEX_LIST_ARRAY
#define GRIN_ENABLE_VERTEX_LIST_ITERATOR
#define GRIN_ENABLE_EDGE_LIST
#define GRIN_ENABLE_EDGE_LIST_ARRAY
#define GRIN_ENABLE_EDGE_LIST_ITERATOR
#define GRIN_ENABLE_ADJACENT_LIST
#define GRIN_ENABLE_ADJACENT_LIST_ARRAY
#define GRIN_ENABLE_ADJACENT_LIST_ITERATOR
// Partition
#define GRIN_ENABLE_GRAPH_PARTITION
#define GRIN_ASSUME_EDGE_CUT_PARTITION
#define GRIN_ASSUME_VERTEX_CUT_PARTITION
#define GRIN_ASSUME_WITH_UNIVERSAL_VERTICES
#define GRIN_TRAIT_NATURAL_ID_FOR_PARTITION
#define GRIN_ENABLE_VERTEX_REF
#define GRIN_TRAIT_FAST_VERTEX_REF
#define GRIN_ENABLE_EDGE_REF
#define GRIN_TRAIT_MASTER_VERTEX_MIRROR_PARTITION_LIST
#define GRIN_TRAIT_MIRROR_VERTEX_MIRROR_PARTITION_LIST
#define GRIN_TRAIT_MASTER_EDGE_MIRROR_PARTITION_LIST
#define GRIN_TRAIT_MIRROR_EDGE_MIRROR_PARTITION_LIST
#define GRIN_TRAIT_SELECT_MASTER_FOR_VERTEX_LIST
#define GRIN_TRAIT_SELECT_PARTITION_FOR_VERTEX_LIST
#define GRIN_TRAIT_SELECT_MASTER_FOR_EDGE_LIST
#define GRIN_TRAIT_SELECT_PARTITION_FOR_EDGE_LIST
#define GRIN_TRAIT_SELECT_MASTER_NEIGHBOR_FOR_ADJACENT_LIST
#define GRIN_TRAIT_SELECT_NEIGHBOR_PARTITION_FOR_ADJACENT_LIST
// Property
#define GRIN_ENABLE_ROW
#define GRIN_TRAIT_CONST_VALUE_PTR
#define GRIN_ENABLE_SCHEMA
#define GRIN_TRAIT_PROPERTY_VALUE_OF_FLOAT_ARRAY
#define GRIN_WITH_VERTEX_PROPERTY
#define GRIN_ENABLE_VERTEX_PRIMARY_KEYS
#define GRIN_WITH_EDGE_PROPERTY
#define GRIN_ENABLE_EDGE_PRIMARY_KEYS
// Index
#define GRIN_WITH_VERTEX_LABEL
#define GRIN_WITH_EDGE_LABEL
#define GRIN_ASSUME_ALL_VERTEX_LIST_SORTED
#define GRIN_ENABLE_VERTEX_INTERNAL_ID_INDEX
#define GRIN_ENABLE_VERTEX_EXTERNAL_ID_OF_INT64
#define GRIN_ENABLE_VERTEX_EXTERNAL_ID_OF_STRING
#define GRIN_ENABLE_VERTEX_PK_INDEX
#define GRIN_ENABLE_EDGE_PK_INDEX


/* 2. Define the handles using typedef */
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
typedef void* GRIN_VERTEX_PROPERTY;
typedef void* GRIN_VERTEX_PROPERTY_LIST;
#endif

#ifdef GRIN_WITH_EDGE_PROPERTY
typedef void* GRIN_EDGE_PROPERTY;
typedef void* GRIN_EDGE_PROPERTY_LIST;
#endif

#ifdef GRIN_ENABLE_SCHEMA
typedef void* GRIN_VERTEX_TYPE;
typedef void* GRIN_VERTEX_TYPE_LIST;
typedef unsigned GRIN_VERTEX_TYPE_ID;
typedef unsigned GRIN_VERTEX_PROPERTY_ID;
typedef void* GRIN_EDGE_TYPE;
typedef void* GRIN_EDGE_TYPE_LIST;
typedef unsigned GRIN_EDGE_TYPE_ID;
typedef unsigned GRIN_EDGE_PROPERTY_ID;
#endif

#ifdef GRIN_ENABLE_ROW
typedef void* GRIN_ROW;
#endif

#if defined(GRIN_WITH_VERTEX_LABEL) || defined(GRIN_WITH_EDGE_LABEL)
typedef void* GRIN_LABEL;
typedef void* GRIN_LABEL_LIST;
#endif

/* 3. Define invalid values for returns of handles */
#define GRIN_NULL_GRAPH NULL
#define GRIN_NULL_VERTEX NULL
#define GRIN_NULL_EDGE NULL
#define GRIN_NULL_VERTEX_DATA NULL
#define GRIN_NULL_VERTEX_LIST NULL
#define GRIN_NULL_VERTEX_LIST_ITERATOR NULL
#define GRIN_NULL_ADJACENT_LIST NULL
#define GRIN_NULL_ADJACENT_LIST_ITERATOR NULL
#define GRIN_NULL_EDGE_DATA NULL
#define GRIN_NULL_EDGE_LIST NULL
#define GRIN_NULL_EDGE_LIST_ITERATOR NULL
#define GRIN_NULL_PARTITIONED_GRAPH NULL
#define GRIN_NULL_PARTITION NULL
#define GRIN_NULL_PARTITION_LIST NULL
#define GRIN_NULL_PARTITION_ID (unsigned)~0
#define GRIN_NULL_VERTEX_REF NULL
#define GRIN_NULL_EDGE_REF NULL
#define GRIN_NULL_VERTEX_TYPE NULL
#define GRIN_NULL_VERTEX_TYPE_LIST NULL
#define GRIN_NULL_VERTEX_PROPERTY NULL
#define GRIN_NULL_VERTEX_PROPERTY_LIST NULL
#define GRIN_NULL_VERTEX_TYPE_ID (unsigned)~0
#define GRIN_NULL_VERTEX_PROPERTY_ID (unsigned)~0
#define GRIN_NULL_EDGE_TYPE NULL
#define GRIN_NULL_EDGE_TYPE_LIST NULL
#define GRIN_NULL_EDGE_PROPERTY NULL
#define GRIN_NULL_EDGE_PROPERTY_LIST NULL
#define GRIN_NULL_EDGE_TYPE_ID (unsigned)~0
#define GRIN_NULL_EDGE_PROPERTY_ID (unsigned)~0
#define GRIN_NULL_ROW NULL
#define GRIN_NULL_LABEL NULL
#define GRIN_NULL_LABEL_LIST NULL
#define GRIN_NULL_SIZE (unsigned)~0
#define GRIN_NULL_NAME NULL

#ifdef __cplusplus
}
#endif

#endif  // GRIN_PREDEFINE_H_