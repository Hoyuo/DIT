#ifndef DIT_BLUETOOTH_H
#define DIT_BLUETOOTH_H

#include <stdbool.h>
#include <stdalign.h>

#include "dit.h"

#include <glib.h>
#include <bluetooth.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Bluetooth * Bluetooth;

struct _Bluetooth
{
    bool (* isAccessible) (Bluetooth this_gen);

    bool (* onConnect) (Bluetooth this_gen);

    bool (* isConnected) (Bluetooth this_gen);

    bool (* onDisconnect) (Bluetooth this_gen);

    void (* FileSend) (Bluetooth this_gen, String sendBuffer);

    void (* FileRecv) (Bluetooth this_gen, String * recvBuffer);

};

Bluetooth NewBluetooth (void);
void      DestroyBluetooth (Bluetooth this_gen);
bool      isBluetoothAccessible (Bluetooth this_gen);
bool      onBluetoothConnect (Bluetooth this_gen);
bool      isBluetoothConnected (Bluetooth this_gen);
bool      onBluetoothDisconnect (Bluetooth this_gen);
void      BluetoothFileSend (Bluetooth this_gen, String sendbuffer);
void      BluetoothFileRecv (Bluetooth this_gen, String * recvBuffer);

const char * BluetoothErrorCheck (int errCode);

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
