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

sensor_event_s getAllSensorData();
bool hasBarometer();
sensor_event_s getBarometerData();
bool hasMagnetoMeter();
sensor_event_s getMagnetoMeterData();
bool hasPhotoMeter();
sensor_event_s getPhotoMeterData();
bool hasProximity();
sensor_event_s getProximityData();
bool hasTiltMeter();
sensor_event_s getTiltMeterData();
bool hasTemperature();
sensor_event_s getTemperatureData();
bool hasUltraViolet();
sensor_event_s getUltraVioletData();
bool hasHumidity();
sensor_event_s getHumidityData();
bool hasLinearAccelation();
sensor_event_s getLinearAccelation();
bool hasRotationVector();
sensor_event_s getRotationVectorData();
bool hasGravity();
sensor_event_s getGravityData();


typedef struct _SensorExtend{

} SensorExtend;


#ifdef __cplusplus
}
#endif

#endif //DIT_SENSOR_H
