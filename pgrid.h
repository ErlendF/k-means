#ifndef PGRID_H
#define PGRID_H

#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "consts.h"
#include "utils.h"

void pgrid_calc(Point *points, Point grid[], Point *clusters, int *belongs_to, int num_cell_corners, int num_grid_cells, int num_corners, int *grid_points_closest, int grid_corners[][(int)(pow(2, dims) + 0.5)], int *cell_closest_cluster, int belongs_to_cell[]);
void pinit_grid(int num_grid_cells, int num_cell_corners, int grid_corners[][(int)(pow(2, dims) + 0.5)], Point grid[], Point points[], int belongs_to_cell[]);
#endif