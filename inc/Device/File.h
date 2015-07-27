/*! @file	File.h
 *  @brief	File API 를 사용하기 위해 포함해야 하는 헤더이다.
 *  @note	File의 File / Video / Audio / Image 관련 API를 제공한다.
 *  @see	https://developer.tizen.org/development/api-references/native-application?redirect=https%3A//developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/index.html
 */

#ifndef _FILE_H
#define _FILE_H

#include <stdbool.h>
#include <stdalign.h>

#include "dit.h"

#include <player.h>
#include <metadata_extractor.h>
#include <media_content.h>
#include <media_info.h>
#include <Evas.h>
#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif


/* File */
/*! @struct	_File
 *  @brief	File 모듈에 대한 구조체이다. File 모듈은 다양한 방식으로 파일을 제어 할 수 있다.
 *  @note	File의 File 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewFile() 함수를 사용해야 하며 사용이 끝났을 때 DestroyFile() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__STORAGE__MODULE.html
 *  @todo	privilege에 "http://tizen.org/privilege/mediastorage" 을 반드시 추가해야 한다. \n
 *  		privilege에 "http://tizen.org/privilege/externalstorage" 을 반드시 추가해야 한다.
 */
typedef struct _File * File;
struct _File
{

    void (* Delete) (String src);

    void (* Copy) (String src, String dst);

    void (* Move) (String src, String dst);

    GList * (* Search) (String src, String dst);

    void (* deleteSearchedList) (GList * searchedList);
};

/*!	@fn			File NewFile (void)
 *  @brief		새로운 File 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	File
 *  @note 		새로운 File 객체를 생성한다. \n
 *  			File 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyFile \n
 *  			deleteFile \n
 *  			copyFile \n
 *  			moveFile \n
 *  			searchFile \n
 *  			deleteSearchedList
 *  @remark 	privilege	: http://tizen.org/privilege/mediastorage \n
 *  						: http://tizen.org/privilege/externalstorage
 */
File NewFile (void);

/*! @fn 		void DestroyFile (File this_gen)
 *  @brief 		생성한 File 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 File 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 File 객체를 소멸 시킨다. \n
 *  			File 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewFile
 *  @remark 	privilege	: http://tizen.org/privilege/mediastorage \n
 *  						: http://tizen.org/privilege/externalstorage
 */
void DestroyFile (File this_gen);

/*! @fn 		void deleteFile (String src)
 *  @brief 		해당 파일을 삭제한다.
 *  @param[in] 	src 삭제할 파일의 path
 *  @param[out] null
 *  @retval 	void
 *  @note 		해당 파일을 삭제한다. \n
 *  @see 		NewFile
 *  @remark 	privilege	: http://tizen.org/privilege/mediastorage \n
 *  						: http://tizen.org/privilege/externalstorage
 */
void deleteFile (String src);

/*! @fn 		void copyFile (String src, String dst);
 *  @brief 		해당 파일을 복사한다.
 *  @param[in] 	src 복사할 파일의 path
 *  @param[in] 	dst 붙여넣을 위치의 파일의 path
 *  @param[out] null
 *  @retval 	void
 *  @note 		해당 파일을 복사한다. \n
 *  @see 		NewFile \n
 *  			DestroyFile \n
 *  			deleteFile \n
 *  			moveFile \n
 *  			searchFile \n
 *  			deleteSearchedList
 *  @remark 	privilege	: http://tizen.org/privilege/mediastorage \n
 *  						: http://tizen.org/privilege/externalstorage
 */

void copyFile (String src, String dst);
/*! @fn 		void moveFile (String src, String dst);
 *  @brief 		해당 파일을 이동 시킨다.
 *  @param[in] 	src 복사할 파일의 path
 *  @param[in] 	dst 이동시킬 위치의 파일의 path
 *  @param[out] null
 *  @retval 	void
 *  @note 		해당 파일을 이동 시킨다. \n
 *  @see 		NewFile \n
 *  			DestroyFile \n
 *  			deleteFile \n
 *  			copyFile \n
 *  			searchFile \n
 *  			deleteSearchedList
 *  @remark 	privilege	: http://tizen.org/privilege/mediastorage \n
 *  						: http://tizen.org/privilege/externalstorage
 */
void moveFile (String src, String dst);

/*! @fn 		GList * searchFile (String src, String dst)
 *  @brief 		파일을 검색한다.
 *  @param[in] 	src 검색을 수행 할 위치의 path
 *  @param[in] 	dst 검색 할 파일의 이름
 *  @param[out] null
 *  @retval 	GList*
 *  @note 		@a src 폴더 내부에서 @a dst 키워드를 가진 파일을 검색한다. \n
 *  @see 		NewFile \n
 *  			DestroyFile \n
 *  			deleteFile \n
 *  			copyFile \n
 *  			moveFile \n
 *  			deleteSearchedList
 *  @remark 	privilege	: http://tizen.org/privilege/mediastorage \n
 *  						: http://tizen.org/privilege/externalstorage
 */
GList * searchFile (String src, String dst);

/*! @fn 		void deleteSearchedList (GList * searchedList)
 *  @brief 		파일 검색 결과 리스트를 삭제한다.
 *  @param[in] 	searchedList 삭제할 파일 검색 결과 리스트
 *  @param[out] null
 *  @retval 	void
 *  @note 		파일 검색 결과 리스트를 삭제한다. \n
 *  @see 		NewFile \n
 *  			DestroyFile \n
 *  			deleteFile \n
 *  			copyFile \n
 *  			moveFile \n
 *  			searchFile
 *  @remark 	privilege	: http://tizen.org/privilege/mediastorage \n
 *  						: http://tizen.org/privilege/externalstorage
 */
void deleteSearchedList (GList * searchedList);
/* File */


/* Video */
/*! @struct	_Video
 *  @brief	Video 모듈에 대한 구조체이다. Video 모듈은 다양한 방식으로 동영상 파일을 제어 할 수 있다.
 *  @note	File의 Video 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewVideo() 함수를 사용해야 하며 사용이 끝났을 때 DestroyVideo() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__MEDIA__CONTENT__MODULE.html
 *  @todo	privilege에 "http://tizen.org/privilege/display" 을 반드시 추가해야 한다. \n
 *  		privilege에 "http://tizen.org/privilege/mediastorage" 을 반드시 추가해야 한다. \n
 *  		privilege에 "http://tizen.org/privilege/externalstorage" 을 반드시 추가해야 한다.
 */
typedef struct _Video * Video;
struct _Video
{
    void (* Play) (Video this_gen);

    void (* Pause) (Video this_gen);

    void (* Stop) (Video this_gen);

    void (* Record) (Video this_gen);

    String (* getInfo) (Video this_gen, metadata_extractor_attr_e element);

    void (* setURI) (Video this_gen, String uri);

    void (* setObject) (Video this_gen, Evas_Object * EvasObject);

};

typedef struct _VideoExtends
{
    struct _Video video;
    Evas_Object * EvasObject;
    player_h             player_handle;
    metadata_extractor_h videoMetadataHandle;
    String               uri;

} VideoExtends;

/*!	@fn			Video NewVideo (void)
 *  @brief		새로운 Video 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Video
 *  @note 		새로운 Video 객체를 생성한다. \n
 *  			Video 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyVideo \n
 *  			playVideo \n
 *  			pauseVideo \n
 *  			stopVideo \n
 *  			recordVideo \n
 *  			getVideoInfo \n
 *  			setVideoURI \n
 *  			setEvasObject
 *  @remark 	privilege :	http://tizen.org/privilege/display \n
 * 							http://tizen.org/privilege/mediastorage \n
 *							http://tizen.org/privilege/externalstorage
 */
Video  NewVideo (void);

/*! @fn 		void DestroyVideo (Video this_gen)
 *  @brief 		생성한 Video 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Video 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Video 객체를 소멸 시킨다. \n
 *  			Video 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewVideo
 *  @remark 	privilege :	http://tizen.org/privilege/display \n
 * 							http://tizen.org/privilege/mediastorage \n
 *							http://tizen.org/privilege/externalstorage
 */
void   DestroyVideo (Video this_gen);

/*! @fn 		void playVideo (Video this_gen)
 *  @brief 		동영상 파일을 재생한다.
 *  @param[in] 	this_gen 재생할 Video 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		해당 Video 객체를 재생한다. \n
 *  			동영상 파일을 재생하기 전 NewVideo() 함수를 통해 Video 객체를 생성한 후 \n
 *  			setEvasObject()과 setVideoURI()를 통해 Video 객체의 설정을 하고 사용해야한다.
 *  @see 		NewVideo \n
 *  			DestroyVideo \n
 *  			pauseVideo \n
 *  			stopVideo \n
 *  			recordVideo \n
 *  			getVideoInfo \n
 *  			setVideoURI \n
 *  			setEvasObject
 *  @remark 	privilege :	http://tizen.org/privilege/display \n
 * 							http://tizen.org/privilege/mediastorage \n
 *							http://tizen.org/privilege/externalstorage
 */
void   playVideo (Video this_gen);

/*! @fn 		void pauseVideo (Video this_gen)
 *  @brief 		동영상 파일을 일시 정지한다.
 *  @param[in] 	this_gen 일시 정지할 Video 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		해당 Video 객체를 일시 정지한다. \n
 *  			동영상 파일을 일시 정지하기 전 해당 Video 객체는 playVideo()를 통해 현재 재생 중이여야 한다.
 *  @see 		NewVideo \n
 *  			DestroyVideo \n
 *  			playVideo \n
 *  			stopVideo \n
 *  			recordVideo \n
 *  			getVideoInfo \n
 *  			setVideoURI \n
 *  			setEvasObject
 *  @remark 	privilege :	http://tizen.org/privilege/display \n
 * 							http://tizen.org/privilege/mediastorage \n
 *							http://tizen.org/privilege/externalstorage
 */
void   pauseVideo (Video this_gen);

/*! @fn 		void stopVideo (Video this_gen)
 *  @brief 		동영상 파일을 정지한다.
 *  @param[in] 	this_gen 정지할 Video 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		해당 Video 객체를 정지한다. \n
 *  @see 		NewVideo \n
 *  			DestroyVideo \n
 *  			playVideo \n
 *  			pauseVideo \n
 *  			recordVideo \n
 *  			getVideoInfo \n
 *  			setVideoURI \n
 *  			setEvasObject
 *  @remark 	privilege :	http://tizen.org/privilege/display \n
 * 							http://tizen.org/privilege/mediastorage \n
 *							http://tizen.org/privilege/externalstorage
 */
void   stopVideo (Video this_gen);

/*! @fn 		void recordVideo (Video this_gen)
 *  @brief 		동영상을 녹화한다.
 *  @param[in] 	this_gen 녹화할 Video 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		해당 Video 객체를 녹화한다. \n
 *  @see 		NewVideo \n
 *  			DestroyVideo \n
 *  			playVideo \n
 *  			pauseVideo \n
 *  			stopVideo \n
 *  			getVideoInfo \n
 *  			setVideoURI \n
 *  			setEvasObject
 *  @remark 	privilege :	http://tizen.org/privilege/display \n
 * 							http://tizen.org/privilege/mediastorage \n
 *							http://tizen.org/privilege/externalstorage
 */
void   recordVideo (Video this_gen);

/*! @fn 		String getVideoInfo (Video this_gen, metadata_extractor_attr_e element)
 *  @brief 		동영상 파일의 meta data를 가져온다.
 *  @param[in] 	this_gen meta data를 가져올 Video 객체
 *  @param[in] 	element 가져올 meta data 종류
 *  @param[out] null
 *  @retval 	String
 *  @note 		동영상 파일의 meta data를 가져온다. \n
 *  			사용전 setVideoURI() 를 통해 meta data 를 가져올 Video 객체의 URI를 설정해야한다. \n
 *				또한 @a <metadata_extractor.h> 를 반드시 include해야 하며 meta data가 저장된 String은 @c free() 해야한다.
 *  @see 		NewVideo \n
 *  			DestroyVideo \n
 *  			playVideo \n
 *  			pauseVideo \n
 *  			stopVideo \n
 *  			recordVideo \n
 *  			setVideoURI \n
 *  			setEvasObject
 *  @remark 	privilege :	http://tizen.org/privilege/display \n
 * 							http://tizen.org/privilege/mediastorage \n
 *							http://tizen.org/privilege/externalstorage
 */
String getVideoInfo (Video this_gen, metadata_extractor_attr_e element);

/*! @fn 		void setVideoURI (Video this_gen, String URI)
 *  @brief 		생성한 Video 객체의 URI를 설정한다.
 *  @param[in] 	this_gen URI를 설정할 Video 객체
 *  @param[in] 	URI 설정할 URI
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Video 객체의 URI를 설정한다. \n
 *				playVideo() , pauseVideo() , stopVideo() ,  recordVideo() , getVideoInfo() 함수를 사용하기 전에 미리 URI를 설정해야 한다.
 *  @see 		NewVideo \n
 *  			DestroyVideo \n
 *  			playVideo \n
 *  			pauseVideo \n
 *  			stopVideo \n
 *  			recordVideo \n
 *  			getVideoInfo \n
 *  			setEvasObject
 *  @remark 	privilege :	http://tizen.org/privilege/display \n
 * 							http://tizen.org/privilege/mediastorage \n
 *							http://tizen.org/privilege/externalstorage
 */
void   setVideoURI (Video this_gen, String URI);

/*! @fn 		void setEvasObject (Video this_gen, Evas_Object * EvasObject)
 *  @brief 		생성한 Video 객체의 Evas Object를 설정한다.
 *  @param[in] 	this_gen Evas Object를 설정할 Video 객체
 *  @param[in] 	EvasObject 설정할 Evas Object
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Video 객체의 Evas Object를 설정한다. \n
 *  @see 		NewVideo \n
 *  			DestroyVideo \n
 *  			playVideo \n
 *  			pauseVideo \n
 *  			stopVideo \n
 *  			recordVideo \n
 *  			getVideoInfo \n
 *  			setVideoURI
 *  @remark 	privilege :	http://tizen.org/privilege/display \n
 * 							http://tizen.org/privilege/mediastorage \n
 *							http://tizen.org/privilege/externalstorage
 */
void   setEvasObject (Video this_gen, Evas_Object * EvasObject);
/* Video */


/* Audio */
/*! @struct	_Audio
 *  @brief	Audio 모듈에 대한 구조체이다. Audio 모듈은 다양한 방식으로 음악 파일을 제어 할 수 있다.
 *  @note	File의 Audio 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewAudio() 함수를 사용해야 하며 사용이 끝났을 때 DestroyAudio() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__MEDIA__CONTENT__MODULE.html
 *  @todo	privilege에 "http://tizen.org/privilege/mediastorage" 을 반드시 추가해야 한다. \n
 *  		privilege에 "http://tizen.org/privilege/externalstorage" 을 반드시 추가해야 한다. \n
 *  		privilege에 "http://tizen.org/privilege/internet" 을 반드시 추가해야 한다.
 */
typedef struct _Audio * Audio;
struct _Audio
{
    void (* Play) (Audio this_gen);

    void (* Pause) (Audio this_gen);

    void (* Stop) (Audio this_gen);

    void (* Record) (Audio this_gen);

    String (* getInfo) (Audio this_gen, metadata_extractor_attr_e metadataKey);

    void (* setURI) (Audio this_gen, String uri);
};

typedef struct _AudioExtends
{
    struct _Audio        audio;
    player_h             player_handle;
    metadata_extractor_h audioMetadataHandle;
    String               uri;

} AudioExtends;

/*!	@fn			Audio NewAudio (void)
 *  @brief		새로운 Audio 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Audio
 *  @note 		새로운 Audio 객체를 생성한다. \n
 *  			Audio 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyAudio \n
 *  			playAudio \n
 *  			pauseAudio \n
 *  			stopAudio \n
 *  			recordAudio \n
 *  			getAudioInfo \n
 *  			setAudioURI
 *  @remark 	privilege :	http://tizen.org/privilege/mediastorage \n
 *							http://tizen.org/privilege/externalstorage \n
 *							http://tizen.org/privilege/internet
 */
Audio  NewAudio (void);

/*! @fn 		void DestroyAudio (Audio this_gen)
 *  @brief 		생성한 Audio 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Audio 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Audio 객체를 소멸 시킨다. \n
 *  			Audio 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewAudio
 *  @remark 	privilege :	http://tizen.org/privilege/mediastorage \n
 *							http://tizen.org/privilege/externalstorage \n
 *							http://tizen.org/privilege/internet
 */
void   DestroyAudio (Audio this_gen);

/*! @fn 		void playAudio (Audio this_gen)
 *  @brief 		음악 파일을 재생한다.
 *  @param[in] 	this_gen 재생할 Audio 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		해당 Audio 객체를 재생한다. \n
 *  			음악 파일을 재생하기 전 NewAudio() 함수를 통해 Audio 객체를 생성한 후 \n
 *  			setAudioURI()를 통해 Audio 객체의 설정을 하고 사용해야한다.
 *  @see 		NewAudio \n
 *  			DestroyAudio \n
 *  			pauseAudio \n
 *  			stopAudio \n
 *  			recordAudio \n
 *  			getAudioInfo \n
 *  			setAudioURI
 *  @remark 	privilege :	http://tizen.org/privilege/mediastorage \n
 *							http://tizen.org/privilege/externalstorage \n
 *							http://tizen.org/privilege/internet
 */
void   playAudio (Audio this_gen);

/*! @fn 		void pauseAudio (Audio this_gen)
 *  @brief 		음악 파일을 일시 정지한다.
 *  @param[in] 	this_gen 일시 정지할 Audio 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		해당 Audio 객체를 일시 정지한다. \n
 *  			음악 파일을 일시 정지하기 전 해당 Audio 객체는 playAudio()를 통해 현재 재생 중이여야 한다.
 *  @see 		NewAudio \n
 *  			DestroyAudio \n
 *  			playAudio \n
 *  			stopAudio \n
 *  			recordAudio \n
 *  			getAudioInfo \n
 *  			setAudioURI
 *  @remark 	privilege :	http://tizen.org/privilege/mediastorage \n
 *							http://tizen.org/privilege/externalstorage \n
 *							http://tizen.org/privilege/internet
 */
void   pauseAudio (Audio this_gen);

/*! @fn 		void stopAudio (Audio this_gen)
 *  @brief 		동영상 파일을 정지한다.
 *  @param[in] 	this_gen 정지할 Audio 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		해당 Audio 객체를 정지한다. \n
 *  @see 		NewAudio \n
 *  			DestroyAudio \n
 *  			playAudio \n
 *  			pauseAudio \n
 *  			recordAudio \n
 *  			getAudioInfo \n
 *  			setAudioURI
 *  @remark 	privilege :	http://tizen.org/privilege/mediastorage \n
 *							http://tizen.org/privilege/externalstorage \n
 *							http://tizen.org/privilege/internet
 */
void   stopAudio (Audio this_gen);

/*! @fn 		void recordAudio (Audio this_gen)
 *  @brief 		음악파일을 녹음한다.
 *  @param[in] 	this_gen 녹음할 Audio 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		해당 Audio 객체를 녹음한다. \n
 *  @see 		NewAudio \n
 *  			DestroyAudio \n
 *  			playAudio \n
 *  			pauseAudio \n
 *  			stopAudio \n
 *  			getAudioInfo \n
 *  			setAudioURI
 *  @remark 	privilege :	http://tizen.org/privilege/mediastorage \n
 *							http://tizen.org/privilege/externalstorage \n
 *							http://tizen.org/privilege/internet
 */
void   recordAudio (Audio this_gen);

/*! @fn 		String getAudioInfo (Audio this_gen, metadata_extractor_attr_e element)
 *  @brief 		음악 파일의 meta data를 가져온다.
 *  @param[in] 	this_gen meta data를 가져올 Audio 객체
 *  @param[in] 	element 가져올 meta data 종류
 *  @param[out] null
 *  @retval 	String
 *  @note 		음악 파일의 meta data를 가져온다. \n
 *  			사용전 setAudioURI() 를 통해 meta data 를 가져올 Audio 객체의 URI를 설정해야한다. \n
 *				또한 @a <metadata_extractor.h> 를 반드시 include해야 하며 meta data가 저장된 String은 @c free() 해야한다.
 *  @see 		NewAudio \n
 *  			DestroyAudio \n
 *  			playAudio \n
 *  			pauseAudio \n
 *  			stopAudio \n
 *  			recordAudio \n
 *  			setAudioURI
 *  @remark 	privilege :	http://tizen.org/privilege/mediastorage \n
 *							http://tizen.org/privilege/externalstorage \n
 *							http://tizen.org/privilege/internet
 */
String getAudioInfo (Audio this_gen, metadata_extractor_attr_e metadataKey);

/*! @fn 		void setAudioURI (Audio this_gen, String URI)
 *  @brief 		생성한 Audio 객체의 URI를 설정한다.
 *  @param[in] 	this_gen URI를 설정할 Audio 객체
 *  @param[in] 	URI 설정할 URI
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Audio 객체의 URI를 설정한다. \n
 *				playAudio() , pauseAudio() , stopAudio() ,  recordAudio() , getAudioInfo() 함수를 사용하기 전에 미리 URI를 설정해야 한다.
 *  @see 		NewAudio \n
 *  			DestroyAudio \n
 *  			playAudio \n
 *  			pauseAudio \n
 *  			stopAudio \n
 *  			recordAudio \n
 *  			getAudioInfo
 *  @remark 	privilege :	http://tizen.org/privilege/mediastorage \n
 *							http://tizen.org/privilege/externalstorage \n
 *							http://tizen.org/privilege/internet
 */
void   setAudioURI (Audio this_gen, String uri);
/* Audio */


/* Image */
/*! @struct	_Image
 *  @brief	Image 모듈에 대한 구조체이다. Image 모듈은 다양한 방식으로 동영상 파일을 제어 할 수 있다.
 *  @note	File의 Image 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewImage() 함수를 사용해야 하며 사용이 끝났을 때 DestroyImage() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__CONTENT__MEDIA__IMAGE__MODULE.html
 */
typedef struct _Image * Image;
struct _Image
{
    void       (* extractInfo) (Image this_gen, String src);

    String     (* getBurstId) (Image this_gen);

    String     (* getMediaId) (Image this_gen);

    String     (* getDateTaken) (Image this_gen);

    int        (* getWidth) (Image this_gen);

    int        (* getHeight) (Image this_gen);
};

typedef struct _ImageExtends
{

    struct _Image image;
    image_meta_h  imageMetaHandle;
    int           width;
    int           height;

    String datetaken;
    String burst_id;
    String media_id;

} ImageExtends;

/*!	@fn			Image NewImage (void)
 *  @brief		새로운 Image 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Video
 *  @note 		새로운 Image 객체를 생성한다. \n
 *  			Image 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyImage \n
 *  			getImageInfo \n
 *  			getImageBurstId \n
 *  			getImageMediaId \n
 *  			getImageDateTaken \n
 *  			getImageWidth \n
 *  			getImageHeight
 */
Image  NewImage (void);

/*! @fn 		void DestroyImage (Image this_gen)
 *  @brief 		생성한 Image 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Image 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Image 객체를 소멸 시킨다. \n
 *  			Image 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewImage
 */
void   DestroyImage (Image this_gen);

/*! @fn 		void getImageInfo (Image this_gen, String src)
 *  @brief 		사진 파일의 meta data를 가져온다.
 *  @param[in] 	this_gen Image 객체
 *  @param[in] 	src meta data를 가져올 사진 파일의 path
 *  @param[out] null
 *  @retval 	void
 *  @note 		사진 파일의 meta data를 가져온다. \n
 *  @see 		NewImage \n
 *  			DestroyImage \n
 *  			getImageBurstId \n
 *  			getImageMediaId \n
 *  			getImageDateTaken \n
 *  			getImageWidth \n
 *  			getImageHeight
 */
void   getImageInfo (Image this_gen, String src);

/*! @fn 		String getImageBurstId (Image this_gen)
 *  @brief 		사진 파일의 meta data 중 Burst Id를 가져온다.
 *  @param[in] 	this_gen Image 객체
 *  @param[out] null
 *  @retval 	String
 *  @note 		사진 파일의 meta data 중 Burst Id를 가져온다. \n
 *  			사용 전 getImageInfo()를 최소 한번 이상 호출해야 한다.
 *  @see 		NewImage \n
 *  			DestroyImage \n
 *  			getImageInfo \n
 *  			getImageMediaId \n
 *  			getImageDateTaken \n
 *  			getImageWidth \n
 *  			getImageHeight
 */
String getImageBurstId (Image this_gen);

/*! @fn 		String getImageMediaId (Image this_gen)
 *  @brief 		사진 파일의 meta data 중 Media Id를 가져온다.
 *  @param[in] 	this_gen Image 객체
 *  @param[out] null
 *  @retval 	String
 *  @note 		사진 파일의 meta data 중 Media Id를 가져온다. \n
 *  			사용 전 getImageInfo()를 최소 한번 이상 호출해야 한다.
 *  @see 		NewImage \n
 *  			DestroyImage \n
 *  			getImageInfo \n
 *  			getImageBurstId \n
 *  			getImageDateTaken \n
 *  			getImageWidth \n
 *  			getImageHeight
 */
String getImageMediaId (Image this_gen);

/*! @fn 		String getImageDateTaken (Image this_gen)
 *  @brief 		사진 파일의 meta data 중 찍은 날짜 정보를 가져온다.
 *  @param[in] 	this_gen Image 객체
 *  @param[out] null
 *  @retval 	String
 *  @note 		사진 파일의 meta data 중 찍은 날짜 정보를 가져온다. \n
 *  			사용 전 getImageInfo()를 최소 한번 이상 호출해야 한다.
 *  @see 		NewImage \n
 *  			DestroyImage \n
 *  			getImageInfo \n
 *  			getImageBurstId \n
 *  			getImageMediaId \n
 *  			getImageWidth \n
 *  			getImageHeight
 */
String getImageDateTaken (Image this_gen);

/*! @fn 		int getImageWidth (Image this_gen)
 *  @brief 		사진 파일의 meta data 중 찍은 width 정보를 가져온다.
 *  @param[in] 	this_gen Image 객체
 *  @param[out] null
 *  @retval 	int (픽셀 단위)
 *  @note 		사진 파일의 meta data 중 찍은 width 정보를 가져온다. \n
 *  			사용 전 getImageInfo()를 최소 한번 이상 호출해야 한다. \n
 *				단위는 픽셀이다.
 *  @see 		NewImage \n
 *  			DestroyImage \n
 *  			getImageInfo \n
 *  			getImageBurstId \n
 *  			getImageMediaId \n
 *  			getImageDateTaken \n
 *  			getImageHeight
 */
int    getImageWidth (Image this_gen);

/*! @fn 		int getImageHeight (Image this_gen)
 *  @brief 		사진 파일의 meta data 중 찍은 height 정보를 가져온다.
 *  @param[in] 	this_gen Image 객체
 *  @param[out] null
 *  @retval 	int (픽셀 단위)
 *  @note 		사진 파일의 meta data 중 찍은 height 정보를 가져온다. \n
 *  			사용 전 getImageInfo()를 최소 한번 이상 호출해야 한다. \n
 *				단위는 픽셀이다.
 *  @see 		NewImage \n
 *  			DestroyImage \n
 *  			getImageInfo \n
 *  			getImageBurstId \n
 *  			getImageMediaId \n
 *  			getImageDateTaken \n
 *  			getImageWidth \n
 */
int    getImageHeight (Image this_gen);
/* Image */

#ifdef __cplusplus
}
#endif

#endif //_FILE_H