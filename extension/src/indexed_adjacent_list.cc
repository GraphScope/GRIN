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

#include "predefine.h"

#include "../include/indexed_adjacent_list.h"
#include "../handle.h"

#include "property/type.h"
#include "property/topology.h"
#include "topology/adjacentlist.h"
#include "topology/structure.h"
#include "index/internal_id.h"

#if defined (GRIN_ENABLE_ADJACENT_LIST_ITERATOR) && !defined(GRIN_ENABLE_ADJACENT_LIST_ARRAY)

void _prepare_cache_for_indexed_adjacent_list(GRIN_GRAPH g, GRIN_INDEXED_ADJACENT_LIST indexed_adj_list) {
    auto _indexed_adj_list = static_cast<GRIN_INDEXED_ADJACENT_LIST_T*>(indexed_adj_list);
    while (!grin_is_adjacent_list_end(g, _indexed_adj_list->iterator)) {
        auto dst_vertex = grin_get_neighbor_from_adjacent_list_iter(g, _indexed_adj_list->iterator);
        _indexed_adj_list->neighbors.push_back(dst_vertex);
        auto edge = grin_get_edge_from_adjacent_list_iter(g, _indexed_adj_list->iterator);
        _indexed_adj_list->edges.push_back(edge);
        grin_get_next_adjacent_list_iter(g, _indexed_adj_list->iterator);
    }
}

GRIN_INDEXED_ADJACENT_LIST grin_get_indexed_adjacent_list(GRIN_GRAPH g, GRIN_ADJACENT_LIST adj_list) {
    GRIN_INDEXED_ADJACENT_LIST_T* indexed_adj_list = new GRIN_INDEXED_ADJACENT_LIST_T();
    indexed_adj_list->iterator = grin_get_adjacent_list_begin(g, adj_list);
    indexed_adj_list->neighbors.clear();
    indexed_adj_list->edges.clear();
    indexed_adj_list->cache_built = false;
    return indexed_adj_list;
}

void grin_destroy_indexed_adjacent_list(GRIN_GRAPH g, GRIN_INDEXED_ADJACENT_LIST indexed_adj_list) {
    auto _indexed_adj_list = static_cast<GRIN_INDEXED_ADJACENT_LIST_T*>(indexed_adj_list);
    grin_destroy_adjacent_list_iter(g, _indexed_adj_list->iterator);
    for (auto idx = 0; idx < _indexed_adj_list->neighbors.size(); idx++) {
        grin_destroy_vertex(g, _indexed_adj_list->neighbors[idx]);
        grin_destroy_edge(g, _indexed_adj_list->edges[idx]);
    }
    _indexed_adj_list->neighbors.clear();
    _indexed_adj_list->edges.clear();
    delete _indexed_adj_list;
}

size_t grin_get_indexed_adjacent_list_size(GRIN_GRAPH g, GRIN_INDEXED_ADJACENT_LIST indexed_adj_list) {
    auto _indexed_adj_list = static_cast<GRIN_INDEXED_ADJACENT_LIST_T*>(indexed_adj_list);
    if (_indexed_adj_list->cache_built) {
        return _indexed_adj_list->neighbors.size();
    }
    _prepare_cache_for_indexed_adjacent_list(g, indexed_adj_list);
    _indexed_adj_list->cache_built = true;
    return _indexed_adj_list->neighbors.size();
}

GRIN_VERTEX grin_get_neighbor_from_indexed_adjacent_list(GRIN_GRAPH g, GRIN_INDEXED_ADJACENT_LIST indexed_adj_list, size_t index) {
    auto _indexed_adj_list = static_cast<GRIN_INDEXED_ADJACENT_LIST_T*>(indexed_adj_list);
    if (_indexed_adj_list->cache_built) {
        if (index >= _indexed_adj_list->neighbors.size()) {
            return GRIN_NULL_VERTEX;
        }
        return _indexed_adj_list->neighbors[index];
    }
    _prepare_cache_for_indexed_adjacent_list(g, indexed_adj_list);
    _indexed_adj_list->cache_built = true;
    if (index >= _indexed_adj_list->neighbors.size()) {
        return GRIN_NULL_VERTEX;
    }
    return _indexed_adj_list->neighbors[index];
}

GRIN_EDGE grin_get_edge_from_indexed_adjacent_list(GRIN_GRAPH g, GRIN_INDEXED_ADJACENT_LIST indexed_adj_list, size_t index) {
    auto _indexed_adj_list = static_cast<GRIN_INDEXED_ADJACENT_LIST_T*>(indexed_adj_list);
    if (_indexed_adj_list->cache_built) {
        if (index >= _indexed_adj_list->edges.size()) {
            return GRIN_NULL_EDGE;
        }
        return _indexed_adj_list->edges[index];
    }
    _indexed_adj_list->cache_built = true;
    _prepare_cache_for_indexed_adjacent_list(g, indexed_adj_list);
    if (index >= _indexed_adj_list->edges.size()) {
        return GRIN_NULL_EDGE;
    }
    return _indexed_adj_list->edges[index];
}

#endif