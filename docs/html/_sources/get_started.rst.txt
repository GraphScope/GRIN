Getting Started
----------------

Get Graph from Storage
^^^^^^^^^^^^^^^^^^^^^^
To use GRIN, the first API we need is to get the graph handle for the graph in storage.
Here we introduce the ``get_graph_from_storage`` API.

::
    
    GRIN_GRAPH grin_get_graph_from_storage(int, char**);

From the definition, we can see that this API takes two parameters, 
the first one is the number of arguments, and the second one is the arguments. 

The arguments are used to specify the graph in storage.
Different storage systems may have different ways to specify the graph.

For example, in Vineyard,
the first argument is the ``IPC_socket`` of the Vineyard server,
and the second argument is the ``object_id`` of the graph.

The return value of this API is a GRIN graph handle.

Partitioned Graph
^^^^^^^^^^^^^^^^^
However in GraphScope, the graphs we often meet are large graphs that are partitioned into multiple fragments.
GRIN regards them as partitioned graphs and each fragment of a partitioned graph is considered as
a graph in GRIN.

To get a partitioned graph, we need to use the ``get_partitioned_graph_from_storage`` API.

::
        
    GRIN_PARTITIONED_GRAPH grin_get_partitioned_graph_from_storage(int, char**);

The parameters of this API are the same as the ``get_graph_from_storage`` API.
The return value of this API is a GRIN partitioned graph handle.

To further get the graph handle of a specific fragment, we use:

::

    GRIN_PARTITIONED_GRAPH pg = grin_get_partitioned_graph_from_storage(2, ["ipc_socket", "object_id"]);
    GRIN_PARTITION_LIST local_partitions = grin_get_local_partition_list(pg);
    size_t num_partitions = grin_get_partition_list_size(local_partitions);

    if (num_partitions == 1) { // suppose we have only one local partition
      GRIN_PARTITION partition = grin_get_partition_from_list(pg, local_partitions, 0);
      GRIN_GRAPH g = grin_get_local_graph_by_partition(pg, partition);
    }

All these types here with ``GRIN_`` prefix are GRIN handle types, which are typedefined by the storage.
Actions should not be taken based on the specific type (e.g., ``void*`` or ``int``) of any handle,
because different storage may use different types for the same handle.

