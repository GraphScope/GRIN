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
 * @file extension/predefine.h
 * @brief Pre-defined macros, handles and null values for
 * GRIN extensions.
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GRIN_EXTENSION_PREDEFINE_H_
#define GRIN_EXTENSION_PREDEFINE_H_

#include "predefine.h"

#if defined(GRIN_ENABLE_VERTEX_LIST) && defined(GRIN_WITH_VERTEX_PROPERTY)
typedef struct GRIN_VERTEX_LIST_CHAIN {
    GRIN_VERTEX_LIST* lists;
    unsigned int size;
} GRIN_VERTEX_LIST_CHAIN;

typedef struct GRIN_VERTEX_LIST_CHAIN_ITERATOR {
    GRIN_VERTEX_LIST_ITERATOR* iterators;
    unsigned int size;
    unsigned int current;
} GRIN_VERTEX_LIST_CHAIN_ITERATOR;
#endif

#if defined(GRIN_ENABLE_EDGE_LIST) && defined(GRIN_WITH_EDGE_PROPERTY)
typedef void* GRIN_EDGE_LIST_CHAIN;

typedef void* GRIN_EDGE_LIST_CHAIN_ITERATOR;
#endif

#if defined(GRIN_ENABLE_ADJACENT_LIST) && defined(GRIN_WITH_EDGE_PROPERTY)
typedef struct GRIN_ADJACENT_LIST_CHAIN {
    GRIN_ADJACENT_LIST* lists;
    unsigned int size;
} GRIN_ADJACENT_LIST_CHAIN;

typedef struct GRIN_ADJACENT_LIST_CHAIN_ITERATOR {
    GRIN_ADJACENT_LIST_ITERATOR* iterators;
    unsigned int size;
    unsigned int current;
} GRIN_ADJACENT_LIST_CHAIN_ITERATOR;
#endif

#endif // GRIN_EXTENSION_PREDEFINE_H_

#ifdef __cplusplus
}
#endif