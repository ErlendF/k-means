#ifndef BRUTE_FORCE_KD_TREE_H
#define BRUTE_FORCE_KD_TREE_H

#include <stdlib.h>

#include "KD_tree.h"
#include "consts.h"
#include "utils.h"


int move_cluster_centers(Point* points, Point* clusters, int* belongs_to);
void calc_belongs_to(Point* points, Point* clusters, int* belongs_to);

#endif