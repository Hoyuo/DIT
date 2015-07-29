
#include <string.h>
#include <stdlib.h>
#include <dlog.h>
#include <Elementary.h>
#include <Evas.h>

#include "Device/MediaRecorder.h"

#define MEDIA_DEFAULT_BITRATE  (288000)
#define MEDIA_DEFAULT_SAMPLERATE (44100)


static bool recorder_define_fileformat_and_rotation(CameraRecorderExtends* cr,const char* filename);
static bool audio_recorder_define_fileformat(AudioRecorderExtends* ar,const char* filename);

const char* recorderErrorCheck(int result);
const char* cameraErrorCheck(int result);

AudioRecorder NewAudioRecroder(void){

	AudioRecorderExtends* this =malloc(sizeof(AudioRecorderExtends));
	this->audiorecorder.Init = audioRecorderInit;
	this->audiorecorder.Start= audioRecorderStart;
	this->audiorecorder.Pause =audioRecorderPause;
	this->audiorecorder.End =audioRecorderEnd;
	this->audiorecorder.Cancel =audioRecorderCancel;

	this->audiorecorderhandle =NULL;

	return &this->audiorecorder;
}

void DestroyAudioRecorder(AudioRecorder this_gen){


	if(this_gen !=NULL)
	{
		AudioRecorderExtends* this= (AudioRecorderExtends*)this_gen;

		if(this->audiorecorderhandle!=NULL)
		{
			recorder_destroy(this->audiorecorderhandle);
		}
		free(this_gen);

		this_gen=NULL;
	}

}

bool audioRecorderInit(AudioRecorder this_gen, const char * filename)
{
	if(this_gen != NULL)
	{
		AudioRecorderExtends* this= (AudioRecorderExtends*)this_gen;

		recorder_error_e ret= RECORDER_ERROR_NONE;

		ret = recorder_create_audiorecorder(&this->audiorecorderhandle);
		if(ret!= RECORDER_ERROR_NONE)
		{
			return false;
		}

		ret= recorder_set_audio_encoder(this->audiorecorderhandle,RECORDER_AUDIO_CODEC_AAC);
		if(ret!= RECORDER_ERROR_NONE)
		{
			return false;
		}
		ret = recorder_attr_set_audio_samplerate(this->audiorecorderhandle, MEDIA_DEFAULT_SAMPLERATE);
		if(ret!= RECORDER_ERROR_NONE)
		{
			return false;
		}

		ret = recorder_set_file_format(this->audiorecorderhandle, RECORDER_FILE_FORMAT_MP4);
		if(ret!= RECORDER_ERROR_NONE)
		{
			return false;
		}

		ret=recorder_attr_set_audio_encoder_bitrate(this->audiorecorderhandle,MEDIA_DEFAULT_BITRATE);
		if(ret!= RECORDER_ERROR_NONE)
		{
			return false;
		}

		ret = recorder_set_filename(this->audiorecorderhandle, filename);
		if(ret!= RECORDER_ERROR_NONE)
		{
			return false;
		}

		ret = recorder_attr_set_audio_device(this->audiorecorderhandle,RECORDER_AUDIO_DEVICE_MIC);
		if(ret!= RECORDER_ERROR_NONE)
		{
			return false;
		}
		ret = recorder_prepare(this->audiorecorderhandle);
		if(ret!= RECORDER_ERROR_NONE)
		{
			return false;
		}
		return true;
	}
	return false;
}

bool audioRecorderStart(AudioRecorder this_gen){

	if(this_gen!=NULL){
		AudioRecorderExtends* this= (AudioRecorderExtends*)this_gen;
		recorder_error_e ret= RECORDER_ERROR_NONE;
		ret = recorder_start(this->audiorecorderhandle);
		if(ret==RECORDER_ERROR_NONE)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool audioRecorderPause(AudioRecorder this_gen){
	if(this_gen!=NULL){
		AudioRecorderExtends* this= (AudioRecorderExtends*)this_gen;
		recorder_error_e ret= RECORDER_ERROR_NONE;

		ret=recorder_pause(this->audiorecorderhandle);
		if(ret==RECORDER_ERROR_NONE)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool audioRecorderEnd(AudioRecorder this_gen){

	if(this_gen!=NULL){
		AudioRecorderExtends* this= (AudioRecorderExtends*)this_gen;
		recorder_error_e ret= RECORDER_ERROR_NONE;

		ret=recorder_commit(this->audiorecorderhandle);
		if(ret==RECORDER_ERROR_NONE)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool audioRecorderCancel(AudioRecorder this_gen){
	if(this_gen!=NULL){
		AudioRecorderExtends* this= (AudioRecorderExtends*)this_gen;
		recorder_error_e ret= RECORDER_ERROR_NONE;
		recorder_cancel(this->audiorecorderhandle);
		if(ret==RECORDER_ERROR_NONE)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;

}


CameraRecorder NewCameraRecroder(void){


	CameraRecorderExtends* this =malloc(sizeof(CameraRecorderExtends));
	this->camerarecorder.Init	 = cameraRecorderInit;
	this->camerarecorder.Start	 = cameraRecorderStart;
	this->camerarecorder.Pause 	 = cameraRecorderPause;
	this->camerarecorder.End	 = cameraRecorderEnd;
	this->camerarecorder.Cancel  = cameraRecorderCancel;

	this->camerarecorderhandle =NULL;
	this->camerahandle=NULL;

	return &this->camerarecorder;
}

void DestroyCameraRecroder(CameraRecorder this_gen){

	if(this_gen !=NULL)
	{
		CameraRecorderExtends* this= (CameraRecorderExtends*)this_gen;

		if(this->camerarecorderhandle!=NULL)
		{
			recorder_unprepare(this->camerarecorderhandle);
			recorder_destroy(this->camerarecorderhandle);
			this->camerarecorderhandle=NULL;

		}
		if(this->camerahandle!=NULL)
		{
			camera_destroy(this->camerahandle);
			this->camerahandle=NULL;
		}
		free(this_gen);

		this_gen=NULL;
	}
}

static bool xxxx(camera_rotation_e rotation, void *user_data)
{
	dlog_print(DLOG_DEBUG,"DIT","%d supports",rotation);
	return true;
}

bool cameraRecorderInit(CameraRecorder this_gen, const char* filename, camera_type camera, Evas_Object* evasObject){

	if(this_gen !=NULL)
	{

		recorder_error_e rret=RECORDER_ERROR_NONE;
		camera_error_e cret=CAMERA_ERROR_NONE;
		bool b=false;
		CameraRecorderExtends* this= (CameraRecorderExtends*)this_gen;

		cret = camera_create((camera_device_e)camera,&this->camerahandle);
		if(cret!= CAMERA_ERROR_NONE)
		{
			return false;
		}

		cret= camera_set_display_mode(this->camerahandle, CAMERA_DISPLAY_MODE_LETTER_BOX);
		if(cret!= CAMERA_ERROR_NONE)
		{
			return false;
		}


//		cret=camera_attr_get_stream_rotation(this->camerahandle,&camera_rotation);
//
//		dlog_print(DLOG_DEBUG,"DIT","%s",cameraErrorcheck(cret));
//		cret=camera_set_display_rotation(this->camerahandle,camera_rotation);
//		dlog_print(DLOG_DEBUG,"DIT","%s",cameraErrorcheck(cret));

		if(camera==1)
		cret=camera_set_display_rotation(this->camerahandle,3);


		cret=camera_attr_foreach_supported_stream_rotation(this->camerahandle,xxxx,NULL);





		cret=camera_set_display(this->camerahandle,CAMERA_DISPLAY_TYPE_EVAS,(void *)evasObject);
		if(cret!= CAMERA_ERROR_NONE)
		{
			return false;
		}

		rret = recorder_create_videorecorder(this->camerahandle, &this->camerarecorderhandle);
		if(rret!= RECORDER_ERROR_NONE)
		{
			return false;
		}
		recorder_attr_set_orientation_tag (this->camerarecorderhandle, 3);

		rret=recorder_set_video_encoder(this->camerarecorderhandle,RECORDER_VIDEO_CODEC_MPEG4);
		if(rret!= RECORDER_ERROR_NONE)
		{
			return false;
		}
		rret=recorder_attr_set_video_encoder_bitrate(this->camerarecorderhandle,MEDIA_DEFAULT_BITRATE);
		if(rret!= RECORDER_ERROR_NONE)
		{
			return false;
		}
		rret=recorder_set_filename(this->camerarecorderhandle, filename);
		if(rret!= RECORDER_ERROR_NONE)
		{
			return false;
		}

		b=recorder_define_fileformat_and_rotation(this,filename);
		if(b!= true)
		{
			return false;
		}

		rret=recorder_set_audio_encoder(this->camerarecorderhandle,RECORDER_AUDIO_CODEC_AAC);
		if(rret!= RECORDER_ERROR_NONE)
		{
			return false;
		}
		rret=recorder_attr_set_audio_encoder_bitrate(this->camerarecorderhandle,MEDIA_DEFAULT_BITRATE);
		if(rret!= RECORDER_ERROR_NONE)
		{
			return false;
		}
		rret=recorder_attr_set_audio_samplerate(this->camerarecorderhandle,MEDIA_DEFAULT_SAMPLERATE);
		if(rret!= RECORDER_ERROR_NONE)
		{
			return false;
		}

		rret = recorder_attr_set_audio_device(this->camerarecorderhandle,RECORDER_AUDIO_DEVICE_MIC);
		if(rret!= RECORDER_ERROR_NONE)
		{
			return false;
		}


		rret=recorder_prepare(this->camerarecorderhandle);
		if(rret!= RECORDER_ERROR_NONE)
		{
			return false;
		}
		return true;
	}
	return false;
}

bool cameraRecorderStart(CameraRecorder this_gen){

	if( this_gen != NULL )
	{
		CameraRecorderExtends* this= (CameraRecorderExtends*)this_gen;
		recorder_error_e ret= RECORDER_ERROR_NONE;
		ret=recorder_start(this->camerarecorderhandle);
		if(ret!=RECORDER_ERROR_NONE)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	return false;
}

bool cameraRecorderPause(CameraRecorder this_gen){

	if( this_gen != NULL )
	{
		CameraRecorderExtends* this= (CameraRecorderExtends*)this_gen;
		recorder_error_e ret= RECORDER_ERROR_NONE;
		ret=recorder_pause(this->camerarecorderhandle);
		if(ret!=RECORDER_ERROR_NONE)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	return false;



}

bool cameraRecorderEnd(CameraRecorder this_gen){

	if( this_gen != NULL )
	{
		CameraRecorderExtends* this= (CameraRecorderExtends*)this_gen;
		recorder_error_e ret= RECORDER_ERROR_NONE;
		ret=recorder_commit(this->camerarecorderhandle);
		if(ret!=RECORDER_ERROR_NONE)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	return false;


}

bool cameraRecorderCancel(CameraRecorder this_gen){

	if( this_gen != NULL )
	{
		CameraRecorderExtends* this= (CameraRecorderExtends*)this_gen;
		recorder_error_e ret= RECORDER_ERROR_NONE;
		ret=recorder_cancel(this->camerarecorderhandle);
		if(ret!=RECORDER_ERROR_NONE)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	return false;


}



static bool recorder_define_fileformat_and_rotation(CameraRecorderExtends* cr,const char* filename)
{
	char* pstr= strdup(filename);
	char* save_pstr= pstr;

	recorder_error_e ret= RECORDER_ERROR_NONE;
	pstr+=sizeof(char)*strlen(save_pstr);
	while(*pstr!='.')pstr-=sizeof(char);
	pstr+=sizeof(char);
	if(strcmp(pstr,"3gp")==0)
	{
		ret=recorder_set_file_format(cr->camerarecorderhandle,RECORDER_FILE_FORMAT_3GP);
		if(ret!=RECORDER_ERROR_NONE)
		{
			free(save_pstr);
			return false;
		}
	}
	if(strcmp(pstr,"mp4")==0)
	{
		ret=recorder_set_file_format(cr->camerarecorderhandle,RECORDER_FILE_FORMAT_MP4);
		if(ret!=RECORDER_ERROR_NONE)
		{
			free(save_pstr);
			return false;
		}
	}

	free(save_pstr);
	return true;
}

static bool audio_recorder_define_fileformat(AudioRecorderExtends* ar,const char* filename)
{

	char* pstr= strdup(filename);
		char* save_pstr= pstr;

		recorder_error_e ret= RECORDER_ERROR_NONE;
		pstr+=sizeof(char)*strlen(save_pstr);
		while(*pstr!='.')pstr-=sizeof(char);
		pstr+=sizeof(char);
		if(strcmp(pstr,"3gp")==0)
		{
			ret=recorder_set_file_format(ar->audiorecorderhandle,RECORDER_FILE_FORMAT_3GP);
			if(ret!=RECORDER_ERROR_NONE)
			{
				free(save_pstr);
				return false;
			}
		}
		if(strcmp(pstr,"mp4")==0)
		{
			ret=recorder_set_file_format(ar->audiorecorderhandle,RECORDER_FILE_FORMAT_MP4);
			if(ret!=RECORDER_ERROR_NONE)
			{
				free(save_pstr);
				return false;
			}
		}

		free(save_pstr);
		return true;
}


const char* RecorderErrorCheck(int result){
	switch(result){

	case RECORDER_ERROR_NONE:
		return "Successful";

	case RECORDER_ERROR_INVALID_PARAMETER:
		return "Invalid parameter";

	case RECORDER_ERROR_INVALID_STATE:
		return "Invalid state";

	case RECORDER_ERROR_OUT_OF_MEMORY:
		return "Out of memory";

	case RECORDER_ERROR_DEVICE:
		return "Device error";

	case RECORDER_ERROR_INVALID_OPERATION:
		return "Internal error";

	case RECORDER_ERROR_SOUND_POLICY:
		return "Blocked by Audio Session Manager";

	case RECORDER_ERROR_SECURITY_RESTRICTED:
		return "Restricted by security system policy";

	case RECORDER_ERROR_SOUND_POLICY_BY_CALL:
		return "Blocked by Audio Session Manager - CALL";

	case RECORDER_ERROR_SOUND_POLICY_BY_ALARM:
		return "Blocked by Audio Session Manager - ALARM";

	case RECORDER_ERROR_ESD:
		return "ESD situation";

	case RECORDER_ERROR_OUT_OF_STORAGE:
		return "Out of storage";

	case RECORDER_ERROR_PERMISSION_DENIED:
		return "The access to the resources can not be granted";

	case RECORDER_ERROR_NOT_SUPPORTED:
		return "The feature is not supported";

	default:
		return "UNKOWN ERROR";
	}

}

const char* cameraErrorCheck(int result)
{
	switch(result)
	{

	case CAMERA_ERROR_NONE:
		return "Successful";

	case CAMERA_ERROR_INVALID_PARAMETER:
		return "Invalid parameter";

	case CAMERA_ERROR_INVALID_STATE:
		return "Invalid state";

	case CAMERA_ERROR_OUT_OF_MEMORY:
		return "Out of memory";

	case CAMERA_ERROR_DEVICE:
		return "Device error";

	case CAMERA_ERROR_INVALID_OPERATION:
		return "Internal error";

	case CAMERA_ERROR_SOUND_POLICY:
		return "Blocked by Audio Session Manager";

	case CAMERA_ERROR_SECURITY_RESTRICTED:
		return "Restricted by security system policy";

	case CAMERA_ERROR_DEVICE_BUSY:
		return "The device is using another application or working on some operation";

	case CAMERA_ERROR_DEVICE_NOT_FOUND:
		return "No camera device";

	case CAMERA_ERROR_SOUND_POLICY_BY_CALL:
		return "Blocked by Audio Session Manager - CALL";

	case CAMERA_ERROR_SOUND_POLICY_BY_ALARM:
		return "Blocked by Audio Session Manager - ALARM";

	case CAMERA_ERROR_ESD:
		return "ESD situation";

	case CAMERA_ERROR_PERMISSION_DENIED:
		return "The access to the resources can not be granted";

	case CAMERA_ERROR_NOT_SUPPORTED:
		return "The feature is not supported";

	default:
		return "UNKNOWN ERROR";
	}
}
