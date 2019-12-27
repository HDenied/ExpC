#include<utils.h>
#include<tst.h>
#include<heap.h>

struct _config_s 
{
    char *f_path;
    int num_words;
};

typedef struct _config_s CONFIG_S;

void parse_config(CONFIG_S *conf, uint num_args, char *args[])
{
    FILE *f=NULL;
    uint idx=0;
    
    conf->num_words=-1;

    if(num_args==1)
    {
        printf("At least an argument should be provided, type '-h' for help\n");
        exit(1);
    }

    for(idx=1; idx<num_args; idx++)
    {
        if(!strcmp(args[idx],"-h"))
        {
            printf("\nNAME:\n\twcounter - counts the top N words occurrances in a file\n");
            printf("\nSYNOPSIS:\n\twcounter file_full_path [-n words_number]\n\n");
            exit(0);
        }
    }

    conf->f_path = args[1];
    if(strchr(conf->f_path, '\\') || strchr(conf->f_path,'-'))
    {
        log_err("Not valid linux path: '%s'",conf->f_path);
        exit(1);
    }

    f=fopen(conf->f_path,"rb");
    if(f)
        fclose(f);
    else
    {
        log_err("File '%s' doesn't exist", conf->f_path);
        exit(1);
    }

    idx=2;
    while(idx<num_args)
    {
        if(!strcmp(args[idx],"-n"))
        {
            if (idx+1<num_args)
            {
                sscanf(args[idx+1], "%d", &(conf->num_words));
            }
            else
            {
                log_err("Missing number of top words to display after '-n'");
                exit(1);
            }
            
        }

        idx++;

    }


}

int main(int argc, char *argv[])
{

    FILE *fp;
    CONFIG_S conf;
    TST_TREE *tree=NULL;
    HEAP_TREE *h_tree = NULL;
    WORD_S word_s;
    char word[W_LEN]="\0";    
    DATA tmp_data;
    uint longest_w_size=0;


    parse_config(&conf, argc, argv);

    fp = fopen(conf.f_path, "rb");

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
    if(conf.num_words>=0)
        HEAP_print_tree(h_tree, conf.num_words);
    else
        HEAP_print_tree(h_tree, HEAP_get_num_w(h_tree));
    
    HEAP_erase(&h_tree);

    return 0;
}