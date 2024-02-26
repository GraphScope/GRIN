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
#include "index/order.h"

#ifdef GRIN_ASSUME_ALL_VERTEX_LIST_SORTED
bool grin_smaller_vertex(GRIN_GRAPH g, GRIN_VERTEX v1, GRIN_VERTEX v2) {
  return v1 < v2;
}
#endif

#if defined(GRIN_ASSUME_ALL_VERTEX_LIST_SORTED) && \
    defined(GRIN_ENABLE_VERTEX_LIST_ARRAY)
size_t grin_get_position_of_vertex_from_sorted_list(GRIN_GRAPH g,
                                                    GRIN_VERTEX_LIST vl,
                                                    GRIN_VERTEX v) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto _vl = static_cast<GRIN_VERTEX_LIST_T*>(vl);
  auto vtype = DEMO_STORAGE_NAMESPACE::get_type_id_from_gid(v);
  auto vid = DEMO_STORAGE_NAMESPACE::get_id_from_gid(v);
  if (vtype != _vl->type_id) {
    return -1;
  }
  if (_vl->label_id != GRIN_NULL_LABEL) {
    return _g->GetVertexPositionInTypeAndLabel(vtype, _vl->label_id, v);
  }
  if (_vl->partition_type == ALL_PARTITION) {
    return vid;
  } else if (_vl->partition_type == ONE_PARTITION) {
    auto partition_id = _g->GetMasterPartitionIdFromVertexGid(v);
    auto partition_num = _g->GetPartitionNum();
    if (partition_id != _vl->partition_id) {
      return -1;
    }
    return vid / partition_num;
  } else if (_vl->partition_type == ALL_BUT_ONE_PARTITION) {
    auto partition_id = _g->GetMasterPartitionIdFromVertexGid(v);
    auto partition_num = _g->GetPartitionNum();
    if (partition_id == _vl->partition_id) {
      return -1;
    }
    size_t pos =
        (vid / partition_num) * (partition_num - 1) + vid % partition_num;
    if (partition_id > _vl->partition_id) {
      pos -= 1;
    }
    return pos;
  }
  return -1;
}
#endif
