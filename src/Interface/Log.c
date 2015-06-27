/*
 * Log.c
 *
 *  Created on: Jun 22, 2015
 *      Author: parksanghyun
 */

#include <stdlib.h>
#include <dlog.h>
#include <stdarg.h>
#include "Interface/Log.h"

Log* NewLog() {
	LogExtends* this = (LogExtends*) malloc(sizeof(Log));

	this->log.Info = LogInfo;
	this->log.Debug = LogDebug;
	this->log.Warnnig = LogWarring;
	this->log.Error = LogError;
	this->log.setTagName = setLogTagName;

	this->tag = (char*) malloc(4);
	strcpy(this->tag, "DIT");

	return &this->log;
}

void DestroyLog(Log* this_gen) {
	if (this_gen == NULL) {
		return;
	}

	LogExtends* this = (LogExtends*) this_gen;

	if(this->tag != NULL)
		free(this->tag);

	dlog_print(DLOG_INFO, "DIT", "설마 ?");

	free(this);
}

void setLogTagName(Log* this_gen, char* tagName) {
	LogExtends* this = (LogExtends*) this_gen;
	size_t length = sizeof(tagName);
	free(this->tag);
	this->tag = (char*) malloc(length + 1);
	memcpy(this->tag, tagName, length + 1);
}

void LogInfo(Log* this_gen, char* msg, ...) {
	LogExtends* this = (LogExtends*) this_gen;
	va_list ap;
	va_start(ap, msg);
	dlog_vprint(DLOG_INFO, this->tag, msg, ap);
	va_end(ap);
}

void LogDebug(Log* this_gen, char* msg, ...) {
	LogExtends* this = (LogExtends*) this_gen;
	va_list ap;
	va_start(ap, msg);
	dlog_vprint(DLOG_DEBUG, this->tag, msg, ap);
	va_end(ap);
}

void LogWarring(Log* this_gen, char* msg, ...) {
	LogExtends* this = (LogExtends*) this_gen;
	va_list ap;
	va_start(ap, msg);
	dlog_vprint(DLOG_WARN, this->tag, msg, ap);
	va_end(ap);
}

void LogError(Log* this_gen, char* msg, ...) {
	LogExtends* this = (LogExtends*) this_gen;
	va_list ap;
	va_start(ap, msg);
	dlog_vprint(DLOG_ERROR, this->tag, msg, ap);
	va_end(ap);
}
