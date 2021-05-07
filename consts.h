#ifndef CONSTS_H
#define CONSTS_H

#define num_points 500000
#define num_clusters 150
#define dims 15
#define max_num 50000  // no more than 5000000
#define decimal 100
#define num_cells 3

#define points_file "points.csv"
#define clusters_file "clusters.csv"

typedef struct Point {
  long double coords[dims];
} Point;

#endif