/*! @file	NFC.c
 *  @brief	NFC API가 정의되어있다.
 *  @note	NFC API가 정의되어있다.
 *  @see	NFC.h 
 */


#include "Commnucation/NFC.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <system_info.h>
#include <nfc.h>
#include <app_control.h>
#include <dlog.h>

NDEF CreateNDEF (String tag, String msg)
{
    NDEF ndef = {0, 0};

    ndef.tag = (String)malloc (strlen (tag) + 1);
    strcpy(ndef.tag, tag);

    ndef.msg = (String)malloc (strlen (msg) + 1);
    strcpy(ndef.msg, msg);

    return ndef;
}

void DeleteNDEF (NDEF * ndef)
{
    if ( ndef != NULL)
    {
        if ( ndef->tag != NULL)
        {
            free (ndef->tag);
        }

        if ( ndef->msg != NULL)
        {
            free (ndef->msg);
        }
    }
}

NFC NewNFC ()
{
    NFCExtends * this = (NFCExtends *)malloc (sizeof (NFCExtends));

    this->nfc.isAccessible = isNFCAccessible;
    this->nfc.onConnect    = onNFCConnect;
    this->nfc.onDisconnect = onNFCDisconnect;
    this->nfc.Send         = NFCSend;
    this->nfc.Recv         = NFCRecv;

    return &this->nfc;
}

void DestoryNFC (NFC this_gen)
{
    if ( this_gen != NULL)
    {
        NFCExtends * this = (NFCExtends *)this_gen;

        DeleteNDEF (&this->ndefMessage);
        free (this);
    }
}

bool isNFCAccessible (NFC this_gen)
{
    if ( this_gen != NULL)
    {
        NFCExtends  * this = (NFCExtends *)this_gen;

        bool ret;
        nfc_error_e res    = NFC_ERROR_NONE;
        system_info_get_platform_bool ("http://tizen.org/feature/network.nfc", &ret);

        if ( ret == true )
        {
            nfc_manager_set_tag_filter (NFC_TAG_FILTER_ALL_ENABLE);

        }
        this->access = ret;

        return ret;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool onNFCConnect (NFC this_gen)
{
    if ( this_gen != NULL)
    {
        NFCExtends * this = (NFCExtends *)this_gen;

        bool access = this->access;
        bool ret = true;

        if ( access == false )
        {
            int         r;
            nfc_error_e res = NFC_ERROR_NONE;
            res = nfc_manager_is_supported ();
            if ( res != NFC_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "NFC Not supported");
                return false;
            }
            nfc_manager_initialize ();

            //NFC 메니저 생성
            app_control_h service = NULL;
            app_control_create (&service);

            //app_control 생성
            app_control_set_operation (service, "http://tizen.org/appcontrol/operation/setting/nfc");
            app_control_add_extra_data (service, "type", "nfc");
            r = app_control_send_launch_request (service, NULL, NULL);
            //NFC 켜기
            if ( r != APP_CONTROL_ERROR_NONE )
            {
                ret = false;
            }
            app_control_destroy (service);

            nfc_manager_set_tag_filter (NFC_TAG_FILTER_ALL_ENABLE);

            if ( nfc_manager_is_system_handler_enabled () != true )
            {
                if ( nfc_manager_set_system_handler_enable (true) == NFC_ERROR_NONE )
                {
                    ret = true;
                }
                else
                {
                    dlog_print (DLOG_INFO, "DIT", "%s", "can't activate NFC");
                    ret = false;
                }
            }
        }
        else
        {
            dlog_print (DLOG_INFO, "DIT", "%s", "can't accessible");
        }
        return ret;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool onNFCDisconnect (NFC this_gen)
{
    if ( this_gen != NULL)
    {
        NFCExtends * this = (NFCExtends *)this_gen;

        bool access = this->access;
        bool ret = false;

        if ( access == true )
        {
            nfc_error_e nfcerror = NFC_ERROR_NONE;
            nfcerror = nfc_manager_deinitialize ();
            if ( nfcerror != NFC_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "%s", NFCErrorChecker (nfcerror));
            }
            ret = true;
        }
        else
        {
            dlog_print (DLOG_INFO, "DIT", "%s", "can't accessible");
        }

        return ret;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool NFCSend (NFC this_gen, NDEF message)
{
    if ( this_gen != NULL)
    {
        NFCExtends * this = (NFCExtends *)this_gen;

        bool access = this->access;
        bool ret = true;

        if ( access == true )
        {
            nfc_ndef_message_h ndef_message = NULL;
            nfc_error_e        ret          = NFC_ERROR_NONE;
            ret = nfc_ndef_message_create (&ndef_message);
            if ( ret != NFC_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "%s", NFCErrorChecker (ret));
                return false;
            }

            if ( strcmp (message.tag, "TEXT") == 0 )
            {
                ret = nfc_ndef_record_create_text (&ndef_message, message.msg, "en-US", NFC_ENCODE_UTF_8);
                if ( ret != NFC_ERROR_NONE )
                {
                    dlog_print (DLOG_INFO, "DIT", "%s", NFCErrorChecker (ret));
                    return false;
                }
            }
            else if ( strcmp (message.tag, "URI") == 0 )
            {
                ret = nfc_ndef_record_create_uri (&ndef_message, message.msg);
                if ( ret != NFC_ERROR_NONE )
                {
                    dlog_print (DLOG_INFO, "DIT", "%s", NFCErrorChecker (ret));
                    return false;
                }
            }
            else if ( strcmp (message.tag, "MIME") == 0 )
            {
                ret = nfc_ndef_record_create_mime (&ndef_message, "image/jpeg", message.msg, sizeof (message.msg));
                if ( ret != NFC_ERROR_NONE )
                {
                    dlog_print (DLOG_INFO, "DIT", "%s", NFCErrorChecker (ret));
                    return false;
                }
            }
            else
            {
                dlog_print (DLOG_INFO, "DIT", "NFC_ERROR_NOT_NDEF_FORMAT: Not NDEF format Tag");
                return false;
            }

            nfc_tag_h tag;
            ret = nfc_tag_write_ndef (tag, ndef_message, NULL, NULL);
            if ( ret != NFC_ERROR_NONE )
            {
                dlog_print (DLOG_INFO, "DIT", "%s", NFCErrorChecker (ret));
                return false;
            }

            nfc_ndef_record_destroy (&ndef_message);
        }
        else
        {
            dlog_print (DLOG_INFO, "DIT", "%s", "can't accessible");
        }
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

NDEF NFCRecv (NFC this_gen)
{
    NDEF ret = {0, 0};
    if ( this_gen != NULL)
    {
        NFCExtends * this = (NFCExtends *)this_gen;
        bool access = this->access;

        if ( access == true )
        {
            nfc_tag_h tag;
            nfc_tag_read_ndef (tag, NULL, NULL);

            char tagChar[1000];
            int  tagLength;

            nfc_ndef_record_get_type (NULL, &tagChar, &tagLength);
            ret.tag = (String)malloc (tagLength + 1);
            strcpy(ret.tag, tagChar);

            char msgChar[1000];
            int  msgLength;

            nfc_ndef_record_get_type (NULL, &msgChar, &msgLength);
            ret.msg = (String)malloc (msgLength + 1);
            strcpy(ret.msg, msgChar);
        }
        else
        {
            dlog_print (DLOG_INFO, "DIT", "%s", "can't accessible");
        }
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return ret;
}

const char * NFCErrorChecker (int errorcode)
{
    switch (errorcode)
    {
    case NFC_ERROR_NONE:
        return "NFC_ERROR_NONE: Successful";

    case NFC_ERROR_OUT_OF_MEMORY:
        return "NFC_ERROR_OUT_OF_MEMORY: Out of memory";

    case NFC_ERROR_OPERATION_FAILED:
        return "NFC_ERROR_OPERATION_FAILED: Operation failed";

    case NFC_ERROR_INVALID_PARAMETER:
        return "NFC_ERROR_INVALID_PARAMETER: Invalid parameter";

    case NFC_ERROR_INVALID_NDEF_MESSAGE:
        return "NFC_ERROR_INVALID_NDEF_MESSAGE: Invalid NDEF message";

    case NFC_ERROR_INVALID_RECORD_TYPE:
        return "NFC_ERROR_INVALID_RECORD_TYPE: Invalid record type";

    case NFC_ERROR_TIMED_OUT:
        return "NFC_ERROR_TIMED_OUT: Timeout error, no answer";

    case NFC_ERROR_DEVICE_BUSY:
        return "NFC_ERROR_DEVICE_BUSY: Previous operation is not finished still busy";

    case NFC_ERROR_NO_DEVICE:
        return "NFC_ERROR_NO_DEVICE: no device";

    case NFC_ERROR_NOT_ACTIVATED:
        return "NFC_ERROR_NOT_ACTIVATED: NFC is not activated";

    case NFC_ERROR_NOT_SUPPORTED:
        return "NFC_ERROR_NOT_SUPPORTED: Not supported";

    case NFC_ERROR_ALREADY_ACTIVATED:
        return "NFC_ERROR_ALREADY_ACTIVATED: Already activated";

    case NFC_ERROR_ALREADY_DEACTIVATED:
        return "NFC_ERROR_ALREADY_DEACTIVATED: Already deactivated";

    case NFC_ERROR_READ_ONLY_NDEF:
        return "NFC_ERROR_READ_ONLY_NDEF: Read only tag";

    case NFC_ERROR_NO_SPACE_ON_NDEF:
        return "NFC_ERROR_NO_SPACE_ON_NDEF: No enough space on tag";

    case NFC_ERROR_NO_NDEF_MESSAGE:
        return "NFC_ERROR_NO_NDEF_MESSAGE: No NDEF Message on Tag";

    case NFC_ERROR_NOT_NDEF_FORMAT:
        return "NFC_ERROR_NOT_NDEF_FORMAT: Not NDEF format Tag";

    case NFC_ERROR_SECURITY_RESTRICTED:
        return "NFC_ERROR_SECURITY_RESTRICTED: Restricted by access control";

    case NFC_ERROR_PERMISSION_DENIED:
        return "NFC_ERROR_PERMISSION_DENIED: Restricted by Smack";

    case NFC_ERROR_ILLEGAL_STATE:
        return "NFC_ERROR_ILLEGAL_STATE: The state is wrong";

    case NFC_ERROR_NOT_INITIALIZED:
        return "NFC_ERROR_NOT_INITIALIZED: NFC is not initialized";

    case NFC_ERROR_TAG_NOT_SUPPORTED:
        return "NFC_ERROR_TAG_NOT_SUPPORTED: Tag is not supported";

    default:
        return "NFC_ERROR_UNKNOWN";
    }
}
