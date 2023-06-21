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

#include "list_chain.h"
#include "property/topology.h"
#include "property/type.h"
#include "topology/vertexlist.h"
#include "topology/adjacentlist.h"
#include "partition/topology.h"

#if defined(GRIN_ENABLE_VERTEX_LIST) && defined(GRIN_WITH_VERTEX_PROPERTY)
GRIN_VERTEX_LIST_CHAIN grin_get_vertex_list_chain_of_all_types(GRIN_GRAPH g) {
    GRIN_VERTEX_TYPE_LIST vtypes = grin_get_vertex_type_list(g);
    unsigned int vtype_num = grin_get_vertex_type_list_size(g, vtypes);
    GRIN_VERTEX_LIST_CHAIN vchain;
    vchain.lists = new GRIN_VERTEX_LIST[vtype_num];
    vchain.size = vtype_num;
    for (unsigned int i = 0; i < vtype_num; i++) {
        GRIN_VERTEX_TYPE vtype = grin_get_vertex_type_from_list(g, vtypes, i);
        vchain.lists[i] = grin_get_vertex_list_by_type(g, vtype);
    }
    return vchain;
}

void grin_destroy_vertex_list_chain(GRIN_GRAPH g, GRIN_VERTEX_LIST_CHAIN vchain) {
    for (unsigned int i = 0; i < vchain.size; i++) {
        grin_destroy_vertex_list(g, vchain.lists[i]);
    }
    delete[] vchain.lists;
}

GRIN_VERTEX_LIST_CHAIN_ITERATOR grin_get_vertex_list_chain_begin(GRIN_GRAPH g, GRIN_VERTEX_LIST_CHAIN vchain) {
    GRIN_VERTEX_LIST_CHAIN_ITERATOR iter;
    iter.iterators = new GRIN_VERTEX_LIST_ITERATOR[vchain.size];
    iter.size = vchain.size;
    iter.current = 0;
    for (unsigned int i = 0; i < vchain.size; i++) {
        iter.iterators[i] = grin_get_vertex_list_begin(g, vchain.lists[i]);
    }
    while (iter.current < iter.size && grin_is_vertex_list_end(g, iter.iterators[iter.current])) {
        iter.current++;
    }
    return iter;
}

void grin_destroy_vertex_list_chain_iter(GRIN_GRAPH g, GRIN_VERTEX_LIST_CHAIN_ITERATOR vchain_iter) {
    for (unsigned int i = 0; i < vchain_iter.size; i++) {
        grin_destroy_vertex_list_iter(g, vchain_iter.iterators[i]);
    }
    delete[] vchain_iter.iterators;
}

void grin_get_next_vertex_list_chain_iter(GRIN_GRAPH g, GRIN_VERTEX_LIST_CHAIN_ITERATOR vchain_iter) {
    grin_get_next_vertex_list_iter(g, vchain_iter.iterators[vchain_iter.current]);
    while (vchain_iter.current < vchain_iter.size && grin_is_vertex_list_end(g, vchain_iter.iterators[vchain_iter.current])) {
        vchain_iter.current++;
    }
}

bool grin_is_vertex_list_chain_end(GRIN_GRAPH g, GRIN_VERTEX_LIST_CHAIN_ITERATOR vchain_iter) {
    return vchain_iter.current >= vchain_iter.size;
}

GRIN_VERTEX grin_get_vertex_from_vertex_list_chain_iter(GRIN_GRAPH g, GRIN_VERTEX_LIST_CHAIN_ITERATOR vchain_iter) {
    GRIN_VERTEX_LIST_ITERATOR iter = vchain_iter.iterators[vchain_iter.current];
    return grin_get_vertex_from_iter(g, iter);
}
#endif

#if defined(GRIN_ENABLE_VERTEX_LIST) && defined(GRIN_WITH_VERTEX_PROPERTY) && defined(GRIN_TRAIT_SELECT_MASTER_FOR_VERTEX_LIST)
GRIN_VERTEX_LIST_CHAIN grin_get_vertex_list_chain_of_all_types_select_master(GRIN_GRAPH g) {
    GRIN_VERTEX_TYPE_LIST vtypes = grin_get_vertex_type_list(g);
    unsigned int vtype_num = grin_get_vertex_type_list_size(g, vtypes);
    GRIN_VERTEX_LIST_CHAIN vchain;
    vchain.lists = new GRIN_VERTEX_LIST[vtype_num];
    vchain.size = vtype_num;
    for (unsigned int i = 0; i < vtype_num; i++) {
        GRIN_VERTEX_TYPE vtype = grin_get_vertex_type_from_list(g, vtypes, i);
        vchain.lists[i] = grin_get_vertex_list_by_type_select_master(g, vtype);
    }
    return vchain;
}

GRIN_VERTEX_LIST_CHAIN grin_get_vertex_list_chain_of_all_types_select_mirror(GRIN_GRAPH g) {
    GRIN_VERTEX_TYPE_LIST vtypes = grin_get_vertex_type_list(g);
    unsigned int vtype_num = grin_get_vertex_type_list_size(g, vtypes);
    GRIN_VERTEX_LIST_CHAIN vchain;
    vchain.lists = new GRIN_VERTEX_LIST[vtype_num];
    vchain.size = vtype_num;
    for (unsigned int i = 0; i < vtype_num; i++) {
        GRIN_VERTEX_TYPE vtype = grin_get_vertex_type_from_list(g, vtypes, i);
        vchain.lists[i] = grin_get_vertex_list_by_type_select_mirror(g, vtype);
    }
    return vchain;
}
#endif

#if defined(GRIN_ENABLE_EDGE_LIST) && defined(GRIN_WITH_EDGE_PROPERTY)
GRIN_EDGE_LIST_CHAIN grin_get_edge_list_chain_of_all_types(GRIN_GRAPH);

void grin_destroy_edge_list_chain(GRIN_GRAPH, GRIN_EDGE_LIST_CHAIN);

GRIN_EDGE_LIST_CHAIN_ITERATOR grin_get_edge_list_chain_begin(GRIN_GRAPH, GRIN_EDGE_LIST_CHAIN);

void grin_destroy_edge_list_chain_iter(GRIN_GRAPH, GRIN_EDGE_LIST_CHAIN_ITERATOR);

void grin_get_next_edge_list_chain_iter(GRIN_GRAPH, GRIN_EDGE_LIST_CHAIN_ITERATOR);

bool grin_is_edge_list_chain_end(GRIN_GRAPH, GRIN_EDGE_LIST_CHAIN_ITERATOR);

GRIN_EDGE grin_get_edge_from_edge_list_chain_iter(GRIN_GRAPH, GRIN_EDGE_LIST_CHAIN_ITERATOR);
#endif

#if defined(GRIN_ENABLE_EDGE_LIST) && defined(GRIN_WITH_EDGE_PROPERTY) && defined(GRIN_TRAIT_SELECT_MASTER_FOR_EDGE_LIST)
GRIN_EDGE_LIST_CHAIN grin_get_edge_list_chain_of_all_types_select_master(GRIN_GRAPH);

GRIN_EDGE_LIST_CHAIN grin_get_edge_list_chain_of_all_types_select_mirror(GRIN_GRAPH);
#endif

#if defined(GRIN_ENABLE_ADJACENT_LIST) && defined(GRIN_WITH_EDGE_PROPERTY)
GRIN_ADJACENT_LIST_CHAIN grin_get_adjacent_list_chain_of_all_edge_types(GRIN_GRAPH g, GRIN_DIRECTION d, GRIN_VERTEX v) {
    GRIN_EDGE_TYPE_LIST etypes = grin_get_edge_type_list(g);
    unsigned int etype_num = grin_get_edge_type_list_size(g, etypes);
    GRIN_ADJACENT_LIST_CHAIN achain;
    achain.lists = new GRIN_ADJACENT_LIST[etype_num];
    achain.size = etype_num;
    for (unsigned int i = 0; i < etype_num; i++) {
        GRIN_EDGE_TYPE etype = grin_get_edge_type_from_list(g, etypes, i);
        achain.lists[i] = grin_get_adjacent_list_by_edge_type(g, d, v, etype);
    }
    return achain;
}

void grin_destroy_adjacent_list_chain(GRIN_GRAPH g, GRIN_ADJACENT_LIST_CHAIN achain) {
    for (unsigned int i = 0; i < achain.size; i++) {
        grin_destroy_adjacent_list(g, achain.lists[i]);
    }
    delete[] achain.lists;
}

GRIN_ADJACENT_LIST_CHAIN_ITERATOR grin_get_adjacent_list_chain_begin(GRIN_GRAPH g, GRIN_ADJACENT_LIST_CHAIN achain) {
    GRIN_ADJACENT_LIST_CHAIN_ITERATOR iter;
    iter.iterators = new GRIN_ADJACENT_LIST_ITERATOR[achain.size];
    iter.size = achain.size;
    iter.current = 0;
    for (unsigned int i = 0; i < achain.size; i++) {
        iter.iterators[i] = grin_get_adjacent_list_begin(g, achain.lists[i]);
    }
    while (iter.current < iter.size && grin_is_adjacent_list_end(g, iter.iterators[iter.current])) {
        iter.current++;
    }
    return iter;
}

void grin_destroy_adjacent_list_chain_iter(GRIN_GRAPH g, GRIN_ADJACENT_LIST_CHAIN_ITERATOR achain_iter) {
    for (unsigned int i = 0; i < achain_iter.size; i++) {
        grin_destroy_adjacent_list_iter(g, achain_iter.iterators[i]);
    }
    delete[] achain_iter.iterators;
}

void grin_get_next_adjacent_list_chain_iter(GRIN_GRAPH g, GRIN_ADJACENT_LIST_CHAIN_ITERATOR achain_iter) {
    grin_get_next_adjacent_list_iter(g, achain_iter.iterators[achain_iter.current]);
    while (achain_iter.current < achain_iter.size && grin_is_adjacent_list_end(g, achain_iter.iterators[achain_iter.current])) {
        achain_iter.current++;
    }
}

bool grin_is_adjacent_list_chain_end(GRIN_GRAPH g, GRIN_ADJACENT_LIST_CHAIN_ITERATOR achain_iter) {
    return achain_iter.current >= achain_iter.size;
}

GRIN_EDGE grin_get_edge_from_adjacent_list_chain_iter(GRIN_GRAPH g, GRIN_ADJACENT_LIST_CHAIN_ITERATOR achain_iter) {
    return grin_get_edge_from_adjacent_list_iter(g, achain_iter.iterators[achain_iter.current]);
}

GRIN_VERTEX grin_get_neighbor_from_adjacent_list_chain_iter(GRIN_GRAPH g, GRIN_ADJACENT_LIST_CHAIN_ITERATOR achain_iter) {
    return grin_get_neighbor_from_adjacent_list_iter(g, achain_iter.iterators[achain_iter.current]);
}
#endif
