#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <stdlib.h>

#include "consts.h"

long double calc_dist(Point x, Point y);
void calc_belongs_to(Point* points, Point* clusters, int* belongs_to);
#endif