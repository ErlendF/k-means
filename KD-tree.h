
#ifndef KD_TREE_H
#define KD_TREE_H
#include <math.h>
#include <stdlib.h>

#include "consts.h"
#include "utils.h"

typedef struct Node {
  struct Node* left;
  struct Node* right;
  int value;
  int dim;
  int isLeaf;
  Point point;
} Node;

#endif
