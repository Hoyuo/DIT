/*! @file	GPS.c
 *  @brief	GPS API가 정의되어있다.
 *  @note	GPS API가 정의되어있다.
 *  @see	GPS.h
 */


#include "Commnucation/GPS.h"
#include "Interface/Log.h"

#include <stdlib.h>

#include <locations.h>
#include <system_info.h>

static void gps_state_changed_cb (location_service_state_e state, void * user_data);

GPS NewGps (void)
{
    GPSExtends * this = (GPSExtends *)malloc (sizeof (GPSExtends));

    this->gps.isAccessible = isGPSAccessible;
    this->gps.onConnect    = onGPSConnect;
    this->gps.onDisconnect = onGPSDisconnect;
    this->gps.Recv         = GPSRecv;

    location_manager_create (LOCATIONS_METHOD_GPS, &this->manager);

    this->state = LOCATIONS_SERVICE_DISABLED;

    Location location = {0,};
    this->location = location;
    this->access   = false;
    this->connect  = false;

    return &this->gps;
}

void DestroyGps (GPS this_gen)
{
    if ( this_gen != NULL)
    {
        GPSExtends * this = (GPSExtends *)this_gen;

        location_manager_unset_service_state_changed_cb (this->manager);
        location_manager_destroy (this->manager);
        this->manager = NULL;
        free (this);
    }
}

bool isGPSAccessible (GPS this_gen)
{
    if ( this_gen != NULL)
    {
        GPSExtends * this = (GPSExtends *)this_gen;

        system_info_get_platform_bool ("http://tizen.org/feature/location", &this->access);

        return this->access;
    }
}

static void gps_state_changed_cb (location_service_state_e state, void * user_data)
{
    GPSExtends * this = (GPSExtends *)user_data;

    if ( state == LOCATIONS_SERVICE_ENABLED )
    {
        Location location;
        int      err;
        location.validation =true;
        err = location_manager_get_location (this->manager, &location.altitude,
                &location.latitude, &location.longitude, &location.climb, &location.direction, &location.speed,
                &location.level, &location.horizontal, &location.vertical, &location.timestamp);

        this->location = location;

        if ( err == LOCATIONS_ERROR_NONE )
        {
            this->state = LOCATIONS_SERVICE_ENABLED;
        }
        else
        {
            this->state = LOCATIONS_SERVICE_DISABLED;
        }
    }
    else if ( state == LOCATIONS_SERVICE_DISABLED )
    {
        this->state = LOCATIONS_SERVICE_DISABLED;
    }
}

bool onGPSConnect (GPS this_gen)
{
    if ( this_gen != NULL)
    {
        GPSExtends * this = (GPSExtends *)this_gen;
        int error;
        error = location_manager_set_service_state_changed_cb (this->manager, gps_state_changed_cb, this);

        error = location_manager_start (this->manager);

        if ( error == LOCATIONS_ERROR_NONE )
        {
            return this->connect = true;
        }
        else
        {
            return this->connect = false;
        }
    }
}

bool onGPSDisconnect (GPS this_gen)
{
    if ( this_gen != NULL)
    {
        GPSExtends * this = (GPSExtends *)this_gen;
        int error = location_manager_stop (this->manager);
        if ( error == LOCATIONS_ERROR_NONE )
        {
            this->access = false;
            return true;
        }
        else
        {
            return false;
        }
    }
}

Location GPSRecv (GPS this_gen)
{
    if ( this_gen != NULL)
    {
        GPSExtends * this = (GPSExtends *)this_gen;

        if ( this->connect && (this->state == LOCATIONS_SERVICE_ENABLED))
        {
            return this->location;
        }
    }
    Location l = {0,};
    return l;
}

const char * GPSErrorChecker (int errCode)
{
    switch (errCode)
    {
    case LOCATIONS_ERROR_NONE:
        return "LOCATIONS_ERROR_NONE : Successful";

    case LOCATIONS_ERROR_OUT_OF_MEMORY:
        return "LOCATIONS_ERROR_OUT_OF_MEMORY : Out of memory";

    case LOCATIONS_ERROR_INVALID_PARAMETER:
        return "LOCATIONS_ERROR_INVALID_PARAMETER : Invalid parameter";

    case LOCATIONS_ERROR_ACCESSIBILITY_NOT_ALLOWED:
        return "LOCATIONS_ERROR_ACCESSIBILITY_NOT_ALLOWED : Permission denied";

    case LOCATIONS_ERROR_NOT_SUPPORTED:
        return "LOCATIONS_ERROR_NOT_SUPPORTED : Not supported";

    case LOCATIONS_ERROR_INCORRECT_METHOD:
        return "LOCATIONS_ERROR_INCORRECT_METHOD : Location manager contains incorrect method for a given call";

    case LOCATIONS_ERROR_NETWORK_FAILED:
        return "LOCATIONS_ERROR_NETWORK_FAILED : Network unavailable";

    case LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE:
        return "LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE : Location service is not available";

    case LOCATIONS_ERROR_GPS_SETTING_OFF:
        return "LOCATIONS_ERROR_GPS_SETTING_OFF : GPS/WPS setting is not enabled";

    case LOCATIONS_ERROR_SECURITY_RESTRICTED:
        return "LOCATIONS_ERROR_SECURITY_RESTRICTED : Restricted by security system policy";

    default:
        return "LOCATIONS_ERROR_UNKNWON";
    }
}