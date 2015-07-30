/*! @file	Sensor.c
 *  @brief	Sensor API가 정의되어있다.
 *  @note	Sensor API가 정의되어있다.
 *  @see	Sensor.h
*/


#include "Device/Sensor.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <sensor.h>
#include <dlog.h>

Accelerometer NewAccelerometer (void)
{

    AccelerometerExtend * this = malloc (sizeof (AccelerometerExtend));

    this->accelerometer.Off            = AccelerometerOff;
    this->accelerometer.On             = AccelerometerOn;
    this->accelerometer.addCallback    = addAccelerometerCallback;
    this->accelerometer.getValue       = getAccelerometerValue;
    this->accelerometer.isSupported    = isAccelerometerSupported;
    this->accelerometer.detachCallback = detachAccelerometerCallback;

    this->type      = SENSOR_ACCELEROMETER;
    this->listener  = NULL;
    this->sensor    = NULL;
    this->activated = false;

    sensor_get_default_sensor (this->type, &this->sensor);
    sensor_create_listener (this->sensor, &this->listener);
    return &this->accelerometer;
}

void DestroyAccelerometer (Accelerometer this_gen)
{
    if ( this_gen != NULL)
    {

        AccelerometerExtend * this = (AccelerometerExtend *)this_gen;
        if ( this->listener )
        {
            sensor_listener_unset_event_cb (this->listener);
            sensor_listener_stop (this->listener);
            sensor_destroy_listener (this->listener);

        }
        free (this_gen);
    }
}

bool addAccelerometerCallback (Accelerometer this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    if ( this_gen != NULL)
    {
        AccelerometerExtend * this = (AccelerometerExtend *)this_gen;

        sensor_error_e ret = sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool detachAccelerometerCallback (Accelerometer this_gen)
{
    if ( this_gen != NULL)
    {

        AccelerometerExtend * this = (AccelerometerExtend *)this_gen;

        sensor_error_e ret = sensor_listener_unset_event_cb (this->listener);

        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }

        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool AccelerometerOn (Accelerometer this_gen)
{
    if ( this_gen != NULL)
    {
        AccelerometerExtend * this = (AccelerometerExtend *)this_gen;
        sensor_error_e ison = SENSOR_ERROR_NONE;
        ison = sensor_listener_start (this->listener);

        if ( ison != SENSOR_ERROR_NONE )
        {
            return false;
        }

        this->activated = true;
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool AccelerometerOff (Accelerometer this_gen)
{
    if ( this_gen != NULL)
    {
    AccelerometerExtend * this = (AccelerometerExtend *)this_gen;
    sensor_error_e ison = SENSOR_ERROR_NONE;
    ison = sensor_listener_stop (this->listener);

    if ( ison != SENSOR_ERROR_NONE )
    {
        return false;
    }

    this->activated = false;
    return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool isAccelerometerSupported (Accelerometer this_gen)
{
    if ( this_gen != NULL)
    {
        bool           supported = false;
        sensor_error_e errorcode = SENSOR_ERROR_NONE;
        errorcode = sensor_is_supported (SENSOR_ACCELEROMETER, &supported);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return false;
        }
        return supported;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

Accelerometer_data getAccelerometerValue (Accelerometer this_gen)
{
    Accelerometer_data invalidvs = {0,};
    if ( this_gen != NULL)
    {
        sensor_error_e errorcode;
        sensor_event_s data;
        AccelerometerExtend * this = (AccelerometerExtend *)this_gen;
        errorcode = sensor_listener_read_data (this->listener, &data);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return invalidvs;
        }
        Accelerometer_data vs;
        vs.x = data.values[0];
        vs.y = data.values[1];
        vs.z = data.values[2];

        vs.value_count = data.value_count;
        vs.timestamp   = data.timestamp;
        vs.accuracy    = data.accuracy;

        if ( this->activated == false )
        {
            vs.accuracy = SENSOR_DATA_ACCURACY_BAD;
        }
        return vs;
    }

    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return invalidvs;

}

Gravity NewGravity (void)
{

    GravityExtend * this = malloc (sizeof (GravityExtend));

    this->gravity.Off            = GravityOff;
    this->gravity.On             = GravityOn;
    this->gravity.addCallback    = addGravityCallback;
    this->gravity.getValue       = getGravityValue;
    this->gravity.isSupported    = isGravitySupported;
    this->gravity.detachCallback = detachGravityCallback;

    this->type     = SENSOR_GRAVITY;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor (this->type, &this->sensor);
    sensor_create_listener (this->sensor, &this->listener);

    return &this->gravity;
}

void DestroyGravity (Gravity this_gen)
{
    if ( this_gen != NULL)
    {

        GravityExtend * this = (GravityExtend *)this_gen;
        if ( this->listener )
        {
            sensor_listener_unset_event_cb (this->listener);
            sensor_listener_stop (this->listener);
            sensor_destroy_listener (this->listener);

        }
        free (this_gen);
    }
}

bool addGravityCallback (Gravity this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    if ( this_gen != NULL)
    {
        GravityExtend * this = (GravityExtend *)this_gen;

        sensor_error_e ret = sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool detachGravityCallback (Gravity this_gen)
{
    if ( this_gen != NULL)
    {

        GravityExtend * this = (GravityExtend *)this_gen;

        sensor_error_e ret = sensor_listener_unset_event_cb (this->listener);

        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }

        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool GravityOn (Gravity this_gen)
{
    if ( this_gen != NULL)
    {
        GravityExtend * this = (GravityExtend *)this_gen;
        sensor_error_e ison = SENSOR_ERROR_NONE;
        ison = sensor_listener_start (this->listener);

        if ( ison != SENSOR_ERROR_NONE )
        {
            return false;
        }

        this->activated = true;
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool GravityOff (Gravity this_gen)
{
    if ( this_gen != NULL)
    {
    	GravityExtend * this = (GravityExtend *)this_gen;
    	sensor_error_e ison = SENSOR_ERROR_NONE;
    	ison = sensor_listener_stop (this->listener);

    	if ( ison != SENSOR_ERROR_NONE )
    	{
    		return false;
    	}

    this->activated = false;
    return true;
    }  dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool isGravitySupported (Gravity this_gen)
{
    if ( this_gen != NULL)
    {
        bool           supported = false;
        sensor_error_e errorcode = SENSOR_ERROR_NONE;
        errorcode = sensor_is_supported (SENSOR_GRAVITY, &supported);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return false;
        }
        return supported;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

Gravity_data getGravityValue (Gravity this_gen)
{
    Gravity_data invalidvs = {0,};
    if ( this_gen != NULL)
    {
        sensor_error_e errorcode;
        sensor_event_s data;
        GravityExtend * this = (GravityExtend *)this_gen;
        errorcode = sensor_listener_read_data (this->listener, &data);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return invalidvs;
        }
        Gravity_data vs;
        vs.x = data.values[0];
        vs.y = data.values[1];
        vs.z = data.values[2];

        vs.value_count = data.value_count;
        vs.timestamp   = data.timestamp;
        vs.accuracy    = data.accuracy;
        if ( this->activated == false )
        {
            vs.accuracy = SENSOR_DATA_ACCURACY_BAD;
        }
        return vs;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return invalidvs;

}

LinearAccelation NewLinearAccelation (void)
{

    LinearAccelationExtend * this = malloc (sizeof (LinearAccelationExtend));

    this->linearaccelation.Off            = LinearAccelationOff;
    this->linearaccelation.On             = LinearAccelationOn;
    this->linearaccelation.addCallback    = addLinearAccelationCallback;
    this->linearaccelation.getValue       = getLinearAccelationValue;
    this->linearaccelation.isSupported    = isLinearAccelationSupported;
    this->linearaccelation.detachCallback = detachLinearAccelationCallback;

    this->type     = SENSOR_LINEAR_ACCELERATION;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor (this->type, &this->sensor);
    sensor_create_listener (this->sensor, &this->listener);
    return &this->linearaccelation;
}

void DestroyLinearAccelation (LinearAccelation this_gen)
{
    if ( this_gen != NULL)
    {

        LinearAccelationExtend * this = (LinearAccelationExtend *)this_gen;
        if ( this->listener )
        {
            sensor_listener_unset_event_cb (this->listener);
            sensor_listener_stop (this->listener);
            sensor_destroy_listener (this->listener);

        }
        free (this_gen);
    }
}

bool addLinearAccelationCallback (LinearAccelation this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    if ( this_gen != NULL)
    {
        LinearAccelationExtend * this = (LinearAccelationExtend *)this_gen;

        sensor_error_e ret = sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool detachLinearAccelationCallback (LinearAccelation this_gen)
{
    if ( this_gen != NULL)
    {

        LinearAccelationExtend * this = (LinearAccelationExtend *)this_gen;

        sensor_error_e ret = sensor_listener_unset_event_cb (this->listener);

        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }

        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool LinearAccelationOn (LinearAccelation this_gen)
{
    if ( this_gen != NULL)
    {
        LinearAccelationExtend * this = (LinearAccelationExtend *)this_gen;
        sensor_error_e ison = SENSOR_ERROR_NONE;
        ison = sensor_listener_start (this->listener);

        if ( ison != SENSOR_ERROR_NONE )
        {
            return false;
        }

        this->activated = true;
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool LinearAccelationOff (LinearAccelation this_gen)
{
    if ( this_gen != NULL)
    {
    	LinearAccelationExtend * this = (LinearAccelationExtend *)this_gen;
    	sensor_error_e ison = SENSOR_ERROR_NONE;
    	ison = sensor_listener_stop (this->listener);

    	if ( ison != SENSOR_ERROR_NONE )
    	{
    		return false;
    	}

    	this->activated = false;
    	return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool isLinearAccelationSupported (LinearAccelation this_gen)
{
    if ( this_gen != NULL)
    {
        bool           supported = false;
        sensor_error_e errorcode = SENSOR_ERROR_NONE;
        errorcode = sensor_is_supported (SENSOR_LINEAR_ACCELERATION, &supported);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return false;
        }
        return supported;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

LinearAcceleration_data getLinearAccelationValue (LinearAccelation this_gen)
{
    LinearAcceleration_data invalidvs = {0,};
    if ( this_gen != NULL)
    {
        sensor_error_e errorcode;
        sensor_event_s data;
        LinearAccelationExtend * this = (LinearAccelationExtend *)this_gen;
        errorcode = sensor_listener_read_data (this->listener, &data);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return invalidvs;
        }
        LinearAcceleration_data vs;
        vs.x = data.values[0];
        vs.y = data.values[1];
        vs.z = data.values[2];

        vs.value_count = data.value_count;
        vs.timestamp   = data.timestamp;
        vs.accuracy    = data.accuracy;
        if ( this->activated == false )
        {
            vs.accuracy = SENSOR_DATA_ACCURACY_BAD;
        }
        return vs;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return invalidvs;

}

Magnetometer NewMagnetometer (void)
{
    MagnetometerExtend * this = malloc (sizeof (MagnetometerExtend));

    this->magnetometer.Off            = MagnetometerOff;
    this->magnetometer.On             = MagnetometerOn;
    this->magnetometer.addCallback    = addMagnetometerCallback;
    this->magnetometer.getValue       = getMagnetometerValue;
    this->magnetometer.isSupported    = isMagnetometerSupported;
    this->magnetometer.detachCallback = detachMagnetometerCallback;
    this->type                        = SENSOR_MAGNETIC;
    this->listener                    = NULL;
    this->sensor                      = NULL;

    sensor_get_default_sensor (this->type, &this->sensor);
    sensor_create_listener (this->sensor, &this->listener);

    return &this->magnetometer;
}

void DestroyMagnetometer (Magnetometer this_gen)
{
    if ( this_gen != NULL)
    {

        MagnetometerExtend * this = (MagnetometerExtend *)this_gen;
        if ( this->listener )
        {
            sensor_listener_unset_event_cb (this->listener);
            sensor_listener_stop (this->listener);
            sensor_destroy_listener (this->listener);

        }
        free (this_gen);
    }
}

bool addMagnetometerCallback (Magnetometer this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    if ( this_gen != NULL)
    {
        MagnetometerExtend * this = (MagnetometerExtend *)this_gen;

        sensor_error_e ret = sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool detachMagnetometerCallback (Magnetometer this_gen)
{
    if ( this_gen != NULL)
    {

        MagnetometerExtend * this = (MagnetometerExtend *)this_gen;

        sensor_error_e ret = sensor_listener_unset_event_cb (this->listener);

        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }

        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool MagnetometerOn (Magnetometer this_gen)
{
    if ( this_gen != NULL)
    {
        MagnetometerExtend * this = (MagnetometerExtend *)this_gen;
        sensor_error_e ison = SENSOR_ERROR_NONE;
        ison = sensor_listener_start (this->listener);

        if ( ison != SENSOR_ERROR_NONE )
        {
            return false;
        }

        this->activated = true;
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool MagnetometerOff (Magnetometer this_gen)
{
    if ( this_gen != NULL)
    {
    MagnetometerExtend * this = (MagnetometerExtend *)this_gen;
    sensor_error_e ison = SENSOR_ERROR_NONE;
    ison = sensor_listener_stop (this->listener);

    if ( ison != SENSOR_ERROR_NONE )
    {
        return false;
    }

    this->activated = false;
    return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool isMagnetometerSupported (Magnetometer this_gen)
{
    if ( this_gen != NULL)
    {
        bool           supported = false;
        sensor_error_e errorcode = SENSOR_ERROR_NONE;
        errorcode = sensor_is_supported (SENSOR_MAGNETIC, &supported);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return false;
        }
        return supported;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

Magnetometer_data getMagnetometerValue (Magnetometer this_gen)
{
    Magnetometer_data invalidvs = {0,};
    if ( this_gen != NULL)
    {
        sensor_error_e errorcode;
        sensor_event_s data;
        MagnetometerExtend * this = (MagnetometerExtend *)this_gen;
        errorcode = sensor_listener_read_data (this->listener, &data);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return invalidvs;
        }
        Magnetometer_data vs;
        vs.x = data.values[0];
        vs.y = data.values[1];
        vs.z = data.values[2];

        vs.value_count = data.value_count;
        vs.timestamp   = data.timestamp;
        vs.accuracy    = data.accuracy;
        if ( this->activated == false )
        {
            vs.accuracy = SENSOR_DATA_ACCURACY_BAD;
        }
        return vs;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return invalidvs;

}

RotationVector NewRotationVector (void)
{
    RotationVectorExtend * this = malloc (sizeof (RotationVectorExtend));

    this->rotationvector.Off            = RotationVectorOff;
    this->rotationvector.On             = RotationVectorOn;
    this->rotationvector.addCallback    = addRotationVectorCallback;
    this->rotationvector.getValue       = getRotationVectorValue;
    this->rotationvector.isSupported    = isRotationVectorSupported;
    this->rotationvector.detachCallback = detachRotationVectorCallback;

    this->type     = SENSOR_ROTATION_VECTOR;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor (this->type, &this->sensor);
    sensor_create_listener (this->sensor, &this->listener);

    return &this->rotationvector;
}

void DestroyRotationVector (RotationVector this_gen)
{
    if ( this_gen != NULL)
    {

        RotationVectorExtend * this = (RotationVectorExtend *)this_gen;
        if ( this->listener )
        {
            sensor_listener_unset_event_cb (this->listener);
            sensor_listener_stop (this->listener);
            sensor_destroy_listener (this->listener);

        }
        free (this_gen);
    }
}

bool addRotationVectorCallback (RotationVector this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    if ( this_gen != NULL)
    {
        RotationVectorExtend * this = (RotationVectorExtend *)this_gen;

        sensor_error_e ret = sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool detachRotationVectorCallback (RotationVector this_gen)
{
    if ( this_gen != NULL)
    {

        RotationVectorExtend * this = (RotationVectorExtend *)this_gen;

        sensor_error_e ret = sensor_listener_unset_event_cb (this->listener);

        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }

        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool RotationVectorOn (RotationVector this_gen)
{
    if ( this_gen != NULL)
    {
        RotationVectorExtend * this = (RotationVectorExtend *)this_gen;
        sensor_error_e ison = SENSOR_ERROR_NONE;
        ison = sensor_listener_start (this->listener);

        if ( ison != SENSOR_ERROR_NONE )
        {
            return false;
        }

        this->activated = true;
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool RotationVectorOff (RotationVector this_gen)
{
    if ( this_gen != NULL)
    {
    	RotationVectorExtend * this = (RotationVectorExtend *)this_gen;
    	sensor_error_e ison = SENSOR_ERROR_NONE;
    	ison = sensor_listener_stop (this->listener);

    	if ( ison != SENSOR_ERROR_NONE )
    	{
    		return false;
    	}

    	this->activated = false;
    	return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool isRotationVectorSupported (RotationVector this_gen)
{
    if ( this_gen != NULL)
    {
        bool           supported = false;
        sensor_error_e errorcode = SENSOR_ERROR_NONE;
        errorcode = sensor_is_supported (SENSOR_ROTATION_VECTOR, &supported);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return false;
        }
        return supported;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

RotationVector_data getRotationVectorValue (RotationVector this_gen)
{
    RotationVector_data invalidvs = {0,};
    if ( this_gen != NULL)
    {
        sensor_error_e errorcode;
        sensor_event_s data;
        RotationVectorExtend * this = (RotationVectorExtend *)this_gen;
        errorcode = sensor_listener_read_data (this->listener, &data);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return invalidvs;
        }
        RotationVector_data vs;
        vs.x = data.values[0];
        vs.y = data.values[1];
        vs.z = data.values[2];
        vs.w = data.values[3];

        vs.value_count = data.value_count;
        vs.timestamp   = data.timestamp;
        vs.accuracy    = data.accuracy;
        if ( this->activated == false )
        {
            vs.accuracy = SENSOR_DATA_ACCURACY_BAD;
        }
        return vs;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return invalidvs;

}

Orientation NewOrientation (void)
{

    OrientationExtend * this = malloc (sizeof (OrientationExtend));

    this->orientation.Off            = OrientationOff;
    this->orientation.On             = OrientationOn;
    this->orientation.addCallback    = addOrientationCallback;
    this->orientation.getValue       = getOrientationValue;
    this->orientation.isSupported    = isOrientationSupported;
    this->orientation.detachCallback = detachOrientationCallback;

    this->type     = SENSOR_ORIENTATION;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor (this->type, &this->sensor);
    sensor_create_listener (this->sensor, &this->listener);

    return &this->orientation;
}

void DestroyOrientation (Orientation this_gen)
{
    if ( this_gen != NULL)
    {

        OrientationExtend * this = (OrientationExtend *)this_gen;
        if ( this->listener )
        {
            sensor_listener_unset_event_cb (this->listener);
            sensor_listener_stop (this->listener);
            sensor_destroy_listener (this->listener);

        }
        free (this_gen);
    }
}

bool addOrientationCallback (Orientation this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    if ( this_gen != NULL)
    {
        OrientationExtend * this = (OrientationExtend *)this_gen;

        sensor_error_e ret = sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool detachOrientationCallback (Orientation this_gen)
{
    if ( this_gen != NULL)
    {

        OrientationExtend * this = (OrientationExtend *)this_gen;

        sensor_error_e ret = sensor_listener_unset_event_cb (this->listener);

        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }

        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool OrientationOn (Orientation this_gen)
{
    if ( this_gen != NULL)
    {
        OrientationExtend * this = (OrientationExtend *)this_gen;
        sensor_error_e ison = SENSOR_ERROR_NONE;
        ison = sensor_listener_start (this->listener);

        if ( ison != SENSOR_ERROR_NONE )
        {
            return false;
        }

        this->activated = true;
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool OrientationOff (Orientation this_gen)
{
    if ( this_gen != NULL)
    {
        OrientationExtend * this = (OrientationExtend *)this_gen;
        sensor_error_e ison = SENSOR_ERROR_NONE;
        ison = sensor_listener_stop (this->listener);

        if ( ison != SENSOR_ERROR_NONE )
        {
        	return false;
        }

        this->activated = false;
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool isOrientationSupported (Orientation this_gen)
{
    if ( this_gen != NULL)
    {
        bool           supported = false;
        sensor_error_e errorcode = SENSOR_ERROR_NONE;
        errorcode = sensor_is_supported (SENSOR_ORIENTATION, &supported);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return false;
        }
        return supported;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

Orientation_data getOrientationValue (Orientation this_gen)
{
    Orientation_data invalidvs = {0,};
    if ( this_gen != NULL)
    {
        sensor_error_e errorcode;
        sensor_event_s data;
        OrientationExtend * this = (OrientationExtend *)this_gen;
        errorcode = sensor_listener_read_data (this->listener, &data);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return invalidvs;
        }
        Orientation_data vs;
        vs.x = data.values[0];
        vs.y = data.values[1];
        vs.z = data.values[2];

        vs.value_count = data.value_count;
        vs.timestamp   = data.timestamp;
        vs.accuracy    = data.accuracy;
        if ( this->activated == false )
        {
            vs.accuracy = SENSOR_DATA_ACCURACY_BAD;
        }
        return vs;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return invalidvs;

}

Gyroscope NewGyroscope (void)
{

    GyroscopeExtend * this = malloc (sizeof (GyroscopeExtend));

    this->gyroscope.Off            = GyroscopeOff;
    this->gyroscope.On             = GyroscopeOn;
    this->gyroscope.addCallback    = addGyroscopeCallback;
    this->gyroscope.getValue       = getGyroscopeValue;
    this->gyroscope.isSupported    = isGyroscopeSupported;
    this->gyroscope.detachCallback = detachGyroscopeCallback;

    this->type     = SENSOR_GYROSCOPE;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_create_listener (this->sensor, &this->listener);
    sensor_listener_start (this->listener);

    return &this->gyroscope;
}

void DestroyGyroscope (Gyroscope this_gen)
{
    if ( this_gen != NULL)
    {

        GyroscopeExtend * this = (GyroscopeExtend *)this_gen;
        if ( this->listener )
        {
            sensor_listener_unset_event_cb (this->listener);
            sensor_listener_stop (this->listener);
            sensor_destroy_listener (this->listener);

        }
        free (this_gen);
    }
}

bool addGyroscopeCallback (Gyroscope this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    if ( this_gen != NULL)
    {
        GyroscopeExtend * this = (GyroscopeExtend *)this_gen;

        sensor_error_e ret = sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool detachGyroscopeCallback (Gyroscope this_gen)
{
    if ( this_gen != NULL)
    {

        GyroscopeExtend * this = (GyroscopeExtend *)this_gen;

        sensor_error_e ret = sensor_listener_unset_event_cb (this->listener);

        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }

        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool GyroscopeOn (Gyroscope this_gen)
{
    if ( this_gen != NULL)
    {
        GyroscopeExtend * this = (GyroscopeExtend *)this_gen;
        sensor_error_e ison = SENSOR_ERROR_NONE;
        ison = sensor_listener_start (this->listener);

        if ( ison != SENSOR_ERROR_NONE )
        {
            return false;
        }

        this->activated = true;
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool GyroscopeOff (Gyroscope this_gen)
{
    if ( this_gen != NULL)
    {
    	GyroscopeExtend * this = (GyroscopeExtend *)this_gen;
        sensor_error_e ison = SENSOR_ERROR_NONE;
        ison = sensor_listener_stop (this->listener);

        if ( ison != SENSOR_ERROR_NONE )
        {
        	return false;
        }

        this->activated = false;
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool isGyroscopeSupported (Gyroscope this_gen)
{
    if ( this_gen != NULL)
    {
        bool           supported = false;
        sensor_error_e errorcode = SENSOR_ERROR_NONE;
        errorcode = sensor_is_supported (SENSOR_GYROSCOPE, &supported);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return false;
        }
        return supported;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

Gyroscope_data getGyroscopeValue (Gyroscope this_gen)
{
    Gyroscope_data invalidvs = {0,};
    if ( this_gen != NULL)
    {
        sensor_error_e errorcode;
        sensor_event_s data;
        GyroscopeExtend * this = (GyroscopeExtend *)this_gen;
        errorcode = sensor_listener_read_data (this->listener, &data);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return invalidvs;
        }
        Gyroscope_data vs;
        vs.x = data.values[0];
        vs.y = data.values[1];
        vs.z = data.values[2];

        vs.value_count = data.value_count;
        vs.timestamp   = data.timestamp;
        vs.accuracy    = data.accuracy;
        if ( this->activated == false )
        {
            vs.accuracy = SENSOR_DATA_ACCURACY_BAD;
        }
        return vs;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return invalidvs;

}

Light NewLight (void)
{

    LightExtend * this = malloc (sizeof (LightExtend));

    this->light.Off            = LightOff;
    this->light.On             = LightOn;
    this->light.addCallback    = addLightCallback;
    this->light.getValue       = getLightValue;
    this->light.isSupported    = isLightSupported;
    this->light.detachCallback = detachLightCallback;

    this->type     = SENSOR_LIGHT;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor (this->type, &this->sensor);
    sensor_create_listener (this->sensor, &this->listener);

    return &this->light;
}

void DestroyLight (Light this_gen)
{
    if ( this_gen != NULL)
    {

        LightExtend * this = (LightExtend *)this_gen;
        if ( this->listener )
        {
            sensor_listener_unset_event_cb (this->listener);
            sensor_listener_stop (this->listener);
            sensor_destroy_listener (this->listener);

        }
        free (this_gen);
    }
}

bool addLightCallback (Light this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    if ( this_gen != NULL)
    {
        LightExtend * this = (LightExtend *)this_gen;

        sensor_error_e ret = sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool detachLightCallback (Light this_gen)
{
    if ( this_gen != NULL)
    {

        LightExtend * this = (LightExtend *)this_gen;

        sensor_error_e ret = sensor_listener_unset_event_cb (this->listener);

        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }

        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool LightOn (Light this_gen)
{
    if ( this_gen != NULL)
    {
        LightExtend * this = (LightExtend *)this_gen;
        sensor_error_e ison = SENSOR_ERROR_NONE;
        ison = sensor_listener_start (this->listener);

        if ( ison != SENSOR_ERROR_NONE )
        {
            return false;
        }

        this->activated = true;
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool LightOff (Light this_gen)
{
    if ( this_gen != NULL)
    {
        LightExtend * this = (LightExtend *)this_gen;
        sensor_error_e ison = SENSOR_ERROR_NONE;
        ison = sensor_listener_stop (this->listener);

        if ( ison != SENSOR_ERROR_NONE )
        {
        	return false;
        }

        this->activated = false;
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool isLightSupported (Light this_gen)
{
    if ( this_gen != NULL)
    {
        bool           supported = false;
        sensor_error_e errorcode = SENSOR_ERROR_NONE;
        errorcode = sensor_is_supported (SENSOR_LIGHT, &supported);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return false;
        }
        return supported;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

Light_data getLightValue (Light this_gen)
{
    Light_data invalidvs = {0,};
    if ( this_gen != NULL)
    {
        sensor_error_e errorcode;
        sensor_event_s data;
        LightExtend * this = (LightExtend *)this_gen;
        errorcode = sensor_listener_read_data (this->listener, &data);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return invalidvs;
        }
        Light_data vs;
        vs.level = data.values[0];

        vs.value_count = data.value_count;
        vs.timestamp   = data.timestamp;
        vs.accuracy    = data.accuracy;
        if ( this->activated == false )
        {
            vs.accuracy = SENSOR_DATA_ACCURACY_BAD;
        }
        return vs;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return invalidvs;

}

Proximity NewProximity (void)
{

    ProximityExtend * this = malloc (sizeof (ProximityExtend));

    this->proximity.Off            = ProximityOff;
    this->proximity.On             = ProximityOn;
    this->proximity.addCallback    = addProximityCallback;
    this->proximity.getValue       = getProximityValue;
    this->proximity.isSupported    = isProximitySupported;
    this->proximity.detachCallback = detachProximityCallback;

    this->type     = SENSOR_PROXIMITY;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor (this->type, &this->sensor);
    sensor_create_listener (this->sensor, &this->listener);

    return &this->proximity;
}

void DestroyProximity (Proximity this_gen)
{
    if ( this_gen != NULL)
    {

        ProximityExtend * this = (ProximityExtend *)this_gen;
        if ( this->listener )
        {
            sensor_listener_unset_event_cb (this->listener);
            sensor_listener_stop (this->listener);
            sensor_destroy_listener (this->listener);

        }
        free (this_gen);
    }
}

bool addProximityCallback (Proximity this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    if ( this_gen != NULL)
    {
        ProximityExtend * this = (ProximityExtend *)this_gen;

        sensor_error_e ret = sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool detachProximityCallback (Proximity this_gen)
{
    if ( this_gen != NULL)
    {

        ProximityExtend * this = (ProximityExtend *)this_gen;

        sensor_error_e ret = sensor_listener_unset_event_cb (this->listener);

        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }

        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool ProximityOn (Proximity this_gen)
{
    if ( this_gen != NULL)
    {
        ProximityExtend * this = (ProximityExtend *)this_gen;
        sensor_error_e ison = SENSOR_ERROR_NONE;
        ison = sensor_listener_start (this->listener);

        if ( ison != SENSOR_ERROR_NONE )
        {
            return false;
        }

        this->activated = true;
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool ProximityOff (Proximity this_gen)
{
    if ( this_gen != NULL)
    {
    	ProximityExtend * this = (ProximityExtend *)this_gen;
    	sensor_error_e ison = SENSOR_ERROR_NONE;
    	ison = sensor_listener_stop (this->listener);

    	if ( ison != SENSOR_ERROR_NONE )
    	{
    		return false;
    	}

    this->activated = false;
    return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool isProximitySupported (Proximity this_gen)
{
    if ( this_gen != NULL)
    {
        bool           supported = false;
        sensor_error_e errorcode = SENSOR_ERROR_NONE;
        errorcode = sensor_is_supported (SENSOR_PROXIMITY, &supported);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return false;
        }
        return supported;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

Proximity_data getProximityValue (Proximity this_gen)
{
    Proximity_data invalidvs = {0,};
    if ( this_gen != NULL)
    {
        sensor_error_e errorcode;
        sensor_event_s data;
        ProximityExtend * this = (ProximityExtend *)this_gen;
        errorcode = sensor_listener_read_data (this->listener, &data);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return invalidvs;
        }
        Proximity_data vs;
        vs.proximity = data.values[0];

        vs.value_count = data.value_count;
        vs.timestamp   = data.timestamp;
        vs.accuracy    = data.accuracy;
        if ( this->activated == false )
        {
            vs.accuracy = SENSOR_DATA_ACCURACY_BAD;
        }
        return vs;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return invalidvs;

}

Pressure NewPressure (void)
{

    PressureExtend * this = malloc (sizeof (PressureExtend));

    this->pressure.Off            = PressureOff;
    this->pressure.On             = PressureOn;
    this->pressure.addCallback    = addPressureCallback;
    this->pressure.getValue       = getPressureValue;
    this->pressure.isSupported    = isPressureSupported;
    this->pressure.detachCallback = detachPressureCallback;

    this->type     = SENSOR_PRESSURE;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor (this->type, &this->sensor);
    sensor_create_listener (this->sensor, &this->listener);

    return &this->pressure;
}

void DestroyPressure (Pressure this_gen)
{
    if ( this_gen != NULL)
    {

        PressureExtend * this = (PressureExtend *)this_gen;
        if ( this->listener )
        {
            sensor_listener_unset_event_cb (this->listener);
            sensor_listener_stop (this->listener);
            sensor_destroy_listener (this->listener);

        }
        free (this_gen);
    }
}

bool addPressureCallback (Pressure this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    if ( this_gen != NULL)
    {
        PressureExtend * this = (PressureExtend *)this_gen;

        sensor_error_e ret = sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool detachPressureCallback (Pressure this_gen)
{
    if ( this_gen != NULL)
    {

        PressureExtend * this = (PressureExtend *)this_gen;

        sensor_error_e ret = sensor_listener_unset_event_cb (this->listener);

        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }

        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool PressureOn (Pressure this_gen)
{
    if ( this_gen != NULL)
    {
        PressureExtend * this = (PressureExtend *)this_gen;
        sensor_error_e ison = SENSOR_ERROR_NONE;
        ison = sensor_listener_start (this->listener);

        if ( ison != SENSOR_ERROR_NONE )
        {
            return false;
        }

        this->activated = true;
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool PressureOff (Pressure this_gen)
{
    if ( this_gen != NULL)
    {
    	PressureExtend * this = (PressureExtend *)this_gen;
    	sensor_error_e ison = SENSOR_ERROR_NONE;
    	ison = sensor_listener_stop (this->listener);

    	if ( ison != SENSOR_ERROR_NONE )
    	{
    		return false;
    	}

    	this->activated = false;
    	return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool isPressureSupported (Pressure this_gen)
{
    if ( this_gen != NULL)
    {
        bool           supported = false;
        sensor_error_e errorcode = SENSOR_ERROR_NONE;
        errorcode = sensor_is_supported (SENSOR_PRESSURE, &supported);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return false;
        }
        return supported;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

Pressure_data getPressureValue (Pressure this_gen)
{
    Pressure_data invalidvs = {0,};
    if ( this_gen != NULL)
    {
        sensor_error_e errorcode;
        sensor_event_s data;
        PressureExtend * this = (PressureExtend *)this_gen;
        errorcode = sensor_listener_read_data (this->listener, &data);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return invalidvs;
        }
        Pressure_data vs;
        vs.hPa = data.values[0];

        vs.value_count = data.value_count;
        vs.timestamp   = data.timestamp;
        vs.accuracy    = data.accuracy;
        if ( this->activated == false )
        {
            vs.accuracy = SENSOR_DATA_ACCURACY_BAD;
        }
        return vs;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return invalidvs;

}

UltraViolet NewUltraViolet (void)
{

    UltraVioletExtend * this = malloc (sizeof (UltraVioletExtend));

    this->ultraviolet.Off            = UltraVioletOff;
    this->ultraviolet.On             = UltraVioletOn;
    this->ultraviolet.addCallback    = addUltraVioletCallback;
    this->ultraviolet.getValue       = getUltraVioletValue;
    this->ultraviolet.isSupported    = isUltraVioletSupported;
    this->ultraviolet.detachCallback = detachUltraVioletCallback;

    this->type     = SENSOR_ULTRAVIOLET;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor (this->type, &this->sensor);
    sensor_create_listener (this->sensor, &this->listener);

    return &this->ultraviolet;
}

void DestroyUltraViolet (UltraViolet this_gen)
{
    if ( this_gen != NULL)
    {

        UltraVioletExtend * this = (UltraVioletExtend *)this_gen;
        if ( this->listener )
        {
            sensor_listener_unset_event_cb (this->listener);
            sensor_listener_stop (this->listener);
            sensor_destroy_listener (this->listener);

        }
        free (this_gen);
    }
}

bool addUltraVioletCallback (UltraViolet this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    if ( this_gen != NULL)
    {
        UltraVioletExtend * this = (UltraVioletExtend *)this_gen;

        sensor_error_e ret = sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool detachUltraVioletCallback (UltraViolet this_gen)
{
    if ( this_gen != NULL)
    {

        UltraVioletExtend * this = (UltraVioletExtend *)this_gen;

        sensor_error_e ret = sensor_listener_unset_event_cb (this->listener);

        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }

        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool UltraVioletOn (UltraViolet this_gen)
{
    if ( this_gen != NULL)
    {
        UltraVioletExtend * this = (UltraVioletExtend *)this_gen;
        sensor_error_e ison = SENSOR_ERROR_NONE;
        ison = sensor_listener_start (this->listener);

        if ( ison != SENSOR_ERROR_NONE )
        {
            return false;
        }

        this->activated = true;
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool UltraVioletOff (UltraViolet this_gen)
{
    if ( this_gen != NULL)
    {
    	UltraVioletExtend * this = (UltraVioletExtend *)this_gen;
    	sensor_error_e ison = SENSOR_ERROR_NONE;
    	ison = sensor_listener_stop (this->listener);

    	if ( ison != SENSOR_ERROR_NONE )
    	{
    		return false;
    	}

    	this->activated = false;
    	return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool isUltraVioletSupported (UltraViolet this_gen)
{
    if ( this_gen != NULL)
    {
        bool           supported = false;
        sensor_error_e errorcode = SENSOR_ERROR_NONE;
        errorcode = sensor_is_supported (SENSOR_ULTRAVIOLET, &supported);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return false;
        }
        return supported;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

UltraViolet_data getUltraVioletValue (UltraViolet this_gen)
{
    UltraViolet_data invalidvs = {0,};
    if ( this_gen != NULL)
    {
        sensor_error_e errorcode;
        sensor_event_s data;
        UltraVioletExtend * this = (UltraVioletExtend *)this_gen;
        errorcode = sensor_listener_read_data (this->listener, &data);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return invalidvs;
        }
        UltraViolet_data vs;
        vs.uvindex = data.values[0];

        vs.value_count = data.value_count;
        vs.timestamp   = data.timestamp;
        vs.accuracy    = data.accuracy;
        if ( this->activated == false )
        {
            vs.accuracy = SENSOR_DATA_ACCURACY_BAD;
        }
        return vs;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return invalidvs;

}

Temperature NewTemperature (void)
{

    TemperatureExtend * this = malloc (sizeof (TemperatureExtend));

    this->temperature.Off            = TemperatureOff;
    this->temperature.On             = TemperatureOn;
    this->temperature.addCallback    = addTemperatureCallback;
    this->temperature.getValue       = getTemperatureValue;
    this->temperature.isSupported    = isTemperatureSupported;
    this->temperature.detachCallback = detachTemperatureCallback;

    this->type     = SENSOR_TEMPERATURE;
    this->listener = NULL;
    this->sensor   = NULL;

    sensor_get_default_sensor (this->type, &this->sensor);
    sensor_create_listener (this->sensor, &this->listener);

    return &this->temperature;
}

void DestroyTemperature (Temperature this_gen)
{
    if ( this_gen != NULL)
    {

        TemperatureExtend * this = (TemperatureExtend *)this_gen;
        if ( this->listener )
        {
            sensor_listener_unset_event_cb (this->listener);
            sensor_listener_stop (this->listener);
            sensor_destroy_listener (this->listener);

        }
        free (this_gen);
    }
}

bool addTemperatureCallback (Temperature this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    if ( this_gen != NULL)
    {
        TemperatureExtend * this = (TemperatureExtend *)this_gen;

        sensor_error_e ret = sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool detachTemperatureCallback (Temperature this_gen)
{
    if ( this_gen != NULL)
    {

        TemperatureExtend * this = (TemperatureExtend *)this_gen;

        sensor_error_e ret = sensor_listener_unset_event_cb (this->listener);

        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }

        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool TemperatureOn (Temperature this_gen)
{
    if ( this_gen != NULL)
    {
        TemperatureExtend * this = (TemperatureExtend *)this_gen;
        sensor_error_e ison = SENSOR_ERROR_NONE;
        ison = sensor_listener_start (this->listener);

        if ( ison != SENSOR_ERROR_NONE )
        {
            return false;
        }

        this->activated = true;
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool TemperatureOff (Temperature this_gen)
{
    if ( this_gen != NULL)
    {
    	TemperatureExtend * this = (TemperatureExtend *)this_gen;
    	sensor_error_e ison = SENSOR_ERROR_NONE;
    	ison = sensor_listener_stop (this->listener);

    	if ( ison != SENSOR_ERROR_NONE )
    	{
    		return false;
    	}

    	this->activated = false;
    	return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool isTemperatureSupported (Temperature this_gen)
{
    if ( this_gen != NULL)
    {
        bool           supported = false;
        sensor_error_e errorcode = SENSOR_ERROR_NONE;
        errorcode = sensor_is_supported (SENSOR_TEMPERATURE, &supported);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return false;
        }
        return supported;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

Temperature_data getTemperatureValue (Temperature this_gen)
{
    Temperature_data invalidvs = {0,};
    if ( this_gen != NULL)
    {
        sensor_error_e errorcode;
        sensor_event_s data;
        TemperatureExtend * this = (TemperatureExtend *)this_gen;
        errorcode = sensor_listener_read_data (this->listener, &data);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return invalidvs;
        }
        Temperature_data vs;
        vs.celsius = data.values[0];

        vs.value_count = data.value_count;
        vs.timestamp   = data.timestamp;
        vs.accuracy    = data.accuracy;

        if ( this->activated == false )
        {
            vs.accuracy = SENSOR_DATA_ACCURACY_BAD;
        }
        return vs;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return invalidvs;

}

Humidity NewHumidity (void)
{

    HumidityExtend * this = malloc (sizeof (HumidityExtend));

    this->humidity.Off            = HumidityOff;
    this->humidity.On             = HumidityOn;
    this->humidity.addCallback    = addHumidityCallback;
    this->humidity.getValue       = getHumidityValue;
    this->humidity.isSupported    = isHumiditySupported;
    this->humidity.detachCallback = detachHumidityCallback;
    this->type                    = SENSOR_HUMIDITY;
    this->listener                = NULL;
    this->sensor                  = NULL;

    sensor_get_default_sensor (this->type, &this->sensor);
    sensor_create_listener (this->sensor, &this->listener);

    return &this->humidity;
}

void DestroyHumidity (Humidity this_gen)
{
    if ( this_gen != NULL)
    {

        HumidityExtend * this = (HumidityExtend *)this_gen;
        if ( this->listener )
        {
            sensor_listener_unset_event_cb (this->listener);
            sensor_listener_stop (this->listener);
            sensor_destroy_listener (this->listener);

        }
        free (this_gen);
    }
}

bool addHumidityCallback (Humidity this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
{
    if ( this_gen != NULL)
    {
        HumidityExtend * this = (HumidityExtend *)this_gen;

        sensor_error_e ret = sensor_listener_set_event_cb (this->listener, timeinterval, sensorCallback, data);
        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool detachHumidityCallback (Humidity this_gen)
{
    if ( this_gen != NULL)
    {

        HumidityExtend * this = (HumidityExtend *)this_gen;

        sensor_error_e ret = sensor_listener_unset_event_cb (this->listener);

        if ( ret != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (ret));
            return false;
        }

        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

bool HumidityOn (Humidity this_gen)
{
    if ( this_gen != NULL)
    {
        HumidityExtend * this = (HumidityExtend *)this_gen;
        sensor_error_e ison = SENSOR_ERROR_NONE;
        ison = sensor_listener_start (this->listener);

        if ( ison != SENSOR_ERROR_NONE )
        {
            return false;
        }

        this->activated = true;
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool HumidityOff (Humidity this_gen)
{
    if ( this_gen != NULL)
    {
    	HumidityExtend * this = (HumidityExtend *)this_gen;
    	sensor_error_e ison = SENSOR_ERROR_NONE;
    	ison = sensor_listener_stop (this->listener);

    	if ( ison != SENSOR_ERROR_NONE )
    	{
    		return false;
    	}

    	this->activated = false;
    	return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool isHumiditySupported (Humidity this_gen)
{
    if ( this_gen != NULL)
    {
        bool           supported = false;
        sensor_error_e errorcode = SENSOR_ERROR_NONE;
        errorcode = sensor_is_supported (SENSOR_HUMIDITY, &supported);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return false;
        }
        return supported;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;

}

Humidity_data getHumidityValue (Humidity this_gen)
{
    Humidity_data invalidvs = {0,};
    if ( this_gen != NULL)
    {
        sensor_error_e errorcode;
        sensor_event_s data;
        HumidityExtend * this = (HumidityExtend *)this_gen;
        errorcode = sensor_listener_read_data (this->listener, &data);
        if ( errorcode != SENSOR_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", SensorErrorCheck (errorcode));
            return invalidvs;
        }
        Humidity_data vs;
        vs.percent = data.values[0];

        vs.value_count = data.value_count;
        vs.timestamp   = data.timestamp;
        vs.accuracy    = data.accuracy;
        if ( this->activated == false )
        {
            vs.accuracy = SENSOR_DATA_ACCURACY_BAD;
        }
        return vs;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return invalidvs;

}

const char * SensorErrorCheck (int errorCode)
{

    switch (errorCode)
    {
    case SENSOR_ERROR_NONE:
        return "SENSOR_ERROR_NONE: Successful";

    case SENSOR_ERROR_IO_ERROR:
        return "SENSOR_ERROR_IO_ERROR: I/O error";

    case SENSOR_ERROR_INVALID_PARAMETER:
        return "SENSOR_ERROR_INVALID_PARAMETER: Invalid parameter";

    case SENSOR_ERROR_NOT_SUPPORTED:
        return "SENSOR_ERROR_NOT_SUPPORTED: Unsupported sensor in the current device";

    case SENSOR_ERROR_PERMISSION_DENIED:
        return "SENSOR_ERROR_PERMISSION_DENIED: Permission denied";

    case SENSOR_ERROR_OUT_OF_MEMORY:
        return "SENSOR_ERROR_OUT_OF_MEMORY: Out of memory";

    case SENSOR_ERROR_NOT_NEED_CALIBRATION:
        return "SENSOR_ERROR_NOT_NEED_CALIBRATION: Sensor doesn't need calibration";

    case SENSOR_ERROR_OPERATION_FAILED:
        return "SENSOR_ERROR_OPERATION_FAILED: Operation failed";

    default:
        return "SENSOR_ERROR_UNKNOWN";

    }
}
