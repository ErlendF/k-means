// Brute-force method

#include "brute_force.h"

#include <stdio.h>

// Moving cluster centers sequentially.
// This returns 1 if atleast one cluster was moved,
// which means that the main loop needs to do another iteration.
// It returns 0 if no cluster was moved, meaning the main loop is finished.
int move_cluster_centers(Point* points, Point* clusters, int* belongs_to) {
  int i, j, cluster;
  int moved = 0;
  int counts[num_clusters];
  long double sum_dims[num_clusters][dims];
  long double new_coord;

  // Initializing
  for (i = 0; i < num_clusters; i++) {
    counts[i] = 0;
    for (j = 0; j < dims; j++) {
      sum_dims[i][j] = 0;
    }
  }
  // Calculating sums
  for (i = 0; i < num_points; i++) {
    cluster = belongs_to[i];
    counts[cluster]++;
    for (j = 0; j < dims; j++) {
      sum_dims[cluster][j] += points[i].coords[j];
    }
  }

  for (i = 0; i < num_clusters; i++) {
    if (counts[i] == 0) {  // There were no points belonging to the cluster
      continue;
    }

    for (j = 0; j < dims; j++) {
      new_coord = sum_dims[i][j] / (long double)counts[i];

      if (clusters[i].coords[j] != new_coord) {  // Checking if the cluster was moved
        moved = 1;
      }

      clusters[i].coords[j] = new_coord;
    }
  }

  return moved;
}

// Calculates which cluster center each point belongs to
void calc_belongs_to(Point* points, Point* clusters, int* belongs_to) {
  int i, j;
  long double dist, tmpdist;
  int cluster;

  for (i = 0; i < num_points; i++) {
    dist = RAND_MAX;
    cluster = -1;

    for (j = 0; j < num_clusters; j++) {
      tmpdist = calc_dist(points[i], clusters[j]);
      if (tmpdist < dist) {
        dist = tmpdist;
        cluster = j;
      }
    }

    belongs_to[i] = cluster;
  }
}
