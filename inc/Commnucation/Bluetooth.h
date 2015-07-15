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
    bool (* isAccessible)(Bluetooth* this_gen);

    bool (* onConnect)(Bluetooth* this_gen);

    bool (* onDisconnect)(Bluetooth* this_gen);

    int (* Recv)(Bluetooth* this_gen);

    int (* Send)(Bluetooth* this_gen, char* sendbuffer);

    bool(* isConnected)(Bluetooth* this_gen);
//
//    GList*(* getBoundDeviceList)(Bluetooth* this_gen);
//
//    GList*(* getSearchedDeviceList)(Bluetooth* this_gen);
//
//    GList *searched_list;
//    GList *bound_list;
    char* remoteMACAddr;

} Bluetooth;

Bluetooth* NewBluetooth();

void DestroyBluetooth(Bluetooth* this_gen);

bool isBTAccessible(Bluetooth* this_gen);

bool onBTConnect(Bluetooth* this_gen);

bool onBTDisconnect(Bluetooth* this_gen);

int BTRecv(Bluetooth* this_gen);

int BTSend(Bluetooth* this_gen, char* sendbuffer);

bool isBTConnected(Bluetooth* this_gen);

GList* BTSearch(Bluetooth* this_gen);

GList* BTBound(Bluetooth* this_gen);

typedef struct {
    Bluetooth Bluetooth;

    bool connected;
    bool accessible;
} BluetoothExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_BLUETOOTH_H
