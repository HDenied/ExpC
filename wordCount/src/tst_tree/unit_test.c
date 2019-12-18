#include<tst.h>



bool _check_word_is_present(char *w_array[], char *word, uint word_num)
{
    uint count=0;

    for (count=0; count<word_num; count++)
    {
        if(!strcmp(w_array[count], word))
            return true;
    }

    return false;
}

void _test_rm(TST_TREE *tree, char *w_array[]) 
{
    uint count=0;
    uint n_words= get_total_words(tree);
    WORD_S word_s;

    for (count=0; count<n_words; count++)
    {
        //Initialise the struct to 0
        memset(&word_s,0,sizeof(WORD_S));
        TST_path_rmv(&tree,&word_s);
        assert(_check_word_is_present(w_array, word_s.word, n_words));
    }
    assert(tree==NULL);
}

void test_root_gen()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    char *word[] = {"ciao"};
    uint n_diff_words = 1;
    uint ref_alloc = 4;
    WORD_S element;

    memset(&element, 0, sizeof(WORD_S));


    assert(TST_path_add(&tree,&node, word[0]));

    assert(get_total_words(tree) == n_diff_words);
    assert(get_alloc_num(tree) == ref_alloc);

    _test_rm(tree, word);

    log_info("PASSED - test_root_gen");

}

void test_equal_insertion()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"ciao"};
    uint n_diff_words = 1;
    uint ref_alloc = 4;

    assert(TST_path_add(&tree,&node, word[0]));
    assert(TST_path_add(&tree,&last_matching, word[0]));

    assert(get_total_words(tree) == 1);
    assert(get_alloc_num(tree) == ref_alloc);

    _test_rm(tree, word);

    log_info("PASSED - test_equal_insertion");

   
}

void test_longer_matching_insertion()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"ciao", "ciaoo", "ciaoos", "ciaoosoo"};
    uint n_diff_words[] = {1,2,3,4};
    uint ref_alloc[] = {4,5,6,8};
    uint count=0;


    for (count=0; count<4; count++)
    {
        assert(TST_path_add(&tree,&node, word[count]));

        assert(get_total_words(tree) == n_diff_words[count]);
        assert(get_alloc_num(tree) == ref_alloc[count]);
        assert(get_num_occ(node)==1);
        assert(is_end_word(node));
        node==NULL;
    }

    _test_rm(tree, word);

    log_info("PASSED - test_longer_matching_insertion");
   
}

void test_shorter_matching_insertion()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"ciao", "cia", "ci", "c"};
    uint ref_occ = 1;
    uint n_diff_words[] = {1,2,3,4};
    uint ref_alloc = 4;
    uint count=0;


    for (count=0; count<4; count++)
    {
        assert(TST_path_add(&tree,&node, word[count]));

        assert(get_num_occ(node) == ref_occ);
        assert(get_total_words(tree) == n_diff_words[count]);
        assert(get_alloc_num(tree) == ref_alloc);
        assert(is_end_word(node));

        node = NULL;
    }

    _test_rm(tree, word);

    log_info("PASSED - test_shorter_matching_insertion");
   
}

void test_multiple_insertion_in_the_middle_of_longer_word()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"ci", "ci"};
    char *word_ref[] = {"ci", "ciao"};
    uint ref_occ[] = {1,2};
    uint n_diff_words=2;
    uint ref_alloc = 4;
    uint count=0;

    TST_path_add(&tree,&node, "ciao");
    node=NULL;

    for (count=0; count<2; count++)
    {
        assert(TST_path_add(&tree,&node, word[count]));

        assert(get_num_occ(node) == ref_occ[count]);
        assert(get_total_words(tree) == n_diff_words);
        assert(get_alloc_num(tree) == ref_alloc);
        assert(is_end_word(node));

        node = NULL;
    }

    _test_rm(tree, word_ref);

    log_info("PASSED - test_multiple_insertion_in_the_middle_of_longer_word");

}

void test_diff_words_beginning()
{

    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"ciao", "pane"};
    uint ref_words=2;
    uint ref_alloc = 8;


    assert(TST_path_add(&tree,&node, word[0]));
    assert(is_end_word(node));
    node=NULL;
    assert(TST_path_add(&tree,&node, word[1]));
    assert(get_total_words(tree) == ref_words);
    assert(get_alloc_num(tree) == ref_alloc);
    assert(is_end_word(node));
    _test_rm(tree, word);

    log_info("PASSED - test_diff_words_beginning");

}

void test_diff_words_middle()
{

    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"ciaone", "ciabatta"};
    uint ref_words=2;
    uint ref_alloc = 11;


    assert(TST_path_add(&tree,&node, word[0]));
    assert(is_end_word(node));
    node=NULL;
    assert(TST_path_add(&tree,&node, word[1]));
    assert(get_total_words(tree) == ref_words);
    assert(get_alloc_num(tree) == ref_alloc);
    assert(is_end_word(node));

    _test_rm(tree, word);
    log_info("PASSED - test_diff_words_middle");

}

void test_diff_words_end()
{

    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"ciaone", "ciaons"};
    uint ref_words=2;
    uint ref_alloc = 7;


    assert(TST_path_add(&tree,&node, word[0]));
    assert(is_end_word(node));
    node=NULL;
    assert(TST_path_add(&tree,&node, word[1]));
    assert(get_total_words(tree) == ref_words);
    assert(get_alloc_num(tree) == ref_alloc);
    assert(is_end_word(node));
    
    _test_rm(tree, word);
    log_info("PASSED - test_diff_words_end");

}

void test_multiple_insertion()
{

    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"ciaone", "pane", "pandoro"};
    uint ref_words=3;
    uint ref_alloc = 14;


    assert(TST_path_add(&tree,&node, word[0]));
    node=NULL;
    assert(TST_path_add(&tree,&node, word[1]));
    node=NULL;
    assert(TST_path_add(&tree,&node, word[2]));
    assert(get_total_words(tree) == ref_words);
    assert(get_alloc_num(tree) == ref_alloc);
    assert(is_end_word(node));
    
    _test_rm(tree, word);
    log_info("PASSED - test_multiple_insertion");

}

void test_single_multiple_insertion()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"i","a","e","o","u"};
    uint ref_words[] = {1,2,3,4,5};
    uint ref_alloc[] = {1,2,3,4,5};
    uint count = 0;

    for(count=0;count<5;count++)
    {
        assert(TST_path_add(&tree,&node, word[count]));
        assert(get_total_words(tree) == ref_words[count]);
        assert(get_alloc_num(tree) == ref_alloc[count]);
        assert(is_end_word(node));
        node=NULL;
    }

    _test_rm(tree, word);
    log_info("PASSED - test_single_multiple_insertion");
}

void test_single_multiple_insertion_level_0()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"c","b","d","a","p"};
    uint ref_words[] = {1,2,3,4,5};
    uint ref_alloc[] = {1,2,3,4,5};
    uint count = 0;

    for(count=0;count<5;count++)
    {
        assert(TST_path_add(&tree,&node, word[count]));
        assert(get_total_words(tree) == ref_words[count]);
        assert(get_alloc_num(tree) == ref_alloc[count]);
        assert(is_end_word(node));
        node=NULL;
    }

    _test_rm(tree, word);
    log_info("PASSED - test_single_multiple_insertion_level_0");
}

void test_multiple_words_one_side()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"bici","birra","broccoli", "bisaccia", "broccoli"};
    uint ref_words[] = {1,2,3,4,4};
    uint ref_alloc[] = {4,7,14,20,20};
    uint count = 0;

    for(count=0;count<5;count++)
    {
        assert(TST_path_add(&tree,&node, word[count]));
        assert(get_total_words(tree) == ref_words[count]);
        assert(get_alloc_num(tree) == ref_alloc[count]);
        assert(is_end_word(node));
        node=NULL;
    }

    _test_rm(tree, word);
    log_info("PASSED - test_multiple_words_one_side");
}

void test_3_long_words_at_top()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"bari","asti","como"};
    uint ref_words[] = {1,2,3};
    uint ref_alloc[] = {4,8,12};
    uint count = 0;

    for(count=0;count<3;count++)
    {
        assert(TST_path_add(&tree,&node, word[count]));
        assert(get_total_words(tree) == ref_words[count]);
        assert(get_alloc_num(tree) == ref_alloc[count]);
        assert(is_end_word(node));
        node=NULL;
    }

    _test_rm(tree, word);
    log_info("PASSED - test_3_long_words_at_top");


}



int main(int argc, void *argv[]) 
{
    test_root_gen();
    test_equal_insertion();
    test_longer_matching_insertion();
    test_shorter_matching_insertion();
    test_multiple_insertion_in_the_middle_of_longer_word();
    test_diff_words_beginning();
    test_diff_words_middle();
    test_diff_words_end();
    test_multiple_insertion();
    test_single_multiple_insertion();
    test_single_multiple_insertion_level_0();
    test_multiple_words_one_side();
    test_3_long_words_at_top();

    return 0;
}