#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>

enum direction {
    LEFT = 0,
    RIGHT = 1,
};

typedef char* Data_t;

struct Node_t {
    char* question;
    struct Node_t* left;
    struct Node_t* right;
};

Node_t*    newNode                    (Data_t data);
void       deleteTree                 (Node_t* root);
void       fprintfTree                (FILE* fp, Node_t* root, size_t depth);
void       fscanfTree                 (FILE* fp, Node_t** root);
int*       getPath                    (char* brackets, size_t* depth);

Node_t*    insertNode                 (Node_t* root, int data);
Node_t*    findMin                    (Node_t* root);
Node_t*    findNode                   (Node_t* root, int value);
Node_t*    deleteNodeWithoutSubtree   (Node_t* root, int data);
void       deleteNodeWithSubtree      (Node_t* root, int value);
int        treeDepth                  (Node_t* root);
void       inorderTraversal           (Node_t* root);
void       postorderTraversal         (Node_t* root);

#define DELETE_TREE(tree) deleteTree(tree); tree = NULL;
#define INSERT_NODE()

const size_t MAX_DEPTH = 40;
const size_t MAX_STR = 100;

#endif /* TREE_H */