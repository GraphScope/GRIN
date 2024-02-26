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

#ifndef TEST_CONFIG_H_
#define TEST_CONFIG_H_

// Define a new macro that is just like the standard C assert macro,
// except that it works even in optimized builds (where NDEBUG is
// defined) and it prints the failed assertion to stderr.
#ifndef ASSERT
#define ASSERT(x)                                    \
  if (!(x)) {                                        \
    char buf[2048];                                  \
    snprintf(buf, sizeof(buf),                       \
             "Assertion failed in \"%s\", line %d\n" \
             "\tProbable bug in software.\n",        \
             __FILE__, __LINE__);                    \
    ABORT(buf);                                      \
  } else  // NOLINT
// The 'else' exists to catch the user's following semicolon
#endif

// Define a new macro that is just like the standard C abort macro,
// except that it prints the failed assertion to stderr.
#ifndef ABORT
#define ABORT(msg)              \
  do {                          \
    fprintf(stderr, "%s", msg); \
    fflush(stderr);             \
    abort();                    \
  } while (0)
#endif

#endif  // TEST_CONFIG_H_
