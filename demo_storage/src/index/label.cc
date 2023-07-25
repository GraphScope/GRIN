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

#if defined(GRIN_WITH_VERTEX_LABEL) || defined(GRIN_WITH_EDGE_LABEL)
size_t grin_get_label_list_size(GRIN_GRAPH g, GRIN_LABEL_LIST ll) {
  auto _ll = static_cast<GRIN_LABEL_LIST_T*>(ll);
  return _ll->size();
}

GRIN_LABEL grin_get_label_from_list(GRIN_GRAPH g, GRIN_LABEL_LIST ll,
                                    size_t idx) {
  auto _ll = static_cast<GRIN_LABEL_LIST_T*>(ll);
  if (idx >= _ll->size()) {
    return GRIN_NULL_LABEL;
  }
  return _ll->at(idx);
}

GRIN_LABEL grin_get_label_by_name(GRIN_GRAPH g, const char* name) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto idx = _g->GetLabelId(std::string(name));
  if (idx == -1) {
    return GRIN_NULL_LABEL;
  }
  return idx;
}

const char* grin_get_label_name(GRIN_GRAPH g, GRIN_LABEL label) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  if (label < _g->GetVertexLabelNum()) {
    return _g->GetVertexLabelName(label).c_str();
  } else if (label < _g->GetVertexLabelNum() + _g->GetEdgeLabelNum()) {
    return _g->GetEdgeLabelName(label - _g->GetVertexLabelNum()).c_str();
  } else {
    return nullptr;
  }
}

void grin_destroy_label(GRIN_GRAPH g, GRIN_LABEL label) { return; }

void grin_destroy_label_list(GRIN_GRAPH g, GRIN_LABEL_LIST ll) {
  auto _ll = static_cast<GRIN_LABEL_LIST_T*>(ll);
  delete _ll;
}
#endif

#ifdef GRIN_WITH_VERTEX_LABEL
GRIN_LABEL_LIST grin_get_vertex_label_list(GRIN_GRAPH g) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto ll = new GRIN_LABEL_LIST_T();
  for (auto i = 0; i < _g->GetVertexLabelNum(); ++i) {
    ll->push_back(i);
  }
  return ll;
}

GRIN_LABEL_LIST grin_get_label_list_by_vertex(GRIN_GRAPH g, GRIN_VERTEX v) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& _v = _g->GetVertex(v);
  auto ll = new GRIN_LABEL_LIST_T();
  auto& labels = _v.GetLabels();
  for (auto& label : labels) {
    ll->push_back(_g->GetVertexLabelId(label));
  }
  return ll;
}
#endif

#if defined(GRIN_WITH_VERTEX_LABEL) && !defined(GRIN_WITH_VERTEX_PROPERTY)
GRIN_VERTEX_LIST grin_get_vertex_list_by_label(GRIN_GRAPH, GRIN_LABEL);
#endif

#if defined(GRIN_WITH_VERTEX_LABEL) && defined(GRIN_WITH_VERTEX_PROPERTY)
GRIN_VERTEX_LIST grin_get_vertex_list_by_type_by_label(GRIN_GRAPH g,
                                                       GRIN_VERTEX_TYPE vtype,
                                                       GRIN_LABEL label) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  if (vtype >= _g->GetVertexTypeNum())
    return GRIN_NULL_VERTEX_LIST;
  auto vl = new GRIN_VERTEX_LIST_T(vtype, ALL_PARTITION, 0, label);
  return vl;
}

GRIN_VERTEX_TYPE_LIST grin_get_vertex_type_list_by_label(GRIN_GRAPH g,
                                                         GRIN_LABEL label) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto vtl = new GRIN_VERTEX_TYPE_LIST_T();
  auto& vtypes = _g->GetVertexTypesByLabel(label);
  for (auto& vtype : vtypes) {
    vtl->push_back(vtype);
  }
  return vtl;
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

GRIN_LABEL_LIST grin_get_label_list_by_edge(GRIN_GRAPH g, GRIN_EDGE e) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto& _e = _g->GetEdge(e);
  auto ll = new GRIN_LABEL_LIST_T();
  auto& labels = _e.GetLabels();
  for (auto& label : labels) {
    ll->push_back(_g->GetEdgeLabelId(label) + _g->GetVertexLabelNum());
  }
  return ll;
}
#endif

#if defined(GRIN_WITH_EDGE_LABEL) && !defined(GRIN_WITH_EDGE_PROPERTY)
GRIN_EDGE_LIST grin_get_edge_list_by_label(GRIN_GRAPH, GRIN_LABEL);
#endif

#if defined(GRIN_WITH_EDGE_LABEL) && defined(GRIN_WITH_EDGE_PROPERTY)
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

GRIN_EDGE_TYPE_LIST grin_get_edge_type_list_by_label(GRIN_GRAPH g,
                                                     GRIN_LABEL label) {
  auto _g = static_cast<GRIN_GRAPH_T*>(g);
  auto etl = new GRIN_EDGE_TYPE_LIST_T();
  auto& etypes = _g->GetEdgeTypesByLabel(label - _g->GetVertexLabelNum());
  for (auto& etype : etypes) {
    etl->push_back(etype);
  }
  return etl;
}
#endif
