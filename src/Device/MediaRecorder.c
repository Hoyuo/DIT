/*! @file	MediaRecorder.c
 *  @brief	Media Recorder API가 정의되어있다.
 *  @note	Media Recorder API가 정의되어있다.
 *  @see	MediaRecorder.h
*/

#include "Device/MediaRecorder.h"

#include <string.h>
#include <stdlib.h>

#include <recorder.h>
#include <camera.h>
#include <Elementary.h>
#include <dlog.h>
#include <Evas.h>

#define MEDIA_DEFAULT_BITRATE  (288000)
#define MEDIA_DEFAULT_SAMPLERATE (44100)

static bool recorder_define_fileformat_and_rotation (CameraRecorderExtends * cr, const String filename);

static bool audio_recorder_define_fileformat (AudioRecorderExtends * ar, const String filename);

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

void DestroyAudioRecorder (AudioRecorder this_gen)
{

    if ( this_gen != NULL)
    {
        AudioRecorderExtends * this = (AudioRecorderExtends *)this_gen;

        if ( this->audiorecorderhandle != NULL)
        {
            recorder_destroy (this->audiorecorderhandle);
        }
        free (this_gen);

        this_gen = NULL;
    }

}

bool audioRecorderInit (AudioRecorder this_gen, const String filename)
{
    if ( this_gen != NULL)
    {
        AudioRecorderExtends * this = (AudioRecorderExtends *)this_gen;
        recorder_state_e status = RECORDER_STATE_NONE;
        recorder_get_state (this->audiorecorderhandle, &status);
        if ( status == RECORDER_STATE_NONE )
        {
            recorder_error_e ret = RECORDER_ERROR_NONE;

            ret = recorder_create_audiorecorder (&this->audiorecorderhandle);
            if ( ret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
                return false;
            }

            ret = recorder_set_audio_encoder (this->audiorecorderhandle, RECORDER_AUDIO_CODEC_AAC);
            if ( ret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
                return false;
            }
            ret = recorder_attr_set_audio_samplerate (this->audiorecorderhandle, MEDIA_DEFAULT_SAMPLERATE);
            if ( ret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
                return false;
            }

            ret = audio_recorder_define_fileformat (this, filename);
            if ( ret != true )
            {
                return false;
            }

            ret = recorder_attr_set_audio_encoder_bitrate (this->audiorecorderhandle, MEDIA_DEFAULT_BITRATE);
            if ( ret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
                return false;
            }

            ret = recorder_set_filename (this->audiorecorderhandle, filename);
            if ( ret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
                return false;
            }

            ret = recorder_attr_set_audio_device (this->audiorecorderhandle, RECORDER_AUDIO_DEVICE_MIC);
            if ( ret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
                return false;
            }
            ret = recorder_prepare (this->audiorecorderhandle);
            if ( ret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
                return false;
            }
            return true;
        }
        dlog_print (DLOG_INFO, "DIT", "Invalid state");
        return false;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool audioRecorderStart (AudioRecorder this_gen)
{

    if ( this_gen != NULL)
    {
        AudioRecorderExtends * this = (AudioRecorderExtends *)this_gen;

        recorder_state_e status = RECORDER_STATE_NONE;
        recorder_get_state (this->audiorecorderhandle, &status);

        if ( status == RECORDER_STATE_READY || status == RECORDER_STATE_PAUSED )
        {
            recorder_error_e ret = RECORDER_ERROR_NONE;
            ret = recorder_start (this->audiorecorderhandle);
            if ( ret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
                return false;
            }
            return true;

        }
        dlog_print (DLOG_INFO, "DIT", "Invalid state");
        return false;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool audioRecorderPause (AudioRecorder this_gen)
{
    if ( this_gen != NULL)
    {
        AudioRecorderExtends * this = (AudioRecorderExtends *)this_gen;
        recorder_state_e status = RECORDER_STATE_NONE;
        recorder_get_state (this->audiorecorderhandle, &status);
        if ( status == RECORDER_STATE_RECORDING )
        {

            recorder_error_e ret = RECORDER_ERROR_NONE;

            ret = recorder_pause (this->audiorecorderhandle);
            if ( ret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
                return false;
            }

            return true;

        }
        dlog_print (DLOG_INFO, "DIT", "Invalid state");
        return false;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool audioRecorderEnd (AudioRecorder this_gen)
{

    if ( this_gen != NULL)
    {
        AudioRecorderExtends * this = (AudioRecorderExtends *)this_gen;

        recorder_state_e status = RECORDER_STATE_NONE;
        recorder_get_state (this->audiorecorderhandle, &status);

        if ( status == RECORDER_STATE_RECORDING || status == RECORDER_STATE_PAUSED )
        {
            recorder_error_e ret = RECORDER_ERROR_NONE;
            ret = recorder_commit (this->audiorecorderhandle);
            if ( ret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
                return false;
            }
            return true;
        }
        dlog_print (DLOG_INFO, "DIT", "Invalid state");
        return false;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool audioRecorderCancel (AudioRecorder this_gen)
{
    if ( this_gen != NULL)
    {
        AudioRecorderExtends * this = (AudioRecorderExtends *)this_gen;
        recorder_state_e status;
        recorder_get_state (this->audiorecorderhandle, &status);
        if ( status == RECORDER_STATE_RECORDING || status == RECORDER_STATE_PAUSED )
        {
            recorder_error_e ret = RECORDER_ERROR_NONE;
            recorder_cancel (this->audiorecorderhandle);
            if ( ret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
                return false;
            }
            return true;
        }
        dlog_print (DLOG_INFO, "DIT", "Invalid state");
        return false;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

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

void DestroyCameraRecorder (CameraRecorder this_gen)
{

    if ( this_gen != NULL)
    {
        CameraRecorderExtends * this = (CameraRecorderExtends *)this_gen;

        if ( this->camerarecorderhandle != NULL)
        {
            recorder_unprepare (this->camerarecorderhandle);
            recorder_destroy (this->camerarecorderhandle);
            this->camerarecorderhandle = NULL;

        }
        if ( this->camerahandle != NULL)
        {
            camera_destroy (this->camerahandle);
            this->camerahandle = NULL;
        }
        free (this_gen);

        this_gen = NULL;
    }
}

bool cameraRecorderInit (CameraRecorder this_gen, const String filename, camera_type camera, Evas_Object * evasObject)
{

    if ( this_gen != NULL)
    {
        CameraRecorderExtends * this = (CameraRecorderExtends *)this_gen;

        recorder_state_e status = RECORDER_STATE_NONE;
        recorder_get_state (this->camerarecorderhandle, &status);

        if ( status == RECORDER_STATE_NONE )
        {
            recorder_error_e rret = RECORDER_ERROR_NONE;
            camera_error_e   cret = CAMERA_ERROR_NONE;
            bool             b    = false;

            cret = camera_create ((camera_device_e)camera, &this->camerahandle);
            if ( cret != CAMERA_ERROR_NONE )
            {
                dlog_print (DLOG_DEBUG, "DIT", "%s", CameraErrorCheck (cret));
            }

            cret = camera_set_display_mode (this->camerahandle, CAMERA_DISPLAY_MODE_LETTER_BOX);
            if ( cret != CAMERA_ERROR_NONE )
            {
                dlog_print (DLOG_DEBUG, "DIT", "%s", CameraErrorCheck (cret));
            }

            if ( camera == CAMERA_FRONT )// if front camara
            {
                cret = camera_set_display_rotation (this->camerahandle, 3);
                dlog_print (DLOG_DEBUG, "DIT", "%s", CameraErrorCheck (cret));
            }

            cret = camera_set_display (this->camerahandle, CAMERA_DISPLAY_TYPE_EVAS, (void *)evasObject);
            if ( cret != CAMERA_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", CameraErrorCheck (cret));
            }

            rret = recorder_create_videorecorder (this->camerahandle, &this->camerarecorderhandle);
            if ( rret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_DEBUG, "DIT", "%s", RecorderErrorCheck (rret));
            }
            recorder_attr_set_orientation_tag (this->camerarecorderhandle, 3);

            rret = recorder_set_video_encoder (this->camerarecorderhandle, RECORDER_VIDEO_CODEC_MPEG4);
            if ( rret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_DEBUG, "DIT", "%s", RecorderErrorCheck (rret));
            }

            rret = recorder_attr_set_video_encoder_bitrate (this->camerarecorderhandle, MEDIA_DEFAULT_BITRATE);
            if ( rret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_DEBUG, "DIT", "%s", RecorderErrorCheck (rret));
            }

            rret = recorder_set_filename (this->camerarecorderhandle, filename);
            if ( rret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_DEBUG, "DIT", "%s", RecorderErrorCheck (rret));
            }

            b = recorder_define_fileformat_and_rotation (this, filename);

            rret = recorder_set_audio_encoder (this->camerarecorderhandle, RECORDER_AUDIO_CODEC_AAC);
            if ( rret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_DEBUG, "DIT", "%s", CameraErrorCheck (cret));
            }

            rret = recorder_attr_set_audio_encoder_bitrate (this->camerarecorderhandle, MEDIA_DEFAULT_BITRATE);
            if ( rret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_DEBUG, "DIT", "%s", RecorderErrorCheck (rret));
            }

            rret = recorder_attr_set_audio_samplerate (this->camerarecorderhandle, MEDIA_DEFAULT_SAMPLERATE);
            if ( rret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_DEBUG, "DIT", "%s", RecorderErrorCheck (rret));
            }

            rret = recorder_attr_set_audio_device (this->camerarecorderhandle, RECORDER_AUDIO_DEVICE_MIC);
            if ( rret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_DEBUG, "DIT", "%s", RecorderErrorCheck (rret));
            }

            rret = recorder_prepare (this->camerarecorderhandle);
            if ( rret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_DEBUG, "DIT", "%s", RecorderErrorCheck (rret));
                return false;
            }
            return true;
        }
        dlog_print (DLOG_INFO, "DIT", "Invalid state");
        return false;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool cameraRecorderStart (CameraRecorder this_gen)
{

    if ( this_gen != NULL)
    {
        CameraRecorderExtends * this = (CameraRecorderExtends *)this_gen;

        recorder_state_e status = RECORDER_STATE_NONE;
        recorder_get_state (this->camerarecorderhandle, &status);

        if ( status == RECORDER_STATE_READY || status == RECORDER_STATE_PAUSED )
        {
            recorder_state_e status;
            recorder_get_state (this->camerarecorderhandle, &status);

            recorder_error_e ret = RECORDER_ERROR_NONE;
            ret = recorder_start (this->camerarecorderhandle);
            if ( ret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", RecorderErrorCheck (ret));
                return false;
            }
            return true;
        }
        dlog_print (DLOG_INFO, "DIT", "Invalid state");
        return false;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool cameraRecorderPause (CameraRecorder this_gen)
{

    if ( this_gen != NULL)
    {
        CameraRecorderExtends * this = (CameraRecorderExtends *)this_gen;

        recorder_state_e status = RECORDER_STATE_NONE;
        recorder_get_state (this->camerarecorderhandle, &status);
        if ( status == RECORDER_STATE_RECORDING )
        {

            recorder_error_e ret = RECORDER_ERROR_NONE;
            ret = recorder_pause (this->camerarecorderhandle);

            if ( ret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
                return false;
            }
            return true;

        }
        dlog_print (DLOG_INFO, "DIT", "Invalid State");
        return false;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool cameraRecorderEnd (CameraRecorder this_gen)
{

    if ( this_gen != NULL)
    {
        CameraRecorderExtends * this = (CameraRecorderExtends *)this_gen;

        recorder_state_e status;
        recorder_get_state (this->camerarecorderhandle, &status);
        if ( status == RECORDER_STATE_RECORDING || status == RECORDER_STATE_PAUSED )
        {

            recorder_error_e ret = RECORDER_ERROR_NONE;
            ret = recorder_commit (this->camerarecorderhandle);
            if ( ret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
                return false;
            }
            return true;
        }
        dlog_print (DLOG_INFO, "DIT", "Invalid state");
        return false;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool cameraRecorderCancel (CameraRecorder this_gen)
{

    if ( this_gen != NULL)
    {
        CameraRecorderExtends * this = (CameraRecorderExtends *)this_gen;

        recorder_state_e status;
        recorder_get_state (this->camerarecorderhandle, &status);
        dlog_print (DLOG_DEBUG, "DIT", "%d", status);
        if ( status == RECORDER_STATE_RECORDING || status == RECORDER_STATE_PAUSED )
        {
            recorder_error_e ret = RECORDER_ERROR_NONE;
            ret = recorder_cancel (this->camerarecorderhandle);
            if ( ret != RECORDER_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
                return false;
            }

            return true;

        }
        dlog_print (DLOG_INFO, "DIT", "Invalid state");
        return false;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

static bool recorder_define_fileformat_and_rotation (CameraRecorderExtends * cr, const String filename)
{
    String pstr      = strdup (filename);
    String save_pstr = pstr;

    recorder_error_e ret = RECORDER_ERROR_NONE;
    pstr += sizeof (char) * strlen (save_pstr);
    while (*pstr != '.')
    {
        pstr -= sizeof (char);
    }
    pstr += sizeof (char);
    if ( strcmp (pstr, "3gp") == 0 )
    {
        ret = recorder_set_file_format (cr->camerarecorderhandle, RECORDER_FILE_FORMAT_3GP);
        if ( ret != RECORDER_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
            free (save_pstr);
            return false;
        }
    }
    if ( strcmp (pstr, "mp4") == 0 )
    {
        ret = recorder_set_file_format (cr->camerarecorderhandle, RECORDER_FILE_FORMAT_MP4);
        if ( ret != RECORDER_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
            free (save_pstr);
            return false;
        }
    }

    free (save_pstr);
    return true;
}

static bool audio_recorder_define_fileformat (AudioRecorderExtends * ar, const String filename)
{

    String pstr      = strdup (filename);
    String save_pstr = pstr;

    recorder_error_e ret = RECORDER_ERROR_NONE;
    pstr += sizeof (char) * strlen (save_pstr);
    while (*pstr != '.')
    {
        pstr -= sizeof (char);
    }
    pstr += sizeof (char);
    if ( strcmp (pstr, "3gp") == 0 )
    {
        ret = recorder_set_file_format (ar->audiorecorderhandle, RECORDER_FILE_FORMAT_3GP);
        if ( ret != RECORDER_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
            free (save_pstr);
            return false;
        }
    }
    if ( strcmp (pstr, "mp4") == 0 )
    {
        ret = recorder_set_file_format (ar->audiorecorderhandle, RECORDER_FILE_FORMAT_MP4);
        if ( ret != RECORDER_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", RecorderErrorCheck (ret));
            free (save_pstr);
            return false;
        }
    }

    free (save_pstr);
    return true;
}

const char * RecorderErrorCheck (int result)
{
    switch (result)
    {

    case RECORDER_ERROR_NONE:
        return "RECORDER_ERROR_NONE: Successful";

    case RECORDER_ERROR_INVALID_PARAMETER:
        return "RECORDER_ERROR_INVALID_PARAMETER: Invalid parameter";

    case RECORDER_ERROR_INVALID_STATE:
        return "RECORDER_ERROR_INVALID_STATE: Invalid state";

    case RECORDER_ERROR_OUT_OF_MEMORY:
        return "RECORDER_ERROR_OUT_OF_MEMORY: Out of memory";

    case RECORDER_ERROR_DEVICE:
        return "RECORDER_ERROR_DEVICE: Device error";

    case RECORDER_ERROR_INVALID_OPERATION:
        return "RECORDER_ERROR_INVALID_OPERATION: Internal error";

    case RECORDER_ERROR_SOUND_POLICY:
        return "RECORDER_ERROR_SOUND_POLICY: Blocked by Audio Session Manager";

    case RECORDER_ERROR_SECURITY_RESTRICTED:
        return "RECORDER_ERROR_SECURITY_RESTRICTED: Restricted by security system policy";

    case RECORDER_ERROR_SOUND_POLICY_BY_CALL:
        return "RECORDER_ERROR_SOUND_POLICY_BY_CALL: Blocked by Audio Session Manager - CALL";

    case RECORDER_ERROR_SOUND_POLICY_BY_ALARM:
        return "RECORDER_ERROR_SOUND_POLICY_BY_ALARM: Blocked by Audio Session Manager - ALARM";

    case RECORDER_ERROR_ESD:
        return "RECORDER_ERROR_ESD: ESD situation";

    case RECORDER_ERROR_OUT_OF_STORAGE:
        return "RECORDER_ERROR_OUT_OF_STORAGE: Out of storage";

    case RECORDER_ERROR_PERMISSION_DENIED:
        return "RECORDER_ERROR_PERMISSION_DENIED: The access to the resources can not be granted";

    case RECORDER_ERROR_NOT_SUPPORTED:
        return "RECORDER_ERROR_NOT_SUPPORTED: The feature is not supported";

    default:
        return "RECORDER_ERROR_UNKNOWN";
    }
}

const char * CameraErrorCheck (int result)
{
    switch (result)
    {

    case CAMERA_ERROR_NONE:
        return "CAMERA_ERROR_NONE: Successful";

    case CAMERA_ERROR_INVALID_PARAMETER:
        return "CAMERA_ERROR_INVALID_PARAMETER: Invalid parameter";

    case CAMERA_ERROR_INVALID_STATE:
        return "CAMERA_ERROR_INVALID_STATE: Invalid state";

    case CAMERA_ERROR_OUT_OF_MEMORY:
        return "CAMERA_ERROR_OUT_OF_MEMORY: Out of memory";

    case CAMERA_ERROR_DEVICE:
        return "CAMERA_ERROR_DEVICE: Device error";

    case CAMERA_ERROR_INVALID_OPERATION:
        return "CAMERA_ERROR_INVALID_OPERATION: Internal error";

    case CAMERA_ERROR_SOUND_POLICY:
        return "CAMERA_ERROR_SOUND_POLICY: Blocked by Audio Session Manager";

    case CAMERA_ERROR_SECURITY_RESTRICTED:
        return "CAMERA_ERROR_SECURITY_RESTRICTED: Restricted by security system policy";

    case CAMERA_ERROR_DEVICE_BUSY:
        return "CAMERA_ERROR_DEVICE_BUSY: The device is using another application or working on some operation";

    case CAMERA_ERROR_DEVICE_NOT_FOUND:
        return "CAMERA_ERROR_DEVICE_NOT_FOUND: No camera device";

    case CAMERA_ERROR_SOUND_POLICY_BY_CALL:
        return "CAMERA_ERROR_SOUND_POLICY_BY_CALL: Blocked by Audio Session Manager - CALL";

    case CAMERA_ERROR_SOUND_POLICY_BY_ALARM:
        return "CAMERA_ERROR_SOUND_POLICY_BY_ALARM: Blocked by Audio Session Manager - ALARM";

    case CAMERA_ERROR_ESD:
        return "CAMERA_ERROR_ESD: ESD situation";

    case CAMERA_ERROR_PERMISSION_DENIED:
        return "CAMERA_ERROR_PERMISSION_DENIED: The access to the resources can not be granted";

    case CAMERA_ERROR_NOT_SUPPORTED:
        return "CAMERA_ERROR_NOT_SUPPORTED: The feature is not supported";

    default:
        return "CAMERA_ERROR_UNKNOWN";
    }

}
