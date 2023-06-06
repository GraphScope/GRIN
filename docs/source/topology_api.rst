Topology APIs
--------------

Low-level Abstraction
^^^^^^^^^^^^^^^^^^^^^
GRIN provides low-level abstraction for graph topology for vertices and edges.
Thus, in property graphs with various vertex types and edge types, GRIN only provides
APIs to get vertex list and edge list of a single type, because a vertex list containing
vertices of different types can be easily constructed by merging vertex lists of different types.
GRIN will support such high-level abstraction in the future under ``GRIN+``.

Vertex List
^^^^^^^^^^^^^^^^
In simple graph, GRIN provides the ``grin_get_vertex_list`` API to get the vertex list of the graph.
While in property graph, GRIN provides the ``grin_get_vertex_list_by_type`` API to get the vertex list.

Also in partitioned graph, when ``GRIN_TRAIT_SELECT_MASTER_FOR_VERTEX_LIST`` features is enabled,
GRIN provides two groups of additional APIs ``[grin_get_vertex_list_select_master, grin_get_vertex_list_select_mirror]``
and ``[grin_get_vertex_list_by_type_select_master, grin_get_vertex_list_by_type_select_mirror]``
for simple graph and property graph respectively.

Edge List
^^^^^^^^^^^
Similar to vertex list, GRIN provides the ``grin_get_edge_list`` API to get the edge list for simple graph,
and ``grin_get_edge_list_by_type`` for property graph.

Adjacent List
^^^^^^^^^^^^^^
GRIN considers adjacent list as a special case of edge list, thus also provides ``grin_get_adjacent_list_by_edge_type`` API
for property graph, as well as ``grin_get_adjacent_list`` for simple graph.

Additional selections can also be attached to adjacent lists of both simple graph and property graph,
such as ``grin_get_adjacent_list_select_neighbor_partition``, ``grin_get_adjacent_list_by_edge_type_select_master_neighbor``, etc.