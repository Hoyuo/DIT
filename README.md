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
#### FILE
```
/*!	@file		파일 이름 (확장자까지 표기)
 *	@brief		간략한 설명
 *	@note		자세한 설명 및 주의 사항
 *	@see		참고 사항 및 현재 파일과 연관된 사항들 
 *				( URL / Header / Soucefile / Function / Struct 등 
 */
```
#### STRUCT
```
/*!	@struct		구조체 이름
 *	@brief		간략한 설명
 *	@note		자세한 설명 및 주의 사항
 *	@see 		참고 사항 및 현재 구조체와 연관된 사항들 
 *				( URL / Header / Soucefile / Function / Struct 등 )
 *	@todo 		Tizen의 features나 privileges 를 명시한다.
 */
```

#### FUNCTION
```
/*!	@fn 			함수 이름
 *	@brief 			간략한 설명
 *	@param[in]		인자 입력 값
 *	@param[out] 	인자로 출력 값을 저장하는 장소
 *	@retval 		반환 인자 타입 및 간략한 설명
 *	@note 			자세한 설명 및 주의 사항
 *	@see 			참고 사항 및 현재 구조체와 연관된 사항들 
 *					( URL / Header / Soucefile / Function / Struct 등 )
 *					주로 같은 모듈 내부의 연관 함수들을 기재한다.
 *	@remark 		Tizen의 features나 privileges 를 명시한다. 
 */
```

### 3. Working Rules
####Due. 2015-07-29




---