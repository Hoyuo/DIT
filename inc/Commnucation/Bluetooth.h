#ifndef DIT_BLUETOOTH_H
#define DIT_BLUETOOTH_H

#include <stdbool.h>
#include <stdalign.h>

#include "dit.h"

#include <bluetooth.h>
#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Bluetooth * Bluetooth;

struct _Bluetooth
{
    bool (* isAccessible) (Bluetooth this_gen);

    bool (* onConnect) (Bluetooth this_gen);

    bool (* onDisconnect) (Bluetooth this_gen);

    int (* Recv) (Bluetooth this_gen);

    int (* Send) (Bluetooth this_gen, String sendbuffer);

    bool (* isConnected) (Bluetooth this_gen);
};

Bluetooth NewBluetooth (void);
void      DestroyBluetooth (Bluetooth this_gen);
bool      isBluetoothAccessible (Bluetooth this_gen);
bool      onBluetoothConnect (Bluetooth this_gen);
bool      isBluetoothConnected (Bluetooth this_gen);
bool      onBluetoothDisconnect (Bluetooth this_gen);
int       BluetoothRecv (Bluetooth this_gen);
int       BluetoothSend (Bluetooth this_gen, String sendbuffer);

GList * BluetoothSearch (Bluetooth this_gen);
GList * BluetoothBound (Bluetooth this_gen);

typedef struct
{
    struct _Bluetooth bluetooth;
    bool              connected;
    bool              accessible;
    String            remoteMACAddr;

} BluetoothExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_BLUETOOTH_H
