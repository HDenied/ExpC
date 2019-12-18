#ifndef UTILS_H
#define UTILS_H

#include<common.h>


bool UTILS_tokenize(FILE *fp, char *word, char delimiter, char skip_delimiters[], uint num_del);

void UTILS_insertionSort(WORD_S *w_array, uint a_size);


#endif