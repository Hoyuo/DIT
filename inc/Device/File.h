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

/**
 *
 * Audio:
 * http://tizen.org/privilege/mediastorage
 * http://tizen.org/privilege/externalstorage
 * http://tizen.org/privilege/internet
 * */

/* File */
typedef struct _File * File;

struct _File
{

    void (* Delete) (String src);

    void (* Copy) (String src, String dst);

    void (* Move) (String src, String dst);

    GList * (* Search) (String src, String dst);

    void (* deleteSearchedList) (GList * searchedList);
};

File NewFile ();
void DestroyFile (File this_gen);
void deleteFile (String src);
void copyFile (String src, String dst);
void moveFile (String src, String dst);
GList * searchFile (String src, String dst);
void deleteSearchedList (GList * searchedList);
/* Video */

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

Video  NewVideo ();
void   DestroyVideo (Video this_gen);
void   playVideo (Video this_gen);
void   pauseVideo (Video this_gen);
void   stopVideo (Video this_gen);
void   recordVideo (Video this_gen);
String getVideoInfo (Video this_gen, metadata_extractor_attr_e element);
void   setVideoURI (Video this_gen, String URI);
void   setEvasObject (Video this_gen, Evas_Object * EvasObject);

typedef struct _VideoExtends
{
    struct _Video video;
    Evas_Object * EvasObject;
    player_h             player_handle;
    metadata_extractor_h videoMetadataHandle;
    String               uri;

} VideoExtends;

/* Audio */

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

Audio  NewAudio ();
void   DestroyAudio (Audio this_gen);
void   playAudio (Audio this_gen);
void   pauseAudio (Audio this_gen);
void   stopAudio (Audio this_gen);
void   recordAudio (Audio this_gen);
String getAudioInfo (Audio this_gen, metadata_extractor_attr_e metadataKey);
void   setAudioURI (Audio this_gen, String uri);

typedef struct _AudioExtends
{
    struct _Audio        audio;
    player_h             player_handle;
    metadata_extractor_h audioMetadataHandle;
    String               uri;

} AudioExtends;

/* Image */
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

Image  NewImage ();
void   DestroyImage (Image this_gen);
void   getImageInfo (Image this_gen, String src);
String getImageBurstId (Image this_gen);
String getImageMediaId (Image this_gen);
String getImageDateTaken (Image this_gen);
int    getImageWidth (Image this_gen);
int    getImageHeight (Image this_gen);

#ifdef __cplusplus
}
#endif

#endif //_FILE_H
