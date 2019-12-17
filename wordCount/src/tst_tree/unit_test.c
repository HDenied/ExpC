#include<stdio.h>
#include<string.h>
#include<assert.h>

#include<tst.h>


uint _get_word_len(const char *word)
{
    uint len = 0;
    while(*(word+len))
        len++;
    return len;
}

///////////////////////////////////////////////////////// TESTS /////////////////////////////////////////////
void test_root_gen()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    char word[] = "ciao";
    uint n_diff_words = 1;
    uint ref_alloc = 4;
    WORD_S element;

    memset(&element, 0, sizeof(WORD_S));


    assert(TST_path_builder(&tree,&node, word));

    assert(get_total_words(tree) == n_diff_words);
    assert(get_alloc_num(tree) == ref_alloc);

    TST_pop_word(&tree, get_root(tree), &element, 0);

    log_info("PASSED - test_root_gen");

}

void test_equal_insertion()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    char word[] = "ciao";
    uint n_diff_words = 1;
    uint ref_alloc = 4;

    assert(TST_path_builder(&tree,&node, word));
    assert(TST_path_builder(&tree,&last_matching, word));

    assert(get_total_words(tree) == 1);
    assert(get_alloc_num(tree) == ref_alloc);

    log_info("PASSED - test_equal_insertion");

   
}

void test_longer_matching_insertion()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    const char *word[] = {"ciao", "ciaoo", "ciaoos", "ciaoosoo"};
    uint n_diff_words[] = {1,2,3,4};
    uint ref_alloc[] = {4,5,6,8};
    uint count=0;


    for (count=0; count<4; count++)
    {
        assert(TST_path_builder(&tree,&node, word[count]));

        assert(get_total_words(tree) == n_diff_words[count]);
        assert(get_alloc_num(tree) == ref_alloc[count]);
        assert(get_num_occ(node)==1);
        assert(is_end_word(node));
        node==NULL;
    }

    log_info("PASSED - test_longer_matching_insertion");
   
}

void test_shorter_matching_insertion()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    const char *word[] = {"ciao", "cia", "ci", "c"};
    uint ref_occ = 1;
    uint n_diff_words[] = {1,2,3,4};
    uint ref_alloc = 4;
    uint count=0;


    for (count=0; count<4; count++)
    {
        assert(TST_path_builder(&tree,&node, word[count]));

        assert(get_num_occ(node) == ref_occ);
        assert(get_total_words(tree) == n_diff_words[count]);
        assert(get_alloc_num(tree) == ref_alloc);
        assert(is_end_word(node));

        node = NULL;
    }

    log_info("PASSED - test_shorter_matching_insertion");
   
}

void test_multiple_insertion_in_the_middle_of_longer_word()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    const char *word[] = {"ci", "ci"};
    uint ref_occ[] = {1,2};
    uint n_diff_words=2;
    uint ref_alloc = 4;
    uint count=0;

    TST_path_builder(&tree,&node, "ciao");
    node=NULL;

    for (count=0; count<2; count++)
    {
        assert(TST_path_builder(&tree,&node, word[count]));

        assert(get_num_occ(node) == ref_occ[count]);
        assert(get_total_words(tree) == n_diff_words);
        assert(get_alloc_num(tree) == ref_alloc);
        assert(is_end_word(node));

        node = NULL;
    }

    log_info("PASSED - test_multiple_insertion_in_the_middle_of_longer_word");

}

void test_diff_words_beginning()
{

    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    const char *word[] = {"ciao", "pane"};
    uint ref_words=2;
    uint ref_alloc = 8;


    assert(TST_path_builder(&tree,&node, word[0]));
    assert(is_end_word(node));
    node=NULL;
    assert(TST_path_builder(&tree,&node, word[1]));
    assert(get_total_words(tree) == ref_words);
    assert(get_alloc_num(tree) == ref_alloc);
    assert(is_end_word(node));
    log_info("PASSED - test_diff_words_beginning");

}

void test_diff_words_middle()
{

    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    const char *word[] = {"ciaone", "ciabatta"};
    uint ref_words=2;
    uint ref_alloc = 11;


    assert(TST_path_builder(&tree,&node, word[0]));
    assert(is_end_word(node));
    node=NULL;
    assert(TST_path_builder(&tree,&node, word[1]));
    assert(get_total_words(tree) == ref_words);
    assert(get_alloc_num(tree) == ref_alloc);
    assert(is_end_word(node));
    log_info("PASSED - test_diff_words_middle");

}

void test_diff_words_end()
{

    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    const char *word[] = {"ciaone", "ciaons"};
    uint ref_words=2;
    uint ref_alloc = 7;


    assert(TST_path_builder(&tree,&node, word[0]));
    assert(is_end_word(node));
    node=NULL;
    assert(TST_path_builder(&tree,&node, word[1]));
    assert(get_total_words(tree) == ref_words);
    assert(get_alloc_num(tree) == ref_alloc);
    assert(is_end_word(node));
    
    log_info("PASSED - test_diff_words_end");

}

void test_multiple_insertion()
{

    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    const char *word[] = {"ciaone", "pane", "pandoro"};
    uint ref_words=3;
    uint ref_alloc = 14;


    assert(TST_path_builder(&tree,&node, word[0]));
    node=NULL;
    assert(TST_path_builder(&tree,&node, word[1]));
    node=NULL;
    assert(TST_path_builder(&tree,&node, word[2]));
    assert(get_total_words(tree) == ref_words);
    assert(get_alloc_num(tree) == ref_alloc);
    assert(is_end_word(node));
    
    log_info("PASSED - test_multiple_insertion");

}

void test_single_multiple_insertion()
{
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    TST_NODE *last_matching=NULL;
    const char *word[] = {"i","a","e","o","u"};
    uint ref_words[] = {1,2,3,4,5};
    uint ref_alloc[] = {1,2,3,4,5};
    uint count = 0;

    for(count=0;count<5;count++)
    {
        assert(TST_path_builder(&tree,&node, word[count]));
        assert(get_total_words(tree) == ref_words[count]);
        assert(get_alloc_num(tree) == ref_alloc[count]);
        assert(is_end_word(node));
        node=NULL;
    }
    
    log_info("PASSED - test_single_multiple_insertion");
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

    return 0;
}