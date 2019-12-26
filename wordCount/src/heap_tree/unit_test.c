#include<heap.h>
#include<utils.h>

void _check_data(HEAP_TREE *tree, DATA *ref_data, uint ref_num)
{
    uint idx_tree=0;
    HEAP_LVL *heap_lvl=NULL;
    uint idx_lvl=0;
    DATA *data=NULL;
    while(HEAP_get_w_pos(&tree, idx_tree, &heap_lvl, &idx_lvl))
    {
        assert(HEAP_get_node(heap_lvl, idx_lvl, &data));
        assert(!strcmp(data->word,ref_data[idx_tree].word));
        assert(data->n_occ==ref_data[idx_tree].n_occ);
        idx_tree++;
    }

    assert((ref_num+1) != idx_tree);
}

void _build_ref_data(DATA *array, char *ref_words[], uint *ref_occ, uint num_elements)
{
    uint idx=0;

    for (idx=0; idx<num_elements; idx++)
    {
        UTILS_init_w(&(array[idx]), ref_words[idx], ref_occ[idx]);
    }
}

void test_btree_insertion_complete()
{
    char *w_arr[] = {"marco","luca","saverio","gomma","primo","auto","martin"};
    uint ref_num = 7;
    DATA d_array[ref_num];
    DATA tmp_data;
    uint idx=0;
    HEAP_TREE *tree=NULL;

    for(idx=0;idx<ref_num;idx++)
    {
        UTILS_init_w(&tmp_data, w_arr[idx], idx+1);
        HEAP_insert_w(&tree,&tmp_data);
        assert(HEAP_get_num_w(tree)==idx+1);
        UTILS_init_w(&(d_array[idx]), w_arr[idx], idx+1);
    }

    _check_data(tree, d_array, ref_num);
    HEAP_erase(&tree);

    for (idx=0; idx<ref_num; idx++)
    {
        UTILS_deallocate_w(&(d_array[idx]));
    }
    log_info("PASSED - test_btree_insertion_complete");

}

void test_btree_insertion_single()
{
    char *w_arr[] = {"marco"};
    uint ref_num = 1;
    DATA d_array[ref_num];
    DATA tmp_data;
    uint idx=0;
    HEAP_TREE *tree=NULL;

    for(idx=0;idx<ref_num;idx++)
    {
        UTILS_init_w(&tmp_data, w_arr[idx], idx+1);
        HEAP_insert_w(&tree,&tmp_data);
        assert(HEAP_get_num_w(tree)==idx+1);
        UTILS_init_w(&(d_array[idx]), w_arr[idx], idx+1);
    }

    _check_data(tree, d_array, ref_num);
    HEAP_erase(&tree);

    for (idx=0; idx<ref_num; idx++)
    {
        UTILS_deallocate_w(&(d_array[idx]));
    }
    log_info("PASSED - test_btree_insertion_single");

}

void test_btree_insertion_partial_single()
{
    char *w_arr[] = {"marco","luca","saverio","gomma","primo","auto","martin","joseph"};
    uint ref_num = 8;
    DATA d_array[ref_num];
    DATA tmp_data;
    uint idx=0;
    HEAP_TREE *tree=NULL;

    for(idx=0;idx<ref_num;idx++)
    {
        UTILS_init_w(&tmp_data, w_arr[idx], idx+1);
        HEAP_insert_w(&tree,&tmp_data);
        assert(HEAP_get_num_w(tree)==idx+1);
        UTILS_init_w(&(d_array[idx]), w_arr[idx], idx+1);
    }

    _check_data(tree, d_array, ref_num);
    HEAP_erase(&tree);

    for (idx=0; idx<ref_num; idx++)
    {
        UTILS_deallocate_w(&(d_array[idx]));
    }
    log_info("PASSED - test_btree_insertion_partial_single");

}

void test_btree_insertion_partial_multiple()
{
    char *w_arr[] = {"marco","luca","saverio","gomma","primo","auto","martin","joseph","bike","venom"};
    uint ref_num = 10;
    DATA d_array[ref_num];
    DATA tmp_data;
    uint idx=0;
    HEAP_TREE *tree=NULL;

    for(idx=0;idx<ref_num;idx++)
    {
        UTILS_init_w(&tmp_data, w_arr[idx], idx+1);
        HEAP_insert_w(&tree,&tmp_data);
        assert(HEAP_get_num_w(tree)==idx+1);
        UTILS_init_w(&(d_array[idx]), w_arr[idx], idx+1);
    }

    _check_data(tree, d_array, ref_num);
    HEAP_erase(&tree);

    for (idx=0; idx<ref_num; idx++)
    {
        UTILS_deallocate_w(&(d_array[idx]));
    }
    log_info("PASSED - test_btree_insertion_partial_multiple");

}

void test_get_node_out_of_bound()
{
    char *w_arr[] = {"marco","luca","saverio","gomma","primo","auto","martin","joseph","bike","venom"};
    uint ref_num = 10;
    DATA tmp_data;
    uint idx=0, lvl_parent_idx=0;
    HEAP_TREE *tree=NULL;
    HEAP_LVL *heap_parent=NULL;
    HEAP_LVL *heap_child=NULL;
    DATA *res_data=NULL;


    for(idx=0;idx<ref_num;idx++)
    {
        UTILS_init_w(&tmp_data, w_arr[idx], idx+1);
        HEAP_insert_w(&tree,&tmp_data);
        assert(HEAP_get_num_w(tree)==idx+1);
    }

    //Check negative index
    assert(!HEAP_get_w_pos(&tree, -1, &heap_child, &idx));

    //Check out of range index
    assert(!HEAP_get_w_pos(&tree, 300, &heap_child, &idx));


    HEAP_erase(&tree);

    log_info("PASSED - test_get_node_out_of_bound");

}

void test_btree_get_parent()
{
    char *w_arr[] = {"marco","luca","saverio","gomma","primo","auto","martin","joseph","bike","venom"};
    uint ref_num = 10;
    DATA tmp_data;
    uint idx=0, lvl_parent_idx=0;
    HEAP_TREE *tree=NULL;
    HEAP_LVL *heap_parent=NULL;
    HEAP_LVL *heap_child=NULL;
    DATA *res_data=NULL;


    for(idx=0;idx<ref_num;idx++)
    {
        UTILS_init_w(&tmp_data, w_arr[idx], idx+1);
        HEAP_insert_w(&tree,&tmp_data);
        assert(HEAP_get_num_w(tree)==idx+1);
    }

    //Check parent first node
    assert(HEAP_get_w_pos(&tree, 0, &heap_child, &idx));
    assert(!HEAP_get_parent_pos(heap_child, idx, &heap_parent, &lvl_parent_idx));

    //Check first two nodes
    assert(HEAP_get_w_pos(&tree, 1, &heap_child, &idx));
    assert(HEAP_get_parent_pos(heap_child, idx, &heap_parent, &lvl_parent_idx));
    assert(HEAP_get_node(heap_parent, lvl_parent_idx, &res_data));
    assert(!strcmp(res_data->word, w_arr[0]));

    assert(HEAP_get_w_pos(&tree, 2, &heap_child, &idx));
    assert(HEAP_get_parent_pos(heap_child, idx, &heap_parent, &lvl_parent_idx));
    assert(HEAP_get_node(heap_parent, lvl_parent_idx, &res_data));
    assert(!strcmp(res_data->word, w_arr[0]));

    //check parent middle node
    assert(HEAP_get_w_pos(&tree, 5, &heap_child, &idx));
    assert(HEAP_get_parent_pos(heap_child, idx, &heap_parent, &lvl_parent_idx));
    assert(HEAP_get_node(heap_parent, lvl_parent_idx, &res_data));
    assert(!strcmp(res_data->word, w_arr[2]));

    //check parent middle node
    assert(HEAP_get_w_pos(&tree, 8, &heap_child, &idx));
    assert(HEAP_get_parent_pos(heap_child, idx, &heap_parent, &lvl_parent_idx));
    assert(HEAP_get_node(heap_parent, lvl_parent_idx, &res_data));
    assert(!strcmp(res_data->word, w_arr[3]));

    HEAP_erase(&tree);

    log_info("PASSED - test_btree_get_parent");
}

void test_btree_get_child()
{
    char *w_arr[] = {"marco","luca","saverio","gomma","primo","auto","martin","joseph","bike","venom"};
    uint ref_num = 10;
    DATA tmp_data;
    uint idx=0, lvl_l_child_idx=0, lvl_r_child_idx=0;
    HEAP_TREE *tree=NULL;
    HEAP_LVL *heap_parent=NULL, *heap_child=NULL;
    HEAP_LVL *heap_l_child=NULL, *heap_r_child=NULL;
    DATA *l_data=NULL, *r_data=NULL;


    for(idx=0;idx<ref_num;idx++)
    {
        UTILS_init_w(&tmp_data, w_arr[idx], idx+1);
        HEAP_insert_w(&tree,&tmp_data);
        assert(HEAP_get_num_w(tree)==idx+1);
    }

    //check children first node
    assert(HEAP_get_w_pos(&tree, 0, &heap_parent, &idx));
    assert(HEAP_get_child_pos(heap_parent, idx, &heap_child, &lvl_l_child_idx, &lvl_r_child_idx));
    assert(HEAP_get_node(heap_child, lvl_l_child_idx, &l_data));
    assert(HEAP_get_node(heap_child, lvl_r_child_idx, &r_data));
    assert(!strcmp(l_data->word, w_arr[1]));
    assert(!strcmp(r_data->word, w_arr[2]));

    //Check one leaf node
    assert(HEAP_get_w_pos(&tree, 4, &heap_parent, &idx));
    assert(HEAP_get_child_pos(heap_parent, idx, &heap_child, &lvl_l_child_idx, &lvl_r_child_idx));
    assert(HEAP_get_node(heap_child, lvl_l_child_idx, &l_data));
    assert(HEAP_get_node(heap_child, lvl_r_child_idx, &r_data));
    assert(!strcmp(l_data->word, w_arr[9]));
    assert(!UTILS_is_valid(r_data));

    //Check extreme left node
    assert(HEAP_get_w_pos(&tree, 1, &heap_parent, &idx));
    assert(HEAP_get_child_pos(heap_parent, idx, &heap_child, &lvl_l_child_idx, &lvl_r_child_idx));
    assert(HEAP_get_node(heap_child, lvl_l_child_idx, &l_data));
    assert(HEAP_get_node(heap_child, lvl_r_child_idx, &r_data));
    assert(!strcmp(l_data->word, w_arr[3]));
    assert(!strcmp(r_data->word, w_arr[4]));

    //Check extreme right node
    assert(HEAP_get_w_pos(&tree, 2, &heap_parent, &idx));
    assert(HEAP_get_child_pos(heap_parent, idx, &heap_child, &lvl_l_child_idx, &lvl_r_child_idx));
    assert(HEAP_get_node(heap_child, lvl_l_child_idx, &l_data));
    assert(HEAP_get_node(heap_child, lvl_r_child_idx, &r_data));
    assert(!strcmp(l_data->word, w_arr[5]));
    assert(!strcmp(r_data->word, w_arr[6]));

    //Check not existent nodes
    assert(HEAP_get_w_pos(&tree, 9, &heap_parent, &idx));
    assert(!HEAP_get_child_pos(heap_parent, idx, &heap_child, &lvl_l_child_idx, &lvl_r_child_idx));


    HEAP_erase(&tree);

    log_info("PASSED - test_btree_get_child");
}

void test_heapify_one_element()
{
    char *arr[] = {"marco"};
    uint occ[]={4};
    char **ref_arr=arr;
    uint *ref_occ=occ;
    uint ref_num = 1;
    DATA ref_array[ref_num];
    DATA tmp_data;
    uint idx=0;
    HEAP_TREE *tree=NULL;

    _build_ref_data(ref_array, ref_arr, ref_occ, ref_num);

    for(idx=0;idx<ref_num;idx++)
    {
        UTILS_init_w(&tmp_data, arr[idx], occ[idx]);
        HEAP_insert_w(&tree,&tmp_data);
        assert(HEAP_get_num_w(tree)==idx+1);
    }

    HEAP_build(tree, HEAP_occ_is_grater);
    _check_data(tree, ref_array, ref_num);

    HEAP_erase(&tree);
    for (idx=0; idx<ref_num; idx++)
    {
        UTILS_deallocate_w(&(ref_array[idx]));
    }

    log_info("PASSED - test_heapify_one_element");

}

void test_heapify_n_elements()
{
    char *arr[] = {"uno", "tre", "cinque", "quattro", "sei", "tredici", "dieci", "nove", "otto", "quindici", "diciassette"};
    uint occ[]= { 1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17 }; 
    char *ref_arr[]={"diciassette", "quindici", "tredici", "nove", "sei", "cinque",  "dieci", "quattro", "otto", "tre", "uno"};
    uint ref_occ[]={17, 15, 13, 9, 6, 5, 10, 4, 8, 3, 1};
    uint ref_num = 11;
    DATA ref_array[ref_num];
    DATA tmp_data;
    uint idx=0;
    HEAP_TREE *tree=NULL;

    _build_ref_data(ref_array, ref_arr, ref_occ, ref_num);

    for(idx=0;idx<ref_num;idx++)
    {
        UTILS_init_w(&tmp_data, arr[idx], occ[idx]);
        HEAP_insert_w(&tree,&tmp_data);
        assert(HEAP_get_num_w(tree)==idx+1);
    }

    HEAP_build(tree, HEAP_occ_is_grater);
    _check_data(tree, ref_array, ref_num);

    HEAP_erase(&tree);
    for (idx=0; idx<ref_num; idx++)
    {
        UTILS_deallocate_w(&(ref_array[idx]));
    }

    log_info("PASSED - test_heapify_n_elements");

}

int main()
{
    test_btree_insertion_single();
    test_btree_insertion_partial_single();
    test_btree_insertion_partial_multiple();
    test_btree_insertion_complete();
    test_get_node_out_of_bound();
    test_btree_get_parent();
    test_btree_get_child();
    test_heapify_one_element();
    test_heapify_n_elements();
    return 0;
}