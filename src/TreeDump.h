#ifndef TREE_DUMP
#define TREE_DUMP

#include <stdio.h>
#include "Tree.h"

int     TreeDump      (Node_t *node, const char* DumpFile, const char* GrafFile);
void    PrintNodes    (FILE* Graf, Node_t *node, size_t temp);

const char* const edgeclr    = "#1e2460";
const char* const defaultslt = "filled";
const char* const clusterclr = "#ebd1d7";
const char* const nodeclr    = "#050505";
const char* const fontclr    = "#0a2033";
const char* const fillclr    = "#6c4675";
const size_t MAX_STR_ = 100;

#endif /* TREE_DUMP */