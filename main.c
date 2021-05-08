#include "main.h"

int *cell_closest_cluster;  // -1 if invalid
int *grid_points_closest;
int num_grid_cells;
int num_cell_corners;
double mt1, mt2;  //timing variables

Point points[num_points];
Point clusters[num_clusters];
Point clusters_copy[num_clusters];

int belongs_to[num_points];

int main(int argc, char *argv[]) {
  int i, j;
  num_grid_cells = (int)(pow(num_cells, dims) + 0.5);
  num_cell_corners = (int)(pow(num_cells + 1, dims) + 0.5);
  int num_corners = (int)(pow(2, dims) + 0.5);
  int grid_corners[num_grid_cells][num_corners];
  Point grid[num_cell_corners];
  init_grid(num_grid_cells, num_cell_corners, cell_closest_cluster, grid_points_closest, grid_corners, grid);
  return 0;
  find_corners(grid_corners);

  for (i = 0; i < num_grid_cells; i++) {
    for (j = 0; j < num_corners; j++) {
      printf("Grid_corners[%d][%d]: %d\n", i, j, grid_corners[i][j]);
    }
  }
  return 0;
  char parallel = 'b';

  if (argc > 1) {
    parallel = *argv[1];
  }

  generate_clustered_list_of_points(points);
  init_uniform_cluster_centers(clusters);

  return 0;

  if (parallel == 'b') {
    for (i = 0; i < num_clusters; i++) {
      for (j = 0; j < dims; j++) {
        clusters_copy[i].coords[j] = clusters[i].coords[j];
      }
    }
  }

  // print_cluster_centers(clusters);
  mt1 = omp_get_wtime();
  if (parallel == 'p') {
    printf("Running parallel with %d threads!\n", omp_get_max_threads());
    do {
      pcalc_belongs_to(points, clusters, belongs_to);
    } while (pmove_cluster_centers(points, clusters, belongs_to) != 0);
  } else if (parallel == 's') {
    printf("\n\nStarting sequential run..\n");
    do {
      calc_belongs_to(points, clusters, belongs_to);
    } while (move_cluster_centers(points, clusters, belongs_to) != 0);
  } else {
    printf("Running both modes, starting sequential");
    mt1 = omp_get_wtime();
    do {
      calc_belongs_to(points, clusters, belongs_to);
    } while (move_cluster_centers(points, clusters, belongs_to) != 0);
    mt2 = omp_get_wtime();
    print_measures(points, clusters, belongs_to);
    printf("Finished running sequentially in %f seconds\n", mt2 - mt1);

    printf("\n\nStarting parallel run with %d threads..\n", omp_get_max_threads());
    mt1 = omp_get_wtime();
    do {
      pcalc_belongs_to(points, clusters_copy, belongs_to);
    } while (pmove_cluster_centers(points, clusters_copy, belongs_to) != 0);
    mt2 = omp_get_wtime();
    print_measures(points, clusters_copy, belongs_to);
    printf("Finished running in parallel in %f seconds\n", mt2 - mt1);

    return 0;
  }

  mt2 = omp_get_wtime();

  print_cluster_centers(clusters);
  print_measures(points, clusters, belongs_to);

  write_points_to_file(points);
  write_clusters_to_file(clusters);

  printf("Clusters found in %f seconds\n", mt2 - mt1);
}
