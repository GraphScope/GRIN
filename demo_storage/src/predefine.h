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

#ifndef SRC_PREDEFINE_H_
#define SRC_PREDEFINE_H_

#include <any>
#include <string>
#include <vector>

#include "../predefine.h"
#include "storage/storage.h"

typedef DEMO_STORAGE_NAMESPACE::Graph GRIN_GRAPH_T;
typedef DEMO_STORAGE_NAMESPACE::Vertex GRIN_VERTEX_T;
typedef DEMO_STORAGE_NAMESPACE::Edge GRIN_EDGE_T;
typedef DEMO_STORAGE_NAMESPACE::Property GRIN_PROPERTY_T;

typedef std::vector<unsigned> GRIN_VERTEX_TYPE_LIST_T;
typedef std::vector<unsigned> GRIN_VERTEX_PROPERTY_LIST_T;
typedef std::vector<unsigned> GRIN_EDGE_TYPE_LIST_T;
typedef std::vector<unsigned> GRIN_EDGE_PROPERTY_LIST_T;
typedef std::vector<unsigned> GRIN_VEV_TYPE_LIST_T;
typedef std::vector<unsigned> GRIN_PARTITION_LIST_T;

typedef std::vector<std::any> GRIN_ROW_T;

typedef enum {
  ALL_PARTITION = 0,
  ONE_PARTITION = 1,
  ALL_BUT_ONE_PARTITION = 2,
  PARTITION_TYPE_MAX = 3
} PARTITION_TYPE_IN_LIST;

struct GRIN_PARTITIONED_GRAPH_T {
  std::string name;
  unsigned partition_num;
  GRIN_PARTITIONED_GRAPH_T(std::string _name, unsigned _partition_num)
      : name(_name), partition_num(_partition_num) {}
};

struct GRIN_VERTEX_LIST_T {
  unsigned type_id;
  PARTITION_TYPE_IN_LIST partition_type;
  // only used when partition_type is ONE_PARTITION/ALL_BUT_ONE_PARTITION
  unsigned partition_id;
  GRIN_VERTEX_LIST_T(unsigned _type_id,
                     PARTITION_TYPE_IN_LIST _partition_type = ALL_PARTITION,
                     unsigned _partition_id = 0)
      : type_id(_type_id),
        partition_type(_partition_type),
        partition_id(_partition_id) {}
};

struct GRIN_VERTEX_LIST_ITERATOR_T {
  unsigned type_id;
  PARTITION_TYPE_IN_LIST partition_type;
  // only used when partition_type is ONE_PARTITION/ALL_BUT_ONE_PARTITION
  unsigned partition_id;
  int64_t current_offset;
  GRIN_VERTEX_LIST_ITERATOR_T(unsigned _type_id,
                              PARTITION_TYPE_IN_LIST _partition_type,
                              unsigned _partition_id, int64_t _current_offset)
      : type_id(_type_id),
        partition_type(_partition_type),
        partition_id(_partition_id),
        current_offset(_current_offset) {}
};

struct GRIN_EDGE_LIST_T {
  unsigned type_id;
  PARTITION_TYPE_IN_LIST partition_type;
  // only used when partition_type is ONE_PARTITION/ALL_BUT_ONE_PARTITION
  unsigned partition_id;
  GRIN_EDGE_LIST_T(unsigned _type_id,
                   PARTITION_TYPE_IN_LIST _partition_type = ALL_PARTITION,
                   unsigned _partition_id = 0)
      : type_id(_type_id),
        partition_type(_partition_type),
        partition_id(_partition_id) {}
};

struct GRIN_EDGE_LIST_ITERATOR_T {
  unsigned type_id;
  PARTITION_TYPE_IN_LIST partition_type;
  // only used when partition_type is ONE_PARTITION/ALL_BUT_ONE_PARTITION
  unsigned partition_id;
  int64_t current_offset;
  GRIN_EDGE_LIST_ITERATOR_T(unsigned _type_id,
                            PARTITION_TYPE_IN_LIST _partition_type,
                            unsigned _partition_id, int64_t _current_offset)
      : type_id(_type_id),
        partition_type(_partition_type),
        partition_id(_partition_id),
        current_offset(_current_offset) {}
};

struct GRIN_ADJACENT_LIST_T {
  unsigned vtype_id;
  int64_t vid;
  GRIN_DIRECTION dir;
  unsigned etype_id;
  PARTITION_TYPE_IN_LIST partition_type;
  // only used when partition_type is ONE_PARTITION/ALL_BUT_ONE_PARTITION
  unsigned partition_id;
  GRIN_ADJACENT_LIST_T(unsigned _vtype_id, int64_t _vid, GRIN_DIRECTION _dir,
                       unsigned _etype_id,
                       PARTITION_TYPE_IN_LIST _partition_type = ALL_PARTITION,
                       unsigned _partition_id = 0)
      : vtype_id(_vtype_id),
        vid(_vid),
        dir(_dir),
        etype_id(_etype_id),
        partition_type(_partition_type),
        partition_id(_partition_id) {}
};

struct GRIN_ADJACENT_LIST_ITERATOR_T {
  unsigned vtype_id;
  int64_t vid;
  GRIN_DIRECTION dir;
  unsigned etype_id;
  PARTITION_TYPE_IN_LIST partition_type;
  // only used when partition_type is ONE_PARTITION/ALL_BUT_ONE_PARTITION
  unsigned partition_id;
  unsigned current_partition;
  int64_t current_offset;
  GRIN_ADJACENT_LIST_ITERATOR_T(unsigned _vtype_id, int64_t _vid,
                                GRIN_DIRECTION _dir, unsigned _etype_id,
                                PARTITION_TYPE_IN_LIST _partition_type,
                                unsigned _partition_id,
                                unsigned _current_partition,
                                int64_t _current_offset)
      : vtype_id(_vtype_id),
        vid(_vid),
        dir(_dir),
        etype_id(_etype_id),
        partition_type(_partition_type),
        partition_id(_partition_id),
        current_partition(_current_partition),
        current_offset(_current_offset) {}
};

#endif  // SRC_PREDEFINE_H_
