/*! @file	Sensor.h
 *  @brief	Sensor API 를 사용하기 위해 포함해야 하는 헤더이다.
 *  @note	Sensor의 다양한 센서의 addCallback / detachCallback / On / Off / isSupported / getValue API를 제공한다.
 *  @see	https://developer.tizen.org/development/api-references/native-application?redirect=https%3A//developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/index.html
 */

#ifndef DIT_SENSOR_H
#define DIT_SENSOR_H

#include <stdbool.h>
#include <stdalign.h>

#include "dit.h"

#include <sensor.h>

#ifdef __cplusplus
extern "C" {
#endif

const char * SensorErrorCheck (int errorCode);

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

/* Accelerometer */
/*! @struct	_Accelerometer
 *  @brief	Accelerometer 모듈에 대한 구조체이다. Accelerometer 모듈은 Accelerometer Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Accelerometer 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewAccelerometer() 함수를 사용해야 하며 사용이 끝났을 때 DestroyAccelerometer() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html
 *  @todo	feature에 "http://tizen.org/feature/sensor.accelerometer" 을 반드시 추가해야 한다.
 */
typedef struct _Accelerometer * Accelerometer;

struct _Accelerometer
{

    bool(* addCallback) (Accelerometer this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    bool(* detachCallback) (Accelerometer this_gen);

    bool(* On) (Accelerometer this_gen);

    bool(* Off) (Accelerometer this_gen);

    bool(* isSupported) (Accelerometer this_gen);

    Accelerometer_data(* getValue) (Accelerometer this_gen);

};

typedef struct _AccelerometerExtend
{
    struct _Accelerometer accelerometer;
    sensor_type_e         type;
    sensor_h              sensor;
    sensor_listener_h     listener;
    bool activated;
}                             AccelerometerExtend;

/*!	@fn			Accelerometer NewAccelerometer (void)
 *  @brief		새로운 Accelerometer 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Accelerometer
 *  @note 		새로운 Accelerometer 객체를 생성한다. \n
 *  			Accelerometer 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyAccelerometer \n
 *  			addAccelerometerCallback \n
 *  			detachAccelerometerCallback \n
 *  			AccelerometerOn \n
 *  			AccelerometerOff \n
 *  			isAccelerometerSupported \n
 *  			getAccelerometerValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer
 */
Accelerometer NewAccelerometer (void);

/*!	@fn			void DestroyAccelerometer (Accelerometer this_gen)
 *  @brief 		생성한 Accelerometer 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Accelerometer 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Accelerometer 객체를 소멸 시킨다. \n
 *  			Accelerometer 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewAccelerometer
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 */
void DestroyAccelerometer (Accelerometer this_gen);

/*!	@fn			void addAccelerometerCallback (Accelerometer this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Accelerometer에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Accelerometer 객체
 *  @param[in] 	sensorCallback 등록할 callback 함수
 *  @param[in] 	timeinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Accelerometer에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewAccelerometer \n
 *  			DestroyAccelerometer \n
 *  			detachAccelerometerCallback \n
 *  			AccelerometerOn \n
 *  			AccelerometerOff \n
 *  			isAccelerometerSupported \n
 *  			getAccelerometerValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 */
bool addAccelerometerCallback (Accelerometer this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			void detachAccelerometerCallback (Accelerometer this_gen)
 *  @brief 		생성한 Accelerometer에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Accelerometer 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Accelerometer에서 callback 함수를 삭제한다. \n
 *  @see 		NewAccelerometer \n
 *  			DestroyAccelerometer \n
 *  			addAccelerometerCallback \n
 *  			AccelerometerOn \n
 *  			AccelerometerOff \n
 *  			isAccelerometerSupported \n
 *  			getAccelerometerValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 */
bool detachAccelerometerCallback (Accelerometer this_gen);

/*!	@fn			void AccelerometerOn (Accelerometer this_gen)
 *  @brief 		생성한 Accelerometer를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Accelerometer 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Accelerometer를 활성화 시킨다.
 *  @see 		NewAccelerometer \n
 *  			DestroyAccelerometer \n
 *  			addAccelerometerCallback \n
 *  			detachAccelerometerCallback \n
 *  			AccelerometerOff \n
 *  			isAccelerometerSupported \n
 *  			getAccelerometerValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 */
bool AccelerometerOn (Accelerometer this_gen);

/*!	@fn			void AccelerometerOff (Accelerometer this_gen)
 *  @brief 		생성한 Accelerometer를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Accelerometer 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Accelerometer를 비활성화 시킨다.
 *  @see 		NewAccelerometer \n
 *  			DestroyAccelerometer \n
 *  			addAccelerometerCallback \n
 *  			detachAccelerometerCallback \n
 *  			AccelerometerOn \n
 *  			isAccelerometerSupported \n
 *  			getAccelerometerValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 */
bool AccelerometerOff (Accelerometer this_gen);

/*!	@fn			bool isAccelerometerSupported (Accelerometer this_gen)
 *  @brief 		Accelerometer의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Accelerometer 객체
 *  @param[out] null
 *  @retval 	bool 사용 가능 여부
 *  @note 		Accelerometer의 사용 가능 여부를 판단한다.
 *  @see 		NewAccelerometer \n
 *  			DestroyAccelerometer \n
 *  			addAccelerometerCallback \n
 *  			detachAccelerometerCallback \n
 *  			AccelerometerOn \n
 *  			AccelerometerOff \n
 *  			getAccelerometerValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 */
bool isAccelerometerSupported (Accelerometer this_gen);

/*!	@fn			Accelerometer_data getAccelerometerValue (Accelerometer this_gen)
 *  @brief 		활성화 되어 있는 Accelerometer의 센서 값을 반환한다.
 *  @param[in] 	this_gen 센서 값을 받을 Accelerometer 객체
 *  @param[out] null
 *  @retval 	Accelerometer_data Accelerometer의 센서 값
 *  @note 		활성화 되어 있는 Accelerometer의 센서 값을 반환한다.
 *  @see 		NewAccelerometer \n
 *  			DestroyAccelerometer \n
 *  			addAccelerometerCallback \n
 *  			detachAccelerometerCallback \n
 *  			AccelerometerOn \n
 *  			AccelerometerOff \n
 *  			isAccelerometerSupported \n
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 */
Accelerometer_data getAccelerometerValue (Accelerometer this_gen);
/* Accelerometer */


/* Gravity */
/*! @struct	_Gravity
 *  @brief	Gravity 모듈에 대한 구조체이다. Gravity 모듈은 Gravity Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Gravity 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewGravity() 함수를 사용해야 하며 사용이 끝났을 때 DestroyGravity() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html
 *  @todo	feature에 "http://tizen.org/feature/sensor.gravity" 을 반드시 추가해야 한다.
*/
typedef struct _Gravity * Gravity;

struct _Gravity
{

    bool(* addCallback) (Gravity this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    bool(* detachCallback) (Gravity this_gen);

    bool(* On) (Gravity this_gen);

    bool(* Off) (Gravity this_gen);

    bool(* isSupported) (Gravity this_gen);

    Gravity_data (* getValue) (Gravity this_gen);

};

typedef struct _GravityExtend
{
    struct _Gravity   gravity;
    sensor_type_e     type;
    sensor_h          sensor;
    sensor_listener_h listener;
    bool activated;

} GravityExtend;

/*!	@fn			Gravity NewGravity (void)
 *  @brief		새로운 Gravity 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Gravity
 *  @note 		새로운 Gravity 객체를 생성한다. \n
 *  			Gravity 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyGravity \n
 *  			addGravityCallback \n
 *  			detachGravityCallback \n
 *  			GravityOn \n
 *  			GravityOff \n
 *  			isGravitySupported \n
 *  			getGravityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.gravity \n
 */
Gravity NewGravity (void);

/*!	@fn			void DestroyGravity (Gravity this_gen)
 *  @brief 		생성한 Gravity 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Gravity 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Gravity 객체를 소멸 시킨다. \n
 *  			Gravity 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewGravity
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.gravity \n
 */
void DestroyGravity (Gravity this_gen);

/*!	@fn			void addGravityCallback (Gravity this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Gravity에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Gravity 객체
 *  @param[in] 	sensorCallback 등록할 callback 함수
 *  @param[in] 	timeinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Gravity에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewGravity \n
 *  			DestroyGravity \n
 *  			detachGravityCallback \n
 *  			GravityOn \n
 *  			GravityOff \n
 *  			isGravitySupported \n
 *  			getGravityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.gravity \n
 */
bool addGravityCallback (Gravity this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			void detachGravityCallback (Gravity this_gen)
 *  @brief 		생성한 Gravity에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Gravity 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Gravity에서 callback 함수를 삭제한다. \n
 *  @see 		NewGravity \n
 *  			DestroyGravity \n
 *  			addGravityCallback \n
 *  			GravityOn \n
 *  			GravityOff \n
 *  			isGravitySupported \n
 *  			getGravityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.gravity \n
 */
bool detachGravityCallback (Gravity this_gen);

/*!	@fn			void GravityOn (Gravity this_gen)
 *  @brief 		생성한 Gravity를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Gravity 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Gravity를 활성화 시킨다.
 *  @see 		NewGravity \n
 *  			DestroyGravity \n
 *  			addGravityCallback \n
 *  			detachGravityCallback \n
 *  			GravityOff \n
 *  			isGravitySupported \n
 *  			getGravityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.gravity \n
 */
bool GravityOn (Gravity this_gen);

/*!	@fn			void GravityOff (Gravity this_gen)
 *  @brief 		생성한 Gravity를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Gravity 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Gravity를 비활성화 시킨다.
 *  @see 		NewGravity \n
 *  			DestroyGravity \n
 *  			addGravityCallback \n
 *  			detachGravityCallback \n
 *  			GravityOn \n
 *  			isGravitySupported \n
 *  			getGravityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.gravity \n
 */
bool GravityOff (Gravity this_gen);

/*!	@fn			bool isGravitySupported (Gravity this_gen)
 *  @brief 		Gravity의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Gravity 객체
 *  @param[out] null
 *  @retval 	bool 사용 가능 여부
 *  @note 		Gravity의 사용 가능 여부를 판단한다.
 *  @see 		NewGravity \n
 *  			DestroyGravity \n
 *  			addGravityCallback \n
 *  			detachGravityCallback \n
 *  			GravityOn \n
 *  			GravityOff \n
 *  			getGravityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.gravity \n
 */
bool isGravitySupported (Gravity this_gen);

/*!	@fn			Gravity_data getGravityValue (Gravity this_gen)
 *  @brief 		활성화 되어 있는 Gravity의 센서 값을 반환한다.
 *  @param[in] 	this_gen 센서 값을 받을 Gravity 객체
 *  @param[out] null
 *  @retval 	Gravity_data Gravity의 센서 값
 *  @note 		활성화 되어 있는 Gravity의 센서 값을 반환한다.
 *  @see 		NewGravity \n
 *  			DestroyGravity \n
 *  			addGravityCallback \n
 *  			detachGravityCallback \n
 *  			GravityOn \n
 *  			GravityOff \n
 *  			isGravitySupported
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.gravity \n
 */
Gravity_data getGravityValue (Gravity this_gen);
/* Gravity */


/* LinearAccelation */
/*! @struct	_LinearAccelation
 *  @brief	LinearAccelation 모듈에 대한 구조체이다. LinearAccelation 모듈은 LinearAccelation Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	LinearAccelation 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewLinearAccelation() 함수를 사용해야 하며 사용이 끝났을 때 DestroyLinearAccelation() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html
 *  @todo	feature에 "http://tizen.org/feature/sensor.linear_acceleration" 을 반드시 추가해야 한다.
 */
typedef struct _LinearAccelation * LinearAccelation;

struct _LinearAccelation
{

    bool(* addCallback) (LinearAccelation this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    bool(* detachCallback) (LinearAccelation this_gen);

    bool(* On) (LinearAccelation this_gen);

    bool(* Off) (LinearAccelation this_gen);

    bool(* isSupported) (LinearAccelation this_gen);

    LinearAcceleration_data (* getValue) (LinearAccelation this_gen);

};

typedef struct _LinearAccelationExtend
{
    struct _LinearAccelation linearaccelation;
    sensor_type_e            type;
    sensor_h                 sensor;
    sensor_listener_h        listener;
    bool activated;

} LinearAccelationExtend;

/*!	@fn			LinearAccelation NewLinearAccelation (void)
 *  @brief		새로운 LinearAccelation 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	LinearAccelation
 *  @note 		새로운 LinearAccelation 객체를 생성한다. \n
 *  			AcceleLinearAccelationrometer 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyLinearAccelation \n
 *  			addLinearAccelationCallback \n
 *  			detachLinearAccelationCallback \n
 *  			LinearAccelationOn \n
 *  			LinearAccelationOff \n
 *  			isLinearAccelationSupported \n
 *  			getLinearAccelationValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.linear_acceleration
 */
LinearAccelation NewLinearAccelation (void);

/*!	@fn			void DestroyLinearAccelation (LinearAccelation this_gen)
 *  @brief 		생성한 LinearAccelation 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 LinearAccelation 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 LinearAccelation 객체를 소멸 시킨다. \n
 *  			LinearAccelation 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewLinearAccelation
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.linear_acceleration \n
 */
void DestroyLinearAccelation (LinearAccelation this_gen);

/*!	@fn			void addLinearAccelationCallback (LinearAccelation this_gen, sensor_callback sensorCallback, int timeenterval, void * data)
 *  @brief 		생성한 LinearAccelation에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 LinearAccelation 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	timeinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 LinearAccelation에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewLinearAccelation \n
 *  			DestroyLinearAccelation \n
 *  			detachLinearAccelationCallback \n
 *  			LinearAccelationOn \n
 *  			LinearAccelationOff \n
 *  			isLinearAccelationSupported \n
 *  			getLinearAccelationValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.linear_acceleration \n
 */
bool addLinearAccelationCallback (LinearAccelation this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			void detachLinearAccelationCallback (LinearAccelation this_gen)
 *  @brief 		생성한 LinearAccelation에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 LinearAccelation 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 LinearAccelation에서 callback 함수를 삭제한다. \n
 *  @see 		NewLinearAccelation \n
 *  			DestroyLinearAccelation \n
 *  			addLinearAccelationCallback \n
 *  			LinearAccelationOn \n
 *  			LinearAccelationOff \n
 *  			isLinearAccelationSupported \n
 *  			getLinearAccelationValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.linear_acceleration \n
 */
bool detachLinearAccelationCallback (LinearAccelation this_gen);

/*!	@fn			void LinearAccelationOn (LinearAccelation this_gen)
 *  @brief 		생성한 LinearAccelation를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 LinearAccelation 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 LinearAccelation를 활성화 시킨다.
 *  @see 		NewLinearAccelation \n
 *  			DestroyLinearAccelation \n
 *  			addLinearAccelationCallback \n
 *  			detachLinearAccelationCallback \n
 *  			LinearAccelationOff \n
 *  			isLinearAccelationSupported \n
 *  			getLinearAccelationValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.linear_acceleration \n
 */
bool LinearAccelationOn (LinearAccelation this_gen);

/*!	@fn			void LinearAccelationOff (LinearAccelation this_gen)
 *  @brief 		생성한 LinearAccelation를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 LinearAccelation 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 LinearAccelation를 비활성화 시킨다.
 *  @see 		NewLinearAccelation \n
 *  			DestroyLinearAccelation \n
 *  			addLinearAccelationCallback \n
 *  			detachLinearAccelationCallback \n
 *  			LinearAccelationOn \n
 *  			isLinearAccelationSupported \n
 *  			getLinearAccelationValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.linear_acceleration \n
 */
bool LinearAccelationOff (LinearAccelation this_gen);

/*!	@fn			bool isLinearAccelationSupported (LinearAccelation this_gen)
 *  @brief 		LinearAccelation의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 LinearAccelation 객체
 *  @param[out] null
 *  @retval 	bool 사용 가능 여부
 *  @note 		LinearAccelation의 사용 가능 여부를 판단한다.
 *  @see 		NewLinearAccelation \n
 *  			DestroyLinearAccelation \n
 *  			addLinearAccelationCallback \n
 *  			detachLinearAccelationCallback \n
 *  			LinearAccelationOn \n
 *  			LinearAccelationOff \n
 *  			getLinearAccelationValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.linear_acceleration \n
 */
bool isLinearAccelationSupported (LinearAccelation this_gen);

/*!	@fn			LinearAccelation_data getLinearAccelationValue (LinearAccelation this_gen)
 *  @brief 		활성화 되어 있는 LinearAccelation의 센서 값을 반환한다.
 *  @param[in] 	this_gen 센서 값을 받을 LinearAccelation 객체
 *  @param[out] null
 *  @retval 	LinearAccelation_data LinearAccelation의 센서 값
 *  @note 		활성화 되어 있는 LinearAccelation의 센서 값을 반환한다.
 *  @see 		NewLinearAccelation \n
 *  			DestroyLinearAccelation \n
 *  			addLinearAccelationCallback \n
 *  			detachLinearAccelationCallback \n
 *  			LinearAccelationOn \n
 *  			LinearAccelationOff \n
 *  			isAccelerometerSupported \n
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.linear_acceleration \n
 */
LinearAcceleration_data getLinearAccelationValue (LinearAccelation this_gen);
/* LinearAccelation */


/* Magnetometer */
/*! @struct	_Magnetometer
 *  @brief	Magnetometer 모듈에 대한 구조체이다. Magnetometer 모듈은 Magnetometer Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Magnetometer 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewMagnetometer() 함수를 사용해야 하며 사용이 끝났을 때 DestroyMagnetometer() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html
 *  @todo	feature에 "http://tizen.org/feature/sensor.magnetometer" 을 반드시 추가해야 한다.
 */
typedef struct _Magnetometer * Magnetometer;

struct _Magnetometer
{

    bool(* addCallback) (Magnetometer this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    bool(* detachCallback) (Magnetometer this_gen);

    bool(* On) (Magnetometer this_gen);

    bool(* Off) (Magnetometer this_gen);

    bool(* isSupported) (Magnetometer this_gen);

    Magnetometer_data (* getValue) (Magnetometer this_gen);

};

typedef struct _MagnetometerExtend
{
    struct _Magnetometer magnetometer;
    sensor_type_e        type;
    sensor_h             sensor;
    sensor_listener_h    listener;
    bool activated;

} MagnetometerExtend;

/*!	@fn			Magnetometer NewMagnetometer (void)
 *  @brief		새로운 Magnetometer 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Magnetometer
 *  @note 		새로운 Magnetometer 객체를 생성한다. \n
 *  			Magnetometer 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyMagnetometer \n
 *  			addMagnetometerCallback \n
 *  			detachMagnetometerCallback \n
 *  			MagnetometerOn \n
 *  			MagnetometerOff \n
 *  			isMagnetometerSupported \n
 *  			getMagnetometerValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.magnetometer \n
 */
Magnetometer NewMagnetometer (void);

/*!	@fn			void DestroyMagnetometer (Magnetometer this_gen)
 *  @brief 		생성한 Magnetometer 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Magnetometer 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Magnetometer 객체를 소멸 시킨다. \n
 *  			Magnetometer 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewMagnetometer
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.magnetometer \n
 */
void DestroyMagnetometer (Magnetometer this_gen);

/*!	@fn			void addMagnetometerCallback (Magnetometer this_gen, sensor_callback sensorCallback, int timeenterval, void * data)
 *  @brief 		생성한 Magnetometer에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Magnetometer 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	timeinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Magnetometer에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewMagnetometer \n
 *  			DestroyMagnetometer \n
 *  			detachMagnetometerCallback \n
 *  			MagnetometerOn \n
 *  			MagnetometerOff \n
 *  			isMagnetometerSupported \n
 *  			getMagnetometerValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.magnetometer \n
 */
bool addMagnetometerCallback (Magnetometer this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			void detachMagnetometerCallback (Magnetometer this_gen)
 *  @brief 		생성한 Magnetometer에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Magnetometer 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Magnetometer에서 callback 함수를 삭제한다. \n
 *  @see 		NewMagnetometer \n
 *  			DestroyMagnetometer \n
 *  			addMagnetometerCallback \n
 *  			MagnetometerOn \n
 *  			MagnetometerOff \n
 *  			isMagnetometerSupported \n
 *  			getMagnetometerValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.magnetometer \n
 */
bool detachMagnetometerCallback (Magnetometer this_gen);

/*!	@fn			void MagnetometerOn (Magnetometer this_gen)
 *  @brief 		생성한 Magnetometer를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Magnetometer 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Magnetometer를 활성화 시킨다.
 *  @see 		NewMagnetometer \n
 *  			DestroyMagnetometer \n
 *  			addMagnetometerCallback \n
 *  			detachMagnetometerCallback \n
 *  			MagnetometerOff \n
 *  			isMagnetometerSupported \n
 *  			getMagnetometerValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.magnetometer \n
 */
bool MagnetometerOn (Magnetometer this_gen);

/*!	@fn			void MagnetometerOff (Magnetometer this_gen)
 *  @brief 		생성한 Magnetometer를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Magnetometer 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Magnetometer를 비활성화 시킨다.
 *  @see 		NewMagnetometer \n
 *  			DestroyMagnetometer \n
 *  			addMagnetometerCallback \n
 *  			detachMagnetometerCallback \n
 *  			MagnetometerOn \n
 *  			isMagnetometerSupported \n
 *  			getMagnetometerValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.magnetometer \n
 */
bool MagnetometerOff (Magnetometer this_gen);

/*!	@fn			bool isMagnetometerSupported (Magnetometer this_gen)
 *  @brief 		Magnetometer의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Magnetometer 객체
 *  @param[out] null
 *  @retval 	bool 사용 가능 여부
 *  @note 		Magnetometer의 사용 가능 여부를 판단한다.
 *  @see 		NewMagnetometer \n
 *  			DestroyMagnetometer \n
 *  			addMagnetometerCallback \n
 *  			detachMagnetometerCallback \n
 *  			MagnetometerOn \n
 *  			MagnetometerOff \n
 *  			getMagnetometerValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.magnetometer \n
 */
bool isMagnetometerSupported (Magnetometer this_gen);

/*!	@fn			Magnetometer_data getMagnetometerValue (Magnetometer this_gen)
 *  @brief 		활성화 되어 있는 Magnetometer의 센서 값을 반환한다.
 *  @param[in] 	this_gen 센서 값을 받을 Magnetometer 객체
 *  @param[out] null
 *  @retval 	Magnetometer_data Magnetometer의 센서 값
 *  @note 		활성화 되어 있는 Magnetometer의 센서 값을 반환한다.
 *  @see 		NewMagnetometer \n
 *  			DestroyMagnetometer \n
 *  			addMagnetometerCallback \n
 *  			detachMagnetometerCallback \n
 *  			MagnetometerOn \n
 *  			MagnetometerOff \n
 *  			isMagnetometerSupported \n
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.magnetometer \n
 */
Magnetometer_data getMagnetometerValue (Magnetometer this_gen);
/* Magnetometer */


/* RotationVector */
/*! @struct	_RotationVector
 *  @brief	RotationVector 모듈에 대한 구조체이다. RotationVector 모듈은 RotationVector Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	RotationVector 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewRotationVector() 함수를 사용해야 하며 사용이 끝났을 때 DestroyRotationVector() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html
 *  @todo	feature에 "http://tizen.org/feature/sensor.rotation_vector" 들을 반드시 추가해야 한다.
 */
typedef struct _RotationVector * RotationVector;

struct _RotationVector
{

    bool(* addCallback) (RotationVector this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    bool(* detachCallback) (RotationVector this_gen);

    bool(* On) (RotationVector this_gen);

    bool(* Off) (RotationVector this_gen);

    bool(* isSupported) (RotationVector this_gen);

    RotationVector_data (* getValue) (RotationVector this_gen);

};

typedef struct _RotationVectorExtend
{
    struct _RotationVector rotationvector;
    sensor_type_e          type;
    sensor_h               sensor;
    sensor_listener_h      listener;
    bool activated;

} RotationVectorExtend;

/*!	@fn			RotationVector NewRotationVector (void)
 *  @brief		새로운 RotationVector 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	RotationVector
 *  @note 		새로운 RotationVector 객체를 생성한다. \n
 *  			RotationVector 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyRotationVector \n
 *  			addRotationVectorCallback \n
 *  			detachRotationVectorCallback \n
 *  			RotationVectorOn \n
 *  			RotationVectorOff \n
 *  			isRotationVectorSupported \n
 *  			getRotationVectorValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.rotation_vector \n
 */
RotationVector NewRotationVector (void);

/*!	@fn			void DestroyRotationVector (RotationVector this_gen)
 *  @brief 		생성한 RotationVector 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 RotationVector 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 RotationVector 객체를 소멸 시킨다. \n
 *  			RotationVector 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewRotationVector
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.rotation_vector \n
 */
void DestroyRotationVector (RotationVector this_gen);

/*!	@fn			void addRotationVectorCallback (RotationVector this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 RotationVector에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 RotationVector 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	timeinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 RotationVector에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewRotationVector \n
 *  			DestroyRotationVector \n
 *  			detachRotationVectorCallback \n
 *  			RotationVectorOn \n
 *  			RotationVectorOff \n
 *  			isRotationVectorSupported \n
 *  			getRotationVectorValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.rotation_vector \n
 */
bool addRotationVectorCallback (RotationVector this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			void detachRotationVectorCallback (RotationVector this_gen)
 *  @brief 		생성한 RotationVector에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 RotationVector 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 RotationVector에서 callback 함수를 삭제한다. \n
 *  @see 		NewRotationVector \n
 *  			DestroyRotationVector \n
 *  			addRotationVectorCallback \n
 *  			RotationVectorOn \n
 *  			RotationVectorOff \n
 *  			isRotationVectorSupported \n
 *  			getRotationVectorValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.rotation_vector \n
 */
bool detachRotationVectorCallback (RotationVector this_gen);

/*!	@fn			void RotationVectorOn (RotationVector this_gen)
 *  @brief 		생성한 RotationVector를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 RotationVector 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 RotationVector를 활성화 시킨다.
 *  @see 		NewRotationVector \n
 *  			DestroyRotationVector \n
 *  			addRotationVectorCallback \n
 *  			detachRotationVectorCallback \n
 *  			RotationVectorOff \n
 *  			isRotationVectorSupported \n
 *  			getRotationVectorValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.rotation_vector \n
 */
bool RotationVectorOn (RotationVector this_gen);

/*!	@fn			void RotationVectorOff (RotationVector this_gen)
 *  @brief 		생성한 RotationVector를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 RotationVector 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 RotationVector를 비활성화 시킨다.
 *  @see 		NewRotationVector \n
 *  			DestroyRotationVector \n
 *  			addRotationVectorCallback \n
 *  			detachRotationVectorCallback \n
 *  			RotationVectorOn \n
 *  			isRotationVectorSupported \n
 *  			getRotationVectorValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.rotation_vector \n
 */
bool RotationVectorOff (RotationVector this_gen);

/*!	@fn			bool isRotationVectorSupported (RotationVector this_gen)
 *  @brief 		RotationVector의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 RotationVector 객체
 *  @param[out] null
 *  @retval 	bool 사용 가능 여부
 *  @note 		RotationVector의 사용 가능 여부를 판단한다.
 *  @see 		NewRotationVector \n
 *  			DestroyRotationVector \n
 *  			addRotationVectorCallback \n
 *  			detachRotationVectorCallback \n
 *  			RotationVectorOn \n
 *  			RotationVectorOff \n
 *  			getRotationVectorValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.rotation_vector \n
 */
bool isRotationVectorSupported (RotationVector this_gen);

/*!	@fn			RotationVector_data getRotationVectorValue (RotationVector this_gen)
 *  @brief 		활성화 되어 있는 RotationVector의 센서 값을 반환한다.
 *  @param[in] 	this_gen 센서 값을 받을 RotationVector 객체
 *  @param[out] null
 *  @retval 	RotationVector_data RotationVector의 센서 값
 *  @note 		활성화 되어 있는 RotationVector의 센서 값을 반환한다.
 *  @see 		NewRotationVector \n
 *  			DestroyRotationVector \n
 *  			addRotationVectorCallback \n
 *  			detachRotationVectorCallback \n
 *  			RotationVectorOn \n
 *  			RotationVectorOff \n
 *  			isRotationVectorSupported \n
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.rotation_vector \n
 */
RotationVector_data getRotationVectorValue (RotationVector this_gen);
/* RotationVector */


/* Orientation */
/*! @struct	_Orientation
 *  @brief	Orientation 모듈에 대한 구조체이다. Orientation 모듈은 Orientation Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Orientation 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewOrientation() 함수를 사용해야 하며 사용이 끝났을 때 DestroyOrientation() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html
 *  @todo	feature에 "http://tizen.org/feature/sensor.accelerometer" 와 "http://tizen.org/feature/sensor.magnetometer" 을 반드시 추가해야 한다.
 */
typedef struct _Orientation * Orientation;

struct _Orientation
{

    bool(* addCallback) (Orientation this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    bool(* detachCallback) (Orientation this_gen);

    bool(* On) (Orientation this_gen);

    bool(* Off) (Orientation this_gen);

    bool(* isSupported) (Orientation this_gen);

    Orientation_data (* getValue) (Orientation this_gen);

};

typedef struct _OrientationExtend
{
    struct _Orientation orientation;
    sensor_type_e       type;
    sensor_h            sensor;
    sensor_listener_h   listener;
    bool activated;

} OrientationExtend;

/*!	@fn			Orientation NewOrientation (void)
 *  @brief		새로운 Orientation 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Orientation
 *  @note 		새로운 Orientation 객체를 생성한다. \n
 *  			Orientation 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyOrientation \n
 *  			addOrientationCallback \n
 *  			detachOrientationCallback \n
 *  			OrientationOn \n
 *  			OrientationOff \n
 *  			isOrientationSupported \n
 *  			getOrientationValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 *							http://tizen.org/feature/sensor.magnetometer \n
 */
Orientation NewOrientation (void);

/*!	@fn			void DestroyOrientation (Orientation this_gen)
 *  @brief 		생성한 Orientation 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Orientation 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Orientation 객체를 소멸 시킨다. \n
 *  			Orientation 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewOrientation
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 *							http://tizen.org/feature/sensor.magnetometer \n
 */
void DestroyOrientation (Orientation this_gen);

/*!	@fn			void addOrientationCallback (Orientation this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Orientation에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Orientation 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	voiceinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Orientation에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewOrientation \n
 *  			DestroyOrientation \n
 *  			detachOrientationCallback \n
 *  			OrientationOn \n
 *  			OrientationOff \n
 *  			isOrientationSupported \n
 *  			getOrientationValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 *							http://tizen.org/feature/sensor.magnetometer \n
 */
bool addOrientationCallback (Orientation this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			void detachOrientationCallback (Orientation this_gen)
 *  @brief 		생성한 Orientation에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Orientation 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Orientation에서 callback 함수를 삭제한다. \n
 *  @see 		NewOrientation \n
 *  			DestroyOrientation \n
 *  			addOrientationCallback \n
 *  			OrientationOn \n
 *  			OrientationOff \n
 *  			isOrientationSupported \n
 *  			getOrientationValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 *							http://tizen.org/feature/sensor.magnetometer \n
 */
bool detachOrientationCallback (Orientation this_gen);

/*!	@fn			void OrientationOn (Orientation this_gen)
 *  @brief 		생성한 Orientation를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Orientation 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Orientation를 활성화 시킨다.
 *  @see 		NewOrientation \n
 *  			DestroyOrientation \n
 *  			addOrientationCallback \n
 *  			detachOrientationCallback \n
 *  			OrientationOff \n
 *  			isOrientationSupported \n
 *  			getOrientationValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 *							http://tizen.org/feature/sensor.magnetometer \n
 */
bool OrientationOn (Orientation this_gen);

/*!	@fn			void OrientationOff (Orientation this_gen)
 *  @brief 		생성한 Orientation를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Orientation 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Orientation를 비활성화 시킨다.
 *  @see 		NewOrientation \n
 *  			DestroyOrientation \n
 *  			addOrientationCallback \n
 *  			detachOrientationCallback \n
 *  			OrientationOn \n
 *  			isOrientationSupported \n
 *  			getOrientationValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 *							http://tizen.org/feature/sensor.magnetometer \n
 */
bool OrientationOff (Orientation this_gen);

/*!	@fn			bool isOrientationSupported (Orientation this_gen)
 *  @brief 		Orientation의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Orientation 객체
 *  @param[out] null
 *  @retval 	bool 사용 가능 여부
 *  @note 		Orientation의 사용 가능 여부를 판단한다.
 *  @see 		NewOrientation \n
 *  			DestroyOrientation \n
 *  			addOrientationCallback \n
 *  			detachOrientationCallback \n
 *  			OrientationOn \n
 *  			OrientationOff \n
 *  			getOrientationValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 *							http://tizen.org/feature/sensor.magnetometer \n
 */
bool isOrientationSupported (Orientation this_gen);

/*!	@fn			Orientation_data getOrientationValue (Orientation this_gen)
 *  @brief 		활성화 되어 있는 Orientation의 센서 값을 반환한다.
 *  @param[in] 	this_gen 센서 값을 받을 Orientation 객체
 *  @param[out] null
 *  @retval 	Orientation_data Orientation의 센서 값
 *  @note 		활성화 되어 있는 Orientation의 센서 값을 반환한다.
 *  @see 		NewOrientation \n
 *  			DestroyOrientation \n
 *  			addOrientationCallback \n
 *  			detachOrientationCallback \n
 *  			OrientationOn \n
 *  			OrientationOff \n
 *  			isOrientationSupported \n
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 *							http://tizen.org/feature/sensor.magnetometer \n
 */
Orientation_data getOrientationValue (Orientation this_gen);
/* Orientation */


/* Gyroscope */
/*! @struct	_Gyroscope
 *  @brief	Gyroscope 모듈에 대한 구조체이다. Gyroscope 모듈은 Gyroscope Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Gyroscope 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewGyroscope() 함수를 사용해야 하며 사용이 끝났을 때 DestroyGyroscope() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html
 *  @todo	feature에 "http://tizen.org/feature/sensor.gyroscope" 을 반드시 추가해야 한다.
 */
typedef struct _Gyroscope * Gyroscope;

struct _Gyroscope
{

    bool(* addCallback) (Gyroscope this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    bool(* detachCallback) (Gyroscope this_gen);

    bool(* On) (Gyroscope this_gen);

    bool(* Off) (Gyroscope this_gen);

    bool(* isSupported) (Gyroscope this_gen);

    Gyroscope_data (* getValue) (Gyroscope this_gen);

};

typedef struct _GyroscopeExtend
{
    struct _Gyroscope gyroscope;
    sensor_type_e     type;
    sensor_h          sensor;
    sensor_listener_h listener;
    bool activated;

} GyroscopeExtend;

/*!	@fn			Gyroscope NewGyroscope (void)
 *  @brief		새로운 Gyroscope 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Gyroscope
 *  @note 		새로운 Gyroscope 객체를 생성한다. \n
 *  			Gyroscope 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyGyroscope \n
 *  			addGyroscopeCallback \n
 *  			detachGyroscopeCallback \n
 *  			GyroscopeOn \n
 *  			GyroscopeOff \n
 *  			isGyroscopeSupported \n
 *  			getGyroscopeValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.gyroscope \n
 */
Gyroscope NewGyroscope (void);

/*!	@fn			void DestroyGyroscope (Gyroscope this_gen)
 *  @brief 		생성한 Gyroscope 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Gyroscope 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Gyroscope 객체를 소멸 시킨다. \n
 *  			Gyroscope 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewGyroscope
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.gyroscope
 */
void DestroyGyroscope (Gyroscope this_gen);

/*!	@fn			void addGyroscopeCallback (Gyroscope this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Gyroscope에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Gyroscope 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	voiceinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Gyroscope에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewGyroscope \n
 *  			DestroyGyroscope \n
 *  			detachGyroscopeCallback \n
 *  			GyroscopeOn \n
 *  			GyroscopeOff \n
 *  			isGyroscopeSupported \n
 *  			getGyroscopeValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.gyroscope
 */
bool addGyroscopeCallback (Gyroscope this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			void detachGyroscopeCallback (Gyroscope this_gen)
 *  @brief 		생성한 Gyroscope에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Gyroscope 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Gyroscope에서 callback 함수를 삭제한다. \n
 *  @see 		NewGyroscope \n
 *  			DestroyGyroscope \n
 *  			addGyroscopeCallback \n
 *  			GyroscopeOn \n
 *  			GyroscopeOff \n
 *  			isGyroscopeSupported \n
 *  			getGyroscopeValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.gyroscope
 */
bool detachGyroscopeCallback (Gyroscope this_gen);

/*!	@fn			void GyroscopeOn (Gyroscope this_gen)
 *  @brief 		생성한 Gyroscope를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Gyroscope 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Gyroscope를 활성화 시킨다.
 *  @see 		NewGyroscope \n
 *  			DestroyGyroscope \n
 *  			addGyroscopeCallback \n
 *  			detachGyroscopeCallback \n
 *  			GyroscopeOff \n
 *  			isGyroscopeSupported \n
 *  			getGyroscopeValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.gyroscope
 */
bool GyroscopeOn (Gyroscope this_gen);

/*!	@fn			void GyroscopeOff (Gyroscope this_gen)
 *  @brief 		생성한 Gyroscope를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Gyroscope 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Gyroscope를 비활성화 시킨다.
 *  @see 		NewGyroscope \n
 *  			DestroyGyroscope \n
 *  			addGyroscopeCallback \n
 *  			detachGyroscopeCallback \n
 *  			GyroscopeOn \n
 *  			isGyroscopeSupported \n
 *  			getGyroscopeValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.gyroscope
 */
bool GyroscopeOff (Gyroscope this_gen);

/*!	@fn			bool isGyroscopeSupported (Gyroscope this_gen)
 *  @brief 		Gyroscope의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Gyroscope 객체
 *  @param[out] null
 *  @retval 	bool 사용 가능 여부
 *  @note 		Gyroscope의 사용 가능 여부를 판단한다.
 *  @see 		NewGyroscope \n
 *  			DestroyGyroscope \n
 *  			addGyroscopeCallback \n
 *  			detachGyroscopeCallback \n
 *  			GyroscopeOn \n
 *  			GyroscopeOff \n
 *  			getGyroscopeValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.gyroscope
 */
bool isGyroscopeSupported (Gyroscope this_gen);

/*!	@fn			Gyroscope_data getGyroscopeValue (Gyroscope this_gen)
 *  @brief 		활성화 되어 있는 Gyroscope의 센서 값을 반환한다.
 *  @param[in] 	this_gen 센서 값을 받을 Gyroscope 객체
 *  @param[out] null
 *  @retval 	Gyroscope_data Gyroscope의 센서 값
 *  @note 		활성화 되어 있는 Gyroscope의 센서 값을 반환한다.
 *  @see 		NewGyroscope \n
 *  			DestroyGyroscope \n
 *  			addGyroscopeCallback \n
 *  			detachGyroscopeCallback \n
 *  			GyroscopeOn \n
 *  			GyroscopeOff \n
 *  			isGyroscopeSupported \n
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.gyroscope
 */
Gyroscope_data getGyroscopeValue (Gyroscope this_gen);
/* Gyroscope */


/* Light */
/*! @struct	_Light
 *  @brief	Light 모듈에 대한 구조체이다. Light 모듈은 Photometer Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Light 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewLight() 함수를 사용해야 하며 사용이 끝났을 때 DestroyLight() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html
 *  @todo	feature에 "http://tizen.org/feature/sensor.photometer" 들을 반드시 추가해야 한다.
 */
typedef struct _Light * Light;

struct _Light
{

    bool(* addCallback) (Light this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    bool(* detachCallback) (Light this_gen);

    bool(* On) (Light this_gen);

    bool(* Off) (Light this_gen);

    bool(* isSupported) (Light this_gen);

    Light_data (* getValue) (Light this_gen);

};

typedef struct _LightExtend
{
    struct _Light     light;
    sensor_type_e     type;
    sensor_h          sensor;
    sensor_listener_h listener;
    bool activated;

} LightExtend;

/*!	@fn			Light NewLight (void)
 *  @brief		새로운 Light 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Light
 *  @note 		새로운 Light 객체를 생성한다. \n
 *  			Light 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyLight \n
 *  			addLightCallback \n
 *  			detachLightCallback \n
 *  			LightOn \n
 *  			LightOff \n
 *  			isLightSupported \n
 *  			getLightValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.photometer \n
 */
Light NewLight (void);

/*!	@fn			void DestroyLight (Light this_gen)
 *  @brief 		생성한 Light 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Light 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Light 객체를 소멸 시킨다. \n
 *  			Light 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewLight
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.photometer \n
 */
void DestroyLight (Light this_gen);

/*!	@fn			void addLightCallback (Light this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Light에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Light 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	voiceinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Light에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewLight \n
 *  			DestroyLight \n
 *  			detachLightCallback \n
 *  			LightOn \n
 *  			LightOff \n
 *  			isLightSupported \n
 *  			getLightValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.photometer \n
 */
bool addLightCallback (Light this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			void detachLightCallback (Light this_gen)
 *  @brief 		생성한 Light에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Light 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Light에서 callback 함수를 삭제한다. \n
 *  @see 		NewLight \n
 *  			DestroyLight \n
 *  			addLightCallback \n
 *  			LightOn \n
 *  			LightOff \n
 *  			isLightSupported \n
 *  			getLightValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.photometer \n
 */
bool detachLightCallback (Light this_gen);

/*!	@fn			void LightOn (Light this_gen)
 *  @brief 		생성한 Light를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Light 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Light를 활성화 시킨다.
 *  @see 		NewLight \n
 *  			DestroyLight \n
 *  			addLightCallback \n
 *  			detachLightCallback \n
 *  			LightOff \n
 *  			isLightSupported \n
 *  			getLightValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.photometer \n
 */
bool LightOn (Light this_gen);

/*!	@fn			void LightOff (Light this_gen)
 *  @brief 		생성한 Light를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Light 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Light를 비활성화 시킨다.
 *  @see 		NewLight \n
 *  			DestroyLight \n
 *  			addLightCallback \n
 *  			detachLightCallback \n
 *  			LightOn \n
 *  			isLightSupported \n
 *  			getLightValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.photometer \n
 */
bool LightOff (Light this_gen);

/*!	@fn			bool isLightSupported (Light this_gen)
 *  @brief 		Light의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Light 객체
 *  @param[out] null
 *  @retval 	bool 사용 가능 여부
 *  @note 		Light의 사용 가능 여부를 판단한다.
 *  @see 		NewLight \n
 *  			DestroyLight \n
 *  			addLightCallback \n
 *  			detachLightCallback \n
 *  			LightOn \n
 *  			LightOff \n
 *  			getLightValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.photometer \n
 */
bool isLightSupported (Light this_gen);

/*!	@fn			Light_data getLightValue (Light this_gen)
 *  @brief 		활성화 되어 있는 Light의 센서 값을 반환한다.
 *  @param[in] 	this_gen 센서 값을 받을 Light 객체
 *  @param[out] null
 *  @retval 	Light_data Light의 센서 값
 *  @note 		활성화 되어 있는 Light의 센서 값을 반환한다.
 *  @see 		NewLight \n
 *  			DestroyLight \n
 *  			addLightCallback \n
 *  			detachLightCallback \n
 *  			LightOn \n
 *  			LightOff \n
 *  			isLightSupported \n
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.photometer \n
 */
Light_data getLightValue (Light this_gen);

/* Light */


/* Proximity */
/*! @struct	_Proximity
 *  @brief	Proximity 모듈에 대한 구조체이다. Proximity 모듈은 Proximity Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Proximity 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewProximity() 함수를 사용해야 하며 사용이 끝났을 때 DestroyProximity() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html
 *  @todo	feature에 "http://tizen.org/feature/sensor.proximity" 들을 반드시 추가해야 한다.
 */
typedef struct _Proximity * Proximity;

struct _Proximity
{

    bool(* addCallback) (Proximity this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    bool(* detachCallback) (Proximity this_gen);

    bool(* On) (Proximity this_gen);

    bool(* Off) (Proximity this_gen);

    bool(* isSupported) (Proximity this_gen);

    Proximity_data (* getValue) (Proximity this_gen);

};

typedef struct _ProximityExtend
{
    struct _Proximity proximity;
    sensor_type_e     type;
    sensor_h          sensor;
    sensor_listener_h listener;
    bool activated;

} ProximityExtend;

/*!	@fn			Proximity NewProximity (void)
 *  @brief		새로운 Proximity 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Proximity
 *  @note 		새로운 Proximity 객체를 생성한다. \n
 *  			Proximity 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyProximity \n
 *  			addProximityCallback \n
 *  			detachProximityCallback \n
 *  			ProximityOn \n
 *  			ProximityOff \n
 *  			isProximitySupported \n
 *  			getProximityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.proximity \n
 */
Proximity NewProximity (void);

/*!	@fn			void DestroyProximity (Proximity this_gen)
 *  @brief 		생성한 Proximity 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Proximity 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Proximity 객체를 소멸 시킨다. \n
 *  			Proximity 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewProximity
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.proximity \n
 */
void DestroyProximity (Proximity this_gen);

/*!	@fn			void addProximityCallback (Proximity this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Proximity에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Proximity 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	voiceinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Proximity에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewProximity \n
 *  			DestroyProximity \n
 *  			detachProximityCallback \n
 *  			ProximityOn \n
 *  			ProximityOff \n
 *  			isProximitySupported \n
 *  			getProximityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.proximity \n
 */
bool addProximityCallback (Proximity this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			void detachProximityCallback (Proximity this_gen)
 *  @brief 		생성한 Proximity에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Proximity 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Proximity에서 callback 함수를 삭제한다. \n
 *  @see 		NewProximity \n
 *  			DestroyProximity \n
 *  			addProximityCallback \n
 *  			ProximityOn \n
 *  			ProximityOff \n
 *  			isProximitySupported \n
 *  			getProximityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.proximity \n
 */
bool detachProximityCallback (Proximity this_gen);

/*!	@fn			void ProximityOn (Proximity this_gen)
 *  @brief 		생성한 Proximity를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Proximity 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Proximity를 활성화 시킨다.
 *  @see 		NewProximity \n
 *  			DestroyProximity \n
 *  			addProximityCallback \n
 *  			detachProximityCallback \n
 *  			ProximityOff \n
 *  			isProximitySupported \n
 *  			getProximityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.proximity \n
 */
bool ProximityOn (Proximity this_gen);

/*!	@fn			void ProximityOff (Proximity this_gen)
 *  @brief 		생성한 Proximity를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Proximity 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Proximity를 비활성화 시킨다.
 *  @see 		NewProximity \n
 *  			DestroyProximity \n
 *  			addProximityCallback \n
 *  			detachProximityCallback \n
 *  			ProximityOn \n
 *  			isProximitySupported \n
 *  			getProximityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.proximity \n
 */
bool ProximityOff (Proximity this_gen);

/*!	@fn			bool isProximitySupported (Proximity this_gen)
 *  @brief 		Proximity의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Proximity 객체
 *  @param[out] null
 *  @retval 	bool 사용 가능 여부
 *  @note 		Proximity의 사용 가능 여부를 판단한다.
 *  @see 		NewProximity \n
 *  			DestroyProximity \n
 *  			addProximityCallback \n
 *  			detachProximityCallback \n
 *  			ProximityOn \n
 *  			ProximityOff \n
 *  			getProximityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.proximity \n
 */
bool isProximitySupported (Proximity this_gen);

/*!	@fn			Proximity_data getProximityValue (Proximity this_gen)
 *  @brief 		활성화 되어 있는 Proximity의 센서 값을 반환한다.
 *  @param[in] 	this_gen 센서 값을 받을 Proximity 객체
 *  @param[out] null
 *  @retval 	Proximity_data Proximity의 센서 값
 *  @note 		활성화 되어 있는 Proximity의 센서 값을 반환한다.
 *  @see 		NewProximity \n
 *  			DestroyProximity \n
 *  			addProximityCallback \n
 *  			detachProximityCallback \n
 *  			ProximityOn \n
 *  			ProximityOff \n
 *  			isProximitySupported \n
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.proximity \n
 */
Proximity_data getProximityValue (Proximity this_gen);
/* Proximity */


/* Pressure */
/*! @struct	_Pressure
 *  @brief	Pressure 모듈에 대한 구조체이다. Pressure 모듈은 Pressure Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Pressure 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewPressure() 함수를 사용해야 하며 사용이 끝났을 때 DestroyPressure() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html
 *  @todo	feature에 "http://tizen.org/feature/sensor.*" 들을 반드시 추가해야 한다.
 */
typedef struct _Pressure * Pressure;

struct _Pressure
{

    bool(* addCallback) (Pressure this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    bool(* detachCallback) (Pressure this_gen);

    bool(* On) (Pressure this_gen);

    bool(* Off) (Pressure this_gen);

    bool(* isSupported) (Pressure this_gen);

    Pressure_data (* getValue) (Pressure this_gen);

};

typedef struct _PressureExtend
{
    struct _Pressure  pressure;
    sensor_type_e     type;
    sensor_h          sensor;
    sensor_listener_h listener;
    bool activated;

} PressureExtend;

/*!	@fn			Pressure NewPressure (void)
 *  @brief		새로운 Pressure 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Pressure
 *  @note 		새로운 Pressure 객체를 생성한다. \n
 *  			Pressure 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyPressure \n
 *  			addPressureCallback \n
 *  			detachPressureCallback \n
 *  			PressureOn \n
 *  			PressureOff \n
 *  			isPressureSupported \n
 *  			getPressureValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 *							http://tizen.org/feature/sensor.barometer \n
 *							http://tizen.org/feature/sensor.gyroscope \n
 *							http://tizen.org/feature/sensor.magnetometer \n
 *							http://tizen.org/feature/sensor.photometer \n
 *							http://tizen.org/feature/sensor.proximity \n
 *							http://tizen.org/feature/sensor.tiltmeter \n
 *							http://tizen.org/feature/sensor.ultraviolet \n
 *							http://tizen.org/feature/sensor.temperature \n
 *							http://tizen.org/feature/sensor.humidity \n
 *							http://tizen.org/feature/sensor.linear_acceleration \n
 *							http://tizen.org/feature/sensor.rotation_vector \n
 *							http://tizen.org/feature/sensor.gravity
 */
Pressure NewPressure (void);

/*!	@fn			void DestroyPressure (Pressure this_gen)
 *  @brief 		생성한 Pressure 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Pressure 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Pressure 객체를 소멸 시킨다. \n
 *  			Pressure 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewPressure
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 *							http://tizen.org/feature/sensor.barometer \n
 *							http://tizen.org/feature/sensor.gyroscope \n
 *							http://tizen.org/feature/sensor.magnetometer \n
 *							http://tizen.org/feature/sensor.photometer \n
 *							http://tizen.org/feature/sensor.proximity \n
 *							http://tizen.org/feature/sensor.tiltmeter \n
 *							http://tizen.org/feature/sensor.ultraviolet \n
 *							http://tizen.org/feature/sensor.temperature \n
 *							http://tizen.org/feature/sensor.humidity \n
 *							http://tizen.org/feature/sensor.linear_acceleration \n
 *							http://tizen.org/feature/sensor.rotation_vector \n
 *							http://tizen.org/feature/sensor.gravity
 */
void DestroyPressure (Pressure this_gen);

/*!	@fn			void addPressureCallback (Pressure this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Pressure에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Pressure 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	voiceinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Pressure에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewPressure \n
 *  			DestroyPressure \n
 *  			detachPressureCallback \n
 *  			PressureOn \n
 *  			PressureOff \n
 *  			isPressureSupported \n
 *  			getPressureValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 *							http://tizen.org/feature/sensor.barometer \n
 *							http://tizen.org/feature/sensor.gyroscope \n
 *							http://tizen.org/feature/sensor.magnetometer \n
 *							http://tizen.org/feature/sensor.photometer \n
 *							http://tizen.org/feature/sensor.proximity \n
 *							http://tizen.org/feature/sensor.tiltmeter \n
 *							http://tizen.org/feature/sensor.ultraviolet \n
 *							http://tizen.org/feature/sensor.temperature \n
 *							http://tizen.org/feature/sensor.humidity \n
 *							http://tizen.org/feature/sensor.linear_acceleration \n
 *							http://tizen.org/feature/sensor.rotation_vector \n
 *							http://tizen.org/feature/sensor.gravity
 */
bool addPressureCallback (Pressure this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			void detachPressureCallback (Pressure this_gen)
 *  @brief 		생성한 Pressure에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Pressure 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Pressure에서 callback 함수를 삭제한다. \n
 *  @see 		NewPressure \n
 *  			DestroyPressure \n
 *  			addPressureCallback \n
 *  			PressureOn \n
 *  			PressureOff \n
 *  			isPressureSupported \n
 *  			getPressureValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 *							http://tizen.org/feature/sensor.barometer \n
 *							http://tizen.org/feature/sensor.gyroscope \n
 *							http://tizen.org/feature/sensor.magnetometer \n
 *							http://tizen.org/feature/sensor.photometer \n
 *							http://tizen.org/feature/sensor.proximity \n
 *							http://tizen.org/feature/sensor.tiltmeter \n
 *							http://tizen.org/feature/sensor.ultraviolet \n
 *							http://tizen.org/feature/sensor.temperature \n
 *							http://tizen.org/feature/sensor.humidity \n
 *							http://tizen.org/feature/sensor.linear_acceleration \n
 *							http://tizen.org/feature/sensor.rotation_vector \n
 *							http://tizen.org/feature/sensor.gravity
 */
bool detachPressureCallback (Pressure this_gen);

/*!	@fn			void PressureOn (Pressure this_gen)
 *  @brief 		생성한 Pressure를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Pressure 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Pressure를 활성화 시킨다.
 *  @see 		NewPressure \n
 *  			DestroyPressure \n
 *  			addPressureCallback \n
 *  			detachPressureCallback \n
 *  			PressureOff \n
 *  			isPressureSupported \n
 *  			getPressureValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 *							http://tizen.org/feature/sensor.barometer \n
 *							http://tizen.org/feature/sensor.gyroscope \n
 *							http://tizen.org/feature/sensor.magnetometer \n
 *							http://tizen.org/feature/sensor.photometer \n
 *							http://tizen.org/feature/sensor.proximity \n
 *							http://tizen.org/feature/sensor.tiltmeter \n
 *							http://tizen.org/feature/sensor.ultraviolet \n
 *							http://tizen.org/feature/sensor.temperature \n
 *							http://tizen.org/feature/sensor.humidity \n
 *							http://tizen.org/feature/sensor.linear_acceleration \n
 *							http://tizen.org/feature/sensor.rotation_vector \n
 *							http://tizen.org/feature/sensor.gravity
 */
bool PressureOn (Pressure this_gen);

/*!	@fn			void PressureOff (Pressure this_gen)
 *  @brief 		생성한 Pressure를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Pressure 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Pressure를 비활성화 시킨다.
 *  @see 		NewPressure \n
 *  			DestroyPressure \n
 *  			addPressureCallback \n
 *  			detachPressureCallback \n
 *  			PressureOn \n
 *  			isPressureSupported \n
 *  			getPressureValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 *							http://tizen.org/feature/sensor.barometer \n
 *							http://tizen.org/feature/sensor.gyroscope \n
 *							http://tizen.org/feature/sensor.magnetometer \n
 *							http://tizen.org/feature/sensor.photometer \n
 *							http://tizen.org/feature/sensor.proximity \n
 *							http://tizen.org/feature/sensor.tiltmeter \n
 *							http://tizen.org/feature/sensor.ultraviolet \n
 *							http://tizen.org/feature/sensor.temperature \n
 *							http://tizen.org/feature/sensor.humidity \n
 *							http://tizen.org/feature/sensor.linear_acceleration \n
 *							http://tizen.org/feature/sensor.rotation_vector \n
 *							http://tizen.org/feature/sensor.gravity
 */
bool PressureOff (Pressure this_gen);

/*!	@fn			bool isPressureSupported (Pressure this_gen)
 *  @brief 		Pressure의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Pressure 객체
 *  @param[out] null
 *  @retval 	bool 사용 가능 여부
 *  @note 		Pressure의 사용 가능 여부를 판단한다.
 *  @see 		NewPressure \n
 *  			DestroyPressure \n
 *  			addPressureCallback \n
 *  			detachPressureCallback \n
 *  			PressureOn \n
 *  			PressureOff \n
 *  			getPressureValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 *							http://tizen.org/feature/sensor.barometer \n
 *							http://tizen.org/feature/sensor.gyroscope \n
 *							http://tizen.org/feature/sensor.magnetometer \n
 *							http://tizen.org/feature/sensor.photometer \n
 *							http://tizen.org/feature/sensor.proximity \n
 *							http://tizen.org/feature/sensor.tiltmeter \n
 *							http://tizen.org/feature/sensor.ultraviolet \n
 *							http://tizen.org/feature/sensor.temperature \n
 *							http://tizen.org/feature/sensor.humidity \n
 *							http://tizen.org/feature/sensor.linear_acceleration \n
 *							http://tizen.org/feature/sensor.rotation_vector \n
 *							http://tizen.org/feature/sensor.gravity
 */
bool isPressureSupported (Pressure this_gen);

/*!	@fn			Pressure_data getPressureValue (Pressure this_gen)
 *  @brief 		활성화 되어 있는 Pressure의 센서 값을 반환한다.
 *  @param[in] 	this_gen 센서 값을 받을 Pressure 객체
 *  @param[out] null
 *  @retval 	Pressure_data Pressure의 센서 값
 *  @note 		활성화 되어 있는 Pressure의 센서 값을 반환한다.
 *  @see 		NewPressure \n
 *  			DestroyPressure \n
 *  			addPressureCallback \n
 *  			detachPressureCallback \n
 *  			PressureOn \n
 *  			PressureOff \n
 *  			isPressureSupported \n
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.accelerometer \n
 *							http://tizen.org/feature/sensor.barometer \n
 *							http://tizen.org/feature/sensor.gyroscope \n
 *							http://tizen.org/feature/sensor.magnetometer \n
 *							http://tizen.org/feature/sensor.photometer \n
 *							http://tizen.org/feature/sensor.proximity \n
 *							http://tizen.org/feature/sensor.tiltmeter \n
 *							http://tizen.org/feature/sensor.ultraviolet \n
 *							http://tizen.org/feature/sensor.temperature \n
 *							http://tizen.org/feature/sensor.humidity \n
 *							http://tizen.org/feature/sensor.linear_acceleration \n
 *							http://tizen.org/feature/sensor.rotation_vector \n
 *							http://tizen.org/feature/sensor.gravity
 */
Pressure_data getPressureValue (Pressure this_gen);
/* Pressure */


/* UltraViolet */
/*! @struct	_UltraViolet
 *  @brief	UltraViolet 모듈에 대한 구조체이다. UltraViolet 모듈은 UltraViolet Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	UltraViolet 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewUltraViolet() 함수를 사용해야 하며 사용이 끝났을 때 DestroyUltraViolet() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html
 *  @todo	feature에 "http://tizen.org/feature/sensor.ultraviolet" 들을 반드시 추가해야 한다.
 */
typedef struct _UltraViolet * UltraViolet;

struct _UltraViolet
{

    bool(* addCallback) (UltraViolet this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    bool(* detachCallback) (UltraViolet this_gen);

    bool(* On) (UltraViolet this_gen);

    bool(* Off) (UltraViolet this_gen);

    bool(* isSupported) (UltraViolet this_gen);

    UltraViolet_data (* getValue) (UltraViolet this_gen);

};

typedef struct _UltraVioletExtend
{
    struct _UltraViolet ultraviolet;
    sensor_type_e       type;
    sensor_h            sensor;
    sensor_listener_h   listener;
    bool activated;

} UltraVioletExtend;

/*!	@fn			UltraViolet NewUltraViolet (void)
 *  @brief		새로운 UltraViolet 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	UltraViolet
 *  @note 		새로운 UltraViolet 객체를 생성한다. \n
 *  			UltraViolet 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyUltraViolet \n
 *  			addUltraVioletCallback \n
 *  			detachUltraVioletCallback \n
 *  			UltraVioletOn \n
 *  			UltraVioletOff \n
 *  			isUltraVioletSupported \n
 *  			getUltraVioletValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.ultraviolet \n
 */
UltraViolet NewUltraViolet (void);

/*!	@fn			void DestroyUltraViolet (UltraViolet this_gen)
 *  @brief 		생성한 UltraViolet 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 UltraViolet 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 UltraViolet 객체를 소멸 시킨다. \n
 *  			UltraViolet 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewUltraViolet
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.ultraviolet \n
 */
void DestroyUltraViolet (UltraViolet this_gen);

/*!	@fn			void addUltraVioletCallback (UltraViolet this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 UltraViolet에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 UltraViolet 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	voiceinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 UltraViolet에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewUltraViolet \n
 *  			DestroyUltraViolet \n
 *  			detachUltraVioletCallback \n
 *  			UltraVioletOn \n
 *  			UltraVioletOff \n
 *  			isUltraVioletSupported \n
 *  			getUltraVioletValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.ultraviolet \n
 */
bool addUltraVioletCallback (UltraViolet this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			void detachUltraVioletCallback (UltraViolet this_gen)
 *  @brief 		생성한 UltraViolet에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 UltraViolet 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 UltraViolet에서 callback 함수를 삭제한다. \n
 *  @see 		NewUltraViolet \n
 *  			DestroyUltraViolet \n
 *  			addUltraVioletCallback \n
 *  			UltraVioletOn \n
 *  			UltraVioletOff \n
 *  			isUltraVioletSupported \n
 *  			getUltraVioletValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.ultraviolet \n
 */
bool detachUltraVioletCallback (UltraViolet this_gen);

/*!	@fn			void UltraVioletOn (UltraViolet this_gen)
 *  @brief 		생성한 UltraViolet를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 UltraViolet 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 UltraViolet를 활성화 시킨다.
 *  @see 		NewUltraViolet \n
 *  			DestroyUltraViolet \n
 *  			addUltraVioletCallback \n
 *  			detachUltraVioletCallback \n
 *  			UltraVioletOff \n
 *  			isUltraVioletSupported \n
 *  			getUltraVioletValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.ultraviolet \n
 */
bool UltraVioletOn (UltraViolet this_gen);

/*!	@fn			void UltraVioletOff (UltraViolet this_gen)
 *  @brief 		생성한 UltraViolet를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 UltraViolet 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 UltraViolet를 비활성화 시킨다.
 *  @see 		NewUltraViolet \n
 *  			DestroyUltraViolet \n
 *  			addUltraVioletCallback \n
 *  			detachUltraVioletCallback \n
 *  			UltraVioletOn \n
 *  			isUltraVioletSupported \n
 *  			getUltraVioletValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.ultraviolet \n
 */
bool UltraVioletOff (UltraViolet this_gen);

/*!	@fn			bool isUltraVioletSupported (UltraViolet this_gen)
 *  @brief 		UltraViolet의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 UltraViolet 객체
 *  @param[out] null
 *  @retval 	bool 사용 가능 여부
 *  @note 		UltraViolet의 사용 가능 여부를 판단한다.
 *  @see 		NewUltraViolet \n
 *  			DestroyUltraViolet \n
 *  			addUltraVioletCallback \n
 *  			detachUltraVioletCallback \n
 *  			UltraVioletOn \n
 *  			UltraVioletOff \n
 *  			getUltraVioletValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.ultraviolet \n
 */
bool isUltraVioletSupported (UltraViolet this_gen);

/*!	@fn			UltraViolet_data getUltraVioletValue (UltraViolet this_gen)
 *  @brief 		활성화 되어 있는 UltraViolet의 센서 값을 반환한다.
 *  @param[in] 	this_gen 센서 값을 받을 UltraViolet 객체
 *  @param[out] null
 *  @retval 	UltraViolet_data UltraViolet의 센서 값
 *  @note 		활성화 되어 있는 UltraViolet의 센서 값을 반환한다.
 *  @see 		NewUltraViolet \n
 *  			DestroyUltraViolet \n
 *  			addUltraVioletCallback \n
 *  			detachUltraVioletCallback \n
 *  			UltraVioletOn \n
 *  			UltraVioletOff \n
 *  			isUltraVioletSupported \n
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.ultraviolet \n
 */
UltraViolet_data getUltraVioletValue (UltraViolet this_gen);
/* UltraViolet */


/* Temperature */
/*! @struct	_Temperature
 *  @brief	Temperature 모듈에 대한 구조체이다. Temperature 모듈은 Temperature Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Temperature 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewTemperature() 함수를 사용해야 하며 사용이 끝났을 때 DestroyTemperature() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html
 *  @todo	feature에 "http://tizen.org/feature/sensor.temperature" 들을 반드시 추가해야 한다.
 */
typedef struct _Temperature * Temperature;

struct _Temperature
{

    bool(* addCallback) (Temperature this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    bool(* detachCallback) (Temperature this_gen);

    bool(* On) (Temperature this_gen);

    bool(* Off) (Temperature this_gen);

    bool(* isSupported) (Temperature this_gen);

    Temperature_data (* getValue) (Temperature this_gen);

};

typedef struct _TemperatureExtend
{
    struct _Temperature temperature;
    sensor_type_e       type;
    sensor_h            sensor;
    sensor_listener_h   listener;
    bool activated;

} TemperatureExtend;

/*!	@fn			Temperature NewTemperature (void)
 *  @brief		새로운 Temperature 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Temperature
 *  @note 		새로운 Temperature 객체를 생성한다. \n
 *  			Temperature 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyTemperature \n
 *  			addTemperatureCallback \n
 *  			detachTemperatureCallback \n
 *  			TemperatureOn \n
 *  			TemperatureOff \n
 *  			isTemperatureSupported \n
 *  			getTemperatureValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.temperature \n
 */
Temperature NewTemperature (void);

/*!	@fn			void DestroyTemperature (Temperature this_gen)
 *  @brief 		생성한 Temperature 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Temperature 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Temperature 객체를 소멸 시킨다. \n
 *  			Temperature 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewTemperature
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.temperature \n
 */
void DestroyTemperature (Temperature this_gen);

/*!	@fn			void addTemperatureCallback (Temperature this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Temperature에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Temperature 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	voiceinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Temperature에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewTemperature \n
 *  			DestroyTemperature \n
 *  			detachTemperatureCallback \n
 *  			TemperatureOn \n
 *  			TemperatureOff \n
 *  			isTemperatureSupported \n
 *  			getTemperatureValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.temperature \n
 */
bool addTemperatureCallback (Temperature this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			void detachTemperatureCallback (Temperature this_gen)
 *  @brief 		생성한 Temperature에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Temperature 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Temperature에서 callback 함수를 삭제한다. \n
 *  @see 		NewTemperature \n
 *  			DestroyTemperature \n
 *  			addTemperatureCallback \n
 *  			TemperatureOn \n
 *  			TemperatureOff \n
 *  			isTemperatureSupported \n
 *  			getTemperatureValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.temperature \n
 */
bool detachTemperatureCallback (Temperature this_gen);

/*!	@fn			void TemperatureOn (Temperature this_gen)
 *  @brief 		생성한 Temperature를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Temperature 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Temperature를 활성화 시킨다.
 *  @see 		NewTemperature \n
 *  			DestroyTemperature \n
 *  			addTemperatureCallback \n
 *  			detachTemperatureCallback \n
 *  			TemperatureOff \n
 *  			isTemperatureSupported \n
 *  			getTemperatureValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.temperature \n
 */
bool TemperatureOn (Temperature this_gen);

/*!	@fn			void TemperatureOff (Temperature this_gen)
 *  @brief 		생성한 Temperature를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Temperature 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Temperature를 비활성화 시킨다.
 *  @see 		NewTemperature \n
 *  			DestroyTemperature \n
 *  			addTemperatureCallback \n
 *  			detachTemperatureCallback \n
 *  			TemperatureOn \n
 *  			isTemperatureSupported \n
 *  			getTemperatureValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.temperature \n
 */
bool TemperatureOff (Temperature this_gen);

/*!	@fn			bool isTemperatureSupported (Temperature this_gen)
 *  @brief 		Temperature의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Temperature 객체
 *  @param[out] null
 *  @retval 	bool 사용 가능 여부
 *  @note 		Temperature의 사용 가능 여부를 판단한다.
 *  @see 		NewTemperature \n
 *  			DestroyTemperature \n
 *  			addTemperatureCallback \n
 *  			detachTemperatureCallback \n
 *  			TemperatureOn \n
 *  			TemperatureOff \n
 *  			getTemperatureValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.temperature \n
 */
bool isTemperatureSupported (Temperature this_gen);

/*!	@fn			Temperature_data getTemperatureValue (Temperature this_gen)
 *  @brief 		활성화 되어 있는 Temperature의 센서 값을 반환한다.
 *  @param[in] 	this_gen 센서 값을 받을 Temperature 객체
 *  @param[out] null
 *  @retval 	Temperature_data Temperature의 센서 값
 *  @note 		활성화 되어 있는 Temperature의 센서 값을 반환한다.
 *  @see 		NewTemperature \n
 *  			DestroyTemperature \n
 *  			addTemperatureCallback \n
 *  			detachTemperatureCallback \n
 *  			TemperatureOn \n
 *  			TemperatureOff \n
 *  			isTemperatureSupported \n
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.temperature \n
 */
Temperature_data getTemperatureValue (Temperature this_gen);
/* Temperature */


/* Humidity */
/*! @struct	_Humidity
 *  @brief	Humidity 모듈에 대한 구조체이다. Humidity 모듈은 Humidity Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Humidity 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewHumidity() 함수를 사용해야 하며 사용이 끝났을 때 DestroyHumidity() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html
 *  @todo	feature에 "http://tizen.org/feature/sensor.humidity" 들을 반드시 추가해야 한다.
 */
typedef struct _Humidity * Humidity;

struct _Humidity
{

    bool(* addCallback) (Humidity this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    bool(* detachCallback) (Humidity this_gen);

    bool(* On) (Humidity this_gen);

    bool(* Off) (Humidity this_gen);

    bool(* isSupported) (Humidity this_gen);

    Humidity_data (* getValue) (Humidity this_gen);

};

typedef struct _HumidityExtend
{
    struct _Humidity  humidity;
    sensor_type_e     type;
    sensor_h          sensor;
    sensor_listener_h listener;
    bool activated;

} HumidityExtend;

/*!	@fn			Humidity NewHumidity (void)
 *  @brief		새로운 Humidity 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Humidity
 *  @note 		새로운 Humidity 객체를 생성한다. \n
 *  			Humidity 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyHumidity \n
 *  			addHumidityCallback \n
 *  			detachHumidityCallback \n
 *  			HumidityOn \n
 *  			HumidityOff \n
 *  			isHumiditySupported \n
 *  			getHumidityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.humidity \n
 */
Humidity NewHumidity (void);

/*!	@fn			void DestroyHumidity (Humidity this_gen)
 *  @brief 		생성한 Humidity 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Humidity 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Humidity 객체를 소멸 시킨다. \n
 *  			Humidity 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewHumidity
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.humidity \n
 */
void DestroyHumidity (Humidity this_gen);

/*!	@fn			void addHumidityCallback (Humidity this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Humidity에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Humidity 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	voiceinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Humidity에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewHumidity \n
 *  			DestroyHumidity \n
 *  			detachHumidityCallback \n
 *  			HumidityOn \n
 *  			HumidityOff \n
 *  			isHumiditySupported \n
 *  			getHumidityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.humidity \n
 */
bool addHumidityCallback (Humidity this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			void detachHumidityCallback (Humidity this_gen)
 *  @brief 		생성한 Humidity에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Humidity 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Humidity에서 callback 함수를 삭제한다. \n
 *  @see 		NewHumidity \n
 *  			DestroyHumidity \n
 *  			addHumidityCallback \n
 *  			HumidityOn \n
 *  			HumidityOff \n
 *  			isHumiditySupported \n
 *  			getHumidityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.humidity \n
 */
bool detachHumidityCallback (Humidity this_gen);

/*!	@fn			void HumidityOn (Humidity this_gen)
 *  @brief 		생성한 Humidity를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Humidity 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Humidity를 활성화 시킨다.
 *  @see 		NewHumidity \n
 *  			DestroyHumidity \n
 *  			addHumidityCallback \n
 *  			detachHumidityCallback \n
 *  			HumidityOff \n
 *  			isHumiditySupported \n
 *  			getHumidityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.humidity \n
 */
bool HumidityOn (Humidity this_gen);

/*!	@fn			void HumidityOff (Humidity this_gen)
 *  @brief 		생성한 Humidity를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Humidity 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Humidity를 비활성화 시킨다.
 *  @see 		NewHumidity \n
 *  			DestroyHumidity \n
 *  			addHumidityCallback \n
 *  			detachHumidityCallback \n
 *  			HumidityOn \n
 *  			isHumiditySupported \n
 *  			getHumidityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.humidity \n
 */
bool HumidityOff (Humidity this_gen);

/*!	@fn			bool isHumiditySupported (Humidity this_gen)
 *  @brief 		Humidity의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Humidity 객체
 *  @param[out] null
 *  @retval 	bool 사용 가능 여부
 *  @note 		Humidity의 사용 가능 여부를 판단한다.
 *  @see 		NewHumidity \n
 *  			DestroyHumidity \n
 *  			addHumidityCallback \n
 *  			detachHumidityCallback \n
 *  			HumidityOn \n
 *  			HumidityOff \n
 *  			getHumidityValue
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.humidity \n
 */
bool isHumiditySupported (Humidity this_gen);

/*!	@fn			Humidity_data getHumidityValue (Humidity this_gen)
 *  @brief 		활성화 되어 있는 Humidity의 센서 값을 반환한다.
 *  @param[in] 	this_gen 센서 값을 받을 Humidity 객체
 *  @param[out] null
 *  @retval 	Humidity_data Humidity의 센서 값
 *  @note 		활성화 되어 있는 Humidity의 센서 값을 반환한다.
 *  @see 		NewHumidity \n
 *  			DestroyHumidity \n
 *  			addHumidityCallback \n
 *  			detachHumidityCallback \n
 *  			HumidityOn \n
 *  			HumidityOff \n
 *  			isHumiditySupported \n
 *  @remark 	feature	: 	http://tizen.org/feature/sensor.humidity \n
 */
Humidity_data getHumidityValue (Humidity this_gen);
/* Humidity */

#ifdef __cplusplus
}
#endif

#endif //DIT_SENSOR_H
