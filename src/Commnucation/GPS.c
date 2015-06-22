#include <stddef.h>
#include <stdlib.h>
#include "dit.h"
#include "Commnucation/GPS.h"

GPS* newGPS() {
	GPSExtends* this;
	this = (GPSExtends*) malloc(sizeof(GPSExtends));

	this->gps.isAccessible = isGPSAccessible;
	this->gps.onConnect = onGPSConnect;
	this->gps.onDisconnect = onGPSDisconnect;
	this->gps.Recv = GPSRecv;

	return &this->gps;
}

void deleteGPS(GPS* this_gen) {
	if (this_gen != NULL) {
		GPSExtends* this = (GPSExtends*) this_gen;
		free(this);
	}
}

bool isGPSAccessible(GPS* this) {
	return false;
}

bool onGPSConnect(GPS* this) {
	return false;
}

bool onGPSDisconnect(GPS* this) {
	return false;
}

Location GPSRecv(GPS* this) {
	Location t;
	return t;
}
