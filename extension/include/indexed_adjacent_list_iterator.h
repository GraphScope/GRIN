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

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GRIN_EXTENSION_INCLUDE_INDEXED_ADJACENT_LIST_ITERATOR_H_
#define GRIN_EXTENSION_INCLUDE_INDEXED_ADJACENT_LIST_ITERATOR_H_

#include "../handle.h"

#if defined (GRIN_ENABLE_ADJACENT_LIST_ITERATOR) && !defined(GRIN_ENABLE_ADJACENT_LIST_ARRAY)
GRIN_INDEXED_ADJACENT_LIST_ITERATOR grin_get_vertex_indexed_adjacent_list_iterator_by_edge_type(GRIN_GRAPH, GRIN_DIRECTION, GRIN_VERTEX, GRIN_EDGE_TYPE);

void grin_destroy_vertex_indexed_adjacent_list_iterator(GRIN_GRAPH, GRIN_INDEXED_ADJACENT_LIST_ITERATOR);

size_t grin_get_indexed_adjacent_list_iterator_size(GRIN_GRAPH, GRIN_INDEXED_ADJACENT_LIST_ITERATOR);

GRIN_VERTEX grin_get_neighbor_from_indexed_adjacent_list_iterator(GRIN_GRAPH, GRIN_INDEXED_ADJACENT_LIST_ITERATOR, size_t);

GRIN_EDGE grin_get_edge_from_indexed_adjacent_list_iterator(GRIN_GRAPH, GRIN_INDEXED_ADJACENT_LIST_ITERATOR, size_t);
#endif


#endif // GRIN_EXTENSION_INCLUDE_INDEXED_ADJACENT_LIST_ITERATOR_H_

#ifdef __cplusplus
}
#endif