#ifndef DIT_SENSOR_H
#define DIT_SENSOR_H

#include <stdbool.h>
#include <stdalign.h>

#include "dit.h"

#include <sensor.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (* sensor_callback) (sensor_h sensor, sensor_event_s * event, void * user_data);

typedef struct _3d_data
{
    float x;
    float y;
    float z;

    int                    value_count;
    int                    accuracy;
    unsigned long long int timestamp;

} _3d_data;

typedef struct _3d_data Accelerometer_data;
typedef struct _3d_data Gravity_data;
typedef struct _3d_data LinearAcceleration_data;
typedef struct _3d_data Magnetometer_data;
typedef struct _3d_data Orientation_data;
typedef struct _3d_data Gyroscope_data;

typedef struct _4d_data
{

    float x;
    float y;
    float z;
    float w;

    int                    value_count;
    int                    accuracy;
    unsigned long long int timestamp;

} RotationVector_data;

typedef struct _Light_data
{
    float                  level;
    int                    value_count;
    int                    accuracy;
    unsigned long long int timestamp;
} Light_data;

typedef struct _Proximity_data
{
    float                  proximity;
    int                    value_count;
    int                    accuracy;
    unsigned long long int timestamp;
} Proximity_data;

typedef struct _Pressure_data
{
    float                  hPa;
    int                    value_count;
    int                    accuracy;
    unsigned long long int timestamp;
} Pressure_data;

typedef struct _UltraViolet_data
{
    float                  uvindex;
    int                    value_count;
    int                    accuracy;
    unsigned long long int timestamp;
} UltraViolet_data;

typedef struct _Temperature_data
{
    float                  celsius;
    int                    value_count;
    int                    accuracy;
    unsigned long long int timestamp;
} Temperature_data;

typedef struct _Humidity_data
{
    float                  percent;
    int                    value_count;
    int                    accuracy;
    unsigned long long int timestamp;
} Humidity_data;

typedef struct _Accelerometer * Accelerometer;

struct _Accelerometer
{

    void(* addCallback) (Accelerometer this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

    void(* On) (Accelerometer this_gen);

    void(* Off) (Accelerometer this_gen);

    bool(* isSupported) (Accelerometer this_gen);

    Accelerometer_data(* getValue) (Accelerometer this_gen);

};

typedef struct _AccelerometerExtend
{
    struct _Accelerometer accelerometer;
    sensor_type_e         type;
    sensor_h              sensor;
    sensor_listener_h     listener;

} AccelerometerExtend;

Accelerometer NewAccelerometer ();

void DestroyAccelerometer (Accelerometer this_gen);

void addAccelerometerCallback (Accelerometer this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

void AccelerometerOn (Accelerometer this_gen);

void AccelerometerOff (Accelerometer this_gen);

bool isAccelerometerSupported (Accelerometer this_gen);

Accelerometer_data getAccelerometerValue (Accelerometer this_gen);

typedef struct _Gravity * Gravity;

struct _Gravity
{

    void(* addCallback) (Gravity this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

    void(* On) (Gravity this_gen);

    void(* Off) (Gravity this_gen);

    bool(* isSupported) (Gravity this_gen);

    Gravity_data (* getValue) (Gravity this_gen);

};

typedef struct _GravityExtend
{
    struct _Gravity   gravity;
    sensor_type_e     type;
    sensor_h          sensor;
    sensor_listener_h listener;

} GravityExtend;

Gravity NewGravity ();

void DestroyGravity (Gravity this_gen);

void addGravityCallback (Gravity this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

void GravityOn (Gravity this_gen);

void GravityOff (Gravity this_gen);

bool isGravitySupported (Gravity this_gen);

Gravity_data getGravityValue (Gravity this_gen);

typedef struct _LinearAccelation * LinearAccelation;

struct _LinearAccelation
{

    void(* addCallback) (LinearAccelation this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

    void(* On) (LinearAccelation this_gen);

    void(* Off) (LinearAccelation this_gen);

    bool(* isSupported) (LinearAccelation this_gen);

    LinearAcceleration_data (* getValue) (LinearAccelation this_gen);

};

typedef struct _LinearAccelationExtend
{
    struct _LinearAccelation linearaccelation;
    sensor_type_e            type;
    sensor_h                 sensor;
    sensor_listener_h        listener;

} LinearAccelationExtend;

LinearAccelation NewLinearAccelation ();

void DestroyLinearAccelation (LinearAccelation this_gen);

void addLinearAccelationCallback (LinearAccelation this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

void LinearAccelationOn (LinearAccelation this_gen);

void LinearAccelationOff (LinearAccelation this_gen);

bool isLinearAccelationSupported (LinearAccelation this_gen);

LinearAcceleration_data getLinearAccelationValue (LinearAccelation this_gen);

typedef struct _MagnetoMeter * MagnetoMeter;

struct _MagnetoMeter
{

    void(* addCallback) (MagnetoMeter this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

    void(* On) (MagnetoMeter this_gen);

    void(* Off) (MagnetoMeter this_gen);

    bool(* isSupported) (MagnetoMeter this_gen);

    Magnetometer_data (* getValue) (MagnetoMeter this_gen);

};

typedef struct _MagnetoMeterExtend
{
    struct _MagnetoMeter magnetometer;
    sensor_type_e        type;
    sensor_h             sensor;
    sensor_listener_h    listener;

} MagnetoMeterExtend;

MagnetoMeter NewMagnetoMeter ();

void DestroyMagnetoMeter (MagnetoMeter this_gen);

void addMagnetoMeterCallback (MagnetoMeter this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

void MagnetoMeterOn (MagnetoMeter this_gen);

void MagnetoMeterOff (MagnetoMeter this_gen);

bool isMagnetoMeterSupported (MagnetoMeter this_gen);

Magnetometer_data getMagnetoMeterValue (MagnetoMeter this_gen);

typedef struct _RotationVector * RotationVector;

struct _RotationVector
{

    void(* addCallback) (RotationVector this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

    void(* On) (RotationVector this_gen);

    void(* Off) (RotationVector this_gen);

    bool(* isSupported) (RotationVector this_gen);

    RotationVector_data (* getValue) (RotationVector this_gen);

};

typedef struct _RotationVectorExtend
{
    struct _RotationVector rotationvector;
    sensor_type_e          type;
    sensor_h               sensor;
    sensor_listener_h      listener;

} RotationVectorExtend;

RotationVector NewRotationVector ();

void DestroyRotationVector (RotationVector this_gen);

void addRotationVectorCallback (RotationVector this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

void RotationVectorOn (RotationVector this_gen);

void RotationVectorOff (RotationVector this_gen);

bool isRotationVectorSupported (RotationVector this_gen);

RotationVector_data getRotationVectorValue (RotationVector this_gen);

typedef struct _Orientation * Orientation;

struct _Orientation
{

    void(* addCallback) (Orientation this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

    void(* On) (Orientation this_gen);

    void(* Off) (Orientation this_gen);

    bool(* isSupported) (Orientation this_gen);

    Orientation_data (* getValue) (Orientation this_gen);

};

typedef struct _OrientationExtend
{
    struct _Orientation orientation;
    sensor_type_e       type;
    sensor_h            sensor;
    sensor_listener_h   listener;

} OrientationExtend;

Orientation NewOrientation ();

void DestroyOrientation (Orientation this_gen);

void addOrientationCallback (Orientation this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

void OrientationOn (Orientation this_gen);

void OrientationOff (Orientation this_gen);

bool isOrientationSupported (Orientation this_gen);

Orientation_data getOrientationValue (Orientation this_gen);

typedef struct _Gyroscope * Gyroscope;

struct _Gyroscope
{

    void(* addCallback) (Gyroscope this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

    void(* On) (Gyroscope this_gen);

    void(* Off) (Gyroscope this_gen);

    bool(* isSupported) (Gyroscope this_gen);

    Gyroscope_data (* getValue) (Gyroscope this_gen);

};

typedef struct _GyroscopeExtend
{
    struct _Gyroscope gyroscope;
    sensor_type_e     type;
    sensor_h          sensor;
    sensor_listener_h listener;

} GyroscopeExtend;

Gyroscope NewGyroscope ();

void DestroyGyroscope (Gyroscope this_gen);

void addGyroscopeCallback (Gyroscope this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

void GyroscopeOn (Gyroscope this_gen);

void GyroscopeOff (Gyroscope this_gen);

bool isGyroscopeSupported (Gyroscope this_gen);

Gyroscope_data getGyroscopeValue (Gyroscope this_gen);

typedef struct _Light * Light;

struct _Light
{

    void(* addCallback) (Light this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

    void(* On) (Light this_gen);

    void(* Off) (Light this_gen);

    bool(* isSupported) (Light this_gen);

    Light_data (* getValue) (Light this_gen);

};

typedef struct _LightExtend
{
    struct _Light     light;
    sensor_type_e     type;
    sensor_h          sensor;
    sensor_listener_h listener;

} LightExtend;

Light NewLight ();

void DestroyLight (Light this_gen);

void addLightCallback (Light this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

void LightOn (Light this_gen);

void LightOff (Light this_gen);

bool isLightSupported (Light this_gen);

Light_data getLightValue (Light this_gen);

typedef struct _Proximity * Proximity;

struct _Proximity
{

    void(* addCallback) (Proximity this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

    void(* On) (Proximity this_gen);

    void(* Off) (Proximity this_gen);

    bool(* isSupported) (Proximity this_gen);

    Proximity_data (* getValue) (Proximity this_gen);

};

typedef struct _ProximityExtend
{
    struct _Proximity proximity;
    sensor_type_e     type;
    sensor_h          sensor;
    sensor_listener_h listener;

} ProximityExtend;

Proximity NewProximity ();

void DestroyProximity (Proximity this_gen);

void addProximityCallback (Proximity this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

void ProximityOn (Proximity this_gen);

void ProximityOff (Proximity this_gen);

bool isProximitySupported (Proximity this_gen);

Proximity_data getProximityValue (Proximity this_gen);

typedef struct _Pressure * Pressure;

struct _Pressure
{

    void(* addCallback) (Pressure this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

    void(* On) (Pressure this_gen);

    void(* Off) (Pressure this_gen);

    bool(* isSupported) (Pressure this_gen);

    Pressure_data (* getValue) (Pressure this_gen);

};

typedef struct _PressureExtend
{
    struct _Pressure  pressure;
    sensor_type_e     type;
    sensor_h          sensor;
    sensor_listener_h listener;

} PressureExtend;

Pressure NewPressure ();

void DestroyPressure (Pressure this_gen);

void addPressureCallback (Pressure this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

void PressureOn (Pressure this_gen);

void PressureOff (Pressure this_gen);

bool isPressureSupported (Pressure this_gen);

Pressure_data getPressureValue (Pressure this_gen);

typedef struct _UltraViolet * UltraViolet;

struct _UltraViolet
{

    void(* addCallback) (UltraViolet this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

    void(* On) (UltraViolet this_gen);

    void(* Off) (UltraViolet this_gen);

    bool(* isSupported) (UltraViolet this_gen);

    UltraViolet_data (* getValue) (UltraViolet this_gen);

};

typedef struct _UltraVioletExtend
{
    struct _UltraViolet ultraviolet;
    sensor_type_e       type;
    sensor_h            sensor;
    sensor_listener_h   listener;

} UltraVioletExtend;

UltraViolet NewUltraViolet ();

void DestroyUltraViolet (UltraViolet this_gen);

void addUltraVioletCallback (UltraViolet this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

void UltraVioletOn (UltraViolet this_gen);

void UltraVioletOff (UltraViolet this_gen);

bool isUltraVioletSupported (UltraViolet this_gen);

UltraViolet_data getUltraVioletValue (UltraViolet this_gen);

typedef struct _Temperature * Temperature;

struct _Temperature
{

    void(* addCallback) (Temperature this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

    void(* On) (Temperature this_gen);

    void(* Off) (Temperature this_gen);

    bool(* isSupported) (Temperature this_gen);

    Temperature_data (* getValue) (Temperature this_gen);

};

typedef struct _TemperatureExtend
{
    struct _Temperature temperature;
    sensor_type_e       type;
    sensor_h            sensor;
    sensor_listener_h   listener;

} TemperatureExtend;

Temperature NewTemperature ();

void DestroyTemperature (Temperature this_gen);

void addTemperatureCallback (Temperature this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

void TemperatureOn (Temperature this_gen);

void TemperatureOff (Temperature this_gen);

bool isTemperatureSupported (Temperature this_gen);

Temperature_data getTemperatureValue (Temperature this_gen);

typedef struct _Humidity * Humidity;

struct _Humidity
{

    void(* addCallback) (Humidity this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

    void(* On) (Humidity this_gen);

    void(* Off) (Humidity this_gen);

    bool(* isSupported) (Humidity this_gen);

    Humidity_data (* getValue) (Humidity this_gen);

};

typedef struct _HumidityExtend
{
    struct _Humidity  humidity;
    sensor_type_e     type;
    sensor_h          sensor;
    sensor_listener_h listener;

} HumidityExtend;

Humidity NewHumidity ();

void DestroyHumidity (Humidity this_gen);

void addHumidityCallback (Humidity this_gen, sensor_callback sensorCallback, int timeenterval, void * data);

void HumidityOn (Humidity this_gen);

void HumidityOff (Humidity this_gen);

bool isHumiditySupported (Humidity this_gen);

Humidity_data getHumidityValue (Humidity this_gen);

#ifdef __cplusplus
}
#endif

#endif //DIT_SENSOR_H
