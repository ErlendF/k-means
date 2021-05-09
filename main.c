#include "main.h"

#define test_iter 1
#define thread_iter 5

int num_grid_cells;    // Number of cells for grid method
int num_cell_corners;  // Number of cell corners for grid method
double mt1, mt2;       // timing variables

Point points[num_points];      // Array for storing all points
Point clusters[num_clusters];  // Array for storing all clusters

int belongs_to[num_points];       // Array for storing what cluster ID each points belongs to
int belongs_to_cell[num_points];  // Array for storing what cell ID each points belongs to

void sequential_bruteforce();  // Sequential brute-force method
void parallel_bruteforce();    // Parallel brute-force method
void sequential_grid();        // Sequential grid method
void parallel_grid();          // Parallel grid method
void sequential_kd_tree();     // Sequential brute-force KD-tree method
void parallel_kd_tree();       // Parallel brute-force KD-tree method
int test;                      // Flag to identify if test mode is activated

int main(int argc, char *argv[]) {
  generate_clustered_list_of_points(points);  // Generates random clustered points for the algorithm
  init_uniform_cluster_centers(clusters);     // Generates random start cluster centers

  int i, j;            // Iteration variables
  int parallel = 0;    // Flag for parallel run
  int sequential = 0;  // Flag for sequential run
  int grid_mode = 0;   // Flag for grid mode
  int bruteforce = 0;  // Flag for brute-force mode
  int kd_tree = 0;     // Flag for KD-tree mode

  test = 0;  //test flag default off

  //Sets values to the flags depending on the input from the makefile
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
      case 'g':
        grid_mode = 1;
        break;
      case 'k':
        kd_tree = 1;
        break;
    }
  }

  // Fallback if no input flags are given
  if (parallel + sequential + grid_mode + bruteforce + test < 1) {
    printf("No inputs given, running parallel brute-force mode\n");
    parallel = 1;
    bruteforce = 1;
  }

  // If test, we first run the sequential algorithms, then we run for test_iter iterations with every thread_iter number of threads.
  if (test) {
    printf("Running test mode, every %dth thread, be patient...!\n", thread_iter);
    init_performance_file();
    int num_threads;
    for (i = 0; i < test_iter; i++) {
      sequential_bruteforce();
      if (dims <= 3) {  // Grid mode only support up to 3 dimensions
        sequential_grid();
      }
    }
    int max_threads = omp_get_max_threads();
    for (i = 0; i <= max_threads; i += thread_iter) {
      for (j = 0; j < test_iter; j++) {
        num_threads = i;
        if (i == 0) {  // Forcing the algorithms to run with 1 thread first
          num_threads = 1;
        }
        omp_set_num_threads(num_threads);
        parallel_bruteforce();
        if (dims <= 3) {  // Grid mode only support up to 3 dimensions
          parallel_grid();
        }
      }
    }
    if (num_threads != max_threads) {    // If max threads is not divisible by thread_iter,
      for (i = 0; i < test_iter; i++) {  // we run with the max number of threads
        num_threads = max_threads;
        omp_set_num_threads(num_threads);
        parallel_bruteforce();
        if (dims <= 3) {
          parallel_grid();  // Grid mode only support up to 3 dimensions
        }
      }
    }
  } else {  // Runs algorithms depending on flags
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
    if (kd_tree) {
      if (sequential) {
        sequential_kd_tree();
      }
      if (parallel) {
        parallel_kd_tree();
      }
    }
  }

  write_points_to_file(points);      // Writes the points used to a file
  write_clusters_to_file(clusters);  // Writes the clusters used to a file

  return 0;
}

void parallel_kd_tree() {
  Point clusters_copy[num_clusters];
  int i, j;
  for (i = 0; i < num_clusters; i++) {
    for (j = 0; j < dims; j++) {
      clusters_copy[i].coords[j] = clusters[i].coords[j];
    }
  }

  printf("\nStarting parallel kd-tree algorithm..\n");
  mt1 = omp_get_wtime();
  do {
    kd_pcalc_belongs_to(points, clusters_copy, belongs_to);
  } while (pmove_cluster_centers(points, clusters_copy, belongs_to) != 0);
  mt2 = omp_get_wtime();
  printf("Finished parallel kd-tree in %f seconds.\n", mt2 - mt1);
  if (!test) {
    //print_measures(points, clusters_copy, belongs_to);
  } else {
    write_performance(-1, "Parallel", "KD-Tree", mt2 - mt1);
  }
}

void sequential_kd_tree() {
  Point clusters_copy[num_clusters];
  int i, j;
  for (i = 0; i < num_clusters; i++) {
    for (j = 0; j < dims; j++) {
      clusters_copy[i].coords[j] = clusters[i].coords[j];
    }
  }

  printf("\nStarting sequential kd-tree algorithm..\n");
  mt1 = omp_get_wtime();
  do {
    kd_calc_belongs_to(points, clusters_copy, belongs_to);
  } while (move_cluster_centers(points, clusters_copy, belongs_to) != 0);
  mt2 = omp_get_wtime();
  printf("Finished sequential kd-tree in %f seconds.\n", mt2 - mt1);
  if (!test) {
    //print_measures(points, clusters_copy, belongs_to);
  } else {
    write_performance(-1, "Parallel", "KD-Tree", mt2 - mt1);
  }
}

void sequential_bruteforce() {
  Point clusters_copy[num_clusters];
  int i, j;
  for (i = 0; i < num_clusters; i++) {  // Copies the initial generated clusters to not change the the array if used by other algorithms
    for (j = 0; j < dims; j++) {
      clusters_copy[i].coords[j] = clusters[i].coords[j];
    }
  }

  printf("\nStarting sequential brute-force algorithm..\n");
  mt1 = omp_get_wtime();
  do {  // If we move the cluster centers, we recalculate what cluster each point belongs to
    calc_belongs_to(points, clusters_copy, belongs_to);
  } while (move_cluster_centers(points, clusters_copy, belongs_to) != 0);

  mt2 = omp_get_wtime();

  // If not test printing measures (points in cluster, average distance, variation etc.), if test mode, it writes algorithm and time to a file
  if (!test) {
    print_measures(points, clusters_copy, belongs_to);
  } else {
    write_performance(-1, "Sequential", "Brute-force", mt2 - mt1);
  }
  printf("Finished sequential brute-force in %f seconds.\n", mt2 - mt1);
}

void parallel_bruteforce() {
  Point clusters_copy[num_clusters];
  int i, j;
  for (i = 0; i < num_clusters; i++) {  // Copies the initial generated clusters to not change the the array if used by other algorithms
    for (j = 0; j < dims; j++) {
      clusters_copy[i].coords[j] = clusters[i].coords[j];
    }
  }

  printf("\nStarting parallel brute-force algorithm with %d threads..\n",
         omp_get_max_threads());
  mt1 = omp_get_wtime();
  do {
    pcalc_belongs_to(points, clusters_copy, belongs_to);
  } while (pmove_cluster_centers(points, clusters_copy, belongs_to) != 0);
  mt2 = omp_get_wtime();

  if (!test) {
    print_measures(points, clusters_copy, belongs_to);
  } else {
    write_performance(omp_get_max_threads(), "Parallel", "Brute-force", mt2 - mt1);
  }
  printf("Finished parallel brute-force in %f seconds.\n", mt2 - mt1);
}

void sequential_grid() {
  printf("\nStarting sequential grid algorithm..\n");
  Point clusters_copy[num_clusters];
  int i, j;
  for (i = 0; i < num_clusters; i++) {  // Copies the initial generated clusters to not change the the array if used by other algorithms
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

  init_grid(num_grid_cells, num_cell_corners, grid_corners, grid, points,
            belongs_to_cell);
  do {
    grid_closest_cluster(grid, clusters_copy, num_cell_corners, num_grid_cells, num_corners, grid_points_closest, grid_corners, cell_closest_cluster);
    grid_calc_belongs_to(points, clusters_copy, belongs_to, cell_closest_cluster, belongs_to_cell);
  } while (move_cluster_centers(points, clusters_copy, belongs_to) != 0);
  mt2 = omp_get_wtime();

  if (!test) {
    print_measures(points, clusters_copy, belongs_to);
  } else {
    write_performance(-1, "Sequential", "Grid", mt2 - mt1);
  }
  printf("Finished sequential grid in %f seconds.\n", mt2 - mt1);
}

void parallel_grid() {
  printf("\nStarting parallel grid algorithm with %d threads..\n", omp_get_max_threads());
  Point clusters_copy[num_clusters];
  int i, j;
  for (i = 0; i < num_clusters; i++) {  // Copies the initial generated clusters to not change the the array if used by other algorithms
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
  pgrid_calc(points, grid, clusters_copy, belongs_to, num_cell_corners, num_grid_cells, num_corners, grid_points_closest, grid_corners, cell_closest_cluster, belongs_to_cell);
  mt2 = omp_get_wtime();
  if (!test) {
    print_measures(points, clusters_copy, belongs_to);
  } else {
    write_performance(omp_get_max_threads(), "Parallel", "Grid", mt2 - mt1);
  }
  printf("Finished parallel grid in %f seconds.\n", mt2 - mt1);
}
