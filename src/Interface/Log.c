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

Log* CreateLog() {
    LogExtends* this = (LogExtends*) malloc(sizeof(Log));

    this->log.Info = LogInfo;
    this->log.Debug = LogDebug;
    this->log.Warnnig = LogWarring;
    this->log.Error = LogError;

    return this;
}

void DeleteLog(Log* this_gen) {
    if (this_gen != NULL) {
        LogExtends* this = (LogExtends*) this_gen;
        free(this);
    }
}

void LogInfo(Log* this, char* tag, char* msg, ...) {
    va_list ap;
    va_start(ap, msg);
    dlog_vprint(DLOG_INFO, tag, msg, ap);
    va_end(ap);
}

void LogDebug(Log* this, char* tag, char* msg, ...) {
    va_list ap;
    va_start(ap, msg);
    dlog_vprint(DLOG_DEBUG, tag, msg, ap);
    va_end(ap);
}

void LogWarring(Log* this, char* tag, char* msg, ...) {
    va_list ap;
    va_start(ap, msg);
    dlog_vprint(DLOG_WARN, tag, msg, ap);
    va_end(ap);
}

void LogError(Log* this, char* tag, char* msg, ...) {
    va_list ap;
    va_start(ap, msg);
    dlog_vprint(DLOG_ERROR, tag, msg, ap);
    va_end(ap);
}
