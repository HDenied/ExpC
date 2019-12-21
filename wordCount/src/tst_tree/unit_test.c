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

void _test_rm(TST_TREE *tree, char *w_array[], uint len_test_array) 
{
    uint count=0;
    uint n_words= get_total_words(tree);
    WORD_S word_s;

    for (count=0; count<n_words; count++)
    {
        //Initialise the struct to 0
        memset(&word_s,0,sizeof(WORD_S));
        TST_pick_w(&tree,&word_s);
        assert(_check_word_is_present(w_array, word_s.word, len_test_array));
        //log_info("Word %s\toccurrance=%d", word_s.word, word_s.number);
    }
    assert(tree==NULL);
}

void test_root_gen()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    char *word[] = {"ciao"};
    uint n_diff_words[] = {1};
    uint ref_alloc = 4;
    uint len_test_array = sizeof(n_diff_words)/sizeof(uint);
    WORD_S element;

    memset(&element, 0, sizeof(WORD_S));


    TST_insert_w(&tree,word[0]);

    assert(get_total_words(tree) == n_diff_words[0]);
    assert(get_alloc_num(tree) == ref_alloc);

    _test_rm(tree, word, len_test_array);

    log_info("PASSED - test_root_gen");

}

void test_equal_insertion()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"ciao"};
    uint n_diff_words[] = {1};
    uint len_test_array = sizeof(n_diff_words)/sizeof(uint);
    uint ref_alloc = 4;

    TST_insert_w(&tree,word[0]);
    TST_insert_w(&tree, word[0]);

    assert(get_total_words(tree) == n_diff_words[0]);
    assert(get_alloc_num(tree) == ref_alloc);

    _test_rm(tree, word, len_test_array);

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
    uint len_test_array = sizeof(n_diff_words)/sizeof(uint);
    uint count=0;


    for (count=0; count<4; count++)
    {
        TST_insert_w(&tree,word[count]);

        assert(get_total_words(tree) == n_diff_words[count]);
        assert(get_alloc_num(tree) == ref_alloc[count]);
        node==NULL;
    }

    _test_rm(tree, word, len_test_array);

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
    uint len_test_array = sizeof(n_diff_words)/sizeof(uint);
    uint ref_alloc = 4;
    uint count=0;


    for (count=0; count<4; count++)
    {

        TST_insert_w(&tree,word[count]);

        assert(get_total_words(tree) == n_diff_words[count]);
        assert(get_alloc_num(tree) == ref_alloc);

        node = NULL;
    }

    _test_rm(tree, word, len_test_array);

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
    uint len_test_array = sizeof(ref_occ)/sizeof(uint);
    uint n_diff_words=2;
    uint ref_alloc = 4;
    uint count=0;

    TST_insert_w(&tree,"ciao");

    node=NULL;

    for (count=0; count<2; count++)
    {
        TST_insert_w(&tree,word[count]);

        assert(get_total_words(tree) == n_diff_words);
        assert(get_alloc_num(tree) == ref_alloc);

        node = NULL;
    }

    _test_rm(tree, word_ref, len_test_array);

    log_info("PASSED - test_multiple_insertion_in_the_middle_of_longer_word");

}

void test_diff_words_beginning()
{

    TST_TREE *tree=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"ciao", "pane"};
    uint ref_words=2;
    uint ref_alloc = 8;


    TST_insert_w(&tree,word[0]);
    TST_insert_w(&tree,word[1]);
    assert(get_total_words(tree) == ref_words);
    assert(get_alloc_num(tree) == ref_alloc);
    _test_rm(tree, word, ref_words);

    log_info("PASSED - test_diff_words_beginning");

}

void test_diff_words_middle()
{

    TST_TREE *tree=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"ciaone", "ciabatta"};
    uint ref_words=2;
    uint ref_alloc = 11;


    TST_insert_w(&tree,word[0]);
    TST_insert_w(&tree,word[1]);
    assert(get_total_words(tree) == ref_words);
    assert(get_alloc_num(tree) == ref_alloc);

    _test_rm(tree, word, ref_words);
    log_info("PASSED - test_diff_words_middle");

}

void test_diff_words_end()
{

    TST_TREE *tree=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"ciaone", "ciaons"};
    uint ref_words=2;
    uint ref_alloc = 7;

    TST_insert_w(&tree,word[0]);
    TST_insert_w(&tree,word[1]);
    assert(get_total_words(tree) == ref_words);
    assert(get_alloc_num(tree) == ref_alloc);
    
    _test_rm(tree, word, ref_words);
    log_info("PASSED - test_diff_words_end");

}

void test_multiple_insertion()
{

    TST_TREE *tree=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"ciaone", "pane", "pandoro"};
    uint ref_words=3;
    uint ref_alloc = 14;

    TST_insert_w(&tree,word[0]);
    TST_insert_w(&tree,word[1]);
    TST_insert_w(&tree,word[2]);
    assert(get_total_words(tree) == ref_words);
    assert(get_alloc_num(tree) == ref_alloc);

    
    _test_rm(tree, word, ref_words);
    log_info("PASSED - test_multiple_insertion");

}

void test_single_multiple_insertion()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    char *word[] = {"i","a","e","o","u"};
    uint n_diff_words[] = {1,2,3,4,5};
    uint len_test_array = sizeof(n_diff_words)/sizeof(uint);
    uint ref_alloc[] = {1,2,3,4,5};
    uint count = 0;


    for (count=0; count<5; count++)
    {
        TST_insert_w(&tree,word[count]);

        assert(get_total_words(tree) == n_diff_words[count]);
        assert(get_alloc_num(tree) == ref_alloc[count]);
        node==NULL;
    }


    _test_rm(tree, word, len_test_array);
    log_info("PASSED - test_single_multiple_insertion");
}

void test_single_multiple_insertion_level_0()
{
    TST_TREE *tree=NULL;
    char *word[] = {"c","b","d","a","p"};
    uint n_diff_words[] = {1,2,3,4,5};
    uint ref_alloc[] = {1,2,3,4,5};
    uint len_test_array = sizeof(n_diff_words)/sizeof(uint);
    uint count = 0;

    for (count=0; count<5; count++)
    {
        TST_insert_w(&tree,word[count]);

        assert(get_total_words(tree) == n_diff_words[count]);
        assert(get_alloc_num(tree) == ref_alloc[count]);
    }

    _test_rm(tree, word, len_test_array);
    log_info("PASSED - test_single_multiple_insertion_level_0");
}

void test_multiple_words_one_side()
{
    TST_TREE *tree=NULL;
    char *word[] = {"bici","birra","broccoli", "bisaccia", "broccoli"};
    uint n_diff_words[] = {1,2,3,4,4};
    uint len_test_array = sizeof(n_diff_words)/sizeof(uint);
    uint ref_alloc[] = {4,7,14,20,20};
    uint count = 0;

    for (count=0; count<5; count++)
    {
        TST_insert_w(&tree,word[count]);

        assert(get_total_words(tree) == n_diff_words[count]);
        assert(get_alloc_num(tree) == ref_alloc[count]);
    }

    _test_rm(tree, word, len_test_array);
    log_info("PASSED - test_multiple_words_one_side");
}

void test_tree_rotation()
{
    TST_TREE *tree=NULL;
    char *word[] = {"bari","asti","como"};
    uint n_diff_words[] = {1,2,3};
    uint len_test_array = sizeof(n_diff_words)/sizeof(uint);
    uint ref_alloc[] = {4,8,12};
    uint count = 0;

    for (count=0; count<3; count++)
    {
        TST_insert_w(&tree,word[count]);

        assert(get_total_words(tree) == n_diff_words[count]);
        assert(get_alloc_num(tree) == ref_alloc[count]);
    }

    _test_rm(tree, word, len_test_array);
    log_info("PASSED - test_tree_rotation");


}

void test_full_tree()
{
    TST_TREE *tree=NULL;
    uint n_diff_words[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,13,13,13,14,14,15,
    16,17,18,19,20,20,21,22,23,24,25,26,27,28,29};
    uint ref_alloc[] = {10,15,22,25,32,32,36,37,45,49,50,54,55,55,55,55,61,
    61,67,71,78,78,78,81,81,87,90,92,100,100,100,106,107,108};
    uint len_test_array = sizeof(n_diff_words)/sizeof(uint);
    uint count = 0;

    char *word[]={"mercenario","carlo","alberto","ciro","cialtrone","ci","carletto","ma",
    "marcellino","marcelletto","marcella","mercenarietto","mercenarietta","ma","ma","ma",
    "minorca","ma","pesaro","posto","progetto","post","pro","progettino","progettino",
    "mitomane","micio","miur","trattore","mercenari","mercenar","maniglia","0","1"};

    for (count=0; count<len_test_array; count++)
    {
        TST_insert_w(&tree,word[count]);

        assert(get_total_words(tree) == n_diff_words[count]);
        assert(get_alloc_num(tree) == ref_alloc[count]);
    }

    _test_rm(tree, word, len_test_array);
    log_info("PASSED - test_full_tree");


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
    test_tree_rotation();
    test_full_tree();

    return 0;
}