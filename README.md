# Do It Tizen! (D.I.T.)
---
link of DIT video ()

[![Start Video](https:/github.com/Phlow/feeling-responsive/blob/gh-pages/images/video-feeling-responsive-1280x720.jpg)](https://www.youtube.com/embed/3b5zCFSmVvU)

## *!!! BEWARE !!!*

> **This Document is *under construction*.**

## Welcome to the DIT GitHub page.
DIT library is a light-weight library for manipulating Tizen Native API.
Our goal is to make Tizen Native coding simpler, easier, and more fun!
~~sorry, actually it's not fun...~~

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


	깃북 : https://www.gitbook.com/book/hoyuo/tizen-d-i-t/details
	깃헙 : https://github.com/Hoyuo/DIT
	레퍼런스 : https://
	릴리스 : https://github.com/Hoyuo/DIT/releases
	기부 : https://gumroad.com/l/gitbook_55b5a748e3411810000a9b5d?wanted=true
	

테스트
![](https://cloud.githubusercontent.com/assets/8381373/8943209/a90dfaf0-35b4-11e5-9ed5-55db28e22f9d.png)