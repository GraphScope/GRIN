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
 * @brief Get the default vertex type when loose schema is enabled.
 * This default vertex type can be further used to get vertices belongs to
 * none of the vertex types defined in the schema.
 * @return The default vertex type.
*/
GRIN_VERTEX_TYPE grin_get_default_vertex_type();
#endif

#if defined(GRIN_TRAIT_LOOSE_SCHEMA) && defined(GRIN_WITH_EDGE_PROPERTY)
/**
 * @brief Get the default edge type when loose schema is enabled.
 * This default edge type can be further used to get edges belongs to
 * none of the edge types defined in the schema.
 * @return The default edge type.
*/
GRIN_EDGE_TYPE grin_get_default_edge_type();
#endif

#endif // GRIN_INCLUDE_COMMON_SCHEMA_H_

#ifdef __cplusplus
}
#endif