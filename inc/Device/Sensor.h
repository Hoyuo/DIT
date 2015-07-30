/*! @file	Sensor.h
 *  @brief	Sensor API 를 사용하기 위해 포함해야 하는 헤더이다.
 *  @note	Sensor의 다양한 센서의 addCallback / detachCallback / On / Off / isSupported / getValue API를 제공한다.
 *  @see	[Tizen Native API](https://developer.tizen.org/development/api-references/native-application?redirect=https%3A//developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/index.html)
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

/*! @fn         const char * SensorErrorCheck (int errCode)
 *  @brief      Device Status API에서 발생하는 Error Code들을 확인 해준다.
 *  @param[in]  errCode 확인 하고자 하는 Error Code
 *  @param[out] null
 *  @retval     SENSOR_ERROR_NONE                   : Successful
 *  @retval     SENSOR_ERROR_IO_ERROR               : I/O error
 *  @retval     SENSOR_ERROR_INVALID_PARAMETER      : Invalid parameter
 *  @retval     SENSOR_ERROR_NOT_SUPPORTED          : Unsupported sensor in the current device
 *  @retval     SENSOR_ERROR_PERMISSION_DENIED      : Permission denied
 *  @retval     SENSOR_ERROR_OUT_OF_MEMORY          : Out of memory
 *  @retval     SENSOR_ERROR_NOT_NEED_CALIBRATION   : Sensor doesn't need calibration
 *  @retval     SENSOR_ERROR_OPERATION_FAILED       : Operation failed
 *  @retval     SENSOR_ERROR_UNKNOWN                : Unknown error occurred
 *  @note       Sensor API에서 발생하는 Error Code들을 확인 해준다. \n
 *              Error의 내용은 Log를 통해 출력 된다.    
 *              9가지의 Error Code들을 확인 가능 하다.
 *  @see        [Tizen Native API Document - Sensor Error](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html#ga1e7aa4addd02f92677c9e7f916c2fb7b)
 */
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
 *  @see	[Tizen Native API Document - Sensor part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html)
 *  @pre	@b feature \n
 *          * http://tizen.org/feature/sensor.accelerometer
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
 *  @pre     	@b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer
 *  @warning    사용이 끝났을 때 DestroyAccelerometer() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
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
 *	@endcode
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer
 */
void DestroyAccelerometer (Accelerometer this_gen);

/*!	@fn			bool addAccelerometerCallback (Accelerometer this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Accelerometer에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Accelerometer 객체
 *  @param[in] 	sensorCallback 등록할 callback 함수
 *  @param[in] 	timeinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data 주소
 *  @param[out] data callback 함수에 전달될 사용자 data
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Accelerometer에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 @c milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewAccelerometer \n
 *  			DestroyAccelerometer \n
 *  			detachAccelerometerCallback \n
 *  			AccelerometerOn \n
 *  			AccelerometerOff \n
 *  			isAccelerometerSupported \n
 *  			getAccelerometerValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer
 */
bool addAccelerometerCallback (Accelerometer this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			bool detachAccelerometerCallback (Accelerometer this_gen)
 *  @brief 		생성한 Accelerometer에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Accelerometer 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Accelerometer에서 callback 함수를 삭제한다. \n
 *  @see 		NewAccelerometer \n
 *  			DestroyAccelerometer \n
 *  			addAccelerometerCallback \n
 *  			AccelerometerOn \n
 *  			AccelerometerOff \n
 *  			isAccelerometerSupported \n
 *  			getAccelerometerValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer
 */
bool detachAccelerometerCallback (Accelerometer this_gen);

/*!	@fn			bool AccelerometerOn (Accelerometer this_gen)
 *  @brief 		생성한 Accelerometer를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Accelerometer 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Accelerometer를 활성화 시킨다.
 *  @see 		NewAccelerometer \n
 *  			DestroyAccelerometer \n
 *  			addAccelerometerCallback \n
 *  			detachAccelerometerCallback \n
 *  			AccelerometerOff \n
 *  			isAccelerometerSupported \n
 *  			getAccelerometerValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer
 */
bool AccelerometerOn (Accelerometer this_gen);

/*!	@fn			bool AccelerometerOff (Accelerometer this_gen)
 *  @brief 		생성한 Accelerometer를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Accelerometer 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Accelerometer를 비활성화 시킨다.
 *  @see 		NewAccelerometer \n
 *  			DestroyAccelerometer \n
 *  			addAccelerometerCallback \n
 *  			detachAccelerometerCallback \n
 *  			AccelerometerOn \n
 *  			isAccelerometerSupported \n
 *  			getAccelerometerValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer
 */
bool AccelerometerOff (Accelerometer this_gen);

/*!	@fn			bool isAccelerometerSupported (Accelerometer this_gen)
 *  @brief 		Accelerometer의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Accelerometer 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Accelerometer의 사용 가능 여부를 판단한다.
 *  @see 		NewAccelerometer \n
 *  			DestroyAccelerometer \n
 *  			addAccelerometerCallback \n
 *  			detachAccelerometerCallback \n
 *  			AccelerometerOn \n
 *  			AccelerometerOff \n
 *  			getAccelerometerValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer
 */
Accelerometer_data getAccelerometerValue (Accelerometer this_gen);
/* Accelerometer */


/* Gravity */
/*! @struct	_Gravity
 *  @brief	Gravity 모듈에 대한 구조체이다. Gravity 모듈은 Gravity Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Gravity 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewGravity() 함수를 사용해야 하며 사용이 끝났을 때 DestroyGravity() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Sensor part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html)
 *  @pre	@b feature \n
 *          * http://tizen.org/feature/sensor.gravity
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
 *  @pre     	@b feature \n
 *              * http://tizen.org/feature/sensor.gravity
 *  @warning    사용이 끝났을 때 DestroyGravity() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
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
 *	@endcode
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.gravity
 */
void DestroyGravity (Gravity this_gen);

/*!	@fn			bool addGravityCallback (Gravity this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Gravity에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Gravity 객체
 *  @param[in] 	sensorCallback 등록할 callback 함수
 *  @param[in] 	timeinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data 주소
 *  @param[out] data callback 함수에 전달될 사용자 data
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Gravity에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewGravity \n
 *  			DestroyGravity \n
 *  			detachGravityCallback \n
 *  			GravityOn \n
 *  			GravityOff \n
 *  			isGravitySupported \n
 *  			getGravityValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.gravity
 */
bool addGravityCallback (Gravity this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			bool detachGravityCallback (Gravity this_gen)
 *  @brief 		생성한 Gravity에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Gravity 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Gravity에서 callback 함수를 삭제한다. \n
 *  @see 		NewGravity \n
 *  			DestroyGravity \n
 *  			addGravityCallback \n
 *  			GravityOn \n
 *  			GravityOff \n
 *  			isGravitySupported \n
 *  			getGravityValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.gravity
 */
bool detachGravityCallback (Gravity this_gen);

/*!	@fn			bool GravityOn (Gravity this_gen)
 *  @brief 		생성한 Gravity를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Gravity 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Gravity를 활성화 시킨다.
 *  @see 		NewGravity \n
 *  			DestroyGravity \n
 *  			addGravityCallback \n
 *  			detachGravityCallback \n
 *  			GravityOff \n
 *  			isGravitySupported \n
 *  			getGravityValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.gravity
 */
bool GravityOn (Gravity this_gen);

/*!	@fn			bool GravityOff (Gravity this_gen)
 *  @brief 		생성한 Gravity를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Gravity 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Gravity를 비활성화 시킨다.
 *  @see 		NewGravity \n
 *  			DestroyGravity \n
 *  			addGravityCallback \n
 *  			detachGravityCallback \n
 *  			GravityOn \n
 *  			isGravitySupported \n
 *  			getGravityValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.gravity
 */
bool GravityOff (Gravity this_gen);

/*!	@fn			bool isGravitySupported (Gravity this_gen)
 *  @brief 		Gravity의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Gravity 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.\
 *  @note 		Gravity의 사용 가능 여부를 판단한다.
 *  @see 		NewGravity \n
 *  			DestroyGravity \n
 *  			addGravityCallback \n
 *  			detachGravityCallback \n
 *  			GravityOn \n
 *  			GravityOff \n
 *  			getGravityValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.gravity
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.gravity
 */
Gravity_data getGravityValue (Gravity this_gen);
/* Gravity */


/* LinearAccelation */
/*! @struct	_LinearAccelation
 *  @brief	LinearAccelation 모듈에 대한 구조체이다. LinearAccelation 모듈은 LinearAccelation Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	LinearAccelation 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewLinearAccelation() 함수를 사용해야 하며 사용이 끝났을 때 DestroyLinearAccelation() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Sensor part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html)
 *  @pre	@b feature \n
 *          * http://tizen.org/feature/sensor.linear_acceleration
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
 *  @pre     	@b feature \n
 *              * http://tizen.org/feature/sensor.linear_acceleration
 *  @warning    사용이 끝났을 때 DestroyLinearAccelation() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
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
 *	@endcode
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.linear_acceleration
 */
void DestroyLinearAccelation (LinearAccelation this_gen);

/*!	@fn			bool addLinearAccelationCallback (LinearAccelation this_gen, sensor_callback sensorCallback, int timeenterval, void * data)
 *  @brief 		생성한 LinearAccelation에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 LinearAccelation 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	timeinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data 주소
 *  @param[out] data callback 함수에 전달될 사용자 data
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 LinearAccelation에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewLinearAccelation \n
 *  			DestroyLinearAccelation \n
 *  			detachLinearAccelationCallback \n
 *  			LinearAccelationOn \n
 *  			LinearAccelationOff \n
 *  			isLinearAccelationSupported \n
 *  			getLinearAccelationValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.linear_acceleration
 */
bool addLinearAccelationCallback (LinearAccelation this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			bool detachLinearAccelationCallback (LinearAccelation this_gen)
 *  @brief 		생성한 LinearAccelation에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 LinearAccelation 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 LinearAccelation에서 callback 함수를 삭제한다. \n
 *  @see 		NewLinearAccelation \n
 *  			DestroyLinearAccelation \n
 *  			addLinearAccelationCallback \n
 *  			LinearAccelationOn \n
 *  			LinearAccelationOff \n
 *  			isLinearAccelationSupported \n
 *  			getLinearAccelationValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.linear_acceleration
 */
bool detachLinearAccelationCallback (LinearAccelation this_gen);

/*!	@fn			bool LinearAccelationOn (LinearAccelation this_gen)
 *  @brief 		생성한 LinearAccelation를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 LinearAccelation 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 LinearAccelation를 활성화 시킨다.
 *  @see 		NewLinearAccelation \n
 *  			DestroyLinearAccelation \n
 *  			addLinearAccelationCallback \n
 *  			detachLinearAccelationCallback \n
 *  			LinearAccelationOff \n
 *  			isLinearAccelationSupported \n
 *  			getLinearAccelationValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.linear_acceleration
 */
bool LinearAccelationOn (LinearAccelation this_gen);

/*!	@fn			bool LinearAccelationOff (LinearAccelation this_gen)
 *  @brief 		생성한 LinearAccelation를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 LinearAccelation 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 LinearAccelation를 비활성화 시킨다.
 *  @see 		NewLinearAccelation \n
 *  			DestroyLinearAccelation \n
 *  			addLinearAccelationCallback \n
 *  			detachLinearAccelationCallback \n
 *  			LinearAccelationOn \n
 *  			isLinearAccelationSupported \n
 *  			getLinearAccelationValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.linear_acceleration
 */
bool LinearAccelationOff (LinearAccelation this_gen);

/*!	@fn			bool isLinearAccelationSupported (LinearAccelation this_gen)
 *  @brief 		LinearAccelation의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 LinearAccelation 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		LinearAccelation의 사용 가능 여부를 판단한다.
 *  @see 		NewLinearAccelation \n
 *  			DestroyLinearAccelation \n
 *  			addLinearAccelationCallback \n
 *  			detachLinearAccelationCallback \n
 *  			LinearAccelationOn \n
 *  			LinearAccelationOff \n
 *  			getLinearAccelationValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.linear_acceleration
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.linear_acceleration
 */
LinearAcceleration_data getLinearAccelationValue (LinearAccelation this_gen);
/* LinearAccelation */


/* Magnetometer */
/*! @struct	_Magnetometer
 *  @brief	Magnetometer 모듈에 대한 구조체이다. Magnetometer 모듈은 Magnetometer Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Magnetometer 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewMagnetometer() 함수를 사용해야 하며 사용이 끝났을 때 DestroyMagnetometer() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Sensor part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html)
 *  @pre	@b feature \n
 *          * http://tizen.org/feature/sensor.magnetometer
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
 *  @pre     	@b feature \n
 *              * http://tizen.org/feature/sensor.magnetometer
 *  @warning    사용이 끝났을 때 DestroyMagnetometer() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
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
 *	@endcode
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.magnetometer
 */
void DestroyMagnetometer (Magnetometer this_gen);

/*!	@fn			bool addMagnetometerCallback (Magnetometer this_gen, sensor_callback sensorCallback, int timeenterval, void * data)
 *  @brief 		생성한 Magnetometer에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Magnetometer 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	timeinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data 주소
 *  @param[out] data callback 함수에 전달될 사용자 data
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Magnetometer에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewMagnetometer \n
 *  			DestroyMagnetometer \n
 *  			detachMagnetometerCallback \n
 *  			MagnetometerOn \n
 *  			MagnetometerOff \n
 *  			isMagnetometerSupported \n
 *  			getMagnetometerValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.magnetometer
 */
bool addMagnetometerCallback (Magnetometer this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			bool detachMagnetometerCallback (Magnetometer this_gen)
 *  @brief 		생성한 Magnetometer에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Magnetometer 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Magnetometer에서 callback 함수를 삭제한다. \n
 *  @see 		NewMagnetometer \n
 *  			DestroyMagnetometer \n
 *  			addMagnetometerCallback \n
 *  			MagnetometerOn \n
 *  			MagnetometerOff \n
 *  			isMagnetometerSupported \n
 *  			getMagnetometerValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.magnetometer
 */
bool detachMagnetometerCallback (Magnetometer this_gen);

/*!	@fn			bool MagnetometerOn (Magnetometer this_gen)
 *  @brief 		생성한 Magnetometer를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Magnetometer 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Magnetometer를 활성화 시킨다.
 *  @see 		NewMagnetometer \n
 *  			DestroyMagnetometer \n
 *  			addMagnetometerCallback \n
 *  			detachMagnetometerCallback \n
 *  			MagnetometerOff \n
 *  			isMagnetometerSupported \n
 *  			getMagnetometerValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.magnetometer
 */
bool MagnetometerOn (Magnetometer this_gen);

/*!	@fn			bool MagnetometerOff (Magnetometer this_gen)
 *  @brief 		생성한 Magnetometer를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Magnetometer 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Magnetometer를 비활성화 시킨다.
 *  @see 		NewMagnetometer \n
 *  			DestroyMagnetometer \n
 *  			addMagnetometerCallback \n
 *  			detachMagnetometerCallback \n
 *  			MagnetometerOn \n
 *  			isMagnetometerSupported \n
 *  			getMagnetometerValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.magnetometer
 */
bool MagnetometerOff (Magnetometer this_gen);

/*!	@fn			bool isMagnetometerSupported (Magnetometer this_gen)
 *  @brief 		Magnetometer의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Magnetometer 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Magnetometer의 사용 가능 여부를 판단한다.
 *  @see 		NewMagnetometer \n
 *  			DestroyMagnetometer \n
 *  			addMagnetometerCallback \n
 *  			detachMagnetometerCallback \n
 *  			MagnetometerOn \n
 *  			MagnetometerOff \n
 *  			getMagnetometerValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.magnetometer
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.magnetometer
 */
Magnetometer_data getMagnetometerValue (Magnetometer this_gen);
/* Magnetometer */


/* RotationVector */
/*! @struct	_RotationVector
 *  @brief	RotationVector 모듈에 대한 구조체이다. RotationVector 모듈은 RotationVector Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	RotationVector 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewRotationVector() 함수를 사용해야 하며 사용이 끝났을 때 DestroyRotationVector() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Sensor part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html)
 *  @pre	@b feature \n
 *          * http://tizen.org/feature/sensor.rotation_vector
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
 *  @pre     	@b feature \n
 *              * http://tizen.org/feature/sensor.rotation_vector
 *  @warning    사용이 끝났을 때 DestroyRotationVector() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
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
 *	@endcode
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.rotation_vector
 */
void DestroyRotationVector (RotationVector this_gen);

/*!	@fn			bool addRotationVectorCallback (RotationVector this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 RotationVector에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 RotationVector 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	timeinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data 주소
 *  @param[out] data callback 함수에 전달될 사용자 data
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 RotationVector에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewRotationVector \n
 *  			DestroyRotationVector \n
 *  			detachRotationVectorCallback \n
 *  			RotationVectorOn \n
 *  			RotationVectorOff \n
 *  			isRotationVectorSupported \n
 *  			getRotationVectorValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.rotation_vector
 */
bool addRotationVectorCallback (RotationVector this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			bool detachRotationVectorCallback (RotationVector this_gen)
 *  @brief 		생성한 RotationVector에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 RotationVector 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 RotationVector에서 callback 함수를 삭제한다. \n
 *  @see 		NewRotationVector \n
 *  			DestroyRotationVector \n
 *  			addRotationVectorCallback \n
 *  			RotationVectorOn \n
 *  			RotationVectorOff \n
 *  			isRotationVectorSupported \n
 *  			getRotationVectorValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.rotation_vector
 */
bool detachRotationVectorCallback (RotationVector this_gen);

/*!	@fn			bool RotationVectorOn (RotationVector this_gen)
 *  @brief 		생성한 RotationVector를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 RotationVector 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 RotationVector를 활성화 시킨다.
 *  @see 		NewRotationVector \n
 *  			DestroyRotationVector \n
 *  			addRotationVectorCallback \n
 *  			detachRotationVectorCallback \n
 *  			RotationVectorOff \n
 *  			isRotationVectorSupported \n
 *  			getRotationVectorValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.rotation_vector
 */
bool RotationVectorOn (RotationVector this_gen);

/*!	@fn			bool RotationVectorOff (RotationVector this_gen)
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.rotation_vector
 */
bool RotationVectorOff (RotationVector this_gen);

/*!	@fn			bool isRotationVectorSupported (RotationVector this_gen)
 *  @brief 		RotationVector의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 RotationVector 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		RotationVector의 사용 가능 여부를 판단한다.
 *  @see 		NewRotationVector \n
 *  			DestroyRotationVector \n
 *  			addRotationVectorCallback \n
 *  			detachRotationVectorCallback \n
 *  			RotationVectorOn \n
 *  			RotationVectorOff \n
 *  			getRotationVectorValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.rotation_vector
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.rotation_vector
 */
RotationVector_data getRotationVectorValue (RotationVector this_gen);
/* RotationVector */


/* Orientation */
/*! @struct	_Orientation
 *  @brief	Orientation 모듈에 대한 구조체이다. Orientation 모듈은 Orientation Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Orientation 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewOrientation() 함수를 사용해야 하며 사용이 끝났을 때 DestroyOrientation() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Sensor part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html)
 *  @pre	@b feature \n
 *          * http://tizen.org/feature/sensor.accelerometer \n
 *          * http://tizen.org/feature/sensor.magnetometer
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
 *  @pre     	@b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer \n
 *				* http://tizen.org/feature/sensor.magnetometer
 *  @warning    사용이 끝났을 때 DestroyOrientation() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
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
 *	@endcode
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer \n
 *              * http://tizen.org/feature/sensor.magnetometer
 */
void DestroyOrientation (Orientation this_gen);

/*!	@fn			bool addOrientationCallback (Orientation this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Orientation에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Orientation 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	voiceinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data 주소
 *  @param[out] data callback 함수에 전달될 사용자 data
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Orientation에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewOrientation \n
 *  			DestroyOrientation \n
 *  			detachOrientationCallback \n
 *  			OrientationOn \n
 *  			OrientationOff \n
 *  			isOrientationSupported \n
 *  			getOrientationValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer \n
 *              * http://tizen.org/feature/sensor.magnetometer
 */
bool addOrientationCallback (Orientation this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			bool detachOrientationCallback (Orientation this_gen)
 *  @brief 		생성한 Orientation에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Orientation 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Orientation에서 callback 함수를 삭제한다. \n
 *  @see 		NewOrientation \n
 *  			DestroyOrientation \n
 *  			addOrientationCallback \n
 *  			OrientationOn \n
 *  			OrientationOff \n
 *  			isOrientationSupported \n
 *  			getOrientationValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer \n
 *              * http://tizen.org/feature/sensor.magnetometer
 */
bool detachOrientationCallback (Orientation this_gen);

/*!	@fn			bool OrientationOn (Orientation this_gen)
 *  @brief 		생성한 Orientation를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Orientation 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Orientation를 활성화 시킨다.
 *  @see 		NewOrientation \n
 *  			DestroyOrientation \n
 *  			addOrientationCallback \n
 *  			detachOrientationCallback \n
 *  			OrientationOff \n
 *  			isOrientationSupported \n
 *  			getOrientationValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer \n
 *              * http://tizen.org/feature/sensor.magnetometer
 */
bool OrientationOn (Orientation this_gen);

/*!	@fn			bool OrientationOff (Orientation this_gen)
 *  @brief 		생성한 Orientation를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Orientation 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Orientation를 비활성화 시킨다.
 *  @see 		NewOrientation \n
 *  			DestroyOrientation \n
 *  			addOrientationCallback \n
 *  			detachOrientationCallback \n
 *  			OrientationOn \n
 *  			isOrientationSupported \n
 *  			getOrientationValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer \n
 *              * http://tizen.org/feature/sensor.magnetometer
 */
bool OrientationOff (Orientation this_gen);

/*!	@fn			bool isOrientationSupported (Orientation this_gen)
 *  @brief 		Orientation의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Orientation 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Orientation의 사용 가능 여부를 판단한다.
 *  @see 		NewOrientation \n
 *  			DestroyOrientation \n
 *  			addOrientationCallback \n
 *  			detachOrientationCallback \n
 *  			OrientationOn \n
 *  			OrientationOff \n
 *  			getOrientationValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer \n
 *              * http://tizen.org/feature/sensor.magnetometer
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer \n
 *              * http://tizen.org/feature/sensor.magnetometer
 */
Orientation_data getOrientationValue (Orientation this_gen);
/* Orientation */


/* Gyroscope */
/*! @struct	_Gyroscope
 *  @brief	Gyroscope 모듈에 대한 구조체이다. Gyroscope 모듈은 Gyroscope Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Gyroscope 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewGyroscope() 함수를 사용해야 하며 사용이 끝났을 때 DestroyGyroscope() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Sensor part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html)
 *  @pre	@b feature \n
 *          * http://tizen.org/feature/sensor.gyroscope
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
 *  @pre     	@b feature \n
 *              http://tizen.org/feature/sensor.gyroscope
 *  @warning    사용이 끝났을 때 DestroyGyroscope() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
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
 *	@endcode
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
 *  @pre        @b feature \n
 *              http://tizen.org/feature/sensor.gyroscope
 */
void DestroyGyroscope (Gyroscope this_gen);

/*!	@fn			bool addGyroscopeCallback (Gyroscope this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Gyroscope에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Gyroscope 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	voiceinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data 주소
 *  @param[out] data callback 함수에 전달될 사용자 data
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Gyroscope에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewGyroscope \n
 *  			DestroyGyroscope \n
 *  			detachGyroscopeCallback \n
 *  			GyroscopeOn \n
 *  			GyroscopeOff \n
 *  			isGyroscopeSupported \n
 *  			getGyroscopeValue
 *  @pre        @b feature \n
 *              http://tizen.org/feature/sensor.gyroscope
 */
bool addGyroscopeCallback (Gyroscope this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			bool detachGyroscopeCallback (Gyroscope this_gen)
 *  @brief 		생성한 Gyroscope에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Gyroscope 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Gyroscope에서 callback 함수를 삭제한다. \n
 *  @see 		NewGyroscope \n
 *  			DestroyGyroscope \n
 *  			addGyroscopeCallback \n
 *  			GyroscopeOn \n
 *  			GyroscopeOff \n
 *  			isGyroscopeSupported \n
 *  			getGyroscopeValue
 *  @pre        @b feature \n
 *              http://tizen.org/feature/sensor.gyroscope
 */
bool detachGyroscopeCallback (Gyroscope this_gen);

/*!	@fn			bool GyroscopeOn (Gyroscope this_gen)
 *  @brief 		생성한 Gyroscope를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Gyroscope 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Gyroscope를 활성화 시킨다.
 *  @see 		NewGyroscope \n
 *  			DestroyGyroscope \n
 *  			addGyroscopeCallback \n
 *  			detachGyroscopeCallback \n
 *  			GyroscopeOff \n
 *  			isGyroscopeSupported \n
 *  			getGyroscopeValue
 *  @pre        @b feature \n
 *              http://tizen.org/feature/sensor.gyroscope
 */
bool GyroscopeOn (Gyroscope this_gen);

/*!	@fn			bool GyroscopeOff (Gyroscope this_gen)
 *  @brief 		생성한 Gyroscope를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Gyroscope 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Gyroscope를 비활성화 시킨다.
 *  @see 		NewGyroscope \n
 *  			DestroyGyroscope \n
 *  			addGyroscopeCallback \n
 *  			detachGyroscopeCallback \n
 *  			GyroscopeOn \n
 *  			isGyroscopeSupported \n
 *  			getGyroscopeValue
 *  @pre        @b feature \n
 *              http://tizen.org/feature/sensor.gyroscope
 */
bool GyroscopeOff (Gyroscope this_gen);

/*!	@fn			bool isGyroscopeSupported (Gyroscope this_gen)
 *  @brief 		Gyroscope의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Gyroscope 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Gyroscope의 사용 가능 여부를 판단한다.
 *  @see 		NewGyroscope \n
 *  			DestroyGyroscope \n
 *  			addGyroscopeCallback \n
 *  			detachGyroscopeCallback \n
 *  			GyroscopeOn \n
 *  			GyroscopeOff \n
 *  			getGyroscopeValue
 *  @pre        @b feature \n
 *              http://tizen.org/feature/sensor.gyroscope
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
 *  @pre        @b feature \n
 *              http://tizen.org/feature/sensor.gyroscope
 */
Gyroscope_data getGyroscopeValue (Gyroscope this_gen);
/* Gyroscope */


/* Light */
/*! @struct	_Light
 *  @brief	Light 모듈에 대한 구조체이다. Light 모듈은 Photometer Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Light 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewLight() 함수를 사용해야 하며 사용이 끝났을 때 DestroyLight() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Sensor part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html)
 *  @pre	@b feature \n
 *          * http://tizen.org/feature/sensor.photometer
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
 *  @pre     	@b feature \n
 *              * http://tizen.org/feature/sensor.photometer
 *  @warning    사용이 끝났을 때 DestroyLight() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
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
 *	@endcode
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.photometer
 */
void DestroyLight (Light this_gen);

/*!	@fn			bool addLightCallback (Light this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Light에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Light 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	voiceinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data 주소
 *  @param[out] data callback 함수에 전달될 사용자 data
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Light에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewLight \n
 *  			DestroyLight \n
 *  			detachLightCallback \n
 *  			LightOn \n
 *  			LightOff \n
 *  			isLightSupported \n
 *  			getLightValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.photometer
 */
bool addLightCallback (Light this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			bool detachLightCallback (Light this_gen)
 *  @brief 		생성한 Light에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Light 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Light에서 callback 함수를 삭제한다. \n
 *  @see 		NewLight \n
 *  			DestroyLight \n
 *  			addLightCallback \n
 *  			LightOn \n
 *  			LightOff \n
 *  			isLightSupported \n
 *  			getLightValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.photometer
 */
bool detachLightCallback (Light this_gen);

/*!	@fn			bool LightOn (Light this_gen)
 *  @brief 		생성한 Light를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Light 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Light를 활성화 시킨다.
 *  @see 		NewLight \n
 *  			DestroyLight \n
 *  			addLightCallback \n
 *  			detachLightCallback \n
 *  			LightOff \n
 *  			isLightSupported \n
 *  			getLightValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.photometer
 */
bool LightOn (Light this_gen);

/*!	@fn			bool LightOff (Light this_gen)
 *  @brief 		생성한 Light를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Light 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Light를 비활성화 시킨다.
 *  @see 		NewLight \n
 *  			DestroyLight \n
 *  			addLightCallback \n
 *  			detachLightCallback \n
 *  			LightOn \n
 *  			isLightSupported \n
 *  			getLightValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.photometer
 */
bool LightOff (Light this_gen);

/*!	@fn			bool isLightSupported (Light this_gen)
 *  @brief 		Light의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Light 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Light의 사용 가능 여부를 판단한다.
 *  @see 		NewLight \n
 *  			DestroyLight \n
 *  			addLightCallback \n
 *  			detachLightCallback \n
 *  			LightOn \n
 *  			LightOff \n
 *  			getLightValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.photometer
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.photometer
 */
Light_data getLightValue (Light this_gen);

/* Light */


/* Proximity */
/*! @struct	_Proximity
 *  @brief	Proximity 모듈에 대한 구조체이다. Proximity 모듈은 Proximity Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Proximity 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewProximity() 함수를 사용해야 하며 사용이 끝났을 때 DestroyProximity() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Sensor part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html)
 *  @pre	@b feature \n
 *          * http://tizen.org/feature/sensor.proximity
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
 *  @pre     	@b feature \n
 *              * http://tizen.org/feature/sensor.proximity
 *  @warning    사용이 끝났을 때 DestroyProximity() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
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
 *	@endcode
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.proximity
 */
void DestroyProximity (Proximity this_gen);

/*!	@fn			bool addProximityCallback (Proximity this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Proximity에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Proximity 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	voiceinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data 주소
 *  @param[out] data callback 함수에 전달될 사용자 data
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Proximity에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewProximity \n
 *  			DestroyProximity \n
 *  			detachProximityCallback \n
 *  			ProximityOn \n
 *  			ProximityOff \n
 *  			isProximitySupported \n
 *  			getProximityValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.proximity
 */
bool addProximityCallback (Proximity this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			bool detachProximityCallback (Proximity this_gen)
 *  @brief 		생성한 Proximity에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Proximity 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Proximity에서 callback 함수를 삭제한다. \n
 *  @see 		NewProximity \n
 *  			DestroyProximity \n
 *  			addProximityCallback \n
 *  			ProximityOn \n
 *  			ProximityOff \n
 *  			isProximitySupported \n
 *  			getProximityValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.proximity
 */
bool detachProximityCallback (Proximity this_gen);

/*!	@fn			bool ProximityOn (Proximity this_gen)
 *  @brief 		생성한 Proximity를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Proximity 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Proximity를 활성화 시킨다.
 *  @see 		NewProximity \n
 *  			DestroyProximity \n
 *  			addProximityCallback \n
 *  			detachProximityCallback \n
 *  			ProximityOff \n
 *  			isProximitySupported \n
 *  			getProximityValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.proximity
 */
bool ProximityOn (Proximity this_gen);

/*!	@fn			bool ProximityOff (Proximity this_gen)
 *  @brief 		생성한 Proximity를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Proximity 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Proximity를 비활성화 시킨다.
 *  @see 		NewProximity \n
 *  			DestroyProximity \n
 *  			addProximityCallback \n
 *  			detachProximityCallback \n
 *  			ProximityOn \n
 *  			isProximitySupported \n
 *  			getProximityValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.proximity
 */
bool ProximityOff (Proximity this_gen);

/*!	@fn			bool isProximitySupported (Proximity this_gen)
 *  @brief 		Proximity의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Proximity 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Proximity의 사용 가능 여부를 판단한다.
 *  @see 		NewProximity \n
 *  			DestroyProximity \n
 *  			addProximityCallback \n
 *  			detachProximityCallback \n
 *  			ProximityOn \n
 *  			ProximityOff \n
 *  			getProximityValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.proximity
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.proximity
 */
Proximity_data getProximityValue (Proximity this_gen);
/* Proximity */


/* Pressure */
/*! @struct	_Pressure
 *  @brief	Pressure 모듈에 대한 구조체이다. Pressure 모듈은 Pressure Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Pressure 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewPressure() 함수를 사용해야 하며 사용이 끝났을 때 DestroyPressure() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Sensor part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html)
 *  @pre	@b feature \n
 *          * http://tizen.org/feature/sensor.accelerometer \n
 *          * http://tizen.org/feature/sensor.barometer \n
 *          * http://tizen.org/feature/sensor.gyroscope \n
 *          * http://tizen.org/feature/sensor.magnetometer \n
 *          * http://tizen.org/feature/sensor.photometer \n
 *          * http://tizen.org/feature/sensor.proximity \n
 *          * http://tizen.org/feature/sensor.tiltmeter \n
 *          * http://tizen.org/feature/sensor.ultraviolet \n
 *          * http://tizen.org/feature/sensor.temperature \n
 *          * http://tizen.org/feature/sensor.humidity \n
 *          * http://tizen.org/feature/sensor.linear_acceleration \n
 *          * http://tizen.org/feature/sensor.rotation_vector \n
 *          * http://tizen.org/feature/sensor.gravity
 *  @warning    Pressure Sensor의 경우 device에 있는 다양한 센서들을 조합해서 사용하므로 모든 Sensor를 추가해야 한다.
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer \n
 *              * http://tizen.org/feature/sensor.barometer \n
 *              * http://tizen.org/feature/sensor.gyroscope \n
 *              * http://tizen.org/feature/sensor.magnetometer \n
 *              * http://tizen.org/feature/sensor.photometer \n
 *              * http://tizen.org/feature/sensor.proximity \n
 *              * http://tizen.org/feature/sensor.tiltmeter \n
 *              * http://tizen.org/feature/sensor.ultraviolet \n
 *              * http://tizen.org/feature/sensor.temperature \n
 *              * http://tizen.org/feature/sensor.humidity \n
 *              * http://tizen.org/feature/sensor.linear_acceleration \n
 *              * http://tizen.org/feature/sensor.rotation_vector \n
 *              * http://tizen.org/feature/sensor.gravity
 *  @warning    사용이 끝났을 때 DestroyPressure() 함수를 꼭 사용해야 한다. \n
 *              Pressure Sensor의 경우 device에 있는 다양한 센서들을 조합해서 사용하므로 모든 Sensor를 추가해야 한다.
 *
 *  @code{.c}
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
 *	@endcode
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer \n
 *              * http://tizen.org/feature/sensor.barometer \n
 *              * http://tizen.org/feature/sensor.gyroscope \n
 *              * http://tizen.org/feature/sensor.magnetometer \n
 *              * http://tizen.org/feature/sensor.photometer \n
 *              * http://tizen.org/feature/sensor.proximity \n
 *              * http://tizen.org/feature/sensor.tiltmeter \n
 *              * http://tizen.org/feature/sensor.ultraviolet \n
 *              * http://tizen.org/feature/sensor.temperature \n
 *              * http://tizen.org/feature/sensor.humidity \n
 *              * http://tizen.org/feature/sensor.linear_acceleration \n
 *              * http://tizen.org/feature/sensor.rotation_vector \n
 *              * http://tizen.org/feature/sensor.gravity
 */
void DestroyPressure (Pressure this_gen);

/*!	@fn			bool addPressureCallback (Pressure this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Pressure에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Pressure 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	voiceinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data 주소
 *  @param[out] data callback 함수에 전달될 사용자 data
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Pressure에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewPressure \n
 *  			DestroyPressure \n
 *  			detachPressureCallback \n
 *  			PressureOn \n
 *  			PressureOff \n
 *  			isPressureSupported \n
 *  			getPressureValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer \n
 *              * http://tizen.org/feature/sensor.barometer \n
 *              * http://tizen.org/feature/sensor.gyroscope \n
 *              * http://tizen.org/feature/sensor.magnetometer \n
 *              * http://tizen.org/feature/sensor.photometer \n
 *              * http://tizen.org/feature/sensor.proximity \n
 *              * http://tizen.org/feature/sensor.tiltmeter \n
 *              * http://tizen.org/feature/sensor.ultraviolet \n
 *              * http://tizen.org/feature/sensor.temperature \n
 *              * http://tizen.org/feature/sensor.humidity \n
 *              * http://tizen.org/feature/sensor.linear_acceleration \n
 *              * http://tizen.org/feature/sensor.rotation_vector \n
 *              * http://tizen.org/feature/sensor.gravity
 */
bool addPressureCallback (Pressure this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			bool detachPressureCallback (Pressure this_gen)
 *  @brief 		생성한 Pressure에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Pressure 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Pressure에서 callback 함수를 삭제한다. \n
 *  @see 		NewPressure \n
 *  			DestroyPressure \n
 *  			addPressureCallback \n
 *  			PressureOn \n
 *  			PressureOff \n
 *  			isPressureSupported \n
 *  			getPressureValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer \n
 *              * http://tizen.org/feature/sensor.barometer \n
 *              * http://tizen.org/feature/sensor.gyroscope \n
 *              * http://tizen.org/feature/sensor.magnetometer \n
 *              * http://tizen.org/feature/sensor.photometer \n
 *              * http://tizen.org/feature/sensor.proximity \n
 *              * http://tizen.org/feature/sensor.tiltmeter \n
 *              * http://tizen.org/feature/sensor.ultraviolet \n
 *              * http://tizen.org/feature/sensor.temperature \n
 *              * http://tizen.org/feature/sensor.humidity \n
 *              * http://tizen.org/feature/sensor.linear_acceleration \n
 *              * http://tizen.org/feature/sensor.rotation_vector \n
 *              * http://tizen.org/feature/sensor.gravity
 */
bool detachPressureCallback (Pressure this_gen);

/*!	@fn			bool PressureOn (Pressure this_gen)
 *  @brief 		생성한 Pressure를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Pressure 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Pressure를 활성화 시킨다.
 *  @see 		NewPressure \n
 *  			DestroyPressure \n
 *  			addPressureCallback \n
 *  			detachPressureCallback \n
 *  			PressureOff \n
 *  			isPressureSupported \n
 *  			getPressureValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer \n
 *              * http://tizen.org/feature/sensor.barometer \n
 *              * http://tizen.org/feature/sensor.gyroscope \n
 *              * http://tizen.org/feature/sensor.magnetometer \n
 *              * http://tizen.org/feature/sensor.photometer \n
 *              * http://tizen.org/feature/sensor.proximity \n
 *              * http://tizen.org/feature/sensor.tiltmeter \n
 *              * http://tizen.org/feature/sensor.ultraviolet \n
 *              * http://tizen.org/feature/sensor.temperature \n
 *              * http://tizen.org/feature/sensor.humidity \n
 *              * http://tizen.org/feature/sensor.linear_acceleration \n
 *              * http://tizen.org/feature/sensor.rotation_vector \n
 *              * http://tizen.org/feature/sensor.gravity
 */
bool PressureOn (Pressure this_gen);

/*!	@fn			bool PressureOff (Pressure this_gen)
 *  @brief 		생성한 Pressure를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Pressure 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Pressure를 비활성화 시킨다.
 *  @see 		NewPressure \n
 *  			DestroyPressure \n
 *  			addPressureCallback \n
 *  			detachPressureCallback \n
 *  			PressureOn \n
 *  			isPressureSupported \n
 *  			getPressureValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer \n
 *              * http://tizen.org/feature/sensor.barometer \n
 *              * http://tizen.org/feature/sensor.gyroscope \n
 *              * http://tizen.org/feature/sensor.magnetometer \n
 *              * http://tizen.org/feature/sensor.photometer \n
 *              * http://tizen.org/feature/sensor.proximity \n
 *              * http://tizen.org/feature/sensor.tiltmeter \n
 *              * http://tizen.org/feature/sensor.ultraviolet \n
 *              * http://tizen.org/feature/sensor.temperature \n
 *              * http://tizen.org/feature/sensor.humidity \n
 *              * http://tizen.org/feature/sensor.linear_acceleration \n
 *              * http://tizen.org/feature/sensor.rotation_vector \n
 *              * http://tizen.org/feature/sensor.gravity
 */
bool PressureOff (Pressure this_gen);

/*!	@fn			bool isPressureSupported (Pressure this_gen)
 *  @brief 		Pressure의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Pressure 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Pressure의 사용 가능 여부를 판단한다.
 *  @see 		NewPressure \n
 *  			DestroyPressure \n
 *  			addPressureCallback \n
 *  			detachPressureCallback \n
 *  			PressureOn \n
 *  			PressureOff \n
 *  			getPressureValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer \n
 *              * http://tizen.org/feature/sensor.barometer \n
 *              * http://tizen.org/feature/sensor.gyroscope \n
 *              * http://tizen.org/feature/sensor.magnetometer \n
 *              * http://tizen.org/feature/sensor.photometer \n
 *              * http://tizen.org/feature/sensor.proximity \n
 *              * http://tizen.org/feature/sensor.tiltmeter \n
 *              * http://tizen.org/feature/sensor.ultraviolet \n
 *              * http://tizen.org/feature/sensor.temperature \n
 *              * http://tizen.org/feature/sensor.humidity \n
 *              * http://tizen.org/feature/sensor.linear_acceleration \n
 *              * http://tizen.org/feature/sensor.rotation_vector \n
 *              * http://tizen.org/feature/sensor.gravity
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.accelerometer \n
 *              * http://tizen.org/feature/sensor.barometer \n
 *              * http://tizen.org/feature/sensor.gyroscope \n
 *              * http://tizen.org/feature/sensor.magnetometer \n
 *              * http://tizen.org/feature/sensor.photometer \n
 *              * http://tizen.org/feature/sensor.proximity \n
 *              * http://tizen.org/feature/sensor.tiltmeter \n
 *              * http://tizen.org/feature/sensor.ultraviolet \n
 *              * http://tizen.org/feature/sensor.temperature \n
 *              * http://tizen.org/feature/sensor.humidity \n
 *              * http://tizen.org/feature/sensor.linear_acceleration \n
 *              * http://tizen.org/feature/sensor.rotation_vector \n
 *              * http://tizen.org/feature/sensor.gravity
 */
Pressure_data getPressureValue (Pressure this_gen);
/* Pressure */


/* UltraViolet */
/*! @struct	_UltraViolet
 *  @brief	UltraViolet 모듈에 대한 구조체이다. UltraViolet 모듈은 UltraViolet Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	UltraViolet 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewUltraViolet() 함수를 사용해야 하며 사용이 끝났을 때 DestroyUltraViolet() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Sensor part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html)
 *  @pre	@b feature \n
 *          * http://tizen.org/feature/sensor.ultraviolet
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
 *  @pre     	@b feature \n
 *              * http://tizen.org/feature/sensor.ultraviolet
 *  @warning    사용이 끝났을 때 DestroyUltraViolet() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
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
 *	@endcode
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.ultraviolet
 */
void DestroyUltraViolet (UltraViolet this_gen);

/*!	@fn			bool addUltraVioletCallback (UltraViolet this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 UltraViolet에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 UltraViolet 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	voiceinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data 주소
 *  @param[out] data callback 함수에 전달될 사용자 data
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 UltraViolet에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewUltraViolet \n
 *  			DestroyUltraViolet \n
 *  			detachUltraVioletCallback \n
 *  			UltraVioletOn \n
 *  			UltraVioletOff \n
 *  			isUltraVioletSupported \n
 *  			getUltraVioletValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.ultraviolet
 */
bool addUltraVioletCallback (UltraViolet this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			bool detachUltraVioletCallback (UltraViolet this_gen)
 *  @brief 		생성한 UltraViolet에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 UltraViolet 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 UltraViolet에서 callback 함수를 삭제한다. \n
 *  @see 		NewUltraViolet \n
 *  			DestroyUltraViolet \n
 *  			addUltraVioletCallback \n
 *  			UltraVioletOn \n
 *  			UltraVioletOff \n
 *  			isUltraVioletSupported \n
 *  			getUltraVioletValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.ultraviolet
 */
bool detachUltraVioletCallback (UltraViolet this_gen);

/*!	@fn			bool UltraVioletOn (UltraViolet this_gen)
 *  @brief 		생성한 UltraViolet를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 UltraViolet 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 UltraViolet를 활성화 시킨다.
 *  @see 		NewUltraViolet \n
 *  			DestroyUltraViolet \n
 *  			addUltraVioletCallback \n
 *  			detachUltraVioletCallback \n
 *  			UltraVioletOff \n
 *  			isUltraVioletSupported \n
 *  			getUltraVioletValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.ultraviolet
 */
bool UltraVioletOn (UltraViolet this_gen);

/*!	@fn			bool UltraVioletOff (UltraViolet this_gen)
 *  @brief 		생성한 UltraViolet를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 UltraViolet 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 UltraViolet를 비활성화 시킨다.
 *  @see 		NewUltraViolet \n
 *  			DestroyUltraViolet \n
 *  			addUltraVioletCallback \n
 *  			detachUltraVioletCallback \n
 *  			UltraVioletOn \n
 *  			isUltraVioletSupported \n
 *  			getUltraVioletValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.ultraviolet
 */
bool UltraVioletOff (UltraViolet this_gen);

/*!	@fn			bool isUltraVioletSupported (UltraViolet this_gen)
 *  @brief 		UltraViolet의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 UltraViolet 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		UltraViolet의 사용 가능 여부를 판단한다.
 *  @see 		NewUltraViolet \n
 *  			DestroyUltraViolet \n
 *  			addUltraVioletCallback \n
 *  			detachUltraVioletCallback \n
 *  			UltraVioletOn \n
 *  			UltraVioletOff \n
 *  			getUltraVioletValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.ultraviolet
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.ultraviolet
 */
UltraViolet_data getUltraVioletValue (UltraViolet this_gen);
/* UltraViolet */


/* Temperature */
/*! @struct	_Temperature
 *  @brief	Temperature 모듈에 대한 구조체이다. Temperature 모듈은 Temperature Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Temperature 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewTemperature() 함수를 사용해야 하며 사용이 끝났을 때 DestroyTemperature() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Sensor part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html)
 *  @pre	@b feature \n
 *          * http://tizen.org/feature/sensor.temperature
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
 *  @pre     	@b feature \n
 *              * http://tizen.org/feature/sensor.temperature
 *  @warning    사용이 끝났을 때 DestroyTemperature() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
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
 *	@endcode
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.temperature
 */
void DestroyTemperature (Temperature this_gen);

/*!	@fn			bool addTemperatureCallback (Temperature this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Temperature에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Temperature 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	voiceinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data 주소
 *  @param[out] data callback 함수에 전달될 사용자 data
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Temperature에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewTemperature \n
 *  			DestroyTemperature \n
 *  			detachTemperatureCallback \n
 *  			TemperatureOn \n
 *  			TemperatureOff \n
 *  			isTemperatureSupported \n
 *  			getTemperatureValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.temperature
 */
bool addTemperatureCallback (Temperature this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			bool detachTemperatureCallback (Temperature this_gen)
 *  @brief 		생성한 Temperature에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Temperature 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Temperature에서 callback 함수를 삭제한다. \n
 *  @see 		NewTemperature \n
 *  			DestroyTemperature \n
 *  			addTemperatureCallback \n
 *  			TemperatureOn \n
 *  			TemperatureOff \n
 *  			isTemperatureSupported \n
 *  			getTemperatureValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.temperature
 */
bool detachTemperatureCallback (Temperature this_gen);

/*!	@fn			bool TemperatureOn (Temperature this_gen)
 *  @brief 		생성한 Temperature를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Temperature 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Temperature를 활성화 시킨다.
 *  @see 		NewTemperature \n
 *  			DestroyTemperature \n
 *  			addTemperatureCallback \n
 *  			detachTemperatureCallback \n
 *  			TemperatureOff \n
 *  			isTemperatureSupported \n
 *  			getTemperatureValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.temperature
 */
bool TemperatureOn (Temperature this_gen);

/*!	@fn			bool TemperatureOff (Temperature this_gen)
 *  @brief 		생성한 Temperature를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Temperature 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Temperature를 비활성화 시킨다.
 *  @see 		NewTemperature \n
 *  			DestroyTemperature \n
 *  			addTemperatureCallback \n
 *  			detachTemperatureCallback \n
 *  			TemperatureOn \n
 *  			isTemperatureSupported \n
 *  			getTemperatureValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.temperature
 */
bool TemperatureOff (Temperature this_gen);

/*!	@fn			bool isTemperatureSupported (Temperature this_gen)
 *  @brief 		Temperature의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Temperature 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Temperature의 사용 가능 여부를 판단한다.
 *  @see 		NewTemperature \n
 *  			DestroyTemperature \n
 *  			addTemperatureCallback \n
 *  			detachTemperatureCallback \n
 *  			TemperatureOn \n
 *  			TemperatureOff \n
 *  			getTemperatureValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.temperature
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.temperature
 */
Temperature_data getTemperatureValue (Temperature this_gen);
/* Temperature */


/* Humidity */
/*! @struct	_Humidity
 *  @brief	Humidity 모듈에 대한 구조체이다. Humidity 모듈은 Humidity Sensor를 다양한 방식으로 제어할 수 있다.
 *  @note	Humidity 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewHumidity() 함수를 사용해야 하며 사용이 끝났을 때 DestroyHumidity() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Sensor part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__SENSOR__MODULE.html)
 *  @pre	@b feature \n
 *          * http://tizen.org/feature/sensor.humidity
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
 *  @pre     	@b feature \n
 *              * http://tizen.org/feature/sensor.humidity
 *  @warning    사용이 끝났을 때 DestroyHumidity() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
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
 *	@endcode
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.humidity
 */
void DestroyHumidity (Humidity this_gen);

/*!	@fn			bool addHumidityCallback (Humidity this_gen, sensor_callback sensorCallback, int timeinterval, void * data)
 *  @brief 		생성한 Humidity에 callback 함수를 등록한다.
 *  @param[in] 	this_gen callback 함수를 등록할 Humidity 객체
 *  @param[in] 	sensor callback 등록할 callback 함수
 *  @param[in] 	voiceinterval callback 함수가 수행될 시간 간격
 *  @param[in] 	data callback 함수에 전달될 사용자 data 주소
 *  @param[out] data callback 함수에 전달될 사용자 data
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Humidity에 callback 함수를 등록한다. \n
 *  			@a interval 의 단위는 milliseconds 이며 만약 @c 0 으로 설정하면 기본 값인 100ms로 설정된다.
 *  @see 		NewHumidity \n
 *  			DestroyHumidity \n
 *  			detachHumidityCallback \n
 *  			HumidityOn \n
 *  			HumidityOff \n
 *  			isHumiditySupported \n
 *  			getHumidityValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.humidity
 */
bool addHumidityCallback (Humidity this_gen, sensor_callback sensorCallback, int timeinterval, void * data);

/*!	@fn			bool detachHumidityCallback (Humidity this_gen)
 *  @brief 		생성한 Humidity에서 callback 함수를 삭제한다.
 *  @param[in] 	this_gen callback 함수를 삭제할 Humidity 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Humidity에서 callback 함수를 삭제한다. \n
 *  @see 		NewHumidity \n
 *  			DestroyHumidity \n
 *  			addHumidityCallback \n
 *  			HumidityOn \n
 *  			HumidityOff \n
 *  			isHumiditySupported \n
 *  			getHumidityValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.humidity
 */
bool detachHumidityCallback (Humidity this_gen);

/*!	@fn			bool HumidityOn (Humidity this_gen)
 *  @brief 		생성한 Humidity를 활성화 시킨다.
 *  @param[in] 	this_gen 활성화 시킬 Humidity 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Humidity를 활성화 시킨다.
 *  @see 		NewHumidity \n
 *  			DestroyHumidity \n
 *  			addHumidityCallback \n
 *  			detachHumidityCallback \n
 *  			HumidityOff \n
 *  			isHumiditySupported \n
 *  			getHumidityValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.humidity
 */
bool HumidityOn (Humidity this_gen);

/*!	@fn			bool HumidityOff (Humidity this_gen)
 *  @brief 		생성한 Humidity를 비활성화 시킨다.
 *  @param[in] 	this_gen 비활성화 시킬 Humidity 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		생성한 Humidity를 비활성화 시킨다.
 *  @see 		NewHumidity \n
 *  			DestroyHumidity \n
 *  			addHumidityCallback \n
 *  			detachHumidityCallback \n
 *  			HumidityOn \n
 *  			isHumiditySupported \n
 *  			getHumidityValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.humidity
 */
bool HumidityOff (Humidity this_gen);

/*!	@fn			bool isHumiditySupported (Humidity this_gen)
 *  @brief 		Humidity의 사용 가능 여부를 판단한다.
 *  @param[in] 	this_gen 사용 가능 여부를 판단할 Humidity 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Humidity의 사용 가능 여부를 판단한다.
 *  @see 		NewHumidity \n
 *  			DestroyHumidity \n
 *  			addHumidityCallback \n
 *  			detachHumidityCallback \n
 *  			HumidityOn \n
 *  			HumidityOff \n
 *  			getHumidityValue
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.humidity
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
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/sensor.humidity
 */
Humidity_data getHumidityValue (Humidity this_gen);
/* Humidity */

#ifdef __cplusplus
}
#endif

#endif //DIT_SENSOR_H
