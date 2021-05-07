
#include "parallel.h"

void pcalc_belongs_to(Point *points, Point *clusters, int *belongs_to) {
  int i, j, cluster;

  //printf("Num threads = %d\n", num_threads);
  // omp_set_num_threads(4);
  int num_threads = omp_get_max_threads();
  long double dist, tmpdist;
#pragma omp parallel for schedule(static, num_points / num_threads) private(i, j, dist, tmpdist, cluster)
  for (i = 0; i < num_points; i++) {
    // printf("Thread %d, i = %d\n", omp_get_thread_num(), i);
    dist = RAND_MAX;
    cluster = -1;
    for (j = 0; j < num_clusters; j++) {
      tmpdist = calc_dist(points[i], clusters[j]);
      if (tmpdist < dist) {
        dist = tmpdist;
        cluster = j;
      }
    }
    belongs_to[i] = cluster;
  }
}

int pmove_cluster_centers(Point *points, Point *clusters, int *belongs_to) {
  int num_threads = omp_get_max_threads();

  int counts[num_threads][num_clusters];
  long double sum_dims[num_threads][num_clusters][dims];

  int moved = 0;

  long double new_coord;

  int i, j, k, cluster;

#pragma omp parallel private(i, j, cluster)
  {
    int thread_id = omp_get_thread_num();
    for (i = 0; i < num_clusters; i++) {
      counts[thread_id][i] = 0;
      for (j = 0; j < dims; j++) {
        sum_dims[thread_id][i][j] = 0;
      }
    }

#pragma omp barrier
#pragma omp for  //schedule(static, num_points / omp_get_num_threads())
    for (i = 0; i < num_points; i++) {
      {
        cluster = belongs_to[i];
        counts[thread_id][cluster]++;
        for (j = 0; j < dims; j++) {
          sum_dims[thread_id][cluster][j] += points[i].coords[j];
        }
      }
    }
  }

  for (i = 1; i < num_threads; i++) {
    for (j = 0; j < num_clusters; j++) {
      counts[0][j] += counts[i][j];
      for (k = 0; k < dims; k++) {
        sum_dims[0][j][k] += sum_dims[i][j][k];
      }
    }
  }

  for (i = 0; i < num_clusters; i++) {
    if (counts[0][i] == 0) {
      continue;
    }

    for (j = 0; j < dims; j++) {
      new_coord = sum_dims[0][i][j] / (long double)counts[0][i];

      if (clusters[i].coords[j] != new_coord)
        moved = 1;

      clusters[i].coords[j] = new_coord;
    }
  }

  return moved;
}