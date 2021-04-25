#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define num_points 100
#define num_clusters 4
#define dims 2

typedef struct Point {
  long double coords[dims];
} Point;

// typedef struct Grid_cell {
//   int *coords;
// } Grid_cell;

Point points[num_points];
Point clusters[num_clusters];

int belongs_to[num_points];

void generate_list_of_points();
void print_points();
long double calc_dist(Point x, Point y);
void calc_belongs_to();
void print_belongs_to();
int move_cluster_centers();
void init_cluster_centers();
void print_cluster_centers();

int main(int argc, char *argv[]) {
  generate_list_of_points();
  print_points();
  init_cluster_centers();
  do {
    printf("New round!!\n\n");
    print_cluster_centers();
    calc_belongs_to();
    print_belongs_to();
  } while (move_cluster_centers() != 0);

  printf("Finished!\n");
  print_cluster_centers();
}

void generate_list_of_points() {
  int count = 0;  // coordinate array and its pointer
  int i, j;       // iteration variables

  for (i = 0; i < num_points; i++) {
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
        printf("(%Lf, ", points[i].coords[j]);
      } else if (j == dims - 1) {
        printf("%Lf)\n", points[i].coords[j]);
      } else {
        printf("%Lf, ", points[i].coords[j]);
      }
    }
  }
}

long double calc_dist(Point x, Point y) {
  int i;
  long double dist = 0;
  for (i = 0; i < dims; i++) {
    dist += pow(x.coords[i] - y.coords[i], 2);  // Ignored sqrt as we are comparing relative distances
  }
  // printf("points = (%Lf, %Lf),(%Lf, %Lf) (distance = %Lf)\n", x.coords[0], x.coords[1], y.coords[0], y.coords[1], dist);

  return dist;
}

int move_cluster_centers() {
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
    for (j = 0; j < dims; j++) {
      new_coord = sum_dims[i][j] / (long double)counts[i];

      if (clusters[i].coords[j] != new_coord) {
        moved = 1;
      }

      clusters[i].coords[j] = new_coord;
    }
  }

  return moved;
}

void calc_belongs_to() {
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

void init_cluster_centers() {
  int i, j;
  for (i = 0; i < num_clusters; i++) {
    int pt = rand() % num_points;
    for (j = 0; j < dims; j++) {
      clusters[i].coords[j] = points[pt].coords[j];
    }
  }
}

void print_belongs_to() {
  int i, j;
  for (i = 0; i < num_points; i++) {
    printf("Point %d (", i);
    for (j = 0; j < dims; j++) {
      if (j == dims - 1)
        printf("%.2Lf) ", points[i].coords[j]);
      else
        printf("%.2Lf, ", points[i].coords[j]);
    }
    printf("belongs to cluster %d\n", belongs_to[i]);
  }
}

void print_cluster_centers() {
  int i, j;
  for (i = 0; i < num_clusters; i++) {
    printf("Cluster %d: (", i);
    for (j = 0; j < dims; j++) {
      if (j == dims - 1)
        printf("%.2Lf)\n", clusters[i].coords[j]);
      else
        printf("%.2Lf, ", clusters[i].coords[j]);
    }
  }
}