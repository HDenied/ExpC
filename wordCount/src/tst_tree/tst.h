#ifndef TST_H
#define TST_H

#include<common.h>

struct TST_tree;
typedef struct TST_tree TST_TREE;


struct TST_node_s;
typedef struct TST_node_s TST_NODE;


bool is_root(const TST_TREE *tree, TST_NODE *node);
bool is_leaf(const TST_NODE* node);
bool is_end_word(const TST_NODE* node);

uint get_num_occ(const TST_NODE* node);
uint get_total_words(const TST_TREE*tree);
uint get_alloc_num(const TST_TREE*tree);

TST_NODE * get_root(TST_TREE *tree);

/* This function will fetch a word stored in the tree*/
void TST_pick_w(TST_TREE **tree_ptr, WORD_S *word_s);

/* This function will build the TST tree */
void TST_insert_w(TST_TREE **tree_ptr, char *word);


#endif