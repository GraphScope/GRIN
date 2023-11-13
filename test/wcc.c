#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>     
#include "predefine.h"
#include "common/error.h"
#include "common/message.h"
#include "index/external_id.h"
#include "index/internal_id.h"
#include "index/label.h"
#include "index/order.h"
#include "index/pk.h"
#include "partition/partition.h"
#include "partition/reference.h"
#include "partition/topology.h"
#include "property/primarykey.h"
#include "property/property.h"
#include "property/propertylist.h"
#include "property/row.h"
#include "property/topology.h"
#include "property/type.h"
#include "property/value.h"
#include "topology/adjacentlist.h"
#include "topology/edgelist.h"
#include "topology/structure.h"
#include "topology/vertexlist.h"

int main(int argc, char** argv) {
  GRIN_GRAPH g = get_graph(argc, argv, 0);

  struct timeval t1, t2;
  double elapsedTime;
  gettimeofday(&t1, NULL);

  GRIN_VERTEX_TYPE vt = grin_get_vertex_type_by_name(g, "person");

  long long int lb = grin_get_vertex_internal_id_lower_bound_by_type(g, vt);
  long long int ub = grin_get_vertex_internal_id_upper_bound_by_type(g, vt);

  printf("lb: %lld, ub: %lld\n", lb, ub);

  long long* comp = (long long*)malloc(sizeof(long long) * (ub - lb));
  bool* next_modified = (bool*)malloc(sizeof(bool) * (ub - lb));

  GRIN_VERTEX_LIST iv = grin_get_vertex_list_by_type_select_master(g, vt);
  size_t iv_size = grin_get_vertex_list_size(g, iv);

  for (size_t i = 0; i < iv_size; ++i) {
    GRIN_VERTEX v = grin_get_vertex_from_list(g, iv, i);
    long long int iid = grin_get_vertex_internal_id_by_type(g, vt, v);
    GRIN_VERTEX_REF vf = grin_get_vertex_ref_by_vertex(g, v);
    long long int ivf = grin_serialize_vertex_ref_as_int64(g, vf);

    if (i == 0 || i == iv_size - 1) {
      printf("Inner %lld %lld\n", iid, ivf);
    }

    comp[iid - lb] = ivf;
    grin_destroy_vertex(g, v);
    grin_destroy_vertex_ref(g, vf);
  }

  GRIN_VERTEX_LIST ov = grin_get_vertex_list_by_type_select_mirror(g, vt);
  size_t ov_size = grin_get_vertex_list_size(g, ov);

  for (size_t i = 0; i < ov_size; ++i) {
    GRIN_VERTEX v = grin_get_vertex_from_list(g, ov, i);
    long long int iid = grin_get_vertex_internal_id_by_type(g, vt, v);
    GRIN_VERTEX_REF vf = grin_get_vertex_ref_by_vertex(g, v);
    long long int ivf = grin_serialize_vertex_ref_as_int64(g, vf);

    if (i == 0 || i == ov_size - 1) {
      printf("Outer %lld %lld\n", iid, ivf);
    }

    comp[iid - lb] = ivf;
    grin_destroy_vertex(g, v);
    grin_destroy_vertex_ref(g, vf);
  }


  gettimeofday(&t2, NULL);
  elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
  elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0 / 1000.0; 
  printf("------------- 2 -------------: %lf s.\n", elapsedTime);

  GRIN_EDGE_TYPE et = grin_get_edge_type_by_name(g, "knows");
  for (size_t i = 0; i < iv_size; ++i) {
    GRIN_VERTEX v = grin_get_vertex_from_list(g, iv, i);
    long long int iid = grin_get_vertex_internal_id_by_type(g, vt, v) - lb;
    long long cid = comp[iid];

    GRIN_ADJACENT_LIST al = grin_get_adjacent_list_by_edge_type(g, OUT, v, et);
    size_t al_size = grin_get_adjacent_list_size(g, al);
    for (size_t j = 0; j < al_size; ++j) {
      GRIN_VERTEX u = grin_get_neighbor_from_adjacent_list(g, al, j);
      long long int uid = grin_get_vertex_internal_id_by_type(g, vt, u) - lb;
      if (comp[uid] > cid) {
        comp[uid] = cid;
        next_modified[uid] = true;
      }
      grin_destroy_vertex(g, u);
    }
    grin_destroy_adjacent_list(g, al);

    al = grin_get_adjacent_list_by_edge_type(g, IN, v, et);
    al_size = grin_get_adjacent_list_size(g, al);
    for (size_t j = 0; j < al_size; ++j) {
      GRIN_VERTEX u = grin_get_neighbor_from_adjacent_list(g, al, j);
      long long int uid = grin_get_vertex_internal_id_by_type(g, vt, u) - lb;
      if (comp[uid] > cid) {
        comp[uid] = cid;
        next_modified[uid] = true;
      }
      grin_destroy_vertex(g, u);
    }
  }

  gettimeofday(&t2, NULL);
  elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
  elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0 / 1000.0; 
  printf("------------- 3 -------------: %lf s.\n", elapsedTime);

  grin_destroy_vertex_list(g, iv);
  grin_destroy_vertex_list(g, ov);
  grin_destroy_vertex_type(g, vt);
  grin_destroy_graph(g);
  return 0;
}
