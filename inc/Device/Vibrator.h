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
    void (* Custom)(Vibration* this, int period);

    void (* Short)(Vibration* this);

    void (* Middle)(Vibration* this);

    void (* Long)(Vibration* this);
};

Vibration* NewVibrate();

void DestroyVibrate(Vibration* this);

void VibrateCustom(Vibration* this, int period);

void VibrateShort(Vibration* this);

void VibrateMiddle(Vibration* this);

void VibrateLong(Vibration* this);

typedef struct _VibrationExtend {
    Vibration vibration;
    haptic_device_h handle;
    int error;
} VibrationExtend;

#ifdef __cplusplus
}
#endif

#endif //DIT_VIBRATOR_H
