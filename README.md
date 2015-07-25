# DIT
Tizen Native API Project

# DIT Library
## 1. 모듈화 규칙
* 각 서브 모듈은 파일로 만든다. 하나의 모듈당 하나의 c source file과 head file로 이루어져 있다.
* 파일의 시작부분, 구조체 시작부분, 함수 시작부분에는 주석을 추가한다.

```
파일 주석
/*!	@file		파일명
 *	@brief		간략한 설명
 *	@note		남기고 싶은 설명
 *	@see		외부URL or Header or soucefile or Function or Struct등을 의미하며 추가 적으로 현재의 파일과 연관된 것을 명시한다.
*/

구조체 주석
/*!	@struct		구조체 이름
 *	@brief		간략한 설명
 *	@note		자세한설명
 *	@see 		외부URL or Header or soucefile or Function or Struct등을 의미하며 추가 적으로 현재의 구조체와 연관된 것을 명시한다.
 *	@todo 		Tizen의 features나 privileges 를 명시한다.
*/

함수 주석
/*!	@fn 			함수 이름
 *	@brief 			간략한 설명
 *	@param[in]		인자 입력값
 *	@param[out] 	인자로 출력값을 저장하는 장소
 *	@retval 		반환인자
 *	@note 			자세한 설명
 *	@see 			외부URL or Header or soucefile or Function or Struct등을 의미하며 추가 적으로 현재의 함수와 연관된 것을 명시한다. 관련 API 포함
 *	@remark 		Tizen의 features나 privileges 를 명시한다.
 *	@code			Sample Codes
 *	@endcode
*/
```


