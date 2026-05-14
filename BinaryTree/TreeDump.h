#ifndef TREE_DUMP
#define TREE_DUMP

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#include <stdio.h>
#include "Tree.h"

int     TreeDump      (Node_t *node, const char* DumpFile);
void    PrintNodes    (FILE* Graf, Node_t *node, size_t temp);

const char* const edgeclr    = "#1e2460";
const char* const N_edgeclr  = "#cd0000"; ///< color of left edge that means NO
const char* const Y_edgeclr  = "#03c03c"; ///< color of right edge that means YES
const char* const defaultslt = "filled"; 
const char* const clusterclr = "#ff9696";
const char* const nodeclr    = "#050505";
const char* const fontclr    = "#000000";
const char* const Q_fillclr  = "#cc4646"; ///< color of nodes with questions
const char* const A_fillclr  = "#8e1f1f"; ///< color of nodes with answers

const size_t MAX_STR_ = 100;

#endif /* TREE_DUMP */