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

    location_manager_create(LOCATIONS_METHOD_GPS, &manager);
    Location temp = {0, 0};
    this->location = temp;

    return &this->gps;
}

void deleteGPS(GPS* this_gen) {
    if (this_gen != NULL) {
        GPSExtends* this = (GPSExtends*) this_gen;
        location_manager_destroy(this->manager);
        this->manager = NULL;
        free(this);
    }
}

bool isGPSAccessible(GPS* this) {

}

bool onGPSConnect(GPS* this) {
    GPSExtends* temp = (GPSExtends*) this;
    int error = location_manager_start(temp->manager);
    if (error == LOCATIONS_ERROR_NONE) {
        return true;
    } else {
        return false;
    }
}


bool onGPSDisconnect(GPS* this) {
    GPSExtends* temp = (GPSExtends*) this;
    int error = location_manager_stop(temp->manager);
    if (error == LOCATIONS_ERROR_NONE) {
        return true;
    } else {
        return false;
    }
}

Location GPSRecv(GPS* this) {

}
