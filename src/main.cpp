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
    FILE* fp = NULL;
    if (argc == 1) {
        fp = fopen(DEFAULT_DATA_FILE, "r");
    } else {
        fp = fopen(argv[1], "r");
    }
    Node_t* tree = NULL;
    fscanfTree(fp, &tree);
    
    play_akinator(fp, tree);

    DELETE_TREE(tree); 
    fclose(fp);

    return 0;
}

