// Parallel brute force method

#ifndef PL_BF_H
#define PL_BF_H
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "consts.h"
#include "utils.h"

void pcalc_belongs_to(Point *points, Point *clusters, int *belongs_to);
int pmove_cluster_centers(Point *points, Point *clusters, int *belongs_to);  // , int counts[][num_clusters], long double sum_dims[][num_clusters][dims]
#endif