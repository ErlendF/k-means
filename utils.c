#include "utils.h"

// TODO: Remove sqrt, not needed (most likely)
long double calc_dist(Point x, Point y) {
  int i;
  long double dist = 0;
  for (i = 0; i < dims; i++) {
    dist += (pow(x.coords[i] - y.coords[i],
                 2));  // Ignored sqrt as we are comparing relative distances
  }
  return sqrt(dist);
}

long double calc_dist_no_sqrt(Point x, Point y) {
  int i;
  long double dist = 0;
  for (i = 0; i < dims; i++) {
    dist += pow(x.coords[i] - y.coords[i],
                2);  // Ignored sqrt as we are comparing relative distances
  }
  return dist;
}