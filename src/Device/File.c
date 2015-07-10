#include "Device/File.h"
#include "tizen.h"
#include <stdlib.h>
#include <stdio.h>
#include <dlog.h>
#include <Evas.h>
#include <metadata_extractor.h>
void AerrorTest(player_error_e x);

File* NewFile() {

	FileExtends* this = malloc(sizeof(FileExtends));

	this->file.copyFile = copyDITFile;
	this->file.createFile = createDITFile;
	this->file.deleteFile = deleteDITFile;
	this->file.moveFile = moveDITFile;
	this->file.searchFile = searchDITFile;

	return &this->file;

}

void DestroyFile(File* this_gen) {
	if (NULL == this_gen) {
		return;
	}

	FileExtends* this = (FileExtends*) this_gen;

	free(this);

}


void createDITFile(File* this_gen, char* src) {

	FileExtends* this = (FileExtends*) this_gen;
	FILE* temp = fopen(src, "wb+");
	fclose(temp);

}

void deleteDITFile(File* this_gen, char* src) {

	FileExtends* this = (FileExtends*) this_gen;
	if(NULL==this_gen||NULL==src){
		return;
	}
	remove(src);

}

void copyDITFile(File* this_gen, char* src, char* dst) {

	FileExtends* this = (FileExtends*) this_gen;

	   FILE *source, *target;

	   source = fopen(src, "r");
	   target = fopen(dst, "w");
	   char ch=0;
	  while( ( ch = fgetc(source) ) != EOF )
	      fputc(ch, target);
	  	  fclose(source);
	     fclose(target);
}
/*
 *
 * error handling needed
 *
 * */

void moveDITFile(File* this_gen, char* src, char* dst) {


	FileExtends* this = (FileExtends*) this_gen;

		   FILE *source, *target;
		   char buf[1024];
		   source = fopen(src, "r");
		   target = fopen(dst, "w");
		   int len=0;
		   while ( (len = fread(buf, sizeof(char), sizeof(buf), source)) != 0 )
		     if (fwrite(buf, sizeof(char), len, target) == 0) {
		       fclose(source); fclose(target);

		       remove(dst);// 에러난 파일 지우고 종료
		       return ;
		     }

	       fclose(source);
	       fclose(target);
	       remove(src);
}

//좀 있다 생각하자
char** searchDITFile(File* this_gen, char* src, char* dst) {

	FileExtends* this = (FileExtends*) this_gen;

	return NULL;
}

Video* NewVideo() {

	VideoExtends* this = (VideoExtends*) malloc(sizeof(VideoExtends));

	this->video.getVideoInfo	= getDITVideoInfo;
	this->video.pauseVideo		= pauseDITVideo;
	this->video.playVideo		= playDITVideo;
	this->video.recordVideo 	= recordDITVideo;
	this->video.stopVideo		= stopDITVideo;
	this->video.setURI			= setDITVideoURI;
	this->video.setEvasObject 	= setDITEvasObject;

	this->videoMetadataHandle=NULL;
	this->player_handle=NULL;
	this->uri=NULL;
	this->EvasObject=NULL;

	player_error_e res;
	res=player_create(&this->player_handle);
	AerrorTest(res);
	res=metadata_extractor_create(&this->videoMetadataHandle);
	AerrorTest(res);

	return &this->video;
}

void DestroyVideo(Video* this_gen) {

	if(NULL==this_gen)
		return;

	VideoExtends* this = (VideoExtends*) this_gen;
	player_error_e res;
	res= player_destroy(this->player_handle);

	if(this->uri!=NULL){
		free(this->uri);
	}

	free(this);
}

void playDITVideo(Video* this_gen) {
	VideoExtends* this = (VideoExtends*) this_gen;

	player_error_e res;
	res = player_set_uri(this->player_handle,this->uri);
	AerrorTest(res);
	res=player_set_display(this->player_handle,PLAYER_DISPLAY_TYPE_EVAS,GET_DISPLAY(this->EvasObject));
	AerrorTest(res);

	res=player_set_display_mode(this->player_handle,PLAYER_DISPLAY_MODE_ORIGIN_OR_LETTER);
	AerrorTest(res);

	res=player_prepare(this->player_handle);
	AerrorTest(res);

	res=player_start(this->player_handle);
	AerrorTest(res);
}

void pauseDITVideo(Video* this_gen) {
		VideoExtends* this = (VideoExtends*) this_gen;
		player_error_e res;
		res=player_pause(this->player_handle);

}

void stopDITVideo(Video* this_gen) {
	VideoExtends* this = (VideoExtends*) this_gen;
	player_error_e res;
		res=player_stop(this->player_handle);

}

void recordDITVideo(Video* this_gen) {
	VideoExtends* this = (VideoExtends*) this_gen;

}

void getDITVideoInfo(Video* this_gen) {
	VideoExtends* this = (VideoExtends*) this_gen;

}

void setDITVideoURI(Video* this_gen, char* uri) {

			if (this_gen == NULL) {
		        return;
		    }

		    if (NULL == uri) {
		        return;
		    }

		    VideoExtends* this = (VideoExtends*) this_gen;

		    if (NULL != this->uri) {
		        free(this->uri);
		    }
		    this->uri = malloc(strlen(uri) + sizeof(char));
		    strcpy(this->uri, uri);




}

void setDITEvasObject(Video* this_gen, Evas_Object* EvasObject){

	if (this_gen == NULL) {
			        return;
			    }
    VideoExtends* this = (VideoExtends*) this_gen;

    this->EvasObject=EvasObject;

}


Audio* NewAudio() {

	AudioExtends* this = (AudioExtends*) malloc(sizeof(AudioExtends));

	this->audio.getAudioInfo = getDITAudioInfo;
	this->audio.pauseAudio = pauseDITAudio;
	this->audio.playAudio = playDITAudio;
	this->audio.recordAudio = recordDITAudio;
	this->audio.stopAudio = stopDITAudio;
	this->audio.setURI= setAudioURI;

	this->uri=NULL;
	this->player_handle=NULL;
	this->audioMetadataHandle=NULL;

	player_error_e res;

	res=player_create(&this->player_handle);

	res=metadata_extractor_create(&this->audioMetadataHandle);
	AerrorTest(res);
	return &this->audio;
}

void DestroyAudio(Audio* this_gen) {

	if(this_gen==NULL){
		return;
	}
	AudioExtends* this = (AudioExtends*) this_gen;
	if(this->uri!=NULL){
		free(this->uri);
	}
	player_error_e res;
	metadata_extractor_destroy(this->audioMetadataHandle);
	res=player_unprepare(this->player_handle);
	res=player_destroy(this->player_handle);
	free(this);

}


void playDITAudio(Audio* this_gen) {
	player_error_e res;

	AudioExtends* this = (AudioExtends*) this_gen;


	res = player_set_uri(this->player_handle,this->uri);
	AerrorTest(res);

	res=player_prepare(this->player_handle);
	AerrorTest(res);

	res=player_start(this->player_handle);
	AerrorTest(res);
}

void pauseDITAudio(Audio* this_gen) {
	player_error_e res;

	AudioExtends* this = (AudioExtends*) this_gen;
	res=player_pause(this->player_handle);
	AerrorTest(res);

}

void stopDITAudio(Audio* this_gen) {
	player_error_e res;

	AudioExtends* this = (AudioExtends*) this_gen;
	res=player_stop(this->player_handle);
	AerrorTest(res);

}

void recordDITAudio(Audio* this_gen) {

	AudioExtends* this = (AudioExtends*) this_gen;
}

void setAudioURI(Audio* this_gen, char* uri){

	   if (this_gen == NULL) {
	        return;
	    }
		AudioExtends* this = (AudioExtends*) this_gen;

	    if (NULL == uri) {
	        return;
	    }
	    if (NULL != this->uri) {
	        free(this->uri);
	    }
	    this->uri = malloc(strlen(uri) + sizeof(char));
	    strcpy(this->uri, uri);

	    metadata_extractor_set_path(this->audioMetadataHandle,this->uri);
	}


/**
 *	@brief for use this function, caller must import <metadata_extractor.h>
 *
 *	@remark return value must be free()
 */
char* getDITAudioInfo(Audio* this_gen,  metadata_extractor_attr_e metadataKey){

	AudioExtends* this = (AudioExtends*) this_gen;
		metadata_extractor_error_e error_value;

		char* res=NULL;
	error_value=metadata_extractor_get_metadata(this->audioMetadataHandle,metadataKey,&res);

	return res;
}

Image* NewImage() {
	ImageExtends* this = (ImageExtends*) malloc(sizeof(ImageExtends));

	this->image.getImageInfo = getDITImageInfo;

	return &this->image;
}

void DestroyImage(Image* this_gen) {
	if(this_gen) return;

	ImageExtends* this = (ImageExtends*) this_gen;
	free(this);
}

void getDITImageInfo(Image* this_gen) {
	ImageExtends* this = (ImageExtends*) this_gen;

}

void AerrorTest(player_error_e x){
	char code[]="DIT Error";
	switch(x){
	case PLAYER_ERROR_NONE:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_NONE");
		break;

	case PLAYER_ERROR_OUT_OF_MEMORY:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_OUT_OF_MEMORY");
		break;
	case 	PLAYER_ERROR_INVALID_PARAMETER:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_INVALID_PARAMETER");
		break;

	case 	PLAYER_ERROR_NO_SUCH_FILE:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_NO_SUCH_FILE");
		break;

	case 	PLAYER_ERROR_INVALID_OPERATION:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_INVALID_OPERATION");
		break;

	case 	PLAYER_ERROR_FILE_NO_SPACE_ON_DEVICE:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_FILE_NO_SPACE_ON_DEVICE");
		break;

	case 	PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE");
		break;

	case 	PLAYER_ERROR_SEEK_FAILED:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_SEEK_FAILED");
		break;

	case 	PLAYER_ERROR_INVALID_STATE:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_INVALID_STATE");
		break;

	case 	PLAYER_ERROR_NOT_SUPPORTED_FILE:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_NOT_SUPPORTED_FILE");
		break;

	case 	PLAYER_ERROR_INVALID_URI:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_INVALID_URI");
		break;

	case 	PLAYER_ERROR_SOUND_POLICY:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_SOUND_POLICY");
		break;

	case 	PLAYER_ERROR_CONNECTION_FAILED:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_CONNECTION_FAILED");
			break;

	case 	PLAYER_ERROR_VIDEO_CAPTURE_FAILED:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_VIDEO_CAPTURE_FAILED");
			break;

	case 	PLAYER_ERROR_DRM_EXPIRED:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_DRM_EXPIRED");
			break;

	case 	PLAYER_ERROR_DRM_NO_LICENSE:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_DRM_NO_LICENSE");
			break;

	case 	PLAYER_ERROR_DRM_FUTURE_USE:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_DRM_FUTURE_USE");
			break;

	case 	PLAYER_ERROR_DRM_NOT_PERMITTED:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_DRM_NOT_PERMITTED");
			break;

	case 	PLAYER_ERROR_RESOURCE_LIMIT:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_RESOURCE_LIMIT");
			break;

	case 	PLAYER_ERROR_PERMISSION_DENIED:
		dlog_print(DLOG_ERROR,code,"PLAYER_ERROR_PERMISSION_DENIED");
			break;


	}

}
