#ifndef COMMON_H
#define COMMON_H

#include<stdbool.h>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#include<string.h>



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



#define uint unsigned int
#define W_LEN 256


struct word_s {
    char word[W_LEN];
    uint number;
};

typedef struct word_s WORD_S;

#endif