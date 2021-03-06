// Sequential initialization of grid

#ifndef GRID_H
#define GRID_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "consts.h"
#include "utils.h"

void init_grid(int num_grid_cells, int num_cell_corners, int grid_corners[][(int)(pow(2, dims) + 0.5)], Point grid[], Point points[], int belongs_to_cell[]);
void calc_point_cell(int num_cell_corners, int num_grid_cells, Point grid[], Point *points, int *belongs_to_cell, int grid_corners[][(int)(pow(2, dims) + 0.5)]);
void find_corners(int grid_corners[][(int)(pow(2, dims) + 0.5)]);
#endif