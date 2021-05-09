// Brute force method using KD

#ifndef KD_TREE_H
#define KD_TREE_H
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"
#include "init.h"
#include "output.h"
#include "utils.h"

typedef struct Cluster {
  Point point;
  int ID;
} Cluster;

typedef struct Node {
  struct Node* left;
  struct Node* right;
  long double value;
  int dim;
  int isLeaf;
  Cluster cluster;
} Node;

typedef struct ClusterDist {
  struct Cluster cluster;
  double distance;
} ClusterDist;

void search_kd_tree(Node current, Point search_from, ClusterDist* best);
void search_kd_tree_help(Node root, Point search_from, ClusterDist* best);
Node* build_kd_tree_helper(Cluster* clusters, int size, int dim);
Node* build_kd_tree(Point* cluster);
int compare(const void* a, const void* b);
void realse_kd_tree();
void display_kd_tree(Node root);
void display_kd_tree_helper(Node current, int depth);
void display_point(Point point);

#endif
