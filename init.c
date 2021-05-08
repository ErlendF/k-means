#include "init.h"

void generate_uniform_list_of_points(Point *points) {
  int i, j;  // iteration variables

  for (i = 0; i < num_points; i++) {
    for (j = 0; j < dims; j++) {
      points[i].coords[j] = (long double)(rand() % max_num) /
                            decimal;  // generating points with two decimals
    }
  }
  return;
}

void generate_clustered_list_of_points(Point *points) {
  int i, j, k;

  long double cluster_offsets[dims];
  for (i = 0; i < dims; i++) {
    cluster_offsets[i] = 0;
  }

  int cluster_size = 0;
  int cluster_count = 0;

  for (i = 0, j = 0; i < num_points; i++, cluster_size--) {
    if (cluster_size <= 0) {
      cluster_count++;
      cluster_size = fmax(((rand() % num_points) / 10) + num_points / 100, 5);
      printf("New cluster size: %d\n", cluster_size);
      for (k = 0; k < dims; k++) {
        cluster_offsets[k] =
            (long double)(rand() % (max_num)) / decimal;
      }
    }

    for (k = 0; k < dims; k++) {
      points[i].coords[k] =
          (((long double)(rand() % (max_num * decimal)) / decimal) + (long double)cluster_offsets[k]);
    }
  }

  printf("Num clusters: %d\n", cluster_count);
}

void init_uniform_cluster_centers(Point *clusters) {
  int i, j;
  for (i = 0; i < num_clusters; i++) {
    // int pt = rand() % num_points;
    for (j = 0; j < dims; j++) {
      clusters[i].coords[j] = (long double)(rand() % max_num) / decimal;
    }
  }
}
