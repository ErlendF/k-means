#include "brute_force_kd_tree.h"
int move_cluster_centers(Point* points, Point* clusters, int* belongs_to) {
  int i, j, cluster;
  int moved = 0;
  int counts[num_clusters];
  long double sum_dims[num_clusters][dims];
  long double new_coord;

  // Initializing
  for (i = 0; i < num_clusters; i++) {
    counts[i] = 0;
    for (j = 0; j < dims; j++) {
      sum_dims[i][j] = 0;
    }
  }
  // Calculating sums
  for (i = 0; i < num_points; i++) {
    cluster = belongs_to[i];
    counts[cluster]++;
    for (j = 0; j < dims; j++) {
      sum_dims[cluster][j] += points[i].coords[j];
    }
  }

  for (i = 0; i < num_clusters; i++) {
    if (counts[i] == 0) {
      continue;
    }

    for (j = 0; j < dims; j++) {
      new_coord = sum_dims[i][j] / (long double)counts[i];

      if (clusters[i].coords[j] != new_coord) {
        moved = 1;
      }

      clusters[i].coords[j] = new_coord;
    }
  }

  return moved;
}

void calc_belongs_to(Point* points, Point* clusters, int* belongs_to) {
  int i, j;
  long double dist, tmpdist;
  int cluster;
  Node root = build_kd_tree(clusters);
  ClusterDist* best;
  for (i = 0; i < num_points; i++) {
    best->distance = RAND_MAX;
    search_kd_tree(root, points[i], best);
    belongs_to[i] = best->cluster.ID;
  }
}
