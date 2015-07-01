#include "Commnucation/Bluetooth.h"

#include <stdlib.h>
#include <app_control.h>
#include <glib.h>
#include <dlog.h>
//블루투스 장비 검색용 callback function
static void adapter_device_discovery_state_changed_cb(int result, bt_adapter_device_discovery_state_e discovery_state, bt_adapter_device_discovery_info_s *discovery_info, void* user_data)
{

	GList *foundList=(GList* )user_data;

   switch (discovery_state)
   {
   case BT_ADAPTER_DEVICE_DISCOVERY_STARTED:
      dlog_print(DLOG_INFO, LOG_TAG, "BT_ADAPTER_DEVICE_DISCOVERY_STARTED");
      break;
   case BT_ADAPTER_DEVICE_DISCOVERY_FINISHED:
      dlog_print(DLOG_INFO, LOG_TAG, "BT_ADAPTER_DEVICE_DISCOVERY_FINISHED");
      int ret=bt_adapter_unset_device_discovery_state_changed_cb();
      bt_adapter_stop_device_discovery();

      dlog_print(DLOG_INFO, LOG_TAG, "[adapter_device_discovery_state_changed_cb]callback unset",ret);
      break;

   case BT_ADAPTER_DEVICE_DISCOVERY_FOUND:
      dlog_print(DLOG_INFO, LOG_TAG, "BT_ADAPTER_DEVICE_DISCOVERY_FOUND");
      if (discovery_info != NULL)
      {
         dlog_print(DLOG_INFO, LOG_TAG, "Device Address: %s", discovery_info->remote_address);
         dlog_print(DLOG_INFO, LOG_TAG, "Device Name is: %s", discovery_info->remote_name);
         bt_adapter_device_discovery_info_s * new_device_info = malloc(sizeof(bt_adapter_device_discovery_info_s));
         if (new_device_info != NULL)
         {
            memcpy(new_device_info, discovery_info, sizeof(bt_adapter_device_discovery_info_s));
            new_device_info->remote_address = strdup(discovery_info->remote_address);
            new_device_info->remote_name = strdup(discovery_info->remote_name);
            foundList = g_list_append(foundList, (gpointer)new_device_info);
         }
      }
      break;
   }
}

//페어링된 Device iter callback
static bool adapter_bonded_device_cb(bt_device_info_s *device_info, void *user_data)
{

	GList* pairedList=(GList*)user_data;
   if (device_info == NULL)
   {
      return true;
   }
   bt_device_info_s *paired_info;
   paired_info=(bt_device_info_s*)malloc(sizeof(bt_device_info_s));
   memcpy(paired_info, device_info, sizeof(bt_device_info_s));

   pairedList = g_list_append(pairedList, (gpointer)paired_info);

   return true;
}



void __bt_opp_client_push_responded_cb(int result,
                                       const char *remote_address,
                                       void *user_data)
{
   dlog_print(DLOG_INFO, LOG_TAG, "result: %d", result);
   dlog_print(DLOG_INFO, LOG_TAG, "remote_address: %s", remote_address);
}

void __bt_opp_client_push_progress_cb(const char *file,
                                      long long size,
                                      int percent,
                                      void *user_data)
{
   dlog_print(DLOG_INFO, LOG_TAG, "size: %ld", (long)size);
   dlog_print(DLOG_INFO, LOG_TAG, "percent: %d", percent);
   dlog_print(DLOG_INFO, LOG_TAG, "file: %s", file);
}
void __bt_opp_client_push_finished_cb(int result,
                                      const char *remote_address,
                                      void *user_data)
{
   dlog_print(DLOG_INFO, LOG_TAG, "result: %d", result);
   dlog_print(DLOG_INFO, LOG_TAG, "remote_address: %s", remote_address);
}


bool isBluetoothAccessible(Bluetooth* this_gen) {

    return ((BluetoothExtends*) this_gen)->connected;
}

bool onBluetoothConnect(Bluetooth* this_gen) {

    int res = 0;
    res = bt_initialize();


    return false;
}

GList* BTSearch(Bluetooth* this_gen){
BluetoothExtends* this =(BluetoothExtends*) this_gen;

return this_gen->searched_list;
}

GList* BTBound(Bluetooth* this_gen){
	BluetoothExtends* this =(BluetoothExtends*) this_gen;

	return  this_gen->bound_list;
}

bool onBluetoothDisconnect(Bluetooth* this_gen) {

	BluetoothExtends* this =(BluetoothExtends*) this_gen;

    int res=0;
    res = bt_deinitialize();
    if(BT_ERROR_NONE==res){
    	return !(this->connected =false);
    }
    else
    	return !(this->connected =false);
}

/**
 * error 발생...
 */
int BluetoothRecv(Bluetooth* this_gen, char* recvfile) {

    return -1;
}

/**
 *
 */
int BluetoothSend(Bluetooth* this_gen, char* sendfile) {
	BluetoothExtends* this =(BluetoothExtends*) this_gen;

		int ret = bt_opp_client_initialize();
		if (ret != 0)
		{
		   dlog_print(DLOG_ERROR, LOG_TAG, "bt_opp_client_initialize() fail %d",ret);

		   return -1;
		}

		dlog_print(DLOG_INFO,LOG_TAG,sendfile);
		ret = bt_opp_client_add_file(sendfile);

		if (ret != 0)
		{

		   dlog_print(DLOG_ERROR, LOG_TAG, "bt_opp_client_add_file() fail(%d)",ret);
		   return -1;
		}

		ret = bt_opp_client_push_files(this->remoteMACAddr,
											__bt_opp_client_push_responded_cb,
		                               __bt_opp_client_push_progress_cb,
		                               __bt_opp_client_push_finished_cb, NULL);
		if (ret != 0)
		{
		   dlog_print(DLOG_ERROR, LOG_TAG, "[bt_opp_client_push_files] Failed.");
		   return -1;
		}


		ret = bt_opp_client_clear_files();
		if (ret != 0)
		{
		   dlog_print(DLOG_ERROR, LOG_TAG, "bt_opp_client_clear_files() fail");

		}

		ret = bt_opp_client_deinitialize();
		if (ret != 0)
		{
		   dlog_print(DLOG_ERROR, LOG_TAG, "bt_opp_client_initialize Failed.");


		}

		return 0;
}

bool isBluetoothConnected(Bluetooth* this_gen) {
    return ((BluetoothExtends*)this_gen)->connected;
}

Bluetooth* NewBluetooth() {

    BluetoothExtends* this = malloc(sizeof(BluetoothExtends));

    this->Bluetooth.isBluetoothAccessible = isBluetoothAccessible;
    this->Bluetooth.onBluetoothConnect = onBluetoothConnect;
    this->Bluetooth.isBluetoothConnected = isBluetoothConnected;
    this->Bluetooth.onBluetoothDisconnect = onBluetoothDisconnect;
    this->Bluetooth.BluetoothSend = BluetoothRecv;
    this->Bluetooth.BluetoothRecv = BluetoothSend;
    this->Bluetooth.getBoundDeviceList=BTBound;
    this->Bluetooth.getSearchedDeviceList=BTSearch;

    this->Bluetooth.bound_list=NULL;
    this->Bluetooth.searched_list=NULL;

    bt_error_e ret;
    ret = bt_adapter_foreach_bonded_device(adapter_bonded_device_cb, (void*)this->Bluetooth.searched_list);
   	if (ret != BT_ERROR_NONE)
   	{
   	   dlog_print(DLOG_ERROR, LOG_TAG, "[bt_adapter_foreach_bonded_device] Failed!");
   	}

    ret = bt_adapter_set_device_discovery_state_changed_cb(
   	adapter_device_discovery_state_changed_cb, (void*)(this->Bluetooth.searched_list));

   	if (ret != BT_ERROR_NONE)
   	{
   	   dlog_print(DLOG_ERROR, LOG_TAG, "[bt_adapter_set_device_discovery_state_changed_cb] Failed.");
   	}

   	ret = bt_adapter_start_device_discovery();


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
    bt_adapter_unset_state_changed_cb();
    bt_adapter_unset_device_discovery_state_changed_cb();
    bt_device_unset_service_searched_cb();
    bt_socket_unset_data_received_cb();
    bt_socket_unset_connection_state_changed_cb();
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
