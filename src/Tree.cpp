#include "Tree.h"

// function for creation a new node
Node_t* newNode(Data_t data) 
{
    Node_t* node = (Node_t*) calloc(sizeof(Node_t), 1);
    node->question = (char *) calloc(MAX_STR, sizeof(char));
    strcpy(node->question, data);
    node->left = node->right = NULL;

    return node;
}

// function for deletion a tree
void deleteTree(Node_t* root) 
{
    if (root == NULL) {
        return;
    }
    
    deleteTree(root->left);
    deleteTree(root->right);

    free(root->question); root->question = NULL;
    free(root); root = NULL;
}

// function print given tree into entered file (pre-order)
// 2th parametr is needed for recursion algorithm, set it null
void fprintfTree(FILE* outfile, Node_t* node, size_t depth) 
{   
    assert(outfile);

    if (node == NULL) {
        return;
    }

    if (depth >= MAX_DEPTH) {
        fprintf(stderr, "ERROR: wrong depth");
        abort();
    }

    for (size_t i = 0; i < depth; i++) {
        printf("\t");
    }
    printf("{\n");

    for (size_t i = 0; i <= depth; i++) {
        printf("\t");
    }
    printf("\"%s\"\n", node->question);

    if (node->left ) fprintfTree(outfile, node->left, depth + 1);
    if (node->right) fprintfTree(outfile, node->right, depth + 1);

    for (size_t i = 0; i < depth; i++) {
        printf("\t");
    }
    printf("}\n");
}

void fscanfTree(FILE* inputfile, Node_t** root)
{   
    assert(inputfile);

    char* matrix = (char *) calloc(2 * MAX_DEPTH, sizeof(char));
    char  symbol = 0;

    size_t lt_bracket_num = 0;
    size_t rt_bracket_num = 0;

    while (lt_bracket_num != rt_bracket_num || lt_bracket_num == 0 || rt_bracket_num == 0) {
        while ((symbol = (char) fgetc(inputfile)) != '{' && symbol != '}' && symbol != '\"' && symbol != EOF);
        
        if (symbol == EOF) {
            fprintf(stderr, "ERROR: broken input file\n");
            assert(0);
        }

        if (symbol == '{') {
            lt_bracket_num++;
            matrix[lt_bracket_num + rt_bracket_num - 1] = '{';
        }
        if (symbol == '}') {
            rt_bracket_num++;
            matrix[lt_bracket_num + rt_bracket_num - 1] = '}';
        }


        if (symbol == '\"') {

            char* buffer = (char *) calloc(MAX_STR, sizeof(char));

            for (size_t i = 0; (symbol = (char) fgetc(inputfile)) != '\"' && symbol != EOF && i < MAX_STR; i++) {
                
                if (symbol == '}' || symbol == '{') {
                    fprintf(stderr, "ERROR: broken input file\n");
                    assert(0);
                }
                buffer[i] = symbol;
            }

            if (symbol == EOF) {
                fprintf(stderr, "ERROR: broken input file\n");
                assert(0);
            }

            fprintf(stderr, "\nbuffer = %s\n", buffer);
            fprintf(stderr, "matrix = %s\npath = ", matrix);

            size_t depth = 0;
            int *path = getPath(matrix, &depth);

            for (size_t i = 0; i < depth; i++)
                fprintf(stderr, "%d", path[i]);
            
            if (depth == 0) {
                *root = newNode(buffer);
            }
            Node_t* node = *root;
            fprintf(stderr, "root = %p\n", *root);
            

            for (size_t i = 0; i < depth; i++) {

                if (path[i] == LEFT) {

                    if (node->left == NULL) {
                        node->left = newNode(buffer);
                    }
                    node = node->left;
                }
                if (path[i] == RIGHT) {

                    if (node->right == NULL) {
                        node->right = newNode(buffer);
                    }
                    node = node->right;
                }
            }

            fprintf(stderr, "node = %p\n", node);


            free(path  );   path = NULL;
            free(buffer); buffer = NULL;
        }
        
    }

    free(matrix); matrix = NULL;
}

int *getPath(char* matrix, size_t* depth)
{   
    assert(matrix);

    int* path = (int *) calloc(MAX_DEPTH, sizeof(int));

    size_t pathlen = 0;
    bool go_right = false;

    for (size_t i = 1; matrix[i] != 0; i++) {

        if (matrix[i] == '{') {

            if (!go_right) {
                path[pathlen] = LEFT;
            } else {
                path[pathlen] = RIGHT;
                go_right = false;
            }
            pathlen++;
        }

        if (matrix[i] == '}') {
            pathlen--;
            go_right = true;
        }
    }

    *depth = pathlen;
    path = (int *) realloc(path, pathlen * sizeof(int));

    return path;
}

// function for node insertion in binary tree
// returns tree with new node
Node_t* insertNode(Node_t* root, Data_t data) 
{
    if (root == NULL) {
        return newNode(data);
    }

    if (root->left) {
        insertNode(root->left, data);
    }
    if (root->right) {
        insertNode(root->right, data);
    }



    return root;
}

// // function for determination tree depth
// int treeDepth(Node_t* root) 
// {
//     if (root == NULL) {
//         return 0;
//     }
//     int leftDepth = treeDepth(root->left);
//     int rightDepth = treeDepth(root->right);

//     return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
// }

// // function for a symmetrical traversal (in-order)
// void inorderTraversal(Node_t* node) 
// {
//     if (node == NULL) {
//         return;
//     }
//     printf("(");
//     printf("%d", node->question);

//     if (node->left ) inorderTraversal(node->left);
//     printf("%d", node->question);
//     if (node->right) inorderTraversal(node->right);

//     printf(")");
// }



// // Function for a reversed traversal (post-order)
// void postorderTraversal(Node_t* node) 
// {
//     if (node == NULL) {
//         return;
//     }
//     printf("(");

//     if (node->left ) postorderTraversal(node->left);
//     if (node->right) postorderTraversal(node->right);

//     printf("%d", node->question);
//     printf(")");
// }



// // Function for search node with minimal tree element 
// Node_t* findMin(Node_t* root) 
// {
//     while (root->left != NULL) {
//         root = root->left;
//     }
//     return root;
// }

// Node_t* findNode(Node_t* root, int value) 
// {
//     if (root == NULL) {
//         return NULL;
//     }

//     if (root->question == value) {
//         return root;
//     }

//     if (value < root->question) {
//         return findNode(root->left, value);
//     } else {
//         return findNode(root->right, value);
//     }
// }

// Node_t* deleteNodeWithoutSubtree(Node_t* root, int data) 
// {
//     if (root == NULL) {
//         return root;
//     }
    
//     if (data < root->question) {
//         root->left = deleteNodeWithoutSubtree(root->left, data);
//     } else if (data > root->question) {
//         root->right = deleteNodeWithoutSubtree(root->right, data);
//     } else { 
//         // Deleting current node without deleting it's subtree
//         if (root->left == NULL) {
//             Node_t* temp = root->right;
//             free(root);
//             return temp;
//         } else if (root->right == NULL) {
//             Node_t* temp = root->left;
//             free(root);
//             return temp;
//         } else {
//             // If node has both left and right subtree, seek for min element in the right one
//             Node_t* temp = findMin(root->right);
//             root->question = temp->question;
//             root->right = deleteNodeWithoutSubtree(root->right, temp->question);
//         }
//     }
//     return root;
// }

// // Function for deletion node with it's subtree
// void deleteNodeWithSubtree(Node_t* root, int value) 
// {
//     if (root == NULL) {
//         return;
//     }

//     if (root->question == value) {
//         if (root->left != NULL) {
//             deleteNodeWithSubtree(root->left, root->left->question);
//         }
//         if (root->right != NULL) {
//             deleteNodeWithSubtree(root->right, root->right->question);
//         }
//         free(root);

//         return;
//     }

//     if (value < root->question) {
//         deleteNodeWithSubtree(root->left, value);
//     } else {
//         deleteNodeWithSubtree(root->right, value);
//     }
// }
