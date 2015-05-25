#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Http.h"

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

bool isHTTPAccessible(HTTP* this) {
	return false;
}

bool onHTTPConnect(HTTP* this) {
	return false;
}

bool onHTTPDisconnect(HTTP* this) {
	return false;
}

void HTTPDownload(HTTP* this, char* url) {

}

void HTTPExcute(HTTP* this, char* res, char* req) {

}
