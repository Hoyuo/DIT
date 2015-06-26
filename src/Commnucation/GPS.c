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

    Location location = {0,};
    this->location = location;
    this->access = false;

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
    //todo 어떤 작업을 해야하는지가 의문이다.
    GPSExtends* temp = (GPSExtends*) this;
    return temp->access;
}

bool onGPSConnect(GPS* this) {
    GPSExtends* temp = (GPSExtends*) this;
    int error = location_manager_start(temp->manager);
    if (error == LOCATIONS_ERROR_NONE) {
        return temp->access = true;
    } else {
        return temp->access = false;
    }
}

bool onGPSDisconnect(GPS* this) {
    GPSExtends* temp = (GPSExtends*) this;
    int error = location_manager_stop(temp->manager);
    if (error == LOCATIONS_ERROR_NONE) {
        temp->access = false;
        return true;
    } else {
        return false;
    }
}

Location GPSRecv(GPS* this) {
    GPSExtends* temp = (GPSExtends*) this;
    if (temp->access) {
        double altitude, latitude, longitude, climb, direction, speed;
        double horizontal, vertical;
        location_accuracy_level_e level;
        time_t timestamp;
        ret = location_manager_get_last_location(temp->manager, &altitude, &latitude, &longitude, &climb, &direction, &speed, &level, &horizontal, &vertical, &timestamp);
        temp->location.altitude = altitude;
        temp->location.latitude = latitude;
        temp->location.longitude = longitude;
        temp->location.climb = climb;
        temp->location.direction = direction;
        temp->location.speed = speed;
        temp->location.level = level;
        temp->location.horizontal = horizontal;
        temp->location.vertical = vertical;
        temp->location.timestamp = timestamp;
        //ret = location_manager_get_location(temp->manager, &altitude, &latitude, &longitude, &climb, &direction, &speed, &level, &horizontal, &vertical, &timestamp);
        return temp->location;
    }
}
