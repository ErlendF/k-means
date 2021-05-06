#include "main.h"

#include <math.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

// int *cell_clust;  // The cluster closest to the cell
int *cell_valid;  // 1 if there is only one cluster closest to the cell, 0 otherwise
int *grid_points_closest;
int tot_num_cells;
int num_cell_corners;
double mt1, mt2;  //timing variables

Point *grid_corners;

Point points[num_points];
Point clusters[num_clusters];

int belongs_to[num_points];

void generate_uniform_list_of_points();
void generate_clustered_list_of_points();
int move_cluster_centers();
void init_uniform_cluster_centers();
// void pkmeans();
void pcalc_belongs_to();
int pmove_cluster_centers();

int main(int argc, char *argv[]) {
  // srand(time(NULL));    // set rand seed

  // printf("Test\n");
  // init_grid();
  // int i;
  // for (i = 0; i < num_cell_corners; i++) {
  //   printf("%d: (%Lf, %Lf, %Lf)\n", i, grid_corners[i].coords[0], grid_corners[i].coords[1], grid_corners[i].coords[2]);
  // }

  generate_clustered_list_of_points();  //Sequential
  init_uniform_cluster_centers();       //Sequential?
  // pkmeans(num_points, num_clusters, dims, points, clusters, belongs_to);
  // init_grid();
  //calculate_grid_closest_cluster();

  do {
    calc_belongs_to(points, clusters, belongs_to);  //Parallel
  } while (move_cluster_centers() != 0);            //Parallel?

  // mt1 = omp_get_wtime();

  // do {
  //   pcalc_belongs_to();                    //Parallel
  // } while (pmove_cluster_centers() != 0);  //Parallel?

  // printf("TEST\n");
  // mt2 = omp_get_wtime();

  // print_belongs_to();
  print_cluster_centers(clusters);
  print_measures(points, clusters, belongs_to);

  write_points_to_file(points);
  write_clusters_to_file(clusters);

  printf("Clusters found in %f seconds\n", mt2 - mt1);
}

void generate_uniform_list_of_points() {
  int i, j;  // iteration variables

  for (i = 0; i < num_points; i++) {
    for (j = 0; j < dims; j++) {
      points[i].coords[j] = (long double)(rand() % max_num) /
                            decimal;  // generating points with two decimals
    }
  }
  return;
}

void generate_clustered_list_of_points() {
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
            (long double)(rand() % max_num) / decimal;
      }
    }

    for (k = 0; k < dims; k++) {
      points[i].coords[k] =
          (((long double)(rand() % (num_points * decimal)) / decimal) + (long double)cluster_offsets[k]);
    }
  }

  printf("Num clusters: %d\n", cluster_count);
}

int move_cluster_centers() {
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

void init_uniform_cluster_centers() {
  int i, j;
  for (i = 0; i < num_clusters; i++) {
    int pt = rand() % num_points;
    for (j = 0; j < dims; j++) {
      clusters[i].coords[j] = (long double)(rand() % max_num) / decimal;
    }
  }
}

/*
LALALALALALALALALALALALALALLALA her prøver jeg parallel shit damdidamdidamdidam

--------------------------------------------------------------------------------------------------------------------------
##########################################################################################################################
--------------------------------------------------------------------------------------------------------------------------
##########################################################################################################################
--------------------------------------------------------------------------------------------------------------------------
##########################################################################################################################
--------------------------------------------------------------------------------------------------------------------------
##########################################################################################################################
--------------------------------------------------------------------------------------------------------------------------
##########################################################################################################################
--------------------------------------------------------------------------------------------------------------------------
##########################################################################################################################


void pkmeans(int num_points, int num_clusters, int dims, Point *points, Point *clusters, int *belongs_to) {
  int num_threads = omp_get_num_threads();
  int thread_id = omp_get_thread_num();
  do {
    pcalc_belongs_to(num_points, num_clusters, belongs_to, dims, clusters);  //Parallel
  } while (pmove_cluster_centers(num_clusters, dims, num_points, belongs_to, points) != 0);
}
*/

void pcalc_belongs_to() {
  int i, j, k, cluster;
  int num_threads = omp_get_num_threads();
  //printf("Num threads = %d\n", num_threads);
  omp_set_num_threads(4);
  long double dist, tmpdist;
#pragma omp parallel
  {
//printf("Belongs To\n");
#pragma omp parallel for schedule(static, num_points / num_threads) private(dist, tmpdist, cluster)
    for (i = 0; i < num_points; i++) {
      dist = RAND_MAX;
      //printf("Thread %d of %d\n", omp_get_thread_num, omp_get_num_threads);
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
}

int pmove_cluster_centers() {
  //int num_threads = omp_get_num_threads();
  //int num_threads = 4;
  //printf("Num_threads = %d\n", num_threads);
  int mv;
  int moved = 0;

#pragma omp parallel
  {
    int num_threads = omp_get_num_threads();
    int thread_id = omp_get_thread_num();
    int i, j, cluster;
    //  int thread_id;

    int counts[num_clusters];
    long double sum_dims[num_clusters][dims];
    long double new_coord;
    //  int num_threads;

    //printf("Thread id = %d of %d\n", thread_id, num_threads);
    //printf("Num threads = %d\n", num_threads);
    // Initializing
    //#pragma omp barrier

    //printf("Initializing\n");
//#pragma omp for private(i, j) schedule(static, num_clusters/num_threads)
#pragma omp master
    for (i = 0; i < num_clusters; i++) {
      counts[i] = 0;
      for (j = 0; j < dims; j++) {
        sum_dims[i][j] = 0;
      }
    }

    //printf("sums\n");
#pragma omp barrier
//printf("num_points/Num_threads%d\n", num_points/num_threads);
// Calculating sums TODO FIX
#pragma omp for private(cluster, i, j) schedule(static, num_points / num_threads)
    for (i = 0; i < num_points; i++) {
      cluster = belongs_to[i];
      counts[cluster]++;
      for (j = 0; j < dims; j++) {
        sum_dims[cluster][j] += points[i].coords[j];
      }
    }
#pragma omp barrier
//printf("moving centers\n");
//#pragma omp for private(i, j, new_coord)
#pragma omp master
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
  }
  return moved;
}