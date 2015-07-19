#ifndef DIT_HTTP_H
#define DIT_HTTP_H

#include <stdbool.h>
#include <stdalign.h>
#include <stddef.h>

#include "dit.h"

#include <curl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Http * Http;

struct _Http
{
    bool (* isAccessible) (Http this_gen);

    bool (* onConnect) (Http this_gen, String url, int port);

    bool (* onDisconnect) (Http this_gen);

    void (* Download) (Http this_gen, String filename);

    void (* Post) (Http this_gen, String res, String * req);

    void (* Get) (Http this_gen, String res, String * req);

};

/*
 * @privlevel public
 * @privilege %http://tizen.org/privilege/internet
 */
Http NewHttp (void);
void DestoryHttp (Http this_gen);
bool isHttpAccessible (Http this_gen);
bool onHttpConnect (Http this_gen, String url, int port);
bool onHttpDisconnect (Http this_gen);
void HttpDownload (Http this_gen, String filename);
void HttpExcutePost (Http this_gen, String req, String * res);
void HttpExcuteGet (Http this_gen, String req, String * res);

static size_t write_callback (void * contents, size_t size, size_t nmemb, void ** res);
static size_t write_data (void * ptr, size_t size, size_t nmemb, FILE * stream);

const char * HttpErrorCheck (CURLcode errorCode);

typedef struct
{
    struct _Http http;
    String       url;
    int          port;
    bool         access;
    bool         conect;

} HttpExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_HTTP_H
