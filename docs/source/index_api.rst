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


Original ID
^^^^^^^^^^^
Building index on vertex is a common need in graph processing.
GRIN provides indexing on primary keys for property graphs which will be described in the primary key section.
However, the simple graphs have no properties, their vertex indexing is usually built on their original IDs (e.g., uuid).

GRIN provides two types of original ID indexing, namely int64 and string:

::

    #ifdef GRIN_ENABLE_VERTEX_ORIGINAL_ID_OF_INT64
    long long int grin_get_vertex_original_id_of_int64(GRIN_GRAPH, GRIN_VERTEX);

    GRIN_VERTEX grin_get_vertex_by_original_id_of_int64(GRIN_GRAPH, long long int);
    #endif

    #ifdef GRIN_ENABLE_VERTEX_ORIGINAL_ID_OF_STRING
    const char* grin_get_vertex_original_id_of_string(GRIN_GRAPH, GRIN_VERTEX);

    GRIN_VERTEX grin_get_vertex_by_original_id_of_string(GRIN_GRAPH, const char*);
    #endif

Note that the ``const char*`` returned in the ``original_id_of_string`` is also considered
as a property value, meaning that it should be destroyed using ``grin_destroy_string_value``.

GRIN does NOT provide orginal ID indexing on edges because orignal IDs are usually used
to describe edges in the raw data, thus makes edges have no original IDs. 

Also, GRIN does NOT provide original ID indexing for property graphs because it is redundant
to indexing by primary keys.