#include "main.h"

size_t WriteMemoryCallback(void *content, size_t size, size_t nmemb, void *userp) {
    size_t real_size = size * nmemb;
    MemoryStruct *mem = (MemoryStruct *) userp;

    char *ptr = realloc(mem->str, mem->size + real_size + 1);

    if (!ptr) {
        return 0;
    }

    mem->str = ptr;
    memcpy(&(mem->str[mem->size]), content, real_size);
    mem->size += real_size;
    mem->str[mem->size] = 0;
    return real_size;
}