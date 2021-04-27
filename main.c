#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define num_points 100
#define num_clusters 3
#define dims 2
#define max_num 50000  // no more than 5000000
#define decimal 100
#define num_cells 4

#define points_file "points.csv"
#define clusters_file "clusters.csv"

typedef struct Point {
  long double coords[dims];
} Point;

// int *cell_clust;  // The cluster closest to the cell
int *cell_valid;  // 1 if there is only one cluster closest to the cell, 0 otherwise
int *grid_points_closest;
int tot_num_cells;
int num_cell_points;

Point *grid_points;

Point points[num_points];
Point clusters[num_clusters];

int belongs_to[num_points];

void generate_uniform_list_of_points();
void generate_clustered_list_of_points();
void print_points();
long double calc_dist(Point x, Point y);
void calc_belongs_to();
void print_belongs_to();
int move_cluster_centers();
void init_uniform_cluster_centers();
void print_cluster_centers();
void print_measures();
void write_points_to_file();
void write_clusters_to_file();
void init_grid();

int main(int argc, char *argv[]) {
  // srand(time(NULL));    // set rand seed

  // printf("Test\n");
  // init_grid();
  // int i;
  // for (i = 0; i < num_cell_points; i++) {
  //   printf("%d: (%Lf, %Lf, %Lf)\n", i, grid_points[i].coords[0], grid_points[i].coords[1], grid_points[i].coords[2]);
  // }

  generate_clustered_list_of_points();
  init_uniform_cluster_centers();
  do {
    calc_belongs_to();
  } while (move_cluster_centers() != 0);

  // print_belongs_to();
  print_cluster_centers();
  print_measures();
  write_points_to_file();
  write_clusters_to_file();
}

void generate_uniform_list_of_points() {
  int i, j;  // iteration variables

  for (i = 0; i < num_points; i++) {
    for (j = 0; j < dims; j++) {
      points[i].coords[j] = (long double)(rand() % max_num) /
                            decimal;  // generating points with two decimals
    }
  }
  return;
}

// TODO: fix :)
void generate_clustered_list_of_points() {
  int i, j, k;

  long double cluster_offsets[dims];
  for (i = 0; i < dims; i++) {
    cluster_offsets[i] = 0;
  }

  int cluster_size = 0;
  int cluster_count = 0;

  for (i = 0, j = 0; i < num_points; i++, cluster_size--) {
    if (cluster_size <= 0) {
      cluster_count++;
      cluster_size = fmax(((rand() % num_points) / 10) + num_points / 100, 5);
      printf("New cluster size: %d\n", cluster_size);
      for (k = 0; k < dims; k++) {
        cluster_offsets[k] =
            (long double)(rand() % max_num) / decimal;
      }
    }

    for (k = 0; k < dims; k++) {
      points[i].coords[k] =
          (((long double)(rand() % (num_points * decimal)) / decimal) + (long double)cluster_offsets[k]);
    }
  }

  printf("Num clusters: %d\n", cluster_count);
}

void print_points() {
  int i, j;
  for (i = 0; i < num_points; i++) {
    for (j = 0; j < dims; j++) {
      if (j == 0) {
        printf("(%.2Lf, ", points[i].coords[j]);
      } else if (j == dims - 1) {
        printf("%.2Lf)\n", points[i].coords[j]);
      } else {
        printf("%.2Lf, ", points[i].coords[j]);
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

void init_uniform_cluster_centers() {
  int i, j;
  for (i = 0; i < num_clusters; i++) {
    int pt = rand() % num_points;
    for (j = 0; j < dims; j++) {
      clusters[i].coords[j] = (long double)(rand() % max_num) / decimal;
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
    max[i] = FLT_MIN;
    min[i] = FLT_MAX;
    count[i] = 0;
    sum[i] = 0;
  }
  long double tmp;
  for (i = 0; i < num_points; i++) {
    cls = belongs_to[i];
    tmp = calc_dist(points[i], clusters[cls]);
    ct++;
    sum[cls] += tmp;
    count[cls]++;
    if (tmp < min[cls]) min[cls] = tmp;
    if (tmp > max[cls]) max[cls] = tmp;
  }

  for (i = 0; i < num_clusters; i++) {
    if (count[i] == 0) {
      printf("\nCluster %d did not find any points </3\n", i + 1);
      continue;
    }
    printf("\nAverage distance from cluster %d = %.3Lf\n", i + 1, sum[i] / count[i]);
    printf("Variation  = %.3Lf, min = %.3Lf, max = %.3Lf, count = %d, sum = %Lf\n", max[i] - min[i], min[i], max[i], count[i], sum[i]);
  }

  printf("\n Actual number of points = %d, Defined number of points = %d\n", ct,
         num_points);
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

// https://stackoverflow.com/questions/29787310/does-pow-work-for-int-data-type-in-c
void init_grid() {
  tot_num_cells = (int)(pow(num_cells, dims) + 0.5);  // TODO: test :)
  num_cell_points = (int)(pow(num_cells + 1, dims) + 0.5);
  printf("Num cell points: %d\nTot num cells: %d\n", num_cell_points, tot_num_cells);

  cell_valid = (int *)malloc(sizeof(int) * tot_num_cells);
  grid_points_closest = (int *)malloc(sizeof(int) * num_cell_points);  // Holds clost cluster nr.
  grid_points = (Point *)malloc(sizeof(Point) * num_cell_points);

  int i, j;

  // TODO: handle edge cases :)
  for (i = 0; i < num_cell_points; i++) {
    for (j = 0; j < dims; j++) {
      grid_points[i].coords[j] = (i % (int)(pow(num_cells + 1, j + 1) + 0.5)) / (int)(pow(num_cells + 1, j) + 0.5);  // TODO: gang med cell width
    }
  }
}

// TODO: Point -> index

// TODO: Index -> Point

void calculate_grid_closest_cluster() {
  int i, j;
  for (i = 0; i < num_cell_points; i++) {
  }
}
