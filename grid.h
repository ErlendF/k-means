#ifndef GRID_H
#define GRID_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "consts.h"
#include "utils.h"

void init_grid(int num_grid_cells, int num_cell_corners, int *cell_closest_cluster, int *grid_points_closest, int grid_corners[][(int)(pow(2, dims) + 0.5)], Point grid[]);
void calc_cell_closest_cluster(int num_grid_cells, int num_corners, int *grid_points_closest, int grid_corners[][(int)(pow(2, dims) + 0.5)], int *cell_closest_cluster);
void find_corners(int grid_corners[][(int)(pow(2, dims) + 0.5)]);
#endif