#include "Device/DeviceStatus.h"
#include <device/battery.h>
#include <stdlib.h>

DeviceStatus* NewDeviceStatus()
{
	DeviceStatusExtend* this = (DeviceStatusExtend*)malloc(sizeof(DeviceStatusExtend));

	this->deviceStatus.getBattery = getBatteryRemainsPercent;
	this->deviceStatus.isCharging = isBatteryCharging;
	this->deviceStatus.DisplayLock = DisplayLock;
	this->deviceStatus.DisplayUnlock = DisplayUnlock;
	this->deviceStatus.DisplayDim = DisplayDim;
	this->deviceStatus.FlashOn = onFlash;
	this->deviceStatus.FlashOff = offFlash;
	this->deviceStatus.getDisplay = getDisplayBrightLevel;
	this->deviceStatus.setDisplay = setDisplayBrightLevel;

	return &this->deviceStatus;
}

void DestroyDeviceStatus(DeviceStatus* this_gen)
{
	if (this_gen != NULL)
	{
		DeviceStatusExtend* this = (DeviceStatusExtend*) this_gen;
		free(this);
	}
}

int getBatteryRemainsPercent(DeviceStatus* this_gen)
{
	DeviceStatusExtend* this = (DeviceStatusExtend*) this_gen;
	this->error = device_battery_get_percent(&this->value);

	return this->value;
}

bool isBatteryCharging(DeviceStatus* this_gen)
{
	DeviceStatusExtend* this = (DeviceStatusExtend*) this_gen;
	this->error= device_battery_is_charging(&this->value);

	return (bool)this->value;
}

void DisplayLock(DeviceStatus* this_gen)
{
	DeviceStatusExtend* this = (DeviceStatusExtend*) this_gen;
	this->error = device_display_get_state(&this->state);
	if(this->state != DISPLAY_STATE_SCREEN_OFF)
		this->error = device_display_change_state(DISPLAY_STATE_SCREEN_OFF);
}


void DisplayUnlock(DeviceStatus* this_gen)
{
	DeviceStatusExtend* this = (DeviceStatusExtend*) this_gen;
	this->error = device_display_get_state(&this->state);
	if(this->state != DISPLAY_STATE_NORMAL)
		this->error = device_display_change_state(DISPLAY_STATE_NORMAL);
}

void DisplayDim(DeviceStatus* this_gen)
{
	DeviceStatusExtend* this = (DeviceStatusExtend*) this_gen;
	this->error = device_display_get_state(&this->state);
	if(this->state != DISPLAY_STATE_SCREEN_DIM)
		this->error = device_display_change_state(DISPLAY_STATE_SCREEN_DIM);
}

void onFlash(DeviceStatus* this_gen)
{
	DeviceStatusExtend* this = (DeviceStatusExtend*) this_gen;
	this->error = device_flash_get_max_brightness(&this->value);
	this->error = device_flash_set_brightness(this->value);
}
void offFlash(DeviceStatus* this_gen)
{
	DeviceStatusExtend* this = (DeviceStatusExtend*) this_gen;
	this->error = device_flash_set_brightness(0);
}
int getDisplayBrightLevel(DeviceStatus* this_gen)
{
	DeviceStatusExtend* this = (DeviceStatusExtend*) this_gen;
	this->error = device_display_get_brightness(0, &this->value);

	return this->value;
}
void setDisplayBrightLevel(DeviceStatus* this_gen, int bright)
{
	if (bright > 100)
		bright = 100;
	else if ( bright < 0)
		bright = 0;

	DeviceStatusExtend* this = (DeviceStatusExtend*) this_gen;
	this->error = device_display_set_brightness(0, bright);
}
