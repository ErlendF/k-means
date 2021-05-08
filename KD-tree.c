
#include <KD-tree.h>
Point search_kd_tree(Node root, Point search_from) {
  if (root.isLeaf == 1) {
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
  int local_dim = (dim + 1) % dims;
  curr_dim = local_dim;
  // Sort each node with repsect to the current dimention.
  qsort(clusters, size, sizeof(Point), compare);

  // Recursivly build up the left side.
  Point* left_side = clusters;
  int left_size = size / 2;
  Node* left = malloc(sizeof(Node));
  left[0] = build_kd_tree(clusters, left_side, local_dim);
  root.left = left;

  // Recursivly build up the right side.
  Point* right_side = &clusters[size / 2];
  int right_side = ceil(size / 2.0);
  Node* right = malloc(sizeof(Node));
  right[0] = build_kd_tree(clusters, left_side, local_dim);
  root.right = right;

  root.value =
      right_side[0]
          .coords[local_dim];  // If dim values is >= to this we go right.
  return root;
}

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
