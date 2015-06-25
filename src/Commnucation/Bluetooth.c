//
// Created by Park SangHyun on 2015. 5. 9..
//

#include "Commnucation/Bluetooth.h"
#include <stdbool.h>
#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>

bool isBluetoothAccessible(Bluetooth* this_gen){

	BluetoothExtends* this=(BluetoothExtends*)this_gen;
	return this->accessible;
}

bool onBluetoothConnect(Bluetooth* this_gen){

	bt_error_e ret=bt_initialize();

}

bool onBluetoothDisconnect(Bluetooth* this_gen){
	return false;

}

int BluetoothRecv(Bluetooth* this_gen, char* recvbuffer){
return -1;
}
/**
 *
 */
int BluetoothSend(Bluetooth* this_gen, char* sendbuffer){
	return -1;

}

bool isBluetoothConnected(Bluetooth *this_gen){

return false;
}

Bluetooth* newBluetooth(){

	BluetoothExtends *this =malloc(sizeof(BluetoothExtends*));

	this->Bluetooth.isBluetoothAccessible=isBlutoothAccessible;
	this->Bluetooth.onBluetoothConnect=onBluetoothConnect;
	this->Bluetooth.isBluetoothConnected=isBluetoothConnected;
	this->Bluetooth.onBluetoothDisconnect=onBluetoothDisconnect;
	this->Bluetooth.BluetoothSend=BluetoothRecv;
	this->Bluetooth.BluetoothRecv=BluetoothSend;


	bt_error_e ret = bt_ᅟinitialize();

	return &this->Bluetooth;
}

void deleteBluetooth(Bluetooth* this_gen){

	if(NULL==this_gen) return;

	BluetoothExtends* this =(BluetoothExtends* )this_gen;

	if(NULL!=this->Bluetooth)
	{
		ret = bt_deinitialize();
		// do somthing...
	}



	free(this);

}
