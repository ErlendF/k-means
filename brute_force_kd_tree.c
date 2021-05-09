#include "brute_force_kd_tree.h"
int kd_move_cluster_centers(Point* points, Point* clusters, int* belongs_to) {
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

void kd_calc_belongs_to(Point* points, Point* clusters, int* belongs_to) {
  int i, j;
  long double dist, tmpdist;
  int cluster;
  //printf("Trying to build tree\n");
  Node* root = build_kd_tree(clusters);
  //printf("Managed to build tree\n");
  ClusterDist best;
  // best = malloc(sizeof(ClusterDist));
  for (i = 0; i < num_points; i++) {
    best.distance = RAND_MAX;
    search_kd_tree(*root, points[i], &best);
    // if (best[0].cluster.ID != belongs_to[i]) {
    //   printf("Point: %d swappes from %d to %d. Curr distance %.2Lf\n", i, belongs_to[i], best[0].cluster.ID, best[0].distance);
    // }
    // for (j = 0; j < num_clusters; j++) {
    //   double distance = calc_dist(clusters[j], points[i]);
    //   if (distance < best.distance) {
    //     printf("Algorthim fakks up at: %d. Found %d distance: %.2f. Better is %d distance: %.2f\n", i, best.cluster.ID, best.distance, j, distance);
    //     display_point(points[i]);
    //     printf("###### TREE ######\n");
    //     display_kd_tree(*root);
    //     printf("###### DONE ######\n");

    //     break;
    //   }
    // }
    belongs_to[i] = best.cluster.ID;
  }
  realse_kd_tree(root);
}
