
#ifndef KD_TREE_H
#define KD_TREE_H
#include <math.h>
#include <stdlib.h>

#include "consts.h"
#include "init.h"
#include "output.h"
#include "utils.h"

typedef struct Node {
  struct Node* left;
  struct Node* right;
  long double value;
  int dim;
  int isLeaf;
  Point point;
} Node;

typedef struct PointDist {
  struct Point point;
  long double distance;
} PointDist;

void search_kd_tree(Node current, Point search_from, PointDist* best);
Node build_kd_tree(Point* clusters, int size, int dim);
int compare(const void* a, const void* b);
void realse_kd_tree();
void print_kd_tree(Node root);
void print_kd_tree_helper(Node current, int depth);
void display_point(Point point);

#endif
