#ifndef DIT_GPS_H
#define DIT_GPS_H

#include <stdbool.h>
#include <stdalign.h>

#include <locations.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _gps GPS;
typedef struct _location {
    bool vaild;
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
    bool (* isAccessible)(GPS* this_gen);

    bool (* onConnect)(GPS* this_gen);

    bool (* onDisconnect)(GPS* this_gen);

    Location (* Recv)(GPS* this_gen);
} GPS;

GPS* NewGps();

void DestroyGps(GPS* this_gen);

bool isGPSAccessible(GPS* this_gen);

static void __state_changed_cb(location_service_state_e state, void* user_data);

bool onGPSConnect(GPS* this_gen);

bool onGPSDisconnect(GPS* this_gen);

Location GPSRecv(GPS* this_gen);

void LogErrorChecker(int errorCode);

typedef struct {
    GPS gps;
    location_manager_h manager;
    Location location;
    bool access;
} GPSExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_GPS_H
