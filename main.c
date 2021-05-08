#include "main.h"

#define test_iter 1
#define thread_iter 3

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
int test;

int main(int argc, char *argv[]) {
  int i, j;
  generate_clustered_list_of_points(points);
  init_uniform_cluster_centers(clusters);
  // print_cluster_centers(clusters);

  int parallel = 0;
  int sequential = 0;
  int grid_mode = 0;
  int bruteforce = 0;

  test = 0;
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
      case 't':
        test = 1;
        break;
      // case 'k':
      //   kd = 1;
      //   break;
      case 'g':
        grid_mode = 1;
        break;
    }
  }

  if (parallel + sequential + grid_mode + bruteforce + test < 1) {
    printf("No inputs given, running parallel brute-force mode\n");
    parallel = 1;
    bruteforce = 1;
  }

  // printf("parallel=%d, sequential = %d, grid = %d, bruteforce = %d\n", parallel, sequential, grid_mode, bruteforce);

  if (test) {
    printf("Running test mode, every %dth thread, be patient...!\n", thread_iter);
    init_performance_file();
    int num_threads;
    for (i = 0; i < test_iter; i++) {
      sequential_bruteforce();
      sequential_grid();
    }
    int max_threads = omp_get_max_threads();
    for (i = 0; i <= max_threads; i += 1) {
      for (j = 0; j < test_iter; j++) {
        num_threads = i;
        if (i == 0) {
          num_threads = 1;
        }
        omp_set_num_threads(num_threads);
        parallel_bruteforce();
        parallel_grid();
      }
    }
    if (num_threads != omp_get_max_threads()) {
      for (i = 0; i < test_iter; i++) {
        num_threads = omp_get_max_threads();
        omp_set_num_threads(num_threads);
        parallel_bruteforce();
        parallel_grid();
      }
    }
  } else {
    if (grid_mode) {
      if (sequential) {
        sequential_grid();
      }
      if (parallel) {
        parallel_grid();
      }
    }
    if (bruteforce) {
      if (sequential) {
        sequential_bruteforce();
      }

      if (parallel) {
        parallel_bruteforce();
      }
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

  printf("\nStarting sequential brute-force algorithm..\n");
  mt1 = omp_get_wtime();
  do {
    calc_belongs_to(points, clusters_copy, belongs_to);
  } while (move_cluster_centers(points, clusters_copy, belongs_to) != 0);
  mt2 = omp_get_wtime();
  printf("Finished sequential brute-force in %f seconds.\n", mt2 - mt1);
  if (!test) {
    print_measures(points, clusters_copy, belongs_to);
  } else {
    write_performance(-1, "Sequential", "Brute-force", mt2 - mt1);
  }
}

void parallel_bruteforce() {
  Point clusters_copy[num_clusters];
  int i, j;
  for (i = 0; i < num_clusters; i++) {
    for (j = 0; j < dims; j++) {
      clusters_copy[i].coords[j] = clusters[i].coords[j];
    }
  }

  printf("\nStarting parallel brute-force algorithm with %d threads..\n", omp_get_max_threads());
  mt1 = omp_get_wtime();
  do {
    pcalc_belongs_to(points, clusters_copy, belongs_to);
  } while (pmove_cluster_centers(points, clusters_copy, belongs_to) != 0);
  mt2 = omp_get_wtime();
  printf("Finished parallel brute-force in %f seconds.\n", mt2 - mt1);
  if (!test) {
    print_measures(points, clusters_copy, belongs_to);
  } else {
    write_performance(omp_get_max_threads(), "Parallel", "Brute-force", mt2 - mt1);
  }
}

void sequential_grid() {
  printf("\nStarting sequential grid algorithm..\n");
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
  printf("Finished sequential grid in %f seconds.\n", mt2 - mt1);
  if (!test) {
    print_measures(points, clusters_copy, belongs_to);
  } else {
    write_performance(-1, "Sequential", "Grid", mt2 - mt1);
  }
}

void parallel_grid() {
  double mt3;
  printf("\nStarting parallel grid algorithm with %d threads..\n", omp_get_max_threads());
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
  printf("Finished parallel grid in %f seconds.\n", mt2 - mt1);
  if (!test) {
    print_measures(points, clusters_copy, belongs_to);
  } else {
    write_performance(omp_get_max_threads(), "Parallel", "Grid", mt2 - mt1);
  }
}