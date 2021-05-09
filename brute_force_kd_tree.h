#ifndef BRUTE_FORCE_KD_TREE_H
#define BRUTE_FORCE_KD_TREE_H

#include <stdlib.h>

#include "KD_tree.h"
#include "consts.h"
#include "utils.h"

int kd_move_cluster_centers(Point* points, Point* clusters, int* belongs_to);
void kd_calc_belongs_to(Point* points, Point* clusters, int* belongs_to);

#endif