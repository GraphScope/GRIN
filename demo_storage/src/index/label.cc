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
#include "index/label.h"

#ifdef GRIN_WITH_VERTEX_LABEL
GRIN_LABEL_LIST grin_get_vertex_label_list(GRIN_GRAPH g) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto ll = new GRIN_LABEL_LIST_T();
  for (auto i = 0; i < _g->GetVertexLabelNum(); ++i) {
    ll->push_back(i);
  }
  return ll;
}
#endif

#if defined(GRIN_WITH_VERTEX_LABEL) && !defined(GRIN_ENABLE_SCHEMA)
GRIN_VERTEX_LIST grin_get_vertex_list_by_label(GRIN_GRAPH, GRIN_LABEL);
#endif

#if defined(GRIN_WITH_VERTEX_LABEL) && defined(GRIN_ENABLE_SCHEMA)
GRIN_VERTEX_LIST grin_get_vertex_list_by_type_by_label(GRIN_GRAPH g,
                                                       GRIN_VERTEX_TYPE vtype,
                                                       GRIN_LABEL label) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  if (vtype >= _g->GetVertexTypeNum())
    return GRIN_NULL_VERTEX_LIST;
  auto vl = new GRIN_VERTEX_LIST_T(vtype, ALL_PARTITION, 0, label);
  return vl;
}
#endif

#ifdef GRIN_WITH_EDGE_LABEL
GRIN_LABEL_LIST grin_get_edge_label_list(GRIN_GRAPH g) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto ll = new GRIN_LABEL_LIST_T();
  for (auto i = 0; i < _g->GetEdgeLabelNum(); ++i) {
    ll->push_back(i + _g->GetVertexLabelNum());
  }
  return ll;
}
#endif

#if defined(GRIN_WITH_EDGE_LABEL) && !defined(GRIN_ENABLE_SCHEMA)
GRIN_EDGE_LIST grin_get_edge_list_by_label(GRIN_GRAPH, GRIN_LABEL);
#endif

#if defined(GRIN_WITH_EDGE_LABEL) && defined(GRIN_ENABLE_SCHEMA)
GRIN_EDGE_LIST grin_get_edge_list_by_type_by_label(GRIN_GRAPH g,
                                                   GRIN_EDGE_TYPE etype,
                                                   GRIN_LABEL label) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  if (etype >= _g->GetEdgeTypeNum())
    return GRIN_NULL_EDGE_LIST;
  auto el = new GRIN_EDGE_LIST_T(etype, ALL_PARTITION, 0,
                                 label - _g->GetVertexLabelNum());
  return el;
}
#endif
