#include "grid.h"

void init_grid(int num_grid_cells, int num_cell_corners, int *cell_closest_cluster, int *grid_points_closest, int grid_corners[][(int)(pow(2, dims) + 0.5)], Point grid[]) {
  int i, j, k, h;
  int num_corners = (int)(pow(2, dims) + 0.5);
  long double cell_width = ((long double)max_num * 1.01) / (long double)num_cells;

  find_corners(grid_corners);
  printf("Num grid cells: %d, cell width = %Lf\n", num_grid_cells, cell_width);

  cell_closest_cluster = (int *)malloc(sizeof(int) * num_grid_cells);
  grid_points_closest = (int *)malloc(sizeof(int) * (int)(pow(num_cells + 1, dims) + 0.5));

  for (i = 0; i < num_cell_corners; i++) {
    for (j = 0; j < dims; j++) {
      grid[i].coords[j] = -1;
    }
  }

  if (dims >= 3) {
    for (i = 0; i < num_cell_corners; i++) {
      grid[i].coords[2] = (long double)(i / ((num_cells + 1) * (num_cells + 1))) * cell_width;
    }
  }

  if (dims >= 2) {
    for (i = 0; i < num_cell_corners; i++) {
      grid[i].coords[1] = (long double)((i / (num_cells + 1)) % (num_cells + 1)) * cell_width;
    }
  }

  for (i = 0; i < num_cell_corners; i++) {
    grid[i].coords[0] = (long double)(i % (num_cells + 1)) * cell_width;
  }

  for (k = 0; k < num_cell_corners; k++) {
    printf("Corner[%d], (%Lf, %Lf, %Lf)\n", k, grid[k].coords[0], grid[k].coords[1], grid[k].coords[2]);
  }
}

void calculate_grid_closest_cluster(int num_cell_corners, int num_grid_cells, int *grid_points_closest, int *cell_valid, Point *grid_corners, Point *clusters) {
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
      }
    }
    grid_points_closest[i] = cluster;
  }
}

void calc_cell_closest_cluster(int num_grid_cells, int num_corners, int *grid_points_closest, int grid_corners[][(int)(pow(2, dims) + 0.5)], int *cell_closest_cluster) {
  int i, j, k, prev_value;

  for (i = 0; i < num_grid_cells; i++) {
    for (j = 0; j < num_corners; j++) {
      if (j == 0) {
        prev_value = grid_points_closest[grid_corners[i][j]];
      } else {
        if (grid_points_closest[grid_corners[i][j]] != prev_value) {
          prev_value = -1;
          break;
        }
      }
    }
    cell_closest_cluster[i] = prev_value;
  }
}

void find_corners(int grid_corners[][(int)(pow(2, dims) + 0.5)]) {
  int i, j, k, idx, cluster;
  int t_num_cells = (int)(pow(num_cells, dims) + 0.5);
  int corners = (int)(pow(2, dims) + 0.5);
  int cells_sq = (num_cells) * (num_cells);
  int cells_one_sq = (num_cells + 1) * (num_cells + 1);
  for (i = 0; i < t_num_cells; i++) {
    for (j = 0; j < corners; j++) {
      idx = i % cells_sq +                   // 1d
            (i / num_cells) % (num_cells) +  // 2d
            (i / cells_sq) * cells_one_sq;   // 3d

      for (k = 0; k < dims; k++) {
        if ((j / (int)(pow(2, k) + 0.5)) % 2 != 0) {
          idx += (int)(pow(num_cells + 1, k) + 0.5);
        }
      }
      grid_corners[i][j] = idx;
    }
  }
}