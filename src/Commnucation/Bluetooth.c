/*! @file	Bluetooth.c
 *  @brief	Bluetooth API가 정의되어있다.
 *  @note	Bluetooth API가 정의되어있다.
 *  @see	Bluetooth.h
*/


#include "Commnucation/Bluetooth.h"

#include <stdlib.h>

#include <bluetooth.h>
#include <app_control.h>
#include <dlog.h>
#include <glib.h>

static bool adapter_bonded_device_cbx (bt_device_info_s * device_info, void * user_data);
static void __bt_opp_client_push_responded_cbx (int result, const char * remote_address, void * user_data);
static void __bt_opp_client_push_progress_cbx (const char * file, long long size, int percent, void * user_data);
static void __bt_opp_client_push_finished_cbx (int result, const char * remote_address, void * user_data);
static void adapter_state_changed_cbx (int result, bt_adapter_state_e adapter_state, void * user_data);
static void bt_opp_server_transfer_progress_cb_for_oppx (const char * file, long long size, int percent, void * user_data);
static void bt_opp_server_transfer_finished_cb_for_oppx (int result, const char * file, long long size, void * user_data);
static void connection_requested_cb_for_opp_serverx (const char * remote_address, void * user_data);

Bluetooth NewBluetooth (void)
{
    BluetoothExtends * this = malloc (sizeof (BluetoothExtends));

    this->bluetooth.isAccessible = isBluetoothAccessible;
    this->bluetooth.onConnect    = onBluetoothConnect;
    this->bluetooth.isConnected  = isBluetoothConnected;
    this->bluetooth.onDisconnect = onBluetoothDisconnect;
    this->bluetooth.FileRecv     = BluetoothFileRecv;
    this->bluetooth.FileSend     = BluetoothFileSend;

    this->connected     = false;
    this->accessible    = false;
    this->remoteMACAddr = NULL;

    return &this->bluetooth;
}

void DestroyBluetooth (Bluetooth this_gen)
{
    if ( NULL != this_gen )
    {
        bt_opp_server_deinitialize ();
        bt_adapter_stop_device_discovery ();
        bt_adapter_unset_state_changed_cb ();
        bt_adapter_unset_device_discovery_state_changed_cb ();
        bt_device_unset_service_searched_cb ();
        bt_socket_unset_data_received_cb ();
        bt_socket_unset_connection_state_changed_cb ();
        bt_adapter_unset_visibility_duration_changed_cb ();

        BluetoothExtends * this = (BluetoothExtends *)this_gen;

        if ( this->remoteMACAddr != NULL)
        {
            free (this->remoteMACAddr);
        }
        free (this);
    }
}

bool isBluetoothAccessible (Bluetooth this_gen)
{
    if ( this_gen != NULL)
    {
        BluetoothExtends * this = (BluetoothExtends *)this_gen;

        bool ret;
        system_info_get_platform_bool ("http://tizen.org/feature/network.bluetooth", &ret);

        if ( ret )
        {
            app_control_h service = NULL;
            app_control_create (&service);

            app_control_set_operation (service, "http://tizen.org/appcontrol/operation/edit");
            app_control_set_mime (service, "application/x-bluetooth-on-off");

            int ret = app_control_send_launch_request (service, NULL, NULL);

            app_control_destroy (service);

            bt_adapter_state_e adapter_state;

            int re = bt_adapter_get_state (&adapter_state);

            if ( re == BT_ERROR_NONE )
            {
                this->accessible = true;
                return true;
            }
        }
    }
    return false;
}

bool onBluetoothConnect (Bluetooth this_gen)
{
    dlog_print(DLOG_ERROR,"DIT","%s",BluetoothErrorCheck(0));

	if ( this_gen != NULL)
    {
        BluetoothExtends * this = (BluetoothExtends *)this_gen;

        if ( this->connected==false )
        {
            int res = 0;

            bt_initialize ();

            bt_adapter_set_state_changed_cb (adapter_state_changed_cbx, this);

            bt_adapter_foreach_bonded_device (adapter_bonded_device_cbx, this);

            bt_adapter_start_device_discovery ();

            if ( res == BT_ERROR_NONE )
            {
                this->connected = true;
                return this->connected;
            }
        }

        this->connected = false;

    }
    return false;

}

bool isBluetoothConnected (Bluetooth this_gen)
{
    if ( this_gen != NULL)
    {
        return ((BluetoothExtends *)this_gen)->connected;
    }
    return false;
}

bool onBluetoothDisconnect (Bluetooth this_gen)
{
    dlog_print(DLOG_ERROR,"DIT","%s",BluetoothErrorCheck(0));

    if ( this_gen != NULL)
    {
        BluetoothExtends * this = (BluetoothExtends *)this_gen;

        if ( this->connected )
        {
            int ret = 0;
            bt_opp_server_deinitialize ();
            dlog_print(DLOG_ERROR,"DIT","%s",BluetoothErrorCheck(ret));

             bt_adapter_stop_device_discovery ();

            bt_adapter_unset_state_changed_cb ();

            bt_adapter_unset_device_discovery_state_changed_cb ();

            bt_device_unset_service_searched_cb ();

            bt_socket_unset_data_received_cb ();

            bt_socket_unset_connection_state_changed_cb ();

            bt_adapter_unset_visibility_duration_changed_cb ();

            bt_deinitialize ();

            if ( BT_ERROR_NONE == ret )
            {
                this->connected = false;
                if ( this->remoteMACAddr != NULL)
                {
                    free (this->remoteMACAddr);
                    this->remoteMACAddr = NULL;
                }
                return true;
            }
        }
    }
    return false;
}

/**
 *  @param[in] this_gen assign Bluetooth object
 *  @param[in] recvfile NULLABLE assign filename
 *
 */
void BluetoothFileRecv (Bluetooth this_gen, String * recvBuffer)
{
    //todo 파일만 처리 가능한 상황
    if ( this_gen != NULL)
    {
        BluetoothExtends * this = (BluetoothExtends *)this_gen;

        if ( this->connected )
        {
            int ret = bt_opp_server_initialize_by_connection_request (DOWNLOADSFOLDERPATH, connection_requested_cb_for_opp_serverx, recvBuffer);
        }
    }
}

/**
 *
 *	param[in] sendfilepath fullpath of file to send
 */
void BluetoothFileSend (Bluetooth this_gen, String sendbuffer)
{
    if ( this_gen != NULL)
    {
        BluetoothExtends * this = (BluetoothExtends *)this_gen;

        if ( this->connected )
        {

            int ret = bt_opp_client_initialize ();
            if ( ret != BT_ERROR_NONE )
            {
            	bt_opp_client_deinitialize();
                return;
            }

            ret = bt_opp_client_add_file (sendbuffer);

            if ( ret != BT_ERROR_NONE )
            {
            	bt_opp_client_clear_files ();
            	bt_opp_client_deinitialize();
                return;
            }

            ret = bt_opp_client_push_files (this->remoteMACAddr, __bt_opp_client_push_responded_cbx, __bt_opp_client_push_progress_cbx, __bt_opp_client_push_finished_cbx, NULL);

            if ( ret != BT_ERROR_NONE )
            {
            	bt_opp_client_cancel_push();
            	bt_opp_client_clear_files ();
            	bt_opp_client_deinitialize();
                return;
            }

            ret = bt_opp_client_clear_files ();

            if ( ret != BT_ERROR_NONE )
            {
            	bt_opp_client_deinitialize();
                return;
            }
        	bt_opp_client_deinitialize();

        }
    }
}

//페어링된 Device iter callback
static bool adapter_bonded_device_cbx (bt_device_info_s * device_info, void * user_data)
{
    if ( device_info == NULL)
    {
        return false;
    }

    BluetoothExtends * this = (BluetoothExtends *)user_data;

    if ( this->remoteMACAddr != NULL)
    {
    	free(this->remoteMACAddr);
    }


//        paired_info = (bt_device_info_s *)malloc (sizeof (bt_device_info_s));
//        paired_info->remote_address = strdup (device_info->remote_address);
//        paired_info->remote_name    = strdup (device_info->remote_name);

        size_t size = strlen (device_info->remote_address);
        this->remoteMACAddr = (String)malloc (size + 1);

        strcpy (this->remoteMACAddr, device_info->remote_address);
        dlog_print(DLOG_INFO,"DIT",this->remoteMACAddr);
        return false;
    }

//Data Push
static void __bt_opp_client_push_responded_cbx (int result, const char * remote_address, void * user_data)
{
    dlog_print (DLOG_INFO, "DIT", "result: %s", BluetoothErrorCheck(result));
    dlog_print (DLOG_INFO, "DIT", "remote_address: %s", remote_address);
}

//Data Push
static void __bt_opp_client_push_progress_cbx (const char * file, long long size, int percent, void * user_data)
{
    dlog_print (DLOG_INFO, "DIT", "size: %lld", size);
    dlog_print (DLOG_INFO, "DIT", "percent: %d", percent);
    dlog_print (DLOG_INFO, "DIT", "file: %s", file);
}

//Data Push
static void __bt_opp_client_push_finished_cbx (int result, const char * remote_address, void * user_data)
{
    dlog_print (DLOG_INFO, "DIT", "result: %d", result);
    dlog_print (DLOG_INFO, "DIT", "remote_address: %s", remote_address);
}

//블루투스 연결 가능 체크용 callback
static void adapter_state_changed_cbx (int result, bt_adapter_state_e adapter_state, void * user_data)
{
    BluetoothExtends * this = (BluetoothExtends *)user_data;

    if ( result != BT_ERROR_NONE )
    {
        this->accessible = false;
        return;
    }
    if ( adapter_state == BT_ADAPTER_ENABLED )
    {
        bt_adapter_visibility_mode_e mode;

        int duration = 1;

        bt_adapter_get_visibility (&mode, &duration);

        switch (mode)
        {
        case BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE:
            this->accessible = false;
            break;
        case BT_ADAPTER_VISIBILITY_MODE_GENERAL_DISCOVERABLE:
            this->accessible = true;
            break;
        case BT_ADAPTER_VISIBILITY_MODE_LIMITED_DISCOVERABLE:
            this->accessible = true;
            break;
        }
    }
    else
    {
        this->accessible = false;
    }
}

//Data Recv
static void bt_opp_server_transfer_progress_cb_for_oppx (const char * file, long long size, int percent, void * user_data)
{
    dlog_print (DLOG_INFO, "DIT", "file: %s", file);
    dlog_print (DLOG_INFO, "DIT", "size: %lld", size);
    dlog_print (DLOG_INFO, "DIT", "percent: %d", percent);
}

//Data Recv
static void bt_opp_server_transfer_finished_cb_for_oppx (int result, const char * file, long long size, void * user_data)
{
    dlog_print (DLOG_INFO, "DIT", "result: %d", result);
    dlog_print (DLOG_INFO, "DIT", "file: %s", file);
    dlog_print (DLOG_INFO, "DIT", "size: %lld", size);

    String * recvBuffer = (String *)user_data;

    size_t fileLen = strlen (file);
    size_t downloadLen = strlen (DOWNLOADSFOLDERPATH);
    *recvBuffer = (String)malloc (fileLen + downloadLen + 2);
    strcpy (recvBuffer, DOWNLOADSFOLDERPATH);
    strcat (recvBuffer, "/");
    strcat (recvBuffer, file);
}

//Data Recv
static void connection_requested_cb_for_opp_serverx (const char * remote_address, void * user_data)
{
    bt_error_e ret;

    ret = bt_opp_server_accept (bt_opp_server_transfer_progress_cb_for_oppx, bt_opp_server_transfer_finished_cb_for_oppx, NULL, user_data, NULL);
}

const char * BluetoothErrorCheck (int errCode)
{
    switch (errCode)
    {
    case BT_ERROR_NONE:
        return "BT_ERROR_NONE : Successful";

    case BT_ERROR_CANCELLED:
        return "BT_ERROR_CANCELLED : Operation cancelled";

    case BT_ERROR_INVALID_PARAMETER:
        return "BT_ERROR_INVALID_PARAMETER : Invalid parameter";

    case BT_ERROR_OUT_OF_MEMORY:
        return "BT_ERROR_OUT_OF_MEMORY : Out of memory";

    case BT_ERROR_RESOURCE_BUSY:
        return "BT_ERROR_RESOURCE_BUSY : Device or resource busy";

    case BT_ERROR_TIMED_OUT:
        return "BT_ERROR_TIMED_OUT : Timeout error";

    case BT_ERROR_NOW_IN_PROGRESS :
        return "BT_ERROR_NOW_IN_PROGRESS : Operation now in progress";

    case BT_ERROR_NOT_SUPPORTED:
        return "BT_ERROR_NOT_SUPPORTED : Not Supported";

    case BT_ERROR_PERMISSION_DENIED:
        return "BT_ERROR_PERMISSION_DENIED : Permission denied";

    case BT_ERROR_QUOTA_EXCEEDED:
        return "BT_ERROR_QUOTA_EXCEEDED : Quota exceeded";

    case BT_ERROR_NOT_INITIALIZED:
        return "BT_ERROR_NOT_INITIALIZED : Local adapter not initialized";

    case BT_ERROR_NOT_ENABLED:
        return "BT_ERROR_NOT_ENABLED : Local adapter not enabled";

    case BT_ERROR_ALREADY_DONE:
        return "BT_ERROR_ALREADY_DONE : Operation already done";

    case BT_ERROR_OPERATION_FAILED:
        return "BT_ERROR_OPERATION_FAILED : Operation failed";

    case BT_ERROR_NOT_IN_PROGRESS:
        return "BT_ERROR_NOT_IN_PROGRESS : Operation not in progress";

    case BT_ERROR_REMOTE_DEVICE_NOT_BONDED:
        return "BT_ERROR_REMOTE_DEVICE_NOT_BONDED : Remote device not bonded";

    case BT_ERROR_AUTH_REJECTED:
        return "BT_ERROR_AUTH_REJECTED : Authentication rejected";

    case BT_ERROR_AUTH_FAILED:
        return "BT_ERROR_AUTH_FAILED : Authentication failed";

    case BT_ERROR_REMOTE_DEVICE_NOT_FOUND:
        return "BT_ERROR_REMOTE_DEVICE_NOT_FOUND : Remote device not found";

    case BT_ERROR_SERVICE_SEARCH_FAILED:
        return "BT_ERROR_SERVICE_SEARCH_FAILED : Service search failed";

    case BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED:
        return "BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED : Remote device is not connected";

    case BT_ERROR_AGAIN:
        return "BT_ERROR_AGAIN : Resource temporarily unavailable";

    case BT_ERROR_SERVICE_NOT_FOUND:
        return "BT_ERROR_SERVICE_NOT_FOUND : Service Not Found";

    default:
        return "BT_ERROR_UNKNWON";
    };
}
