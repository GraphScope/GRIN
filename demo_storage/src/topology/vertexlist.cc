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
#include "topology/vertexlist.h"

#if defined(GRIN_ENABLE_VERTEX_LIST) && !defined(GRIN_WITH_VERTEX_PROPERTY)
GRIN_VERTEX_LIST grin_get_vertex_list(GRIN_GRAPH);
#endif

#ifdef GRIN_ENABLE_VERTEX_LIST
void grin_destroy_vertex_list(GRIN_GRAPH g, GRIN_VERTEX_LIST vl) {
  auto _vl = static_cast<GRIN_VERTEX_LIST_T*>(vl);
  delete _vl;
}
#endif

#ifdef GRIN_ENABLE_VERTEX_LIST_ARRAY
size_t grin_get_vertex_list_size(GRIN_GRAPH g, GRIN_VERTEX_LIST vl) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _vl = static_cast<GRIN_VERTEX_LIST_T*>(vl);
  auto vtype = _vl->type_id;
  if (vtype >= _g->GetVertexTypeNum())
    GRIN_NULL_SIZE;

  if (_vl->partition_type == ALL_PARTITION) {
    return _g->GetVertexNum(vtype);
  } else if (_vl->partition_type == ONE_PARTITION) {
    return _g->GetPartitionedVertexNum(vtype, _vl->partition_id);
  } else if (_vl->partition_type == ALL_BUT_ONE_PARTITION) {
    return _g->GetVertexNum(vtype) -
           _g->GetPartitionedVertexNum(vtype, _vl->partition_id);
  }

  return GRIN_NULL_SIZE;
}

GRIN_VERTEX grin_get_vertex_from_list(GRIN_GRAPH g, GRIN_VERTEX_LIST vl,
                                      size_t idx) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _vl = static_cast<GRIN_VERTEX_LIST_T*>(vl);
  auto vtype = _vl->type_id;
  auto num = _g->GetVertexNum(vtype);

  if (_vl->partition_type == ALL_PARTITION) {
    if (idx < num) {
      return DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(vtype,
                                                                      idx);
    } else {
      return GRIN_NULL_VERTEX;
    }
  }

  auto partition_id = _vl->partition_id;
  auto partition_num = _g->GetPartitionNum();
  auto partitioned_num = _g->GetPartitionedVertexNum(vtype, partition_id);

  if (_vl->partition_type == ONE_PARTITION) {
    if (idx < partitioned_num) {
      auto _idx = idx * partition_num + partition_id;
      return DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(vtype,
                                                                      _idx);
    } else {
      return GRIN_NULL_VERTEX;
    }
  }

  if (_vl->partition_type == ALL_BUT_ONE_PARTITION) {
    if (idx < num - partitioned_num) {
      auto _idx = idx + idx / (partition_num - 1);
      if (idx % (partition_num - 1) >= partition_id)
        _idx++;
      return DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(vtype,
                                                                      _idx);
    } else {
      return GRIN_NULL_VERTEX;
    }
  }
  return GRIN_NULL_VERTEX;
}
#endif

#ifdef GRIN_ENABLE_VERTEX_LIST_ITERATOR
GRIN_VERTEX_LIST_ITERATOR grin_get_vertex_list_begin(GRIN_GRAPH g,
                                                     GRIN_VERTEX_LIST vl) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _vl = static_cast<GRIN_VERTEX_LIST_T*>(vl);
  auto vtype = _vl->type_id;

  if (_vl->partition_type == ALL_PARTITION) {
    return new GRIN_VERTEX_LIST_ITERATOR_T(vtype, ALL_PARTITION, 0, 0);
  }

  auto num = _g->GetVertexNum(vtype);
  auto partition_id = _vl->partition_id;
  auto partition_num = _g->GetPartitionNum();

  if (_vl->partition_type == ONE_PARTITION) {
    auto _offset = partition_id;
    if (_offset >= num)
      _offset = -1;
    return new GRIN_VERTEX_LIST_ITERATOR_T(vtype, ONE_PARTITION, partition_id,
                                           _offset);
  }

  if (_vl->partition_type == ALL_BUT_ONE_PARTITION) {
    auto _offset = 0;
    if (_offset % partition_num == partition_id)
      _offset++;
    if (_offset >= num)
      _offset = -1;
    return new GRIN_VERTEX_LIST_ITERATOR_T(vtype, ALL_BUT_ONE_PARTITION,
                                           partition_id, _offset);
  }

  return GRIN_NULL_VERTEX_LIST_ITERATOR;
}

void grin_destroy_vertex_list_iter(GRIN_GRAPH g,
                                   GRIN_VERTEX_LIST_ITERATOR vli) {
  auto _vli = static_cast<GRIN_VERTEX_LIST_ITERATOR_T*>(vli);
  delete _vli;
}

void grin_get_next_vertex_list_iter(GRIN_GRAPH g,
                                    GRIN_VERTEX_LIST_ITERATOR vli) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _vli = static_cast<GRIN_VERTEX_LIST_ITERATOR_T*>(vli);
  auto vtype = _vli->type_id;
  auto num = _g->GetVertexNum(vtype);

  if (_vli->partition_type == ALL_PARTITION) {
    _vli->current_offset++;
    if (_vli->current_offset >= num) {
      _vli->current_offset = -1;
    }
    return;
  }

  auto partition_id = _vli->partition_id;
  auto partition_num = _g->GetPartitionNum();

  if (_vli->partition_type == ONE_PARTITION) {
    _vli->current_offset += partition_num;
    if (_vli->current_offset >= num) {
      _vli->current_offset = -1;
    }
    return;
  }

  if (_vli->partition_type == ALL_BUT_ONE_PARTITION) {
    _vli->current_offset++;
    if (_vli->current_offset % partition_num == partition_id) {
      _vli->current_offset++;
    }
    if (_vli->current_offset >= num) {
      _vli->current_offset = -1;
    }
    return;
  }
}

bool grin_is_vertex_list_end(GRIN_GRAPH g, GRIN_VERTEX_LIST_ITERATOR vli) {
  if (vli == GRIN_NULL_VERTEX_LIST_ITERATOR) {
    return true;
  }
  auto _vli = static_cast<GRIN_VERTEX_LIST_ITERATOR_T*>(vli);
  return _vli->current_offset == -1;
}

GRIN_VERTEX grin_get_vertex_from_iter(GRIN_GRAPH g,
                                      GRIN_VERTEX_LIST_ITERATOR vli) {
  auto _vli = static_cast<GRIN_VERTEX_LIST_ITERATOR_T*>(vli);
  return DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(
      _vli->type_id, _vli->current_offset);
}
#endif
