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

/* This function will build the TST tree */
bool TST_path_add(TST_TREE **tree_ptr, TST_NODE **last_matching, const char *word);

/* This function will pop a word stored in the tree*/
void TST_path_rm(TST_TREE **tree_ptr, TST_NODE *node, WORD_S *word, uint pos);

void TST_path_rmv(TST_TREE **tree_ptr, WORD_S *word_s);




#endif