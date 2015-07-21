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
/*
 *
 * @brief
 * @remark privilege:  http://tizen.org/privilege/mediastorage http://tizen.org/privilege/display/externalstorage needed
 *
 * */
File NewFile ()
{
	File this = malloc (sizeof (struct _File));

	this->Delete = deleteFile;
	this->Copy   = copyFile;
	this->Move   = moveFile;
	this->Search = searchFile;
	this->deleteSearchedList =deleteSearchedList;
	return this;
}

void DestroyFile (File this_gen)
{
	if ( NULL != this_gen )
	{
		free (this_gen);
	}
}
void deleteFile(String src){

	if(src!=NULL){
		remove(src);
	}

}

void moveFile (String src, String dst)
{
	rename(src,dst);
}

void copyFile (String src, String dst)
{
	char buff[BUFSIZ];
	FILE *in, *out;
	size_t n;

	in = fopen( src, "rb" );
	out= fopen( dst, "wb" );
	while ( (n=fread(buff,1,BUFSIZ,in)) != 0 ) {
		fwrite( buff, 1, n, out );
	}
	fclose(in);
	fclose(out);
}



// file search recursion Function using GList
void search_recur(String src, String dest,GList** searchList)
{

	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(src)) == NULL) {
		return;
	}

	chdir(src);

	while((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode))
		{

			/* Found a directory, but ignore . and .. */
			if(strcmp(".",entry->d_name) == 0 ||strcmp("..",entry->d_name) == 0)
				continue;
			if(strcmp(entry->d_name,dest)==0)
			{
				String pPath =realpath(entry->d_name,NULL);
				*searchList= g_list_append(*searchList,(gpointer)pPath);
			}

			/* Recurse at a new indent level */
			search_recur(entry->d_name,dest,searchList);

		}
		else if(strcmp(entry->d_name,dest)==0)
		{
			char* pPath =realpath(entry->d_name,NULL);
			*searchList= g_list_append(*searchList,(gpointer)pPath);

		}
	}
	chdir("..");
	closedir(dp);
}

GList* searchFile (String src, String dst)
{
	//todo : working
	GList * searchList=NULL;
	search_recur(src,dst,&searchList);

	return searchList;
}

//callbacking function
void deleteSearchListElement(gpointer data){

	free(data);

}

void deleteSearchedList(GList* searchList){

	g_list_free_full(searchList,deleteSearchListElement);

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
	res = player_set_display (this->player_handle, PLAYER_DISPLAY_TYPE_EVAS, GET_DISPLAY (this->EvasObject));

	res = player_set_display_mode (this->player_handle, PLAYER_DISPLAY_MODE_ORIGIN_OR_LETTER);

	res = player_prepare (this->player_handle);

	res = player_start (this->player_handle);
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
/**
 *	@brief for use this function, caller must import <metadata_extractor.h>
 *
 *	@remark return value must be free()
 */
String getVideoInfo (Video this_gen, metadata_extractor_attr_e element)
{
	VideoExtends * this = (VideoExtends *)this_gen;
	String resultInfo;

	metadata_extractor_get_metadata(this->videoMetadataHandle,element,&resultInfo);

	return resultInfo;
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

	res = player_prepare (this->player_handle);

	res = player_start (this->player_handle);
}

void pauseAudio (Audio this_gen)
{
	player_error_e res;

	AudioExtends * this = (AudioExtends *)this_gen;
	res = player_pause (this->player_handle);

}

void stopAudio (Audio this_gen)
{
	player_error_e res;

	AudioExtends * this = (AudioExtends *)this_gen;
	res = player_stop (this->player_handle);

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
	ImageExtends * this = (ImageExtends *)malloc (sizeof (ImageExtends));

	this->image.extractInfo = getImageInfo;
	this->imageMetaHandle =NULL;
	this->image.getBurstId	=getImageBurstId;
	this->image.getMediaId	=getImageMediaId;
	this->image.getDateTaken=getImageDateTaken;
	this->image.getWidth	=getImageWidth;
	this->image.getHeight	=getImageHeight;
	this->height =-1;
	this->width =-1;
	this->burst_id =NULL;
	this->datetaken =NULL;
	this->media_id=NULL;

	return &this->image;
}

void DestroyImage (Image this_gen)
{
	if ( this_gen )
	{
		return;
	}

	ImageExtends* this = (ImageExtends*)this_gen;

	if(this->imageMetaHandle !=NULL)
	{
		image_meta_destroy(this->imageMetaHandle);
	}

	if(this->burst_id) 	free(this->burst_id);
	if(this->datetaken) free(this->datetaken);
	if(this->media_id)	free(this->media_id);
	free (this_gen);
}


bool gallery_media_item_cbx(media_info_h media, void *user_data)
{
	media_info_h new_media = NULL;
	media_info_clone(&new_media, media);

	GList **list = (GList**)user_data;
	*list = g_list_append(*list, new_media);

	return false;
}


// @param[in] src fullpath of image

void getImageInfo (Image this_gen, String src)
{
	media_content_connect();


	GList *all_item_list = NULL; // Include glib.h
	media_content_type_e media_type =MEDIA_CONTENT_COLLATE_DEFAULT;
	media_info_h media_handle = NULL;

	char buf[1024] = {'\0'};
	int ret = MEDIA_CONTENT_ERROR_NONE;
	filter_h filter = NULL;
	media_content_collation_e collate_type = MEDIA_CONTENT_COLLATE_NOCASE;
	media_content_order_e order_type = MEDIA_CONTENT_ORDER_DESC;

	ImageExtends* this = (ImageExtends*)this_gen;
	media_filter_create(&filter);

	String filterpath = calloc(strlen(src)+3,sizeof(char));

	snprintf(filterpath,strlen(src)+3,"'%s'\0",src);
	// Set the condition
	snprintf(buf, 1024, "%s = %d AND %s = %s", MEDIA_TYPE, MEDIA_CONTENT_TYPE_IMAGE,MEDIA_PATH,filterpath);

	free(filterpath);
	ret = media_filter_set_condition(filter, buf, collate_type);
	if (ret != MEDIA_CONTENT_ERROR_NONE)
	{
		media_filter_destroy(filter);

		return ;
	}
	ret = media_filter_set_order(filter, order_type, MEDIA_DISPLAY_NAME, collate_type);
	if (ret != MEDIA_CONTENT_ERROR_NONE)
	{
		media_filter_destroy(filter);

		return ;
	}

	ret = media_info_foreach_media_from_db(filter, gallery_media_item_cbx, &all_item_list);
	if (ret != MEDIA_CONTENT_ERROR_NONE)
	{
		return ;
	}
	else
	{
		media_handle = (media_info_h)g_list_nth_data(all_item_list, 0);

		media_info_get_media_id(media_handle, &this->media_id);



		if (media_type == MEDIA_CONTENT_TYPE_IMAGE)
		{
			image_meta_h image_handle;

			ret = media_info_get_image(media_handle, &image_handle);
			if (ret != MEDIA_CONTENT_ERROR_NONE)
			{
				// Error handling
			}
			else
			{
				image_meta_get_width(image_handle, &this->width);

				image_meta_get_height(image_handle, &this->height);


				if(this->datetaken) free(this->datetaken);
				image_meta_get_date_taken(image_handle, &this->datetaken);

				if(this->burst_id) 	free(this->burst_id);
				image_meta_get_burst_id(image_handle, &this->burst_id);

			}

		}
	}
	media_content_disconnect();
}
String  getImageBurstId (Image this_gen){
	ImageExtends* this = (ImageExtends*)this_gen;

	return this->burst_id;
}
String  getImageMediaId (Image this_gen){
	ImageExtends* this = (ImageExtends*)this_gen;

	return this->media_id;
}
String  getImageDateTaken (Image this_gen){
	ImageExtends* this = (ImageExtends*)this_gen;
	return this->datetaken;
}

int		getImageWidth(Image this_gen){
	ImageExtends* this = (ImageExtends*)this_gen;
	return this->width;
}
int 	getImageHeight(Image this_gen){
	ImageExtends* this = (ImageExtends*)this_gen;
	return this->height;
}
