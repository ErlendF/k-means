#ifndef CONSTS_H
#define CONSTS_H

#define num_points 5000
#define num_clusters 10000
#define dims 3
#define max_num 4000000  // no more than 5000000
#define decimal 10
#define num_cells 3

#define points_file "points.csv"
#define clusters_file "clusters.csv"

typedef struct Point {
  long double coords[dims];
} Point;

#endif