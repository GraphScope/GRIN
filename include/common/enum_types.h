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
 @file error.h
 @brief Define the error code related APIs
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GRIN_INCLUDE_ENUM_TYPES_H_
#define GRIN_INCLUDE_ENUM_TYPES_H_

/* Enumerate types of GRIN */
/// Enumerates the directions of edges with respect to a certain vertex
typedef enum {
  IN = 0,     ///< incoming
  OUT = 1,    ///< outgoing
  BOTH = 2,   ///< incoming & outgoing
} GRIN_DIRECTION;

/// Enumerates the datatype supported in the storage
typedef enum {
  Undefined = 0,      ///< other unknown types
  Int32 = 1,          ///< int
  UInt32 = 2,         ///< unsigned int
  Int64 = 3,          ///< long int
  UInt64 = 4,         ///< unsigned long int
  Float = 5,          ///< float
  Double = 6,         ///< double
  String = 7,         ///< string
  Date32 = 8,         ///< date
  Time32 = 9,         ///< Time32
  Timestamp64 = 10,   ///< Timestamp
#ifdef GRIN_TRAIT_PROPERTY_VALUE_OF_FLOAT_ARRAY
  FloatArray = 11,    ///< float array
#endif
} GRIN_DATATYPE;

/// Enumerates the error codes of grin
typedef enum {
  NO_ERROR = 0,              ///< success
  UNKNOWN_ERROR = 1,         ///< unknown error
  INVALID_VALUE = 2,         ///< invalid value
  UNKNOWN_DATATYPE = 3,      ///< unknown datatype
  NULL_VALUE = 4,            ///< null value
} GRIN_ERROR_CODE;

#endif // GRIN_INCLUDE_ENUM_TYPES_H_

#ifdef __cplusplus
}
#endif