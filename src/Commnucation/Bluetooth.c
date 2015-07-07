#include "Commnucation/Bluetooth.h"

#include <stdlib.h>
#include <app_control.h>
#include <glib.h>
#include <dlog.h>
#include <stdio.h>

#define DOWNLOADSFOLDERPATH "/opt/usr/media/Downloads"
bt_adapter_device_discovery_state_e flagx;
void errorTest(int ret);
//블루투스 장비 검색용 callback function
static void adapter_device_discovery_state_changed_cb(int result, bt_adapter_device_discovery_state_e discovery_state, bt_adapter_device_discovery_info_s *discovery_info, void* user_data)
{
	BluetoothExtends* BT= (BluetoothExtends*)user_data;

	flagx=discovery_state;
   switch (discovery_state)
   {
   case BT_ADAPTER_DEVICE_DISCOVERY_STARTED:
      dlog_print(DLOG_INFO, "DIT", "BT_ADAPTER_DEVICE_DISCOVERY_STARTED");
      break;
   case BT_ADAPTER_DEVICE_DISCOVERY_FINISHED:
      dlog_print(DLOG_INFO, "DIT", "BT_ADAPTER_DEVICE_DISCOVERY_FINISHED");
      int ret=bt_adapter_unset_device_discovery_state_changed_cb();
      bt_adapter_stop_device_discovery();

      dlog_print(DLOG_INFO, "DIT", "[adapter_device_discovery_state_changed_cb]callback unset",ret);
      break;

   case BT_ADAPTER_DEVICE_DISCOVERY_FOUND:
      dlog_print(DLOG_INFO, "DIT", "BT_ADAPTER_DEVICE_DISCOVERY_FOUND");
      if (discovery_info != NULL)
      {
         dlog_print(DLOG_INFO, "DIT", "Device Address: %s", discovery_info->remote_address);
         dlog_print(DLOG_INFO, "DIT", "Device Name is: %s", discovery_info->remote_name);
         bt_device_info_s * new_device_info = (bt_device_info_s *)malloc(sizeof(bt_device_info_s));
         if (new_device_info != NULL)
         {
            new_device_info->remote_address = strdup(discovery_info->remote_address);
            new_device_info->remote_name = strdup(discovery_info->remote_name);
            BT->Bluetooth.searched_list = g_list_append( BT->Bluetooth.searched_list, (gpointer)new_device_info);
         }
      }
      break;
   }
}

//페어링된 Device iter callback
static bool adapter_bonded_device_cbx(bt_device_info_s *device_info, void *user_data)
{
	BluetoothExtends* BT= (BluetoothExtends*)user_data;

   if (device_info == NULL)
   {
      return false;
   }
   bt_device_info_s *paired_info;
   paired_info=(bt_device_info_s*)malloc(sizeof(bt_device_info_s));
//   memcpy(paired_info, device_info, sizeof(bt_device_info_s));
   paired_info->remote_address = strdup(device_info->remote_address);
   paired_info->remote_name = strdup(device_info->remote_name);

   BT->Bluetooth.bound_list = g_list_append( BT->Bluetooth.bound_list, (gpointer)paired_info);

   return true;
}



static void __bt_opp_client_push_responded_cbx(int result,
                                       const char *remote_address,
                                       void *user_data)
{
   dlog_print(DLOG_INFO, "DIT", "result: %d", result);
   dlog_print(DLOG_INFO, "DIT", "remote_address: %s", remote_address);
}

void __bt_opp_client_push_progress_cbx(const char *file,
                                      long long size,
                                      int percent,
                                      void *user_data)
{
   dlog_print(DLOG_INFO, "DIT", "size: %lld",size);
   dlog_print(DLOG_INFO, "DIT", "percent: %d", percent);
   dlog_print(DLOG_INFO, "DIT", "file: %s", file);
}
static void __bt_opp_client_push_finished_cbx(int result,
                                      const char *remote_address,
                                      void *user_data)
{
   dlog_print(DLOG_INFO, "DIT", "result: %d", result);
   dlog_print(DLOG_INFO, "DIT", "remote_address: %s", remote_address);
}

//블루투스 연결 가능 체크용 callback
static void adapter_state_changed_cbx(int result, bt_adapter_state_e adapter_state, void* user_data)
{
	BluetoothExtends* certainBTstate= (BluetoothExtends*)user_data;

	if (result != BT_ERROR_NONE)
   {
      dlog_print(DLOG_ERROR, "DIT", "[adapter_state_changed_cb] Failed! result=%d", result);
      certainBTstate->accessible=false;
      return;
   }
   if (adapter_state == BT_ADAPTER_ENABLED)
   {
      dlog_print(DLOG_INFO, "DIT", "[adapter_state_changed_cb] Bluetooth is enabled!");

      // Visibility mode of the Bluetooth device
      bt_adapter_visibility_mode_e mode;
      // Duration until the visibility mode is changed so that other devices cannot find your device
      int duration = 1;
      bt_adapter_get_visibility(&mode, &duration);
      switch (mode)
      {
      case BT_ADAPTER_VISIBILITY_MODE_NON_DISCOVERABLE:
         dlog_print(DLOG_INFO, "DIT", "[adapter_state_changed_cb] Visibility: NON_DISCOVERABLE");
         certainBTstate->accessible=false;
         break;
      case BT_ADAPTER_VISIBILITY_MODE_GENERAL_DISCOVERABLE:
         dlog_print(DLOG_INFO, "DIT", "[adapter_state_changed_cb] Visibility: GENERAL_DISCOVERABLE");
         certainBTstate->accessible=true;

         break;
      case BT_ADAPTER_VISIBILITY_MODE_LIMITED_DISCOVERABLE:
         dlog_print(DLOG_INFO, "DIT", "[adapter_state_changed_cb] Visibility: LIMITED_DISCOVERABLE");
         certainBTstate->accessible=true;

         break;
      }
   }
   else
   {
      dlog_print(DLOG_INFO, "DIT", "[adapter_state_changed_cb] Bluetooth is disabled!");
      certainBTstate->accessible=false;
   }
}

void bt_opp_server_transfer_progress_cb_for_oppx(const char *file, long long size, int percent, void *user_data)
{
   dlog_print(DLOG_INFO, "DIT", "file: %s", file);
   dlog_print(DLOG_INFO, "DIT", "size: %ld", size);
   dlog_print(DLOG_INFO, "DIT", "percent: %d", percent);
}

void bt_opp_server_transfer_finished_cb_for_oppx(int result, const char *file, long long size, void *user_data)
{
   dlog_print(DLOG_INFO, "DIT", "result: %d", result);
   dlog_print(DLOG_INFO, "DIT", "file: %s", file);
   dlog_print(DLOG_INFO, "DIT", "size: %ld", size);
}

void connection_requested_cb_for_opp_serverx(const char *remote_address, void *user_data)
	{
		bt_error_e ret;
	   dlog_print(DLOG_INFO, "DIT", "remote_address: %s", remote_address);


		 ret = bt_opp_server_accept(bt_opp_server_transfer_progress_cb_for_oppx,
		                            bt_opp_server_transfer_finished_cb_for_oppx,
		                            NULL, NULL, NULL);
		 if (ret != BT_ERROR_NONE)
		   {
		      dlog_print(DLOG_ERROR, "DIT", "[bt_opp_server_accept] Failed.");
		      errorTest(ret);
		   }

	}



bool isBTAccessible(Bluetooth* this_gen) {

	return ((BluetoothExtends*)this_gen)->accessible;

}

bool onBTConnect(Bluetooth* this_gen) {

	bt_error_e res = 0;
    res = bt_initialize();
    if(BT_ERROR_NONE!=res)    return false;

    return true;
}


GList* BTSearch(Bluetooth* this_gen){
	BluetoothExtends* this =(BluetoothExtends*) this_gen;

   bt_error_e ret = bt_adapter_set_device_discovery_state_changed_cb(
   	adapter_device_discovery_state_changed_cb, (void*)this);

	if (ret != BT_ERROR_NONE)
   	{
   	   dlog_print(DLOG_ERROR, "DIT", "[bt_adapter_set_device_discovery_state_changed_cb] Failed.");
      	errorTest(ret);

   	}
	return this_gen->searched_list;
}

GList* BTBound(Bluetooth* this_gen){

	return  this_gen->bound_list;
}

bool onBTDisconnect(Bluetooth* this_gen) {

	BluetoothExtends* this =(BluetoothExtends*) this_gen;

    int ret=0;
    ret = bt_deinitialize();
    if(BT_ERROR_NONE==ret){
		   errorTest(ret);
    	return !(this->connected =false);
    }
    else
    {			   errorTest(ret);
    	return !(this->connected =false);
    }
}

/**
 *  @param[in] this_gen assign Bluetooth object
 *  @param[in] recvfile NULLABLE assign filename
 *
 *  @returns 0:sucess -1:failed
 */
int BTRecv(Bluetooth* this_gen) {


		bt_error_e ret;
		ret=	bt_initialize();
		if(ret!= BT_ERROR_NONE){
			   dlog_print(DLOG_ERROR, "DIT", "[bt_initialize] Failed.");
			   errorTest(ret);
		     return -1;

		}
		ret = bt_opp_server_initialize_by_connection_request (DOWNLOADSFOLDERPATH, connection_requested_cb_for_opp_serverx, NULL);
		if (ret != BT_ERROR_NONE)
		{
		   dlog_print(DLOG_ERROR, "DIT", "[bt_opp_server_initialize_by_connection_request] Failed.");
		   errorTest(ret);
		     return -1;
		}
		return 0;
}

/**
 *
 *	param[in] sendfilepath fullpath of file to send
 */
int BTSend(Bluetooth* this_gen, char* sendfilepath) {
	BluetoothExtends* this =(BluetoothExtends*) this_gen;

		int ret = bt_opp_client_initialize();
		if (ret != 0)
		{
		   dlog_print(DLOG_ERROR, "DIT", "bt_opp_client_initialize() fail %d",ret);
		   errorTest(ret);
		   return -1;
		}

		dlog_print(DLOG_INFO,"DIT",sendfilepath);
		ret = bt_opp_client_add_file(sendfilepath);

		if (ret != 0)
		{

		   dlog_print(DLOG_ERROR, "DIT", "bt_opp_client_add_file() fail(%d)",ret);
		   errorTest(ret);
		   return -1;
		}

		ret = bt_opp_client_push_files(this_gen->remoteMACAddr,
											__bt_opp_client_push_responded_cbx,
		                               __bt_opp_client_push_progress_cbx,
		                               __bt_opp_client_push_finished_cbx, NULL);
		if (ret != 0)
		{
		   dlog_print(DLOG_ERROR, "DIT", "[bt_opp_client_push_files] Failed.");
		   errorTest(ret);
		   return -1;
		}


		ret = bt_opp_client_clear_files();
		if (ret != 0)
		{
		   dlog_print(DLOG_ERROR, "DIT", "bt_opp_client_clear_files() fail");
		   errorTest(ret);

		}

		ret = bt_opp_client_deinitialize();
		if (ret != 0)
		{
		   dlog_print(DLOG_ERROR, "DIT", "bt_opp_client_initialize Failed.");
		   errorTest(ret);


		}

		return 0;
}

bool isBTConnected(Bluetooth* this_gen) {
    return ((BluetoothExtends*)this_gen)->connected;
}

Bluetooth* NewBluetooth() {

    BluetoothExtends* this = malloc(sizeof(BluetoothExtends));

    this->Bluetooth.isBluetoothAccessible = isBTAccessible;
    this->Bluetooth.onBluetoothConnect = onBTConnect;
    this->Bluetooth.isBluetoothConnected = isBTConnected;
    this->Bluetooth.onBluetoothDisconnect = onBTDisconnect;
    this->Bluetooth.BluetoothSend = BTSend;
    this->Bluetooth.BluetoothRecv = BTRecv;
    this->Bluetooth.getBoundDeviceList=BTBound;
    this->Bluetooth.getSearchedDeviceList=BTSearch;

    this->Bluetooth.bound_list=NULL;
    this->Bluetooth.searched_list=NULL;

    this->Bluetooth.remoteMACAddr=NULL;
    this->connected=false;
    this->accessible=false;


    bt_error_e ret;

    	ret=bt_initialize();
    	  if (ret != BT_ERROR_NONE)
    		      	{
    		      	   dlog_print(DLOG_ERROR, "DIT", "[bt_initialize] Failed!");
    		      	errorTest(ret);
    		      	}
	   ret = bt_adapter_set_state_changed_cb(adapter_state_changed_cbx, (void*)this);
	   if (ret != BT_ERROR_NONE)
	      	{
	      	   dlog_print(DLOG_ERROR, "DIT", "[bt_adapter_set_state_changed_cb] Failed!");
	      	errorTest(ret);
	      	}


//    ret = bt_adapter_set_device_discovery_state_changed_cb(
//   	adapter_device_discovery_state_changed_cb, (void*)this);
//
//	if (ret != BT_ERROR_NONE)
//   	{
//   	   dlog_print(DLOG_ERROR, "DIT", "[bt_adapter_set_device_discovery_state_changed_cb] Failed.");
//      	errorTest(ret);
//
//   	}

	 ret = bt_adapter_foreach_bonded_device(adapter_bonded_device_cbx, (void*)this);
	   	if (ret != BT_ERROR_NONE)
	   	{
	   	   dlog_print(DLOG_ERROR, "DIT", "[bt_adapter_foreach_bonded_device] Failed!");
	   	errorTest(ret);
	   	}

   	ret = bt_adapter_start_device_discovery();

	if (ret != BT_ERROR_NONE)
   	{
   	   dlog_print(DLOG_ERROR, "DIT", "[bt_adapter_start_device_discovery] Failed.");
      	errorTest(ret);

   	}

    return &this->Bluetooth;
}


void searchedListElementFreeFunc(gpointer x){
	free((bt_adapter_device_discovery_info_s *)x);
}
void boundListElementFreeFunc(gpointer x){
	free((bt_adapter_device_discovery_info_s *)x);
}

void DestroyBluetooth(Bluetooth* this_gen) {


    if (NULL == this_gen) {
        return;
    }
    bt_opp_server_deinitialize();
    bt_adapter_stop_device_discovery();
    bt_adapter_unset_state_changed_cb();
    bt_adapter_unset_device_discovery_state_changed_cb();
    bt_device_unset_service_searched_cb();
    bt_socket_unset_data_received_cb();
    bt_socket_unset_connection_state_changed_cb();
    bt_adapter_unset_visibility_duration_changed_cb ();

	BluetoothExtends* this =(BluetoothExtends*) this_gen;


    if (NULL != this_gen->searched_list) {
    	g_list_free_full (this_gen->searched_list,searchedListElementFreeFunc);
    }
    if (NULL != this_gen->bound_list) {
    	g_list_free_full (this_gen->bound_list,searchedListElementFreeFunc);
        }
    ///do something

    free(this);

}
void errorTest(int ret){
	switch(ret){

			case BT_ERROR_NONE:
			dlog_print(DLOG_INFO, "DIT","1");
			break;

			case BT_ERROR_CANCELLED:
				dlog_print(DLOG_INFO, "DIT","2");
					break;

			case BT_ERROR_INVALID_PARAMETER:
				dlog_print(DLOG_INFO, "DIT","3");
					break;

			case BT_ERROR_OUT_OF_MEMORY:
				dlog_print(DLOG_INFO, "DIT","4");
					break;

			case BT_ERROR_RESOURCE_BUSY:
				dlog_print(DLOG_INFO, "DIT","5");
					break;

			case BT_ERROR_TIMED_OUT:
				dlog_print(DLOG_INFO, "DIT","6");
					break;

			case BT_ERROR_NOW_IN_PROGRESS:
				dlog_print(DLOG_INFO, "DIT","7");
					break;

			case BT_ERROR_NOT_SUPPORTED:
				dlog_print(DLOG_INFO, "DIT","8");
					break;

			case BT_ERROR_PERMISSION_DENIED:
				dlog_print(DLOG_INFO, "DIT","9");
					break;

			case 		BT_ERROR_QUOTA_EXCEEDED:
				dlog_print(DLOG_INFO, "DIT","10");
					break;

			case 		BT_ERROR_NOT_INITIALIZED:
				dlog_print(DLOG_INFO, "DIT","11");
					break;

			case 		BT_ERROR_NOT_ENABLED:
				dlog_print(DLOG_INFO, "DIT","12");
					break;

			case 	BT_ERROR_ALREADY_DONE:
				dlog_print(DLOG_INFO, "DIT","13");
					break;

			case  BT_ERROR_OPERATION_FAILED:
				dlog_print(DLOG_INFO, "DIT","14");
					break;

			case  BT_ERROR_NOT_IN_PROGRESS:
				dlog_print(DLOG_INFO, "DIT","15");
					break;

			case	BT_ERROR_REMOTE_DEVICE_NOT_BONDED:
				dlog_print(DLOG_INFO, "DIT","16");
					break;

			case  BT_ERROR_AUTH_REJECTED:
				dlog_print(DLOG_INFO, "DIT","17");
					break;

			case  BT_ERROR_AUTH_FAILED:
				dlog_print(DLOG_INFO, "DIT","18");
					break;

			case  BT_ERROR_REMOTE_DEVICE_NOT_FOUND:
				dlog_print(DLOG_INFO, "DIT","19");
					break;

			case  BT_ERROR_SERVICE_SEARCH_FAILED:
				dlog_print(DLOG_INFO, "DIT","20");
					break;

			case 	BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED:
				dlog_print(DLOG_INFO, "DIT","21");
					break;

			case BT_ERROR_AGAIN:
				dlog_print(DLOG_INFO, "DIT","22");
					break;

			case BT_ERROR_SERVICE_NOT_FOUND:
				dlog_print(DLOG_INFO, "DIT","23");
					break;
			};
}

