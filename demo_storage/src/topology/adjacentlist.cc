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

#include "src/predefine.h"
// GRIN headers
#include "topology/adjacentlist.h"

#if defined(GRIN_ENABLE_ADJACENT_LIST) && !defined(GRIN_WITH_EDGE_PROPERTY)
GRIN_ADJACENT_LIST grin_get_adjacent_list(GRIN_GRAPH, GRIN_DIRECTION,
                                          GRIN_VERTEX);
#endif

#ifdef GRIN_ENABLE_ADJACENT_LIST
void grin_destroy_adjacent_list(GRIN_GRAPH g, GRIN_ADJACENT_LIST al) {
  auto _al = static_cast<GRIN_ADJACENT_LIST_T*>(al);
  delete _al;
}
#endif

#ifdef GRIN_ENABLE_ADJACENT_LIST_ARRAY
size_t grin_get_adjacent_list_size(GRIN_GRAPH g, GRIN_ADJACENT_LIST al) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _al = static_cast<GRIN_ADJACENT_LIST_T*>(al);
  auto vtype = _al->vtype_id;
  auto vid = _al->vid;
  auto etype = _al->etype_id;
  auto dir = _al->dir;
  auto partition_num = _g->GetPartitionNum();

  if (_al->partition_type == ALL_PARTITION) {
    auto num = 0;
    for (auto i = 0; i < partition_num; i++) {
      num += _g->GetAdjacentListSize(vtype, vid, etype, i, dir);
    }
    return num;
  }

  auto partition_id = _al->partition_id;
  if (_al->partition_type == ONE_PARTITION) {
    return _g->GetAdjacentListSize(vtype, vid, etype, partition_id, dir);
  }

  if (_al->partition_type == ALL_BUT_ONE_PARTITION) {
    auto num = 0;
    for (auto i = 0; i < partition_num; i++) {
      if (i != partition_id) {
        num += _g->GetAdjacentListSize(vtype, vid, etype, i, dir);
      }
    }
    return num;
  }

  return GRIN_NULL_SIZE;
}

GRIN_VERTEX grin_get_neighbor_from_adjacent_list(GRIN_GRAPH g,
                                                 GRIN_ADJACENT_LIST al,
                                                 size_t idx) {
  auto e = grin_get_edge_from_adjacent_list(g, al, idx);
  if (e == GRIN_NULL_EDGE) {
    return GRIN_NULL_VERTEX;
  }
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _al = static_cast<GRIN_ADJACENT_LIST_T*>(al);
  auto& edge = _g->GetEdge(e);
  auto v = DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(
      _al->vtype_id, _al->vid);
  if (edge.GetSource() == v) {
    return edge.GetDest();
  } else if (edge.GetDest() == v) {
    return edge.GetSource();
  } else {
    return GRIN_NULL_VERTEX;
  }
}

GRIN_EDGE grin_get_edge_from_adjacent_list(GRIN_GRAPH g, GRIN_ADJACENT_LIST al,
                                           size_t idx) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _al = static_cast<GRIN_ADJACENT_LIST_T*>(al);
  auto vtype = _al->vtype_id;
  auto vid = _al->vid;
  auto etype = _al->etype_id;
  auto dir = _al->dir;
  auto partition_num = _g->GetPartitionNum();
  size_t prefix = 0;
  for (auto i = 0; i < partition_num; i++) {
    auto size = _g->GetAdjacentListSize(vtype, vid, etype, i, dir);
    if (_al->partition_type == ONE_PARTITION && i != _al->partition_id) {
      size = 0;
    }
    if (_al->partition_type == ALL_BUT_ONE_PARTITION &&
        i == _al->partition_id) {
      size = 0;
    }
    if (idx >= prefix && idx < prefix + size) {
      auto& edges = _g->GetAdjacentList(vtype, vid, etype, i, dir);
      return edges[idx - prefix];
    }
    prefix += size;
  }
  return GRIN_NULL_EDGE;
}
#endif

#ifdef GRIN_ENABLE_ADJACENT_LIST_ITERATOR
GRIN_ADJACENT_LIST_ITERATOR grin_get_adjacent_list_begin(
    GRIN_GRAPH g, GRIN_ADJACENT_LIST al) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _al = static_cast<GRIN_ADJACENT_LIST_T*>(al);
  auto vtype = _al->vtype_id;
  auto vid = _al->vid;
  auto etype = _al->etype_id;
  auto dir = _al->dir;
  auto partition_id = _al->partition_id;
  auto partition_num = _g->GetPartitionNum();

  auto current_partition = 0;
  while (current_partition < partition_num) {
    auto size =
        _g->GetAdjacentListSize(vtype, vid, etype, current_partition, dir);
    if (_al->partition_type == ONE_PARTITION &&
        current_partition != partition_id) {
      size = 0;
    }
    if (_al->partition_type == ALL_BUT_ONE_PARTITION &&
        current_partition == partition_id) {
      size = 0;
    }
    if (size > 0) {
      return new GRIN_ADJACENT_LIST_ITERATOR_T(
          vtype, vid, dir, etype, _al->partition_type, partition_id,
          current_partition, 0);
    }
    current_partition++;
  }

  return new GRIN_ADJACENT_LIST_ITERATOR_T(vtype, vid, dir, etype,
                                           _al->partition_type, partition_id,
                                           current_partition, 0);
}

void grin_destroy_adjacent_list_iter(GRIN_GRAPH g,
                                     GRIN_ADJACENT_LIST_ITERATOR ali) {
  auto _ali = static_cast<GRIN_ADJACENT_LIST_ITERATOR_T*>(ali);
  delete _ali;
}

void grin_get_next_adjacent_list_iter(GRIN_GRAPH g,
                                      GRIN_ADJACENT_LIST_ITERATOR ali) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _ali = static_cast<GRIN_ADJACENT_LIST_ITERATOR_T*>(ali);
  auto vtype = _ali->vtype_id;
  auto vid = _ali->vid;
  auto etype = _ali->etype_id;
  auto dir = _ali->dir;
  auto partition_num = _g->GetPartitionNum();
  auto partition_id = _ali->partition_id;

  _ali->current_offset++;
  if (_ali->current_offset >= _g->GetAdjacentListSize(vtype, vid, etype,
                                                      _ali->current_partition,
                                                      dir)) {
    _ali->current_offset = 0;
    _ali->current_partition++;
    while (_ali->current_partition < partition_num) {
      auto size = _g->GetAdjacentListSize(vtype, vid, etype,
                                          _ali->current_partition, dir);
      if (_ali->partition_type == ONE_PARTITION &&
          _ali->current_partition != partition_id) {
        size = 0;
      }
      if (_ali->partition_type == ALL_BUT_ONE_PARTITION &&
          _ali->current_partition == partition_id) {
        size = 0;
      }
      if (size > 0) {
        return;
      }
      _ali->current_partition++;
    }
  }
}

bool grin_is_adjacent_list_end(GRIN_GRAPH g, GRIN_ADJACENT_LIST_ITERATOR ali) {
  if (ali == GRIN_NULL_ADJACENT_LIST_ITERATOR) {
    return true;
  }
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _ali = static_cast<GRIN_ADJACENT_LIST_ITERATOR_T*>(ali);
  return _ali->current_partition >= _g->GetPartitionNum();
}

GRIN_VERTEX grin_get_neighbor_from_adjacent_list_iter(
    GRIN_GRAPH g, GRIN_ADJACENT_LIST_ITERATOR ali) {
  auto e = grin_get_edge_from_adjacent_list_iter(g, ali);
  if (e == GRIN_NULL_EDGE) {
    return GRIN_NULL_VERTEX;
  }
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _ali = static_cast<GRIN_ADJACENT_LIST_ITERATOR_T*>(ali);
  auto& edge = _g->GetEdge(e);
  auto v = DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(
      _ali->vtype_id, _ali->vid);
  if (edge.GetSource() == v) {
    return edge.GetDest();
  } else if (edge.GetDest() == v) {
    return edge.GetSource();
  } else {
    return GRIN_NULL_VERTEX;
  }
}

GRIN_EDGE grin_get_edge_from_adjacent_list_iter(
    GRIN_GRAPH g, GRIN_ADJACENT_LIST_ITERATOR ali) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _ali = static_cast<GRIN_ADJACENT_LIST_ITERATOR_T*>(ali);
  auto& edges = _g->GetAdjacentList(_ali->vtype_id, _ali->vid, _ali->etype_id,
                                    _ali->current_partition, _ali->dir);
  if (_ali->current_offset >= edges.size()) {
    return GRIN_NULL_EDGE;
  }
  return edges[_ali->current_offset];
}
#endif
