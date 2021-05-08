
#include "KD_tree.h"
int count = 0;  // Used to count how many calls to search_kd_tree there is.
/**
 * Information of the best is stored in the "best" value sent in.
 */
void search_kd_tree(Node current, Point search_from, PointDist* best) {
  count++;  // Lets see how many things we visit.

  Node root = current;
  if (root.isLeaf == 1) {
    long double curr_distance = calc_dist(search_from, root.point);
    if (best->distance > curr_distance) {
      best->distance = curr_distance;
      best->point = root.point;
    }
    return;
  }

  int dim = root.dim;
  Node first;
  Node second;

  if (search_from.coords[dim] >= root.value) {
    first = root.right[0];  // If isLeaf = 0; both right, and left should have
                            // values.
    second = root.left[0];  // TODO: Add check not null. (should not be needed)?
  } else {
    first = root.left[0];
    second = root.right[0];
  }

  search_kd_tree(first, search_from, best);

  long double minDistanceToOther = abs(second.value - search_from.coords[dim]);
  if (minDistanceToOther < best->distance) {
    search_kd_tree(second, search_from, best);
  }
}

int curr_dim = 0;
Node build_kd_tree(Point* clusters, int size, int dim) {
  Node root;
  root.dim = dim;
  // If there is only one element in the list, this i a leaf.
  if (size == 1) {
    root.point = clusters[0];
    root.isLeaf = 1;
    return root;
  }

  root.isLeaf = 0;

  // Cycle through every dimention when splitting.

  curr_dim = dim;
  // Sort each node with repsect to the current dimention.
  qsort(clusters, size, sizeof(Point), compare);

  int local_dim = (dim + 1) % dims;

  // Calculate area for left side
  Point* left_side = clusters;
  int left_size = size / 2;
  Node* left = malloc(sizeof(Node));

  // Calculate area for left side
  Point* right_side = &(clusters[size / 2]);
  int right_size = ceil(size / 2.0);
  Node* right = malloc(sizeof(Node));

  root.value =
      right_side[0].coords[dim];  // If dim values is >= to this we go right.

  // TODO: Check time to see if we should make it parallel for both calls.
  // Recursivly build up the left side.
  left[0] = build_kd_tree(left_side, left_size, local_dim);
  root.left = left;

  // Recursivly build up the right side.
  right[0] = build_kd_tree(right_side, right_size, local_dim);
  root.right = right;

  return root;
}

void realse_kd_tree(Node root) {
  if (root.isLeaf == 0) {
    realse_kd_tree(*root.left);
    realse_kd_tree(*root.right);
  }
  free(root.left);
  free(root.right);
}  // TODO: Make realse of KD Tree

int compare(const void* a, const void* b) {
  Point point_a = *((Point*)a);
  Point point_b = *((Point*)b);
  int compare_a = point_a.coords[curr_dim];
  int compare_b = point_b.coords[curr_dim];

  if (compare_a == compare_b)
    return 0;
  else if (compare_a < compare_b)
    return -1;
  else
    return 1;
}

int main() {
  Point clusters[num_clusters];
  init_uniform_cluster_centers(clusters);
  print_cluster_centers(clusters);
  Node root = build_kd_tree(clusters, num_clusters, 0);
  print_kd_tree(root);

  Point target;
  int i, j;
  for (i = 0; i < dims; i++) {
    target.coords[i] = 400;
  }

  PointDist* best;
  best = malloc(sizeof(PointDist));
  best->distance = RAND_MAX;
  count = 0;
  search_kd_tree(root, target, best);
  printf("Best point: ");
  Point best_point = best->point;
  display_point(best_point);
  printf("Distance: %.2Lf\n", best->distance);
  printf("Using: %d look ups\n", count);

  Point best_cluster;
  long double min = RAND_MAX;
  for (i = 0; i < num_clusters; i++) {
    long double total = calc_dist(target, clusters[i]);
    if (total < min) {
      best_cluster = clusters[i];
      min = total;
    }
  }

  printf("Found to be best: ");
  display_point(best_cluster);
  printf("Found best distance: %2.Lf\n", min);
}

void display_point(Point point) {
  int i;
  printf("(%.2Lf", point.coords[0]);
  for (i = 1; i < dims; i++) {
    printf(", %.2Lf", point.coords[i]);
  }
  printf(")\n");
}

void print_kd_tree(Node root) { print_kd_tree_helper(root, 0); }

void print_kd_tree_helper(Node current, int depth) {
  int i;
  char a[depth * 5];
  for (i = 0; i < depth * 5; i++) {
    a[i] = ' ';
  }

  if (current.isLeaf == 1) {
    printf("%sLv:%d Dim: %d Point:(", a, depth, current.dim);
    printf("%.2Lf", current.point.coords[0]);
    for (i = 1; i < dims; i++) {
      printf(", %.2Lf", current.point.coords[i]);
    }
    printf(")\n");

  } else {
    printf("%sLv:%d Dim: %d value: %.2Lf\n", a, depth, current.dim,
           current.value);
    print_kd_tree_helper(current.left[0], depth + 1);
    print_kd_tree_helper(current.right[0], depth + 1);
  }
}