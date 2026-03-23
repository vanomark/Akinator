#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "Tree.h"

enum endings {
    ENDINGS_DFLT_END =  0,
    ENDINGS_QUIT     =  1,
    ENDINGS_ERROR    = -1,
};

void           play_akinator   (Node_t* root);
enum endings   play_game       (Node_t* root);
char           skip_spaces     (void);
int            clean_buffer    (void);

#endif /* AKINATOR_H */