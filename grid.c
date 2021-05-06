#include "grid.h"

// https://stackoverflow.com/questions/29787310/does-pow-work-for-int-data-type-in-c
void init_grid(int *tot_num_cells, int *num_cell_corners, int *cell_valid, int *grid_points_closest, Point *grid_corners) {
  *tot_num_cells = (int)(pow(num_cells, dims) + 0.5);  // TODO: test :)
  *num_cell_corners = (int)(pow(num_cells + 1, dims) + 0.5);
  printf("Num cell points: %d\nTot num cells: %d\n", *num_cell_corners, *tot_num_cells);

  cell_valid = (int *)malloc(sizeof(int) * *(tot_num_cells));
  grid_points_closest = (int *)malloc(sizeof(int) * *(num_cell_corners));  // Holds clost cluster nr.
  grid_corners = (Point *)malloc(sizeof(Point) * *(num_cell_corners));

  int i, j;

  // TODO: handle edge cases :)
  for (i = 0; i < *num_cell_corners; i++) {
    for (j = 0; j < dims; j++) {
      grid_corners[i].coords[j] = (i % (int)(pow(num_cells + 1, j + 1) + 0.5)) / (int)(pow(num_cells + 1, j) + 0.5);  // TODO: gang med cell width
    }
  }
}

// TODO: Point -> index

// TODO: Index -> Point

void calculate_grid_closest_cluster(int num_cell_corners, int tot_num_cells, int *grid_points_closest, int *cell_valid, Point *grid_corners, Point *clusters) {
  int i, j, k, cluster;
  long double dist, tmpdist;
  for (i = 0; i < num_cell_corners; i++) {
    dist = RAND_MAX;
    cluster = -1;
    for (j = 0; j < num_clusters; j++) {
      tmpdist = calc_dist(grid_corners[i], clusters[j]);
      if (tmpdist < dist) {
        dist = tmpdist;
        cluster = j;
        if ((j / k) % k + 1 != 0) {
          //   idx += (int)(pow(num_cells + 1, (j / k + 1) % k + 1));
          // }
        }

        int closest, idx, valid;
        int corners = (int)(pow(2, dims) + 0.5);
        for (i = 0; i < tot_num_cells; i++) {
          valid = 1;
          closest = -1;
          for (j = 0; j < corners; j++) {
            idx = i + (i / num_cells);
            for (k = 1; k < dims; k++) {
              //grid_corners

              //[4]       [0][1]=[0+num_cell]  [2]=[0+num_cell^dim], 3=[1]+num_cell^2

              // if ((j / k) % k + 1 != 0) {
              //   idx += (int)(pow(num_cells + 1, (j / k + 1) % k + 1));
              // }
            }
            printf("Cell %d, corner %d: idx %d\n", i, j, idx);

            if (closest == -1) {
              closest = grid_points_closest[idx];
            } else if (closest != grid_points_closest[idx]) {
              cell_valid[i] = 0;
              break;
            }
          }
        }
      }
    }
  }
}