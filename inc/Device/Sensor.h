#ifndef DIT_SENSOR_H
#define DIT_SENSOR_H

#include "dit.h"
#include <stdbool.h>
#include <stdalign.h>
#include <sensor.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Sensor Sensor;
typedef struct _Sensor {

}Sensor;


Sensor* NewSensor();

void DestroySensor(Sensor* this_gen);

sensor_event_s getAllSensorData(Sensor* this_gen);

bool hasBarometer(Sensor* this_gen);

sensor_event_s getBarometerData(Sensor* this_gen);

bool hasMagnetoMeter(Sensor* this_gen);

sensor_event_s getMagnetoMeterData(Sensor* this_gen);

bool hasPhotoMeter(Sensor* this_gen);

sensor_event_s getPhotoMeterData(Sensor* this_gen);

bool hasProximity(Sensor* this_gen);

sensor_event_s getProximityData(Sensor* this_gen);

bool hasTiltMeter(Sensor* this_gen);

sensor_event_s getTiltMeterData(Sensor* this_gen);

bool hasTemperature(Sensor* this_gen);

sensor_event_s getTemperatureData(Sensor* this_gen);

bool hasUltraViolet(Sensor* this_gen);

sensor_event_s getUltraVioletData(Sensor* this_gen);

bool hasHumidity(Sensor* this_gen);

sensor_event_s getHumidityData(Sensor* this_gen);

bool hasLinearAccelation(Sensor* this_gen);

sensor_event_s getLinearAccelation(Sensor* this_gen);

bool hasRotationVector(Sensor* this_gen);

sensor_event_s getRotationVectorData(Sensor* this_gen);

bool hasGravity(Sensor* this_gen);

sensor_event_s getGravityData(Sensor* this_gen);

typedef struct _SensorExtend{

} SensorExtend;


#ifdef __cplusplus
}
#endif

#endif //DIT_SENSOR_H
