#include "Device/DeviceStatus.h"

#include <device/battery.h>
#include <device/display.h>
#include <device/led.h>

#include <stdlib.h>

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

