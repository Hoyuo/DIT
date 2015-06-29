#include "Commnucation/Http.h"
#include <stdbool.h>
#include <stdlib.h>
#include <curl.h>

/*
 * @privlevel public
 * @privilege %http://tizen.org/privilege/internet
 */

HTTP* newHTTP() {
    HTTPExtends* this;

    this = (HTTPExtends*) malloc(sizeof(HTTPExtends));

    this->http.isAccessible = isHTTPAccessible;
    this->http.onConnect = onHTTPConnect;
    this->http.onDisconnect = onHTTPDisconnect;
    this->http.Download = HTTPDownload;
    this->http.Excute = HTTPExcute;

    return &this->http;
}

void deleteHTTP(HTTP* this_gen) {
    if (this_gen != NULL) {
        HTTPExtends* this = (HTTPExtends*) this_gen;
        free(this);
    }
}

bool isHTTPAccessible(HTTP* this_gen) {

    return false;
}

bool onHTTPConnect(HTTP* this_gen) {
    HTTPExtends* this = (HTTPExtends*) this_gen;
    CURL* curl;
    CURLcode res;

    FILE* file;
    file = fopen("test.html", "w");

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://210.118.74.89:3000");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }

    fclose(file);

    return false;
}

bool onHTTPDisconnect(HTTP* this_gen) {
    return false;
}

void HTTPDownload(HTTP* this_gen, char* url) {

}

void HTTPExcute(HTTP* this_gen, char* res, char* req) {

}
