// Various utility functions used throughout the program

#ifndef UTILS_H
#define UTILS_H

#include <math.h>

#include "consts.h"

long double calc_dist(Point x, Point y);
void copy_clusters(Point clusters_copy[num_clusters], Point clusters[num_clusters]);

#endif