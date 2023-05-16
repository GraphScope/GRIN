Topology APIs
--------------

Graph Traversal
^^^^^^^^^^^^^^^^
GRIN provides adjacent list of a vertex for graph traversal in a CSR fashion.

::

    GRIN_ADJACENT_LIST adj_list = grin_get_adjacent_list(g, OUT, v);

    #ifdef GRIN_ENABLE_ADJACENT_LIST_ARRAY
    size_t adj_list_size = grin_get_adjacent_list_size(g, adj_list);

    for (size_t i = 0; i < adj_list_size; ++i) {
        GRIN_VERTEX u = grin_get_neighbor_from_adjacent_list(g, adj_list, i);
        // use u 
        grin_destroy_vertex(g, u);
    }
    #endif

    grin_destroy_adjacent_list(g, adj_list);