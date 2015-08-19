[![Start Video](https://cloud.githubusercontent.com/assets/8381373/8979980/6a5e1bac-36e8-11e5-8604-1c2b63b64f0a.png)](https://www.youtube.com/embed/ZlEkwy6Rhfw)

## The Easiest Tizen Native Library: *Do It Tizen! (D.I.T.)*
### Welcome to the *D.I.T.* GitHub page.
D.I.T. library is a light-weight library for manipulating Tizen Native API. Our goal is to make Tizen Native coding simpler, easier, and more fun!  

![DIT](https://cloud.githubusercontent.com/assets/8381373/8978836/b61dad1c-36e0-11e5-9ef4-593ffdba8ed3.png)

## Why use this library?
1. We're **not used to** developing Tizen Native.
2. We need more easier Tizen Native Library.
3. D.I.T. library is easy, great and efficient library.
4. D.I.T. library makes Tizen seems like Android.
5. D.I.T. is heavily customizable.
	* If you want to edit D.I.T. for your taste, **[please follow D.I.T. Library Rules](https://github.com/Hoyuo/DIT#dit-library-rules)**

**[More ›][2]**


## How to use this library?
1. Download Tizen IDE and Tizen SDK. You can download.   
 	**[› Here](https://developer.tizen.org/development/tools/download)**
2. You can download release version.  
	**[› D.I.T. release version][4]**
3. D.I.T. Book will help you !    
	**[› D.I.T. Book][6]**


## D.I.T. Library Rules
### 1. Modulation Rules
* Each of files contain their own sub modules. 
* A module is composed of one c file and header file.
* The comments should be the top of each FILE, STRUCTURE and FUNCTION.

### 2. Doxygen Comment Rules
#### FILE
```
/*!	@file			파일 이름 (확장자까지 표기)
 *	@brief			간략한 설명
 *	@note			자세한 설명 및 주의 사항
 *	@see			참고 사항 및 현재 파일과 연관된 사항
 *					( URL / Header / Soucefile / Function / Struct 등 
 */
```
#### STRUCT
```
/*!	@struct			구조체 이름
 *	@brief			간략한 설명
 *	@note			자세한 설명 및 주의 사항
 *	@see 			참고 사항 및 현재 구조체와 연관된 사항
 *					( URL / Header / Soucefile / Function / Struct 등 )
 *	@pre			Tizen의 features나 privileges 를 명시
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
 *	@see			참고 사항 및 현재 구조체와 연관된 사항
 *					( URL / Header / Soucefile / Function / Struct 등 )
 *					주로 같은 모듈 내부의 연관 함수들을 기재한다.
 *	@pre			Tizen의 features나 privileges 를 명시
 *	@warning		함수 사용시 중요한 주의 사항을 명시
 */
```
	
## More Informarion
GitHub ›[![GitHub](https://cloud.githubusercontent.com/assets/8381373/8948058/b7450220-35dd-11e5-97ac-b8b827d07b80.png)][1]
GitBook ›[![GitBook](https://cloud.githubusercontent.com/assets/8381373/8948068/de7c08b6-35dd-11e5-9b5e-714191b32406.png)][2]
Reference ›[![Documents](https://cloud.githubusercontent.com/assets/8381373/8948073/ec4f6910-35dd-11e5-9fee-89f241f38520.PNG)][3]
Release ›[![Release](https://cloud.githubusercontent.com/assets/8381373/8948079/f864c2e0-35dd-11e5-9b5a-1fdcd9cd00d7.png)][4]

##Click here to help out
Donation ›[![Donation](https://cloud.githubusercontent.com/assets/8381373/8948083/058d7750-35de-11e5-9674-cd5e568847e7.PNG)][5]


<br><br><br><br><br><br><br>

##Tizen Developer Guide for beginners
**[Click ›](http://hoyuo.gitbooks.io/tizen)**


 [1]: https://github.com/Hoyuo/DIT
 [2]: https://www.gitbook.com/book/hoyuo/tizen-d-i-t/details
 [3]: http://dee-j.github.io/html/index.html
 [4]: https://github.com/Hoyuo/DIT/releases/tag/1.0
 [5]: https://gumroad.com/l/gitbook_55b5a748e3411810000a9b5d?wanted=true
 [6]: http://hoyuo.gitbooks.io/tizen-d-i-t/content/use.html
 [7]: #
 [8]: #
 [9]: #
 [10]: #