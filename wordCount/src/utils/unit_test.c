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

    while(UTILS_tokenize(fp,word,' ', skip_delimiters, sizeof(skip_delimiters)/sizeof(char)))
    {
        assert(!strcmp(word,ref_words[count]));
        printf("%-10s len: %u\n", word, UTILS_get_word_len(word));
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
    
    
int main()
{
   test_reading_bin_file();
   test_insertion_sort();   
   return 0;
}


