// Parallel grid method

#include "pl_grid.h"

#include "pl_bf.h"

void pgrid_calc(Point *points, Point grid[], Point *clusters, int *belongs_to, int num_cell_corners, int num_grid_cells, int num_corners, int *grid_points_closest, int grid_corners[][(int)(pow(2, dims) + 0.5)], int *cell_closest_cluster, int belongs_to_cell[]) {
  do {
#pragma omp parallel
    {
      int i, j, k, prev_value, cluster;
      long double dist, tmpdist;
#pragma omp for
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
      }
#pragma omp barrier
#pragma omp for
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
        // printf("Cell %d belongs to %d\n", i, prev_value);
        cell_closest_cluster[i] = prev_value;
      }
#pragma omp for
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
  } while (pmove_cluster_centers(points, clusters, belongs_to) != 0);
}

void pinit_grid(int num_grid_cells, int num_cell_corners, int grid_corners[][(int)(pow(2, dims) + 0.5)], Point grid[], Point points[], int belongs_to_cell[]) {
  int num_corners = (int)(pow(2, dims) + 0.5);
  long double cell_width = ((long double)max_num * 1.01) / (long double)num_cells;
  int t_num_cells = (int)(pow(num_cells, dims) + 0.5);
  int corners = (int)(pow(2, dims) + 0.5);
  int cells_sq = (num_cells) * (num_cells);
  int cells_one_sq = (num_cells + 1) * (num_cells + 1);

  if (dims > 3) {
    printf("Max dims for grid = 3, you set %d\n", dims);
    exit(1);
  }

#pragma omp parallel  //private(i, j, k, idx)
  {
    int i, j, k, h, idx;
#pragma omp for schedule(static, t_num_cells / omp_get_num_threads())
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

#pragma omp for schedule(static, num_cell_corners / omp_get_num_threads())
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

#pragma omp for schedule(static, num_points / omp_get_num_threads())
    for (i = 0; i < num_points; i++) {
      idx = 0;
      for (j = 0; j < dims; j++) {
        idx += ((int)points[i].coords[j] / (int)cell_width) * (int)(pow(num_cells, j) + 0.5);
      }

      belongs_to_cell[i] = idx;
    }
  }
}
