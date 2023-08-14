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
 @file schema.h
 @brief Define schema-related APIs
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GRIN_INCLUDE_COMMON_SCHEMA_H_
#define GRIN_INCLUDE_COMMON_SCHEMA_H_

#if defined(GRIN_TRAIT_LOOSE_SCHEMA) && defined(GRIN_WITH_VERTEX_PROPERTY)
/**
 * @brief Get the loose vertex type when loose schema is enabled.
 * This loose vertex type can be further used to get non-schema vertices.
 * Note that the loose vertex type is a non-schema type,
 * users should not use it in schema-related APIs,
 * such as ``grin_get_vertex_property_list_by_type``, 
 * ``grin_get_primary_keys_by_vertex_type``, etc.
 * @return The loose vertex type.
*/
GRIN_VERTEX_TYPE grin_get_loose_vertex_type();

GRIN_VERTEX_PROPERTY_LIST grin_get_vertex_property_list(GRIN_GRAPH, GRIN_VERTEX);
#endif

#if defined(GRIN_TRAIT_LOOSE_SCHEMA) && defined(GRIN_WITH_EDGE_PROPERTY)
GRIN_EDGE_TYPE grin_get_loose_edge_type();

GRIN_EDGE_PROPERTY_LIST grin_get_edge_property_list(GRIN_GRAPH, GRIN_EDGE);
#endif

#endif // GRIN_INCLUDE_COMMON_SCHEMA_H_

#ifdef __cplusplus
}
#endif