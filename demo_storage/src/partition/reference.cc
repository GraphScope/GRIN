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

#include <sstream>

#include "src/predefine.h"
// GRIN headers
#include "partition/reference.h"

#ifdef GRIN_ENABLE_VERTEX_REF
GRIN_VERTEX_REF grin_get_vertex_ref_by_vertex(GRIN_GRAPH g, GRIN_VERTEX v) {
  return v;
}

void grin_destroy_vertex_ref(GRIN_GRAPH g, GRIN_VERTEX_REF vr) { return; }

GRIN_VERTEX grin_get_vertex_from_vertex_ref(GRIN_GRAPH g, GRIN_VERTEX_REF vr) {
  return vr;
}

GRIN_PARTITION grin_get_master_partition_from_vertex_ref(GRIN_GRAPH g,
                                                         GRIN_VERTEX_REF vr) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  return _g->GetMasterPartitionIdFromVertexGid(vr);
}

const char* grin_serialize_vertex_ref(GRIN_GRAPH g, GRIN_VERTEX_REF vr) {
  std::stringstream ss;
  ss << vr;
  int len = ss.str().length() + 1;
  char* out = new char[len];
  snprintf(out, len, "%s", ss.str().c_str());
  return out;
}

void grin_destroy_serialized_vertex_ref(GRIN_GRAPH g, const char* svr) {
  delete[] svr;
}

GRIN_VERTEX_REF grin_deserialize_to_vertex_ref(GRIN_GRAPH g, const char* svr) {
  std::stringstream ss(svr);
  long long int vr;  // NOLINT
  ss >> vr;
  return vr;
}

bool grin_is_master_vertex(GRIN_GRAPH g, GRIN_VERTEX v) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  return _g->GetMasterPartitionIdFromVertexGid(v) == _g->GetPartitionId();
}

bool grin_is_mirror_vertex(GRIN_GRAPH g, GRIN_VERTEX v) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  return _g->GetMasterPartitionIdFromVertexGid(v) != _g->GetPartitionId();
}
#endif

#ifdef GRIN_TRAIT_FAST_VERTEX_REF
long long int grin_serialize_vertex_ref_as_int64(GRIN_GRAPH g,  // NOLINT
                                                 GRIN_VERTEX_REF vr) {
  return vr;
}

GRIN_VERTEX_REF grin_deserialize_int64_to_vertex_ref(
    GRIN_GRAPH g,
    long long int fvr) {  // NOLINT
  return fvr;
}
#endif

#ifdef GRIN_TRAIT_MASTER_VERTEX_MIRROR_PARTITION_LIST
GRIN_PARTITION_LIST grin_get_master_vertex_mirror_partition_list(
    GRIN_GRAPH g, GRIN_VERTEX v) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto pid = _g->GetMasterPartitionIdFromVertexGid(v);
  if (pid != _g->GetPartitionId())
    return GRIN_NULL_PARTITION_LIST;
  auto pl = new GRIN_PARTITION_LIST_T();
  for (auto i = 0; i < _g->GetPartitionNum(); ++i) {
    if (i != pid)
      pl->push_back(i);
  }
  return pl;
}
#endif

#ifdef GRIN_TRAIT_MIRROR_VERTEX_MIRROR_PARTITION_LIST
GRIN_PARTITION_LIST grin_get_mirror_vertex_mirror_partition_list(
    GRIN_GRAPH g, GRIN_VERTEX v) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto pid = _g->GetMasterPartitionIdFromVertexGid(v);
  if (pid == _g->GetPartitionId())
    return GRIN_NULL_PARTITION_LIST;
  auto pl = new GRIN_PARTITION_LIST_T();
  for (auto i = 0; i < _g->GetPartitionNum(); ++i) {
    if (i != pid)
      pl->push_back(i);
  }
  return pl;
}
#endif

#ifdef GRIN_ENABLE_EDGE_REF
GRIN_EDGE_REF grin_get_edge_ref_by_edge(GRIN_GRAPH g, GRIN_EDGE e) { return e; }

void grin_destroy_edge_ref(GRIN_GRAPH g, GRIN_EDGE_REF er) { return; }

GRIN_EDGE grin_get_edge_from_edge_ref(GRIN_GRAPH g, GRIN_EDGE_REF er) {
  return er;
}

GRIN_PARTITION grin_get_master_partition_from_edge_ref(GRIN_GRAPH g,
                                                       GRIN_EDGE_REF er) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  return _g->GetMasterPartitionIdFromEdgeGid(er);
}

const char* grin_serialize_edge_ref(GRIN_GRAPH g, GRIN_EDGE_REF er) {
  std::stringstream ss;
  ss << er;
  int len = ss.str().length() + 1;
  char* out = new char[len];
  snprintf(out, len, "%s", ss.str().c_str());
  return out;
}

void grin_destroy_serialized_edge_ref(GRIN_GRAPH g, const char* ser) {
  delete[] ser;
}

GRIN_EDGE_REF grin_deserialize_to_edge_ref(GRIN_GRAPH g, const char* ser) {
  std::stringstream ss(ser);
  long long int er;  // NOLINT
  ss >> er;
  return er;
}

bool grin_is_master_edge(GRIN_GRAPH g, GRIN_EDGE e) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  return _g->GetMasterPartitionIdFromEdgeGid(e) == _g->GetPartitionId();
}

bool grin_is_mirror_edge(GRIN_GRAPH g, GRIN_EDGE e) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  return _g->GetMasterPartitionIdFromEdgeGid(e) != _g->GetPartitionId();
}
#endif

#ifdef GRIN_TRAIT_MASTER_EDGE_MIRROR_PARTITION_LIST
GRIN_PARTITION_LIST grin_get_master_edge_mirror_partition_list(GRIN_GRAPH g,
                                                               GRIN_EDGE e) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto pid = _g->GetMasterPartitionIdFromEdgeGid(e);
  if (pid != _g->GetPartitionId())
    return GRIN_NULL_PARTITION_LIST;
  auto pl = new GRIN_PARTITION_LIST_T();
  for (size_t i = 0; i < _g->GetPartitionNum(); ++i) {
    if (i != pid)
      pl->push_back(i);
  }
  return pl;
}
#endif

#ifdef GRIN_TRAIT_MIRROR_EDGE_MIRROR_PARTITION_LIST
GRIN_PARTITION_LIST grin_get_mirror_edge_mirror_partition_list(GRIN_GRAPH g,
                                                               GRIN_EDGE e) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto pid = _g->GetMasterPartitionIdFromEdgeGid(e);
  if (pid == _g->GetPartitionId())
    return GRIN_NULL_PARTITION_LIST;
  auto pl = new GRIN_PARTITION_LIST_T();
  for (size_t i = 0; i < _g->GetPartitionNum(); ++i) {
    if (i != pid)
      pl->push_back(i);
  }
  return pl;
}
#endif
