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
 @file property/topology.h
 @brief Define the topology related APIs under property graph
*/

#ifndef GRIN_INCLUDE_PROPERTY_TOPOLOGY_H_
#define GRIN_INCLUDE_PROPERTY_TOPOLOGY_H_

#include "../../predefine.h"

#ifdef GRIN_WITH_VERTEX_PROPERTY
size_t grin_get_vertex_num_by_type(GRIN_GRAPH, GRIN_VERTEX_TYPE);
#endif

#ifdef GRIN_WITH_EDGE_PROPERTY
size_t grin_get_edge_num_by_type(GRIN_GRAPH, GRIN_EDGE_TYPE);
#endif

#if defined(GRIN_ENABLE_VERTEX_LIST) && defined(GRIN_WITH_VERTEX_PROPERTY)
GRIN_VERTEX_LIST grin_get_vertex_list_by_type(GRIN_GRAPH, GRIN_VERTEX_TYPE);
#endif

#if defined(GRIN_ENABLE_EDGE_LIST) && defined(GRIN_WITH_EDGE_PROPERTY)
GRIN_EDGE_LIST grin_get_edge_list_by_type(GRIN_GRAPH, GRIN_EDGE_TYPE);
#endif

#if defined(GRIN_ENABLE_ADJACENT_LIST) && defined(GRIN_WITH_EDGE_PROPERTY)
GRIN_ADJACENT_LIST grin_get_adjacent_list_by_edge_type(GRIN_GRAPH, GRIN_EDGE_TYPE);
#endif

#endif // GRIN_INCLUDE_PROPERTY_TOPOLOGY_H_