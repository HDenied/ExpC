#ifndef TST_H
#define TST_H

#include<stdbool.h>
#include<stdlib.h>


#define log_info(M, ...) fprintf(stdout, "[INF] %s:%d: " M "\n",\
        __FILE__, __LINE__, ##__VA_ARGS__)

#define log_err(M, ...) fprintf(stdout, "[ERR] %s:%d: " M "\n",\
        __FILE__, __LINE__, ##__VA_ARGS__)


#define uint unsigned int
#define W_LEN 512

struct word_s {
    char word[W_LEN];
    uint number;
    bool is_finished;
};

typedef struct word_s WORD_S;


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



#endif