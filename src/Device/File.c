/*! @file	File.c
 *  @brief	File API가 정의되어있다.
 *  @note	File API가 정의되어있다.
 *  @see	File.h
*/


#include "Device/File.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <glib.h>
#include <tizen.h>
#include <player.h>
#include <Evas.h>
#include <metadata_extractor.h>
#include <media_content.h>
#include <dlog.h>

const char * PlayerErrorCheck(int ret);

const char* MetadataExtractorErrorCheck(int ret);

const char * MediaContentErrorCheck(int ret);

static void player_completed_callback(void* user_data);

static void deletemediaresult		(gpointer data);

static void deleteSearchListElement (gpointer data);


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

void DestroyFile (File this_gen)
{
    if ( NULL != this_gen )
    {
        free (this_gen);
    }
}

bool deleteFile (String src)
{
    if ( src != NULL)
    {

    	if(access(src,F_OK)==-1)
    	{
    		dlog_print(DLOG_INFO,"DIT","source file doesn't exist");
    		return false;
    	}

    	int ret =0;
    	ret= remove (src);

    	if(ret != 0)
    	{
    		dlog_print(DLOG_INFO,"DIT","FILE I/O ERROR");
    		return false;
    	}

    	return true;
    }
   	dlog_print(DLOG_INFO,"DIT","srcfilename NULL");
   	return false;

}

bool moveFile (String src, String dst)
{
    if ( src != NULL && dst!=NULL)
    {

    	if(access(src,F_OK)==-1)
    	{
    		dlog_print(DLOG_INFO,"DIT","source file: %s doesn't exist",src);
    		return false;
    	}

    	char buff[BUFSIZ];
    	FILE * in, * out;
    	size_t n;
    	size_t error;
    	in  = fopen (src, "rb");
    	out = fopen (dst, "wb");

    	if(in == NULL)
    	{
    		dlog_print(DLOG_INFO,"DIT","can not open source file : %s",src);
    	}

    	if(out == NULL)
    	{
    		dlog_print(DLOG_INFO,"DIT","can not open destination file : %s",dst);
    	}

    	while ((n = fread (buff, 1, BUFSIZ, in)) != 0)
    	{
    	    error=fwrite (buff, 1, n, out);
    	    if(error == -1)//error
    	    {
    	    	fclose (in);
    	    	fclose (out);
    	    	remove(dst);
    			dlog_print(DLOG_INFO,"DIT","FILE I/O ERROR");
    	    	return false;
    	    }
    	}

    	fclose (in);
    	fclose (out);

    	int ret =0;
    	ret= remove (src);
    	if(ret != 0)
    	{
    		dlog_print(DLOG_INFO,"DIT","FILE I/O ERROR");
    		return false;
    	}
    	return true;
    }
    dlog_print(DLOG_INFO,"DIT","src filename / dst filename not valid");
    return false;


}

bool copyFile (String src, String dst)
{

	if(access(src,F_OK)==-1)
	{
		dlog_print(DLOG_INFO,"DIT","source file doesn't exist");
	    return false;
	}

    char buff[BUFSIZ];
    FILE * in, * out;
    size_t n;
    size_t error;
    in  = fopen (src, "rb");
    out = fopen (dst, "wb");
    if(in == NULL)
    {
    	dlog_print(DLOG_INFO,"DIT","can not open source file : %s",src);
    }
    if(out == NULL)
    {
    	dlog_print(DLOG_INFO,"DIT","can not open destination file : %s",dst);
    }

    while ((n = fread (buff, 1, BUFSIZ, in)) != 0)
    {
        error=fwrite (buff, 1, n, out);
        if(error == -1)
        {
        	fclose (in);
        	fclose (out);
        	remove(dst);
    		dlog_print(DLOG_INFO,"DIT","FILE I/O ERROR");
        	return false;
        }
    }
    fclose (in);
    fclose (out);
    return true;
}

// file search recursion Function using GList
void search_recur (String src, String dest, GList ** searchList)
{

    DIR           * dp;
    struct dirent * entry;
    struct stat statbuf;
    if ((dp = opendir (src)) == NULL)
    {
    	dlog_print(DLOG_INFO,"DIT","target source file doesn't exist");
        return;
    }

    chdir (src);

    while ((entry = readdir (dp)) != NULL)
    {
        lstat (entry->d_name, &statbuf);
        if ( S_ISDIR(statbuf.st_mode))
        {

            /* Found a directory, but ignore . and .. */
            if ( strcmp (".", entry->d_name) == 0 || strcmp ("..", entry->d_name) == 0 )
            {
                continue;
            }

            if ( strcmp (entry->d_name, dest) == 0 )
            {
                String pPath = realpath (entry->d_name, NULL);
                *searchList = g_list_append (*searchList, (gpointer)pPath);
            }

            /* Recurse at a new indent level */
            search_recur (entry->d_name, dest, searchList);

        }
        else if ( strcmp (entry->d_name, dest) == 0 )
        {
            char * pPath = realpath (entry->d_name, NULL);
            *searchList = g_list_append (*searchList, (gpointer)pPath);

        }
    }

    chdir ("..");
    closedir (dp);
}

GList * searchFile (String src, String dst)
{
    GList * searchList = NULL;
    search_recur (src, dst, &searchList);

    return searchList;
}

//callbacking function
static void deleteSearchListElement (gpointer data)
{
    free (data);

}
static void deletemediaresult		(gpointer data)
{
	free (data);
}


void deleteSearchedList (GList * searchList)
{

    g_list_free_full (searchList, deleteSearchListElement);

}


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

    player_error_e res;
    res = player_create (&this->player_handle);
    res = metadata_extractor_create (&this->videoMetadataHandle);

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
    metadata_extractor_destroy (this->videoMetadataHandle);
    player_unprepare (this->player_handle);
    player_destroy (this->player_handle);

    if ( this->uri != NULL)
    {
        free (this->uri);
    }

    free (this);
}

bool playVideo (Video this_gen)
{
	if(this_gen != NULL){
		VideoExtends * this = (VideoExtends *)this_gen;

		player_error_e ret=PLAYER_ERROR_NONE;

		ret = player_prepare (this->player_handle);
		if(ret !=PLAYER_ERROR_NONE && ret != PLAYER_ERROR_INVALID_STATE)
		{
			dlog_print(DLOG_INFO,"DIT","%s",PlayerErrorCheck(ret));
			return false;
	   	}

    	player_unset_completed_cb(this->player_handle);
    	player_set_completed_cb(this->player_handle, player_completed_callback,this->player_handle);

		ret = player_start (this->player_handle);
		if(ret !=PLAYER_ERROR_NONE && ret != PLAYER_ERROR_INVALID_STATE)
		{
			dlog_print(DLOG_INFO,"DIT","%s",PlayerErrorCheck(ret));
			return false;
     	}
    	return true;
	}
	dlog_print(DLOG_INFO,"DIT","NULL MODULE");
	return false;
}

bool pauseVideo (Video this_gen)
{
	if(this_gen!=NULL)
	{
		VideoExtends * this = (VideoExtends *)this_gen;
		player_error_e ret;
		ret = player_pause (this->player_handle);
		if(ret !=PLAYER_ERROR_NONE && ret != PLAYER_ERROR_INVALID_STATE)
		{
			dlog_print(DLOG_INFO,"DIT","%s",PlayerErrorCheck(ret));
			return false;
		}
		return true;
	}

		dlog_print(DLOG_INFO,"DIT","NULL module");
		return false;

}

bool stopVideo (Video this_gen)
{
	if(this_gen != NULL)
	{
		VideoExtends * this = (VideoExtends *)this_gen;
		player_error_e ret;
		ret = player_stop (this->player_handle);
		if(ret !=PLAYER_ERROR_NONE&& ret != PLAYER_ERROR_INVALID_STATE)
		{
			dlog_print(DLOG_INFO,"DIT","%s",PlayerErrorCheck(ret));
			return false;
		}
		return true;
	}
	dlog_print(DLOG_INFO,"DIT","NULL module");
	return false;
}



String getVideoInfo (Video this_gen, metadata_extractor_attr_e element)
{
	if(this_gen != NULL)
	{
		VideoExtends * this = (VideoExtends *)this_gen;
		String resultInfo;
		player_error_e ret = PLAYER_ERROR_NONE;
		ret=metadata_extractor_get_metadata (this->videoMetadataHandle, element, &resultInfo);
		if(ret!= PLAYER_ERROR_NONE)
		{
			dlog_print(DLOG_INFO,"DIT","%s",PlayerErrorCheck(ret));
			return NULL;
		}
		return resultInfo;
	}
	dlog_print(DLOG_INFO,"DIT","NULL module");
	return NULL;
}

bool setVideoURI (Video this_gen, char * uri)
{

    if ( this_gen != NULL)
    {
        player_error_e ret = PLAYER_ERROR_NONE;

        if ( NULL == uri )
        {
        	dlog_print(DLOG_INFO,"DIT","NULL URI");
        	return false;
        }

        VideoExtends * this = (VideoExtends *)this_gen;

        if ( NULL != this->uri )
        {
        	free (this->uri);
        }
        this->uri = malloc (strlen (uri) + sizeof (char));
        strcpy (this->uri, uri);

        ret = player_set_uri (this->player_handle, this->uri);
        if(ret != PLAYER_ERROR_NONE)
        {
        	dlog_print(DLOG_INFO,"DIT","%s",PlayerErrorCheck(ret));
			return false;
        }
        ret = metadata_extractor_set_path (this->videoMetadataHandle, this->uri);
        if(ret != PLAYER_ERROR_NONE)
	 	{
	 		dlog_print(DLOG_INFO,"DIT","%s",PlayerErrorCheck(ret));
	 		return false;
	 	}
    return true;
    }
	dlog_print(DLOG_INFO,"DIT","NULL module");
    return false;

}

bool setEvasObject (Video this_gen, Evas_Object * EvasObject)
{

    if ( this_gen != NULL)
    {
    	VideoExtends * this = (VideoExtends *)this_gen;

    	this->EvasObject = EvasObject;

    	player_error_e ret = PLAYER_ERROR_NONE;
    	ret = player_set_display (this->player_handle, PLAYER_DISPLAY_TYPE_EVAS, GET_DISPLAY (this->EvasObject));
    	if(ret !=PLAYER_ERROR_NONE)
    	{
    		dlog_print(DLOG_INFO,"DIT","%s",PlayerErrorCheck(ret));
    		return false;
    	}
    	ret = player_set_display_mode (this->player_handle, PLAYER_DISPLAY_MODE_ORIGIN_OR_LETTER);
    	if(ret !=PLAYER_ERROR_NONE)
    	{
    		dlog_print(DLOG_INFO,"DIT","%s",PlayerErrorCheck(ret));
    		return false;
    	}

    	return true;
    }
	dlog_print(DLOG_INFO,"DIT","NULL module");
    return false;

}

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

void DestroyAudio (Audio this_gen)
{

    if ( this_gen != NULL)
    {
    AudioExtends * this = (AudioExtends *)this_gen;
    if ( this->uri != NULL)
    {
        free (this->uri);
    }

    metadata_extractor_destroy (this->audioMetadataHandle);
    player_unprepare (this->player_handle);
    player_destroy (this->player_handle);
    free (this);
    }

	dlog_print(DLOG_INFO,"DIT","NULL module");
    return;

}

bool playAudio (Audio this_gen)
{
	if(this_gen != NULL)
	{
		player_error_e res;

		AudioExtends * this = (AudioExtends *)this_gen;



		res = player_prepare (this->player_handle);
    	if( res != PLAYER_ERROR_NONE && res != PLAYER_ERROR_INVALID_STATE )
    	{
    		dlog_print(DLOG_INFO,"DIT","%s",PlayerErrorCheck(res));
    	}
    	player_unset_completed_cb(this->player_handle);
    	player_set_completed_cb(this->player_handle, player_completed_callback,this->player_handle);
    	res = player_start (this->player_handle);
    	if(res != PLAYER_ERROR_NONE && res != PLAYER_ERROR_INVALID_STATE)
    	{
    		dlog_print(DLOG_INFO,"DIT","%s",PlayerErrorCheck(res));
    		return false;
    	}
    	return true;
	}

	dlog_print(DLOG_INFO,"DIT","NULL module");
	return false;
}

bool pauseAudio (Audio this_gen)
{
	if(this_gen != NULL)
	{
		player_error_e res;

    	AudioExtends * this = (AudioExtends *)this_gen;

    	res = player_pause (this->player_handle);
    	if(res != PLAYER_ERROR_NONE && res != PLAYER_ERROR_INVALID_STATE)
    	{
    		dlog_print(DLOG_INFO,"DIT","%s",PlayerErrorCheck(res));
    		return false;
    	}
    	return true;
	}
	dlog_print(DLOG_INFO,"DIT","NULL module");
	return false;

}

bool stopAudio (Audio this_gen)
{
	if(this_gen != NULL)
	{
		player_error_e res;

    	AudioExtends * this = (AudioExtends *)this_gen;
    	res = player_stop (this->player_handle);
    	if(res != PLAYER_ERROR_NONE && res != PLAYER_ERROR_INVALID_STATE)
    	{
    		dlog_print(DLOG_INFO,"DIT","%s",PlayerErrorCheck(res));
    		return false;
    	}

    	return true;
	}
	dlog_print(DLOG_INFO,"DIT","NULL module");
	return false;

}


bool setAudioURI (Audio this_gen, char * uri)
{

    if ( this_gen != NULL)
    {
    AudioExtends * this = (AudioExtends *)this_gen;
    player_error_e res =PLAYER_ERROR_NONE;

    if ( NULL == uri )
    {
    	dlog_print(DLOG_INFO,"DIT","NULL URI");
        return false;
    }
    if ( NULL != this->uri )
    {
        free (this->uri);
    }
    this->uri = malloc (strlen (uri) + sizeof (char));
    strcpy (this->uri, uri);

    res = player_set_uri (this->player_handle, this->uri);
	if(res != PLAYER_ERROR_NONE )
	{
		dlog_print(DLOG_INFO,"DIT","%s",PlayerErrorCheck(res));
		return false;
	}

    res = metadata_extractor_set_path (this->audioMetadataHandle, this->uri);
    if(res != PLAYER_ERROR_NONE )
    {
    	dlog_print(DLOG_INFO,"DIT","%s",PlayerErrorCheck(res));
    	return false;
    }
    return true;
    }
	dlog_print(DLOG_INFO,"DIT","NULL module");
    return false;

}

String getAudioInfo (Audio this_gen, metadata_extractor_attr_e metadataKey)
{

	if(this_gen != NULL)
	{
    AudioExtends * this = (AudioExtends *)this_gen;
    metadata_extractor_error_e error_value;

    char * res = NULL;
    error_value = metadata_extractor_get_metadata (this->audioMetadataHandle, metadataKey, &res);

    return res;
	}
	dlog_print(DLOG_INFO,"DIT","NULL module");
	return NULL;
}

Image NewImage ()
{
    ImageExtends * this = (ImageExtends *)malloc (sizeof (ImageExtends));

    this->image.extractInfo = getImageInfo;
    this->imageMetaHandle   = NULL;
    this->image.getBurstId  = getImageBurstId;
    this->image.getMediaId  = getImageMediaId;
    this->image.getDateTaken = getImageDateTaken;
    this->image.getWidth    = getImageWidth;
    this->image.getHeight   = getImageHeight;
    this->height            = -1;
    this->width             = -1;
    this->burst_id          = NULL;
    this->datetaken         = NULL;
    this->media_id          = NULL;

    return &this->image;
}

void DestroyImage (Image this_gen)
{
    if ( this_gen )
    {
        return;
    }

    ImageExtends * this = (ImageExtends *)this_gen;

    if ( this->imageMetaHandle != NULL)
    {
        image_meta_destroy (this->imageMetaHandle);
    }

    if ( this->burst_id )
    {
        free (this->burst_id);
    }
    if ( this->datetaken )
    {
        free (this->datetaken);
    }
    if ( this->media_id )
    {
        free (this->media_id);
    }
    free (this_gen);
}

bool gallery_media_item_cbx (media_info_h media, void * user_data)
{
    media_info_h new_media = NULL;
    media_info_clone (&new_media, media);

    GList ** list = (GList **)user_data;
    *list = g_list_append (*list, new_media);

    return false;
}


bool getImageInfo (Image this_gen, String src)
{
	if(this_gen != NULL)
	{
    GList * all_item_list = NULL; // Include glib.h
    media_info_h         	 media_handle  = NULL;
    media_content_type_e	  media_type   =	0;
    char                      buf[1024]    = {'\0'};
    media_content_error_e     ret          = MEDIA_CONTENT_ERROR_NONE;
    filter_h                  filter       = NULL;
    media_content_collation_e collate_type = MEDIA_CONTENT_COLLATE_NOCASE;
    media_content_order_e     order_type   = MEDIA_CONTENT_ORDER_DESC;

    ImageExtends * this = (ImageExtends *)this_gen;

    media_content_connect ();

    media_filter_create (&filter);

    String filterpath = calloc (strlen (src) + 3, sizeof (char));

    snprintf(filterpath, strlen (src) + 3, "'%s'", src);
    // Set the condition
    snprintf(buf, 1024, "%s = %d AND %s = %s", MEDIA_TYPE, MEDIA_CONTENT_TYPE_IMAGE, MEDIA_PATH, filterpath);

    free (filterpath);
    ret = media_filter_set_condition (filter, buf, collate_type);

    if ( ret != MEDIA_CONTENT_ERROR_NONE )
    {
        media_filter_destroy (filter);
        dlog_print(DLOG_INFO,"DIT",MediaContentErrorCheck(ret));
        return false;
    }
    ret = media_filter_set_order (filter, order_type, MEDIA_DISPLAY_NAME, collate_type);

    if ( ret != MEDIA_CONTENT_ERROR_NONE )
    {

        media_filter_destroy (filter);
        dlog_print(DLOG_INFO,"DIT",MediaContentErrorCheck(ret));
        return false;
    }

    ret = media_info_foreach_media_from_db (filter, gallery_media_item_cbx, &all_item_list);

    if ( ret != MEDIA_CONTENT_ERROR_NONE )
    {
        dlog_print(DLOG_INFO,"DIT",MediaContentErrorCheck(ret));
        return false;
    }
    media_handle = (media_info_h)g_list_nth_data (all_item_list, 0);

    ret = media_info_get_media_id (media_handle, &this->media_id);
    if(ret != MEDIA_CONTENT_ERROR_NONE)
    {
      	g_list_free_full(all_item_list,deletemediaresult);
        dlog_print(DLOG_INFO,"DIT",MediaContentErrorCheck(ret));
        return false;
    }
    if ( media_type == MEDIA_CONTENT_TYPE_IMAGE )
    {

    	ret = media_info_get_image (media_handle, &this->imageMetaHandle);

    	if ( ret != MEDIA_CONTENT_ERROR_NONE )
    	{
    		g_list_free_full(all_item_list,deletemediaresult);
    		dlog_print(DLOG_INFO,"DIT",MediaContentErrorCheck(ret));
    		return false;
    	}

    	ret=image_meta_get_width (this->imageMetaHandle, &this->width);

    	if ( ret != MEDIA_CONTENT_ERROR_NONE )
    	{
    	g_list_free_full(all_item_list,deletemediaresult);
    	dlog_print(DLOG_INFO,"DIT",MediaContentErrorCheck(ret));
    	return false;
    	}

    	ret=image_meta_get_height (this->imageMetaHandle, &this->height);
    	if ( ret != MEDIA_CONTENT_ERROR_NONE )
    	{
    		g_list_free_full(all_item_list,deletemediaresult);
    		dlog_print(DLOG_INFO,"DIT",MediaContentErrorCheck(ret));
    		return false;
    	}

    	if ( this->datetaken )
    	{
    		free (this->datetaken);
    	}

    	ret=image_meta_get_date_taken (this->imageMetaHandle, &this->datetaken);
    	if ( ret != MEDIA_CONTENT_ERROR_NONE )
    	{
    		g_list_free_full(all_item_list,deletemediaresult);
    		dlog_print(DLOG_INFO,"DIT",MediaContentErrorCheck(ret));
    		return false;
    	}

    	if ( this->burst_id )
    	{
    		free (this->burst_id);
    	}
    	ret=	image_meta_get_burst_id (this->imageMetaHandle, &this->burst_id);
    	if ( ret	 != MEDIA_CONTENT_ERROR_NONE )
    	{
    		g_list_free_full(all_item_list,deletemediaresult);
    		dlog_print(DLOG_INFO,"DIT",MediaContentErrorCheck(ret));
    		return false;
    	}
    	media_content_disconnect ();

    	return true;
    }
    else
    {
    	dlog_print(DLOG_INFO,"DIT","not image");
    	return false;
    }

	}
	dlog_print(DLOG_INFO,"DIT","NULL module");
	return false;

}


String getImageBurstId (Image this_gen)
{
    ImageExtends * this = (ImageExtends *)this_gen;

    return this->burst_id;
}

String getImageMediaId (Image this_gen)
{
    ImageExtends * this = (ImageExtends *)this_gen;

    return this->media_id;
}

String getImageDateTaken (Image this_gen)
{
    ImageExtends * this = (ImageExtends *)this_gen;
    return this->datetaken;
}

int getImageWidth (Image this_gen)
{
    ImageExtends * this = (ImageExtends *)this_gen;
    return this->width;
}

int getImageHeight (Image this_gen)
{
    ImageExtends * this = (ImageExtends *)this_gen;
    return this->height;
}

static void player_completed_callback(void* user_data)
{
	player_h player_handle = (player_h)user_data;
	dlog_print(DLOG_INFO,"DIT","player_completed_callback call");
	player_stop(player_handle);
}

const char * PlayerErrorCheck(int ret)
{
	switch(ret){
	case PLAYER_ERROR_NONE:
		return "PLAYER_ERROR_NONE: Successful";

	case PLAYER_ERROR_OUT_OF_MEMORY:
		return "PLAYER_ERROR_OUT_OF_MEMORY: Out of memory";

	case PLAYER_ERROR_INVALID_PARAMETER:
		return "PLAYER_ERROR_INVALID_PARAMETER: Invalid parameter";

	case PLAYER_ERROR_NO_SUCH_FILE:
		return "PLAYER_ERROR_NO_SUCH_FILE: No such file or directory";

	case PLAYER_ERROR_INVALID_OPERATION:
		return "PLAYER_ERROR_INVALID_OPERATION: Invalid operation";

	case PLAYER_ERROR_FILE_NO_SPACE_ON_DEVICE:
		return "PLAYER_ERROR_FILE_NO_SPACE_ON_DEVICE: No space left on the device";

	case PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE:
		return "PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE: Not supported";

	case PLAYER_ERROR_SEEK_FAILED:
		return "PLAYER_ERROR_SEEK_FAILED: Seek operation failure";

	case PLAYER_ERROR_INVALID_STATE:
		return "PLAYER_ERROR_INVALID_STATE: Invalid state";

	case PLAYER_ERROR_NOT_SUPPORTED_FILE:
		return "PLAYER_ERROR_NOT_SUPPORTED_FILE: File format not supported";

	case PLAYER_ERROR_INVALID_URI:
		return "PLAYER_ERROR_INVALID_URI: Invalid URI";

	case PLAYER_ERROR_SOUND_POLICY:
		return "PLAYER_ERROR_SOUND_POLICY: Sound policy error";

	case PLAYER_ERROR_CONNECTION_FAILED:
		return "PLAYER_ERROR_CONNECTION_FAILED: Streaming connection failed";

	case PLAYER_ERROR_VIDEO_CAPTURE_FAILED:
		return "PLAYER_ERROR_VIDEO_CAPTURE_FAILED: Video capture failed";

	case PLAYER_ERROR_DRM_EXPIRED:
		return "PLAYER_ERROR_DRM_EXPIRED: Expired license";

	case PLAYER_ERROR_DRM_NO_LICENSE:
		return "PLAYER_ERROR_DRM_NO_LICENSE: No license";

	case PLAYER_ERROR_DRM_FUTURE_USE:
		return "PLAYER_ERROR_DRM_FUTURE_USE: License for future use";

	case PLAYER_ERROR_DRM_NOT_PERMITTED:
		return "PLAYER_ERROR_DRM_NOT_PERMITTED: Format not permitted";

	case PLAYER_ERROR_RESOURCE_LIMIT:
		return "PLAYER_ERROR_RESOURCE_LIMIT: Resource limit";

	case PLAYER_ERROR_PERMISSION_DENIED:
		return "PLAYER_ERROR_PERMISSION_DENIED: Permission denied";

	default:
		return "UNKNOWN ERROR";
	}

}

const char* MetadataExtractorErrorCheck(int ret)
{
	switch(ret)
	{

	case METADATA_EXTRACTOR_ERROR_NONE:
		return "METADATA_EXTRACTOR_ERROR_NONE: Successful";

	case METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER:
		return "METADATA_EXTRACTOR_ERROR_INVALID_PARAMETER: Invalid parameter";

	case METADATA_EXTRACTOR_ERROR_OUT_OF_MEMORY:
		return "METADATA_EXTRACTOR_ERROR_OUT_OF_MEMORY: Out of memory";

	case METADATA_EXTRACTOR_ERROR_FILE_EXISTS:
		return "METADATA_EXTRACTOR_ERROR_FILE_EXISTS: File does not exist";

	case METADATA_EXTRACTOR_ERROR_PERMISSION_DENIED:
		return "METADATA_EXTRACTOR_ERROR_PERMISSION_DENIED: Permission denied";

	case METADATA_EXTRACTOR_ERROR_OPERATION_FAILED:
		return "METADATA_EXTRACTOR_ERROR_OPERATION_FAILED: Invalid internal operation";

	default:
		return "UNKNOWN ERROR";
	}
}

const char * MediaContentErrorCheck(int ret)
{
	switch(ret)
	{
	case MEDIA_CONTENT_ERROR_NONE:
		return "MEDIA_CONTENT_ERROR_NONE: Successful";

	case MEDIA_CONTENT_ERROR_INVALID_PARAMETER:
		return "MEDIA_CONTENT_ERROR_INVALID_PARAMETER: Invalid parameter";

	case MEDIA_CONTENT_ERROR_OUT_OF_MEMORY:
		return "MEDIA_CONTENT_ERROR_OUT_OF_MEMORY: Out of memory";

	case MEDIA_CONTENT_ERROR_INVALID_OPERATION:
		return "MEDIA_CONTENT_ERROR_INVALID_OPERATION: Invalid Operation";

	case MEDIA_CONTENT_FILE_NO_SPACE_ON_DEVICE:
		return "MEDIA_CONTENT_FILE_NO_SPACE_ON_DEVICE: No space left on device";

	case MEDIA_CONTENT_ERROR_PERMISSION_DENIED:
		return "MEDIA_CONTENT_ERROR_PERMISSION_DENIED: Permission denied";

	case MEDIA_CONTENT_ERROR_DB_FAILED:
		return "MEDIA_CONTENT_ERROR_DB_FAILED: DB operation failed";

	case MEDIA_CONTENT_ERROR_DB_BUSY:
		return "MEDIA_CONTENT_ERROR_DB_BUSY: DB operation BUSY";

	case MEDIA_CONTENT_ERROR_NETWORK:
		return "MEDIA_CONTENT_ERROR_NETWORK: Network Fail";

	case MEDIA_CONTENT_ERROR_UNSUPPORTED_CONTENT:
		return "MEDIA_CONTENT_ERROR_UNSUPPORTED_CONTENT: Unsupported Content";

	default:
		return "UNKNOWN ERROR";
	}
}
