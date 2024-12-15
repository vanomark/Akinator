#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include "TreeDump.h"

int TreeDump(Node_t *node, const char* DumpFile, const char* GrafFile) 
{   
    assert(node);
    assert(DumpFile);

    time_t mytime = time(NULL);
    struct tm *now = localtime(&mytime);
    printf("\nDate: %02d.%02d.%d\n", now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
    printf("Time: %02d:%02d:%d\n", now->tm_hour, now->tm_min, now->tm_sec);

    FILE* Graf = fopen(DumpFile, "w");
    assert(Graf);

    fprintf(Graf, "digraph G{\n");
    fprintf(Graf, "\trankdir=TB;\n"
                  "\tedge[color=\"%s\"];\n", edgeclr);

    fprintf(Graf, "\tsubgraph cluster1 {\n"
                  "\t\tstyle = %s;\n"
		          "\t\tcolor = \"%s\";\n", defaultslt, clusterclr);
                          
    PrintNodes(Graf, node, 0);
    fprintf(Graf, "\t}\n}");

    fclose(Graf);

    char* command = (char *) calloc(MAX_STR_, sizeof(char));
    sprintf(command, "dot %s -Tsvg -o %s", DumpFile, GrafFile);
    system(command);
    free(command); command = NULL;

    return 0;
}

//============================================================
//function to traverse the tree
//3th parameter is needed for recursion algorithm, set it null 
void PrintNodes(FILE* Graf, Node_t* tree, size_t rang) 
{   
    if (tree == NULL) {
        return;
    }

    fprintf(Graf, "\t\t_%lu", (size_t) tree->question);
    fprintf(Graf, "[rang = %lu, shape=record,label=\"{ %s }\"", rang, tree->question); 
    fprintf(Graf, "style=%s," "color=\"%s\", fontcolor=\"%s\", fillcolor=\"%s\" ];\n", defaultslt, nodeclr, fontclr, fillclr);

    if (tree->left) {

        fprintf(Graf, "\t\tedge[label = \"No\"]");
        fprintf(Graf, "\t\t_%lu->_%lu;\n", (size_t) tree->question, (size_t) tree->left->question);
        PrintNodes(Graf, tree->left, rang + 1);
    }
    if (tree->right) {  

        fprintf(Graf, "\t\tedge[label = \"Yes\"]");        
        fprintf(Graf, "\t\t_%lu->_%lu;\n", (size_t) tree->question, (size_t) tree->right->question);
        PrintNodes(Graf, tree->right, rang + 1);
    }

}