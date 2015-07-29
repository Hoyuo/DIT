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

const char* recorderErrorCheck(int result);
const char* cameraErrorCheck(int result);

typedef struct _AudioRecorder * AudioRecorder;

struct _AudioRecorder
{

    bool (* Init) (AudioRecorder this_gen, const char * filename);

    bool (* Start) (AudioRecorder this_gen);

    bool (* Pause) (AudioRecorder this_gen);

    bool (* End) (AudioRecorder this_gen);

    bool (* Cancel) (AudioRecorder this_gen);

};

AudioRecorder NewAudioRecroder(void);

void DestroyAudioRecorder(AudioRecorder this_gen);

bool audioRecorderInit(AudioRecorder this_gen, const char * filename);

bool audioRecorderStart(AudioRecorder this_gen);

bool audioRecorderPause(AudioRecorder this_gen);

bool audioRecorderEnd(AudioRecorder this_gen);

bool audioRecorderCancel(AudioRecorder this_gen);

typedef struct _AudioRecorderExtends
{
    struct _AudioRecorder audiorecorder;
    recorder_h   audiorecorderhandle;

} AudioRecorderExtends;

typedef enum{
	CAMERA_BACK = 0,
	CAMERA_FRONT
}camera_type;

typedef struct _CameraRecorder * CameraRecorder;

struct _CameraRecorder
{

    bool (* Init) (CameraRecorder this_gen, const char * filename, camera_type camera, Evas_Object* evasObject);

    bool (* Start) (CameraRecorder this_gen);

    bool (* Pause) (CameraRecorder this_gen);

    bool (* End) (CameraRecorder this_gen);

    bool (* Cancel) (CameraRecorder this_gen);

};

CameraRecorder NewCameraRecroder(void);

void DestroyCameraRecroder(CameraRecorder this_gen);

bool cameraRecorderInit(CameraRecorder this_gen, const char * filename, camera_type camera, Evas_Object* evasObject);

bool cameraRecorderStart(CameraRecorder this_gen);

bool cameraRecorderPause(CameraRecorder this_gen);

bool cameraRecorderEnd(CameraRecorder this_gen);

bool cameraRecorderCancel(CameraRecorder this_gen);

typedef struct _CameraRecorderExtends
{
    struct _CameraRecorder camerarecorder;
    recorder_h   camerarecorderhandle;
    camera_h	 camerahandle;

} CameraRecorderExtends;
#ifdef __cplusplus
}
#endif

#endif // _MEDIARECORDER_H_

