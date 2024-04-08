#include "../main.h"

CURLcode get_remote_data(char *url, MemoryStruct *chunk) {
    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)chunk);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcrp/0.1");

        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }
    return res;
}