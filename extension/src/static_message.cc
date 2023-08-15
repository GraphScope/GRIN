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

#include <google/protobuf/util/json_util.h>

#include "predefine.h"
#include "list_chain.h"
#include "storage.pb.h"

const char* grin_get_static_storage_feature_msg() {
  grin::StorageFeatures s;
  s.set_grin_version("0.1.4");

{
  auto storage_feature = s.add_features();
  // topology
  auto feature = storage_feature->mutable_topology_feature();

#ifdef GRIN_ASSUME_HAS_DIRECTED_GRAPH
  feature->set_grin_assume_has_directed_graph(true);
#endif

#ifdef GRIN_ASSUME_HAS_UNDIRECTED_GRAPH
  feature->set_grin_assume_has_undirected_graph(true);
#endif

#ifdef GRIN_ASSUME_HAS_MULTI_EDGE_GRAPH
  feature->set_grin_assume_has_multi_edge_graph(true);
#endif

#ifdef GRIN_WITH_VERTEX_DATA
  feature->set_grin_with_vertex_data(true);
#endif

#ifdef GRIN_WITH_EDGE_DATA
  feature->set_grin_with_edge_data(true);
#endif

#ifdef GRIN_ENABLE_VERTEX_LIST_ARRAY
  #ifndef GRIN_ENABLE_VERTEX_LIST
  LOG(ERROR) << "GRIN_ENABLE_VERTEX_LIST_ARRAY requires GRIN_ENABLE_VERTEX_LIST"
  #endif
  feature->add_vertex_list_retrievals(grin::ListRetrieval::LR_ARRAY_LIKE);
#endif

#ifdef GRIN_ENABLE_VERTEX_LIST_ITERATOR
  #ifndef GRIN_ENABLE_VERTEX_LIST
  LOG(ERROR) << "GRIN_ENABLE_VERTEX_LIST_ITERATOR requires GRIN_ENABLE_VERTEX_LIST"
  #endif
  feature->add_vertex_list_retrievals(grin::ListRetrieval::LR_ITERATOR);
#endif

#ifdef GRIN_ENABLE_EDGE_LIST_ARRAY
  #ifndef GRIN_ENABLE_EDGE_LIST
  LOG(ERROR) << "GRIN_ENABLE_EDGE_LIST_ARRAY requires GRIN_ENABLE_EDGE_LIST"
  #endif
  feature->add_edge_list_retrievals(grin::ListRetrieval::LR_ARRAY_LIKE);
#endif

#ifdef GRIN_ENABLE_EDGE_LIST_ITERATOR
  #ifndef GRIN_ENABLE_EDGE_LIST
  LOG(ERROR) << "GRIN_ENABLE_EDGE_LIST_ITERATOR requires GRIN_ENABLE_EDGE_LIST"
  #endif
  feature->add_edge_list_retrievals(grin::ListRetrieval::LR_ITERATOR);
#endif

#ifdef GRIN_ENABLE_ADJACENT_LIST_ARRAY
  #ifndef GRIN_ENABLE_ADJACENT_LIST
  LOG(ERROR) << "GRIN_ENABLE_ADJACENT_LIST_ARRAY requires GRIN_ENABLE_ADJACENT_LIST"
  #endif
  feature->add_adjacent_list_retrievals(grin::ListRetrieval::LR_ARRAY_LIKE);
#endif

#ifdef GRIN_ENABLE_ADJACENT_LIST_ITERATOR
  #ifndef GRIN_ENABLE_ADJACENT_LIST
  LOG(ERROR) << "GRIN_ENABLE_ADJACENT_LIST_ITERATOR requires GRIN_ENABLE_ADJACENT_LIST"
  #endif
  feature->add_adjacent_list_retrievals(grin::ListRetrieval::LR_ITERATOR);
#endif
}

{
  auto storage_feature = s.add_features();
  auto feature = storage_feature->mutable_partition_feature();

#ifdef GRIN_TRAIT_NATURAL_ID_FOR_PARTITION
  feature->set_grin_trait_natural_id_for_partition(true);
#endif

#ifdef GRIN_ENABLE_VERTEX_REF
  feature->set_grin_enable_vertex_ref(true);
#endif

#ifdef GRIN_TRAIT_FAST_VERTEX_REF
  feature->set_grin_trait_fast_vertex_ref(true);
#endif

#ifdef GRIN_ENABLE_EDGE_REF
  feature->set_grin_enable_edge_ref(true);
#endif

  auto mpl_feature = feature->mutable_mirror_partition_list_feature();
#ifdef GRIN_TRAIT_MASTER_VERTEX_MIRROR_PARTITION_LIST
  mpl_feature->set_grin_trait_master_vertex_mirror_partition_list(true);
#endif

#ifdef GRIN_TRAIT_MIRROR_VERTEX_MIRROR_PARTITION_LIST
  mpl_feature->set_grin_trait_mirror_vertex_mirror_partition_list(true);
#endif

#ifdef GRIN_TRAIT_MASTER_EDGE_MIRROR_PARTITION_LIST
  mpl_feature->set_grin_trait_master_edge_mirror_partition_list(true);
#endif

#ifdef GRIN_TRAIT_MIRROR_EDGE_MIRROR_PARTITION_LIST
  mpl_feature->set_grin_trait_mirror_edge_mirror_partition_list(true);
#endif

#ifdef GRIN_TRAIT_SELECT_MASTER_FOR_VERTEX_LIST
  feature->set_grin_trait_select_master_for_vertex_list(true);
#endif

#ifdef GRIN_TRAIT_SELECT_PARTITION_FOR_VERTEX_LIST
  feature->set_grin_trait_select_partition_for_vertex_list(true);
#endif

#ifdef GRIN_TRAIT_SELECT_MASTER_FOR_EDGE_LIST
  feature->set_grin_trait_select_master_for_edge_list(true);
#endif

#ifdef GRIN_TRAIT_SELECT_PARTITION_FOR_EDGE_LIST
  feature->set_grin_trait_select_partition_for_edge_list(true);
#endif

#ifdef GRIN_TRAIT_SELECT_MASTER_NEIGHBOR_FOR_ADJACENT_LIST
  feature->set_grin_trait_select_master_neighbor_for_adjacent_list(true);
#endif

#ifdef GRIN_TRAIT_SELECT_NEIGHBOR_PARTITION_FOR_ADJACENT_LIST
  feature->set_grin_trait_select_partition_neighbor_for_adjacent_list(true);
#endif
}

{
  auto storage_feature = s.add_features();
  auto feature = storage_feature->mutable_property_feature();
#ifdef GRIN_ENABLE_ROW
  feature->set_grin_enable_row(true);
#endif

  auto vfeature = feature->mutable_vertex_property_feature();
#ifdef GRIN_WITH_VERTEX_PROPERTY
  vfeature->set_grin_with_vertex_property(true);
#endif

#ifdef GRIN_WITH_VERTEX_PROPERTY_NAME
  vfeature->set_grin_with_vertex_property_name(true);
#endif

#ifdef GRIN_WITH_VERTEX_TYPE_NAME
  vfeature->set_grin_with_vertex_type_name(true);
#endif

#ifdef GRIN_ENABLE_VERTEX_PRIMARY_KEYS
  vfeature->set_grin_enable_vertex_primary_keys(true);
#endif

#ifdef GRIN_TRAIT_NATURAL_ID_FOR_VERTEX_TYPE
  vfeature->set_grin_trait_natural_id_for_vertex_type(true);
#endif

#ifdef GRIN_TRAIT_NATURAL_ID_FOR_VERTEX_PROPERTY
  vfeature->set_grin_trait_natural_id_for_vertex_property(true);
#endif

  auto efeature = feature->mutable_edge_property_feature();
#ifdef GRIN_WITH_EDGE_PROPERTY
  efeature->set_grin_with_edge_property(true);
#endif

#ifdef GRIN_WITH_EDGE_PROPERTY_NAME
  efeature->set_grin_with_edge_property_name(true);
#endif

#ifdef GRIN_WITH_EDGE_TYPE_NAME
  efeature->set_grin_with_edge_type_name(true);
#endif

#ifdef GRIN_ENABLE_EDGE_PRIMARY_KEYS
  efeature->set_grin_enable_edge_primary_keys(true);
#endif

#ifdef GRIN_TRAIT_NATURAL_ID_FOR_EDGE_TYPE
  efeature->set_grin_trait_natural_id_for_edge_type(true);
#endif

#ifdef GRIN_TRAIT_NATURAL_ID_FOR_EDGE_PROPERTY
  efeature->set_grin_trait_natural_id_for_edge_property(true);
#endif

#ifdef GRIN_TRAIT_CONST_VALUE_PTR
  feature->set_grin_trait_const_value_ptr(true);
#endif
}

{
  auto storage_feature = s.add_features();
  auto feature = storage_feature->mutable_index_feature();
#ifdef GRIN_WITH_VERTEX_LABEL
  feature->set_grin_with_vertex_label(true);
#endif

#ifdef GRIN_WITH_EDGE_LABEL
  feature->set_grin_with_edge_label(true);
#endif

#ifdef GRIN_ASSUME_ALL_VERTEX_LIST_SORTED
  feature->set_grin_assume_all_vertex_list_sorted(true);
#endif

#ifdef GRIN_ENABLE_VERTEX_INTERNAL_ID_INDEX
  feature->set_grin_enable_vertex_internal_id_index(true);
#endif

#ifdef GRIN_ENABLE_VERTEX_PK_INDEX
  feature->set_grin_enable_vertex_pk_index(true);
#endif

#ifdef GRIN_ENABLE_EDGE_PK_INDEX
  feature->set_grin_enable_edge_pk_index(true);
#endif

#ifdef GRIN_ENABLE_VERTEX_EXTERNAL_ID_OF_INT64
  feature->set_grin_enable_vertex_external_id_of_int64(true);
#endif

#ifdef GRIN_ENABLE_VERTEX_EXTERNAL_ID_OF_STRING
  feature->set_grin_enable_vertex_external_id_of_string(true);
#endif
}

{
  auto storage_feature = s.add_features();
  auto feature = storage_feature->mutable_common_feature();
#ifdef GRIN_TRAIT_LOOSE_SCHEMA
  feature->set_grin_trait_loose_schema(true);
#endif
}

  std::string msg;
  google::protobuf::util::MessageToJsonString(s, &msg);
  
  int len = msg.length() + 1;
  char* out = new char[len];
  snprintf(out, len, "%s", msg.c_str());
  return out;
}



