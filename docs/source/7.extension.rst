Extension
--------------

GRIN Extension offers high-level APIs to expand functionality, 
as well as a default implementation using GRIN basic(low-level) APIs
Certain GRIN Extension APIs can be overwritten by a more efficient 
implementation from storage.

List Chain
^^^^^^^^^^^

Since v0.1, to keep the basic APIs low-level abstraction, 
GRIN only provides topology lists (i.e., vertex/edge/adjacent list) 
of a single vertex or edge type in property graph.

However, in many cases, we need to traverse all the vertices in a property graph.
Although the user can first iterate all the vertex types, and then get the
vertex list of each vertex type to traverse, this does increase many boilerplate
code for the user. Thus, we provide a high-level handle ``VertexListChain`` and 
related APIs in GRIN extension to handle this case.

Since we call them list chains, we only provide iterators to traverse the list chain,
but not array-like accessment.

