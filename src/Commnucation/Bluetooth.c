#include "Commnucation/Bluetooth.h"

#include <stdlib.h>
#include <app_control.h>

bool isBluetoothAccessible(Bluetooth* this_gen) {

    return ((BluetoothExtends*) this_gen)->accessible;
}

bool onBluetoothConnect(Bluetooth* this_gen) {

    int res = 0;
    res = bt_initialize();

    app_control_h service = NULL;
    app_control_create(&service);
    if (service == NULL) {
        return NULL;
    }
    app_control_set_operation(service, APP_CONTROL_OPERATION_VIEW);
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

    BluetoothExtends* this = malloc(sizeof(BluetoothExtends*));

    this->Bluetooth.isBluetoothAccessible = isBluetoothAccessible;
    this->Bluetooth.onBluetoothConnect = onBluetoothConnect;
    this->Bluetooth.isBluetoothConnected = isBluetoothConnected;
    this->Bluetooth.onBluetoothDisconnect = onBluetoothDisconnect;
    this->Bluetooth.BluetoothSend = BluetoothRecv;
    this->Bluetooth.BluetoothRecv = BluetoothSend;

    bt_error_e ret;

    return &this->Bluetooth;
}

void deleteBluetooth(Bluetooth* this_gen) {

    if (NULL == this_gen) {
        return;
    }

    BluetoothExtends* this = (BluetoothExtends*) this_gen;

    if (NULL != this->url) {
        free(this->url);
    }
    ///do something

    free(this);

}
