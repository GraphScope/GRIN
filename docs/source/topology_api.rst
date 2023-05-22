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

Moreover, in property graph, GRIN provides APIs to filter the adjacent list based on edge types.

::

    GRIN_ADJACENT_LIST adj_list = grin_get_adjacent_list(g, OUT, v);

    GRIN_ADJACENT_LIST filtered_adj_list = grin_select_edge_type_for_adjacent_list(g, edge_type, adj_list);

    #ifdef GRIN_ENABLE_ADJACENT_LIST_ITERATOR
    GRIN_ADJACENT_LIST_ITERATOR iter = grin_get_adjacent_list_begin(g, filtered_adj_list);

    while (!grin_is_adjacent_list_end(g, iter)) {
        GRIN_VERTEX u = grin_get_neighbor_from_adjacent_list_iter(g, iter);
        // use u 
        grin_destroy_vertex(g, u);
        grin_get_next_adjacent_list_iter(g, iter);
    }

    grin_destroy_adjacent_list_iter(g, iter);
    #endif

    grin_destroy_adjacent_list(g, filtered_adj_list);
    grin_destroy_adjacent_list(g, adj_list);

As a result, GRIN actually provides four ways to traverse an adjacent list of a vertex, as shown in the following table.
We mark the more efficient way with a higher rank (low numeric value).

=============================== ============= ==============
num_types \\ accessment         Array-like    Iterator
=============================== ============= ==============
all-edge-types (no-select)      4             3
one-edge-type (after-select)    2             1
=============================== ============= ==============

This also applies for vertex list, traversing a set of vertex lists selected by vertex types is 
more efficient than traversing a single vertex list of all types.