#ifndef CONSTS_H
#define CONSTS_H

#define num_points 5000
#define num_clusters 30
#define dims 3
#define max_num 25000  // The maximum size of the points (with clustered points, the max will be 1.01 times max_num)
#define decimal 100    // Makes points with decimals equal to the number of zeros in decimal
#define num_cells 10   // Number of cells in the grid (in each dimension)

typedef struct Point {
  long double coords[dims];
} Point;

#endif