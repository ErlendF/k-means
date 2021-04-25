#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: calculate avg distance/variance something for each cluster
// TODO: print all points and cluster centers to csv
// TODO: better generation of points and cluster centers

#define num_points 10000
#define num_clusters 10
#define dims 5

#define points_file "points.csv"
#define clusters_file "clusters.csv"

typedef struct Point {
  long double coords[dims];
} Point;

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
void print_measures();
void write_points_to_file();
void write_clusters_to_file();

int main(int argc, char *argv[]) {
  generate_list_of_points();
  // print_points();
  init_cluster_centers();
  do {
    calc_belongs_to();
  } while (move_cluster_centers() != 0);

  print_belongs_to();
  print_cluster_centers();
  print_measures();
  write_points_to_file();
  write_clusters_to_file();
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
    if (counts[i] == 0) {
      continue;
    }

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
    printf("Point %d (", i + 1);
    for (j = 0; j < dims; j++) {
      if (j == dims - 1)
        printf("%.2Lf) ", points[i].coords[j]);
      else
        printf("%.2Lf, ", points[i].coords[j]);
    }
    printf("belongs to cluster %d\n", belongs_to[i] + 1);
  }
}

void print_cluster_centers() {
  int i, j;
  for (i = 0; i < num_clusters; i++) {
    printf("Cluster %d: (", i + 1);
    for (j = 0; j < dims; j++) {
      if (j == dims - 1)
        printf("%.2Lf)\n", clusters[i].coords[j]);
      else
        printf("%.2Lf, ", clusters[i].coords[j]);
    }
  }
}

void print_measures() {
  int i, j, cls;
  int ct = 0;
  long double sum[num_clusters], min[num_clusters], max[num_clusters];
  int count[num_clusters];
  for (i = 0; i < num_clusters; i++) {
    max[i] = -1;
    min[i] = (long double)RAND_MAX;
    count[i] = 0;
  }
  long double tmp;
  for (i = 0; i < num_points; i++) {
    cls = belongs_to[i];
    tmp = calc_dist(points[i], clusters[cls]);
    ct++;

    sum[cls] += tmp;
    count[cls]++;
    if (tmp < min[cls])
      min[cls] = tmp;
    else if (tmp > max[cls])
      max[cls] = tmp;
  }

  for (i = 0; i < num_clusters; i++)
    printf("\nAverage distance from cluster %d = %.3Lf\nVariation  = %.3Lf, min = %.3Lf, max = %.3Lf, count = %d\n", i + 1, sum[i] / count[i], max[i] - min[i], min[i], max[i], count[i]);

  printf("\n Actual number of points = %d, Defined number of points = %d\n", ct, num_points);
}

void write_points_to_file() {
  int i, j;
  FILE *fp;

  fp = fopen(points_file, "w+");
  for (i = 0; i < num_points; i++) {
    for (j = 0; j < dims; j++) {
      if (j == dims - 1) {
        fprintf(fp, "%Lf\n", points[i].coords[j]);
      } else {
        fprintf(fp, "%Lf, ", points[i].coords[j]);
      }
    }
  }
}

void write_clusters_to_file() {
  int i, j;
  FILE *fp;

  fp = fopen(clusters_file, "w+");
  for (i = 0; i < num_clusters; i++) {
    for (j = 0; j < dims; j++) {
      if (j == dims - 1) {
        fprintf(fp, "%Lf\n", clusters[i].coords[j]);
      } else {
        fprintf(fp, "%Lf, ", clusters[i].coords[j]);
      }
    }
  }
}