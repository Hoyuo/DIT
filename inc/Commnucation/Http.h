#ifndef DIT_HTTP_H
#define DIT_HTTP_H

#include <stdbool.h>
#include <stdalign.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _http HTTP;

typedef struct _http {
    bool (* isAccessible)(HTTP* this);

    bool (* onConnect)(HTTP* this, char* url);

    bool (* onDisconnect)(HTTP* this);

    void (* Download)(HTTP* this, char* url);

    void (* Excute)(HTTP* this, char* req, char* res);
} HTTP;

HTTP* newHTTP();

void deleteHTTP(HTTP* this_gen);

bool isHTTPAccessible(HTTP* this);

bool onHTTPConnect(HTTP* this);

bool onHTTPDisconnect(HTTP* this);

void HTTPDownload(HTTP* this, char* url);

void HTTPExcute(HTTP* this, char* res, char* req);

typedef struct {
    HTTP http;
    char* url;
    int urlLength;
} HTTPExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_HTTP_H
