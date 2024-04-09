#ifndef BASEALT
#define BASEALT

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <json-c/json.h>

typedef struct {
    char *str;
    size_t size;
} MemoryStruct;

typedef struct { //Singleton
    char branch1[50];
    char branch2[50];
} selected_branches;

size_t WriteMemoryCallback(void *content, size_t size, size_t nmemb, void *userp);
selected_branches *get_selected_branches();
void selected_branches_init(selected_branches *branches);
void perform_get_data();
void perform_set_branch(int id, char *argument);
void perform_show_branches();
void perform_show_branch_data(int id);
void perform_show_highest_version_release();
void perform_compare(int id);
int get_user_input();
CURLcode get_remote_data(char *url, MemoryStruct *chunk);

#endif