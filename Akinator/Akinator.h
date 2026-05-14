#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "Akinator_SFML.hpp"
#include "../BinaryTree/Tree.h"
#include "../BinaryTree/TreeDump.h"

#define DEFAULT_DATA_FILE "./Data/data.txt"
#define DEFAULT_DOT_FILE "./Data/Graf.dot"
#define DEFAULT_SVG_FILE "./Data/Graf.svg"

enum game_mode {
    MODE_CONSOLE = 0,
    MODE_GRAPHICS = 1, 
};

enum endings {
    ENDINGS_DFLT_END =  0,
    ENDINGS_QUIT     =  1,
    ENDINGS_ERROR    = -1,
};

void           play_akinator           (FILE* fp, Node_t* root, game_mode mode);
void           play_akinator_console   (FILE* fp, Node_t* root);
enum endings   play_game               (Node_t* root);
char           skip_spaces             (void);
int            clean_buffer            (void);

#endif /* AKINATOR_H */