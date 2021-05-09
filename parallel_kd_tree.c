
#include "parallel_kd_tree.h"

void kd_pcalc_belongs_to(Point *points, Point *clusters, int *belongs_to) {
  int i, j, cluster;

  int num_threads = omp_get_max_threads();
  long double dist, tmpdist;
  Node *root = build_kd_tree(clusters);
#pragma omp parallel for private(i, j, dist, tmpdist, cluster)
  for (i = 0; i < num_points; i++) {
    ClusterDist best;
    best.distance = RAND_MAX;
    search_kd_tree(*root, points[i], &best);
    // for (j = 0; j < num_clusters; j++) {
    //   long double distance = calc_dist(points[i], clusters[j]);
    //   if (distance < best.distance) {
    //     printf("You done fucked up mate!\n");
    //   }
    // }
    belongs_to[i] = best.cluster.ID;
  }
}