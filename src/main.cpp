#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <locale.h>

#ifdef AKINATOR_DEBUG
    #define ON_DEBUG(code) code 
#else
    #define ON_DEBUG(code)
#endif /* AKINATOR_DEBUG */

#include "Tree.h"
#include "TreeDump.h"
#include "Akinator.h"


int main(const int argc, const char* argv[])
{   
    Node_t* tree = NULL;
    FILE* fp = fopen("data.txt", "r");
    fscanfTree(fp, &tree);

    play_akinator(tree);

    // fprintfTree(stderr, tree, 0);

    ON_DEBUG(TreeDump(tree, "Graf.dot", "Graf.svg");)

    DELETE_TREE(tree); 
    fclose(fp);

    return 0;
}

