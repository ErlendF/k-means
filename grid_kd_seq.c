// Sequential grid method using KD trees

#include "grid_kd_seq.h"

// Calculates which cluster is closest to each gridcell. If there are multiple, it's set to -1
void kd_grid_closest_cluster(Point grid[], Point *clusters, int num_cell_corners, int num_grid_cells, int num_corners, int *grid_points_closest, int grid_corners[][(int)(pow(2, dims) + 0.5)], int *cell_closest_cluster) {
  int i, j, k, prev_value, cluster;
  long double dist, tmpdist;
  Node *root = build_kd_tree(clusters);
  ClusterDist best;
  for (i = 0; i < num_cell_corners; i++) {
    best.distance = RAND_MAX;
    search_kd_tree(*root, grid[i], &best);
    grid_points_closest[i] = best.cluster.ID;
  }

  for (i = 0; i < num_grid_cells; i++) {
    for (j = 0; j < num_corners; j++) {
      if (j == 0) {
        prev_value = grid_points_closest[grid_corners[i][j]];
      } else {
        if (grid_points_closest[grid_corners[i][j]] != prev_value) {
          prev_value = -1;
          break;
        }
      }
    }
    cell_closest_cluster[i] = prev_value;
  }
}

// Calculates which cluster each point belongs to
void kd_grid_calc_belongs_to(Point *points, Point *clusters, int *belongs_to, int *cell_closest_cluster, int belongs_to_cell[]) {
  int i, j;
  long double dist, tmpdist;
  int cluster;
  Node *root = build_kd_tree(clusters);
  ClusterDist best;
  for (i = 0; i < num_points; i++) {
    if (cell_closest_cluster[belongs_to_cell[i]] != -1) {
      belongs_to[i] = cell_closest_cluster[belongs_to_cell[i]];
      continue;
    }

    // dist = RAND_MAX;
    // cluster = -1;
    // for (j = 0; j < num_clusters; j++) {
    //   tmpdist = calc_dist(points[i], clusters[j]);
    //   if (tmpdist < dist) {
    //     dist = tmpdist;
    //     cluster = j;
    //   }
    // }
    best.distance = RAND_MAX;
    search_kd_tree(*root, points[i], &best);
    belongs_to[i] = cluster;
  }
}