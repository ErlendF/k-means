// Sequential grid method using KD trees

#include "seq_grid_kd_tree.h"
void skd_grid_calc(Point *points, Point grid[], Point *clusters, int *belongs_to, int num_cell_corners, int num_grid_cells, int num_corners, int *grid_points_closest, int grid_corners[][(int)(pow(2, dims) + 0.5)], int *cell_closest_cluster, int belongs_to_cell[]) {
  do {
    Node *root = build_kd_tree(clusters);
    {
      int i, j, k, prev_value, cluster;
      long double dist, tmpdist;
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
      for (i = 0; i < num_points; i++) {
        if (cell_closest_cluster[belongs_to_cell[i]] != -1) {
          belongs_to[i] = cell_closest_cluster[belongs_to_cell[i]];
          continue;
        }

        best.distance = RAND_MAX;
        search_kd_tree(*root, points[i], &best);

        belongs_to[i] = best.cluster.ID;
      }
    }
    release_kd_tree(root);

  } while (move_cluster_centers(points, clusters, belongs_to) != 0);
}