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

/**
 @file primarykey.h
 @brief Define the primary key related APIs
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GRIN_INCLUDE_PROPERTY_PRIMARY_KEY_H_
#define GRIN_INCLUDE_PROPERTY_PRIMARY_KEY_H_


#ifdef GRIN_ENABLE_VERTEX_PRIMARY_KEYS
GRIN_VERTEX_TYPE_LIST grin_get_vertex_types_with_primary_keys(GRIN_GRAPH);

GRIN_VERTEX_PROPERTY_LIST grin_get_primary_keys_by_vertex_type(GRIN_GRAPH, GRIN_VERTEX_TYPE);

GRIN_ROW grin_get_primary_keys_row_by_vertex(GRIN_GRAPH, GRIN_VERTEX);
#endif

#ifdef GRIN_ENABLE_VERTEX_PK_OF_INT64
long long int grin_get_vertex_pk_of_int64(GRIN_GRAPH, GRIN_VERTEX);
#endif

#ifdef GRIN_ENABLE_EDGE_PRIMARY_KEYS
GRIN_EDGE_TYPE_LIST grin_get_edge_types_with_primary_keys(GRIN_GRAPH);

GRIN_EDGE_PROPERTY_LIST grin_get_primary_keys_by_edge_type(GRIN_GRAPH, GRIN_EDGE_TYPE);

GRIN_ROW grin_get_primary_keys_row_by_edge(GRIN_GRAPH, GRIN_EDGE);
#endif

#ifdef GRIN_ENABLE_EDGE_PK_OF_INT64
long long int grin_get_edge_pk_of_int64(GRIN_GRAPH, GRIN_EDGE);
#endif

#endif  // GRIN_INCLUDE_PROPERTY_PRIMARY_KEY_H_

#ifdef __cplusplus
}
#endif