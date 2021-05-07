#ifndef OUTPUT_H
#define OUTPUT_H

#include <float.h>
#include <stdio.h>

#include "consts.h"
#include "utils.h"

void print_points(Point* points);
void print_belongs_to(Point* points, int* belongs_to);
void print_cluster_centers(Point* clusters);
void print_measures(Point* points, Point* clusters, int* belongs_to);
void write_points_to_file(Point* points);
void write_clusters_to_file(Point* clusters);

#endif