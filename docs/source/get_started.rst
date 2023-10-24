Getting Started
----------------

Get Graph from Storage
^^^^^^^^^^^^^^^^^^^^^^
GRIN offers a set of APIs to retrieve graph data in storage.
The first API we need is to get a graph handle for a graph from storage.
The API is:

.. code-block:: c 
    
    GRIN_GRAPH grin_get_graph_from_storage(const char* uri);

This API takes a URI as its parameter, which is a string that identifies the graph in storage.

Different storage systems may define different required parameters in the URI:

- gart://{etcd_endpoint}?prefix={etcd_prefix}&version={version}
- graphar://{yaml_path}?partition_num={partition_num}&strategy={strategy}
- v6d://{object_id}?ipc_socket={ipc_socket} where ipc_socket is optional.

The return value of this API is a GRIN graph handle.

Handle
^^^^^^^^^
A handle is an opaque value that identifies an object in GRIN. The type of a handle is
predefined by the storage using ``typedef`` in ``C``. For example, the handle type
``GRIN_GRAPH`` we mentioned earlier could be declared as ``void*`` in some storage
implementation.

It is important to note that users should not make any assumptions about the type or
value of a handle. Handles should be used as input parameters for related APIs to access
the object they represent.

For instance, let's consider an example where we use the mentioned API to obtain a graph
handle. We can then use this handle to check whether the graph is directed.
The code is as follows:

.. code-block:: c 
  :linenos:

    #include "predefine.h"
    #include "topology/structure.h"

    int main(int argc, char** argv) {
        GRIN_GRAPH g = grin_get_graph_from_storage(argv[1]);

        if (grin_is_directed(g)) {
            printf("The graph is directed");
        } else {
            printf("The graph is undirected");
        }
    }

In the code snippet, the first line includes the ``predefine.h`` header file, which contains the
necessary typedef for ``GRIN_GRAPH`` and other handles in GRIN. The second line includes the 
``topology/structure.h`` header file, which declares the API ``bool grin_is_directed(GRIN_GRAPH)``. 
Moving on, in the fifth line of the ``main`` function, the graph handle ``g`` is obtained from the 
storage using a given uri from the command-line. Finally, in the seventh line, we can check whether 
the graph represented by ``g`` is directed.

GRIN provides various handle types, each representing a specific graph concept. These handle
types include graph, vertex, edge, vertex list, edge list, adjacent list, and more. We will introduce
these handle types in detail when discussing related APIs.

Return Values
^^^^^^^^^^^^^^
The most common return values of GRIN APIs are handles. These handles correspond to the resources
created by the APIs. To free these resources after use, GRIN provides corresponding ``destroy`` APIs.
For example, when calling the ``grin_get_graph_from_storage`` API, a graph handle is returned, which
can be freed using the ``grin_destroy_graph`` API. It's important to note that GRIN APIs are stateless,
meaning that the responsibility of memory management lies with the users, rather than the storages.

Some APIs may return values other than handles, such as primitive types like ``int`` and ``double``.
For example, primitive values returned by APIs to get vertex property values are stored on the ``stack``,
meaning they do not need to be freed. We will provide more
detailed information about these return values and whether or not there are corresponding
``destroy`` APIs, when discussing related APIs.

Error Handling
^^^^^^^^^^^^^^^
Each handle type also has a ``invalid`` value. 
For example, the ``GRIN_GRAPH`` handle type has a ``invalid`` value denoted as ``GRIN_NULL_GRAPH``. 
When the ``grin_get_graph_from_storage`` API cannot find the graph with the given uri from the storage,
it returns the ``GRIN_NULL_GRAPH`` value. This value can be used to check whether the API call is
successful. An example code snippet is as follows:

.. code-block:: c 

    #include "predefine.h"
    #include "topology/structure.h"

    int main(int argc, char** argv) {
        GRIN_GRAPH g = grin_get_graph_from_storage(argv[1]);

        if (g == GRIN_NULL_GRAPH) {
            printf("The graph does not exist");
        } else {
            printf("The graph exists");
        }
    }

The ``GRIN_NULL_GRAPH`` value is also defined in the ``predefine.h`` header file,
using a ``#define`` statetment as follows:

.. code-block:: c 

    #define GRIN_NULL_GRAPH NULL

However, it is hard to define a ``invalid`` value for primitive types like ``int`` or ``double``.
Therefore, GRIN uses the ``error code`` mechanism to indicate errors for these return value types.
The details can be found in the ``Error Code`` section in ``Common Functional APIs``.