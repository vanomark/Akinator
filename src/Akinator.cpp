#include "Akinator.h"
#include "ColorPrintFile.h"

void play_akinator(Node_t* root)
{
    printf("\n" YELLOW("Choose one of the options:") "\n");
    printf(YELLOW("<p> (play)\n<q> (quit)\n"));

    char option = (char) tolower(skip_spaces());

    if (option == 'p') {

        printf(YELLOW("Let's play.\n"));
        int check_end = play_game(root);
        
        if (check_end == ENDINGS_ERROR) {
            printf(YELLOW("Go eshe raz? [Yes/No]:\n"));
            char answer = (char) tolower(skip_spaces());

            if (answer == 'y') {

                clean_buffer();
                play_akinator(root);

            } else if (answer == 'n') {

                printf(YELLOW("Nu i poshel ti"));
                clean_buffer();
                return;

            } else {

                printf(YELLOW("Eblan takoy option netu.\nZavershau.\n"));
                clean_buffer();
                return;
            }
        }

    } else if (option == 'q') {

        printf(YELLOW("Quiting the game...\n"));
        return;

    } else {

        printf(YELLOW("Eblan takoy option netu.\nZanovo.\n"));
        clean_buffer();
        play_akinator(root);
    }
}

enum endings play_game(Node_t* root)
{   
    if (root->left && root->right) {
        printf(CYAN("%s [Yes/No]:\n"), root->question);
    } else {
        printf(YELLOW("Eto %s!!!\n"), root->question);
        return ENDINGS_DFLT_END;
    }

    char answer = (char) tolower(skip_spaces());

    if (answer == 'y') {

        clean_buffer();
        play_game(root->right);

    } else if (answer == 'n') {

        clean_buffer();
        play_game(root->left);

    } else if (answer == 'q') {

        printf(YELLOW("Nu i poshel ti\n"));
        clean_buffer();
        return ENDINGS_QUIT;

    } else {

        printf(YELLOW("Eblan takoy option netu.\nZanovo.\n"));
        clean_buffer();
        play_game(root);     
    }

    return ENDINGS_ERROR;
}

int clean_buffer(void) 
{
    char ch = (char) getchar();        
    while (ch != '\n' && ch != EOF) {
        ch = (char) getchar();
    }
    return 0;
}

char skip_spaces(void)
{
    char ch = (char) getchar();        
    while (ch == ' ' || ch == '\n' || ch == '\t') {
        ch = (char) getchar();
    }
    return ch;
}