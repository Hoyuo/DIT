#ifndef DIT_GPS_H
#define DIT_GPS_H

#include <stdbool.h>
#include <stdalign.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "dit.h"
#include <locations.h>

typedef struct _gps GPS;
typedef struct _location {
    double latitude;
    double longitude;
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
    Location location;
    location_manager_h manager;
    GPS gps;
} GPSExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_GPS_H
