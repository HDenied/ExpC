#include<utils.h>


bool UTILS_tokenize(FILE *fp, char *word, char delimiter, char skip_delimiters[], uint skip_counts)
{
    uint ch = 0;
    uint skip_idx=0;
    uint word_idx=0;
    uint idx=0;
    bool skip = false;    while(!feof(fp))
    {
        skip = false;
        ch = fgetc(fp);        if(ch==feof(fp))
        {
            return false;
        }        /*check if to break or skip special characters*/
        for(idx=0; idx<skip_counts;idx++)
        {
            if(ch == skip_delimiters[idx])
            {
                if(word[0]=='\0')
                {
                     skip_idx++;
                     skip = true;
                     break;
                }
                else
                {
                    word[word_idx]='\0';
                    return true;
                }            }
        }        if (!skip)
        {
            if (ch!= delimiter)
            {
                word[word_idx]=ch;
                word_idx++;
                skip_idx++;            }
            else if (ch == delimiter && word[0]=='\0')
            {
                skip_idx++;
            }
            else
            {
                word[word_idx]='\0';
                return true;
            }
        }
    }    return false;
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