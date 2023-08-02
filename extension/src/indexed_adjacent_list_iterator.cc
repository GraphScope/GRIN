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

#include "/opt/wanglei/dev/GART/interfaces/grin/src/predefine.h"
#include "../include/indexed_adjacent_list_iterator.h"
#include "../handle.h"

#include "property/type.h"
#include "topology/adjacentlist.h"
#include "index/internal_id.h"


bool grin_adj_list_cache_init = false;

typedef struct GRIN_ADJACENT_LIST_CACHE_T {
    std::vector<std::vector<std::vector<std::vector<int64_t>>>> adj_list_cache;
    // vertex_type -> edge_type -->src internal_id --> dst internal_id
    std::vector<std::vector<std::vector<uint8_t>>> valid_vertex;
    std::vector<std::vector<std::vector<uint8_t>>> dst_vertex_type;
} GRIN_ADJACENT_LIST_CACHE_T;

GRIN_ADJACENT_LIST_CACHE_T* grin_adj_list_cache;

void grin_init_adj_list_cache(GRIN_GRAPH g) {
    if (!grin_adj_list_cache_init) {
        grin_adj_list_cache = new GRIN_ADJACENT_LIST_CACHE_T();
        auto vtl = grin_get_vertex_type_list(g);
        auto vertex_type_num = grin_get_vertex_type_list_size(g, vtl);
        grin_adj_list_cache->adj_list_cache.resize(vertex_type_num);
        grin_adj_list_cache->valid_vertex.resize(vertex_type_num);
        grin_adj_list_cache->dst_vertex_type.resize(vertex_type_num);
        auto etl = grin_get_edge_type_list(g);
        auto edge_type_num = grin_get_edge_type_list_size(g, etl);
        for (auto idx = 0; idx < vertex_type_num; idx++) {
            grin_adj_list_cache->adj_list_cache[idx].resize(edge_type_num);
            grin_adj_list_cache->valid_vertex[idx].resize(edge_type_num);
            grin_adj_list_cache->dst_vertex_type[idx].resize(edge_type_num);
            size_t begin = grin_get_vertex_internal_id_lower_bound_by_type(g, idx);
            size_t end = grin_get_vertex_internal_id_upper_bound_by_type(g, idx);
            size_t cache_size = end - begin;
            for (auto edge_type_idx = 0; edge_type_idx < edge_type_num; edge_type_idx++) {
                grin_adj_list_cache->adj_list_cache[idx][edge_type_idx].resize(cache_size);
                grin_adj_list_cache->valid_vertex[idx][edge_type_idx].resize(cache_size, 0);
                grin_adj_list_cache->dst_vertex_type[idx][edge_type_idx].resize(cache_size, 0);
            }
        }
        grin_adj_list_cache_init = true;
        grin_destroy_vertex_type_list(g, vtl);
        grin_destroy_edge_type_list(g, etl);
    }
}


// #if defined (GRIN_ENABLE_ADJACENT_LIST_ITERATOR) && !defined(GRIN_ENABLE_ADJACENT_LIST_ARRAY)
GRIN_INDEXED_ADJACENT_LIST_ITERATOR grin_get_vertex_indexed_adjacent_list_iterator_by_edge_type(GRIN_GRAPH g, GRIN_DIRECTION dir, GRIN_VERTEX v, GRIN_EDGE_TYPE et) {
    GRIN_INDEXED_ADJACENT_LIST_ITERATOR_T* iter = new GRIN_INDEXED_ADJACENT_LIST_ITERATOR_T();
    iter->src = v;
    GRIN_ADJACENT_LIST adj_list = grin_get_adjacent_list_by_edge_type(g, dir, v, et);
    iter->iterator = grin_get_adjacent_list_begin(g, adj_list);
    iter->direction = dir;
    iter->edge_type = et;
    grin_destroy_adjacent_list(g, adj_list);
    return iter;
}

void grin_destroy_vertex_indexed_adjacent_list_iterator(GRIN_GRAPH g, GRIN_INDEXED_ADJACENT_LIST_ITERATOR iter) {
    auto _iter = static_cast<GRIN_INDEXED_ADJACENT_LIST_ITERATOR_T*>(iter);
    grin_destroy_adjacent_list_iter(g, _iter->iterator);
    grin_destroy_edge_type(g, _iter->edge_type);
    grin_destroy_vertex(g, _iter->src);
    delete _iter;
}

size_t grin_get_indexed_adjacent_list_iterator_size(GRIN_GRAPH g, GRIN_INDEXED_ADJACENT_LIST_ITERATOR iter) {
    grin_init_adj_list_cache(g);
    auto _iter = static_cast<GRIN_INDEXED_ADJACENT_LIST_ITERATOR_T*>(iter);
    GRIN_VERTEX src = _iter->src;
    GRIN_VERTEX_TYPE src_type = grin_get_vertex_type(g, src);
    GRIN_EDGE_TYPE edge_type = _iter->edge_type;
    auto internal_id = grin_get_vertex_internal_id_by_type(g, src_type, src);
    auto cache_loc = internal_id - grin_get_vertex_internal_id_lower_bound_by_type(g, src_type);
    if (grin_adj_list_cache->valid_vertex[src_type][edge_type][cache_loc] == 1) {
        return grin_adj_list_cache->adj_list_cache[src_type][edge_type][cache_loc].size();
    } 
    // update cache
    size_t result = 0;
    grin_adj_list_cache->adj_list_cache[src_type][edge_type][cache_loc].clear();
    grin_adj_list_cache->valid_vertex[src_type][edge_type][cache_loc] = 1;
    while (!grin_is_adjacent_list_end(g, _iter->iterator)) {
        result++;
        auto dst_vertex = grin_get_neighbor_from_adjacent_list_iter(g, _iter->iterator);
        GRIN_VERTEX_TYPE dst_type = grin_get_vertex_type(g, dst_vertex);
        auto dst_internal_id = grin_get_vertex_internal_id_by_type(g, dst_type, dst_vertex);
        grin_adj_list_cache->adj_list_cache[src_type][edge_type][cache_loc].push_back(dst_internal_id);
        grin_adj_list_cache->dst_vertex_type[src_type][edge_type][cache_loc].push_back(dst_type);
        grin_get_next_adjacent_list_iter(g, _iter->iterator);
        grin_destroy_vertex_type(g, dst_type);
    }
    grin_destroy_vertex_type(g, src_type);
    return result;
}

GRIN_VERTEX grin_get_neighbor_from_indexed_adjacent_list_iterator(GRIN_GRAPH g, GRIN_INDEXED_ADJACENT_LIST_ITERATOR iter, size_t index) {
    grin_init_adj_list_cache(g);
    auto _iter = static_cast<GRIN_INDEXED_ADJACENT_LIST_ITERATOR_T*>(iter);
    GRIN_VERTEX src = _iter->src;
    GRIN_VERTEX_TYPE src_type = grin_get_vertex_type(g, src);
    auto internal_id = grin_get_vertex_internal_id_by_type(g, src_type, src);
    auto cache_loc = internal_id - grin_get_vertex_internal_id_lower_bound_by_type(g, src_type);
    if (grin_adj_list_cache->valid_vertex[src_type][cache_loc] == 1) {
        auto dst_internal_id = grin_adj_list_cache->adj_list_cache[src_type][cache_loc][index];
        auto dst_type = grin_adj_list_cache->dst_vertex_type[src_type][cache_loc][index];
        GRIN_VERTEX dst_vertex = grin_get_vertex_by_internal_id_by_type(g, dst_type, dst_internal_id);
        return dst_vertex;
    } 
    // update cache
    grin_adj_list_cache->adj_list_cache[src_type][edge_type][cache_loc].clear();
    grin_adj_list_cache->valid_vertex[src_type][edge_type][cache_loc] = 1;
    while (!grin_is_adjacent_list_end(g, _iter->iterator)) {
        auto dst_vertex = grin_get_neighbor_from_adjacent_list_iter(g, _iter->iterator);
        GRIN_VERTEX_TYPE dst_type = grin_get_vertex_type(g, dst_vertex);
        auto dst_internal_id = grin_get_vertex_internal_id_by_type(g, dst_type, dst_vertex);
        grin_adj_list_cache->adj_list_cache[src_type][edge_type][cache_loc].push_back(dst_internal_id);
        grin_adj_list_cache->dst_vertex_type[src_type][edge_type][cache_loc].push_back(dst_type);
        grin_get_next_adjacent_list_iter(g, _iter->iterator);
        grin_destroy_vertex_type(g, dst_type);
    }
    grin_destroy_vertex_type(g, src_type);
    auto dst_internal_id = grin_adj_list_cache->adj_list_cache[src_type][cache_loc][index];
    auto dst_type = grin_adj_list_cache->dst_vertex_type[src_type][cache_loc][index];
    GRIN_VERTEX dst_vertex = grin_get_vertex_by_internal_id_by_type(g, dst_type, dst_internal_id);
    return dst_vertex;
}

GRIN_EDGE grin_get_edge_from_indexed_adjacent_list_iterator(GRIN_GRAPH, GRIN_INDEXED_ADJACENT_LIST_ITERATOR, size_t);
// #endif