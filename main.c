#include "main.h"

int main() {
    MemoryStruct chunk;

    chunk.str = malloc(1);
    chunk.size = 0;

    get_user_input();
    get_remote_data("https://petstore.swagger.io/v2/store/inventory", &chunk);

    json_object *root = json_tokener_parse(chunk.str);
    printf("\n%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));

    json_object_put(root);
    free(chunk.str);
    curl_global_cleanup();
    return 0;
}

