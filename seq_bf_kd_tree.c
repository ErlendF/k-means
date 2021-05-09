// Brute-force method using KD trees

#include "seq_bf_kd_tree.h"

void kd_calc_belongs_to(Point* points, Point* clusters, int* belongs_to) {
  int i, j;
  long double dist, tmpdist;
  int cluster;
  Node* root = build_kd_tree(clusters);
  ClusterDist best;
  for (i = 0; i < num_points; i++) {
    best.distance = RAND_MAX;
    search_kd_tree(*root, points[i], &best);
    belongs_to[i] = best.cluster.ID;
  }
  release_kd_tree(root);
}
