// Generating points and initial cluster centers locations

#ifndef INIT_H
#define INIT_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "consts.h"

void generate_uniform_list_of_points(Point *points);
void generate_clustered_list_of_points(Point *points);
void init_uniform_cluster_centers(Point *clusters);

#endif