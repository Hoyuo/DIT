#include "Commnucation/Http.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <curl.h>

Http* NewHttp() {
	HttpExtends* this = (HttpExtends*) malloc(sizeof(HttpExtends));

	this->http.isAccessible = isHttpAccessible;
	this->http.onConnect = onHttpConnect;
	this->http.onDisconnect = onHttpDisconnect;
	this->http.Download = HttpDownload;
	this->http.Get = HttpExcuteGet;
	this->http.Post = HttpExcutePost;

	this->url = NULL;

	return &this->http;
}

void DestoryHttp(Http* this_gen) {
	if (this_gen != NULL) {
		HttpExtends* this = (HttpExtends*) this_gen;

		if (this->url != NULL)
			free(this->url);

		free(this);
	}
}

bool isHttpAccessible(Http* this_gen) {

}

bool onHttpConnect(Http* this_gen, char* url) {
	HttpExtends* this = (HttpExtends*) this_gen;

	int lenght = strlen(url);
	this->url = (char *) malloc(lenght + 1);
	strcpy(this->url, url);

	return true;
}

bool onHttpDisconnect(Http* this_gen) {
	HttpExtends* this = (HttpExtends*) this_gen;

	if (this->url != NULL) {
		free(this->url);
		this->url = NULL;
	}

	return true;
}

void HttpDownload(Http* this_gen, char* url) {

}

void HttpExcutePost(Http* this_gen, char* req, char* res) {
	HttpExtends* this = (HttpExtends*) this_gen;
	if (this->url != NULL) {
		CURL* curl;
		CURLcode r;

		curl_global_init(CURL_GLOBAL_ALL);

		curl = curl_easy_init();
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, this->url);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long ) strlen(req));
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, req);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);
			r = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
		}
		curl_global_cleanup();
	}
}

void HttpExcuteGet(Http* this_gen, char* req, char* res) {
	HttpExtends* this = (HttpExtends*) this_gen;
	if (this->url != NULL) {
		CURL* curl;
		CURLcode r;

		curl_global_init(CURL_GLOBAL_ALL);

		curl = curl_easy_init();
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, this->url);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);
			r = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
		}
		curl_global_cleanup();
	}
}

static size_t write_callback(void* contents, size_t size, size_t nmemb,
		void** res) {
	size_t realsize = size * nmemb;
	*res = (char*) malloc(realsize + 1);
	memcpy(*res, contents, realsize);
	return realsize;
}
