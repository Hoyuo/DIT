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

    void(* addCallback) (Accelerometer this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    void(* detachCallback) (Accelerometer this_gen);

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
    bool activated;
} AccelerometerExtend;

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.accelerometer
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
 *  @remark 	feature	: http://tizen.org/feature/sensor.accelerometer
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
 *  @remark 	feature	: http://tizen.org/feature/sensor.accelerometer
*/
void addAccelerometerCallback (Accelerometer this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.accelerometer
*/
void detachAccelerometerCallback (Accelerometer this_gen);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.accelerometer
*/
void AccelerometerOn (Accelerometer this_gen);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.accelerometer
*/
void AccelerometerOff (Accelerometer this_gen);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.accelerometer
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
 *  @remark 	feature	: http://tizen.org/feature/sensor.accelerometer
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

    void(* addCallback) (Gravity this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    void(* detachCallback) (Gravity this_gen);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.gravity
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
 *  @remark 	feature	: http://tizen.org/feature/sensor.gravity
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
 *  @remark 	feature	: http://tizen.org/feature/sensor.gravity
*/
void addGravityCallback (Gravity this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.gravity
*/
void detachGravityCallback (Gravity this_gen);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.gravity
*/
void GravityOn (Gravity this_gen);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.gravity
 */
void GravityOff (Gravity this_gen);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.gravity
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
 *  @remark 	feature	: http://tizen.org/feature/sensor.gravity
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

    void(* addCallback) (LinearAccelation this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    void(* detachCallback) (LinearAccelation this_gen);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.linear_acceleration
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
 *  @remark 	feature	: http://tizen.org/feature/sensor.linear_acceleration
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
 *  @remark 	feature	: http://tizen.org/feature/sensor.linear_acceleration
*/
void addLinearAccelationCallback (LinearAccelation this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.linear_acceleration
 */
void detachLinearAccelationCallback (LinearAccelation this_gen);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.linear_acceleration
 */
void LinearAccelationOn (LinearAccelation this_gen);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.linear_acceleration
 */
void LinearAccelationOff (LinearAccelation this_gen);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.linear_acceleration
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
 *  @remark 	feature	: http://tizen.org/feature/sensor.accelerometer
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

    void(* addCallback) (Magnetometer this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    void(* detachCallback) (Magnetometer this_gen);

    void(* On) (Magnetometer this_gen);

    void(* Off) (Magnetometer this_gen);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.magnetometer
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
 *  @remark 	feature	: http://tizen.org/feature/sensor.magnetometer
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
 *  @remark 	feature	: http://tizen.org/feature/sensor.magnetometer
*/
void addMagnetometerCallback (Magnetometer this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.magnetometer
*/
void detachMagnetometerCallback (Magnetometer this_gen);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.magnetometer
*/
void MagnetometerOn (Magnetometer this_gen);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.magnetometer
*/
void MagnetometerOff (Magnetometer this_gen);

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
 *  @remark 	feature	: http://tizen.org/feature/sensor.magnetometer
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
 *  @remark 	feature	: http://tizen.org/feature/sensor.magnetometer
*/
Magnetometer_data getMagnetometerValue (Magnetometer this_gen);

/* Magnetometer */


/* RotationVector */
typedef struct _RotationVector * RotationVector;

struct _RotationVector
{

    void(* addCallback) (RotationVector this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    void(* detachCallback) (RotationVector this_gen);

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
    bool activated;

} RotationVectorExtend;

RotationVector NewRotationVector ();

void DestroyRotationVector (RotationVector this_gen);

void addRotationVectorCallback (RotationVector this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

void detachRotationVectorCallback (RotationVector this_gen);

void RotationVectorOn (RotationVector this_gen);

void RotationVectorOff (RotationVector this_gen);

bool isRotationVectorSupported (RotationVector this_gen);

RotationVector_data getRotationVectorValue (RotationVector this_gen);

/* RotationVector */


/* Orientation */
typedef struct _Orientation * Orientation;

struct _Orientation
{

    void(* addCallback) (Orientation this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    void(* detachCallback) (Orientation this_gen);

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
    bool activated;

} OrientationExtend;

Orientation NewOrientation ();

void DestroyOrientation (Orientation this_gen);

void addOrientationCallback (Orientation this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

void detachOrientationCallback (Orientation this_gen);

void OrientationOn (Orientation this_gen);

void OrientationOff (Orientation this_gen);

bool isOrientationSupported (Orientation this_gen);

Orientation_data getOrientationValue (Orientation this_gen);

/* Orientation */


/* Gyroscope */
typedef struct _Gyroscope * Gyroscope;

struct _Gyroscope
{

    void(* addCallback) (Gyroscope this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    void(* detachCallback) (Gyroscope this_gen);

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
    bool activated;

} GyroscopeExtend;

Gyroscope NewGyroscope ();

void DestroyGyroscope (Gyroscope this_gen);

void addGyroscopeCallback (Gyroscope this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

void detachGyroscopeCallback (Gyroscope this_gen);

void GyroscopeOn (Gyroscope this_gen);

void GyroscopeOff (Gyroscope this_gen);

bool isGyroscopeSupported (Gyroscope this_gen);

Gyroscope_data getGyroscopeValue (Gyroscope this_gen);

/* Gyroscope */


/* Light */
typedef struct _Light * Light;

struct _Light
{

    void(* addCallback) (Light this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    void(* detachCallback) (Light this_gen);

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
    bool activated;

} LightExtend;

Light NewLight ();

void DestroyLight (Light this_gen);

void addLightCallback (Light this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

void detachLightCallback (Light this_gen);

void LightOn (Light this_gen);

void LightOff (Light this_gen);

bool isLightSupported (Light this_gen);

Light_data getLightValue (Light this_gen);

/* Light */


/* Proximity */
typedef struct _Proximity * Proximity;

struct _Proximity
{

    void(* addCallback) (Proximity this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    void(* detachCallback) (Proximity this_gen);

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
    bool activated;

} ProximityExtend;

Proximity NewProximity ();

void DestroyProximity (Proximity this_gen);

void addProximityCallback (Proximity this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

void detachProximityCallback (Proximity this_gen);

void ProximityOn (Proximity this_gen);

void ProximityOff (Proximity this_gen);

bool isProximitySupported (Proximity this_gen);

Proximity_data getProximityValue (Proximity this_gen);

/* Proximity */


/* Pressure */
typedef struct _Pressure * Pressure;

struct _Pressure
{

    void(* addCallback) (Pressure this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    void(* detachCallback) (Pressure this_gen);

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
    bool activated;

} PressureExtend;

Pressure NewPressure ();

void DestroyPressure (Pressure this_gen);

void addPressureCallback (Pressure this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

void detachPressureCallback (Pressure this_gen);

void PressureOn (Pressure this_gen);

void PressureOff (Pressure this_gen);

bool isPressureSupported (Pressure this_gen);

Pressure_data getPressureValue (Pressure this_gen);

/* Pressure */


/* UltraViolet */
typedef struct _UltraViolet * UltraViolet;

struct _UltraViolet
{

    void(* addCallback) (UltraViolet this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    void(* detachCallback) (UltraViolet this_gen);

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
    bool activated;

} UltraVioletExtend;

UltraViolet NewUltraViolet ();

void DestroyUltraViolet (UltraViolet this_gen);

void addUltraVioletCallback (UltraViolet this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

void detachUltraVioletCallback (UltraViolet this_gen);

void UltraVioletOn (UltraViolet this_gen);

void UltraVioletOff (UltraViolet this_gen);

bool isUltraVioletSupported (UltraViolet this_gen);

UltraViolet_data getUltraVioletValue (UltraViolet this_gen);

/* UltraViolet */


/* Temperature */
typedef struct _Temperature * Temperature;

struct _Temperature
{

    void(* addCallback) (Temperature this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    void(* detachCallback) (Temperature this_gen);

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
    bool activated;

} TemperatureExtend;

Temperature NewTemperature ();

void DestroyTemperature (Temperature this_gen);

void addTemperatureCallback (Temperature this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

void detachTemperatureCallback (Temperature this_gen);

void TemperatureOn (Temperature this_gen);

void TemperatureOff (Temperature this_gen);

bool isTemperatureSupported (Temperature this_gen);

Temperature_data getTemperatureValue (Temperature this_gen);

/* Temperature */


/* Humidity */
typedef struct _Humidity * Humidity;

struct _Humidity
{

    void(* addCallback) (Humidity this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

    void(* detachCallback) (Humidity this_gen);

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
    bool activated;

} HumidityExtend;

Humidity NewHumidity ();

void DestroyHumidity (Humidity this_gen);

void addHumidityCallback (Humidity this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

void detachHumidityCallback (Humidity this_gen);

void HumidityOn (Humidity this_gen);

void HumidityOff (Humidity this_gen);

bool isHumiditySupported (Humidity this_gen);

Humidity_data getHumidityValue (Humidity this_gen);

/* Humidity */

#ifdef __cplusplus
}
#endif

#endif //DIT_SENSOR_H
