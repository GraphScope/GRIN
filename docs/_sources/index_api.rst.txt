Index APIs
--------------

Sorted List and Order
^^^^^^^^^^^^^^^^^^^^^^
Some storage sort the vertices in a vertex list by default.
This enables the ability to let the user to find the position of a vertex in the list
in sub-linear time complexity (O(log(n)) for binary search).

To describe this feature, storage can define ``GRIN_ASSUME_ALL_VERTEX_LIST_SORTED`` to show
that all the vertex lists are sorted by default. If ``GRIN_ENABLE_VERTEX_LIST_ARRAY`` is also
defined, the position API is enabled:

::

    size_t grin_get_position_of_vertex_from_sorted_list(GRIN_GRAPH, GRIN_VERTEX_LIST, GRIN_VERTEX);

Internal ID
^^^^^^^^^^^

Primary Keys
^^^^^^^^^^^^^
In GRIN v0.1.1, we explicitly distinguish the concepts of primary keys and indexing based on primary keys.
Primary keys are the properties that are used to identify a vertex or an edge.
Just like in relational databases, primary keys are unique under a given vertex or edge type.
While indexing based on primary keys is the ability to find a vertex or an edge by its primary key.
These two sets of APIs are defined in ``property/primarykey.h`` and ``index/pk.h`` respectively.