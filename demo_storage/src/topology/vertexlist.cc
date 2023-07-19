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
  auto label = _vl->label_id;
  if (vtype >= _g->GetVertexTypeNum())
    GRIN_NULL_SIZE;

  if (label != GRIN_NULL_LABEL) {
    return _g->GetVertexNumByLabel(vtype, label);
  }

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
  auto label = _vl->label_id;
  auto num = _g->GetVertexNum(vtype);

  if (label != GRIN_NULL_LABEL) {
    auto& vertices = _g->GetVertexIdsByLabel(vtype, label);
    if (idx < vertices.size()) {
      return vertices[idx];
    } else {
      return GRIN_NULL_VERTEX;
    }
  }

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
  auto label = _vl->label_id;

  if (_vl->partition_type == ALL_PARTITION) {
    return new GRIN_VERTEX_LIST_ITERATOR_T(vtype, ALL_PARTITION, 0, label, 0);
  }

  auto num = _g->GetVertexNum(vtype);
  auto partition_id = _vl->partition_id;
  auto partition_num = _g->GetPartitionNum();

  if (_vl->partition_type == ONE_PARTITION) {
    auto _offset = partition_id;
    if (_offset >= num)
      _offset = -1;
    return new GRIN_VERTEX_LIST_ITERATOR_T(vtype, ONE_PARTITION, partition_id,
                                           GRIN_NULL_LABEL, _offset);
  }

  if (_vl->partition_type == ALL_BUT_ONE_PARTITION) {
    auto _offset = 0;
    if (_offset % partition_num == partition_id)
      _offset++;
    if (_offset >= num)
      _offset = -1;
    return new GRIN_VERTEX_LIST_ITERATOR_T(
        vtype, ALL_BUT_ONE_PARTITION, partition_id, GRIN_NULL_LABEL, _offset);
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
  auto label = _vli->label_id;
  auto num = label == GRIN_NULL_LABEL ? _g->GetVertexNum(vtype)
                                      : _g->GetVertexNumByLabel(vtype, label);

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
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _vli = static_cast<GRIN_VERTEX_LIST_ITERATOR_T*>(vli);
  if (_vli->label_id != GRIN_NULL_LABEL) {
    return _g->GetVertexIdsByLabel(_vli->type_id,
                                   _vli->label_id)[_vli->current_offset];
  } else {
    return DEMO_STORAGE_NAMESPACE::generate_gid_from_type_id_and_id(
        _vli->type_id, _vli->current_offset);
  }
}
#endif
