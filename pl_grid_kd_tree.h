// Parallelized grid method using KD trees

#ifndef PL_GRID_KD_TREE_H
#define PL_GRID_KD_TREE_H

#include "consts.h"
#include "kd_tree.h"
#include "pl_bf.h"
#include "pl_grid.h"
#include "utils.h"

void pkd_grid_calc(Point *points, Point grid[], Point *clusters, int *belongs_to, int num_cell_corners, int num_grid_cells, int num_corners, int *grid_points_closest, int grid_corners[][(int)(pow(2, dims) + 0.5)], int *cell_closest_cluster, int belongs_to_cell[]);
#endif