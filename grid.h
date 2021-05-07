#ifndef GRID_H
#define GRID_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "consts.h"
#include "utils.h"

void init_grid(int *tot_num_cells, int *num_cell_corners, int *cell_valid, int *grid_points_closest, Point *grid_corners);
void calculate_grid_closest_cluster(int num_cell_corners, int tot_num_cells, int *grid_points_closest, int *cell_valid, Point *grid_corners, Point *clusters);

#endif