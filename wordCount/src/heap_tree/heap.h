#ifndef HEAP_H
#define HEAP_H

#include<utils.h>


struct HEAP_tree_s;

typedef struct HEAP_tree_s HEAP_TREE;



void HEAP_insert_w(HEAP_TREE **tree, char *word);


void HEAP_sort(HEAP_TREE *tree, uint num_elements);



#endif