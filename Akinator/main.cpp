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

#include "../BinaryTree/Tree.h"
#include "../BinaryTree/TreeDump.h"
#include "Akinator.h"


int main(const int argc, const char* argv[])
{   
    game_mode AkinatorMode = MODE_GRAPHICS;
    const char* inputFilePath = DEFAULT_DATA_FILE; 

    for (int i = 1; i < argc; ++i) {
        std::string_view arg = argv[i];

        if (arg == "--gui" || arg == "-g") {
            AkinatorMode = MODE_GRAPHICS;
        } 
        else if (arg == "--text" || arg == "-t") {
            AkinatorMode = MODE_CONSOLE;
        } 
        
        else if (arg == "--file" || arg == "-f") {
            
            if (i + 1 < argc) {
                inputFilePath = argv[++i]; 

            } else {
                fprintf(stderr, "ERROR: No file given");
                return 1;
            }
        } 
    }

    FILE* fp = NULL;
    fp = fopen(inputFilePath, "r");
    assert(fp);
    Node_t* tree = NULL;
    fscanfTree(fp, &tree);

    
    play_akinator(fp, tree, AkinatorMode);
    DELETE_TREE(tree); 
    fclose(fp);

    return 0;
}

