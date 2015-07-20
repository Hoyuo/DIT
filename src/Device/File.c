#include "Device/File.h"

#include <stdlib.h>
#include <stdio.h>

#include <tizen.h>
#include <player.h>
#include <Evas.h>
#include <metadata_extractor.h>

File NewFile ()
{
    File this = malloc (sizeof (struct _File));

    this->Create = createFile;
    this->Delete = deleteFile;
    this->Copy   = copyFile;
    this->Move   = moveFile;
    this->Search = searchFile;

    return this;
}

void DestroyFile (File this_gen)
{
    if ( NULL != this_gen )
    {
        free (this_gen);
    }
}

void createFile (String src)
{
    if ( NULL != src )
    {
        FILE * temp = fopen (src, "wb+");
        fclose (temp);
    }
}

void deleteFile (String src)
{
    if ( NULL != src )
    {
        remove (src);
    }
}

void copyFile (String src, String dst)
{
    FILE * source, * target;

    source = fopen (src, "r");
    target = fopen (dst, "w");

    char ch = 0;
    while ((ch = fgetc (source)) != EOF)
    {
        fputc (ch, target);
    }
    fclose (source);
    fclose (target);
}

void moveFile (String src, String dst)
{
    FILE * source, * target;

    source = fopen (src, "r");
    target = fopen (dst, "w");

    int  len = 0;
    char buf[1024];
    while ((len = fread (buf, sizeof (char), sizeof (buf), source)) != 0)
    {
        if ( fwrite (buf, sizeof (char), len, target) == 0 )
        {
            fclose (source);
            fclose (target);

            remove (dst);// 에러난 파일 지우고 종료
            return;
        }
    }

    fclose (source);
    fclose (target);
    remove (src);
}

String * searchFile (String src, String dst)
{
    //todo : 작업 진행 안함

    return NULL;
}

/*
 *
 * @brief
 * @remark privilege: http://tizen.org/privilege/display http://tizen.org/privilege/mediastorage http://tizen.org/privilege/display/externalstorage needed
 *
 * */
Video NewVideo ()
{

    VideoExtends * this = (VideoExtends *)malloc (sizeof (VideoExtends));

    this->video.getInfo  = getVideoInfo;
    this->video.Pause    = pauseVideo;
    this->video.Play     = playVideo;
    this->video.Record   = recordVideo;
    this->video.Stop     = stopVideo;
    this->video.setURI        = setVideoURI;
    this->video.setObject = setEvasObject;

    this->videoMetadataHandle = NULL;
    this->player_handle       = NULL;
    this->uri                 = NULL;
    this->EvasObject          = NULL;

    player_error_e res;
    res = player_create (&this->player_handle);
    AerrorTest (res);
    res = metadata_extractor_create (&this->videoMetadataHandle);
    AerrorTest (res);

    return &this->video;
}

void DestroyVideo (Video this_gen)
{

    if ( NULL == this_gen )
    {
        return;
    }

    VideoExtends * this = (VideoExtends *)this_gen;
    player_error_e res;
    res = player_destroy (this->player_handle);

    if ( this->uri != NULL)
    {
        free (this->uri);
    }

    free (this);
}

void playVideo (Video this_gen)
{
    VideoExtends * this = (VideoExtends *)this_gen;

    player_error_e res;
    res = player_set_uri (this->player_handle, this->uri);
    AerrorTest (res);
    res = player_set_display (this->player_handle, PLAYER_DISPLAY_TYPE_EVAS, GET_DISPLAY (this->EvasObject));
    AerrorTest (res);

    res = player_set_display_mode (this->player_handle, PLAYER_DISPLAY_MODE_ORIGIN_OR_LETTER);
    AerrorTest (res);

    res = player_prepare (this->player_handle);
    AerrorTest (res);

    res = player_start (this->player_handle);
    AerrorTest (res);
}

void pauseVideo (Video this_gen)
{
    VideoExtends * this = (VideoExtends *)this_gen;
    player_error_e res;
    res = player_pause (this->player_handle);

}

void stopVideo (Video this_gen)
{
    VideoExtends * this = (VideoExtends *)this_gen;
    player_error_e res;
    res = player_stop (this->player_handle);

}

void recordVideo (Video this_gen)
{
    VideoExtends * this = (VideoExtends *)this_gen;

}

void getVideoInfo (Video this_gen)
{
    VideoExtends * this = (VideoExtends *)this_gen;

}

void setVideoURI (Video this_gen, char * uri)
{

    if ( this_gen == NULL)
    {
        return;
    }

    if ( NULL == uri )
    {
        return;
    }

    VideoExtends * this = (VideoExtends *)this_gen;

    if ( NULL != this->uri )
    {
        free (this->uri);
    }
    this->uri = malloc (strlen (uri) + sizeof (char));
    strcpy (this->uri, uri);

}

void setEvasObject (Video this_gen, Evas_Object * EvasObject)
{

    if ( this_gen == NULL)
    {
        return;
    }
    VideoExtends * this = (VideoExtends *)this_gen;

    this->EvasObject = EvasObject;

}

Audio NewAudio ()
{

    AudioExtends * this = (AudioExtends *)malloc (sizeof (AudioExtends));

    this->audio.getInfo = getAudioInfo;
    this->audio.Pause   = pauseAudio;
    this->audio.Play    = playAudio;
    this->audio.Record  = recordAudio;
    this->audio.Stop    = stopAudio;
    this->audio.setURI       = setAudioURI;

    this->uri                 = NULL;
    this->player_handle       = NULL;
    this->audioMetadataHandle = NULL;

    player_error_e res;

    res = player_create (&this->player_handle);

    res = metadata_extractor_create (&this->audioMetadataHandle);
    AerrorTest (res);
    return &this->audio;
}

void DestroyAudio (Audio this_gen)
{

    if ( this_gen == NULL)
    {
        return;
    }
    AudioExtends * this = (AudioExtends *)this_gen;
    if ( this->uri != NULL)
    {
        free (this->uri);
    }
    player_error_e res;
    metadata_extractor_destroy (this->audioMetadataHandle);
    res = player_unprepare (this->player_handle);
    res = player_destroy (this->player_handle);
    free (this);

}

void playAudio (Audio this_gen)
{
    player_error_e res;

    AudioExtends * this = (AudioExtends *)this_gen;

    res = player_set_uri (this->player_handle, this->uri);
    AerrorTest (res);

    res = player_prepare (this->player_handle);
    AerrorTest (res);

    res = player_start (this->player_handle);
    AerrorTest (res);
}

void pauseAudio (Audio this_gen)
{
    player_error_e res;

    AudioExtends * this = (AudioExtends *)this_gen;
    res = player_pause (this->player_handle);
    AerrorTest (res);

}

void stopAudio (Audio this_gen)
{
    player_error_e res;

    AudioExtends * this = (AudioExtends *)this_gen;
    res = player_stop (this->player_handle);
    AerrorTest (res);

}

void recordAudio (Audio this_gen)
{

    AudioExtends * this = (AudioExtends *)this_gen;
}

void setAudioURI (Audio this_gen, char * uri)
{

    if ( this_gen == NULL)
    {
        return;
    }
    AudioExtends * this = (AudioExtends *)this_gen;

    if ( NULL == uri )
    {
        return;
    }
    if ( NULL != this->uri )
    {
        free (this->uri);
    }
    this->uri = malloc (strlen (uri) + sizeof (char));
    strcpy (this->uri, uri);

    metadata_extractor_set_path (this->audioMetadataHandle, this->uri);
}

/**
 *	@brief for use this function, caller must import <metadata_extractor.h>
 *
 *	@remark return value must be free()
 */
char * getAudioInfo (Audio this_gen, metadata_extractor_attr_e metadataKey)
{

    AudioExtends * this = (AudioExtends *)this_gen;
    metadata_extractor_error_e error_value;

    char * res = NULL;
    error_value = metadata_extractor_get_metadata (this->audioMetadataHandle, metadataKey, &res);

    return res;
}

Image NewImage ()
{
    Image this = (Image)malloc (sizeof (struct _Image));

    this->getInfo = getImageInfo;

    return this;
}

void DestroyImage (Image this_gen)
{
    if ( this_gen )
    {
        return;
    }

    free (this_gen);
}

void getImageInfo (Image this_gen)
{

}

//void AerrorTest (player_error_e x)
//{
//    char code[] = "DIT Error";
//    switch (x)
//    {
//    case PLAYER_ERROR_NONE:
//        LOGERROR (code, "PLAYER_ERROR_NONE");
//        break;
//
//    case PLAYER_ERROR_OUT_OF_MEMORY:
//        LOGERROR (code, "PLAYER_ERROR_OUT_OF_MEMORY");
//        break;
//    case    PLAYER_ERROR_INVALID_PARAMETER:
//        LOGERROR (code, "PLAYER_ERROR_INVALID_PARAMETER");
//        break;
//
//    case    PLAYER_ERROR_NO_SUCH_FILE:
//        LOGERROR (code, "PLAYER_ERROR_NO_SUCH_FILE");
//        break;
//
//    case    PLAYER_ERROR_INVALID_OPERATION:
//        LOGERROR (code, "PLAYER_ERROR_INVALID_OPERATION");
//        break;
//
//    case    PLAYER_ERROR_FILE_NO_SPACE_ON_DEVICE:
//        LOGERROR (code, "PLAYER_ERROR_FILE_NO_SPACE_ON_DEVICE");
//        break;
//
//    case    PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE:
//        LOGERROR (code, "PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE");
//        break;
//
//    case    PLAYER_ERROR_SEEK_FAILED:
//        LOGERROR (code, "PLAYER_ERROR_SEEK_FAILED");
//        break;
//
//    case    PLAYER_ERROR_INVALID_STATE:
//        LOGERROR (code, "PLAYER_ERROR_INVALID_STATE");
//        break;
//
//    case    PLAYER_ERROR_NOT_SUPPORTED_FILE:
//        LOGERROR (code, "PLAYER_ERROR_NOT_SUPPORTED_FILE");
//        break;
//
//    case    PLAYER_ERROR_INVALID_URI:
//        LOGERROR (code, "PLAYER_ERROR_INVALID_URI");
//        break;
//
//    case    PLAYER_ERROR_SOUND_POLICY:
//        LOGERROR (code, "PLAYER_ERROR_SOUND_POLICY");
//        break;
//
//    case    PLAYER_ERROR_CONNECTION_FAILED:
//        LOGERROR (code, "PLAYER_ERROR_CONNECTION_FAILED");
//        break;
//
//    case    PLAYER_ERROR_VIDEO_CAPTURE_FAILED:
//        LOGERROR (code, "PLAYER_ERROR_VIDEO_CAPTURE_FAILED");
//        break;
//
//    case    PLAYER_ERROR_DRM_EXPIRED:
//        LOGERROR (code, "PLAYER_ERROR_DRM_EXPIRED");
//        break;
//
//    case    PLAYER_ERROR_DRM_NO_LICENSE:
//        LOGERROR (code, "PLAYER_ERROR_DRM_NO_LICENSE");
//        break;
//
//    case    PLAYER_ERROR_DRM_FUTURE_USE:
//        LOGERROR (code, "PLAYER_ERROR_DRM_FUTURE_USE");
//        break;
//
//    case    PLAYER_ERROR_DRM_NOT_PERMITTED:
//        LOGERROR (code, "PLAYER_ERROR_DRM_NOT_PERMITTED");
//        break;
//
//    case    PLAYER_ERROR_RESOURCE_LIMIT:
//        LOGERROR (code, "PLAYER_ERROR_RESOURCE_LIMIT");
//        break;
//
//    case    PLAYER_ERROR_PERMISSION_DENIED:
//        LOGERROR (code, "PLAYER_ERROR_PERMISSION_DENIED");
//        break;
//
//    }
//
//}
