// Parallellized brute force method using KD trees

#ifndef PL_BF_KD_TREE_H
#define PL_BF_KD_TREE_H
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "consts.h"
#include "kd_tree.h"
#include "pl_bf.h"
#include "utils.h"

void kd_pcalc_belongs_to(Point *points, Point *clusters, int *belongs_to);
#endif