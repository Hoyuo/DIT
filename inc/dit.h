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


/*!
 *	@mainpage 'Do It Tizen!' library for Native API
 *	@brief
 *	@b 'D.I.T.' API is carefully selected and tightly managed APIs from the Tizen native systems. The @b 'D.I.T.' API Specification available in the Tizen Native SDK shows full list of the selected native subsystem APIs. \n
 * 	The @b 'D.I.T.' API is divided into dozens of API modules; each module represents a logically similar set of submodule APIs, which can be grouped into the same category.\n


 *	@section intro Required Header
	To be able to use an API, you need to include a header in which API is defined. You can find required headers in API reference as illustrated below: \n
	![required_header.png](https://cloud.githubusercontent.com/assets/8381373/8975996/6a8ddde6-36c1-11e5-9e63-e92d730b3dcd.png) \n

 *	@section feature Feature
 	Some of the @b 'D.I.T.' APIs require features to prevent your application from being shown in the application list on the Tizen store. \n
 	If related Feature is included in API reference as shown below and your application uses that feature, then you need to declare the feature in the tizen-manifest.xml file. \n
	![feature.png](https://cloud.githubusercontent.com/assets/8381373/8976000/78a64d28-36c1-11e5-89c6-5eeb529b136d.png) \n

 *	@section privilege Privilege
 	The privilege is essential part to get access grant for privacy related data or sensitive system resources. \n
	Some of the @b 'D.I.T.' API API functions require adding appropriate privileges to the tizen-manifest.xml file. \n
	If required privileges are not included in the tizen-manifest.xml file, then the function will return @a PERMISSION_DENIED error. \n
	For example, see the "Privilege:" section in the following picture: \n
	![privilege.png](https://cloud.githubusercontent.com/assets/8381373/8976001/837ce3ce-36c1-11e5-8c79-e5b3e150b54d.png) \n

 *	@section structure Structure of Function Descriptions
 	In the function documentation for each module, the functions are described using a unified structure, illustrated in the below example. \n
 	![structure.png](https://cloud.githubusercontent.com/assets/8381373/8976002/8b17d120-36c1-11e5-9f8d-2519aef52b37.png) \n
*/
