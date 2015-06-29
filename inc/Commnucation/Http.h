#ifndef DIT_HTTP_H
#define DIT_HTTP_H

#include <stdbool.h>
#include <stdalign.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _http HTTP;

typedef struct _http {
    bool (* isAccessible)(HTTP* this_gen);

    bool (* onConnect)(HTTP* this_gen, char* url);

    bool (* onDisconnect)(HTTP* this_gen);

    void (* Download)(HTTP* this_gen, char* url);

    void (* Excute)(HTTP* this_gen, char* req, char* res);
} HTTP;

HTTP* newHTTP();

void deleteHTTP(HTTP* this_gen);

bool isHTTPAccessible(HTTP* this_gen);

bool onHTTPConnect(HTTP* this_gen);

bool onHTTPDisconnect(HTTP* this_gen);

void HTTPDownload(HTTP* this_gen, char* url);

void HTTPExcute(HTTP* this_gen, char* res, char* req);

typedef struct {
    HTTP http;
    char* url;
    int urlLength;
} HTTPExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_HTTP_H
