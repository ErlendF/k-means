#include "utils.h"

long double calc_dist(Point x, Point y) {
  int i;
  long double dist = 0;
  for (i = 0; i < dims; i++) {
    dist += sqrt(pow(x.coords[i] - y.coords[i], 2));  // Ignored sqrt as we are comparing relative distances
  }
  return dist;
}
