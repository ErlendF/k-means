#ifndef OUTPUT_H
#define OUTPUT_H

#include <float.h>
#include <stdio.h>
#include <stdlib.h>

#include "consts.h"
#include "utils.h"

#define points_file "points.csv"
#define clusters_file "clusters.csv"
#define performance_file "performance.csv"

void print_points(Point* points);
void print_belongs_to(Point* points, int* belongs_to);
void print_cluster_centers(Point* clusters);
void print_measures(Point* points, Point* clusters, int* belongs_to);
void write_points_to_file(Point* points);
void write_clusters_to_file(Point* clusters);
void write_performance(int num_threads, char* mode, char* alg, double time);
void init_performance_file();
#endif