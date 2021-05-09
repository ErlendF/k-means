// Various definitions of constants

#ifndef CONSTS_H
#define CONSTS_H

#define num_points 200000  // Number of points used
#define num_clusters 300   // Number of cluster centers used
#define dims 3             // Number of dimensions used (grid methods only supports up to 3)
#define max_num 2500000    // The maximum size of the points (with clustered points, the max will be 1.01 times max_num)
#define decimal 100        // Makes points with decimals equal to the number of zeros in decimal
#define num_cells 20       // Number of cells in the grid (in each dimension)

typedef struct Point {
  long double coords[dims];  // Coordinate in each dimension
} Point;

#endif