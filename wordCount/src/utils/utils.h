#ifndef UTILS_H
#define UTILS_H

#include<common.h>


bool UTILS_tokenize(FILE *fp, char *word);

void UTILS_insertionSort(WORD_S *w_array, uint a_size);

uint UTILS_get_word_len(const char *word);


#endif