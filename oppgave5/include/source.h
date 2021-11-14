#ifndef _SOURCE_h
#define _SOURCE_h


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <syscall.h>// må aktiveres for feilsøking med syscall
//#include <unistd.h>//for sleeep for feilsøking

//initialize mutexes and conditions
pthread_mutex_t lock_data;
pthread_cond_t write_data;
pthread_cond_t read_data;


//A struct to share the data of input between two threads
typedef struct Buffer{
  char input[11];
}Buffer;


void *workThread(void *structPointer);

#endif