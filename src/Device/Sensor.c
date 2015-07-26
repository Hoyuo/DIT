/*! @file	Sensor.c
 *  @brief	Sensor API가 정의되어있다.
 *  @note	Sensor API가 정의되어있다.
 *  @see	Sensor.h
*/


#include "Device/Sensor.h"

#include <stdlib.h>
#include <sensor.h>
#include <string.h>

Accelerometer NewAccelerometer (void)
{
    bool supported;
    sensor_is_supported (SENSOR_ACCELEROMETER, &supported);
    if ( supported == false )
    {
        return NULL;
    }

    AccelerometerExtend * this = malloc (sizeof (AccelerometerExtend));

    this->accelerometer.Off        		= AccelerometerOff;
    this->accelerometer.On        		= AccelerometerOn;
    this->accelerometer.addCallback		= addAccelerometerCallback;
    this->accelerometer.getValue   		= getAccelerometerValue;
    this->accelerometer.isSupported 	= isAccelerometerSupported;
    this->accelerometer.detachCallback = detachAccelerometerCallback;

    this->type     = SENSOR_ACCELEROMETER;
    this->listener = NULL;
    this->sensor   = NULL;
    this->activated =false;

    sensor_get_default_sensor(this->type,&this->sensor);
    sensor_create_listener(this->sensor,&this->listener);
    return &this->accelerometer;
}

void DestroyAccelerometer (Accelerometer this_gen)
{
    if ( this_gen == NULL)
    {
        return;
    }

    AccelerometerExtend * this = (AccelerometerExtend *)this_gen;
    if ( this->listener )
    {
        sensor_listener_unset_event_cb (this->listener);
        sensor_listener_stop (this->listener);
        sensor_destroy_listener (this->listener);

    }
    free (this_gen);
}

void addAccelerometerCallback (Accelerometer this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    AccelerometerExtend * this = (AccelerometerExtend *)this_gen;

    sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
}

void detachAccelerometerCallback (Accelerometer this_gen)
{
    AccelerometerExtend * this = (AccelerometerExtend *)this_gen;

    sensor_listener_unset_event_cb(this->listener);
}

void AccelerometerOn (Accelerometer this_gen)
{
    AccelerometerExtend * this = (AccelerometerExtend *)this_gen;
    sensor_error_e ison = sensor_listener_start (this->listener);
    if ( ison == SENSOR_ERROR_NONE )
    {
    	this->activated = true;
    }

}

void AccelerometerOff (Accelerometer this_gen)
{
    AccelerometerExtend * this = (AccelerometerExtend *)this_gen;
    sensor_error_e ison = sensor_listener_stop (this->listener);
     if(ison==SENSOR_ERROR_NONE)
     {
         this->activated = false;
     }
}

bool isAccelerometerSupported (Accelerometer this_gen)
{
    bool supported = false;
    sensor_is_supported (SENSOR_ACCELEROMETER, &supported);
    return supported;
}

Accelerometer_data getAccelerometerValue (Accelerometer this_gen)
{
    sensor_event_s data;
    AccelerometerExtend * this = (AccelerometerExtend *)this_gen;
    sensor_listener_read_data (this->listener, &data);

    Accelerometer_data vs;
    vs.x = data.values[0];
    vs.y = data.values[1];
    vs.z = data.values[2];

    vs.value_count = data.value_count;
    vs.timestamp   = data.timestamp;
    vs.accuracy    = data.accuracy;
    if(this->activated==false)
    	vs.accuracy    = SENSOR_DATA_ACCURACY_BAD;
    return vs;

}

Gravity NewGravity (void)
{
    bool supported;
    sensor_is_supported (SENSOR_GRAVITY, &supported);
    if ( supported == false )
    {
        return NULL;
    }

    GravityExtend * this = malloc (sizeof (GravityExtend));

    this->gravity.Off         = GravityOff;
    this->gravity.On          = GravityOn;
    this->gravity.addCallback = addGravityCallback;
    this->gravity.getValue    = getGravityValue;
    this->gravity.isSupported = isGravitySupported;
    this->gravity.detachCallback = detachGravityCallback;

    this->type     = SENSOR_GRAVITY;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor(this->type,&this->sensor);
    sensor_create_listener(this->sensor,&this->listener);

    return &this->gravity;
}

void DestroyGravity (Gravity this_gen)
{
    if ( this_gen == NULL)
    {
        return;
    }

    GravityExtend * this = (GravityExtend *)this_gen;
    if ( this->listener )
    {
        sensor_listener_unset_event_cb (this->listener);
        sensor_listener_stop (this->listener);
        sensor_destroy_listener (this->listener);

    }
    free (this_gen);
}

void addGravityCallback (Gravity this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    GravityExtend * this = (GravityExtend *)this_gen;

    sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
}

void detachGravityCallback (Gravity this_gen)
{
	GravityExtend * this = (GravityExtend *)this_gen;

    sensor_listener_unset_event_cb(this->listener);
}

void GravityOn (Gravity this_gen)
{
    GravityExtend * this = (GravityExtend *)this_gen;
    sensor_error_e ison = sensor_listener_start (this->listener);
    if ( ison == SENSOR_ERROR_NONE )
    {
    	this->activated = true;
    }

}

void GravityOff (Gravity this_gen)
{
    GravityExtend * this = (GravityExtend *)this_gen;
    sensor_error_e ison = sensor_listener_stop (this->listener);
     if(ison==SENSOR_ERROR_NONE)
     {
         this->activated = false;
     }
}

bool isGravitySupported (Gravity this_gen)
{
    bool supported = false;
    sensor_is_supported (SENSOR_GRAVITY, &supported);
    return supported;
}

Gravity_data getGravityValue (Gravity this_gen)
{
    sensor_event_s data;
    GravityExtend * this = (GravityExtend *)this_gen;
    sensor_listener_read_data (this->listener, &data);
    Gravity_data vs;
    vs.x = data.values[0];
    vs.y = data.values[1];
    vs.z = data.values[2];

    vs.value_count = data.value_count;
    vs.timestamp   = data.timestamp;
    vs.accuracy    = data.accuracy;
    if(this->activated==false)
    {
       	vs.accuracy    = SENSOR_DATA_ACCURACY_BAD;
    }
    return vs;

}

LinearAccelation NewLinearAccelation (void)
{
    bool supported;
    sensor_is_supported (SENSOR_LINEAR_ACCELERATION, &supported);
    if ( supported == false )
    {
        return NULL;
    }

    LinearAccelationExtend * this = malloc (sizeof (LinearAccelationExtend));

    this->linearaccelation.Off         = LinearAccelationOff;
    this->linearaccelation.On          = LinearAccelationOn;
    this->linearaccelation.addCallback = addLinearAccelationCallback;
    this->linearaccelation.getValue    = getLinearAccelationValue;
    this->linearaccelation.isSupported = isLinearAccelationSupported;
    this->linearaccelation.detachCallback = detachLinearAccelationCallback;

    this->type     = SENSOR_LINEAR_ACCELERATION;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor(this->type,&this->sensor);
    sensor_create_listener(this->sensor,&this->listener);
    return &this->linearaccelation;
}

void DestroyLinearAccelation (LinearAccelation this_gen)
{
    if ( this_gen == NULL)
    {
        return;
    }

    LinearAccelationExtend * this = (LinearAccelationExtend *)this_gen;
    if ( this->listener )
    {
        sensor_listener_unset_event_cb (this->listener);
        sensor_listener_stop (this->listener);
        sensor_destroy_listener (this->listener);

    }
    free (this_gen);
}

void addLinearAccelationCallback (LinearAccelation this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    LinearAccelationExtend * this = (LinearAccelationExtend *)this_gen;

    sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
}

void detachLinearAccelationCallback (LinearAccelation this_gen)
{
	LinearAccelationExtend * this = (LinearAccelationExtend *)this_gen;

    sensor_listener_unset_event_cb(this->listener);
}

void LinearAccelationOn (LinearAccelation this_gen)
{
    LinearAccelationExtend * this = (LinearAccelationExtend *)this_gen;
    sensor_error_e ison = sensor_listener_start (this->listener);
    if ( ison == SENSOR_ERROR_NONE )
    {
    	this->activated = true;
    }
}

void LinearAccelationOff (LinearAccelation this_gen)
{
    LinearAccelationExtend * this = (LinearAccelationExtend *)this_gen;
    sensor_error_e ison = sensor_listener_stop (this->listener);
     if(ison==SENSOR_ERROR_NONE)
     {
         this->activated = false;
     }
}

bool isLinearAccelationSupported (LinearAccelation this_gen)
{
    bool supported = false;
    sensor_is_supported (SENSOR_LINEAR_ACCELERATION, &supported);
    return supported;
}

LinearAcceleration_data getLinearAccelationValue (LinearAccelation this_gen)
{
    sensor_event_s data;
    LinearAccelationExtend * this = (LinearAccelationExtend *)this_gen;
    sensor_listener_read_data (this->listener, &data);
    LinearAcceleration_data vs;
    vs.x = data.values[0];
    vs.y = data.values[1];
    vs.z = data.values[2];

    vs.value_count = data.value_count;
    vs.timestamp   = data.timestamp;
    vs.accuracy    = data.accuracy;
    if(this->activated==false)
    {
       	vs.accuracy    = SENSOR_DATA_ACCURACY_BAD;
    }
    return vs;

}

MagnetoMeter NewMagnetoMeter (void)
{
    bool supported;
    sensor_is_supported (SENSOR_MAGNETIC, &supported);
    if ( supported == false )
    {
        return NULL;
    }

    MagnetoMeterExtend * this = malloc (sizeof (MagnetoMeterExtend));

    this->magnetometer.Off         = MagnetoMeterOff;
    this->magnetometer.On          = MagnetoMeterOn;
    this->magnetometer.addCallback = addMagnetoMeterCallback;
    this->magnetometer.getValue    = getMagnetoMeterValue;
    this->magnetometer.isSupported = isMagnetoMeterSupported;
    this->magnetometer.detachCallback = detachMagnetoMeterCallback;
    this->type     = SENSOR_MAGNETIC;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor(this->type,&this->sensor);
    sensor_create_listener(this->sensor,&this->listener);

    return &this->magnetometer;
}

void DestroyMagnetoMeter (MagnetoMeter this_gen)
{
    if ( this_gen == NULL)
    {
        return;
    }

    MagnetoMeterExtend * this = (MagnetoMeterExtend *)this_gen;
    if ( this->listener )
    {
        sensor_listener_unset_event_cb (this->listener);
        sensor_listener_stop (this->listener);
        sensor_destroy_listener (this->listener);

    }
    free (this_gen);
}

void addMagnetoMeterCallback (MagnetoMeter this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    MagnetoMeterExtend * this = (MagnetoMeterExtend *)this_gen;

    sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
}

void detachMagnetoMeterCallback (MagnetoMeter this_gen)
{
	MagnetoMeterExtend * this = (MagnetoMeterExtend *)this_gen;

    sensor_listener_unset_event_cb(this->listener);
}

void MagnetoMeterOn (MagnetoMeter this_gen)
{
    MagnetoMeterExtend * this = (MagnetoMeterExtend *)this_gen;
    sensor_error_e ison = sensor_listener_start (this->listener);
    if ( ison == SENSOR_ERROR_NONE )
    {
    	this->activated = true;
    }
}

void MagnetoMeterOff (MagnetoMeter this_gen)
{
    MagnetoMeterExtend * this = (MagnetoMeterExtend *)this_gen;
    sensor_error_e ison = sensor_listener_stop (this->listener);
     if(ison==SENSOR_ERROR_NONE)
     {
         this->activated = false;
     }
}

bool isMagnetoMeterSupported (MagnetoMeter this_gen)
{
    bool supported = false;
    sensor_is_supported (SENSOR_ACCELEROMETER, &supported);
    return supported;
}

Magnetometer_data getMagnetoMeterValue (MagnetoMeter this_gen)
{
    sensor_event_s data;
    MagnetoMeterExtend * this = (MagnetoMeterExtend *)this_gen;
    sensor_listener_read_data (this->listener, &data);
    Magnetometer_data vs;

    vs.x = data.values[0];
    vs.y = data.values[1];
    vs.z = data.values[2];

    vs.value_count = data.value_count;
    vs.timestamp   = data.timestamp;
    vs.accuracy    = data.accuracy;
    if(this->activated==false)
    {
       	vs.accuracy    = SENSOR_DATA_ACCURACY_BAD;
    }
    return vs;

}

RotationVector NewRotationVector (void)
{
    bool supported;
    sensor_is_supported (SENSOR_ROTATION_VECTOR, &supported);
    if ( supported == false )
    {
        return NULL;
    }

    RotationVectorExtend * this = malloc (sizeof (RotationVectorExtend));

    this->rotationvector.Off         = RotationVectorOff;
    this->rotationvector.On          = RotationVectorOn;
    this->rotationvector.addCallback = addRotationVectorCallback;
    this->rotationvector.getValue    = getRotationVectorValue;
    this->rotationvector.isSupported = isRotationVectorSupported;
    this->rotationvector.detachCallback = detachRotationVectorCallback;

    this->type     = SENSOR_ROTATION_VECTOR;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor(this->type,&this->sensor);
    sensor_create_listener(this->sensor,&this->listener);

    return &this->rotationvector;
}

void DestroyRotationVector (RotationVector this_gen)
{
    if ( this_gen == NULL)
    {
        return;
    }

    RotationVectorExtend * this = (RotationVectorExtend *)this_gen;
    if ( this->listener )
    {
        sensor_listener_unset_event_cb (this->listener);
        sensor_listener_stop (this->listener);
        sensor_destroy_listener (this->listener);

    }
    free (this_gen);
}

void addRotationVectorCallback (RotationVector this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    RotationVectorExtend * this = (RotationVectorExtend *)this_gen;

    sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
}

void detachRotationVectorCallback (RotationVector this_gen)
{
	RotationVectorExtend * this = (RotationVectorExtend *)this_gen;

    sensor_listener_unset_event_cb(this->listener);
}

void RotationVectorOn (RotationVector this_gen)
{
    RotationVectorExtend * this = (RotationVectorExtend *)this_gen;
    sensor_error_e ison = sensor_listener_start (this->listener);
    if ( ison == SENSOR_ERROR_NONE )
    {
    	this->activated = true;
    }
}

void RotationVectorOff (RotationVector this_gen)
{
    RotationVectorExtend * this = (RotationVectorExtend *)this_gen;
    sensor_error_e ison = sensor_listener_stop (this->listener);
     if(ison==SENSOR_ERROR_NONE)
     {
         this->activated = false;
     }
}

bool isRotationVectorSupported (RotationVector this_gen)
{
    bool supported = false;
    sensor_is_supported (SENSOR_ROTATION_VECTOR, &supported);
    return supported;
}

RotationVector_data getRotationVectorValue (RotationVector this_gen)
{
    sensor_event_s data;
    RotationVectorExtend * this = (RotationVectorExtend *)this_gen;
    sensor_listener_read_data (this->listener, &data);
    RotationVector_data vs;
    vs.x = data.values[0];
    vs.y = data.values[1];
    vs.z = data.values[2];
    vs.w = data.values[3];

    vs.value_count = data.value_count;
    vs.timestamp   = data.timestamp;
    vs.accuracy    = data.accuracy;
    if(this->activated==false)
    {
       	vs.accuracy    = SENSOR_DATA_ACCURACY_BAD;
    }
    return vs;

}

Orientation NewOrientation (void)
{
    bool supported;
    sensor_is_supported (SENSOR_ORIENTATION, &supported);
    if ( supported == false )
    {
        return NULL;
    }

    OrientationExtend * this = malloc (sizeof (OrientationExtend));

    this->orientation.Off         = OrientationOff;
    this->orientation.On          = OrientationOn;
    this->orientation.addCallback = addOrientationCallback;
    this->orientation.getValue    = getOrientationValue;
    this->orientation.isSupported = isOrientationSupported;
    this->orientation.detachCallback=detachOrientationCallback;

    this->type     = SENSOR_ORIENTATION;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor(this->type,&this->sensor);
    sensor_create_listener(this->sensor,&this->listener);

    return &this->orientation;
}

void DestroyOrientation (Orientation this_gen)
{
    if ( this_gen == NULL)
    {
        return;
    }

    OrientationExtend * this = (OrientationExtend *)this_gen;
    if ( this->listener )
    {
        sensor_listener_unset_event_cb (this->listener);
        sensor_listener_stop (this->listener);
        sensor_destroy_listener (this->listener);

    }
    free (this_gen);
}

void addOrientationCallback (Orientation this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    OrientationExtend * this = (OrientationExtend *)this_gen;

    sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
}

void detachOrientationCallback (Orientation this_gen)
{
	OrientationExtend * this = (OrientationExtend *)this_gen;

    sensor_listener_unset_event_cb(this->listener);
}

void OrientationOn (Orientation this_gen)
{
    OrientationExtend * this = (OrientationExtend *)this_gen;
    sensor_error_e ison = sensor_listener_start (this->listener);
    if ( ison == SENSOR_ERROR_NONE )
    {
    	this->activated = true;
    }
}

void OrientationOff (Orientation this_gen)
{
    OrientationExtend * this = (OrientationExtend *)this_gen;
    sensor_error_e ison = sensor_listener_stop (this->listener);
     if(ison==SENSOR_ERROR_NONE)
     {
         this->activated = false;
     }}

bool isOrientationSupported (Orientation this_gen)
{
    bool supported = false;
    sensor_is_supported (SENSOR_ORIENTATION, &supported);
    return supported;
}

Orientation_data getOrientationValue (Orientation this_gen)
{
    sensor_event_s data;
    OrientationExtend * this = (OrientationExtend *)this_gen;
    sensor_listener_read_data (this->listener, &data);
    Orientation_data vs;

    vs.x = data.values[0];
    vs.y = data.values[1];
    vs.z = data.values[2];

    vs.value_count = data.value_count;
    vs.timestamp   = data.timestamp;
    vs.accuracy    = data.accuracy;
    if(this->activated==false)
    {
       	vs.accuracy    = SENSOR_DATA_ACCURACY_BAD;
    }
    return vs;

}

Gyroscope NewGyroscope (void)
{
    bool supported;
    sensor_is_supported (SENSOR_GYROSCOPE, &supported);
    if ( supported == false )
    {
        return NULL;
    }

    GyroscopeExtend * this = malloc (sizeof (GyroscopeExtend));

    this->gyroscope.Off         = GyroscopeOff;
    this->gyroscope.On          = GyroscopeOn;
    this->gyroscope.addCallback = addGyroscopeCallback;
    this->gyroscope.getValue    = getGyroscopeValue;
    this->gyroscope.isSupported = isGyroscopeSupported;
    this->gyroscope.detachCallback = detachGyroscopeCallback;

    this->type     = SENSOR_GYROSCOPE;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_create_listener(this->sensor,&this->listener);
    sensor_listener_start (this->listener);

    return &this->gyroscope;
}

void DestroyGyroscope (Gyroscope this_gen)
{
    if ( this_gen == NULL)
    {
        return;
    }

    GyroscopeExtend * this = (GyroscopeExtend *)this_gen;
    if ( this->listener )
    {
        sensor_listener_unset_event_cb (this->listener);
        sensor_listener_stop (this->listener);
        sensor_destroy_listener (this->listener);

    }
    free (this_gen);
}

void addGyroscopeCallback (Gyroscope this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    GyroscopeExtend * this = (GyroscopeExtend *)this_gen;

    sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
}

void detachGyroscopeCallback (Gyroscope this_gen)
{
	GyroscopeExtend * this = (GyroscopeExtend *)this_gen;

    sensor_listener_unset_event_cb(this->listener);
}

void GyroscopeOn (Gyroscope this_gen)
{
    GyroscopeExtend * this = (GyroscopeExtend *)this_gen;
    sensor_error_e ison = sensor_listener_start (this->listener);
    if ( ison == SENSOR_ERROR_NONE )
    {
    	this->activated = true;
    }
}

void GyroscopeOff (Gyroscope this_gen)
{
    GyroscopeExtend * this = (GyroscopeExtend *)this_gen;
    sensor_error_e ison = sensor_listener_stop (this->listener);
     if(ison==SENSOR_ERROR_NONE)
     {
         this->activated = false;
     }}

bool isGyroscopeSupported (Gyroscope this_gen)
{
    bool supported = false;
    sensor_is_supported (SENSOR_GYROSCOPE, &supported);
    return supported;
}

Gyroscope_data getGyroscopeValue (Gyroscope this_gen)
{
    sensor_event_s data;
    GyroscopeExtend * this = (GyroscopeExtend *)this_gen;
    sensor_listener_read_data (this->listener, &data);
    Gyroscope_data vs;
    vs.x = data.values[0];
    vs.y = data.values[1];
    vs.z = data.values[2];

    vs.value_count = data.value_count;
    vs.timestamp   = data.timestamp;
    vs.accuracy    = data.accuracy;
    if(this->activated==false)
    {
       	vs.accuracy    = SENSOR_DATA_ACCURACY_BAD;
    }
    return vs;

}

Light NewLight (void)
{
    bool supported;
    sensor_is_supported (SENSOR_LIGHT, &supported);
    if ( supported == false )
    {
        return NULL;
    }

    LightExtend * this = malloc (sizeof (LightExtend));

    this->light.Off         = LightOff;
    this->light.On          = LightOn;
    this->light.addCallback = addLightCallback;
    this->light.getValue    = getLightValue;
    this->light.isSupported = isLightSupported;
    this->light.detachCallback= detachLightCallback;

    this->type     = SENSOR_LIGHT;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor(this->type,&this->sensor);
    sensor_create_listener(this->sensor,&this->listener);

    return &this->light;
}

void DestroyLight (Light this_gen)
{
    if ( this_gen == NULL)
    {
        return;
    }

    LightExtend * this = (LightExtend *)this_gen;
    if ( this->listener )
    {
        sensor_listener_unset_event_cb (this->listener);
        sensor_listener_stop (this->listener);
        sensor_destroy_listener (this->listener);

    }
    free (this_gen);
}

void addLightCallback (Light this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    LightExtend * this = (LightExtend *)this_gen;

    sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
}

void detachLightCallback (Light this_gen)
{
    AccelerometerExtend * this = (AccelerometerExtend *)this_gen;

    sensor_listener_unset_event_cb(this->listener);
}

void LightOn (Light this_gen)
{
    LightExtend * this = (LightExtend *)this_gen;
    sensor_error_e ison = sensor_listener_start (this->listener);
    if ( ison == SENSOR_ERROR_NONE )
    {
    	this->activated = true;
    }
}

void LightOff (Light this_gen)
{
    LightExtend * this = (LightExtend *)this_gen;
    sensor_error_e ison = sensor_listener_stop (this->listener);
     if(ison==SENSOR_ERROR_NONE)
     {
         this->activated = false;
     }}

bool isLightSupported (Light this_gen)
{
    bool supported = false;
    sensor_is_supported (SENSOR_LIGHT, &supported);
    return supported;
}

Light_data getLightValue (Light this_gen)
{
    sensor_event_s data;
    LightExtend * this = (LightExtend *)this_gen;
    sensor_listener_read_data (this->listener, &data);
    Light_data vs;

    vs.level       = data.values[0];
    vs.value_count = data.value_count;
    vs.timestamp   = data.timestamp;
    vs.accuracy    = data.accuracy;
    if(this->activated==false)
    {
       	vs.accuracy    = SENSOR_DATA_ACCURACY_BAD;
    }
    return vs;

}

Proximity NewProximity (void)
{
    bool supported;
    sensor_is_supported (SENSOR_PROXIMITY, &supported);
    if ( supported == false )
    {
        return NULL;
    }

    ProximityExtend * this = malloc (sizeof (ProximityExtend));

    this->proximity.Off         = ProximityOff;
    this->proximity.On          = ProximityOn;
    this->proximity.addCallback = addProximityCallback;
    this->proximity.getValue    = getProximityValue;
    this->proximity.isSupported = isProximitySupported;
    this->proximity.detachCallback = detachProximityCallback;

    this->type     = SENSOR_PROXIMITY;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor(this->type,&this->sensor);
    sensor_create_listener(this->sensor,&this->listener);

    return &this->proximity;
}

void DestroyProximity (Proximity this_gen)
{
    if ( this_gen == NULL)
    {
        return;
    }

    ProximityExtend * this = (ProximityExtend *)this_gen;
    if ( this->listener )
    {
        sensor_listener_unset_event_cb (this->listener);
        sensor_listener_stop (this->listener);
        sensor_destroy_listener (this->listener);

    }
    free (this_gen);
}

void addProximityCallback (Proximity this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    ProximityExtend * this = (ProximityExtend *)this_gen;

    sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
}

void detachProximityCallback (Proximity this_gen)
{
	ProximityExtend * this = (ProximityExtend *)this_gen;

    sensor_listener_unset_event_cb(this->listener);
}

void ProximityOn (Proximity this_gen)
{
    ProximityExtend * this = (ProximityExtend *)this_gen;
    sensor_error_e ison = sensor_listener_start (this->listener);
    if ( ison == SENSOR_ERROR_NONE )
    {
    	this->activated = true;
    }
}

void ProximityOff (Proximity this_gen)
{
    ProximityExtend * this = (ProximityExtend *)this_gen;
    sensor_error_e ison = sensor_listener_stop (this->listener);
     if(ison==SENSOR_ERROR_NONE)
     {
         this->activated = false;
     }}

bool isProximitySupported (Proximity this_gen)
{
    bool supported = false;
    sensor_is_supported (SENSOR_PROXIMITY, &supported);
    return supported;
}

Proximity_data getProximityValue (Proximity this_gen)
{
    sensor_event_s data;
    ProximityExtend * this = (ProximityExtend *)this_gen;
    sensor_listener_read_data (this->listener, &data);
    Proximity_data vs;
    vs.proximity   = data.values[0];
    vs.value_count = data.value_count;
    vs.timestamp   = data.timestamp;
    vs.accuracy    = data.accuracy;
    if(this->activated==false)
    {
       	vs.accuracy    = SENSOR_DATA_ACCURACY_BAD;
    }
    return vs;

}

Pressure NewPressure (void)
{
    bool supported;
    sensor_is_supported (SENSOR_PRESSURE, &supported);
    if ( supported == false )
    {
        return NULL;
    }

    PressureExtend * this = malloc (sizeof (PressureExtend));

    this->pressure.Off         = PressureOff;
    this->pressure.On          = PressureOn;
    this->pressure.addCallback = addPressureCallback;
    this->pressure.getValue    = getPressureValue;
    this->pressure.isSupported = isPressureSupported;
    this->pressure.detachCallback = detachPressureCallback;

    this->type     = SENSOR_PRESSURE;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor(this->type,&this->sensor);
    sensor_create_listener(this->sensor,&this->listener);

    return &this->pressure;
}

void DestroyPressure (Pressure this_gen)
{
    if ( this_gen == NULL)
    {
        return;
    }

    PressureExtend * this = (PressureExtend *)this_gen;
    if ( this->listener )
    {
        sensor_listener_unset_event_cb (this->listener);
        sensor_listener_stop (this->listener);
        sensor_destroy_listener (this->listener);

    }
    free (this_gen);
}

void addPressureCallback (Pressure this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    PressureExtend * this = (PressureExtend *)this_gen;

    sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
}

void detachPressureCallback (Pressure this_gen)
{
	PressureExtend * this = (PressureExtend *)this_gen;

    sensor_listener_unset_event_cb(this->listener);
}

void PressureOn (Pressure this_gen)
{
    PressureExtend * this = (PressureExtend *)this_gen;
    sensor_error_e ison = sensor_listener_start (this->listener);
    if ( ison == SENSOR_ERROR_NONE )
    {
    	this->activated = true;
    }
}

void PressureOff (Pressure this_gen)
{
    PressureExtend * this = (PressureExtend *)this_gen;
    sensor_error_e ison = sensor_listener_stop (this->listener);
     if(ison==SENSOR_ERROR_NONE)
     {
         this->activated = false;
     }}

bool isPressureSupported (Pressure this_gen)
{
    bool supported = false;
    sensor_is_supported (SENSOR_PRESSURE, &supported);
    return supported;
}

Pressure_data getPressureValue (Pressure this_gen)
{
    sensor_event_s data;
    PressureExtend * this = (PressureExtend *)this_gen;
    sensor_listener_read_data (this->listener, &data);
    Pressure_data vs;

    vs.hPa = data.values[0];

    vs.value_count = data.value_count;
    vs.timestamp   = data.timestamp;
    vs.accuracy    = data.accuracy;
    if(this->activated==false)
    {
       	vs.accuracy    = SENSOR_DATA_ACCURACY_BAD;
    }
    return vs;

}

UltraViolet NewUltraViolet (void)
{
    bool supported;
    sensor_is_supported (SENSOR_ULTRAVIOLET, &supported);
    if ( supported == false )
    {
        return NULL;
    }

    UltraVioletExtend * this = malloc (sizeof (UltraVioletExtend));

    this->ultraviolet.Off         = UltraVioletOff;
    this->ultraviolet.On          = UltraVioletOn;
    this->ultraviolet.addCallback = addUltraVioletCallback;
    this->ultraviolet.getValue    = getUltraVioletValue;
    this->ultraviolet.isSupported = isUltraVioletSupported;
    this->ultraviolet.detachCallback =detachUltraVioletCallback;

    this->type     = SENSOR_ULTRAVIOLET;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor(this->type,&this->sensor);
    sensor_create_listener(this->sensor,&this->listener);

    return &this->ultraviolet;
}

void DestroyUltraViolet (UltraViolet this_gen)
{
    if ( this_gen == NULL)
    {
        return;
    }

    UltraVioletExtend * this = (UltraVioletExtend *)this_gen;
    if ( this->listener )
    {
        sensor_listener_unset_event_cb (this->listener);
        sensor_listener_stop (this->listener);
        sensor_destroy_listener (this->listener);

    }
    free (this_gen);
}

void addUltraVioletCallback (UltraViolet this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    UltraVioletExtend * this = (UltraVioletExtend *)this_gen;

    sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
}

void detachUltraVioletCallback (UltraViolet this_gen)
{
	UltraVioletExtend * this = (UltraVioletExtend *)this_gen;

    sensor_listener_unset_event_cb(this->listener);
}

void UltraVioletOn (UltraViolet this_gen)
{
    UltraVioletExtend * this = (UltraVioletExtend *)this_gen;
    sensor_error_e ison = sensor_listener_start (this->listener);
    if ( ison == SENSOR_ERROR_NONE )
    {
    	this->activated = true;
    }
}

void UltraVioletOff (UltraViolet this_gen)
{
    UltraVioletExtend * this = (UltraVioletExtend *)this_gen;
    sensor_error_e ison = sensor_listener_stop (this->listener);
     if(ison==SENSOR_ERROR_NONE)
     {
         this->activated = false;
     }
}

bool isUltraVioletSupported (UltraViolet this_gen)
{
    bool supported = false;
    sensor_is_supported (SENSOR_ULTRAVIOLET, &supported);
    return supported;
}

UltraViolet_data getUltraVioletValue (UltraViolet this_gen)
{
    sensor_event_s data;
    UltraVioletExtend * this = (UltraVioletExtend *)this_gen;
    sensor_listener_read_data (this->listener, &data);
    UltraViolet_data vs;

    vs.uvindex     = data.values[0];
    vs.value_count = data.value_count;
    vs.timestamp   = data.timestamp;
    vs.accuracy    = data.accuracy;
    if(this->activated==false)
    {
       	vs.accuracy    = SENSOR_DATA_ACCURACY_BAD;
    }
    return vs;

}

Temperature NewTemperature (void)
{
    bool supported;
    sensor_is_supported (SENSOR_TEMPERATURE, &supported);
    if ( supported == false )
    {
        return NULL;
    }

    TemperatureExtend * this = malloc (sizeof (TemperatureExtend));

    this->temperature.Off         = TemperatureOff;
    this->temperature.On          = TemperatureOn;
    this->temperature.addCallback = addTemperatureCallback;
    this->temperature.getValue    = getTemperatureValue;
    this->temperature.isSupported = isTemperatureSupported;
    this->temperature.detachCallback =detachTemperatureCallback;

    this->type     = SENSOR_TEMPERATURE;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor(this->type,&this->sensor);
    sensor_create_listener(this->sensor,&this->listener);

    return &this->temperature;
}

void DestroyTemperature (Temperature this_gen)
{
    if ( this_gen == NULL)
    {
        return;
    }

    TemperatureExtend * this = (TemperatureExtend *)this_gen;
    if ( this->listener )
    {
        sensor_listener_unset_event_cb (this->listener);
        sensor_listener_stop (this->listener);
        sensor_destroy_listener (this->listener);

    }
    free (this_gen);
}

void addTemperatureCallback (Temperature this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    TemperatureExtend * this = (TemperatureExtend *)this_gen;

    sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
}

void detachTemperatureCallback (Temperature this_gen)
{
	TemperatureExtend * this = (TemperatureExtend *)this_gen;

    sensor_listener_unset_event_cb(this->listener);
}

void TemperatureOn (Temperature this_gen)
{
    TemperatureExtend * this = (TemperatureExtend *)this_gen;
    sensor_error_e ison = sensor_listener_start (this->listener);
    if ( ison == SENSOR_ERROR_NONE )
    {
    	this->activated = true;
    }
}

void TemperatureOff (Temperature this_gen)
{
    TemperatureExtend * this = (TemperatureExtend *)this_gen;
    sensor_error_e ison = sensor_listener_stop (this->listener);
     if(ison==SENSOR_ERROR_NONE)
     {
         this->activated = false;
     }
}

bool isTemperatureSupported (Temperature this_gen)
{
    bool supported = false;
    sensor_is_supported (SENSOR_TEMPERATURE, &supported);
    return supported;
}

Temperature_data getTemperatureValue (Temperature this_gen)
{
    sensor_event_s data;
    TemperatureExtend * this = (TemperatureExtend *)this_gen;
    sensor_listener_read_data (this->listener, &data);
    Temperature_data vs;

    vs.celsius     = data.values[0];
    vs.value_count = data.value_count;
    vs.timestamp   = data.timestamp;
    vs.accuracy    = data.accuracy;
    if(this->activated==false)
    {
       	vs.accuracy    = SENSOR_DATA_ACCURACY_BAD;
    }
    return vs;

}

Humidity NewHumidity (void)
{
    bool supported;
    sensor_is_supported (SENSOR_HUMIDITY, &supported);
    if ( supported == false )
    {
        return NULL;
    }

    HumidityExtend * this = malloc (sizeof (HumidityExtend));

    this->humidity.Off         = HumidityOff;
    this->humidity.On          = HumidityOn;
    this->humidity.addCallback = addHumidityCallback;
    this->humidity.getValue    = getHumidityValue;
    this->humidity.isSupported = isHumiditySupported;
    this->humidity.detachCallback = detachHumidityCallback;
    this->type     = SENSOR_HUMIDITY;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor(this->type,&this->sensor);
    sensor_create_listener(this->sensor,&this->listener);

    return &this->humidity;
}

void DestroyHumidity (Humidity this_gen)
{
    if ( this_gen == NULL)
    {
        return;
    }

    HumidityExtend * this = (HumidityExtend *)this_gen;
    if ( this->listener )
    {
        sensor_listener_unset_event_cb (this->listener);
        sensor_listener_stop (this->listener);
        sensor_destroy_listener (this->listener);

    }
    free (this_gen);
}

void addHumidityCallback (Humidity this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    HumidityExtend * this = (HumidityExtend *)this_gen;

    sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
}

void detachHumidityCallback (Humidity this_gen)
{
	HumidityExtend * this = (HumidityExtend *)this_gen;

    sensor_listener_unset_event_cb(this->listener);
}

void HumidityOn (Humidity this_gen)
{
    HumidityExtend * this = (HumidityExtend *)this_gen;
    sensor_error_e ison = sensor_listener_start (this->listener);
    if ( ison == SENSOR_ERROR_NONE )
    {
    	this->activated = true;
    }
}

void HumidityOff (Humidity this_gen)
{
    HumidityExtend * this = (HumidityExtend *)this_gen;
    sensor_error_e ison = sensor_listener_stop (this->listener);
     if(ison==SENSOR_ERROR_NONE)
     {
         this->activated = false;
     }
}

bool isHumiditySupported (Humidity this_gen)
{
    bool supported = false;
    sensor_is_supported (SENSOR_HUMIDITY, &supported);
    return supported;
}

Humidity_data getHumidityValue (Humidity this_gen)
{
    sensor_event_s data;
    HumidityExtend * this = (HumidityExtend *)this_gen;
    sensor_listener_read_data (this->listener, &data);
    Humidity_data vs;
    vs.percent     = data.values[0];
    vs.value_count = data.value_count;
    vs.timestamp   = data.timestamp;
    vs.accuracy    = data.accuracy;
    if(this->activated==false)
    {
       	vs.accuracy    = SENSOR_DATA_ACCURACY_BAD;
    }    return vs;

}
