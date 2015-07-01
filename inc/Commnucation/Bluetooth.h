#ifndef DIT_BLUETOOTH_H
#define DIT_BLUETOOTH_H

#include <stdbool.h>
#include <stdalign.h>

#include <bluetooth.h>
#include <glib.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Bluetooth Bluetooth;

typedef struct _Bluetooth {
    bool (* isBluetoothAccessible)(Bluetooth* this_gen);

    bool (* onBluetoothConnect)(Bluetooth* this_gen);

    bool (* onBluetoothDisconnect)(Bluetooth* this_gen);

    int (* BluetoothRecv)(Bluetooth* this_gen, char* recvbuffer);

    int (* BluetoothSend)(Bluetooth* this_gen, char* sendbuffer);

    bool(* isBluetoothConnected)(Bluetooth* this_gen);

    GList*(* getBoundDeviceList)(Bluetooth* this_gen);

    GList*(* getSearchedDeviceList)(Bluetooth* this_gen);

    GList *searched_list;
    GList *bound_list;
} Bluetooth;

Bluetooth* NewBluetooth();

void DestroyBluetooth(Bluetooth* this_gen);

bool isBluetoothAccessible(Bluetooth* this_gen);

bool onBluetoothConnect(Bluetooth* this_gen);

bool onBluetoothDisconnect(Bluetooth* this_gen);

int BluetoothRecv(Bluetooth* this_gen, char* recvbuffer);

int BluetoothSend(Bluetooth* this_gen, char* sendbuffer);

bool isBluetoothConnected(Bluetooth* this_gen);

typedef struct {
    Bluetooth Bluetooth;

    char* remoteMACAddr;
    bool connected;
    bool accessible;
} BluetoothExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_BLUETOOTH_H
