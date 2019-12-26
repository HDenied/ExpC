#ifndef HEAP_H
#define HEAP_H

#include<utils.h>

#define EMPTY_NODE -1

struct HEAP_level_s;
typedef struct HEAP_level_s HEAP_LVL;

struct HEAP_tree_s;
typedef struct HEAP_tree_s HEAP_TREE;

uint HEAP_get_num_w(HEAP_TREE *tree);

uint HEAP_get_num_lvl(HEAP_TREE *tree);

void HEAP_insert_w(HEAP_TREE **tree, DATA *data);

bool HEAP_get_w_pos(HEAP_TREE **tree, uint idx_tree, HEAP_LVL **heap_lvl, uint *idx_lvl);

bool HEAP_get_parent_pos(HEAP_LVL *child_lvl, uint lvl_child_idx, HEAP_LVL **parent_lvl, uint *lvl_parent_idx);

bool HEAP_get_child_pos(HEAP_LVL *parent_lvl, uint lvl_parent_idx, HEAP_LVL **child_lvl, uint *lvl_l_idx, uint *lvl_r_idx);

bool HEAP_get_node(HEAP_LVL *heap_lvl, uint idx, DATA **data);

void HEAP_sort(HEAP_TREE *tree, uint num_elements);

void HEAP_erase(HEAP_TREE **tree);



#endif