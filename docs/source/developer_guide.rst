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
cater to a larger user base seeking to execute their programs using GRIN.


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




Developer Guide For Users
----------------------------

How to Use GRIN
================

To use GRIN within a graph computing system, follow these recommended steps:

1. Start by adding GRIN as a submodule to the repository of the graph
   computing system.
2. Ensure that the storage system is installed locally and that it implements
   the same version of GRIN that you intend to use.
3. If you are programming in C++, include the necessary header files for the
   GRIN APIs in your program. If you are programming in Rust, import the GRIN
   APIs using the auto-generated ``Rust-FFI`` files found in the ``rust`` folder.
4. Link the GRIN library of the storage system to your program.
5. (Optional) If applicable, load a sample graph into the storage system and run
   the ctest for GRIN to verify its functionality.
6. Confirm that the graph has been successfully loaded into the storage system
   and make a note of its ``URI``.
7. Build your program and run it, specifying the ``URI`` of the graph to be used.


API Naming Rules
=================

GRIN APIs are defined in C and thus can be complex. 
However, understanding the API naming rules can simplify the implementation
of programs using GRIN APIs.

Get A From B
^^^^^^^^^^^^^^
The most common API pattern in GRIN is ``get_A_from_B``.
The word **from** indicates that A is within B, or A is a part of B.
For example, ``grin_get_graph_from_storage``, ``grin_get_src_vertex_from_edge``,
``grin_get_int32_from_row``, and ``grin_get_neighbor_from_adjacent_list``.

When B is an A list, we use ``get_A_from_list`` for short.
For example, ``grin_get_vertex_from_list``, ``grin_get_edge_property_from_list``.

When B is an A iterator, we also use ``get_A_from_iter`` for short.
For example, ``grin_get_vertex_from_iter``.
But ``grin_get_neighbor_from_adjacent_list_iter`` has no short name, because B 
is an adjacent list iterator, while ``neighbor`` is a vertex.

We also use ``from`` in converting references to handles.
For example, ``grin_get_vertex_from_vertex_ref``.
We don't use ``by`` here because in general the vertex reference contains more information
than the vertex, so we consider the vertex as "a part of" the vertex reference.

Get B A
^^^^^^^^^
This pattern is also used when A is a part of B, when A is not a handle, but ``size``,
``name``, etc.
For example, ``grin_get_vertex_list_size``, ``grin_get_vertex_property_name``.


Get A by B
^^^^^^^^^^^^
This pattern is used when B is like a key for A.
For example, ``grin_get_vertex_by_external_id_of_int64``, ``grin_get_vertex_list_by_label``,
``grin_get_vertex_by_primary_keys_row``, ``grin_get_local_graph_by_partition``,
``grin_get_vertex_property_list_by_type`` and ``grin_get_edge_type_by_id``.

We also use ``by`` in converting handles to references.
For example, ``grin_get_vertex_ref_by_vertex``.

Get A of B
^^^^^^^^^^^^
This pattern is used when B is a data type.
For example, ``grin_get_vertex_property_value_of_uint32``.

Get A 
^^^^^^
This pattern is mainly used when A is a statistic.
For example, ``grin_get_vertex_num``.

Destroy A 
^^^^^^^^^^
This pattern is used when destroy a handle.
For example, ``grin_destroy_graph``, ``grin_destroy_vertex_list``.
Return values like string or float array should also be destroyed,
we use ``of`` to indicate the type.
For example, ``grin_destroy_vertex_property_value_of_string``.

Is C 
^^^^^^
This pattern is used when C is a condition.
For example, ``grin_is_directed`` and ``grin_is_vertex_list_end``.

Equal A 
^^^^^^^^
This pattern is used when comparing two handles of type A.
For example, ``grin_equal_vertex``.