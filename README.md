link of DIT video in embed style and 1280x720 resolution image file

[![Start Video](http://images.technewstoday.com.s3.amazonaws.com/tnt/the-new-samsung-z3-is-hitting-the-market-soon-after-the-surprising-success.jpg)](https://www.youtube.com/embed/MBfxQIz80Jk)

## The Easiest Tizen Native Library: *Do It Tizen! (D.I.T.)*
### Welcome to the *D.I.T.* GitHub page.
D.I.T. library is a light-weight library for manipulating Tizen Native API. Our goal is to make Tizen Native coding simpler, easier, and more fun!  

## Why use this library?
1. We're **not used to** developing Tizen Native.
2. We need more easier Tizen Native Library.
3. ~~Some of sample codes of Tizen Native in 'tizen.org' is not working.~~
4. D.I.T. library makes Tizen seems like Android.
5. D.I.T. is heavily customizable.
	* If you want to edit D.I.T. for your taste, **please follow D.I.T. Library Rules**

**[More ›][2]**


## How to use this library?
1. Download Tizen IDE and Tizen SDK. You can download [here](https://developer.tizen.org/development/tools/download).
2. You can download release version of **[D.I.T.][4]**
3. 파일 옮기기 뭐 그런거 설명충 등장


## D.I.T. Library Rules
### 1. Modulation Rules
* Each of files contain their own sub modules. 
* A module is composed of one c file and header file.
* The start and end of the file파일의 시작부분, 구조체 시작부분, 함수 시작부분에는 주석을 추가한다.

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
/*!	@struct			구조체 이름
 *	@brief			간략한 설명
 *	@note			자세한 설명 및 주의 사항
 *	@see 			참고 사항 및 현재 구조체와 연관된 사항들 
 *					( URL / Header / Soucefile / Function / Struct 등 )
 *	@todo			Tizen의 features나 privileges 를 명시한다.
 */
```

#### FUNCTION
```
/*!	@fn				함수 이름
 *	@brief			간략한 설명
 *	@param[in]		인자 입력 값
 *	@param[out]		인자로 출력 값을 저장하는 장소
 *	@retval			반환 인자 타입 및 간략한 설명
 *	@note			자세한 설명 및 주의 사항
 *	@see			참고 사항 및 현재 구조체와 연관된 사항들 
 *					( URL / Header / Soucefile / Function / Struct 등 )
 *					주로 같은 모듈 내부의 연관 함수들을 기재한다.
 *	@remark			Tizen의 features나 privileges 를 명시한다. 
 */
```

### 3. Working Rules
####Due. 2015-07-29
[GitHub : Source][1]  
[GitBook : Manual][2]  
[Documents : Reference API][3]  
[Release Version][4]  
[Donation : You can help me][5]
	
##More Informarion
[![GitHub](https://cloud.githubusercontent.com/assets/8381373/8947623/0d663904-35d8-11e5-8d77-31083477c045.png)][1]
[![GitBook](https://cloud.githubusercontent.com/assets/8381373/8947741/94cca5b2-35d9-11e5-84c2-49d1f105fcd3.png)][2]
[![Documents](https://cloud.githubusercontent.com/assets/8381373/8947703/15c25ee2-35d9-11e5-90d4-0081ec9f6888.PNG)][3]
[![Release](https://cloud.githubusercontent.com/assets/8381373/8947929/15cbddde-35dc-11e5-8dbc-96b86b656724.png)][4]
[![Donation](https://cloud.githubusercontent.com/assets/8381373/8947648/605d4756-35d8-11e5-8c24-0c2992c1c42e.PNG)][5]



 [1]: https://github.com/Hoyuo/DIT
 [2]: https://www.gitbook.com/book/hoyuo/tizen-d-i-t/details
 [3]: https://www.naver.com
 [4]: https://github.com/Hoyuo/DIT/releases
 [5]: https://gumroad.com/l/gitbook_55b5a748e3411810000a9b5d?wanted=true
 [6]: #
 [7]: #
 [8]: #
 [9]: #
 [10]: #