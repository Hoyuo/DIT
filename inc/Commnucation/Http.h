#ifndef DIT_HTTP_H
#define DIT_HTTP_H

#include <stdbool.h>
#include <stdalign.h>
#include <stddef.h>
#include <curl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Http Http;

typedef struct _Http {
	bool (*isAccessible)(Http* this_gen);

	bool (*onConnect)(Http* this_gen, char* url, int port);

	bool (*onDisconnect)(Http* this_gen);

	void (*Download)(Http* this_gen, char* filename);

	void (*Post)(Http* this_gen, char* res, char** req);

	void (*Get)(Http* this_gen, char* res, char** req);

} Http;

/*
 * @privlevel public
 * @privilege %http://tizen.org/privilege/internet
 */
Http* NewHttp();

void DestoryHttp(Http* this_gen);

bool isHttpAccessible(Http* this_gen);

bool onHttpConnect(Http* this_gen, char* url, int port);

bool onHttpDisconnect(Http* this_gen);

void HttpDownload(Http* this_gen, char* filename);

void HttpExcutePost(Http* this_gen, char* req, char** res);

void HttpExcuteGet(Http* this_gen, char* req, char** res);

static size_t write_callback(void* contents, size_t size, size_t nmemb, void** res);

static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);

typedef struct {
	Http http;
	char* url;
	int port;
	bool access;
	bool conect;
} HttpExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_HTTP_H
