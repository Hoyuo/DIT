#include "Device/Sensor.h"
#include <stdlib.h>
#include <sensor.h>

Sensor* NewSensor()
{
	SensorExtend* this = (SensorExtend*)malloc(sizeof(SensorExtend));
	this->sensor.getAllSensorData = getAllSensorData;
	this->sensor.hasBarometer = hasBarometer;
	this->sensor.getBarometerData = getBarometerData;
	this->sensor.hasMagnetoMeter = hasMagnetoMeter;
	this->sensor.getMagnetoMeterData = getMagnetoMeterData;
	this->sensor.hasPhotoMeter = hasPhotoMeter;
	this->sensor.getPhotoMeterData = getPhotoMeterData;
	this->sensor.hasProximity = hasProximity;
	this->sensor.getProximityData = getProximityData;
	this->sensor.hasTiltMeter = hasTiltMeter;
	this->sensor.getTiltMeterData = getTiltMeterData;
	this->sensor.hasTemperature = hasTemperature;
	this->sensor.getTemperatureData = getTemperatureData;
	this->sensor.hasUltraViolet = hasUltraViolet;
	this->sensor.getUltraVioletData = getUltraVioletData;
	this->sensor.hasHumidity = hasHumidity;
	this->sensor.getHumidityData = getHumidityData;
	this->sensor.hasLinearAccelation = hasLinearAccelation;
	this->sensor.getLinearAccelation = getLinearAccelation;
	this->sensor.hasRotationVector = hasRotationVector;
	this->sensor.getRotationVectorData = getRotationVectorData;
	this->sensor.hasGravity = hasGravity;
	this->sensor.getGravityData = getGravityData;

	return this->sensor;
}

void DestroySensor(Sensor* this_gen)
{
	if (this_gen != NULL)
	{
		SensorExtend* this = (SensorExtend*) this_gen;
		free(this);
	}
}

SensorValue getAllSensorData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

bool hasBarometer(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

SensorValue getBarometerData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

bool hasMagnetoMeter(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

SensorValue getMagnetoMeterData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

bool hasPhotoMeter(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

SensorValue getPhotoMeterData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

bool hasProximity(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

SensorValue getProximityData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

bool hasTiltMeter(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

SensorValue getTiltMeterData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

bool hasTemperature(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

SensorValue getTemperatureData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

bool hasUltraViolet(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

SensorValue getUltraVioletData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

bool hasHumidity(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

SensorValue getHumidityData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

bool hasLinearAccelation(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

SensorValue getLinearAccelation(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

bool hasRotationVector(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

SensorValue getRotationVectorData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

bool hasGravity(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}

SensorValue getGravityData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
}
