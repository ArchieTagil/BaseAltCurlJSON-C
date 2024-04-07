#include "main.h"

int main() {
    CURL *curl;
    CURLcode res;

    struct curl_slist *headers = NULL;
    MemoryStruct chunk;

    chunk.str = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL, "https://petstore.swagger.io/v2/store/inventory");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcrp/0.1");

        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }

    json_object *root = json_tokener_parse(chunk.str);
    printf("\n%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));

    json_object_put(root);
    free(chunk.str);
    curl_global_cleanup();
    return 0;
}