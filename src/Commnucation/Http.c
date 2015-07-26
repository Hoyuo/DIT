#include "Commnucation/Http.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <curl.h>
#include <system_info.h>

static size_t write_callback (void * contents, size_t size, size_t nmemb, void ** res);
static size_t write_data (void * ptr, size_t size, size_t nmemb, FILE * stream);

/*
 * @privlevel public
 * @privilege %http://tizen.org/privilege/internet
 */

Http NewHttp (void)
{
    HttpExtends * this = (HttpExtends *)malloc (sizeof (HttpExtends));

    this->http.isAccessible = isHttpAccessible;
    this->http.onConnect    = onHttpConnect;
    this->http.onDisconnect = onHttpDisconnect;
    this->http.Download     = HttpDownload;
    this->http.Get          = HttpExcuteGet;
    this->http.Post         = HttpExcutePost;

    this->url  = NULL;
    this->port = 80;

    this->access = false;
    this->conect = false;

    return &this->http;
}

void DestoryHttp (Http this_gen)
{
    if ( this_gen != NULL)
    {
        HttpExtends * this = (HttpExtends *)this_gen;

        if ( this->url != NULL)
        {
            free (this->url);
        }

        free (this);
    }
}

bool isHttpAccessible (Http this_gen)
{
    if ( this_gen != NULL)
    {
        HttpExtends * this = (HttpExtends *)this_gen;

        bool check1, check2;

        system_info_get_platform_bool ("http://tizen.org/feature/network.wifi", &check1);
        system_info_get_platform_bool ("http://tizen.org/feature/network.telephony", &check2);

        this->access = check1 || check2;
        return this->access;
    }
    return false;
}

bool onHttpConnect (Http this_gen, String url, int port)
{
    if ( this_gen != NULL)
    {
        HttpExtends * this = (HttpExtends *)this_gen;

        if ( this->access )
        {
            int lenght = strlen (url);
            if(this->url != NULL)
            {
            	free(this->url);
            }
            this->url = (String)malloc (lenght + 1);
            strcpy(this->url, url);
            this->port = port;

            CURL * curl;
            CURLcode r;
            curl_global_init (CURL_GLOBAL_ALL);

            curl = curl_easy_init ();
            if ( curl )
            {
                curl_easy_setopt (curl, CURLOPT_URL, url);
                curl_easy_setopt (curl, CURLOPT_PORT, port);

                r = curl_easy_perform (curl);

                if ( r == CURLE_OK )
                {
                    this->conect = true;
                    return true;
                }
            }
        }
    }
    return false;
}

bool onHttpDisconnect (Http this_gen)
{
    if ( this_gen != NULL)
    {
        HttpExtends * this = (HttpExtends *)this_gen;

        if ( this->access )
        {
            if ( this->url != NULL)
            {
                free (this->url);
                this->url = NULL;
            }

            this->conect = false;
            return true;
        }
    }
    return false;
}

/*
 * @privlevel public
 * @privilege %http://tizne.org/privileges/mediastorage
 * @privilege %http://tizne.org/privileges/download
 */
void HttpDownload (Http this_gen, String filename)
{
    if ( this_gen != NULL)
    {
        HttpExtends * this = (HttpExtends *)this_gen;

        if ( this->conect )
        {
            String path = (String)malloc (FILENAME_MAX);
            strcpy(path, "/opt/usr/media/Downloads/");
            strcat(path, filename);

            String url = (String)malloc (FILENAME_MAX);
            strcpy(url, this->url);
            strcat(url, "/");
            strcat(url, filename);

            CURL * curl = curl_easy_init ();
            if ( curl )
            {
                FILE * fp = fopen (path, "wb");
                curl_easy_setopt (curl, CURLOPT_URL, url);
                curl_easy_setopt (curl, CURLOPT_PORT, this->port);
                curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, write_data);
                curl_easy_setopt (curl, CURLOPT_WRITEDATA, fp);
                curl_easy_perform (curl);
                /* always cleanup */
                curl_easy_cleanup (curl);
                fclose (fp);
            }
            free (url);
            free (path);
        }
    }
}

void HttpExcutePost (Http this_gen, String req, String * res)
{
    if ( this_gen != NULL)
    {
        HttpExtends * this = (HttpExtends *)this_gen;

        if ( this->conect )
        {
            CURL * curl;
            CURLcode r;

            curl = curl_easy_init ();
            if ( curl )
            {
                curl_easy_setopt (curl, CURLOPT_URL, this->url);
                curl_easy_setopt (curl, CURLOPT_PORT, this->port);
                curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, write_callback);
                curl_easy_setopt (curl, CURLOPT_POSTFIELDSIZE, (long)strlen (req) );
                curl_easy_setopt (curl, CURLOPT_POSTFIELDS, req);
                curl_easy_setopt (curl, CURLOPT_WRITEDATA, res);

                r = curl_easy_perform (curl);
                curl_easy_cleanup (curl);
            }
            curl_global_cleanup ();
        }
    }
}

void HttpExcuteGet (Http this_gen, String req, String * res)
{
    if ( this_gen != NULL)
    {
        HttpExtends * this = (HttpExtends *)this_gen;

        if ( this->conect )
        {
            CURL * curl;
            CURLcode r;

            curl = curl_easy_init ();
            if ( curl )
            {
            	String url = (String)malloc (FILENAME_MAX);
            	strcpy(url, this->url);
            	strcat(url, "/");
            	strcat(url, req);

            	curl_easy_setopt (curl, CURLOPT_URL, url);
                curl_easy_setopt (curl, CURLOPT_PORT, this->port);
                curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, write_callback);
                curl_easy_setopt (curl, CURLOPT_WRITEDATA, res);

                r = curl_easy_perform (curl);
                curl_easy_cleanup (curl);
                free(url);
            }
            curl_global_cleanup ();
        }
    }
}

static size_t write_callback (void * contents, size_t size, size_t nmemb, void ** res)
{
    size_t realsize = size * nmemb;
    *res = (String)malloc (realsize + 1);
    strcpy(*res, contents);
    return realsize;
}

static size_t write_data (void * ptr, size_t size, size_t nmemb, FILE * stream)
{
    size_t written = fwrite (ptr, size, nmemb, stream);
    return written;
}

const char * HttpErrorCheck (CURLcode errorCode)
{
    return curl_easy_strerror (errorCode);
}
