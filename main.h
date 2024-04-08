#ifndef BASEALT
#define BASEALT

#include <stdio.h> //valgrind --leak-check=full ./main
#include <string.h> //gcc main.c -lcurl -o main && ./main
#include <stdlib.h>
#include <curl/curl.h> //apt-get install libcurl-devel
#include <json-c/json.h>

typedef struct  {
    char *str;
    size_t size;
} MemoryStruct;

size_t WriteMemoryCallback(void *content, size_t size, size_t nmemb, void *userp);
int get_user_input();
CURLcode get_remote_data(char *url, MemoryStruct *chunk);

#endif