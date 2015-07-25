/*! @file	DeviceStatus.c
 *  @brief	Device Status API가 정의되어있다.
 *  @note	Device Status API가 정의되어있다.
 *  @see	DeviceStatus.h
*/


#include "Device/DeviceStatus.h"
#include <stdlib.h>
#include <device/battery.h>
#include <device/display.h>
#include <device/led.h>
#include <device/haptic.h>

const char * DeviceStatusErrorCheck (int errCode)
{
    switch (errCode)
    {
    case DEVICE_ERROR_NONE:
        return "DEVICE_ERROR_NONE : Successful";

    case DEVICE_ERROR_OPERATION_FAILED:
        return "DEVICE_ERROR_OPERATION_FAILED : Operation not permitted";

    case DEVICE_ERROR_PERMISSION_DENIED:
        return "DEVICE_ERROR_PERMISSION_DENIED : Permission denied";

    case DEVICE_ERROR_INVALID_PARAMETER:
        return "DEVICE_ERROR_INVALID_PARAMETER : Invalid parameter";

    case DEVICE_ERROR_ALREADY_IN_PROGRESS:
        return "DEVICE_ERROR_ALREADY_IN_PROGRESS : Operation already in progress";

    case DEVICE_ERROR_NOT_SUPPORTED:
        return "DEVICE_ERROR_NOT_SUPPORTED : Not supported in this device";

    case DEVICE_ERROR_NOT_INITIALIZED:
        return "DEVICE_ERROR_NOT_INITIALIZED : Not initialized";

    default:
        return "DEVICE_ERROR_NOT_UNKNOWN";
    }
}

Vibration NewVibration (void)
{
    VibrationExtend * this = (VibrationExtend *)malloc (sizeof (VibrationExtend));

    this->vibration.Custom = VibrationCustom;
    this->vibration.Short  = VibrationShort;
    this->vibration.Middle = VibrationMiddle;
    this->vibration.Long   = VibrationLong;

    device_haptic_open (0, &this->handle);

    return &this->vibration;
}

void DestroyVibration (Vibration this_gen)
{
    if ( this_gen != NULL)
    {
        VibrationExtend * this = (VibrationExtend *)this_gen;

        free (this);
    }
}

void VibrationCustom (Vibration this_gen, int period)
{
    if ( this_gen != NULL)
    {
        VibrationExtend * this = (VibrationExtend *)this_gen;

        device_haptic_vibrate (this->handle, period, 0, 0);
    }
}

void VibrationShort (Vibration this_gen)
{
    if ( this_gen != NULL)
    {
        VibrationExtend * this = (VibrationExtend *)this_gen;

        device_haptic_vibrate (this->handle, 100, 0, 0);
    }
}

void VibrationMiddle (Vibration this_gen)
{
    if ( this_gen != NULL)
    {
        VibrationExtend * this = (VibrationExtend *)this_gen;

        device_haptic_vibrate (this->handle, 500, 0, 0);
    }
}

void VibrationLong (Vibration this_gen)
{
    if ( this_gen != NULL)
    {
        VibrationExtend * this = (VibrationExtend *)this_gen;

        device_haptic_vibrate (this->handle, 1500, 0, 0);
    }
}

Display NewDisplay (void)
{
    DisplayExtend * this = (DisplayExtend *)malloc (sizeof (DisplayExtend));

    this->display.Lock      = DisplayLock;
    this->display.Unlock    = DisplayUnlock;
    this->display.Dim       = DisplayDim;
    this->display.getBright = getDisplayBrightLevel;
    this->display.setBright = setDisplayBrightLevel;

    return &this->display;
}

void DestroyDisplay (Display this_gen)
{
    if ( this_gen != NULL)
    {
        DisplayExtend * this = (DisplayExtend *)this_gen;
        free (this);
    }
}

void DisplayLock (Display this_gen)
{
    if ( this_gen != NULL)
    {
        DisplayExtend * this = (DisplayExtend *)this_gen;

        device_display_get_state (&this->state);

        if ( this->state != DISPLAY_STATE_SCREEN_OFF )
        {
            device_display_change_state (DISPLAY_STATE_SCREEN_OFF);
        }
    }
}

void DisplayUnlock (Display this_gen)
{
    if ( this_gen != NULL)
    {
        DisplayExtend * this = (DisplayExtend *)this_gen;

        device_display_get_state (&this->state);

        if ( this->state != DISPLAY_STATE_NORMAL )
        {
            device_display_change_state (DISPLAY_STATE_NORMAL);
        }
    }
}

void DisplayDim (Display this_gen)
{
    if ( this_gen != NULL)
    {
        DisplayExtend * this = (DisplayExtend *)this_gen;

        device_display_get_state (&this->state);

        if ( this->state != DISPLAY_STATE_SCREEN_DIM )
        {
            device_display_change_state (DISPLAY_STATE_SCREEN_DIM);
        }
    }
}

int getDisplayBrightLevel (Display this_gen)
{
    if ( this_gen != NULL)
    {
        DisplayExtend * this = (DisplayExtend *)this_gen;

        device_display_get_brightness (0, &this->brightLevel);

        return this->brightLevel;
    }
}

void setDisplayBrightLevel (Display this_gen, int brightLevel)
{

    if ( this_gen != NULL)
    {
        DisplayExtend * this = (DisplayExtend *)this_gen;

        if ( brightLevel > 100 )
        {
            brightLevel = 100;
        }
        else if ( brightLevel < 0 )
        {
            brightLevel = 0;
        }

        this->brightLevel = brightLevel;

        device_display_set_brightness (0, this->brightLevel);
    }
}

Battery NewBattery (void)
{
    BatteryExtend * this = (BatteryExtend *)malloc (sizeof (BatteryExtend));

    this->battery.getLevel   = getBatteryRemainsPercent;
    this->battery.isCharging = isBatteryCharging;

    return &this->battery;
}

void DestoryBattery (Battery this_gen)
{
    if ( this_gen != NULL)
    {
        BatteryExtend * this = (BatteryExtend *)this_gen;

        free (this);
    }
}

int getBatteryRemainsPercent (Battery this_gen)
{
    if ( this_gen != NULL)
    {
        BatteryExtend * this = (BatteryExtend *)this_gen;

        device_battery_get_percent (&this->batteryLevel);

        return this->batteryLevel;
    }
}

bool isBatteryCharging (Battery this_gen)
{
    if ( this_gen != NULL)
    {
        BatteryExtend * this = (BatteryExtend *)this_gen;

        device_battery_is_charging (&this->charging);

        return this->charging;
    }
}


Flash NewFlash (void)
{
    Flash this = (Flash)malloc (sizeof (struct _Flash));

    this->On  = onFlash;
    this->Off = offFlash;

    return this;
}

void DestoryFlash (Flash this_gen)
{
    if ( this_gen != NULL)
    {
        free (this_gen);
    }
}

void onFlash (void)
{
    int value;
    device_flash_get_max_brightness (&value);
    device_flash_set_brightness (value);

}

void offFlash (void)
{
    device_flash_set_brightness (0);
}
