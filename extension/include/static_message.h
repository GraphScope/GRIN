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

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GRIN_EXTENSION_INCLUDE_STATIC_MESSAGE_H_
#define GRIN_EXTENSION_INCLUDE_STATIC_MESSAGE_H_

#include "../handle.h"

void grin_destroy_static_storage_feature_msg(const char* msg);

const char* grin_get_static_storage_feature_msg();

#endif // GRIN_EXTENSION_INCLUDE_STATIC_MESSAGE_H_

#ifdef __cplusplus
}
#endif