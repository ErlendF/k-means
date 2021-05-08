#include "main.h"

int num_grid_cells;
int num_cell_corners;
double mt1, mt2;  //timing variables

Point points[num_points];
Point clusters[num_clusters];

int belongs_to[num_points];
int belongs_to_cell[num_points];
void sequential_bruteforce();
void parallel_bruteforce();
void sequential_grid();
void parallel_grid();

int main(int argc, char *argv[]) {
  int i, j;
  generate_clustered_list_of_points(points);
  init_uniform_cluster_centers(clusters);
  // print_cluster_centers(clusters);

  int parallel = 0;
  int sequential = 0;
  int grid_mode = 0;
  int bruteforce = 0;
  // int kd =0;

  // if (argc > 1) {
  //   parallel = *argv[1];
  // }

  for (i = 1; i < argc; i++) {
    switch (*argv[i]) {
      case 'p':
        parallel = 1;
        break;
      case 's':
        sequential = 1;
        break;
      case 'b':
        bruteforce = 1;
        break;
      // case 'k':
      //   kd = 1;
      //   break;
      case 'g':
        grid_mode = 1;
        break;
    }
  }

  if (parallel + sequential + grid_mode + bruteforce < 1) {
    printf("No inputs given, running sequential brute force mode");
    sequential = 1;
    bruteforce = 1;
  }

  // printf("parallel=%d, sequential = %d, grid = %d, bruteforce = %d\n", parallel, sequential, grid_mode, bruteforce);

  if (grid_mode == 1) {
    if (sequential == 1) {
      sequential_grid();
    }
    if (parallel == 1) {
      parallel_grid();
    }
  }
  if (bruteforce == 1) {
    if (sequential == 1) {
      sequential_bruteforce();
    }

    if (parallel == 1) {
      parallel_bruteforce();
    }
  }

  write_points_to_file(points);
  write_clusters_to_file(clusters);

  return 0;
}

void sequential_bruteforce() {
  Point clusters_copy[num_clusters];
  int i, j;
  for (i = 0; i < num_clusters; i++) {
    for (j = 0; j < dims; j++) {
      clusters_copy[i].coords[j] = clusters[i].coords[j];
    }
  }

  printf("\n\nStarting sequential run..\n");
  mt1 = omp_get_wtime();
  do {
    calc_belongs_to(points, clusters_copy, belongs_to);
  } while (move_cluster_centers(points, clusters_copy, belongs_to) != 0);
  mt2 = omp_get_wtime();
  print_measures(points, clusters_copy, belongs_to);
  printf("Finished running in sequential bruteforce in %f seconds\n", mt2 - mt1);
}

void parallel_bruteforce() {
  Point clusters_copy[num_clusters];
  int i, j;
  for (i = 0; i < num_clusters; i++) {
    for (j = 0; j < dims; j++) {
      clusters_copy[i].coords[j] = clusters[i].coords[j];
    }
  }

  printf("Running parallel with %d threads!\n", omp_get_max_threads());
  mt1 = omp_get_wtime();
  do {
    pcalc_belongs_to(points, clusters_copy, belongs_to);
  } while (pmove_cluster_centers(points, clusters_copy, belongs_to) != 0);
  mt2 = omp_get_wtime();
  print_measures(points, clusters_copy, belongs_to);
  printf("Finished running in parallel bruteforce in %f seconds\n", mt2 - mt1);
}

void sequential_grid() {
  printf("Running sequential grid mode..\n");
  Point clusters_copy[num_clusters];
  int i, j;
  double mt3;
  for (i = 0; i < num_clusters; i++) {
    for (j = 0; j < dims; j++) {
      clusters_copy[i].coords[j] = clusters[i].coords[j];
    }
  }

  num_grid_cells = (int)(pow(num_cells, dims) + 0.5);
  num_cell_corners = (int)(pow(num_cells + 1, dims) + 0.5);
  int num_corners = (int)(pow(2, dims) + 0.5);
  int grid_corners[num_grid_cells][num_corners];

  int cell_closest_cluster[num_grid_cells];
  int grid_points_closest[num_cell_corners];

  Point grid[num_cell_corners];

  mt1 = omp_get_wtime();

  init_grid(num_grid_cells, num_cell_corners, grid_corners, grid, points, belongs_to_cell);
  mt3 = omp_get_wtime();
  do {
    grid_closest_cluster(grid, clusters_copy, num_cell_corners, num_grid_cells, num_corners, grid_points_closest, grid_corners, cell_closest_cluster);
    grid_calc_belongs_to(points, clusters_copy, belongs_to, cell_closest_cluster, belongs_to_cell);
  } while (move_cluster_centers(points, clusters_copy, belongs_to) != 0);
  mt2 = omp_get_wtime();
  print_measures(points, clusters_copy, belongs_to);
  printf("Finished running in parallel grid in %f seconds, init took %f seconds\n", mt2 - mt1, mt3 - mt1);
}

void parallel_grid() {
  double mt3;
  printf("Running parallel grid mode with %d threads!\n", omp_get_max_threads());
  Point clusters_copy[num_clusters];
  int i, j;
  for (i = 0; i < num_clusters; i++) {
    for (j = 0; j < dims; j++) {
      clusters_copy[i].coords[j] = clusters[i].coords[j];
    }
  }

  num_grid_cells = (int)(pow(num_cells, dims) + 0.5);
  num_cell_corners = (int)(pow(num_cells + 1, dims) + 0.5);
  int num_corners = (int)(pow(2, dims) + 0.5);
  int grid_corners[num_grid_cells][num_corners];

  int cell_closest_cluster[num_grid_cells];
  int grid_points_closest[num_cell_corners];

  Point grid[num_cell_corners];

  mt1 = omp_get_wtime();

  pinit_grid(num_grid_cells, num_cell_corners, grid_corners, grid, points, belongs_to_cell);
  mt3 = omp_get_wtime();

  do {
    grid_closest_cluster(grid, clusters_copy, num_cell_corners, num_grid_cells, num_corners, grid_points_closest, grid_corners, cell_closest_cluster);
    pgrid_calc_belongs_to(points, clusters_copy, belongs_to, cell_closest_cluster, belongs_to_cell);
  } while (pmove_cluster_centers(points, clusters_copy, belongs_to) != 0);
  mt2 = omp_get_wtime();
  print_measures(points, clusters_copy, belongs_to);
  printf("Finished running in parallel grid in %f seconds, init took %f seconds\n", mt2 - mt1, mt3 - mt1);
}