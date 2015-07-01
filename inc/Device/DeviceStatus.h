#ifndef DIT_VIBRATOR_H
#define DIT_VIBRATOR_H


#include "dit.h"

#include <stdbool.h>
#include <stdalign.h>

#include <device/battery.h>
#include <device/callback.h>
#include <device/display.h>
#include <device/led.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _DeviceStatus DeviceStatus;
typedef struct _DeviceStatus {
	int (* getBattery)(DeviceStatus* this_gen);
	bool (* isCharging)(DeviceStatus* this_gen);
    void (* DisplayLock)(DeviceStatus* this_gen);
    void (* DisplayUnlock)(DeviceStatus* this_gen);
    void (* DisplayDim)(DeviceStatus* this_gen);
    void (* FlashOn)(DeviceStatus* this_gen);
    void (* FlashOff)(DeviceStatus* this_gen);
    int (* getDisplay)(DeviceStatus* this_gen);
    void (* setDisplay)(DeviceStatus* this_gen, int bright);
}DeviceStatus;

DeviceStatus* NewDeviceStatus();
void DestroyDeviceStatus(DeviceStatus* this_gen);

int getBatteryRemainsPercent(DeviceStatus* this_gen);
bool isBatteryCharging(DeviceStatus* this_gen);
void DisplayLock(DeviceStatus* this_gen);
void DisplayUnlock(DeviceStatus* this_gen);
void DisplayDim(DeviceStatus* this_gen);
void onFlash(DeviceStatus* this_gen);
void offFlash(DeviceStatus* this_gen);
int getDisplayBrightLevel(DeviceStatus* this_gen);
void setDisplayBrightLevel(DeviceStatus* this_gen, int bright);

typedef struct _DeviceStatusExtend{
	DeviceStatus deviceStatus;
	int error;
	int value;
	display_state_e state;
} DeviceStatusExtend;

#ifdef __cplusplus
}
#endif

#endif //DIT_VIBRATOR_H
