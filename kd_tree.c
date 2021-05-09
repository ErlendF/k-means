// Builds and searches in KD-trees

#include "kd_tree.h"
int count = 0;  // Used to count how many calls to search_kd_tree there is.
/**
 * Information of the best is stored in the "best" value sent in.
 */
void search_kd_tree(Node root, Point search_from, ClusterDist* best) {
  count = 0;
  search_kd_tree_help(root, search_from, best);

  //printf("Checked: %d\n", count);
}

void search_kd_tree_help(Node root, Point search_from, ClusterDist* best) {
  count++;  // Lets see how many things we visit.

  if (root.isLeaf == 1) {
    long double curr_distance = calc_dist(search_from, root.cluster.point);
    if ((*best).distance > curr_distance) {
      (*best).distance = curr_distance;
      (*best).cluster = root.cluster;
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

  search_kd_tree_help(first, search_from, best);
  long double minDistanceToOther = abs(root.value - search_from.coords[root.dim]);
  if (minDistanceToOther < (*best).distance) {
    search_kd_tree_help(second, search_from, best);
  }
}

int curr_dim = 0;  // Used in qsort to decide what dim we are looking at.

Node* build_kd_tree(Point* clusterPoints) {
  Cluster clusters[num_clusters];
  int i, j;
  for (i = 0; i < num_clusters; i++) {
    clusters[i].ID = i;
    for (j = 0; j < dims; j++) {
      clusters[i].point.coords[j] = clusterPoints[i].coords[j];
    }
  }

  return build_kd_tree_helper(clusters, num_clusters, 0);
}

Node* build_kd_tree_helper(Cluster* clusters, int size, int dim) {
  Node* root = malloc(sizeof(Node));
  root->dim = dim;
  // If there is only one element in the list, this is a leaf.
  if (size == 1) {
    root->cluster = clusters[0];
    // printf("Creating cluster with point: ");
    // display_point(root.cluster.point);
    root->isLeaf = 1;
    return root;
  }

  root->isLeaf = 0;

  curr_dim = dim;
  // Sort each node with repsect to the current dimention.
  qsort(clusters, size, sizeof(Cluster), compare);

  // Cycle through every dimention when splitting.

  int local_dim = (dim + 1) % dims;

  // Calculate area for left side
  Cluster* left_side = clusters;
  int left_size = size / 2;
  // printf("Left side: ");
  // display_point(left_side[0].point);

  // Calculate area for left side
  Cluster* right_side = &(clusters[size / 2]);
  // printf("Right side: ");
  // display_point(right_side[0].point);
  int right_size = ceil(size / 2.0);

  root->value = right_side[0]
                    .point.coords[dim];  // If dim values is >= to this we go right.

  // TODO: Check time to see if we should make it parallel for both calls.
  // Recursivly build up the left side.
  // Recursivly build up the right side.

  root->right = build_kd_tree_helper(right_side, right_size, local_dim);
  root->left = build_kd_tree_helper(left_side, left_size, local_dim);

  return root;
}

void realse_kd_tree(Node* root) {
  if (root->isLeaf == 0) {
    realse_kd_tree(root->left);
    realse_kd_tree(root->right);
    free(root->left);
    free(root->right);
  }

}  // TODO: Make realse of KD Tree

int compare(const void* a, const void* b) {
  Cluster point_a = *((Cluster*)a);
  Cluster point_b = *((Cluster*)b);
  int compare_a = point_a.point.coords[curr_dim];
  int compare_b = point_b.point.coords[curr_dim];

  if (compare_a == compare_b)
    return 0;
  else if (compare_a < compare_b)
    return -1;
  else
    return 1;
}

void display_point(Point point) {
  int i;
  printf("(%.2Lf", point.coords[0]);
  for (i = 1; i < dims; i++) {
    printf(", %.2Lf", point.coords[i]);
  }
  printf(")\n");
}

void display_kd_tree(Node root) { display_kd_tree_helper(root, 0); }

void display_kd_tree_helper(Node current, int depth) {
  int i;
  char a[depth * 4];
  for (i = 0; i < depth * 5; i++) {
    a[i] = ' ';
  }

  if (current.isLeaf == 1) {
    printf("%sLv:%d Dim: %d ", a, depth, current.dim);
    display_point(current.cluster.point);

  } else {
    printf("%sLv:%d Dim: %d value: %.2Lf\n", a, depth, current.dim,
           current.value);
    display_kd_tree_helper(*(current.left), depth + 1);
    display_kd_tree_helper(*(current.right), depth + 1);
  }
}