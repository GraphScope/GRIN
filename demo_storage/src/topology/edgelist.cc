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
#include "topology/edgelist.h"

#if defined(GRIN_ENABLE_EDGE_LIST) && !defined(GRIN_WITH_EDGE_PROPERTY)
GRIN_EDGE_LIST grin_get_edge_list(GRIN_GRAPH);
#endif

#ifdef GRIN_ENABLE_EDGE_LIST
void grin_destroy_edge_list(GRIN_GRAPH g, GRIN_EDGE_LIST el) {
  auto _el = static_cast<GRIN_EDGE_LIST_T*>(el);
  delete _el;
}
#endif

#ifdef GRIN_ENABLE_EDGE_LIST_ARRAY
size_t grin_get_edge_list_size(GRIN_GRAPH g, GRIN_EDGE_LIST el) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _el = static_cast<GRIN_EDGE_LIST_T*>(el);
  auto etype = _el->type_id;
  auto label = _el->label_id;
  if (etype >= _g->GetEdgeTypeNum())
    return GRIN_NULL_SIZE;

  if (label != GRIN_NULL_LABEL) {
    return _g->GetEdgeNumByLabel(etype, label);
  }

  if (_el->partition_type == ALL_PARTITION) {
    return _g->GetEdgeNum(etype);
  } else if (_el->partition_type == ONE_PARTITION) {
    return _g->GetPartitionedEdgeNum(etype, _el->partition_id);
  } else if (_el->partition_type == ALL_BUT_ONE_PARTITION) {
    return _g->GetEdgeNum(etype) -
           _g->GetPartitionedEdgeNum(etype, _el->partition_id);
  }

  return GRIN_NULL_SIZE;
}

GRIN_EDGE grin_get_edge_from_list(GRIN_GRAPH g, GRIN_EDGE_LIST el, size_t idx) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _el = static_cast<GRIN_EDGE_LIST_T*>(el);
  auto etype = _el->type_id;
  auto label = _el->label_id;
  auto num = _g->GetEdgeNum(etype);

  if (label != GRIN_NULL_LABEL) {
    auto& edges = _g->GetEdgeIdsByLabel(etype, label);
    if (idx < edges.size()) {
      return edges[idx];
    } else {
      return GRIN_NULL_EDGE;
    }
  }

  if (_el->partition_type == ALL_PARTITION) {
    if (idx < num) {
      return DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(etype,
                                                                      idx);
    } else {
      return GRIN_NULL_EDGE;
    }
  }

  auto partition_id = _el->partition_id;
  auto partition_num = _g->GetPartitionNum();
  auto partitioned_num = _g->GetPartitionedEdgeNum(etype, partition_id);

  if (_el->partition_type == ONE_PARTITION) {
    if (idx < partitioned_num) {
      auto _idx = idx * partition_num + partition_id;
      return DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(etype,
                                                                      _idx);
    } else {
      return GRIN_NULL_EDGE;
    }
  }
  if (_el->partition_type == ALL_BUT_ONE_PARTITION) {
    if (idx < num - partitioned_num) {
      auto _idx = idx + idx / (partition_num - 1);
      if (idx % (partition_num - 1) >= partition_id)
        _idx++;
      return DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(etype,
                                                                      _idx);
    } else {
      return GRIN_NULL_EDGE;
    }
  }
  return GRIN_NULL_EDGE;
}
#endif

#ifdef GRIN_ENABLE_EDGE_LIST_ITERATOR
GRIN_EDGE_LIST_ITERATOR grin_get_edge_list_begin(GRIN_GRAPH g,
                                                 GRIN_EDGE_LIST el) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _el = static_cast<GRIN_EDGE_LIST_T*>(el);
  auto etype = _el->type_id;

  if (_el->partition_type == ALL_PARTITION) {
    return new GRIN_EDGE_LIST_ITERATOR_T(etype, ALL_PARTITION, 0,
                                         GRIN_NULL_LABEL, 0);
  }

  auto num = _g->GetEdgeNum(etype);
  auto partition_id = _el->partition_id;
  auto partition_num = _g->GetPartitionNum();

  if (_el->partition_type == ONE_PARTITION) {
    auto _offset = partition_id;
    if (_offset >= num)
      _offset = -1;
    return new GRIN_EDGE_LIST_ITERATOR_T(etype, ONE_PARTITION, partition_id,
                                         GRIN_NULL_LABEL, _offset);
  }

  if (_el->partition_type == ALL_BUT_ONE_PARTITION) {
    auto _offset = 0;
    if (_offset % partition_num == partition_id)
      _offset++;
    if (_offset >= num)
      _offset = -1;
    return new GRIN_EDGE_LIST_ITERATOR_T(
        etype, ALL_BUT_ONE_PARTITION, partition_id, GRIN_NULL_LABEL, _offset);
  }

  return GRIN_NULL_EDGE_LIST_ITERATOR;
}

void grin_destroy_edge_list_iter(GRIN_GRAPH g, GRIN_EDGE_LIST_ITERATOR eli) {
  auto _eli = static_cast<GRIN_EDGE_LIST_ITERATOR_T*>(eli);
  delete _eli;
}

void grin_get_next_edge_list_iter(GRIN_GRAPH g, GRIN_EDGE_LIST_ITERATOR eli) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _eli = static_cast<GRIN_EDGE_LIST_ITERATOR_T*>(eli);
  auto etype = _eli->type_id;
  auto num = _g->GetEdgeNum(etype);

  if (_eli->partition_type == ALL_PARTITION) {
    _eli->current_offset++;
    if (_eli->current_offset >= num) {
      _eli->current_offset = -1;
    }
    return;
  }

  auto partition_id = _eli->partition_id;
  auto partition_num = _g->GetPartitionNum();

  if (_eli->partition_type == ONE_PARTITION) {
    _eli->current_offset += partition_num;
    if (_eli->current_offset >= num) {
      _eli->current_offset = -1;
    }
    return;
  }

  if (_eli->partition_type == ALL_BUT_ONE_PARTITION) {
    _eli->current_offset++;
    if (_eli->current_offset % partition_num == partition_id) {
      _eli->current_offset++;
    }
    if (_eli->current_offset >= num) {
      _eli->current_offset = -1;
    }
    return;
  }
}

bool grin_is_edge_list_end(GRIN_GRAPH g, GRIN_EDGE_LIST_ITERATOR eli) {
  if (eli == GRIN_NULL_EDGE_LIST_ITERATOR) {
    return true;
  }
  auto _eli = static_cast<GRIN_EDGE_LIST_ITERATOR_T*>(eli);
  return _eli->current_offset == -1;
}

GRIN_EDGE grin_get_edge_from_iter(GRIN_GRAPH g, GRIN_EDGE_LIST_ITERATOR eli) {
  auto _eli = static_cast<GRIN_EDGE_LIST_ITERATOR_T*>(eli);
  return DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(
      _eli->type_id, _eli->current_offset);
}
#endif
