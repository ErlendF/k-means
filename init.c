#include "init.h"

// This isn't really in use.
// It was designed to generate a uniform distribution of points
void generate_uniform_list_of_points(Point *points) {
  int i, j;  // iteration variables

  for (i = 0; i < num_points; i++) {
    for (j = 0; j < dims; j++) {
      points[i].coords[j] = (long double)(rand() % max_num) / decimal;  // generating points with two decimals
    }
  }
  return;
}

// This generates random points in a roughly clustered fashion.
// The number of clusters may vary.
void generate_clustered_list_of_points(Point *points) {
  int i, j, k;

  long double cluster_offsets[dims];  // The cluster offsets is used to disperse the clusters randomly in each dimension
  int cluster_size = 0;

  for (i = 0, j = 0; i < num_points; i++, cluster_size--) {
    if (cluster_size <= 0) {  // The current cluster is "empty", generating a new cluster
      cluster_size = fmax(((rand() % num_points) / 10) + num_points / 100, 5);
      for (k = 0; k < dims; k++) {
        cluster_offsets[k] = (long double)(rand() % (max_num)) / decimal;  // generating new cluster offsets
      }
    }

    for (k = 0; k < dims; k++) {  // Generating the acutal points, and adding the cluster offsets
      points[i].coords[k] = (((long double)(rand() % (max_num * decimal)) / decimal) + (long double)cluster_offsets[k]);
    }
  }
}

// Generates a uniform distribution of cluster centers
void init_uniform_cluster_centers(Point *clusters) {
  int i, j;
  for (i = 0; i < num_clusters; i++) {
    for (j = 0; j < dims; j++) {
      clusters[i].coords[j] = (long double)(rand() % max_num) / decimal;
    }
  }
}
