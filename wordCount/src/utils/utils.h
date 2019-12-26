#ifndef UTILS_H
#define UTILS_H

#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<string.h>

#define uint unsigned int
#define W_LEN 256


#define log_info(M, ...) while(true){ \
    fprintf(stdout, "[INF] %s:%d: " M "\n",\
        __FILE__, __LINE__, ##__VA_ARGS__); \
    break; \
}

#define log_err(M, ...) while(true){ \
    fprintf(stdout, "[ERR] %s:%d: " M "\n",\
        __FILE__, __LINE__, ##__VA_ARGS__);\
    break; \
}

#ifdef DEBUG 

    #define log_dbg(M, ...) fprintf(stdout, "[DBG] %s:%d: " M "\n",\
            __FILE__, __LINE__, ##__VA_ARGS__);
#else
    #define log_dbg(M, ...)
#endif


struct word_s {
    char word[W_LEN];
    uint number;
};

typedef struct word_s WORD_S;


struct data_s{

    char *word;
    uint n_occ;

};

typedef struct data_s DATA;

void UTILS_init_w(DATA *data, const char *word, uint n_occ);
void UTILS_deallocate_w(DATA *data);
void UTILS_swap_w(DATA *d1, DATA *d2);
void UTILS_move_w(DATA *src, DATA *dst);
bool UTILS_is_valid(DATA *d);

bool UTILS_tokenize(FILE *fp, char *word);

void UTILS_insertionSort(WORD_S *w_array, uint a_size);

uint UTILS_get_word_len(const char *word);


#endif