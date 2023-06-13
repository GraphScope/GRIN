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
 * @brief 
 * Storage implementors first Turn-ON (i.e., define) the specific 
 * macros in this area based the features of the storage.
 * Then define the types of the enabled handles as well as corresponding
 * null values.
*/

/* Define supported macros based on storage features */
// Topology
#define GRIN_ASSUME_HAS_DIRECTED_GRAPH
#define GRIN_ASSUME_HAS_UNDIRECTED_GRAPH
#define GRIN_ASSUME_HAS_MULTI_EDGE_GRAPH
#define GRIN_ENABLE_VERTEX_LIST
#define GRIN_ENABLE_VERTEX_LIST_ARRAY
#define GRIN_ENABLE_VERTEX_LIST_ITERATOR
#define GRIN_ENABLE_ADJACENT_LIST
#define GRIN_ENABLE_ADJACENT_LIST_ARRAY
#define GRIN_ENABLE_ADJACENT_LIST_ITERATOR
// Partition
#define GRIN_ENABLE_GRAPH_PARTITION
#define GRIN_TRAIT_NATURAL_ID_FOR_PARTITION
#define GRIN_ENABLE_VERTEX_REF
#define GRIN_TRAIT_FAST_VERTEX_REF
#define GRIN_ASSUME_EDGE_CUT_PARTITION
#define GRIN_TRAIT_SELECT_MASTER_FOR_VERTEX_LIST
// Property
#define GRIN_ENABLE_ROW
#define GRIN_WITH_VERTEX_PROPERTY
#define GRIN_WITH_VERTEX_PROPERTY_NAME
#define GRIN_WITH_VERTEX_TYPE_NAME
#define GRIN_TRAIT_NATURAL_ID_FOR_VERTEX_TYPE
#define GRIN_ENABLE_VERTEX_PK_OF_INT64
#define GRIN_TRAIT_NATURAL_ID_FOR_VERTEX_PROPERTY
#define GRIN_WITH_EDGE_PROPERTY
#define GRIN_WITH_EDGE_PROPERTY_NAME
#define GRIN_WITH_EDGE_TYPE_NAME
#define GRIN_TRAIT_NATURAL_ID_FOR_EDGE_TYPE
#define GRIN_TRAIT_NATURAL_ID_FOR_EDGE_PROPERTY
#define GRIN_TRAIT_SELECT_TYPE_FOR_VERTEX_LIST
#define GRIN_TRAIT_SELECT_EDGE_TYPE_FOR_ADJACENT_LIST
// Index
#define GRIN_ASSUME_ALL_VERTEX_LIST_SORTED
#define GRIN_ENABLE_VERTEX_ORIGINAL_ID_OF_INT64
#define GRIN_ENABLE_VERTEX_PK_INDEX

/* Define the handles using typedef */
typedef void* GRIN_GRAPH;                      
typedef unsigned long long int GRIN_VERTEX;                     
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
typedef unsigned GRIN_PARTITION;
typedef void* GRIN_PARTITION_LIST;
#endif

#ifdef GRIN_TRAIT_NATURAL_ID_FOR_PARTITION
typedef unsigned GRIN_PARTITION_ID;
#endif

#ifdef GRIN_ENABLE_VERTEX_REF
typedef long long int GRIN_VERTEX_REF;
#endif

#ifdef GRIN_ENABLE_EDGE_REF
typedef void* GRIN_EDGE_REF;
#endif

#ifdef GRIN_WITH_VERTEX_PROPERTY
typedef unsigned GRIN_VERTEX_TYPE;
typedef void* GRIN_VERTEX_TYPE_LIST;
typedef unsigned long long int GRIN_VERTEX_PROPERTY;
typedef void* GRIN_VERTEX_PROPERTY_LIST;
#endif

#ifdef GRIN_TRAIT_NATURAL_ID_FOR_VERTEX_TYPE
typedef unsigned GRIN_VERTEX_TYPE_ID;
#endif

#ifdef GRIN_TRAIT_NATURAL_ID_FOR_VERTEX_PROPERTY
typedef unsigned GRIN_VERTEX_PROPERTY_ID;
#endif

#ifdef GRIN_WITH_EDGE_PROPERTY
typedef unsigned GRIN_EDGE_TYPE;
typedef void* GRIN_EDGE_TYPE_LIST;
typedef void* GRIN_VEV_TYPE;
typedef void* GRIN_VEV_TYPE_LIST;
typedef unsigned long long int GRIN_EDGE_PROPERTY;
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

/* Define invalid values for returns of handles */
#define GRIN_NULL_GRAPH NULL
#define GRIN_NULL_VERTEX (unsigned long long int)~0
#define GRIN_NULL_EDGE NULL
#define GRIN_NULL_LIST NULL
#define GRIN_NULL_LIST_ITERATOR NULL
#define GRIN_NULL_PARTITION (unsigned)~0
#define GRIN_NULL_VERTEX_REF -1
#define GRIN_NULL_EDGE_REF NULL
#define GRIN_NULL_VERTEX_TYPE (unsigned)~0
#define GRIN_NULL_EDGE_TYPE (unsigned)~0
#define GRIN_NULL_VERTEX_PROPERTY (unsigned long long int)~0
#define GRIN_NULL_EDGE_PROPERTY (unsigned long long int)~0
#define GRIN_NULL_ROW NULL
#define GRIN_NULL_NATURAL_ID (unsigned)~0
#define GRIN_NULL_SIZE (unsigned)~0
#define GRIN_NULL_NAME NULL
