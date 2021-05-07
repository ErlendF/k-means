#include <float.h>
#include <math.h>

#define grid_size 0.1
#define nr_clusters 5
typedef struct Point {
  long double coords[2];
} Point;

typedef struct GridPos {
  int possibleCluster[nr_clusters]
} GridPos;

#define parts_grid_x 10
#define parts_grid_y 10
GridPos allGrids[parts_grid_x * parts_grid_y];

void initialize_grid_structs() {
  // To start off we set all grids to not reach any cluster
  int i, j;
  for (i = 0; i < parts_grid_y * parts_grid_x; i++) {
    for (j = 0; j < nr_clusters; j++) {
      allGrids[i].possibleCluster[j] = 0;
    }
  }
}

Point closest_cluster(int num_clusters, Point *clusters, float x1, float y1,
                      float x2, float y2) {
  /*
      Search to find the closest cluster.
  */
  int i;
  Point closest;
  long double dist = FLT_MIN;
  for (i = 0; i < num_clusters; i++) {
    int current_cluster_x = clusters[i].coords[0];
    int current_cluster_y = clusters[i].coords[1];
    long double current_dist = distance_from_line_to_point(
        current_cluster_x, current_cluster_y, x1, y1, x2, y2);
    if (current_dist > dist) {
      dist = current_dist;
      closest = clusters[i];
    }
  }
  return closest;
}

void update_grid(int num_clusters, Point *clusters, GridPos current,
                 double grid_x, double grid_y, double grid_dx, double grid_dy) {
  // Top_left - Top_right
  int lx = grid_x;
  int ly = grid_y;
  int rx = grid_x + grid_dx;
  int ry = grid_y + grid_dy;
  Point closest = closest_cluster(num_clusters, clusters, lx, ly, rx, ry);

  // Top_left - bottom_left

  // Bottom_left - bottom_right

  // Bottom_right - top_right
}
/*
long double distance_from_line_to_point(float px1, float py1, float lx1,
                                        float ly1, float lx2, float ly2) {
  // Joikned from stackOverflow.
  // https://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment?page=1&tab=votes#tab-top
  long double px = lx1 - px1;
  long double py = ly1 - py1;
  long double temp = (px * px) + (py * py);
  long double u = ((lx2 - px1) * px + (ly2 - py1) * py) / (temp);
  if (u > 1) {
    u = 1;
  } else if (u < 0) {
    u = 0;
  }
  long double x = px1 + u * px;
  long double y = py1 + u * py;

  long double dx = x - lx2;
  long double dy = y - ly2;
  long double dist = sqrt(dx * dx + dy * dy);
  return dist;
}*/

int grid_calc_belongs_to(int nodes_num, int cluster_num, int max_width,
                         Point *nodes, Point *clusters) {
  initialize_grid_structs();
}