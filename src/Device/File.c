#include "Device/File.h"
#include "tizen.h"
#include <stdlib.h>
#include <stdio.h>
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

	  while( ( ch = fgetc(source) ) != EOF )
	      fputc(ch, target);
	  	  fclose(source);
	     fclose(target);
}

void moveDITFile(File* this_gen, char* src, char* dst) {

	FileExtends* this = (FileExtends*) this_gen;

	FileExtends* this = (FileExtends*) this_gen;

		   FILE *source, *target;
		   char buf[1024];
		   source = fopen(src, "r");
		   target = fopen(dst, "w");
		   int len=0;
		   while ( (len = fread(buf, sizeof(char), sizeof(buf), source)) != NULL )
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

	this->video.getVideoInfo = getDITVideoInfo;
	this->video.pauseVideo = pauseDITVideo;
	this->video.playVideo = playDITVideo;
	this->video.recordVideo = recordDITVideo;
	this->video.stopVideo = stopDITVideo;

	return &this->video;
}

void DestroyVideo(Video* this_gen) {

	VideoExtends* this = (VideoExtends*) this_gen;

	free(this);
}

void playDITVideo(Video* this_gen) {
	VideoExtends* this = (VideoExtends*) this_gen;

}

void pauseDITVideo(Video* this_gen) {
	VideoExtends* this = (VideoExtends*) this_gen;

}

void stopDITVideo(Video* this_gen) {
	VideoExtends* this = (VideoExtends*) this_gen;

}

void recordDITVideo(Video* this_gen) {
	VideoExtends* this = (VideoExtends*) this_gen;

}

void getDITVideoInfo(Video* this_gen) {
	VideoExtends* this = (VideoExtends*) this_gen;

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

	player_create(&(this->player_handle));
	player_prepare(this->player_handle);

	return &this->audio;
}

void DestroyAudio(Audio* this_gen) {

	if(this_gen!=NULL){
		return;
	}
	AudioExtends* this = (AudioExtends*) this_gen;
	if(this->uri!=NULL){
		free(this->uri);
	}
	player_unprepare(this->player_handle);
	player_destroy(this->player_handle);
	free(this);
}


void playDITAudio(Audio* this_gen) {

	AudioExtends* this = (AudioExtends*) this_gen;
	player_start(this->player_handle);

}

void pauseDITAudio(Audio* this_gen) {

	AudioExtends* this = (AudioExtends*) this_gen;
	player_pause(this->player_handle);

}

void stopDITAudio(Audio* this_gen) {

	AudioExtends* this = (AudioExtends*) this_gen;
	player_stop(this->player_handle);
}

void recordDITAudio(Audio* this_gen) {

	AudioExtends* this = (AudioExtends*) this_gen;
}

void setAudioURI(Audio* this_gen, char* uri){

	player_error_e res;

	if(NULL==this_gen||NULL==uri){
		return;
	}

	AudioExtends* this = (AudioExtends*) this_gen;

	res = player_set_uri(this->player_handle,uri);

}

Image* NewImage() {
	ImageExtends* this = (ImageExtends*) malloc(sizeof(ImageExtends));

	this->image.getImageInfo = getDITImageInfo;

	return &this->image;
}

void DestroyImage(Image* this_gen) {
	if(this_gen) return;

	ImageExtends* this = (ImageExtends*) this_gen;
	player_destroy(&(this->player_handle));

	free(this);
}

void getDITImageInfo(Image* this_gen) {
	ImageExtends* this = (ImageExtends*) this_gen;

}
