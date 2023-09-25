Developer Guide For Storage Implementors
-----------------------------------------

To support GRIN, storage system implementors should implement the APIs that
they **choose** to support.
The first step is to create a ``predefine.h`` header file from the template.
Within this header file, the implementors will define the macros for the
categories and traits they have decided to support. Additionally, they will
type-define the corresponding handle types.
Finally, the implementors will proceed to implement the APIs of the categories
and traits that they have chosen to support.


Implementation Principles
==========================

Efficiency First
^^^^^^^^^^^^^^^^^
To effectively implement GRIN APIs, implementors should prioritize efficiency as
their main consideration. It is crucial to aim for the best possible time
complexity, while still maintaining a reasonable level of space complexity.
Ideally, the recommended upper bound for time complexity should be O(log n),
where n represents the size of the graph.

In cases where achieving O(log n) time complexity is not feasible for certain
APIs, implementors should explore the option of caching the results the first
time the API is called. Subsequently, when the API is called again, the cached
results can be returned, thereby improving overall performance.


More Traits More Users
^^^^^^^^^^^^^^^^^^^^^^^
The implementation of a storage system should aim to support a wide range of
categories and traits. This is important because certain users may depend on
specific traits to effectively implement their algorithms. For instance,
graph analytical systems often rely on the ``internal ID`` indexing trait in
order to efficiently implement a Single-Source Shortest Path (SSSP)
algorithm. By incorporating a greater number of traits, a storage system can
cater to a larger user base seeking to implement their algorithms using GRIN.


How to Implement GRIN
======================

To implement GRIN within a storage system, follow these steps:

1. Add GRIN as a submodule to the storage system's repository.
2. Create a ``grin`` folder.
3. Inside the ``grin`` folder, create a ``predefine.h`` header file using the
   provided template from GRIN.
4. Define the macros for the categories and traits that the storage system has
   decided to support in the ``predefine.h`` header file.
5. Type-define the corresponding handle types in the ``predefine.h`` header file.
6. Create a ``src`` folder inside the ``grin`` folder and create sub-folders for
   each category.
7. Implement the APIs of each category in their corresponding sub-folders.
8. Add scripts to build and install the GRIN library into the storage system's
   build system (e.g., CMakeLists.txt).


