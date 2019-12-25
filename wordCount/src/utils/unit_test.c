#include<utils.h>

void test_reading_bin_file()
{
    FILE *fp;
    char skip_delimiters[] = {',', '\n', '.', ';', '\t', '*', '!', '[', ']', '(',')','{', '}','@','#','\\','/','\"','\'','\?','-'};
    char f_path[]="./test_read.txt";
    char word[W_LEN]="\0";    
    uint count=0;
    char *ref_words[]=  {"mercenario","carlo","alberto","ciro","cialtrone","ci","carletto","ma",
    "marcellino","marcelletto","marcella","mercenarietto","mercenarietta","ma","ma","ma",
    "minorca","ma","pesaro","posto","progetto","post","pro","progettino","progettino",
    "mitomane","micio","miur","trattore","mercenari","mercenar","maniglia","0","1"};
    fp = fopen(f_path, "rb");

    while(UTILS_tokenize(fp,word))
    {
        assert(!strcmp(word,ref_words[count]));
        log_dbg("%-10s len: %u\n", word, UTILS_get_word_len(word));
        word[0]='\0';
        count++;
    }
  
    fclose(fp);

    log_info("PASSED - test_reading_bin_file");

}

void test_insertion_sort()
{
    WORD_S w_array[]={{"marco",90}, {"luca",17}, {"auto",2},{"bike",32}, {"gino",8}};    
    WORD_S w_sorted[]= {{"marco",90}, {"bike",32}, {"luca",17}, {"gino",8}, {"auto",2}};
    UTILS_insertionSort(w_array,5);
    uint warr_len = sizeof(w_array)/sizeof(WORD_S);
    uint count=0;

    for (count=0; count<warr_len; count++)
    {
        assert(!strcmp(w_array[count].word, w_sorted[count].word)); 
        assert(w_array[count].number==w_sorted[count].number); 
    }

    log_info("PASSED - test_insertion_sort");

    
}
    
void test_swap_words()
{
    char *w1="ciao";
    char *w2="banana";
    uint ref_w1=10;
    uint ref_w2=5;
    DATA d1,d2;

    memset(&d1,0,sizeof(DATA));
    memset(&d2,0,sizeof(DATA));

    UTILS_init_w(&d1, w1,ref_w1);
    UTILS_init_w(&d2, w2,ref_w2);

    UTILS_swap_w(&d1,&d2);

    assert(!strcmp(d1.word,w2));
    assert(!strcmp(d2.word,w1));

    assert(d1.n_occ==ref_w2);
    assert(d2.n_occ==ref_w1);

    UTILS_deallocate_w(&d1);
    UTILS_deallocate_w(&d2);

    log_info("PASSED - test_swap_words");


}

void test_move_words()
{
    char *src_w="piroetta";
    uint ref_src=3;
    DATA src,dst;

    memset(&src,0,sizeof(DATA));
    memset(&dst,0,sizeof(DATA));

    UTILS_init_w(&src, src_w, ref_src);
    UTILS_move_w(&src,&dst);

    assert(!strcmp(src_w,dst.word));
    assert(dst.n_occ==ref_src);

    assert(src.word==NULL);
    assert(src.n_occ==0);

    UTILS_deallocate_w(&dst);

    log_info("PASSED - test_move_words");

}

int main()
{
   test_swap_words();
   test_move_words();
   test_reading_bin_file();
   return 0;
}


