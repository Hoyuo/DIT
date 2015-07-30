/*!
 *	@file DIT.h
 *	@brief DIT Library를 통합 관리한다.
 *	@note TIZEN API를 새롭게 Wrapping 하여서 Library형식으로 제공한다.
 *	@see https://developer.tizen.org/dev-guide/2.3.0
 */

#ifndef DIT_H
#define DIT_H

#define DOWNLOADSFOLDERPATH "/opt/usr/media/Downloads"

#include <stdbool.h>
#include <stdalign.h>
#include <tizen.h>

typedef char * String;

#ifndef EXPORT_API
#define EXPORT_API __attribute__((__visibility__("default")))
#endif

#endif //DIT_H
