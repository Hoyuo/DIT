#ifndef DIT_SENSOR_H
#define DIT_SENSOR_H

#include "dit.h"
#include <stdbool.h>
#include <stdalign.h>
#include <sensor.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _SensorValue {
	float values[MAX_VALUE_SIZE];
}SensorValue;

typedef struct _Sensor Sensor;
typedef struct _Sensor {
	SensorValue (* getAllSensorData)(Sensor* this_gen);

	bool (* hasBarometer)(Sensor* this_gen);

	SensorValue (* getBarometerData)(Sensor* this_gen);

	bool (* hasMagnetoMeter)(Sensor* this_gen);

	SensorValue (* getMagnetoMeterData)(Sensor* this_gen);

	bool (* hasPhotoMeter)(Sensor* this_gen);

	SensorValue (* getPhotoMeterData)(Sensor* this_gen);

	bool (* hasProximity)(Sensor* this_gen);

	SensorValue (* getProximityData)(Sensor* this_gen);

	bool (* hasTiltMeter)(Sensor* this_gen);

	SensorValue (* getTiltMeterData)(Sensor* this_gen);

	bool (* hasTemperature)(Sensor* this_gen);

	SensorValue (* getTemperatureData)(Sensor* this_gen);

	bool (* hasUltraViolet)(Sensor* this_gen);

	SensorValue (* getUltraVioletData)(Sensor* this_gen);

	bool (* hasHumidity)(Sensor* this_gen);

	SensorValue (* getHumidityData)(Sensor* this_gen);

	bool (* hasLinearAccelation)(Sensor* this_gen);

	SensorValue (* getLinearAccelation)(Sensor* this_gen);

	bool (* hasRotationVector)(Sensor* this_gen);

	SensorValue (* getRotationVectorData)(Sensor* this_gen);

	bool (* hasGravity)(Sensor* this_gen);

	SensorValue (* getGravityData)(Sensor* this_gen);

}Sensor;


Sensor* NewSensor();

void DestroySensor(Sensor* this_gen);

SensorValue getAllSensorData(Sensor* this_gen);

bool hasBarometer(Sensor* this_gen);

SensorValue getBarometerData(Sensor* this_gen);

bool hasMagnetoMeter(Sensor* this_gen);

SensorValue getMagnetoMeterData(Sensor* this_gen);

bool hasPhotoMeter(Sensor* this_gen);

SensorValue getPhotoMeterData(Sensor* this_gen);

bool hasProximity(Sensor* this_gen);

SensorValue getProximityData(Sensor* this_gen);

bool hasTiltMeter(Sensor* this_gen);

SensorValue getTiltMeterData(Sensor* this_gen);

bool hasTemperature(Sensor* this_gen);

SensorValue getTemperatureData(Sensor* this_gen);

bool hasUltraViolet(Sensor* this_gen);

SensorValue getUltraVioletData(Sensor* this_gen);

bool hasHumidity(Sensor* this_gen);

SensorValue getHumidityData(Sensor* this_gen);

bool hasLinearAccelation(Sensor* this_gen);

SensorValue getLinearAccelation(Sensor* this_gen);

bool hasRotationVector(Sensor* this_gen);

SensorValue getRotationVectorData(Sensor* this_gen);

bool hasGravity(Sensor* this_gen);

SensorValue getGravityData(Sensor* this_gen);

typedef struct _SensorExtend{
	Sensor sensor;
} SensorExtend;


#ifdef __cplusplus
}
#endif

#endif //DIT_SENSOR_H
