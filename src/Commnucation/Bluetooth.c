//
// Created by Park SangHyun on 2015. 5. 9..
//

#include "Commnucation/Bluetooth.h"
#include <stdbool.h>
#include <stdalign.h>

Bluetooth* newBluetooth(){

	return NULL;
}

void deleteBluetooth(Bluetooth* this_gen){

}

bool isBluetoothAccessible(Bluetooth* this){

	return false;
}

bool onBluetoothConnect(Bluetooth* this){
	return false;

}

bool onBluetoothDisconnect(Bluetooth* this){
	return false;

}

int BluetoothRecv(Bluetooth* this, char* recvbuffer){
return -1;
}

int BluetoothSend(Bluetooth* this, char* sendbuffer){
	return -1;

}

bool isBluetoothConnected(Bluetooth *this){

return false;
}
