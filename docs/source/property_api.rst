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


::

    GRIN_VERTEX_TYPE vtype = grin_get_vertex_type_by_name(g, "person");
    GRIN_ROW row = grin_create_row(g);
    if (!grin_insert_string_to_row(g, row, "marko")) {
        printf("Failed to insert string to row\n");
    }
    if (!grin_insert_int32_to_row(g, row, 29)) {
        printf("Failed to insert int32 to row\n");
    }
    GRIN_VERTEX v = grin_get_vertex_by_primary_keys(g, vtype, row);


Get Vertex Property Value
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
GRIN provides APIs to get a single property value of a vertex, as well as all the property values
of a vertex as a row.

::

    GRIN_ROW row = grin_get_vertex_row(g, v);
    
    GRIN_VERTEX_TYPE vtype = grin_get_vertex_type(g, v);
    GRIN_VERTEX_PROPERTY_LIST vpl = grin_get_vertex_property_list_by_type(g, vtype);
    size_t vpl_sz = grin_get_vertex_property_list_size(g, vpl);

    for (size_t i = 0; i < vpl_sz; ++i) {
        GRIN_VERTEX_PROPERTY vprop = grin_get_vertex_property_from_list(g, vpl, i);
        GRIN_DATATYPE dt = grin_get_vertex_property_datatype(g, vprop);

        if (dt == Int64) {
            long long int value = grin_get_vertex_property_of_int64(g, v, vprop);
            long long int value1 = grin_get_int64_from_row(g, row, i);
            // use the value
        } else if (dt == String) {
            const char* value = grin_get_vertex_property_of_string(g, v, vprop);
            const char* value1 = grin_get_string_from_row(g, row, i);
            // use the value
            grin_destroy_string_value(g, value);
            grin_destroy_string_value(g, value1);
        } else ...
    }



