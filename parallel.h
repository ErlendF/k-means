#ifndef PARALLEL_H
#define PARALLEL_H
#include <omp.h>
#include <stdlib.h>

#include "consts.h"
#include "utils.h"

void pcalc_belongs_to(Point *points, Point *clusters, int *belongs_to);
int pmove_cluster_centers(Point *points, Point *clusters, int *belongs_to);
#endif