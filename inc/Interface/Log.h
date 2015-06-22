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
    void (* Info)(Log* this, char* tag, char* msg, ...);

    void (* Debug)(Log* this, char* tag, char* msg, ...);

    void (* Warnnig)(Log* this, char* tag, char* msg, ...);

    void (* Error)(Log* this, char* tag, char* msg, ...);
};

Log* CreateLog();

void DeleteLog(Log* this_gen);

void LogInfo(Log* this, char* tag, char* msg, ...);

void LogDebug(Log* this, char* tag, char* msg, ...);

void LogWarring(Log* this, char* tag, char* msg, ...);

void LogError(Log* this, char* tag, char* msg, ...);

typedef struct _logExtends {
    Log log;
    char* tag;
} LogExtends;

#ifdef __cplusplus
}
#endif

#endif /* LOG_H_ */
