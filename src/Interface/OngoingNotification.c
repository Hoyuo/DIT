/*! @file	OngoingNotification.c
 *  @brief	Ongoing Notification API가 정의되어있다.
 *  @note	Ongoing Notification API가 정의되어있다.
 *  @see	OngoingNotification.h
*/


#include "Interface/OngoingNotification.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <dlog.h>
#include <notification.h>

OngoingNotification NewOngoingNotification (void)
{
    OngoingNotificationExtend * this;

    this = (OngoingNotificationExtend *)malloc (sizeof (OngoingNotificationExtend));

    this->Ongoingnotification.Show        = OngoingNotificationShow;
    this->Ongoingnotification.Hide        = OngoingNotificationHide;
    this->Ongoingnotification.setTitle    = setOngoingNotificationTitle;
    this->Ongoingnotification.setText     = setOngoingNotificationText;
    this->Ongoingnotification.setIcon     = setOngoingNotificationIcon;
    this->Ongoingnotification.setSound    = setOngoingNotificationSound;
    this->Ongoingnotification.setProgress = setOngoingNotificationProgress;
    this->Ongoingnotification.update      = updateOngoingNotification;

    this->ongoingnotification_handle = notification_create (NOTIFICATION_TYPE_ONGOING);
    this->title                      = NULL;
    this->text                       = NULL;
    this->imagePath                  = NULL;
    this->soundPath                  = NULL;
    this->visible                    = false;

    notification_set_display_applist (this->ongoingnotification_handle, NOTIFICATION_DISPLAY_APP_NOTIFICATION_TRAY | NOTIFICATION_DISPLAY_APP_TICKER);

    return &this->Ongoingnotification;
}

void DestroyOngoingNotification (OngoingNotification this_gen)
{
    if ( this_gen != NULL)
    {

        OngoingNotificationExtend * this = (OngoingNotificationExtend *)this_gen;

        if ( NULL != this->title )
        {
            free (this->title);
        }

        if ( NULL != this->text )
        {
            free (this->text);
        }

        if ( NULL != this->imagePath )
        {
            free (this->imagePath);
        }

        if ( NULL != this->soundPath )
        {
            free (this->soundPath);
        }

        if ( this->visible )
        {
            notification_delete (this->ongoingnotification_handle);
            this->visible = false;
        }

        if ( NULL != this->ongoingnotification_handle )
        {
            notification_free (this->ongoingnotification_handle);
        }

        free (this);
    }
}

bool OngoingNotificationShow (OngoingNotification this_gen)
{
    if ( this_gen != NULL)
    {
        OngoingNotificationExtend * this = (OngoingNotificationExtend *)this_gen;
        notification_error_e ret = NOTIFICATION_ERROR_NONE;

        ret = notification_post (this->ongoingnotification_handle);
        if ( ret != NOTIFICATION_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", OngoingNotificationErrorCheck (ret));
            return false;
        }
        this->visible = true;
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool OngoingNotificationHide (OngoingNotification this_gen)
{
    if ( this_gen != NULL)
    {
        OngoingNotificationExtend * this = (OngoingNotificationExtend *)this_gen;
        notification_error_e ret = NOTIFICATION_ERROR_NONE;

        ret = notification_delete (this->ongoingnotification_handle);
        if ( ret != NOTIFICATION_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", OngoingNotificationErrorCheck (ret));
            return false;
        }
        this->visible = false;
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool setOngoingNotificationTitle (OngoingNotification this_gen, String title)
{
    if ( this_gen != NULL)
    {
        OngoingNotificationExtend * this = (OngoingNotificationExtend *)this_gen;

        if ( NULL == title )
        {
            dlog_print (DLOG_INFO, "DIT", "NULL Title");
            return false;
        }

        if ( NULL != this->title )
        {
            free (this->title);
        }

        this->title = malloc (strlen (title) + sizeof (char));
        strcpy(this->title, title);
        notification_error_e ret = NOTIFICATION_ERROR_NONE;
        ret = notification_set_text (this->ongoingnotification_handle, NOTIFICATION_TEXT_TYPE_TITLE, this->title, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
        if ( ret != NOTIFICATION_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", OngoingNotificationErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool setOngoingNotificationText (OngoingNotification this_gen, String text)
{
    if ( this_gen != NULL)
    {
        OngoingNotificationExtend * this = (OngoingNotificationExtend *)this_gen;

        if ( NULL == text )
        {
            dlog_print (DLOG_INFO, "DIT", "NULL Text");
            return false;
        }

        if ( NULL != this->text )
        {
            free (this->text);
        }

        this->text = malloc (strlen (text) + sizeof (char));
        strcpy(this->text, text);

        notification_error_e ret = NOTIFICATION_ERROR_NONE;
        ret = notification_set_text (this->ongoingnotification_handle, NOTIFICATION_TEXT_TYPE_CONTENT, this->text, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
        if ( ret != NOTIFICATION_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", OngoingNotificationErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool setOngoingNotificationIcon (OngoingNotification this_gen, String imagePath)
{
    if ( this_gen != NULL)
    {

        OngoingNotificationExtend * this = (OngoingNotificationExtend *)this_gen;

        if ( NULL == imagePath )
        {
            dlog_print (DLOG_INFO, "DIT", "NULL Iconpath");
            return false;
        }

        if ( NULL != this->imagePath )
        {
            free (this->imagePath);
        }

        this->imagePath = malloc (strlen (imagePath) + sizeof (char));
        strcpy(this->imagePath, imagePath);

        notification_error_e ret = NOTIFICATION_ERROR_NONE;
        ret = notification_set_image (this->ongoingnotification_handle, NOTIFICATION_IMAGE_TYPE_ICON, this->imagePath);
        if ( ret != NOTIFICATION_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", OngoingNotificationErrorCheck (ret));
            return false;
        }
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool setOngoingNotificationSound (OngoingNotification this_gen, String soundPath)
{
    if ( this_gen != NULL)
    {

        OngoingNotificationExtend * this = (OngoingNotificationExtend *)this_gen;

        if ( NULL == soundPath )
        {
            dlog_print (DLOG_INFO, "DIT", "NULL Soundpath");
            return false;
        }

        if ( NULL != this->soundPath )
        {
            free (this->soundPath);
        }

        this->soundPath = malloc (strlen (soundPath) + sizeof (char));
        strcpy(this->soundPath, soundPath);
        notification_error_e ret = NOTIFICATION_ERROR_NONE;
        notification_set_sound (this->ongoingnotification_handle, NOTIFICATION_SOUND_TYPE_USER_DATA, this->soundPath);
        if ( ret != NOTIFICATION_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", OngoingNotificationErrorCheck (ret));
            return false;
        }
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool setOngoingNotificationProgress (OngoingNotification this_gen, double progress)
{
    if ( this_gen != NULL)
    {
        OngoingNotificationExtend * this = (OngoingNotificationExtend *)this_gen;

        notification_error_e ret = NOTIFICATION_ERROR_NONE;
        ret = notification_set_progress (this->ongoingnotification_handle, progress);
        if ( ret != NOTIFICATION_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", OngoingNotificationErrorCheck (ret));
            return false;
        }
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool updateOngoingNotification (OngoingNotification this_gen)
{
    if ( this_gen != NULL)
    {
        OngoingNotificationExtend * this = (OngoingNotificationExtend *)this_gen;
        notification_error_e ret = NOTIFICATION_ERROR_NONE;
        ret = notification_update (this->ongoingnotification_handle);
        if ( ret != NOTIFICATION_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", OngoingNotificationErrorCheck (ret));
            return false;
        }
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

const char * OngoingNotificationErrorCheck (int errCode)
{
    switch (errCode)
    {
    case NOTIFICATION_ERROR_NONE :
        return "NOTIFICATION_ERROR_NONE : Success";

    case NOTIFICATION_ERROR_INVALID_PARAMETER :
        return "NOTIFICATION_ERROR_INVALID_PARAMETER : Invalid parameter";

    case NOTIFICATION_ERROR_OUT_OF_MEMORY:
        return "NOTIFICATION_ERROR_OUT_OF_MEMORY : Out of memory";

    case NOTIFICATION_ERROR_IO_ERROR :
        return "NOTIFICATION_ERROR_IO_ERROR : I/O error";

    case NOTIFICATION_ERROR_PERMISSION_DENIED :
        return "NOTIFICATION_ERROR_PERMISSION_DENIED : Permission denied";

    case NOTIFICATION_ERROR_FROM_DB:
        return "NOTIFICATION_ERROR_FROM_DB : Error from DB query";

    case NOTIFICATION_ERROR_ALREADY_EXIST_ID:
        return "NOTIFICATION_ERROR_ALREADY_EXIST_ID : Already exist private ID";

    case NOTIFICATION_ERROR_FROM_DBUS :
        return "NOTIFICATION_ERROR_FROM_DBUS Error from DBus";

    case NOTIFICATION_ERROR_NOT_EXIST_ID:
        return "NOTIFICATION_ERROR_NOT_EXIST_ID Not exist private ID";

    case NOTIFICATION_ERROR_SERVICE_NOT_READY:
        return "NOTIFICATION_ERROR_SERVICE_NOT_READY : No response from notification service";

    default:
        return "NOTIFICATION_ERROR_UNKNOWN";
    }
}
