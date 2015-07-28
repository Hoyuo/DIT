/*! @file	NFC.c
 *  @brief	NFC API가 정의되어있다.
 *  @note	NFC API가 정의되어있다.
 *  @see	NFC.h
*/


#include "Commnucation/NFC.h"

#include <stdlib.h>
#include <string.h>
#include <system_info.h>
#include <nfc.h>
#include <app_control.h>

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
        NFCExtends * this = (NFCExtends *)this_gen;

        bool ret;
        system_info_get_platform_bool ("http://tizen.org/feature/network.nfc", &ret);

        if ( ret == true )
        {
            nfc_manager_set_tag_filter (NFC_TAG_FILTER_ALL_ENABLE);
        }
        this->access = ret;

        return ret;
    }
    return false;
}

bool onNFCConnect (NFC this_gen)
{
    if ( this_gen != NULL)
    {
        NFCExtends * this = (NFCExtends *)this_gen;

        bool access = this->access;
        bool ret    = true;

        if ( access == false )
        {
            int r;
            nfc_manager_initialize ();
            nfc_manager_is_supported ();

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
                    ret = false;
                }
            }
        }
        return ret;
    }
    return false;
}

bool onNFCDisconnect (NFC this_gen)
{
    if ( this_gen != NULL)
    {
        NFCExtends * this = (NFCExtends *)this_gen;

        bool access = this->access;
        bool ret    = false;

        if ( access == true )
        {
            nfc_manager_deinitialize ();
            ret = true;
        }

        return ret;
    }
    return false;
}

void NFCSend (NFC this_gen, NDEF message)
{
    if ( this_gen != NULL)
    {
        NFCExtends * this = (NFCExtends *)this_gen;

        bool access = this->access;
        bool ret    = true;

        if ( access == true )
        {
            nfc_ndef_message_h ndef_message = NULL;
            nfc_ndef_message_create (&ndef_message);

            if ( strcmp (message.tag, "TEXT") == 0 )
            {
                nfc_ndef_record_create_text (&ndef_message, message.msg, "en-US", NFC_ENCODE_UTF_8);
            }
            else if ( strcmp (message.tag, "URI") == 0 )
            {
                nfc_ndef_record_create_uri (&ndef_message, message.msg);
            }
            else if ( strcmp (message.tag, "MIME") == 0 )
            {
                nfc_ndef_record_create_mime (&ndef_message, "image/jpeg", message.msg, sizeof (message.msg));
            }
            else
            {
                return;
            }

            nfc_tag_h tag;
            nfc_tag_write_ndef (tag, ndef_message, NULL, NULL);

            nfc_ndef_record_destroy (&ndef_message);
        }
    }
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
    }
    return ret;
}
