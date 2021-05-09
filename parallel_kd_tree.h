#ifndef PARALLEL_KD_H
#define PARALLEL_KD_H
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "KD_tree.h"
#include "consts.h"
#include "utils.h"

void kd_pcalc_belongs_to(Point *points, Point *clusters, int *belongs_to);
#endif