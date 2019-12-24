#include<utils.h>


uint UTILS_get_word_len(const char *word)
{
    uint len = 0;
    while(*(word+len))
        len++;
    return len;
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