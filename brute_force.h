// Brute-force method

#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include <stdlib.h>

#include "consts.h"
#include "utils.h"

int move_cluster_centers(Point* points, Point* clusters, int* belongs_to);
void calc_belongs_to(Point* points, Point* clusters, int* belongs_to);

#endif