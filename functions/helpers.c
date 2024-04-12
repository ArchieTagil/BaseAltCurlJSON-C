#include "../main.h"

selected_branches *get_selected_branches() {
    static selected_branches branches;
    return &branches;
}

void selected_branches_init(selected_branches *branches) {
    strcpy(branches->branch1, "empty");
    strcpy(branches->branch2, "empty");
}

data_buffer *get_data_buffer() {
    static data_buffer buffer;
    return &buffer;
}

void data_buffer_init(data_buffer *buffer) {
    for (size_t i = 0; i < 6; i++) {
        buffer->buffer1[i].str = malloc(1);
        buffer->buffer1[i].size = 0; 

        buffer->buffer2[i].str = malloc(1);
        buffer->buffer2[i].size = 0;
    }
    

}

void perform_show_branches() {
    selected_branches *branches = get_selected_branches();
    printf("branch1 = \"%s\"\n", branches->branch1);
    printf("branch2 = \"%s\"\n", branches->branch2);
}

void perform_set_branch(int id, char *argument) {
    if (strcmp(argument, "p10") == 0 || strcmp(argument, "p9") == 0 || strcmp(argument, "sisyphus") == 0) {
        selected_branches *branches = get_selected_branches();
        if (id == 1) strcpy(branches->branch1, argument);
        if (id == 2) strcpy(branches->branch2, argument);
    } else {
        printf("There isn't such branch\n");
    }
}

void perform_get_data() {
    selected_branches *branches = get_selected_branches();
    data_buffer *buffer = get_data_buffer();
    if (strcmp(branches->branch1, "empty") !=0 && strcmp(branches->branch2, "empty") != 0) {
        char src[100] = {0};
        char arch_name[6][8] = {"aarch64", "armh", "i586", "noarch", "ppc64le", "x86_64"};
        for (size_t i = 0; i < 6; i++) {
            strcpy(src, "https://rdb.altlinux.org/api/export/branch_binary_packages/");
            strcat(src, branches->branch1); //add p10, p9, etc to the path
            strcat(src, "?arch=");
            strcat(src, arch_name[i]);
            get_remote_data(src, &buffer->buffer1[i]);
        }
        for (size_t i = 0; i < 6; i++) {
            strcpy(src, "https://rdb.altlinux.org/api/export/branch_binary_packages/");
            strcat(src, branches->branch2); //add p10, p9, etc to the path
            strcat(src, "?arch=");
            strcat(src, arch_name[i]);
            get_remote_data(src, &buffer->buffer2[i]);
        }
    } else {
        printf("at least of branches wasn't set\n");
    }
}

void perform_show_branch_data(int id) {
    data_buffer *buffer = get_data_buffer();
    json_object *obj;
    for (size_t i = 0; i < 6; i++) {
        if (id == 1) obj = json_tokener_parse(buffer->buffer1[i].str);
        if (id == 2) obj = json_tokener_parse(buffer->buffer2[i].str);
    }
    
    
    printf("\n%s\n", json_object_to_json_string_ext(obj, JSON_C_TO_STRING_PRETTY));
    json_object_put(obj);
}

void perform_show_highest_version_release() {
    printf("Didn't implement yet, sorry :'(\n");
}

void perform_compare(int id) { //1 left; 2 right
    data_buffer *buffer = get_data_buffer();
    if (id == 1) perform_compare_logic(buffer->buffer1, buffer->buffer2);
    else perform_compare_logic(buffer->buffer2, buffer->buffer1);
}

void perform_compare_logic(MemoryStruct buffer1[6], MemoryStruct buffer2[6]) {
    json_object *root_obj2[6];
    json_object *result_json = json_object_new_object();

    for (size_t i2 = 0; i2 < 6; i2++) { 
        root_obj2[i2] = json_tokener_parse(buffer2[i2].str);
    }

    for (size_t i = 0; i < 6; i++) { //reduce for faster result
        json_object *root_obj1 = json_tokener_parse(buffer1[i].str);
        json_object *packages1 = json_object_object_get(root_obj1, "packages");

        int arr_len1 = json_object_array_length(packages1);

        for (int j = 0; j < arr_len1; j++) {
            int package_found = 0;
            json_object *tmp_object1 = json_object_array_get_idx(packages1, j);

            const char *name1 = json_object_get_string(json_object_object_get(tmp_object1, "name"));
            const char *arch1 = json_object_get_string(json_object_object_get(tmp_object1, "arch"));

            package_found = is_package_found_in_buffer2(arch1, root_obj2, name1);

            if (package_found == 0) {
                json_object *sub_object = json_object_new_object();
                json_object_object_add(sub_object, "name", json_object_object_get(tmp_object1, "name"));
                json_object_object_add(sub_object, "version", json_object_object_get(tmp_object1, "version"));
                json_object_object_add(sub_object, "arch", json_object_object_get(tmp_object1, "arch"));

                json_object_object_add(result_json, name1, sub_object);
            }
        }
    }
    save_to_file("./result.json", json_object_to_json_string_ext(result_json, JSON_C_TO_STRING_PRETTY));
}

int is_package_found_in_buffer2(const char *arch, json_object *root[6], const char *name1) {
    int buffer2_id = get_buffer2_id(arch);
    int package_found = 0;

    json_object *packages2 = json_object_object_get(root[buffer2_id], "packages");
    int arr_len2 = json_object_array_length(packages2);

    for (int k = 0; k < arr_len2; k++) {
        json_object *tmp_object2 = json_object_array_get_idx(packages2, k);
    
        const char *name2 = json_object_get_string(json_object_object_get(tmp_object2, "name"));
        const char *arch2 = json_object_get_string(json_object_object_get(tmp_object2, "arch"));

        if (strcmp(name1, name2) == 0 && strcmp(arch, arch2) == 0) {
            package_found = 1;
            break;
        }
    }
    return package_found;
}

int get_buffer2_id(const char *arch1) {
    int result = 0;
    if (strcmp(arch1, "aarch64") == 0) result = 0;
    if (strcmp(arch1, "armh") == 0) result = 1;
    if (strcmp(arch1, "i586") == 0) result = 2;
    if (strcmp(arch1, "noarch") == 0) result = 3;
    if (strcmp(arch1, "ppc64le") == 0) result = 4;
    if (strcmp(arch1, "x86_64") == 0) result = 5;
    return result;
}

void save_to_file(char *filename, const char *text) {
    FILE* fptr;
    fptr = fopen(filename, "w");
    fwrite(text,sizeof(char),strlen(text),fptr);
    fclose(fptr);   
}