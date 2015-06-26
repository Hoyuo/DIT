//
// Created by Park SangHyun on 2015. 5. 9..
//

#include "Commnucation/Bluetooth.h"
#include <stdbool.h>
#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>
#include <app_control.h>
#include <dlog.h>

bool isBluetoothAccessible(Bluetooth* this_gen) {

    bt_adapter_state_e adapter_state;
    int ret = bt_adapter_get_state(&adapter_state);
    if (ret != BT_ERROR_NONE) {
        dlog_print(DLOG_ERROR, LOG_TAG, "[bt_adapter_get_state] Failed");
        return false;
    }
    // If the Bluetooth Service is not enabled
    if (adapter_state == BT_ADAPTER_ENABLED) {
        dlog_print(DLOG_ERROR, LOG_TAG, "Bluetooth adapter ENABLED");
        return true;
    }
}

bool onBluetoothConnect(Bluetooth* this_gen) {

    int res = 0;
    app_control_h service = NULL;
    app_control_create(&service);
    if (service == NULL) {
        return NULL;
    }
    app_control_set_operation(service, "http://tizen.org/appcontrol/operation/edit");
    app_control_set_mime(service, "application/x-bluetooth-visibility");
    res = app_control_send_launch_request(service, NULL, NULL);

    app_control_destroy(service);
    if (res == APP_CONTROL_ERROR_NONE) {

    } else {

    }

    return false;
}

bool onBluetoothDisconnect(Bluetooth* this_gen) {
    return false;

}

int BluetoothRecv(Bluetooth* this_gen, char* recvbuffer) {
    return -1;
}

/**
 *
 */
int BluetoothSend(Bluetooth* this_gen, char* sendbuffer) {
    return -1;

}

bool isBluetoothConnected(Bluetooth* this_gen) {

    return false;
}

Bluetooth* newBluetooth() {

    BluetoothExtends* this = malloc(sizeof(BluetoothExtends * ));

    this->Bluetooth.isBluetoothAccessible = isBluetoothAccessible;
    this->Bluetooth.onBluetoothConnect = onBluetoothConnect;
    this->Bluetooth.isBluetoothConnected = isBluetoothConnected;
    this->Bluetooth.onBluetoothDisconnect = onBluetoothDisconnect;
    this->Bluetooth.BluetoothSend = BluetoothRecv;
    this->Bluetooth.BluetoothRecv = BluetoothSend;

    bt_error_e ret;

    ret = bt_initialize();


    return &this->Bluetooth;
}

void deleteBluetooth(Bluetooth* this_gen) {

    if (NULL == this_gen) {
        return;
    }

    BluetoothExtends* this = (BluetoothExtends*) this_gen;

    ///do something


    free(this);

}
