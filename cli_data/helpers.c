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
    buffer->buffer1.str = malloc(1);
    buffer->buffer1.size = 0; 

    buffer->buffer2.str = malloc(1);
    buffer->buffer2.size = 0;
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
    char src[100] = {0};
    if (strcmp(branches->branch1, "empty") !=0 && strcmp(branches->branch2, "empty") != 0) {
        strcpy(src, "https://rdb.altlinux.org/api/export/branch_binary_packages/");
        get_remote_data(strcat(src, branches->branch1), &buffer->buffer1);
        strcpy(src, "https://rdb.altlinux.org/api/export/branch_binary_packages/");
        get_remote_data(strcat(src, branches->branch2), &buffer->buffer2);
    } else {
        printf("at least of branches wasn't set\n");
    }
}

void perform_show_branch_data(int id) {
    data_buffer *buffer = get_data_buffer();
    json_object *obj;
    if (id == 1) obj = json_tokener_parse(buffer->buffer1.str);
    if (id == 2) obj = json_tokener_parse(buffer->buffer2.str);
    
    printf("\n%s\n", json_object_to_json_string_ext(obj, JSON_C_TO_STRING_PRETTY));
    json_object_put(obj);
}

void perform_show_highest_version_release() {

}

void perform_compare(int id) { //1 left; 2 right
    data_buffer *buffer = get_data_buffer();
    json_object *root_obj1;
    json_object *root_obj2;

    root_obj1 = json_tokener_parse(buffer->buffer1.str);
    root_obj2 = json_tokener_parse(buffer->buffer2.str);

    // root_obj1 = json_object_from_file("p9example.json");
    // root_obj2 = json_object_from_file("p10example.json");

    json_object *packages1 = json_object_object_get(root_obj1, "packages");
    json_object *packages2 = json_object_object_get(root_obj2, "packages");

    int arr_len1 = json_object_array_length(packages1);
    int arr_len2 = json_object_array_length(packages2);

    printf("arrlen1 = %d\n", arr_len1);
    printf("arrlen2 = %d\n\n", arr_len2);

    int package_found = 0;
    for (size_t i = 0; i < arr_len1; i++) {
        package_found = 0;
        json_object *tmp_object1 = json_object_array_get_idx(packages1, i);

        const char *name1 = json_object_get_string(json_object_object_get(tmp_object1, "name"));
        const char *arch1 = json_object_get_string(json_object_object_get(tmp_object1, "arch"));
        const char *distag = json_object_get_string(json_object_object_get(tmp_object1, "disttag"));

        for (size_t j = 0; j < arr_len2; j++) {
            json_object *tmp_object2 = json_object_array_get_idx(packages2, j);
            
            const char *name2 = json_object_get_string(json_object_object_get(tmp_object2, "name"));
            const char *arch2 = json_object_get_string(json_object_object_get(tmp_object2, "arch"));

            if (strcmp(name1, name2) == 0 && strcmp(arch1, arch2) == 0) {
                package_found = 1;
                break;
            }
        }

        if (package_found == 0) {
            printf("name: %s\n", name1);
            printf("disttag: %s\n", distag);
            printf("arch: %s\n\n", arch1);
        }
    }
}