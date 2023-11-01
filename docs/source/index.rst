.. GRIN documentation master file, created by
   sphinx-quickstart on Thu May 11 17:08:47 2023.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to GRIN's documentation!
================================

.. \outline{GRIN stands for the Graph Retrieval INterface in GraphScope||1}
.. \outline{GRIN offers graph computing engines in GraphScope a unique way to retrieve graph data stored in different storage systems in GraphScope||1}
.. \outline{To achieve the goal, GRIN abstracts the common graph retrieval requirements in graph computing systems into categories, such as topology, property, partition, index, etc.||1}
.. \outline{GRIN also abstracts the compute-specific graph retrieval requirements into traits, such as traversal, filter, partition strategy, external/internal ids, etc.||1}
.. \outline{GRIN offers APIs for the above abstracted requirements, and organize them with a series of C macros.||1}
.. \outline{Each graph storage system that supports GRIN can filter out the APIs that it cannot support using the C macros.||1}
.. \outline{Then for the rest APIs that the storage can support, it should implement the APIs efficiently, and avoid hidden overheads, so that the computing systems can these APIs without worring about the performance.||2}
.. introduction

GRIN, which stands for Graph Retrieval INterface, is an interface designed to simplify the retrieval of graph data 
from various storage systems within GraphScope. 
It organizes **common** graph retrieval needs into
categories such as topology, property, partition, and index, 
as well as **compute-specific** graph
retrieval requirements as traits including traversal, filter, partition strategy, 
external/internal ids, etc.

GRIN offers APIs to fulfill these abstracted requirements.
These APIs are defined in C and can be utilized in systems developed in various programming languages such as C++, Rust, and Java. 
GRIN organizes its APIs using categorized header files. 
Additionally, C macros are utilized by GRIN to allow storage systems that support GRIN 
to filter out APIs that they are unable to handle.
This ensures compatibility while maximizing efficiency. 
The supported APIs are then implemented in the storage systems to prioritize efficient retrieval with minimal hidden overhead.
By using GRIN, computing systems can utilize the supported APIs without worrying about performance concerns.

The documentation is organized as follows:

First, we introduce the basic concepts of GRIN, including the handle, API, and macros.

Next, we dive into the details of each API category, starting with the ``topology`` APIs.
We then introduce the Labeled Property Graph (LPG) data model along with the ``property`` APIs.
Within the LPG data model, we also address the additional ``topology``-related APIs that handle the transition from a simple graph to a LPG.
After that, we introduce the ``partition`` APIs, which are designed for partitioned graphs.
Since graph partitioning is another layer on top of simple graphs and LPGs, we also provide additional ``topology`` and ``property``-related APIs for this purpose.
This three-level "stacking" of ``topology``, ``property``, and ``partition`` forms the fundamental organization of GRIN APIs.

Next, we introduce the ``index`` APIs, which are designed for graph indexing.
Following that, we present the ``common`` APIs, which include the common functions of GRIN, such as *schema* message and *error code*.
Finally, we end the per-category API introduction by presenting the ``extension`` APIs, which are a series of advanced APIs with default implementations that utilize the basic APIs of GRIN.

Lastly, we provide the developer guide of GRIN for developers to follow.

.. toctree::
   :maxdepth: 2
   :caption: Contents:
   :glob:

   get_started
   api/1.topology_api
   api/2.property_api
   api/3.partition_api
   api/4.index_api
   api/5.common_api
   api/6.extension_api
   guide/storage
   guide/user

.. getting_started

.. apis
   .. graph topology & apis
   .. LPG data model & apis
   .. graph partition strategy & partition apis
   .. graph index & apis
   .. common functions & apis
   .. grin extension & apis

.. developer_guide
   .. for graph storage system developer
      .. add submodule
      .. implement principles
   .. for graph computing engine developer
      .. v6d cmake example
      .. api naming




.. **GRIN** is a proposed standard graph retrieval interface in GraphScope.
.. The goal of GRIN is to provide a common way for the graph computing engines to 
.. retrieve graph data stored in different storage systems in GraphScope, 
.. and to simplify the integration of these engines with each other.

.. GRIN is defined in C, which makes it portable to systems written in different 
.. programming languages, such as C++, Rust and Java. 
.. It provides a set of common operations and data structure handles that can 
.. be used to access graph data, regardless of the underlying storage system. 

.. These operations include:

.. - *Traversal*: navigating the graph structure to explore relationships between vertices
.. - *Retrieval*: retrieving the data and properties of vertices and edges
.. - *Filter*: filtering data structures with partitioning or property conditions

.. GRIN is designed to be read-only, meaning that it does not provide operations for
.. modifying the graph data. This decision was made to simplify the implementation 
.. of GRIN and ensure that it can be used safely with any storage system.


..    0.get_started
..    1.return_value
..    2.api_naming
..    4.partition_api   
..    6.index_api
..    7.extension



