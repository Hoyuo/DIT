#ifndef DIT_HTTP_H
#define DIT_HTTP_H

#include <stdbool.h>
#include <stdalign.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Http Http;

typedef struct _Http {
	bool (*isAccessible)(Http* this_gen);

	bool (*onConnect)(Http* this_gen, char* url);

	bool (*onDisconnect)(Http* this_gen);

	void (*Download)(Http* this_gen, char* url);

	void (*Post)(Http* this_gen, char* res, char* req);

	void (*Get)(Http* this_gen, char* res, char* req);

} Http;

/*
 * @privlevel public
 * @privilege %http://tizen.org/privilege/internet
 */
Http* NewHttp();

void DestoryHttp(Http* this_gen);

bool isHttpAccessible(Http* this_gen);

bool onHttpConnect(Http* this_gen, char* url);

bool onHttpDisconnect(Http* this_gen);

void HttpDownload(Http* this_gen, char* url);

void HttpExcutePost(Http* this_gen, char* req, char* res);

void HttpExcuteGet(Http* this_gen, char* req, char* res);

static size_t write_callback(void* contents, size_t size, size_t nmemb, void** res);

typedef struct {
	Http http;
	char* url;
} HttpExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_HTTP_H
