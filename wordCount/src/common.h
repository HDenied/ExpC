#ifndef COMMON_H
#define COMMON_H

#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<string.h>



#define log_info(M, ...) fprintf(stdout, "[INF] %s:%d: " M "\n",\
        __FILE__, __LINE__, ##__VA_ARGS__)

#define log_err(M, ...) fprintf(stdout, "[ERR] %s:%d: " M "\n",\
        __FILE__, __LINE__, ##__VA_ARGS__)


#define uint unsigned int
#define W_LEN 512


struct word_s {
    char word[W_LEN];
    uint number;
    bool is_finished;
};

typedef struct word_s WORD_S;

#endif