#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define num_points 100

typedef struct Point {
  int *coords;
} Point;

// typedef struct Grid_cell {
//   int *coords;
// } Grid_cell;

// const grid_size = 3;
const int dims = 2;
const int num_clusters = 4;
Point points[num_points];  // must be equal to num_points

void generate_list_of_points();
void print_points();
int calc_dist(Point x, Point y);

int main(int argc, char *argv[]) {
  generate_list_of_points();
  print_points();
}

void generate_list_of_points() {
  int count = 0;  // coordinate array and its pointer
  int i, j;       // iteration variables

  for (i = 0; i < num_points; i++) {
    points[i].coords = (int *)malloc(sizeof(int) * dims);
    if (i % (num_points / num_clusters) == 0 &&
        i > 0) {  // adds 20 to both future x and y coordinates to force clear
                  // clusters
      count += 20;
    }

    for (j = 0; j < dims; j++) {
      points[i].coords[j] =
          count +
          rand() % 10;  // giving values to the coordinate [coordinate][0=x,1=y]
    }
  }
  return;
}

void print_points() {
  int i, j;
  for (i = 0; i < num_points; i++) {
    for (j = 0; j < dims; j++) {
      if (j == 0) {
        printf("(%d, ", points[i].coords[j]);
      } else if (j == dims - 1) {
        printf("%d)\n", points[i].coords[j]);
      } else {
        printf("%d, ", points[i].coords[j]);
      }
    }
  }
}

int calc_dist(Point x, Point y) {
  int i;
  int dist = 0;
  for (i = 0; i < dims; i++) {
    dist += pow(x.coords[i] - y.coords[i], 2);  // Ignored sqrt as we are looking at relative distance
  }

  return dist;
}
