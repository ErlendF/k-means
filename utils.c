#include "utils.h"

// Calculating the Euclidian distance between the two points
long double calc_dist(Point x, Point y) {
  int i;
  long double dist = 0;
  for (i = 0; i < dims; i++) {
    dist += pow(x.coords[i] - y.coords[i], 2);
  }
  return sqrt(dist);
}

// Calculating the squared Euclidean distance between the two points
long double calc_dist_no_sqrt(Point x, Point y) {
  int i;
  long double dist = 0;
  for (i = 0; i < dims; i++) {
    dist += pow(x.coords[i] - y.coords[i], 2);
  }
  return dist;  // Ignored sqrt as we are comparing relative distances
}