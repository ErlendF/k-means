#include "grid.h"

void init_grid(int num_grid_cells, int *cell_closest_cluster, int *grid_points_closest, Point grid_corners[][(int)(pow(2, dims) + 0.5)]) {
  int i, j, k, h;
  int num_corners = (int)(pow(2, dims) + 0.5);
  printf("Num grid cells: %d\n", num_grid_cells);

  cell_closest_cluster = (int *)malloc(sizeof(int) * num_grid_cells);

  // int cell_width = (max_num * 1.01) / num_cells;

  printf("dims %d, num_corners %d, num_grid cells %d\n\n", dims, num_corners, num_grid_cells);
  // for (i = 0; i < dims; i++) {
  //   for (j = 0; j < num_corners; j++) {
  //     for (k = 0; k < num_grid_cells; k++) {
  //       // printf("Trying: dims %d, num_corners %d, num_grid cells %d\n", i, j, k);
  //       if (k % num_cells == 0) {
  //         if (k == 0) {
  //           if (j == i && j != 0) {
  //             grid_corners[k][j].coords[i] = 1;
  //           } else {
  //             grid_corners[k][j].coords[i] = 0;
  //           }
  //         } else if (j == 0 || i == 0) {
  //           grid_corners[k][j].coords[i] = 0;
  //         } else {
  //           grid_corners[k][j].coords[i] = 1;
  //         }
  //       } else {
  //         int value = (int)(grid_corners[k - 1][j].coords[i] + 1);
  //         printf("Setting grid[%d][%d].coords[%d] to %d\n", k, j, i, value);
  //         grid_corners[k][j].coords[i] = value;
  //       }
  //       if (k == 0 && j == 3) printf("[0][3]= (%Lf, %Lf)\n", grid_corners[k][j].coords[0], grid_corners[k][j].coords[1]);
  //       // printf("Cell %d corner %d, dim %d: %Lf\n", k, j, i, grid_corners[k][j].coords[i]);
  //     }
  //   }
  // }
  for (i = 0; i < dims; i++) {
    int mod = (int)(pow(2, i) + 0.5);
    for (j = 0; j < num_corners; j++) {
      int first = (int)(pow(num_cells, i) + 0.5);
      for (k = 0; k < num_grid_cells; k++) {
        if (k % first == 0) {
          if (j / mod % 2 == 0) {
            grid_corners[k][j].coords[i] = 0;
          } else {
            grid_corners[k][j].coords[i] = 1;
          }
        } else {
          int value = (int)(grid_corners[k - 1][j].coords[i] + 1);
          printf("Setting grid[%d][%d].coords[%d] to %d\n", k, j, i, value);
          grid_corners[k][j].coords[i] = value;
        }
      }
    }
  }

  for (k = 0; k < num_grid_cells; k++) {
    for (j = 0; j < num_corners; j++) {
      printf("Cell[%d][%d], (%Lf, %Lf)\n", k, j, grid_corners[k][j].coords[0], grid_corners[k][j].coords[1]);
    }
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

void calc_cell_closest_cluster(int num_grid_cells) {
  int i, j, k;
  int num_corners = (int)(pow(2, dims) + 0.5);
  for (i = 0; i < num_grid_cells; i++) {
    int counts[dims];
    for (j = 0; j < dims; j++) {
      counts[j] = 0;
    }

    for (j = 0; j < num_corners; j++) {
      int corner_idx = i + (i / num_cells);
      for (k = 0; k < dims; k++) {
      }
    }
  }
}

// if ((i / k) % k + 1 != 0) {
//   idx += (int)(pow(num_cells + 1, (j / k + 1) % k + 1));
// }
// }

//     int closest, idx, valid;
//     int corners = (int)(pow(2, dims) + 0.5);
//     for (i = 0; i < num_grid_cells; i++) {
//       valid = 1;
//       closest = -1;
//       for (j = 0; j < corners; j++) {
//         idx = i + (i / num_cells);
//         for (k = 1; k < dims; k++) {
//           //grid_corners

//           //[4]       [0][1]=[0+num_cell]  [2]=[0+num_cell^dim], 3=[1]+num_cell^2

//           // if ((j / k) % k + 1 != 0) {
//           //   idx += (int)(pow(num_cells + 1, (j / k + 1) % k + 1));
//           // }
//         }
//         printf("Cell %d, corner %d: idx %d\n", i, j, idx);

//         if (closest == -1) {
//           closest = grid_points_closest[idx];
//         } else if (closest != grid_points_closest[idx]) {
//           cell_valid[i] = 0;
//           break;
//         }
//       }
//     }
//   }
// }
// }

void find_corners() {
  int i, j, k, idx, cluster;
  int t_num_cells = 27;
  int corners = 8;
  int count = 0;
  for (i = 0; i < t_num_cells; i++) {
    for (j = 0; j < corners; j++) {
      idx = i + i / num_cells;
      if (i != 0 && i % (int)(pow(num_cells, 2) + 0.5) == 0) {
        count += 4;
      }
      idx += count;

      for (k = 0; k < dims; k++) {
        if ((j / (int)(pow(2, k) + 0.5)) % 2 != 0) {
          idx += (int)(pow(num_cells + 1, k) + 0.5);
        }
      }
      printf("Cell %d, corner %d: idx %d\n", i, j, idx);
    }
  }
}