//
// Created by Park SangHyun on 2015. 5. 9..
//

#ifndef DIT_BLUETOOTH_H
#define DIT_BLUETOOTH_H


#include <stdbool.h>
#include <stdalign.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Bluetooth Bluetooth;

typedef struct _Bluetooth {
    bool (* isBluetoothAccessible)(Bluetooth* this);

    bool (* onBluetoothConnect)(Bluetooth* this);

    bool (* onBluetoothDisconnect)(Bluetooth* this);

    int (* BluetoothRecv)(Bluetooth* this, char* recvbuffer);

    int (* BluetoothSend)(Bluetooth* this, char* sendbuffer);

    bool(*isBluetoothConnected)(Bluetooth *this);
} Bluetooth;

Bluetooth* newBluetooth();

void deleteBluetooth(Bluetooth* this_gen);

bool isBluetoothAccessible(Bluetooth* this);

bool onBluetoothConnect(Bluetooth* this);

bool onBluetoothDisconnect(Bluetooth* this);

int BluetoothRecv(Bluetooth* this, char* recvbuffer);

int BluetoothSend(Bluetooth* this, char* sendbuffer);

bool isBluetoothConnected(Bluetooth *this);

typedef struct {
	Bluetooth Bluetooth;
    char* url;
    int urlLength;
} BluetoothExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_BLUETOOTH_H
