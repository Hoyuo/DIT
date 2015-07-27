# Do It Tizen! (DIT)

## *!!! BEWARE !!!*

> **This Document is *under construction*.**

## Welcome to the DIT GitHuh page.
DIT library is a light-weight library for manipulating Tizen Native API.
Our goal is to make Tizen Native coding simpler, easier, and more fun!
~~`sorry, actually it's not fun...`~~

## DIT Library
### 1. Modulation Rules
* 각 서브 모듈은 파일로 만든다. 하나의 모듈당 하나의 c source file과 head file로 이루어져 있다.
* 파일의 시작부분, 구조체 시작부분, 함수 시작부분에는 주석을 추가한다.

### 2. Doxygen Comment Rules
#### ==FILE==
```
/*!	@file		파일명
 *	@brief		간략한 설명
 *	@note		남기고 싶은 설명
 *	@see		외부URL or Header or soucefile or Function or Struct등을 의미하며 
 *				추가 적으로 현재의 파일과 연관된 것을 명시한다.
 */
```
#### ==STRUCT==
```
/*!	@struct		구조체 이름
 *	@brief		간략한 설명
 *	@note		자세한설명
 *	@see 		외부URL or Header or soucefile or Function or Struct등을 의미하며 
 *				추가 적으로 현재의 구조체와 연관된 것을 명시한다.
 *	@todo 		Tizen의 features나 privileges 를 명시한다.
 */
```

#### ==FUNCTION==
```
/*!	@fn 			함수 이름
 *	@brief 			간략한 설명
 *	@param[in]		인자 입력값
 *	@param[out] 	인자로 출력값을 저장하는 장소
 *	@retval 		반환인자
 *	@note 			자세한 설명
 *	@see 			외부URL or Header or soucefile or Function or Struct등을 의미하며
 *					추가 적으로 현재의 함수와 연관된 것을 명시한다. 관련 API 포함
 *	@remark 		Tizen의 features나 privileges 를 명시한다.
 *	@code			Sample Codes [삭제 할수도...]
 *	@endcode
 */
```

### 3. Working Rules
####Due. 2015-07-29




---