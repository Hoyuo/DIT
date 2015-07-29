/*! @file	Log.h
 *  @brief	Log API 를 사용하기 위해 포함해야 하는 헤더이다.
 *  @note	Log의 Info / Debug / Warning / Error 관련 Log API를 제공한다.
 *  @see	[Tizen Native API](https://developer.tizen.org/development/api-references/native-application?redirect=https%3A//developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/index.html)
 */

#ifndef DIT_LOG_H
#define DIT_LOG_H

#include <stdbool.h>
#include <stdalign.h>

#include <dlog.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Log */
/*!	@def LOGINFO(tag, format, arg...)
 *  @brief 		문자열에 특정 태그를 붙여서 Information log를 발생시킨다.
 *  @param[in] 	tag 발생시키고자 하는 log의 태그 이름
 *  @param[in] 	format 발생시키고자 하는 log의 문자열
 *  @param[in] 	arg 발생시키고자 하는 log의 arguments
 *  @param[out]	null
 *  @note 		문자열에 특정 태그를 붙여서 @c Information log를 발생시킨다. \n
 *  			@a arg는 가변인자이다.
 *  @see 		LOGDEBUG \n
 *  			LOGWARNING \n
 *  			LOGERROR \n
 *  			LOGIF
 */
#define LOGINFO(tag, format, arg...) LOG_(LOG_ID_MAIN, DLOG_INFO, tag, format, ##arg)

/*!	@def LOGDEBUG(tag, format, arg...)
 *  @brief 		문자열에 특정 태그를 붙여서 Debug log를 발생시킨다.
 *  @param[in] 	tag 발생시키고자 하는 log의 태그 이름
 *  @param[in] 	format 발생시키고자 하는 log의 문자열
 *  @param[in] 	arg 발생시키고자 하는 log의 arguments
 *  @param[out]	null
 *  @note 		문자열에 특정 태그를 붙여서 @c Debug log를 발생시킨다. \n
 *  			@a arg 는 가변인자이다.
 *  @see 		LOGINFO \n
 *  			LOGWARNING \n
 *  			LOGERROR \n
 *  			LOGIF
 */
#define LOGDEBUG(tag, format, arg...) LOG_(LOG_ID_MAIN, DLOG_DEBUG, tag, format, ##arg)

/*!	@def LOGWARNING(tag, format, arg...)
 *  @brief 		문자열에 특정 태그를 붙여서 Warning log를 발생시킨다.
 *  @param[in] 	tag 발생시키고자 하는 log의 태그 이름
 *  @param[in] 	format 발생시키고자 하는 log의 문자열
 *  @param[in] 	arg 발생시키고자 하는 log의 arguments
 *  @param[out]	null
 *  @note 		문자열에 특정 태그를 붙여서 @c Warning log를 발생시킨다. \n
 *  			@a arg 는 가변인자이다.
 *  @see 		LOGINFO \n
 *  			LOGDEBUG \n
 *  			LOGERROR \n
 *  			LOGIF
 */
#define LOGWARNING(tag, format, arg...) LOG_(LOG_ID_MAIN, DLOG_WARN, tag, format, ##arg)

/*!	@def LOGERROR(tag, format, arg...)
 *  @brief 		문자열에 특정 태그를 붙여서 Error log를 발생시킨다.
 *  @param[in] 	tag 발생시키고자 하는 log의 태그 이름
 *  @param[in] 	format 발생시키고자 하는 log의 문자열
 *  @param[in] 	arg 발생시키고자 하는 log의 arguments
 *  @param[out]	null
 *  @note 		문자열에 특정 태그를 붙여서 @c Error log를 발생시킨다. \n
 *  			@a arg 는 가변인자이다.
 *  @see 		LOGINFO \n
 *  			LOGDEBUG \n
 *  			LOGWARNING \n
 *  			LOGIF
 */
#define LOGERROR(tag, format, arg...) LOG_(LOG_ID_MAIN, DLOG_ERROR, tag, format, ##arg)

/*!	@def LOGIF(expr, tag, format, arg...)
 *  @brief 		특정한 조건에서 문자열에 해당 태그를 붙여서 Error log를 발생시킨다.
 *  @param[in] 	expr 발생시키고자 하는 log의 발생 조건
 *  @param[in] 	tag 발생시키고자 하는 log의 태그 이름
 *  @param[in] 	format 발생시키고자 하는 log의 문자열
 *  @param[in] 	arg 발생시키고자 하는 log의 arguments
 *  @param[out]	null
 *  @note 		@b 특정한 조건에서 문자열에 해당 태그를 붙여서 @c Error log를 발생시킨다.
 *  			@a arg 는 가변인자이다.
 *  @see 		LOGINFO \n
 *  			LOGDEBUG \n
 *  			LOGWARNING \n
 *  			LOGERROR
 */
#define LOGIF(expr, tag, format, arg...) \
{ \
    if (expr) \
    { \
        LOGERROR(tag, format, ##arg); \
    } \
}
/* Log */

#ifdef __cplusplus
}
#endif

#endif /* LOG_H_ */
