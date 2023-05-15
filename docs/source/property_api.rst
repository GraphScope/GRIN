Property APIs
--------------

Primary Key 
^^^^^^^^^^^^
Primary keys (p.k. for short) are defined in the schema of property graphs to ensure the values of
p.k. properties are unique across all vertices under a given type. Moreover, p.k. are also used to
index vertices and edges. In the future, GRIN may distinguish p.k. from "indexing with p.k.", but
currently they are the same thing.

To get a vertex from its p.k. values, we will first put all the values into a row according to the
properties of p.k.. Then we will use the row to get the vertex handler. The following example shows
how to get the vertex of type "person" with name "marko" and age 29.

TODO: ask moran whether the info is got from schema.

::

    GRIN_ROW row = grin_create_row(g);
    if (!grin_insert_string_to_row(g, row, "marko")) {
        printf("Failed to insert string to row\n");
    }
    if (!grin_insert_int32_to_row(g, row, 29)) {
        printf("Failed to insert int32 to row\n");
    }



Get Value From Table
^^^^^^^^^^^^^^^^^^^^^




Edge Type and Vertex Type Pairs
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^