#include <stddef.h>
#include <stdlib.h>
#include <locations.h>
#include <dlog.h>
#include "Commnucation/GPS.h"

GPS* NewGps() {
    GPSExtends* this;
    this = (GPSExtends*) malloc(sizeof(GPSExtends));

    this->gps.isAccessible = isGPSAccessible;
    this->gps.onConnect = onGPSConnect;
    this->gps.onDisconnect = onGPSDisconnect;
    this->gps.Recv = GPSRecv;
    location_manager_h manager;
    location_manager_create(LOCATIONS_METHOD_GPS, &manager);

    this->manager = manager;

    Location location = {false,};
    this->location = location;
    this->access = false;

    return &this->gps;
}

void DestroyGps(GPS* this_gen) {
    if (this_gen != NULL) {
        GPSExtends* this = (GPSExtends*) this_gen;
        location_manager_destroy(this->manager);
        this->manager = NULL;
        free(this);
    }
}

bool isGPSAccessible(GPS* this_gen) {
    //todo 어떤 작업을 해야하는지가 의문이다.
    GPSExtends* this = (GPSExtends*) this_gen;
    return this->access;
}

bool onGPSConnect(GPS* this_gen) {
    GPSExtends* this = (GPSExtends*) this_gen;
    int error = location_manager_start(this->manager);
    if (error == LOCATIONS_ERROR_NONE) {
        return this->access = true;
    } else {
        return this->access = false;
    }
}

bool onGPSDisconnect(GPS* this_gen) {
    GPSExtends* this = (GPSExtends*) this_gen;
    int error = location_manager_stop(this->manager);
    if (error == LOCATIONS_ERROR_NONE) {
        this->access = false;
        return true;
    } else {
        return false;
    }
}

Location GPSRecv(GPS* this_gen) {
    GPSExtends* this = (GPSExtends*) this_gen;
    if (this->access) {
        double altitude, latitude, longitude, climb, direction, speed;
        double horizontal, vertical;
        location_accuracy_level_e level;
        time_t timestamp;
        int ret = location_manager_get_location(this->manager, &altitude, &latitude, &longitude, &climb, &direction, &speed, &level, &horizontal, &vertical, &timestamp);
        if (ret == LOCATIONS_ERROR_NONE) {
            this->location.vaild = true;
            this->location.altitude = altitude;
            this->location.latitude = latitude;
            this->location.longitude = longitude;
            this->location.climb = climb;
            this->location.direction = direction;
            this->location.speed = speed;
            this->location.level = level;
            this->location.horizontal = horizontal;
            this->location.vertical = vertical;
            this->location.timestamp = timestamp;
        } else {
            this->location.vaild = 0;
        }
        return this->location;
    }
}

