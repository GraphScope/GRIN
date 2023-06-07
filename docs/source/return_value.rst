Return Values
--------------
handle
^^^^^^^^^^
The return value of a GRIN API call is a GRIN handle in most cases.
A GRIN handle represents a GRIN object such as vertex or edge, and
it can be used as a paramter of another GRIN API call.

In the last section, we already got a ``GRIN_GRAPH`` handle ``g``.
We can use it to get the vertex list of the graph:

:: 
    
    GRIN_VERTEX_LIST vlist = grin_get_vertex_list(g);

    #ifdef GRIN_ENABLE_VERTEX_LIST_ARRAY
    size_t vlist_size = grin_get_vertex_list_size(g, vlist);

    for (unsigned int i = 0; i < vlist_size; ++i) {
        GRIN_VERTEX v = grin_get_vertex_from_list(g, vlist, i);
        // use v 
        grin_destroy_vertex(g, v);
    }
    #endif

    #ifdef GRIN_ENABLE_VERTEX_LIST_ITERATOR
    GRIN_VERTEX_LIST_ITERATOR vlist_iter = grin_get_vertex_list_begin(g, vlist);

    while (grin_is_vertex_list_end(g, vlist_iter)) {
        GRIN_VERTEX v = grin_get_vertex_from_iter(g, vlist_iter);
        // use v 
        grin_destroy_vertex(g, v);
        grin_get_next_vertex_list_iter(g, vlist_iter);
    }

    grin_destroy_vertex_list_iter(g, vlist_iter);
    #endif

    grin_destroy_vertex_list(g, vlist);

In the first line, we get a ``vertex list`` handle in GRIN from a graph handle.
Then the vertex list can be accessed in two ways: array and iterator.
This is controlled by the macros enabled by the storage, meaning some storage may
only support one type of accessment while some may support both.
Finally, we have to destroy every handle we get from GRIN to avoid memory leak.

Others
^^^^^^
Exceptionally, there are three types of values returned by GRIN API calls other than handles:

- GRIN enumerates: This includes enumerates defined in predefine.h, namely GRIN_DIRECTION, GRIN_DATATYPE and GRIN_ERROR_CODE.
- common values: This includes common values such as ``size_t`` for list size, ``bool`` for condition check, ``unsigned int`` for id, and ``const char*`` for name.
- property values: This includes property values such as ``int32``, ``int64``, ``float``, ``double`` and ``const char*``. The types of defined in the GRIN_DATATYPE enumerate.
- serialized values: This includes serialized ``const char*`` from vertex ref or edge ref.

Users do NOT have to destroy these return values since they are on ``"stack"`` only except for 
the ``const char*`` in property values and serialized values.
In which case, users have to destroy the string value by ``grin_destroy_string_value`` and ``grin_destroy_serialized_vertex(edge)_ref`` accordingly.

Note that if the ``const char*`` is returned by a GRIN API call for name, such as vertex type name,
or edge property name, users do NOT have to destroy it, since they are common values.

Validation
^^^^^^^^^^
GRIN provides invalid values for handles to let users check if a handle is valid or not.
Normally, the invalid value is of a GRIN handle ``GRIN_A`` is defined as ``GRIN_NULL_A``.
If ``A`` is a list or iterator, use ``GRIN_NULL_LIST`` or ``GRIN_NULL_LIST_ITERATOR`` instead of
specifying ``GRIN_NULL_A_LIST``.

GRIN also provides invalid values for common values, namely ``GRIN_NULL_SIZE``, ``GRIN_NULL_NATURAL_ID``
and ``GRIN_NULL_NAME``.

GRIN does NOT provide invalid values for enumerates, because each enumerate should cover all the possible
values.

GRIN also does NOT define invalid values for property values, because there is no specific value can
be defined as invalid for types like ``int32`` or ``double``. This case if handled by GRIN error codes
in the next section.

Error Code
^^^^^^^^^^
GRIN defines a set of error codes in ``GRIN_ERROR_CODE`` enumerate.
When a GRIN API call figures out an error, but cannot return invalid values (e.g., the property value case
above), it can set the ``thread_local`` error code to indicate the error.
Users can get the error code using ``grin_get_last_error_code`` API and handle the error case.

::

    int value = grin_get_int32_from_row(g, row, 0);
    if (grin_get_last_error_code() != GRIN_ERROR_CODE::GRIN_NO_ERROR) {
        // handle error
    }

Summary
^^^^^^^
To summerize, we list a table for return values of GRIN API calls and related operations:

=================== =========================== =================
Return Value Types  Check Invalid               Destroy Required
=================== =========================== =================
handle              != GRIN_NULL_A              grin_destroy_A
GRIN enumerates     N/A                         N/A
Common values       != GRIN_NULL_X              N/A
Property values     grin_get_last_error_code    grin_destroy_string_value only
Serialized values   N/A                         grin_destroy_serialized_A_ref only
=================== =========================== =================
