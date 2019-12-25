#include<utils.h>


uint UTILS_get_word_len(const char *word)
{
    uint len = 0;
    while(*(word+len))
        len++;
    return len;
}

void UTILS_init_w(DATA *data, const char *word, uint n_occ)
{
    uint w_len = UTILS_get_word_len(word);
    data->word=calloc(w_len+1,sizeof(char));
    memcpy(data->word, word, w_len);
    data->word[w_len]='\0';
    data->n_occ=n_occ;
}
void UTILS_deallocate_w(DATA *data)
{
    if (data->word)
    {
        free(data->word);
        data->word=NULL;
        data->n_occ=0;
    }
}
void UTILS_swap_w(DATA *d1, DATA *d2)
{
    char *tmp_word=NULL;
    uint tmp_occ= 0;

    if (d1 && d2)
    {
        tmp_word=d1->word;
        tmp_occ=d1->n_occ;
        d1->word=d2->word;
        d1->n_occ=d2->n_occ;
        d2->word=tmp_word;
        d2->n_occ=tmp_occ;
    }
    else
    {
        log_err("Can't swap not existent data");
        assert(false);
    }
    
}

void UTILS_move_w(DATA *src, DATA *dst)
{
    if(src && dst)
    {
        dst->word=src->word;
        dst->n_occ=src->n_occ;
        src->word=NULL;
        src->n_occ=0;
    }
    else
    {
        log_err("Can't move not existent data");
        assert(false);
    }
    
}

bool UTILS_tokenize(FILE *fp, char *word)
{
      uint ch = 0;
      uint word_idx=0;
      uint idx=0;
      
      while(!feof(fp))
      {
          ch = fgetc(fp);

          if(ch >= 'a' && ch <= 'z')
          {
              word[word_idx]=ch;
              word_idx++;
          }
          else if (ch >= 'A' && ch <= 'Z')
          {
              ch+=32;
              word[word_idx]=ch;
              word_idx++;
          }
          else if (word[0]!='\0')
          {
              word[word_idx]='\0';
              return true;
          }

      }

      return false;

}

void UTILS_insertionSort(WORD_S *w_array, uint a_size)
{
    int idx=0, prev_idx=0;
    uint key=0;
    WORD_S ref_word;    
    
    for (idx = 1; idx < a_size; idx++)
    {
        key = w_array[idx].number;
        memcpy(&ref_word, &w_array[idx], sizeof(WORD_S));
        prev_idx = idx - 1;       

        while (prev_idx>=0 && w_array[prev_idx].number < key)
        {
            memcpy(&w_array[prev_idx + 1] , &w_array[prev_idx], sizeof(WORD_S));
            prev_idx--;
        }

        memcpy(&w_array[prev_idx + 1], &ref_word, sizeof(WORD_S));
    }
}