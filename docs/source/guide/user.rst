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

GRIN APIs are defined in C and thus their names can be complex. 
We provide the following naming rules to help users understand how the APIs are named,
so that they will not be confused when programming with GRIN APIs.

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