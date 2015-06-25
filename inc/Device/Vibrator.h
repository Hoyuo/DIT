//
// Created by Park SangHyun on 2015. 6. 23..
//

#ifndef DIT_VIBRATOR_H
#define DIT_VIBRATOR_H

#include <device/haptic.h>
#include "dit.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Vibration Vibration;
typedef struct _Vibration {
	void (* create)(Vibration* this);
	void (* delete)(Vibration* this);

    void (* Custom)(Vibration* this, int period);
    void (* Short)(Vibration* this);
    void (* Middle)(Vibration* this);
    void (* Long)(Vibration* this);

};

Vibration* newVibrate();
void createVibrate(Vibration* this);
void deleteVibrate(Vibration* this);
void VibrateCustom(Vibration* this, int period);
void VibrateShort(Vibration* this);
void VibrateMiddle(Vibration* this);
void VibrateLong(Vibration* this);

typedef struct _VibrationExtend{
	Vibration vibration;
	haptic_device_h handle;
	int error;
} VibrationExtend;

#ifdef __cplusplus
}
#endif

#endif //DIT_VIBRATOR_H
