#include "Device/Vibrator.h"
#include <stdlib.h>

#include <device/haptic.h>

Vibration * NewVibrate ()
{
    VibrationExtend * this = (VibrationExtend *)malloc (sizeof (VibrationExtend));

    this->vibration.Custom = VibrateCustom;
    this->vibration.Short  = VibrateShort;
    this->vibration.Middle = VibrateMiddle;
    this->vibration.Long   = VibrateLong;

    device_haptic_open (0, &this->handle);

    return &this->vibration;
}

void DestroyVibrate (Vibration * this_gen)
{
    if ( this_gen != NULL)
    {
        VibrationExtend * this = (VibrationExtend *)this_gen;

        //this->error = device_haptic_stop(this->handle, 0);
        //this->error = device_haptic_close(this->handle);
        // No Issue

        free (this);
    }
}

void VibrateCustom (Vibration * this_gen, int period)
{
    if ( this_gen != NULL)
    {
        VibrationExtend * this = (VibrationExtend *)this_gen;

        device_haptic_vibrate (this->handle, period, 0, 0);
    }
}

void VibrateShort (Vibration * this_gen)
{
    if ( this_gen != NULL)
    {
        VibrationExtend * this = (VibrationExtend *)this_gen;

        device_haptic_vibrate (this->handle, 100, 0, 0);
    }
}

void VibrateMiddle (Vibration * this_gen)
{
    if ( this_gen != NULL)
    {
        VibrationExtend * this = (VibrationExtend *)this_gen;

        device_haptic_vibrate (this->handle, 500, 0, 0);
    }
}

void VibrateLong (Vibration * this_gen)
{
    if ( this_gen != NULL)
    {
        VibrationExtend * this = (VibrationExtend *)this_gen;

        device_haptic_vibrate (this->handle, 1500, 0, 0);
    }
}
