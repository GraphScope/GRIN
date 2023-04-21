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

#ifndef GRIN_INCLUDE_TOPOLOGY_DATATYPE_H_
#define GRIN_INCLUDE_TOPOLOGY_DATATYPE_H_

#include "../../predefine.h"

int grin_get_int32(void*);

unsigned int grin_get_uint32(void*);

long int grin_get_int64(void*);

unsigned long int grin_get_uint64(void*);

float grin_get_float(void*);

double grin_get_double(void*);

char* grin_get_string(void*);

#endif  // GRIN_INCLUDE_TOPOLOGY_DATATYPE_H_
