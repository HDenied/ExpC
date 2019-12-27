#include<utils.h>
#include<tst.h>
#include<heap.h>

int main()
{

    FILE *fp;
    TST_TREE *tree=NULL;
    HEAP_TREE *h_tree = NULL;
    WORD_S word_s;
    char f_path[]="../mobydick.txt";
    char word[W_LEN]="\0";    
    fp = fopen(f_path, "rb");
    DATA tmp_data;
    uint longest_w_size=0;

    /* Populating TST tree */
    while(UTILS_tokenize(fp, word))
    {
        TST_insert_w(&tree,word);
        word[0]='\0';
    }

    longest_w_size=get_size_longest_word(tree);
    log_dbg("Total different words: %u, total allocations: %u, longest word size: %u", get_total_words(tree), get_alloc_num(tree), longest_w_size);

    fclose(fp);


    /* Extracting the words and hipifying*/
    while(tree)
    {        
        memset(&word_s,0,sizeof(WORD_S));
        TST_pick_w(&tree,&word_s);
        UTILS_init_w(&tmp_data, word_s.word, word_s.number);
        HEAP_insert_w(&h_tree,&tmp_data);
    }
    
    HEAP_sort(h_tree, HEAP_cmp_occ);
    HEAP_print_tree(h_tree,20);
    HEAP_erase(&h_tree);

    return 0;
}