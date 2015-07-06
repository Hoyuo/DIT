#ifndef DIT_FILE_H
#define DIT_FILE_H

#include <stdbool.h>
#include <stdalign.h>

#ifdef __cplusplus
extern "C" {
#endif



typedef struct _File File;

typedef struct _File {

	void (*createFile)(File* this_gen, char* src);

	void (*deleteFile)(File* this_gen, char* src);

	void (*copyFile)(File* this_gen, char* src, char* dst);

	void (*moveFile)(File* this_gen, char* src, char* dst);

	char** (*searchFile)(File* this_gen, char* src, char* dst);

} File;

typedef struct _FileExtends{
	File file;

}FileExtends;

File* NewFile();

void DestroyFile(File* this_gen);

void createDITFile(File* this_gen, char* src);

void deleteDITFile(File* this_gen, char* src);

void copyDITFile(File* this_gen, char* src, char* dst);

void moveDITFile(File* this_gen, char* src, char* dst);

char** searchDITFile(File* this_gen, char* src, char* dst);


typedef struct _Video{
	void (*playVideo)(File* this_gen);

	void (*pauseVideo)(File* this_gen);

	void (*stopVideo)(File* this_gen);

	void (*recordVideo)(File* this_gen);

	void (*getVideoInfo)(File* this_gen);

}Video;

typedef struct _VideoExtends{
	Video video;

}VideoExtends;

	Video* NewVideo();

	void DestroyVideo(Video* this_gen);

	void playDITVideo(Video* this_gen);

	void pauseDITVideo(Video* this_gen);

	void stopDITVideo(Video* this_gen);

	void recordDITVideo(Video* this_gen);

	void getDITVideoInfo(Video* this_gen);



typedef struct _Audio{
	void (*playAudio)(File* this_gen);

	void (*pauseAudio)(File* this_gen);

	void (*stopAudio)(File* this_gen);

	void (*recordAudio)(File* this_gen);

	void (*getAudioInfo)(File* this_gen);

}Audio;

typedef struct _AudioExtends{
Audio audio;

}AudioExtends;

Audio* NewAudio();

void DestroyAudio(Audio* this_gen);

void playDITAudio(Audio* this_gen);

void pauseDITAudio(Audio* this_gen);

void stopDITAudio(Audio* this_gen);

void recordDITAudio(Audio* this_gen);

void getDITAudioInfo(Audio* this_gen);


typedef struct _Image{

	void (*getImageInfo)(File* this_gen);

}Image;

typedef struct _ImageExtends{
Image image;

}ImageExtends;

Image* NewImage();

void DestroyImage(Image* this_gen);

void getDITImageInfo(Image* this_gen);


#ifdef __cplusplus
}
#endif

#endif //DIT_FILE_H
