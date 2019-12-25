#include<utils.h>
#include<tst.h>

int main()
{

    FILE *fp;
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    WORD_S word_s;
    char f_path[]="../mobydick.txt";
    char word[W_LEN]="\0";    
    fp = fopen(f_path, "rb");
    WORD_S *word_arr=NULL;
    uint w_len=0;
    uint w_idx=0;
    uint longest_w_size=0;

    /* Populating the tree */
    while(UTILS_tokenize(fp, word))
    {
        TST_insert_w(&tree,word);
        word[0]='\0';
    }

    longest_w_size=get_size_longest_word(tree);
    log_dbg("Total different words: %u, total allocations: %u, longest word size: %u", get_total_words(tree), get_alloc_num(tree), longest_w_size);

    fclose(fp);

    word_arr=calloc(get_total_words(tree),sizeof(WORD_S));


    /* Extracting the words */
    while(tree)
    {        
        memset(&word_s,0,sizeof(WORD_S));
        TST_pick_w(&tree,&word_s);

        w_len = UTILS_get_word_len(word_s.word);
        word_arr[w_idx].number=word_s.number;
        memcpy(word_arr[w_idx].word,word_s.word, w_len);
        word_arr[w_idx].word[w_len+1]='\0';
        UTILS_insertionSort(word_arr, w_idx);
        w_idx++;

    }

    for(w_idx=0; w_idx<20; w_idx++)
        printf("%+10u %s\n",  word_arr[w_idx].number, word_arr[w_idx].word);



    return 0;
}