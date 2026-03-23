#ifndef TREE_DUMP
#define TREE_DUMP

#include <stdio.h>
#include "Tree.h"

int     TreeDump      (Node_t *node, const char* DumpFile, const char* GrafFile);
void    PrintNodes    (FILE* Graf, Node_t *node, size_t temp);

const char* const edgeclr    = "#1e2460";
const char* const N_edgeclr  = "#b32851"; ///< color of left edge that means NO
const char* const Y_edgeclr  = "#03c03c"; ///< color of right edge that means YES
const char* const defaultslt = "filled"; 
const char* const clusterclr = "#78dbe2";
const char* const nodeclr    = "#050505";
const char* const fontclr    = "#0a2033";
const char* const Q_fillclr  = "#9f8170"; ///< color of nodes with questions
const char* const A_fillclr  = "#755d9a"; ///< color of nodes with answers

const size_t MAX_STR_ = 100;

#endif /* TREE_DUMP */