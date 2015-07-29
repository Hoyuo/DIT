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
 *	@mainpage Do It Tizen for Native API
 *	@brief		간략한 설명
 *	@details	자세한 설명
 *	@section intro Introduction
	Tizen 2.3의 Native Application API는 필요한 정보들이 세분화 분리가 되어있다.
	예를 들어 NFC를 이용하여서 기본적인 데이터를 작성하는 Application을 개발 해야 한다고 가정 하면,
	NFC를 기록하기 위해서는 기본적인 NFC 장비의 유무를 체크하고(Sensor), NFC 장비가 활성화 상태인지 확인하고(System Information),
	NDEF 형태의 데이터 기록을 준비하고(NDEF), NFC를 기록(NFC) 하는 형태로 진행이 된다. 각각의 API가 독립적으로 있기 때문에 개발자는 각 각의 API를 통해서 접근 해야 한다.
	Tizen Application을 개발할 때 한 기능을 구현 하기 위해서는 여러 API를 융합하면서 사용한다.
	따라서 Tizen Application을 개발을 할 때는 기능을 사용하기 위한 API와 기능을 수행하는 데 필요한 역할을 하는 API를 알아야 한다는 부담이 존재한다.
	DIT의 API는 다음과 같이 3개로 구분된 구조를 제공 함으로써 기존에 나눠서 제공 되어있는 API를 묶어서 제공한다.
	또한, Tizen API를 사용하면서 직관적이지 못한 함수명과 함수의 매개변수 전달 시의 복잡한 문제를 해결을 하여 사용하기 쉬운 구조로 변경을 한다.
 *	@section Program 프로그램명??
	 - 프로그램명 : DIT라고 허허...여기 앞을 어떻게 채울지 핵고민중
	 - 프로그램내용 : Tizen Native API easy version
 *	@section CREATEINFO 작성정보
	 - 작성자  : 최똥
	 - 작성일  : 2015-07-24
 *	@date 2015-07-24
 *	@section MODIFYINFO 수정정보
	 - 수정일 / 수정자 : README.md처럼 꾸며야 할듯
	 - 멘붕...

--------------------------------------------------------

*/
