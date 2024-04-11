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

typedef struct { //something similar to Singleton
    MemoryStruct buffer1[6];
    MemoryStruct buffer2[6];
} data_buffer;

typedef struct { //something similar to Singleton
    char branch1[50];
    char branch2[50];
} selected_branches;

typedef enum {
    AARCH64,
    ARMH,
    I586,
    NOARCH,
    PPC64LE,
    X86_64
} arch_enum;

size_t WriteMemoryCallback(void *content, size_t size, size_t nmemb, void *userp);
selected_branches *get_selected_branches();
void selected_branches_init(selected_branches *branches);
data_buffer *get_data_buffer();
void data_buffer_init(data_buffer *buffer);
void perform_get_data();
void perform_set_branch(int id, char *argument);
void perform_show_branches();
void perform_show_branch_data(int id);
void perform_show_highest_version_release();
void perform_compare(int id);
void get_user_input();
CURLcode get_remote_data(char *url, MemoryStruct *chunk);
int get_buffer2_id(const char *arch1);
int is_package_found_in_buffer2(const char *arch, json_object *root[6], const char *name1);
void save_to_file(char *filename, const char *text);
void perform_compare_logic(MemoryStruct buffer1[6], MemoryStruct buffer2[6]);

#endif