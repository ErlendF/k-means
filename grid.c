#include "grid.h"

void init_grid(int num_grid_cells, int num_cell_corners, int grid_corners[][(int)(pow(2, dims) + 0.5)], Point grid[], Point points[], int belongs_to_cell[]) {
  int i, j, k, h;
  int num_corners = (int)(pow(2, dims) + 0.5);
  long double cell_width = ((long double)max_num * 1.01) / (long double)num_cells;

  find_corners(grid_corners);
  printf("Num grid cells: %d, cell width = %Lf\n", num_grid_cells, cell_width);

  if (dims > 3) {
    printf("Max dims for grid = 3, you set %d\n", dims);
    return;
  }

  for (i = 0; i < num_cell_corners; i++) {
    for (j = 0; j < dims; j++) {
      switch (j) {
        case 0:
          grid[i].coords[j] = (long double)(i % (num_cells + 1)) * cell_width;
          break;
        case 1:
          grid[i].coords[j] = (long double)((i / (num_cells + 1)) % (num_cells + 1)) * cell_width;
          break;
        case 2:
          grid[i].coords[j] = (long double)(i / ((num_cells + 1) * (num_cells + 1))) * cell_width;
          break;
      }
    }
  }
  calc_point_cell(num_cell_corners, num_grid_cells, grid, points, belongs_to_cell, grid_corners);
}

void calc_point_cell(int num_cell_corners, int num_grid_cells, Point grid[], Point *points, int belongs_to_cell[], int grid_corners[][(int)(pow(2, dims) + 0.5)]) {
  int i, j, idx;
  long double cell_width = ((long double)max_num * 1.01) / (long double)num_cells;
  for (i = 0; i < num_points; i++) {
    idx = 0;
    for (j = 0; j < dims; j++) {
      idx += ((int)points[i].coords[j] / (int)cell_width) * (int)(pow(num_cells, j) + 0.5);
    }

    belongs_to_cell[i] = idx;
  }
}

// void calculate_grid_closest_cluster(int num_cell_corners, int num_grid_cells, int *grid_points_closest, Point grid[], Point *clusters) {
//   int i, j, k, cluster;
//   long double dist, tmpdist;
//   for (i = 0; i < num_cell_corners; i++) {
//     dist = RAND_MAX;
//     cluster = -1;
//     for (j = 0; j < num_clusters; j++) {
//       tmpdist = calc_dist(grid[i], clusters[j]);
//       if (tmpdist < dist) {
//         dist = tmpdist;
//         cluster = j;
//       }
//     }
//     grid_points_closest[i] = cluster;
//   }
// }

void grid_closest_cluster(Point grid[], Point *clusters, int num_cell_corners, int num_grid_cells, int num_corners, int *grid_points_closest, int grid_corners[][(int)(pow(2, dims) + 0.5)], int *cell_closest_cluster) {
  int i, j, k, prev_value, cluster;
  long double dist, tmpdist;
  for (i = 0; i < num_cell_corners; i++) {
    dist = RAND_MAX;
    cluster = -1;
    for (j = 0; j < num_clusters; j++) {
      tmpdist = calc_dist(grid[i], clusters[j]);
      if (tmpdist < dist) {
        dist = tmpdist;
        cluster = j;
      }
    }
    grid_points_closest[i] = cluster;
    printf("Grid point (%Lf, %Lf) belongs to cluster %d\n", grid[i].coords[0], grid[i].coords[1], cluster);
  }

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
    printf("Cell %d belongs to %d\n", i, prev_value);
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

void grid_calc_belongs_to(Point *points, Point *clusters, int *belongs_to, int *cell_closest_cluster, int belongs_to_cell[]) {
  int i, j;
  long double dist, tmpdist;
  int cluster;
  for (i = 0; i < num_points; i++) {
    if (cell_closest_cluster[belongs_to_cell[i]] != -1) {
      belongs_to[i] = cell_closest_cluster[belongs_to_cell[i]];
      continue;
    }

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