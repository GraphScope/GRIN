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
 @file property.h
 @brief Define the property related APIs
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GRIN_INCLUDE_PROPERTY_PROPERTY_H_
#define GRIN_INCLUDE_PROPERTY_PROPERTY_H_

#include "common/enum_types.h"

#if !defined(GRIN_ENABLE_SCHEMA) && defined(GRIN_WITH_VERTEX_PROPERTY)
/**
 * @brief Get the vertex property list of the vertex.
 * When schema is not enabled, each vertex has its own property list.
 * @param GRIN_GRAPH The graph.
 * @param GRIN_VERTEX The vertex.
 * @return The vertex property list.
*/
GRIN_VERTEX_PROPERTY_LIST grin_get_vertex_property_list(GRIN_GRAPH, GRIN_VERTEX);

/**
 * @brief Get the vertex property name
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX The vertex
 * @param GRIN_VERTEX_PROPERTY The vertex property
 * @return The property's name as string
 */
const char* grin_get_vertex_property_name(GRIN_GRAPH, GRIN_VERTEX, GRIN_VERTEX_PROPERTY);

/**
 * @brief Get the vertex property with a given name under a specific vertex
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX The specific vertex
 * @param name The name
 * @return The vertex property
 */
GRIN_VERTEX_PROPERTY grin_get_vertex_property_by_name(GRIN_GRAPH, GRIN_VERTEX, const char* name);
#endif

#if defined(GRIN_ENABLE_SCHEMA) && defined(GRIN_WITH_VERTEX_PROPERTY)
/**
 * @brief Get the vertex property list of the graph.
 * This API is only available for property graph.
 * @param GRIN_GRAPH The graph.
 * @return The vertex property list.
*/
GRIN_VERTEX_PROPERTY_LIST grin_get_vertex_property_list_by_type(GRIN_GRAPH, GRIN_VERTEX_TYPE);

/**
 * @brief Get the vertex type that a given vertex property belongs to.
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX_PROPERTY The vertex property
 * @return The vertex type
*/
GRIN_VERTEX_TYPE grin_get_vertex_type_from_property(GRIN_GRAPH, GRIN_VERTEX_PROPERTY);

/**
 * @brief Get the vertex property name
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX_TYPE The vertex type that the property belongs to
 * @param GRIN_VERTEX_PROPERTY The vertex property
 * @return The property's name as string
 */
const char* grin_get_vertex_property_name(GRIN_GRAPH, GRIN_VERTEX_TYPE, GRIN_VERTEX_PROPERTY);

/**
 * @brief Get the vertex property with a given name under a specific vertex type
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX_TYPE The specific vertex type
 * @param name The name
 * @return The vertex property
 */
GRIN_VERTEX_PROPERTY grin_get_vertex_property_by_name(GRIN_GRAPH, GRIN_VERTEX_TYPE, const char* name);

/**
 * @brief Get properties under all types with a given name.
 * For example, vertex type "person" and "company" both have a property 
 * called "name". When this API is called given "name", it will return a list 
 * of "name" properties under both types.
 * @param GRIN_GRAPH The graph
 * @param name The name
 * @return The vertex property list of properties with the given name
 */
GRIN_VERTEX_PROPERTY_LIST grin_get_vertex_properties_by_name(GRIN_GRAPH, const char* name);

/**
 * @brief Get the vertex property handle by id.
 * In strict schema, storage has naturally increasing ids for vertex properties
 * under a certain vertex type.
 * @param GRIN_GRAPH The graph.
 * @param GRIN_VERTEX_TYPE The vertex type.
 * @param GRIN_VERTEX_PROPERTY_ID The vertex property id.
 * @return The vertex property handle.
*/
GRIN_VERTEX_PROPERTY grin_get_vertex_property_by_id(GRIN_GRAPH, GRIN_VERTEX_TYPE, GRIN_VERTEX_PROPERTY_ID);

/**
 * @brief Get the vertex property's natural id.
 * In strict schema, the storage has naturally increasing ids for vertex properties
 * under a certain vertex type.
 * @param GRIN_GRAPH The graph.
 * @param GRIN_VERTEX_TYPE The vertex type.
 * @param GRIN_VERTEX_PROPERTY The vertex property handle.
 * @return The vertex property id.
*/
GRIN_VERTEX_PROPERTY_ID grin_get_vertex_property_id(GRIN_GRAPH, GRIN_VERTEX_TYPE, GRIN_VERTEX_PROPERTY);
#endif

#if !defined(GRIN_ENABLE_SCHEMA) && defined(GRIN_WITH_EDGE_PROPERTY)
GRIN_EDGE_PROPERTY_LIST grin_get_edge_property_list(GRIN_GRAPH, GRIN_EDGE);

const char* grin_get_edge_property_name(GRIN_GRAPH, GRIN_EDGE, GRIN_EDGE_PROPERTY);

GRIN_EDGE_PROPERTY grin_get_edge_property_by_name(GRIN_GRAPH, GRIN_EDGE, const char* name);
#endif

#if defined(GRIN_ENABLE_SCHEMA) && defined(GRIN_WITH_EDGE_PROPERTY)
GRIN_EDGE_PROPERTY_LIST grin_get_edge_property_list_by_type(GRIN_GRAPH, GRIN_EDGE_TYPE);

const char* grin_get_edge_property_name(GRIN_GRAPH, GRIN_EDGE_TYPE, GRIN_EDGE_PROPERTY);

GRIN_EDGE_PROPERTY grin_get_edge_property_by_name(GRIN_GRAPH, GRIN_EDGE_TYPE, const char* name);

GRIN_EDGE_PROPERTY_LIST grin_get_edge_properties_by_name(GRIN_GRAPH, const char* name);

GRIN_EDGE_TYPE grin_get_edge_type_from_property(GRIN_GRAPH, GRIN_EDGE_PROPERTY);

GRIN_EDGE_PROPERTY grin_get_edge_property_by_id(GRIN_GRAPH, GRIN_EDGE_TYPE, GRIN_EDGE_PROPERTY_ID);

GRIN_EDGE_PROPERTY_ID grin_get_edge_property_id(GRIN_GRAPH, GRIN_EDGE_TYPE, GRIN_EDGE_PROPERTY);
#endif

#ifdef GRIN_WITH_VERTEX_PROPERTY
bool grin_equal_vertex_property(GRIN_GRAPH, GRIN_VERTEX_PROPERTY, GRIN_VERTEX_PROPERTY);

void grin_destroy_vertex_property(GRIN_GRAPH, GRIN_VERTEX_PROPERTY);

/**
 * @brief Get the datatype of the vertex property
 * @param GRIN_GRAPH The graph
 * @param GRIN_VERTEX_PROPERTY The vertex property
 * @return The datatype of the vertex property
*/
GRIN_DATATYPE grin_get_vertex_property_datatype(GRIN_GRAPH, GRIN_VERTEX_PROPERTY);
#endif

#ifdef GRIN_WITH_EDGE_PROPERTY
bool grin_equal_edge_property(GRIN_GRAPH, GRIN_EDGE_PROPERTY, GRIN_EDGE_PROPERTY);

void grin_destroy_edge_property(GRIN_GRAPH, GRIN_EDGE_PROPERTY);

GRIN_DATATYPE grin_get_edge_property_datatype(GRIN_GRAPH, GRIN_EDGE_PROPERTY);
#endif

#endif  // GRIN_INCLUDE_PROPERTY_PROPERTY_H_

#ifdef __cplusplus
}
#endif