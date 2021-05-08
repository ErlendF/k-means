#include "output.h"

void print_points(Point* points) {
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

void print_belongs_to(Point* points, int* belongs_to) {
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

void print_cluster_centers(Point* clusters) {
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

void print_measures(Point* points, Point* clusters, int* belongs_to) {
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

void write_points_to_file(Point* points) {
  int i, j;
  FILE* fp;

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

void write_clusters_to_file(Point* clusters) {
  int i, j;
  FILE* fp;

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

void init_performance_file() {
  FILE* fp = fopen(performance_file, "w+");
  fprintf(fp, "mode,algorithm,time,num_points,num_clusters,dims,num_cells\n");
  fclose(fp);
}

void write_performance(int num_threads, char* mode, char* alg, double time) {
  FILE* fp = fopen(performance_file, "a");

  fprintf(fp, "%s,%s,%d,%f,%d,%d,%d,%d\n", mode, alg, num_threads, time, num_points, num_clusters, dims, num_cells);
  fclose(fp);
}