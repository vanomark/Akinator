#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
//====================================================================================================================//
#define AKINATOR_DEBUG
//====================================================================================================================//
#ifdef AKINATOR_DEBUG
    #define ON_DEBUG(code) code 
#else
    #define ON_DEBUG(code)
#endif /* AKINATOR_DEBUG */

#include "Tree.h"
#include "TreeDump.h"

// int clean_buffer(void) 
// {
//     char ch = (char) getchar();        
//     while (ch != '\n' && ch != EOF) {
//         ch = (char) getchar();
//         putc(ch, stdout);
//     }
//     return 0;
// }

int main()
{   
    
    // Node_t * tree = newNode("Dick?");
    // Node_t * ltree = newNode("Cock?");
    // Node_t * rtree = newNode("Pisun?");
    // Node_t * ltree1 = newNode("ABIBA");
    // Node_t * rtree1 = newNode("ABOBA");
    // Node_t * ltree2 = newNode("BOBUS");
    // Node_t * rtree2 = newNode("BOBIC");
    
    // tree->left = ltree;
    // tree->right = rtree;
    // tree->left->left = ltree1;
    // tree->left->right = rtree1;
    // tree->right->left = ltree2;
    // tree->right->right = rtree2;

    Node_t* tree = NULL;
    FILE* fp = fopen("data.txt", "r");
    fscanfTree(fp, &tree);

    

    // fprintfTree(stderr, tree, 0);

    ON_DEBUG(TreeDump(tree, "Graf.dot", "Graf.svg");)

    DELETE_TREE(tree);

    printf("Bobic\n");

    // char* buffer = (char *) calloc(MAX_STR, sizeof(char));
    // buffer[0] = '{';
    // buffer[1] = '{';
    // buffer[2] = '{';
    // buffer[3] = '}';
    // buffer[4] = '{';
    // buffer[5] = '}';
    // buffer[6] = '}';
    // buffer[7] = '{';
    // buffer[8] = '{';
    // printf("%s\n", buffer);
    // size_t depth = 0;
    // int *path = getPath(buffer, &depth);

    // for (size_t i = 0; i < depth; i++)
    //     printf("%d", path[i]);

    // free(buffer);
    // free(path);

    return 0;
}

