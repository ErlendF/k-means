#include "main.h"

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

int main(int argc, char *argv[]) {
  // srand(time(NULL));    // set rand seed

  char *parallel = "s";

  if (argc > 1) {
    parallel = argv[1];
  }

  generate_clustered_list_of_points(points);
  init_uniform_cluster_centers(clusters);

  // print_cluster_centers(clusters);
  mt1 = omp_get_wtime();
  if (parallel == "p") {
    do {
      pcalc_belongs_to(points, clusters, belongs_to);
      // pcalc_belongs_to();
    } while (pmove_cluster_centers(points, clusters, belongs_to) != 0);
  } else {
    do {
      calc_belongs_to(points, clusters, belongs_to);
      // pcalc_belongs_to();
    } while (move_cluster_centers(points, clusters, belongs_to) != 0);
  }

  mt2 = omp_get_wtime();

  printf("TEST\n");

  // print_belongs_to();
  print_cluster_centers(clusters);
  print_measures(points, clusters, belongs_to);

  write_points_to_file(points);
  write_clusters_to_file(clusters);

  printf("Clusters found in %f seconds\n", mt2 - mt1);
}
