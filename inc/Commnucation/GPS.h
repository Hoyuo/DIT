
#ifndef DIT_GPS_H
#define DIT_GPS_H

#include <stdbool.h>
#include <stdalign.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _gps GPS;
typedef struct _location {
} Location;

typedef struct _gps {
    bool (*isAccessible)(GPS* this);
    bool (*onConnect)(GPS* this);
    bool (*onDisconnect)(GPS* this);
    Location (*Recv)(GPS* this);
} GPS;

GPS* newGPS();
void deleteGPS(GPS* this_gen);

bool isGPSAccessible(GPS * this);
bool onGPSConnect(GPS * this);
bool onGPSDisconnect(GPS * this);
Location GPSRecv(GPS * this);

typedef struct {
    Location location;
    GPS gps;
} GPSExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_GPS_H
