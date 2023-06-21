#include <assert.h>
#include <stdio.h>
#include "predefine.h"
#include "partition/partition.h"
#include "topology/structure.h"
#include "property/type.h"
#include "index/internal_id.h"
#include "list_chain.h"

GRIN_GRAPH get_graph(const char* uri, int p) {
#ifdef GRIN_ENABLE_GRAPH_PARTITION
  GRIN_PARTITIONED_GRAPH pg =
      grin_get_partitioned_graph_from_storage(uri);
  GRIN_PARTITION_LIST local_partitions = grin_get_local_partition_list(pg);
  assert(p < grin_get_partition_list_size(pg, local_partitions));
  GRIN_PARTITION partition =
      grin_get_partition_from_list(pg, local_partitions, p);
  GRIN_PARTITION_ID partition_id = grin_get_partition_id(pg, partition);
  GRIN_PARTITION p1 = grin_get_partition_by_id(pg, partition_id);
  if (!grin_equal_partition(pg, partition, p1)) {
    printf("partition not match\n");
  }
  grin_destroy_partition(pg, p1);
  GRIN_GRAPH g = grin_get_local_graph_by_partition(pg, partition);
  grin_destroy_partition(pg, partition);
  grin_destroy_partition_list(pg, local_partitions);
  grin_destroy_partitioned_graph(pg);
#else
  GRIN_GRAPH g = grin_get_graph_from_storage(uri);
#endif
  return g;
}

void test_vertex_list_chain(const char* uri) {
  GRIN_GRAPH g = get_graph(uri, 0);
  GRIN_VERTEX_LIST_CHAIN vlc = grin_get_vertex_list_chain_of_all_types(g);
  GRIN_VERTEX_LIST_CHAIN_ITERATOR iter = grin_get_vertex_list_chain_begin(g, vlc);
  while (!grin_is_vertex_list_chain_end(g, iter)) {
    GRIN_VERTEX v = grin_get_vertex_from_vertex_list_chain_iter(g, iter);
#if defined(GRIN_ENABLE_VERTEX_INTERNAL_ID_INDEX) && defined(GRIN_WITH_VERTEX_PROPERTY)
    GRIN_VERTEX_TYPE vt = grin_get_vertex_type(g, v);
    long long int id = grin_get_vertex_internal_id_by_type(g, vt, v);
    printf("vertex id: %lld\n", id);
#endif
    grin_destroy_vertex(g, v);
    grin_get_next_vertex_list_chain_iter(g, iter);
  }
  grin_destroy_vertex_list_chain_iter(g, iter);
  grin_destroy_vertex_list_chain(g, vlc);
  grin_destroy_graph(g);
}

void test_adjacent_list_chain(const char* uri, GRIN_DIRECTION d) {
  GRIN_GRAPH g = get_graph(uri, 0);
  GRIN_VERTEX_LIST_CHAIN vlc = grin_get_vertex_list_chain_of_all_types_select_master(g);
  GRIN_VERTEX_LIST_CHAIN_ITERATOR iter = grin_get_vertex_list_chain_begin(g, vlc);
  while (!grin_is_vertex_list_chain_end(g, iter)) {
    GRIN_VERTEX v = grin_get_vertex_from_vertex_list_chain_iter(g, iter);
    GRIN_VERTEX_TYPE vt = grin_get_vertex_type(g, v);
    GRIN_ADJACENT_LIST_CHAIN alc = grin_get_adjacent_list_chain_of_all_edge_types(g, d, v);
    GRIN_ADJACENT_LIST_CHAIN_ITERATOR iter2 = grin_get_adjacent_list_chain_begin(g, alc);
    while (!grin_is_adjacent_list_chain_end(g, iter2)) {
      GRIN_EDGE e = grin_get_edge_from_adjacent_list_chain_iter(g, iter2);
      if (d == OUT) {
        GRIN_VERTEX v2 = grin_get_dst_vertex_from_edge(g, e);
        GRIN_VERTEX_TYPE vt2 = grin_get_vertex_type(g, v2);
      #ifdef GRIN_ENABLE_VERTEX_INTERNAL_ID_INDEX
        long long int id1 = grin_get_vertex_internal_id_by_type(g, vt, v);
        long long int id2 = grin_get_vertex_internal_id_by_type(g, vt2, v2);
        GRIN_EDGE_TYPE et = grin_get_edge_type(g, e);
        printf("OUT %s %lld %s %s %lld\n", grin_get_vertex_type_name(g, vt), id1,
               grin_get_edge_type_name(g, et), grin_get_vertex_type_name(g, vt2), id2);
      #endif
        grin_destroy_vertex(g, v2);
      } else {
        GRIN_VERTEX v2 = grin_get_src_vertex_from_edge(g, e);
        GRIN_VERTEX_TYPE vt2 = grin_get_vertex_type(g, v2);
      #ifdef GRIN_ENABLE_VERTEX_INTERNAL_ID_INDEX
        long long int id1 = grin_get_vertex_internal_id_by_type(g, vt, v);
        long long int id2 = grin_get_vertex_internal_id_by_type(g, vt2, v2);
        GRIN_EDGE_TYPE et = grin_get_edge_type(g, e);
        printf("IN %s %lld %s %s %lld\n", grin_get_vertex_type_name(g, vt2), id2,
               grin_get_edge_type_name(g, et), grin_get_vertex_type_name(g, vt), id1);
      #endif
      }
      grin_destroy_edge(g, e);
      grin_get_next_adjacent_list_chain_iter(g, iter2);
    }
    grin_destroy_adjacent_list_chain_iter(g, iter2);
    grin_destroy_adjacent_list_chain(g, alc);
    grin_destroy_vertex(g, v);
    grin_get_next_vertex_list_chain_iter(g, iter);
  }
  grin_destroy_vertex_list_chain_iter(g, iter);
  grin_destroy_vertex_list_chain(g, vlc);
  grin_destroy_graph(g);
}

int main(int argc, char** argv) {
#if defined(GRIN_WITH_VERTEX_PROPERTY) && defined(GRIN_WITH_EDGE_PROPERTY) && \
    defined(GRIN_WITH_VERTEX_PROPERTY_NAME) && defined(GRIN_WITH_EDGE_PROPERTY_NAME)
  test_vertex_list_chain(argv[1]);
  test_adjacent_list_chain(argv[1], OUT);
  test_adjacent_list_chain(argv[1], IN);
#endif
  return 0;
}