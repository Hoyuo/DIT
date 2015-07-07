#ifndef DIT_VIBRATOR_H
#define DIT_VIBRATOR_H

#include <stdbool.h>
#include <stdalign.h>

#include <device/haptic.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Vibration Vibration;
typedef struct _Vibration {
	void (* Custom)(Vibration* this_gen, int period);

	void (* Short)(Vibration* this_gen);

	void (* Middle)(Vibration* this_gen);

	void (* Long)(Vibration* this_gen);
}Vibration;

Vibration* NewVibrate();

void DestroyVibrate(Vibration* this_gen);

void VibrateCustom(Vibration* this_gen, int period);

void VibrateShort(Vibration* this_gen);

void VibrateMiddle(Vibration* this_gen);

void VibrateLong(Vibration* this_gen);


typedef struct _VibrationExtend {
    Vibration vibration;
    haptic_device_h handle;
    int error;
} VibrationExtend;

#ifdef __cplusplus
}
#endif

#endif //DIT_VIBRATOR_H
