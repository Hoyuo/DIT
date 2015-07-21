#ifndef DIT_LOG_H
#define DIT_LOG_H

#include <stdbool.h>
#include <stdalign.h>

#include <dlog.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LOGINFO(tag, format, arg...) LOG_(LOG_ID_MAIN, DLOG_INFO, tag, format, ##arg)

#define LOGDEBUG(tag, format, arg...) LOG_(LOG_ID_MAIN, DLOG_DEBUG, tag, format, ##arg)

#define LOGWARNING(tag, format, arg...) LOG_(LOG_ID_MAIN, DLOG_WARN, tag, format, ##arg)

#define LOGERROR(tag, format, arg...) LOG_(LOG_ID_MAIN, DLOG_ERROR, tag, format, ##arg)

#define LOGIF(expr, tag, fmt, arg...) \
{ \
    if (expr) \
    { \
    	LOGERROR(tag, fmt, ##arg); \
        return; \
    } \
}

#ifdef __cplusplus
}
#endif

#endif /* LOG_H_ */

