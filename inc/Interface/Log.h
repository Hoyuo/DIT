/*
 * Log.h
 *
 *  Created on: Jun 22, 2015
 *      Author: parksanghyun
 */

#ifndef DIT_LOG_H
#define DIT_LOG_H

#include <stdbool.h>
#include <stdalign.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _log Log;
typedef struct _log {
    void (* Info)(Log* this_gen, char* msg, ...);

    void (* Debug)(Log* this_gen, char* msg, ...);

    void (* Warnnig)(Log* this_gen, char* msg, ...);

    void (* Error)(Log* this_gen, char* msg, ...);
};

Log* NewLog();

void DestroyLog(Log* this_gen);

void setTagName(Log* this_gen, char* tagName);

void LogInfo(Log* this_gen, char* msg, ...);

void LogDebug(Log* this_gen, char* msg, ...);

void LogWarring(Log* this_gen, char* msg, ...);

void LogError(Log* this_gen, char* msg, ...);

typedef struct _logExtends {
    Log log;
    char* tag;
} LogExtends;

#ifdef __cplusplus
}
#endif

#endif /* LOG_H_ */
