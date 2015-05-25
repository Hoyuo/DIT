#include <stddef.h>
#include <stdlib.h>
#include "GPS.h"

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
	return fasle;
}

bool onGPSConnect(GPS* this) {
	return fasle;
}

bool onGPSDisconnect(GPS* this) {
	return fasle;
}

Location GPSRecv(GPS* this) {
	return NULL;
}
