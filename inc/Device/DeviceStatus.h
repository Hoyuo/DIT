#ifndef DIT_VIBRATOR_H
#define DIT_VIBRATOR_H

#include "dit.h"

#include <stdbool.h>
#include <stdalign.h>

#include <device/display.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Display*/
typedef struct _Display * Display;

struct _Display {
	void (*Lock)(Display this_gen);

	void (*Unlock)(Display this_gen);

	void (*Dim)(Display this_gen);

	int (*getBright)(Display this_gen);

	void (*setBright)(Display this_gen, int bright);
};

Display NewDisplay(void);
void DestroyDisplay(Display this_gen);
void DisplayLock(Display this_gen);
void DisplayUnlock(Display this_gen);
void DisplayDim(Display this_gen);
int getDisplayBrightLevel(Display this_gen);
void setDisplayBrightLevel(Display this_gen, int brightLevel);

typedef struct _DisplayExtend {
	struct _Display display;
	int brightLevel;
	display_state_e state;

} DisplayExtend;

/* Display*/

/* Battery */
typedef struct _Battery * Battery;
struct _Battery {
	int (*getLevel)(Battery this_gen);

	bool (*isCharging)(Battery this_gen);
};

Battery NewBattery(void);
void DestoryBattery(Battery this_gen);
int getBatteryRemainsPercent(Battery this_gen);
bool isBatteryCharging(Battery this_gen);

typedef struct _BatteryExtend {
	struct _Battery battery;
	int batteryLevel;bool charging;

} BatteryExtend;
/* Battery */

/* Flash */
typedef struct _Flash * Flash;

struct _Flash {
	void (*On)(Flash this_gen);

	void (*Off)(Flash this_gen);
};

Flash NewFlash(void);
void DestoryFlash(Flash this_gen);
void onFlash(Flash this_gen);
void offFlash(Flash this_gen);

typedef struct _FlashExtend {
	bool status;
	struct _Flash flash;

} FlashExtend;
/* Flash */

#ifdef __cplusplus
}
#endif

#endif //DIT_VIBRATOR_H
