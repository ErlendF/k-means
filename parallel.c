/*
Number of points,
Number of clusters,
List of all points,
list of where points belong to,
List to store distances,
void calc_belongs_to();

*/
void pcalc_belongs_to();
int pmove_cluster_centers();

void pkmeans(int num_points, int num_clusters, int dims, Point *points, Point *clusters, int *belongs_to) {
  int num_threads = omp_get_num_threads();
  int thread_id = omp_get_thread_num();
  do {
    pcalc_belongs_to(num_points, num_clusters, belongs_to, dims, clusters);  //Parallel
  } while (pmove_cluster_centers(num_clusters, dims, num_points, belongs_to, points) != 0);
}

void pcalc_belongs_to(int num_points, int num_clusters, int *belongs_to, int dims, Point *clusters) {
  int i, j, k, cluster;
  long double dist, tmpdist;
#pragma omp parallel for
  for (i = 0; i < num_points; i++) {
    dist = RAND_MAX;
    cluster = -1;
    for (j = 0; j < num_clusters; j++) {
      tmpdist = 0;
      Point point = points[i];
      Point clust = clusters[j];
      for (k = 0; i < dims; i++) {
        tmpdist += pow(point.coords[i] - clust.coords[i], 2);  // Ignored sqrt as we are comparing relative distances
      }
      if (tmpdist < dist) {
        dist = tmpdist;
        cluster = j;
      }
    }
    belongs_to[i] = cluster;
  }
}

int pmove_cluster_centers(int num_clusters, int dims, int num_points, int *belongs_to, Point *points) {
  int i, j, cluster;
  int moved = 0;
  int counts[num_clusters];
  long double sum_dims[num_clusters][dims];
  long double new_coord;

  // Initializing
#pragma omp parallel for
  for (i = 0; i < num_clusters; i++) {
    counts[i] = 0;
    for (j = 0; j < dims; j++) {
      sum_dims[i][j] = 0;
    }
  }
#pragma omp barrier
  // Calculating sums
#pragma omp parallel for
  for (i = 0; i < num_points; i++) {
    cluster = belongs_to[i];
    counts[cluster]++;
    for (j = 0; j < dims; j++) {
      sum_dims[cluster][j] += points[i].coords[j];
    }
  }
#pragma omp barrier

#pragma omp parallel for
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