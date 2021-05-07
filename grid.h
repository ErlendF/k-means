#ifndef GRID_H
#define GRID_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "consts.h"
#include "utils.h"

void init_grid(int num_grid_cells, int *cell_closest_cluster, int *grid_points_closest, Point grid_corners[][(int)(pow(2, dims) + 0.5)]);
void calculate_grid_closest_cluster(int num_cell_corners, int num_grid_cells, int *grid_points_closest, int *cell_valid, Point *grid_corners, Point *clusters);
void find_corners();
#endif