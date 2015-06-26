#ifndef DIT_GPS_H
#define DIT_GPS_H

#include <stdbool.h>
#include <stdalign.h>
#include "dit.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "dit.h"
#include <locations.h>

typedef struct _gps GPS;
typedef struct _location {
    double altitude;
    double latitude;
    double longitude;
    double climb;
    double direction;
    double speed;
    location_accuracy_level_e level;
    double horizontal;
    double vertical;
    time_t timestamp;
} Location;

typedef struct _gps {
    bool (* isAccessible)(GPS* this);

    bool (* onConnect)(GPS* this);

    bool (* onDisconnect)(GPS* this);

    Location (* Recv)(GPS* this);
} GPS;

GPS* newGPS();

void deleteGPS(GPS* this_gen);

bool isGPSAccessible(GPS* this);

bool onGPSConnect(GPS* this);

bool onGPSDisconnect(GPS* this);

Location GPSRecv(GPS* this);

typedef struct {
    bool access;
    Location location;
    location_manager_h manager;
    GPS gps;
} GPSExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_GPS_H
