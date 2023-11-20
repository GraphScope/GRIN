#define GRIN_FEATURES_ENABLE_ALL
#define GRIN_RUST_CODEGEN

#include "common/enum_types.h"
#include "template/predefine.h"
#include "topology/adjacentlist.h"
#include "topology/edgelist.h"
#include "topology/structure.h"
#include "topology/vertexlist.h"
#include "partition/partition.h"
#include "partition/reference.h"
#include "partition/topology.h"
#include "property/primarykey.h"
#include "property/property.h"
#include "property/propertylist.h"
#include "property/row.h"
#include "property/topology.h"
#include "property/type.h"
#include "index/label.h"
#include "index/order.h"
#include "index/internal_id.h"
#include "index/pk.h"
#include "common/error.h"
#include "common/message.h"

#ifdef GRIN_RUST_CODEGEN
/// GRIN_FEATURES_ENABLE_ALL
/// RUST_KEEP pub const GRIN_NULL_DATATYPE: GrinDatatype = GRIN_DATATYPE_UNDEFINED;
/// RUST_KEEP pub const GRIN_NULL_GRAPH: GrinGraph = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_VERTEX: GrinVertex = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_EDGE: GrinEdge = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_VERTEX_DATA: GrinVertexData = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_VERTEX_LIST: GrinVertexList = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_VERTEX_LIST_ITERATOR: GrinVertexListIterator = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_ADJACENT_LIST: GrinAdjacentList = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_ADJACENT_LIST_ITERATOR: GrinAdjacentListIterator = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_EDGE_DATA: GrinEdgeData = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_EDGE_LIST: GrinEdgeList = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_EDGE_LIST_ITERATOR: GrinEdgeListIterator = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_PARTITIONED_GRAPH: GrinPartitionedGraph = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_PARTITION: GrinPartition = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_PARTITION_LIST: GrinPartitionList = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_PARTITION_ID: GrinPartitionId = u32::MAX;
/// RUST_KEEP pub const GRIN_NULL_VERTEX_REF: GrinVertexRef = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_EDGE_REF: GrinEdgeRef = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_VERTEX_TYPE: GrinVertexType = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_VERTEX_TYPE_LIST: GrinVertexTypeList = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_VERTEX_PROPERTY: GrinVertexProperty = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_VERTEX_PROPERTY_LIST: GrinVertexPropertyList = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_VERTEX_TYPE_ID: GrinVertexTypeId = u32::MAX;
/// RUST_KEEP pub const GRIN_NULL_VERTEX_PROPERTY_ID: GrinVertexPropertyId = u32::MAX;
/// RUST_KEEP pub const GRIN_NULL_EDGE_TYPE: GrinEdgeType = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_EDGE_TYPE_LIST: GrinEdgeTypeList = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_EDGE_PROPERTY: GrinEdgeProperty = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_EDGE_PROPERTY_LIST: GrinEdgePropertyList = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_EDGE_TYPE_ID: GrinEdgeTypeId = u32::MAX;
/// RUST_KEEP pub const GRIN_NULL_EDGE_PROPERTY_ID: GrinEdgePropertyId = u32::MAX;
/// RUST_KEEP pub const GRIN_NULL_ROW: GrinRow = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_LABEL: GrinLabel = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_LABEL_LIST: GrinLabelList = std::ptr::null_mut();
/// RUST_KEEP pub const GRIN_NULL_SIZE: u32 = u32::MAX;
int __rust_keep_grin_null;
#endif
