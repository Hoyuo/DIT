/*! @file	File.h
 *  @brief	File API 를 사용하기 위해 포함해야 하는 헤더이다.
 *  @note	File의 File / Video / Audio / Image 관련 API를 제공한다.
 *  @see    [Tizen Native API](https://developer.tizen.org/development/api-references/native-application?redirect=https%3A//developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/index.html)
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

/*! @fn         const char * PlayerErrorCheck (int errCode)
 *  @brief      Audio / Video를 play하는 API에서 발생하는 Error Code들을 확인 해준다.
 *  @param[in]  errCode 확인 하고자 하는 Error Code
 *  @param[out] null
 *  @retval     PLAYER_ERROR_NONE                            : Successful
 *  @retval     PLAYER_ERROR_OUT_OF_MEMORY                   : Out of memory
 *  @retval     PLAYER_ERROR_INVALID_PARAMETER               : Invalid parameter
 *  @retval     PLAYER_ERROR_NO_SUCH_FILE                    : No such file or directory
 *  @retval     PLAYER_ERROR_INVALID_OPERATION               : Invalid operation
 *  @retval     PLAYER_ERROR_FILE_NO_SPACE_ON_DEVICE         : No space left on the device
 *  @retval     PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE : Not supported
 *  @retval     PLAYER_ERROR_SEEK_FAILED                     : Seek operation failure
 *  @retval     PLAYER_ERROR_INVALID_STATE                   : Invalid state
 *  @retval     PLAYER_ERROR_NOT_SUPPORTED_FILE              : File format not supported
 *  @retval     PLAYER_ERROR_INVALID_URI                     : Invalid URI
 *  @retval     PLAYER_ERROR_SOUND_POLICY                    : Sound policy error
 *  @retval     PLAYER_ERROR_CONNECTION_FAILED               : Streaming connection failed
 *  @retval     PLAYER_ERROR_VIDEO_CAPTURE_FAILED            : Video capture failed
 *  @retval     PLAYER_ERROR_DRM_EXPIRED                     : Expired license
 *  @retval     PLAYER_ERROR_DRM_NO_LICENSE                  : No license
 *  @retval     PLAYER_ERROR_DRM_FUTURE_USE                  : License for future use
 *  @retval     PLAYER_ERROR_DRM_NOT_PERMITTED               : Format not permitted
 *  @retval     PLAYER_ERROR_RESOURCE_LIMIT                  : Resource limit
 *  @retval     PLAYER_ERROR_PERMISSION_DENIED               : Permission denied
 *  @retval     PLAYER_ERROR_UNKNOWN                         : Unknown error occurred 
 *  @note       Audio / Video를 play하는 API에서 발생하는 Error Code들을 확인 해준다. \n
 *              Error의 내용은 Log를 통해 출력 된다.    \n
 *              21가지의 Error Code들을 확인 가능 하다.
 *  @see        [Tizen Native API Document - Player Error](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__MEDIA__PLAYER__MODULE.html#ga777e585d4ffacf5740aaeeddfd9853aa)
 */
const char * PlayerErrorCheck (int ret);

/*! @fn         const char * MetadataExtractorErrorCheck (int errCode)
 *  @brief      Metadata를 읽어올 때 사용하는 API에서 발생하는 Error Code들을 확인 해준다.
 *  @param[in]  errCode 확인 하고자 하는 Error Code
 *  @param[out] null
 *  @retval     METADATA_EXTRACTOR_ERROR_NONE               : Successful
 *  @retval     METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER  : Invalid parameter
 *  @retval     METADATA_EXTRACTOR_ERROR_OUT_OF_MEMORY      : Out of memory
 *  @retval     METADATA_EXTRACTOR_ERROR_FILE_EXISTS        : File does not exist
 *  @retval     METADATA_EXTRACTOR_ERROR_PERMISSION_DENIED  : Permission denied
 *  @retval     METADATA_EXTRACTOR_ERROR_OPERATION_FAILED   : Invalid internal operation
 *  @retval     METADATA_ERROR_UNKNOWN                      : Unknown error occurred 
 *  @note       Metadata를 읽어올 때 사용하는 API에서 발생하는 Error Code들을 확인 해준다. \n
 *              Error의 내용은 Log를 통해 출력 된다.    \n
 *              7가지의 Error Code들을 확인 가능 하다.
 *  @see        [Tizen Native API Document - Metadata Extractor Error](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__METADATA__EXTRACTOR__MODULE.html#gab7dface72c18d3653f15f3dd219f0e71)
 */
const char * MetadataExtractorErrorCheck (int ret);

/*! @fn         const char * MediaContentErrorCheck (int errCode)
 *  @brief      Media Content Information을 읽어올 때 사용하는 API에서 발생하는 Error Code들을 확인 해준다.
 *  @param[in]  errCode 확인 하고자 하는 Error Code
 *  @param[out] null
 *  @retval     MEDIA_CONTENT_ERROR_NONE                : Successful
 *  @retval     MEDIA_CONTENT_ERROR_INVALID_PARAMETER   : Invalid parameter
 *  @retval     MEDIA_CONTENT_ERROR_OUT_OF_MEMORY       : Out of memory
 *  @retval     MEDIA_CONTENT_ERROR_INVALID_OPERATION   : Invalid Operation
 *  @retval     MEDIA_CONTENT_FILE_NO_SPACE_ON_DEVICE   : No space left on device
 *  @retval     MEDIA_CONTENT_ERROR_PERMISSION_DENIED   : Permission denied
 *  @retval     MEDIA_CONTENT_ERROR_DB_FAILED           : DB operation failed
 *  @retval     MEDIA_CONTENT_ERROR_DB_BUSY             : DB operation BUSY
 *  @retval     MEDIA_CONTENT_ERROR_NETWORK             : Network Fail
 *  @retval     MEDIA_CONTENT_ERROR_UNSUPPORTED_CONTENT : Unsupported Content
 *  @retval     MEDIA_ERROR_UNKNOWN                     : Unknown error occurred 
 *  @note       Media Content Information을 읽어올 때 사용하는 API에서 발생하는 Error Code들을 확인 해준다. \n
 *              Error의 내용은 Log를 통해 출력 된다.    
 *              11가지의 Error Code들을 확인 가능 하다.
 *  @see        [Tizen Native API Document - Media Content Error](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__MEDIA__CONTENT__MODULE.html#ga7021a96fec7bb8becfe524c95af347ba)
 */
const char * MediaContentErrorCheck (int ret);

/* File */
/*! @struct	_File
 *  @brief	File 모듈에 대한 구조체이다. File 모듈은 다양한 방식으로 파일을 제어 할 수 있다.
 *  @note	File의 File 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewFile() 함수를 사용해야 하며 사용이 끝났을 때 DestroyFile() 함수를 꼭 사용해야 한다.
 *  @see    [Tizen Native API Document - File part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__STORAGE__MODULE.html)
 *  @pre	@b privilege \n
 *          * http://tizen.org/privilege/mediastorage \n
 *  		* http://tizen.org/privilege/externalstorage
 */
typedef struct _File * File;
struct _File
{

    bool (* Delete) (String src);

    bool (* Copy) (String src, String dst);

    bool (* Move) (String src, String dst);

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
 *  @pre    	@b privilege \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage
 *  @warning    사용이 끝났을 때 DestroyFile() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
File NewFile (void)
{
    File this = malloc (sizeof (struct _File));

    this->Delete             = deleteFile;
    this->Copy               = copyFile;
    this->Move               = moveFile;
    this->Search             = searchFile;
    this->deleteSearchedList = deleteSearchedList;
    return this;
}
 *	@endcode
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
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage
 */
void DestroyFile (File this_gen);

/*! @fn 		bool deleteFile (String src)
 *  @brief 		해당 파일을 삭제한다.
 *  @param[in] 	src 삭제할 파일의 path
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		해당 파일을 삭제한다. \n
 *  @see 		NewFile
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage
 */
bool deleteFile (String src);

/*! @fn 		bool copyFile (String src, String dst);
 *  @brief 		해당 파일을 복사한다.
 *  @param[in] 	src 복사할 파일의 path
 *  @param[in] 	dst 붙여넣을 위치의 파일의 path
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		해당 파일을 복사한다. \n
 *  @see 		NewFile \n
 *  			DestroyFile \n
 *  			deleteFile \n
 *  			moveFile \n
 *  			searchFile \n
 *  			deleteSearchedList
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage
 */

bool copyFile (String src, String dst);
/*! @fn 		bool moveFile (String src, String dst);
 *  @brief 		해당 파일을 이동 시킨다.
 *  @param[in] 	src 복사할 파일의 path
 *  @param[in] 	dst 이동시킬 위치의 파일의 path
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		해당 파일을 이동 시킨다. \n
 *  @see 		NewFile \n
 *  			DestroyFile \n
 *  			deleteFile \n
 *  			copyFile \n
 *  			searchFile \n
 *  			deleteSearchedList
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage
 */
bool moveFile (String src, String dst);

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
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage
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
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage
 */
void deleteSearchedList (GList * searchedList);
/* File */


/* Video */
/*! @struct	_Video
 *  @brief	Video 모듈에 대한 구조체이다. Video 모듈은 다양한 방식으로 동영상 파일을 제어 할 수 있다.
 *  @note	File의 Video 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewVideo() 함수를 사용해야 하며 사용이 끝났을 때 DestroyVideo() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Video part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__MEDIA__CONTENT__MODULE.html)
 *  @pre	@b privilege \n
 *          * http://tizen.org/privilege/display \n
 *          * http://tizen.org/privilege/mediastorage \n
 *          * http://tizen.org/privilege/externalstorage
 */
typedef struct _Video * Video;
struct _Video
{
    bool (* Play) (Video this_gen);

    bool (* Pause) (Video this_gen);

    bool (* Stop) (Video this_gen);

    String (* getInfo) (Video this_gen, metadata_extractor_attr_e element);

    bool (* setURI) (Video this_gen, String uri);

    bool (* setObject) (Video this_gen, Evas_Object * EvasObject);

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
 *  			getVideoInfo \n
 *  			setVideoURI \n
 *  			setEvasObject
 *  @pre    	@b privilege \n
 *              * http://tizen.org/privilege/display \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage
 *  @warning    사용이 끝났을 때 DestoryVideo() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
Video NewVideo (void)
{

    VideoExtends * this = (VideoExtends *)malloc (sizeof (VideoExtends));

    this->video.getInfo   = getVideoInfo;
    this->video.Pause     = pauseVideo;
    this->video.Play      = playVideo;
    this->video.Stop      = stopVideo;
    this->video.setURI    = setVideoURI;
    this->video.setObject = setEvasObject;

    this->videoMetadataHandle = NULL;
    this->player_handle       = NULL;
    this->uri                 = NULL;
    this->EvasObject          = NULL;

    player_create (&this->player_handle);
    metadata_extractor_create (&this->videoMetadataHandle);

    return &this->video;
}
 *	@endcode
 */
Video NewVideo (void);

/*! @fn 		void DestroyVideo (Video this_gen)
 *  @brief 		생성한 Video 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Video 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Video 객체를 소멸 시킨다. \n
 *  			Video 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewVideo
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/display \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage
 */
void DestroyVideo (Video this_gen);

/*! @fn 		bool playVideo (Video this_gen)
 *  @brief 		동영상 파일을 재생한다.
 *  @param[in] 	this_gen 재생할 Video 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		해당 Video 객체를 재생한다. \n
 *  			동영상 파일을 재생하기 전 NewVideo() 함수를 통해 Video 객체를 생성한 후 \n
 *  			setEvasObject()과 setVideoURI()를 통해 Video 객체의 설정을 하고 사용해야한다.
 *  @see 		NewVideo \n
 *  			DestroyVideo \n
 *  			pauseVideo \n
 *  			stopVideo \n
 *  			getVideoInfo \n
 *  			setVideoURI \n
 *  			setEvasObject
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/display \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage
 */
bool playVideo (Video this_gen);

/*! @fn 		bool pauseVideo (Video this_gen)
 *  @brief 		동영상 파일을 일시 정지한다.
 *  @param[in] 	this_gen 일시 정지할 Video 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		해당 Video 객체를 일시 정지한다. \n
 *  			동영상 파일을 일시 정지하기 전 해당 Video 객체는 playVideo()를 통해 현재 재생 중이여야 한다.
 *  @see 		NewVideo \n
 *  			DestroyVideo \n
 *  			playVideo \n
 *  			stopVideo \n
 *  			getVideoInfo \n
 *  			setVideoURI \n
 *  			setEvasObject
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/display \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage
 */
bool pauseVideo (Video this_gen);

/*! @fn 		bool stopVideo (Video this_gen)
 *  @brief 		동영상 파일을 정지한다.
 *  @param[in] 	this_gen 정지할 Video 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		해당 Video 객체를 정지한다. \n
 *  @see 		NewVideo \n
 *  			DestroyVideo \n
 *  			playVideo \n
 *  			pauseVideo \n
 *  			getVideoInfo \n
 *  			setVideoURI \n
 *  			setEvasObject
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/display \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage
 */
bool stopVideo (Video this_gen);

/*! @fn 		String getVideoInfo (Video this_gen, metadata_extractor_attr_e element)
 *  @brief 		동영상 파일의 meta data를 가져온다.
 *  @param[in] 	this_gen meta data를 가져올 Video 객체
 *  @param[in] 	element 가져올 meta data 종류
 *  @param[out] null
 *  @retval 	String
 *  @note 		동영상 파일의 meta data를 가져온다. \n
 *  @see 		NewVideo \n
 *  			DestroyVideo \n
 *  			playVideo \n
 *  			pauseVideo \n
 *  			stopVideo \n
 *  			setVideoURI \n
 *  			setEvasObject
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/display \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage
 *  @warning    사용전 setVideoURI() 를 통해 meta data 를 가져올 Video 객체의 URI를 설정해야한다. \n
 *              또한 @a <metadata_extractor.h> 를 반드시 include해야 하며 meta data가 저장된 String은 @c free() 해야한다.
 */
String getVideoInfo (Video this_gen, metadata_extractor_attr_e element);

/*! @fn 		bool setVideoURI (Video this_gen, String URI)
 *  @brief 		생성한 Video 객체의 URI를 설정한다.
 *  @param[in] 	this_gen URI를 설정할 Video 객체
 *  @param[in] 	URI 설정할 URI
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Video 객체의 URI를 설정한다. \n
 *  @see 		NewVideo \n
 *  			DestroyVideo \n
 *  			playVideo \n
 *  			pauseVideo \n
 *  			stopVideo \n
 *  			getVideoInfo \n
 *  			setEvasObject
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/display \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage
 *  @warning    playVideo() , pauseVideo() , stopVideo() , getVideoInfo() 함수를 사용하기 전에 미리 URI를 설정해야 한다.
 */
bool setVideoURI (Video this_gen, String URI);

/*! @fn 		bool setEvasObject (Video this_gen, Evas_Object * EvasObject)
 *  @brief 		생성한 Video 객체의 Evas Object를 설정한다.
 *  @param[in] 	this_gen Evas Object를 설정할 Video 객체
 *  @param[in] 	EvasObject 설정할 Evas Object
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Video 객체의 Evas Object를 설정한다. \n
 *  @see 		NewVideo \n
 *  			DestroyVideo \n
 *  			playVideo \n
 *  			pauseVideo \n
 *  			stopVideo \n
 *  			getVideoInfo \n
 *  			setVideoURI
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/display \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage
 */
bool setEvasObject (Video this_gen, Evas_Object * EvasObject);
/* Video */


/* Audio */
/*! @struct	_Audio
 *  @brief	Audio 모듈에 대한 구조체이다. Audio 모듈은 다양한 방식으로 음악 파일을 제어 할 수 있다.
 *  @note	File의 Audio 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewAudio() 함수를 사용해야 하며 사용이 끝났을 때 DestroyAudio() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Audio part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__MEDIA__CONTENT__MODULE.html)
 *  @pre	@b privilege \n
 *          * http://tizen.org/privilege/mediastorage \n
 *          * http://tizen.org/privilege/externalstorage \n
 *          * http://tizen.org/privilege/internet
 */
typedef struct _Audio * Audio;
struct _Audio
{
    bool (* Play) (Audio this_gen);

    bool (* Pause) (Audio this_gen);

    bool (* Stop) (Audio this_gen);

    String (* getInfo) (Audio this_gen, metadata_extractor_attr_e metadataKey);

    bool (* setURI) (Audio this_gen, String uri);
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
 *  @pre    	@b privilege \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *              * http://tizen.org/privilege/internet
 *  @warning    사용이 끝났을 때 DestoryAudio() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
Audio NewAudio ()
{

    AudioExtends * this = (AudioExtends *)malloc (sizeof (AudioExtends));

    this->audio.getInfo = getAudioInfo;
    this->audio.Pause   = pauseAudio;
    this->audio.Play    = playAudio;
    this->audio.Stop    = stopAudio;
    this->audio.setURI  = setAudioURI;

    this->uri                 = NULL;
    this->player_handle       = NULL;
    this->audioMetadataHandle = NULL;

    player_create (&this->player_handle);
    metadata_extractor_create (&this->audioMetadataHandle);

    return &this->audio;
}
 *	@endcode
 */
Audio NewAudio (void);

/*! @fn 		void DestroyAudio (Audio this_gen)
 *  @brief 		생성한 Audio 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Audio 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Audio 객체를 소멸 시킨다. \n
 *  			Audio 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewAudio
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *              * http://tizen.org/privilege/internet
 */
void DestroyAudio (Audio this_gen);

/*! @fn 		bool playAudio (Audio this_gen)
 *  @brief 		음악 파일을 재생한다.
 *  @param[in] 	this_gen 재생할 Audio 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		해당 Audio 객체를 재생한다. \n
 *  @see 		NewAudio \n
 *  			DestroyAudio \n
 *  			pauseAudio \n
 *  			stopAudio \n
 *  			recordAudio \n
 *  			getAudioInfo \n
 *  			setAudioURI
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *              * http://tizen.org/privilege/internet
 *  @warning    음악 파일을 재생하기 전 NewAudio() 함수를 통해 Audio 객체를 생성한 후 \n
 *              setAudioURI()를 통해 Audio 객체의 설정을 하고 사용해야한다.
 */
bool playAudio (Audio this_gen);

/*! @fn 		bool pauseAudio (Audio this_gen)
 *  @brief 		음악 파일을 일시 정지한다.
 *  @param[in] 	this_gen 일시 정지할 Audio 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		해당 Audio 객체를 일시 정지한다. \n 
 *  @see 		NewAudio \n
 *  			DestroyAudio \n
 *  			playAudio \n
 *  			stopAudio \n
 *  			recordAudio \n
 *  			getAudioInfo \n
 *  			setAudioURI
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *              * http://tizen.org/privilege/internet
 *  @warning    음악 파일을 일시 정지하기 전 해당 Audio 객체는 playAudio()를 통해 현재 재생 중이여야 한다.
 */
bool pauseAudio (Audio this_gen);

/*! @fn 		bool stopAudio (Audio this_gen)
 *  @brief 		동영상 파일을 정지한다.
 *  @param[in] 	this_gen 정지할 Audio 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		해당 Audio 객체를 정지한다. \n
 *  @see 		NewAudio \n
 *  			DestroyAudio \n
 *  			playAudio \n
 *  			pauseAudio \n
 *  			recordAudio \n
 *  			getAudioInfo \n
 *  			setAudioURI
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *              * http://tizen.org/privilege/internet
 */
bool stopAudio (Audio this_gen);

/*! @fn 		String getAudioInfo (Audio this_gen, metadata_extractor_attr_e element)
 *  @brief 		음악 파일의 meta data를 가져온다.
 *  @param[in] 	this_gen meta data를 가져올 Audio 객체
 *  @param[in] 	element 가져올 meta data 종류
 *  @param[out] null
 *  @retval 	String
 *  @note 		음악 파일의 meta data를 가져온다. \n
 *  @see 		NewAudio \n
 *  			DestroyAudio \n
 *  			playAudio \n
 *  			pauseAudio \n
 *  			stopAudio \n
 *  			recordAudio \n
 *  			setAudioURI
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *              * http://tizen.org/privilege/internet
 *  @warming    사용전 setAudioURI() 를 통해 meta data 를 가져올 Audio 객체의 URI를 설정해야한다. \n
 *              또한 @a <metadata_extractor.h> 를 반드시 include해야 하며 meta data가 저장된 String은 @c free() 해야한다.
 */
String getAudioInfo (Audio this_gen, metadata_extractor_attr_e metadataKey);

/*! @fn 		bool setAudioURI (Audio this_gen, String URI)
 *  @brief 		생성한 Audio 객체의 URI를 설정한다.
 *  @param[in] 	this_gen URI를 설정할 Audio 객체
 *  @param[in] 	URI 설정할 URI
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Audio 객체의 URI를 설정한다. \n
 *  @see 		NewAudio \n
 *  			DestroyAudio \n
 *  			playAudio \n
 *  			pauseAudio \n
 *  			stopAudio \n
 *  			recordAudio \n
 *  			getAudioInfo
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *              * http://tizen.org/privilege/internet
 *  @warming    playAudio() , pauseAudio() , stopAudio() ,  recordAudio() , getAudioInfo() 함수를 사용하기 전에 미리 URI를 설정해야 한다.
 */
bool setAudioURI (Audio this_gen, String uri);
/* Audio */


/* Image */
/*! @struct	_Image
 *  @brief	Image 모듈에 대한 구조체이다. Image 모듈은 다양한 방식으로 동영상 파일을 제어 할 수 있다.
 *  @note	File의 Image 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewImage() 함수를 사용해야 하며 사용이 끝났을 때 DestroyImage() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Image part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__CONTENT__MEDIA__IMAGE__MODULE.html)
 */
typedef struct _Image * Image;
struct _Image
{
    bool       (* setURI) (Image this_gen, String src);

    String     (* getMediaId) (Image this_gen);

    String     (* getDate) (Image this_gen);

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
 *  			setImageURI \n
 *  			getImageMediaId \n
 *  			getImageDate \n
 *  			getImageWidth \n
 *  			getImageHeight
 *  @warning    사용이 끝났을 때 DestoryImage() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
Image NewImage ()
{
    ImageExtends * this = (ImageExtends *)malloc (sizeof (ImageExtends));

    this->image.setURI		 = setImageURI;
    this->imageMetaHandle    = NULL;
    this->image.getMediaId   = getImageMediaId;
    this->image.getDate		 = getImageDate;
    this->image.getWidth     = getImageWidth;
    this->image.getHeight    = getImageHeight;
    this->height             = -1;
    this->width              = -1;
    this->datetaken          = NULL;
    this->media_id           = NULL;

    return &this->image;
}
 *	@endcode
 */
Image NewImage (void);

/*! @fn 		void DestroyImage (Image this_gen)
 *  @brief 		생성한 Image 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Image 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Image 객체를 소멸 시킨다. \n
 *  			Image 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewImage
 */
void DestroyImage (Image this_gen);

/*! @fn 		bool setImageURI (Image this_gen, String src)
 *  @brief 		생성한 Image 객체의 URI를 설정한다.
 *  @param[in] 	this_gen Image 객체
 *  @param[in] 	src 설정할
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Image 객체의 URI를 설정한다. \n
 *  @see 		NewImage \n
 *  			DestroyImage \n
 *  			getImageMediaId \n
 *  			getImageDate \n
 *  			getImageWidth \n
 *  			getImageHeight
 */
bool setImageURI (Image this_gen, String src);

/*! @fn 		String getImageMediaId (Image this_gen)
 *  @brief 		사진 파일의 meta data 중 Media Id를 가져온다.
 *  @param[in] 	this_gen Image 객체
 *  @param[out] null
 *  @retval 	String
 *  @note 		사진 파일의 meta data 중 Media Id를 가져온다. \n
 *  @see 		NewImage \n
 *  			DestroyImage \n
 *  			setImageURI \n
 *  			getImageDate \n
 *  			getImageWidth \n
 *  			getImageHeight
 *  @warning   사용 전 setImageURI()를 최소 한번 이상 호출해야 한다.
 */
String getImageMediaId (Image this_gen);

/*! @fn 		String getImageDate (Image this_gen)
 *  @brief 		사진 파일의 meta data 중 날짜 정보를 가져온다.
 *  @param[in] 	this_gen Image 객체
 *  @param[out] null
 *  @retval 	String
 *  @note 		사진 파일의 meta data 중 날짜 정보를 가져온다. \n
 *  @see 		NewImage \n
 *  			DestroyImage \n
 *  			setImageURI \n
 *  			getImageMediaId \n
 *  			getImageWidth \n
 *  			getImageHeight
 *  @warning   사용 전 setImageURI()를 최소 한번 이상 호출해야 한다.
 */
String getImageDate (Image this_gen);

/*! @fn 		int getImageWidth (Image this_gen)
 *  @brief 		사진 파일의 meta data 중 width 정보를 가져온다.
 *  @param[in] 	this_gen Image 객체
 *  @param[out] null
 *  @retval 	int (픽셀 단위)
 *  @note 		사진 파일의 meta data 중 width 정보를 가져온다. \n
 *				단위는 픽셀이다.
 *  @see 		NewImage \n
 *  			DestroyImage \n
 *  			setImageURI \n
 *  			getImageMediaId \n
 *  			getImageDate \n
 *  			getImageHeight
 *  @warning   사용 전 setImageURI()를 최소 한번 이상 호출해야 한다.
 */
int getImageWidth (Image this_gen);

/*! @fn 		int getImageHeight (Image this_gen)
 *  @brief 		사진 파일의 meta data 중 height 정보를 가져온다.
 *  @param[in] 	this_gen Image 객체
 *  @param[out] null
 *  @retval 	int (픽셀 단위)
 *  @note 		사진 파일의 meta data 중 height 정보를 가져온다. \n
 *				단위는 픽셀이다.
 *  @see 		NewImage \n
 *  			DestroyImage \n
 *  			setImageURI \n
 *  			getImageMediaId \n
 *  			getImageDate \n
 *  			getImageWidth \n
 *  @warning   사용 전 setImageURI()를 최소 한번 이상 호출해야 한다.
 */
int getImageHeight (Image this_gen);
/* Image */

#ifdef __cplusplus
}
#endif

#endif //_FILE_H
