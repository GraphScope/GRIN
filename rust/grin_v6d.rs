#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinGraph = *mut ::std::os::raw::c_void;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinVertex = u64;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinEdge = *mut ::std::os::raw::c_void;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinVertexList = *mut ::std::os::raw::c_void;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinVertexListIterator = *mut ::std::os::raw::c_void;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinAdjacentList = *mut ::std::os::raw::c_void;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinAdjacentListIterator = *mut ::std::os::raw::c_void;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinPartitionedGraph = *mut ::std::os::raw::c_void;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinPartition = u32;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinPartitionList = *mut ::std::os::raw::c_void;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinPartitionId = u32;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinVertexRef = i64;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinVertexType = u32;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinVertexTypeList = *mut ::std::os::raw::c_void;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinVertexProperty = u64;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinVertexPropertyList = *mut ::std::os::raw::c_void;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinVertexTypeId = u32;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinVertexPropertyId = u32;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinEdgeType = u32;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinEdgeTypeList = *mut ::std::os::raw::c_void;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinVevType = *mut ::std::os::raw::c_void;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinVevTypeList = *mut ::std::os::raw::c_void;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinEdgeProperty = u64;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinEdgePropertyList = *mut ::std::os::raw::c_void;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinEdgeTypeId = u32;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinEdgePropertyId = u32;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub type GrinRow = *mut ::std::os::raw::c_void;
extern "C" {
}

#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_DATATYPE: GrinDatatype = GRIN_DATATYPE_UNDEFINED;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_GRAPH: GrinGraph = std::ptr::null_mut();
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_VERTEX: GrinVertex = u64::MAX;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_EDGE: GrinEdge = std::ptr::null_mut();
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_VERTEX_LIST: GrinVertexList = std::ptr::null_mut();
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_VERTEX_LIST_ITERATOR: GrinVertexListIterator = std::ptr::null_mut();
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_ADJACENT_LIST: GrinAdjacentList = std::ptr::null_mut();
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_ADJACENT_LIST_ITERATOR: GrinAdjacentListIterator = std::ptr::null_mut();
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_PARTITIONED_GRAPH: GrinPartitionedGraph = std::ptr::null_mut();
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_PARTITION: GrinPartition = u32::MAX;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_PARTITION_LIST: GrinPartitionList = std::ptr::null_mut();
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_PARTITION_ID: GrinPartitionId = u32::MAX;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_VERTEX_REF: GrinVertexRef = -1;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_VERTEX_TYPE: GrinVertexType = u32::MAX;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_VERTEX_TYPE_LIST: GrinVertexTypeList = std::ptr::null_mut();
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_VERTEX_PROPERTY: GrinVertexProperty = u64::MAX;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_VERTEX_PROPERTY_LIST: GrinVertexPropertyList = std::ptr::null_mut();
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_VERTEX_TYPE_ID: GrinVertexTypeId = u32::MAX;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_VERTEX_PROPERTY_ID: GrinVertexPropertyId = u32::MAX;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_EDGE_TYPE: GrinEdgeType = u32::MAX;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_EDGE_TYPE_LIST: GrinEdgeTypeList = std::ptr::null_mut();
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_VEV_TYPE: GrinVevType = std::ptr::null_mut();
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_VEV_TYPE_LIST: GrinVevTypeList = std::ptr::null_mut();
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_EDGE_PROPERTY: GrinEdgeProperty = u64::MAX;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_EDGE_PROPERTY_LIST: GrinEdgePropertyList = std::ptr::null_mut();
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_EDGE_TYPE_ID: GrinEdgeTypeId = u32::MAX;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_EDGE_PROPERTY_ID: GrinEdgePropertyId = u32::MAX;
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_ROW: GrinRow = std::ptr::null_mut();
#[cfg(feature = "grin_features_enable_v6d")]
#[allow(unused)]
pub const GRIN_NULL_SIZE: u32 = u32::MAX;
