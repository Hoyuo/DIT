#include "Device/DeviceStatus.h"
#include <device/battery.h>
#include <stdlib.h>

DeviceStatus* NewDeviceStatus()
{
	DeviceStatusExtend* this = (DeviceStatusExtend*)malloc(sizeof(DeviceStatusExtend));

	this->deviceStatus.getBattery = getBatteryRemainsPercent;
	this->deviceStatus.DisplayLock = DisplayLock;
	this->deviceStatus.DisplayUnlock = DisplayUnlock;
	this->deviceStatus.FlashOn = onFlash;
	this->deviceStatus.FlashOff = offFlash;
	this->deviceStatus.getDisplay = getDisplayBrightLevel;
	this->deviceStatus.setDisplay = setDisplayBrightLevel;

	return &this->deviceStatus;
}
int getBatteryRemainsPercent(DeviceStatus* this_gen)
{
	int error, pct;
	error = device_battery_get_percent(&pct);

	return pct;
}

bool isBatteryCharging(DeviceStatus* this_gen)
{
	int error;
	bool charging;
	error = device_battery_is_charging(&charging);
	return charging;
}
void DisplayLock(DeviceStatus* this_gen)
{

}
void DisplayUnlock(DeviceStatus* this_gen)
{

}
void onFlash(DeviceStatus* this_gen)
{

}
void offFlash(DeviceStatus* this_gen)
{

}
int getDisplayBrightLevel(DeviceStatus* this_gen)
{

	return 0;
}
void setDisplayBrightLevel(DeviceStatus* this_gen, int bright)
{

}
