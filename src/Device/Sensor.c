#include "Device/Sensor.h"
#include <stdlib.h>
#include <sensor.h>

Sensor* NewSensor()
{
	SensorExtend* this = (SensorExtend*)malloc(sizeof(SensorExtend));
	this->sensor.getAllSensorData = getAllSensorData;
	this->sensor.hasAccelerometer = hasAccelerometer;
	this->sensor.getAccelerometerData = getAccelerometerData;
	this->sensor.hasGravity = hasGravity;
	this->sensor.getGravityData = getGravityData;
	this->sensor.hasLinearAccelation = hasLinearAccelation;
	this->sensor.getLinearAccelationData = getAllSensorData;
	this->sensor.hasMagnetoMeter = hasMagnetoMeter;
	this->sensor.getMagnetoMeterData = getMagnetoMeterData;
	this->sensor.hasRotationVector = hasRotationVector;
	this->sensor.getRotationVectorData = getRotationVectorData;
	this->sensor.hasOrientation = hasOrientation;
	this->sensor.getOrientationData = getOrientationData;
	this->sensor.hasGyroscope = hasGyroscope;
	this->sensor.getGyroscopeData = getGyroscopeData;
	this->sensor.hasLight = hasLight;
	this->sensor.getLightData = getLightData;
	this->sensor.hasProximity = hasProximity;
	this->sensor.getProximityData = getProximityData;
	this->sensor.hasPressure = hasPressure;
	this->sensor.getPressureData = getPressureData;
	this->sensor.hasUltraViolet = hasUltraViolet;
	this->sensor.getUltraVioletData = getUltraVioletData;
	this->sensor.hasTemperature = hasTemperature;
	this->sensor.getTemperatureData = getTemperatureData;
	this->sensor.hasHumidity = hasHumidity;
	this->sensor.getHumidityData = getHumidityData;

	return &this->sensor;
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
	this->type = SENSOR_ALL;
	sensor_h *list;

	this->error = sensor_get_default_sensor(this->type, &list);
	this->error = sensor_create_listener(this->sensors, &this->listener);
	this->error = sensor_listener_start(this->listener);
	this->error = sensor_listener_read_data(this->listener, &this->event);

	SensorValue data;
	for(int i=0; i<MAX_VALUE_SIZE;i++)
		data.values[i] = this->event.values[i];

	this->error = sensor_listener_stop(this->listener);
	this->error = sensor_destroy_listener(this->listener);

	free(list);
	return data;
}

bool hasAccelerometer(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	bool supported;
	this->type = SENSOR_ACCELEROMETER;
	this->error = sensor_is_supported(this->type, &supported);

	return supported;
}

SensorValue getAccelerometerData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	this->type = SENSOR_ACCELEROMETER;
	this->error = sensor_get_default_sensor(this->type, &this->sensors);
	this->error = sensor_create_listener(this->sensors, &this->listener);
	this->error = sensor_listener_start(this->listener);
	this->error = sensor_listener_read_data(this->listener, &this->event);

	SensorValue data;
	for(int i=0; i<MAX_VALUE_SIZE;i++)
		data.values[i] = this->event.values[i];

	this->error = sensor_listener_stop(this->listener);
	this->error = sensor_destroy_listener(this->listener);

	return data;
}

bool hasGravity(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	bool supported;
	this->type = SENSOR_GRAVITY;
	this->error = sensor_is_supported(this->type, &supported);

	return supported;
}

SensorValue getGravityData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	this->type = SENSOR_GRAVITY;
	this->error = sensor_get_default_sensor(this->type, &this->sensors);
	this->error = sensor_create_listener(this->sensors, &this->listener);
	this->error = sensor_listener_start(this->listener);
	this->error = sensor_listener_read_data(this->listener, &this->event);

	SensorValue data;
	for(int i=0; i<MAX_VALUE_SIZE;i++)
		data.values[i] = this->event.values[i];

	this->error = sensor_listener_stop(this->listener);
	this->error = sensor_destroy_listener(this->listener);

	return data;
}

bool hasLinearAccelation(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	bool supported;
	this->type = SENSOR_LINEAR_ACCELERATION;
	this->error = sensor_is_supported(this->type, &supported);

	return supported;
}

SensorValue getLinearAccelationData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	this->type = SENSOR_LINEAR_ACCELERATION;
	this->error = sensor_get_default_sensor(this->type, &this->sensors);
	this->error = sensor_create_listener(this->sensors, &this->listener);
	this->error = sensor_listener_start(this->listener);
	this->error = sensor_listener_read_data(this->listener, &this->event);

	SensorValue data;
	for(int i=0; i<MAX_VALUE_SIZE;i++)
		data.values[i] = this->event.values[i];

	this->error = sensor_listener_stop(this->listener);
	this->error = sensor_destroy_listener(this->listener);

	return data;
}

bool hasMagnetoMeter(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	bool supported;
	this->type = SENSOR_MAGNETIC;
	this->error = sensor_is_supported(this->type, &supported);

	return supported;
}

SensorValue getMagnetoMeterData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	this->type = SENSOR_MAGNETIC;
	this->error = sensor_get_default_sensor(this->type, &this->sensors);
	this->error = sensor_create_listener(this->sensors, &this->listener);
	this->error = sensor_listener_start(this->listener);
	this->error = sensor_listener_read_data(this->listener, &this->event);

	SensorValue data;
	for(int i=0; i<MAX_VALUE_SIZE;i++)
		data.values[i] = this->event.values[i];

	this->error = sensor_listener_stop(this->listener);
	this->error = sensor_destroy_listener(this->listener);

	return data;
}

bool hasRotationVector(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	bool supported;
	this->type = SENSOR_ROTATION_VECTOR;
	this->error = sensor_is_supported(this->type, &supported);

	return supported;
}

SensorValue getRotationVectorData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	this->type = SENSOR_ROTATION_VECTOR;
	this->error = sensor_get_default_sensor(this->type, &this->sensors);
	this->error = sensor_create_listener(this->sensors, &this->listener);
	this->error = sensor_listener_start(this->listener);
	this->error = sensor_listener_read_data(this->listener, &this->event);

	SensorValue data;
	for(int i=0; i<MAX_VALUE_SIZE;i++)
		data.values[i] = this->event.values[i];

	this->error = sensor_listener_stop(this->listener);
	this->error = sensor_destroy_listener(this->listener);

	return data;
}

bool hasOrientation(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	bool supported;
	this->type = SENSOR_ORIENTATION;
	this->error = sensor_is_supported(this->type, &supported);

	return supported;
}

SensorValue getOrientationData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	this->type = SENSOR_ORIENTATION;
	this->error = sensor_get_default_sensor(this->type, &this->sensors);
	this->error = sensor_create_listener(this->sensors, &this->listener);
	this->error = sensor_listener_start(this->listener);
	this->error = sensor_listener_read_data(this->listener, &this->event);

	SensorValue data;
	for(int i=0; i<MAX_VALUE_SIZE;i++)
		data.values[i] = this->event.values[i];

	this->error = sensor_listener_stop(this->listener);
	this->error = sensor_destroy_listener(this->listener);

	return data;
}

bool hasGyroscope(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	bool supported;
	this->type = SENSOR_GYROSCOPE;
	this->error = sensor_is_supported(this->type, &supported);

	return supported;
}

SensorValue getGyroscopeData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	this->type = SENSOR_GYROSCOPE;
	this->error = sensor_get_default_sensor(this->type, &this->sensors);
	this->error = sensor_create_listener(this->sensors, &this->listener);
	this->error = sensor_listener_start(this->listener);
	this->error = sensor_listener_read_data(this->listener, &this->event);

	SensorValue data;
	for(int i=0; i<MAX_VALUE_SIZE;i++)
		data.values[i] = this->event.values[i];

	this->error = sensor_listener_stop(this->listener);
	this->error = sensor_destroy_listener(this->listener);

	return data;
}

bool hasLight(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	bool supported;
	this->type = SENSOR_LIGHT;
	this->error = sensor_is_supported(this->type, &supported);

	return supported;
}

SensorValue getLightData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	this->type = SENSOR_LIGHT;
	this->error = sensor_get_default_sensor(this->type, &this->sensors);
	this->error = sensor_create_listener(this->sensors, &this->listener);
	this->error = sensor_listener_start(this->listener);
	this->error = sensor_listener_read_data(this->listener, &this->event);

	SensorValue data;
	for(int i=0; i<MAX_VALUE_SIZE;i++)
		data.values[i] = this->event.values[i];

	this->error = sensor_listener_stop(this->listener);
	this->error = sensor_destroy_listener(this->listener);

	return data;
}

bool hasProximity(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	bool supported;
	this->type = SENSOR_PROXIMITY;
	this->error = sensor_is_supported(this->type, &supported);

	return supported;
}

SensorValue getProximityData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	this->type = SENSOR_PROXIMITY;
	this->error = sensor_get_default_sensor(this->type, &this->sensors);
	this->error = sensor_create_listener(this->sensors, &this->listener);
	this->error = sensor_listener_start(this->listener);
	this->error = sensor_listener_read_data(this->listener, &this->event);

	SensorValue data;
	for(int i=0; i<MAX_VALUE_SIZE;i++)
		data.values[i] = this->event.values[i];

	this->error = sensor_listener_stop(this->listener);
	this->error = sensor_destroy_listener(this->listener);

	return data;
}

bool hasPressure(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	bool supported;
	this->type = SENSOR_PRESSURE;
	this->error = sensor_is_supported(this->type, &supported);

	return supported;
}

SensorValue getPressureData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	this->type = SENSOR_PRESSURE;
	this->error = sensor_get_default_sensor(this->type, &this->sensors);
	this->error = sensor_create_listener(this->sensors, &this->listener);
	this->error = sensor_listener_start(this->listener);
	this->error = sensor_listener_read_data(this->listener, &this->event);

	SensorValue data;
	for(int i=0; i<MAX_VALUE_SIZE;i++)
		data.values[i] = this->event.values[i];

	this->error = sensor_listener_stop(this->listener);
	this->error = sensor_destroy_listener(this->listener);

	return data;
}

bool hasUltraViolet(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	bool supported;
	this->type = SENSOR_ULTRAVIOLET;
	this->error = sensor_is_supported(this->type, &supported);

	return supported;
}

SensorValue getUltraVioletData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	this->type = SENSOR_ULTRAVIOLET;
	this->error = sensor_get_default_sensor(this->type, &this->sensors);
	this->error = sensor_create_listener(this->sensors, &this->listener);
	this->error = sensor_listener_start(this->listener);
	this->error = sensor_listener_read_data(this->listener, &this->event);

	SensorValue data;
	for(int i=0; i<MAX_VALUE_SIZE;i++)
		data.values[i] = this->event.values[i];

	this->error = sensor_listener_stop(this->listener);
	this->error = sensor_destroy_listener(this->listener);

	return data;
}

bool hasTemperature(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	bool supported;
	this->type = SENSOR_TEMPERATURE;
	this->error = sensor_is_supported(this->type, &supported);

	return supported;
}

SensorValue getTemperatureData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	this->type = SENSOR_TEMPERATURE;
	this->error = sensor_get_default_sensor(this->type, &this->sensors);
	this->error = sensor_create_listener(this->sensors, &this->listener);
	this->error = sensor_listener_start(this->listener);
	this->error = sensor_listener_read_data(this->listener, &this->event);

	SensorValue data;
	for(int i=0; i<MAX_VALUE_SIZE;i++)
		data.values[i] = this->event.values[i];

	this->error = sensor_listener_stop(this->listener);
	this->error = sensor_destroy_listener(this->listener);

	return data;
}

bool hasHumidity(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	bool supported;
	this->type = SENSOR_HUMIDITY;
	this->error = sensor_is_supported(this->type, &supported);

	return supported;
}

SensorValue getHumidityData(Sensor* this_gen)
{
	SensorExtend* this = (SensorExtend*) this_gen;
	this->type = SENSOR_HUMIDITY;
	this->error = sensor_get_default_sensor(this->type, &this->sensors);
	this->error = sensor_create_listener(this->sensors, &this->listener);
	this->error = sensor_listener_start(this->listener);
	this->error = sensor_listener_read_data(this->listener, &this->event);

	SensorValue data;
	for(int i=0; i<MAX_VALUE_SIZE;i++)
		data.values[i] = this->event.values[i];

	this->error = sensor_listener_stop(this->listener);
	this->error = sensor_destroy_listener(this->listener);

	return data;
}
