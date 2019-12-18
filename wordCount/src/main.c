#include<common.h>
#include<utils.h>
#include<tst.h>

#define BREAK_NUM 10204


int main()
{

    FILE *fp;
    TST_TREE *tree=NULL;
    TST_NODE *node=NULL;
    WORD_S word_s;
    char skip_delimiters[] = {',', '\n', '.', ';', '\t', '*', '!', '[', ']', '(',')','@','#','"','-'};
    char f_path[]="../mobydick.txt";
    char word[W_LEN]="\0";    
    fp = fopen(f_path, "rb");
    bool b_not_end=true;
    uint count=0;
    WORD_S word_arr[BREAK_NUM];

    memset(word_arr, 0, BREAK_NUM*sizeof(WORD_S));

    /* Populating the tree */
    while(b_not_end)
    {
        b_not_end=UTILS_tokenize(fp, word,' ', skip_delimiters, sizeof(skip_delimiters)/sizeof(char));
        TST_path_add(&tree,&node, word);
        word[0]='\0';
    }

    fclose(fp);


    /* Extracting the words */
    while(true)
    {
        memset(&word_s,0,sizeof(WORD_S));
        TST_path_rmv(&tree,&word_s);

        if((strcmp(word_s.word,"T")))
        {
            uint w_len = UTILS_get_word_len(word_s.word);
            word_arr[count].number=word_s.number;
            memcpy(word_arr[count].word,word_s.word, w_len);
            word_arr[count].word[w_len+1]='\0';
            UTILS_insertionSort(word_arr, count);

        }
        else
        {
            break;
        }
        
        count++;
    }

    for(count=0; count<20; count++)
        printf("Word:%s, num:%d\n",word_arr[count].word, word_arr[count].number);



    return 0;
}