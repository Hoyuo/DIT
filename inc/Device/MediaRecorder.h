/*! @file   MediaRecorder.h
 *  @brief  Media MediaRecorder API 를 사용하기 위해 포함해야 하는 헤더이다.
 *  @note   Media MediaRecorder의 Init / Start / Pause / End / Cancel 관련 API를 제공한다.
 *  @see    [Tizen Native API](https://developer.tizen.org/development/api-references/native-application?redirect=https%3A//developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/index.html)
 */

#ifndef _MEDIARECORDER_H_
#define _MEDIARECORDER_H_

#include "dit.h"

#include <stdbool.h>
#include <stdalign.h>

#include <recorder.h>
#include <camera.h>
#include <Elementary.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! @fn         const char * RecorderErrorCheck (int errCode)
 *  @brief      Media Recorder에서 발생하는 Error Code들을 확인 해준다.
 *  @param[in]  errCode 확인 하고자 하는 Error Code
 *  @param[out] null
 *  @retval     RECORDER_ERROR_NONE                     : Successful
 *  @retval     RECORDER_ERROR_INVALID_PARAMETER        : Invalid parameter
 *  @retval     RECORDER_ERROR_INVALID_STATE            : Invalid state
 *  @retval     RECORDER_ERROR_OUT_OF_MEMORY            : Out of memory
 *  @retval     RECORDER_ERROR_DEVICE                   : Device error
 *  @retval     RECORDER_ERROR_INVALID_OPERATION        : Internal error
 *  @retval     RECORDER_ERROR_SOUND_POLICY             : Blocked by Audio Session Manager
 *  @retval     RECORDER_ERROR_SECURITY_RESTRICTED      : Restricted by security system policy
 *  @retval     RECORDER_ERROR_SOUND_POLICY_BY_CALL     : Blocked by Audio Session Manager - CALL
 *  @retval     RECORDER_ERROR_SOUND_POLICY_BY_ALARM    : Blocked by Audio Session Manager - ALARM
 *  @retval     RECORDER_ERROR_ESD                      : ESD situation
 *  @retval     RECORDER_ERROR_OUT_OF_STORAGE           : Out of storage
 *  @retval     RECORDER_ERROR_PERMISSION_DENIED        : The access to the resources can not be granted
 *  @retval     RECORDER_ERROR_NOT_SUPPORTED            : The feature is not supported
 *  @retval     RECORDER_ERROR_UNKNOWN                  : Unknown error occurred 
 *  @note       Media Recorder에서 발생하는 Error Code들을 확인 해준다. \n
 *              Error의 내용은 Log를 통해 출력 된다.    \n
 *              15가지의 Error Code들을 확인 가능 하다.
 *  @see        [Tizen Native API Document - Recorder Error](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__MEDIA__RECORDER__MODULE.html#ga9edb84cd056c6c6e09190e924f0a2617)
 */
const char * RecorderErrorCheck (int result);

/*! @fn         const char * CameraErrorCheck (int errCode)
 *  @brief      Camera에서 발생하는 Error Code들을 확인 해준다.
 *  @param[in]  errCode 확인 하고자 하는 Error Code
 *  @param[out] null
 *  @retval     CAMERA_ERROR_NONE                   : Successful
 *  @retval     CAMERA_ERROR_INVALID_PARAMETER      : Invalid parameter
 *  @retval     CAMERA_ERROR_INVALID_STATE          : Invalid state
 *  @retval     CAMERA_ERROR_OUT_OF_MEMORY          : Out of memory
 *  @retval     CAMERA_ERROR_DEVICE                 : Device error
 *  @retval     CAMERA_ERROR_INVALID_OPERATION      : Internal error
 *  @retval     CAMERA_ERROR_SOUND_POLICY           : Blocked by Audio Session Manager
 *  @retval     CAMERA_ERROR_SECURITY_RESTRICTED    : Restricted by security system policy
 *  @retval     CAMERA_ERROR_DEVICE_BUSY            : The device is using another application or working on some operation
 *  @retval     CAMERA_ERROR_DEVICE_NOT_FOUND       : No camera device
 *  @retval     CAMERA_ERROR_SOUND_POLICY_BY_CALL   : Blocked by Audio Session Manager - CALL
 *  @retval     CAMERA_ERROR_SOUND_POLICY_BY_ALARM  : Blocked by Audio Session Manager - ALARM
 *  @retval     CAMERA_ERROR_ESD                    : ESD situation
 *  @retval     CAMERA_ERROR_PERMISSION_DENIED      : The access to the resources can not be granted
 *  @retval     CAMERA_ERROR_NOT_SUPPORTED          : The feature is not supported
 *  @retval     CAMERA_ERROR_UNKNOWN                : Unknown error occurred 
 *  @note       Camera에서 발생하는 Error Code들을 확인 해준다. \n
 *              Error의 내용은 Log를 통해 출력 된다.    \n
 *              15가지의 Error Code들을 확인 가능 하다.
 *  @see        [Tizen Native API Document - Camera Error](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__MEDIA__CAMERA__MODULE.html#ga2ef5666f3fa5a86c28347623dba6fd39)
 */
const char * CameraErrorCheck (int result);

/* AudioRecorder */
/*! @struct _AudioRecorder
 *  @brief  AudioRecorder 모듈에 대한 구조체이다. AudioRecorder 모듈은 음원을 녹음할 수 있다.
 *  @note   Media Recorder의 AudioRecorder 모듈에 대한 구조체이다. \n
            구조체를 사용하기 전에 NewAudioRecorder() 함수를 사용해야 하며 사용이 끝났을 때 DestroyAudioRecorder() 함수를 꼭 사용해야 한다.
 *  @see    [Tizen Native API Document - Recorder part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__MEDIA__RECORDER__MODULE.html)
 *  @pre    @b privilege \n
 *          * http://tizen.org/privilege/recorder \n
 *          * http://tizen.org/privilege/mediastorage \n
 *          * http://tizen.org/privilege/externalstorage \n
 *  @pre    @b feature \n 
 *          * http://tizen.org/feature/microphone
 */
typedef struct _AudioRecorder * AudioRecorder;

struct _AudioRecorder
{

    bool (* Init) (AudioRecorder this_gen, const String filename);

    bool (* Start) (AudioRecorder this_gen);

    bool (* Pause) (AudioRecorder this_gen);

    bool (* End) (AudioRecorder this_gen);

    bool (* Cancel) (AudioRecorder this_gen);

};

/*! @fn         AudioRecorder NewAudioRecorder(void)
 *  @brief      새로운 AudioRecorder 객체를 생성한다.
 *  @param[in]  void
 *  @param[out] null
 *  @retval     AudioRecorder
 *  @note       새로운 AudioRecorder 객체를 생성한다. \n
 *              AudioRecorder 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see        DestroyAudioRecorder \n
 *              audioRecorderInit \n
 *              audioRecorderStart \n
 *              audioRecorderPause \n
 *              audioRecorderEnd \n
 *              audioRecorderCancel
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/recorder \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/microphone
 *  @warning    사용이 끝났을 때 DestroyAudioRecorder() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
AudioRecorder NewAudioRecorder (void)
{

    AudioRecorderExtends * this = malloc (sizeof (AudioRecorderExtends));
    this->audiorecorder.Init   = audioRecorderInit;
    this->audiorecorder.Start  = audioRecorderStart;
    this->audiorecorder.Pause  = audioRecorderPause;
    this->audiorecorder.End    = audioRecorderEnd;
    this->audiorecorder.Cancel = audioRecorderCancel;

    this->audiorecorderhandle = NULL;

    return &this->audiorecorder;
}
 *	@endcode
 */
AudioRecorder NewAudioRecorder (void);

/*! @fn         void DestroyAudioRecorder(AudioRecorder this_gen);
 *  @brief      생성한 AudioRecorder 객체를 소멸 시킨다.
 *  @param[in]  this_gen 소멸시킬 AudioRecorder 객체
 *  @param[out] null
 *  @retval     void
 *  @note       생성한 AudioRecorder 객체를 소멸 시킨다. \n
 *              AudioRecorder 객체를 사용한 후 반드시 호출해야 한다.
 *  @see        NewAudioRecorder
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/recorder \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/microphone
 */
void DestroyAudioRecorder (AudioRecorder this_gen);

/*! @fn         bool audioRecorderInit(AudioRecorder this_gen, const String filename)
 *  @brief      녹음을 시작하기전 녹음할 Audio Recorder 객체를 초기화 한다.
 *  @param[in]  this_gen 초기화할 AudioRecorder 객체
 *  @param[in]  filename 녹음한 결과를 저장할 파일 이름
 *  @retval     bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note       녹음을 시작하기전 녹음할 Audio Recorder 객체를 초기화 한다.
 *  @see        NewAudioRecorder \n 
 *              DestroyAudioRecorder \n
 *              audioRecorderStart \n
 *              audioRecorderPause \n
 *              audioRecorderEnd \n
 *              audioRecorderCancel
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/recorder \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/microphone
 *  @warning    audioRecorderStart() 를 통해 녹음을 시작하기 전 반드시 실행 해야 한다.
 */
bool audioRecorderInit (AudioRecorder this_gen, const String filename);

/*! @fn         bool audioRecorderStart(AudioRecorder this_gen)
 *  @brief      녹음을 시작한다.
 *  @param[in]  this_gen 녹음할 AudioRecorder 객체
 *  @retval     bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note       녹음을 시작한다.
 *  @see        NewAudioRecorder \n 
 *              DestroyAudioRecorder \n
 *              audioRecorderInit \n
 *              audioRecorderPause \n
 *              audioRecorderEnd \n
 *              audioRecorderCancel
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/recorder \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/microphone
 *  @warning    녹음을 시작하기 전 반드시 audioRecorderInit() 함수를 실행 해야 한다.
 */
bool audioRecorderStart (AudioRecorder this_gen);

/*! @fn         bool audioRecorderPause(AudioRecorder this_gen)
 *  @brief      녹음을 일시 정지 한다.
 *  @param[in]  this_gen 일시 정지할 AudioRecorder 객체
 *  @retval     bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note       녹음을 일시 정지 한다.
 *  @see        NewAudioRecorder \n 
 *              DestroyAudioRecorder \n
 *              audioRecorderInit \n
 *              audioRecorderStart \n
 *              audioRecorderEnd \n
 *              audioRecorderCancel
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/recorder \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/microphone
 */
bool audioRecorderPause (AudioRecorder this_gen);

/*! @fn         bool audioRecorderEnd(AudioRecorder this_gen)
 *  @brief      녹음을 종료하고 녹음 결과를 저장한다.
 *  @param[in]  this_gen 종료할 AudioRecorder 객체
 *  @retval     bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note       녹음을 종료하고 녹음 결과를 저장한다.
 *  @see        NewAudioRecorder \n 
 *              DestroyAudioRecorder \n
 *              audioRecorderInit \n
 *              audioRecorderStart \n
 *              audioRecorderPause \n
 *              audioRecorderCancel
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/recorder \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/microphone
 */
bool audioRecorderEnd (AudioRecorder this_gen);

/*! @fn         bool audioRecorderCancel(AudioRecorder this_gen)
 *  @brief      녹음을 취소하며 녹음 결과를 저장하지 않는다.
 *  @param[in]  this_gen 취소할 AudioRecorder 객체
 *  @retval     bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note       녹음을 취소하며 녹음 결과를 저장하지 않는다.
 *  @see        NewAudioRecorder \n 
 *              DestroyAudioRecorder \n
 *              audioRecorderInit \n
 *              audioRecorderStart \n
 *              audioRecorderPause \n
 *              audioRecorderEnd
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/recorder \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/microphone
 */
bool audioRecorderCancel (AudioRecorder this_gen);

typedef struct _AudioRecorderExtends
{
    struct _AudioRecorder audiorecorder;
    recorder_h            audiorecorderhandle;

} AudioRecorderExtends;

/* CameraRecorder */
typedef enum
{
    CAMERA_BACK = 0,
    CAMERA_FRONT
} camera_type;

/*! @struct _CameraRecorder
 *  @brief  CameraRecorder 모듈에 대한 구조체이다. CameraRecorder 모듈은 동영상을 녹화할 수 있다.
 *  @note   Media Recorder의 CameraRecorder 모듈에 대한 구조체이다. \n
            구조체를 사용하기 전에 NewCameraRecorder() 함수를 사용해야 하며 사용이 끝났을 때 DestroyAudioRecorder() 함수를 꼭 사용해야 한다.
 *  @see    [Tizen Native API Document - Recorder part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__MEDIA__RECORDER__MODULE.html)
 *  @pre    @b privilege \n
 *          * http://tizen.org/privilege/recorder \n
 *          * http://tizen.org/privilege/mediastorage \n
 *          * http://tizen.org/privilege/externalstorage \n
 *  @pre    @b feature \n
 *          * http://tizen.org/feature/camera \n
 *          * http://tizen.org/feature/microphone
 */
typedef struct _CameraRecorder * CameraRecorder;

struct _CameraRecorder
{

    bool (* Init) (CameraRecorder this_gen, const String filename, camera_type camera, Evas_Object * evasObject);

    bool (* Start) (CameraRecorder this_gen);

    bool (* Pause) (CameraRecorder this_gen);

    bool (* End) (CameraRecorder this_gen);

    bool (* Cancel) (CameraRecorder this_gen);

};

/*! @fn         CameraRecorder NewCameraRecorder(void)
 *  @brief      새로운 CameraRecorder 객체를 생성한다.
 *  @param[in]  void
 *  @param[out] null
 *  @retval     CameraRecorder
 *  @note       새로운 CameraRecorder 객체를 생성한다. \n
 *              CameraRecorder 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see        DestroyCameraRecorder \n
 *              cameraRecorderInit \n
 *              cameraRecorderStart \n
 *              cameraRecorderPause \n
 *              cameraRecorderEnd \n
 *              cameraRecorderCancel
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/recorder \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/camera \n
 *              * http://tizen.org/feature/microphone
 *  @warning    사용이 끝났을 때 DestroyCameraRecorder() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
CameraRecorder NewCameraRecorder (void)
{

    CameraRecorderExtends * this = malloc (sizeof (CameraRecorderExtends));
    this->camerarecorder.Init   = cameraRecorderInit;
    this->camerarecorder.Start  = cameraRecorderStart;
    this->camerarecorder.Pause  = cameraRecorderPause;
    this->camerarecorder.End    = cameraRecorderEnd;
    this->camerarecorder.Cancel = cameraRecorderCancel;

    this->camerarecorderhandle = NULL;
    this->camerahandle         = NULL;

    return &this->camerarecorder;
}
 *	@endcode
 */
CameraRecorder NewCameraRecorder (void);

/*! @fn         void DestroyCameraRecorder(CameraRecorder this_gen)
 *  @brief      생성한 CameraRecorder 객체를 소멸 시킨다.
 *  @param[in]  this_gen 소멸시킬 CameraRecorder 객체
 *  @param[out] null
 *  @retval     void
 *  @note       생성한 CameraRecorder 객체를 소멸 시킨다. \n
 *              CameraRecorder 객체를 사용한 후 반드시 호출해야 한다.
 *  @see        NewCameraRecorder
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/recorder \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/camera \n
 *              * http://tizen.org/feature/microphone
 */
void DestroyCameraRecorder (CameraRecorder this_gen);

/*! @fn         bool cameraRecorderInit(CameraRecorder this_gen, const String filename, camera_type camera, Evas_Object* evasObject)
 *  @brief      녹화를 시작하기전 녹화할 Camera Recorder 객체를 초기화 한다.
 *  @param[in]  this_gen 초기화할 CameraRecorder 객체
 *  @param[in]  filename 녹화한 결과를 저장할 파일 이름
 *  @param[in]  camera 전 / 후방 카메라 선택 ( 후방 카메라 : @c 0 / 전방 카메라 : @c 1)
 *  @param[in]  evasObject 
 *  @retval     bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note       녹화를 시작하기전 녹음할 Audio Recorder 객체를 초기화 한다.
 *  @see        NewCameraRecorder \n
 *              DestroyCameraRecorder \n
 *              cameraRecorderStart \n
 *              cameraRecorderPause \n
 *              cameraRecorderEnd \n
 *              cameraRecorderCancel
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/recorder \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/camera \n
 *              * http://tizen.org/feature/microphone
 *  @warning    cameraRecorderStart() 를 통해 녹화를 시작하기 전 반드시 실행 해야 한다.
 */
bool cameraRecorderInit (CameraRecorder this_gen, const String filename, camera_type camera, Evas_Object * evasObject);

/*! @fn         bool cameraRecorderStart(CameraRecorder this_gen)
 *  @brief      녹화를 시작한다.
 *  @param[in]  this_gen 녹화할 CameraRecorder 객체
 *  @retval     bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note       녹화를 시작한다.
 *  @see        NewCameraRecorder \n
 *              DestroyCameraRecorder \n
 *              cameraRecorderInit \n
 *              cameraRecorderPause \n
 *              cameraRecorderEnd \n
 *              cameraRecorderCancel
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/recorder \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/camera \n
 *              * http://tizen.org/feature/microphone
 *  @warning    녹화를 시작하기 전 반드시 cameraRecorderInit() 함수를 실행 해야 한다.
 */
bool cameraRecorderStart (CameraRecorder this_gen);

/*! @fn         bool cameraRecorderPause(CameraRecorder this_gen)
 *  @brief      녹화를 일시 정지 한다.
 *  @param[in]  this_gen 일시 정지할 CameraRecorder 객체
 *  @retval     bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note       녹화를 일시 정지 한다.
 *  @see        NewCameraRecorder \n
 *              DestroyCameraRecorder \n
 *              cameraRecorderInit \n
 *              cameraRecorderStart \n
 *              cameraRecorderEnd \n
 *              cameraRecorderCancel
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/recorder \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/camera \n
 *              * http://tizen.org/feature/microphone
 */
bool cameraRecorderPause (CameraRecorder this_gen);

/*! @fn         bool cameraRecorderEnd(CameraRecorder this_gen)
 *  @brief      녹화를 종료하고 녹화 결과를 저장한다.
 *  @param[in]  this_gen 종료할 CameraRecorder 객체
 *  @retval     bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note       녹화를 종료하고 녹화 결과를 저장한다.
 *  @see        NewCameraRecorder \n
 *              DestroyCameraRecorder \n
 *              cameraRecorderInit \n
 *              cameraRecorderStart \n
 *              cameraRecorderPause \n
 *              cameraRecorderCancel
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/recorder \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/camera \n
 *              * http://tizen.org/feature/microphone
 */
bool cameraRecorderEnd (CameraRecorder this_gen);

/*! @fn         bool cameraRecorderCancel(CameraRecorder this_gen)
 *  @brief      녹화를 취소하며 녹화 결과를 저장하지 않는다.
 *  @param[in]  this_gen 취소할 CameraRecorder 객체
 *  @retval     bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note       녹화를 취소하며 녹화 결과를 저장하지 않는다.
 *  @see        NewCameraRecorder \n
 *              DestroyCameraRecorder \n
 *              cameraRecorderInit \n
 *              cameraRecorderStart \n
 *              cameraRecorderPause \n
 *              cameraRecorderEnd
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/recorder \n
 *              * http://tizen.org/privilege/mediastorage \n
 *              * http://tizen.org/privilege/externalstorage \n
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/camera \n
 *              * http://tizen.org/feature/microphone
 */
bool cameraRecorderCancel (CameraRecorder this_gen);

typedef struct _CameraRecorderExtends
{
    struct _CameraRecorder camerarecorder;
    recorder_h             camerarecorderhandle;
    camera_h               camerahandle;

} CameraRecorderExtends;
#ifdef __cplusplus
}
#endif

#endif // _MEDIARECORDER_H_

