#include "main.h"

int main() {
    MemoryStruct chunk;
    chunk.str = malloc(1);
    chunk.size = 0;

    selected_branches *branches = get_selected_branches();
    selected_branches_init(branches);

    int branch_id = get_user_input();
    // switch (branch_id) {
    // case 1:
    //     get_remote_data("https://rdb.altlinux.org/api/export/branch_binary_packages/sisyphus", &chunk);
    //     break;
    // case 2:
    //     get_remote_data("https://rdb.altlinux.org/api/export/branch_binary_packages/p10", &chunk);
    //     break;
    // default:
    //     return 1;
    // }

    // json_object *root = json_tokener_parse(chunk.str);
    // printf("\n%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));
    // json_object_put(root);

    free(chunk.str);
    return 0;
}

