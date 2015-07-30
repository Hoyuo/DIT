/*! @file	DeviceStatus.h
 *  @brief	Device Status API 를 사용하기 위해 포함해야 하는 헤더이다.
 *  @note	Device의 Vibration / Display / Battery / Flash 관련 API를 제공한다.
 *  @see    [Tizen Native API](https://developer.tizen.org/development/api-references/native-application?redirect=https%3A//developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/index.html)
 */

#ifndef DIT_DEVICESTATUS_H
#define DIT_DEVICESTATUS_H

#include <stdbool.h>
#include <stdalign.h>

#include "dit.h"

#include <device/display.h>
#include <device/haptic.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! @fn 		const char * DeviceStatusErrorCheck (int errCode)
 *  @brief 		Device Status API에서 발생하는 Error Code들을 확인 해준다.
 *  @param[in] 	errCode 확인 하고자 하는 Error Code
 *  @param[out]	null
 *  @retval     DEVICE_ERROR_NONE                : Successful
 *  @retval     DEVICE_ERROR_OPERATION_FAILED    : Operation not permitted
 *  @retval     DEVICE_ERROR_PERMISSION_DENIED   : Permission denied
 *  @retval     DEVICE_ERROR_INVALID_PARAMETER   : Invalid parameter
 *  @retval     DEVICE_ERROR_ALREADY_IN_PROGRESS : Operation already in progress
 *  @retval     DEVICE_ERROR_NOT_SUPPORTED       : Not supported in this device
 *  @retval     DEVICE_ERROR_NOT_INITIALIZED     : Not initialized
 *  @retval     DEVICE_ERROR_UNKNOWN             : Unknown error occurred  
 *  @note 		Device Status API에서 발생하는 Error Code들을 확인 해준다. \n
 *              Error의 내용은 Log를 통해 출력 된다.    \n
 *  			8가지의 Error Code들을 확인 가능 하다.
 *  @see 		[Tizen Native API Document - Device Error](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__DEVICE__MODULE.html)
 */
const char * DeviceStatusErrorCheck (int errCode);

/* Vibration */
/*! @struct	_Vibration
 *  @brief	Vibration 모듈에 대한 구조체이다. Vibration 모듈은 다양한 방식으로 진동을 조절 할 수 있다.
 *  @note	Device Status의 Vibration 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewVibration() 함수를 사용해야 하며 사용이 끝났을 때 DestroyVibration() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Vibration part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__DEVICE__HAPTIC__MODULE.html)
 *  @pre	@b privilege \n 
 *          * http://tizen.org/privilege/haptic
 */
typedef struct _Vibration * Vibration;
struct _Vibration
{

    bool (* Custom) (Vibration this_gen, int period);

    bool (* Short) (Vibration this_gen);

    bool (* Middle) (Vibration this_gen);

    bool (* Long) (Vibration this_gen);
};

/*!	@fn			Vibration NewVibration (void)
 *  @brief		새로운 Vibration 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Vibration
 *  @note 		새로운 Vibration 객체를 생성한다. \n
 *  			Vibration 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyVibration \n
 *  			VibrationCustom \n
 *  			VibrationShort \n
 *  			VibrationMiddle \n
 *  			VibrationLong
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/haptic
 *  @warning    사용이 끝났을 때 DestroyVibration() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
 *	Vibration NewVibration (void)
 *	{
 *	    VibrationExtend * this = (VibrationExtend *)malloc (sizeof (VibrationExtend));
 *
 *	    this->vibration.Custom = VibrationCustom;
 *	    this->vibration.Short  = VibrationShort;
 *	    this->vibration.Middle = VibrationMiddle;
 *	    this->vibration.Long   = VibrationLong;
 *
 *	   device_haptic_open (0, &this->handle);
 *
 *	    return &this->vibration;
 *	}
 *	@endcode
 */
Vibration NewVibration (void);

/*! @fn 		void DestroyVibration (Vibration this_gen)
 *  @brief 		생성한 Vibration 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Vibration 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Vibration 객체를 소멸 시킨다. \n
 *  			Vibration 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewVibration
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/haptic
 */
void DestroyVibration (Vibration this_gen);

/*! @fn 		bool VibrationCustom (Vibration this_gen, int period)
 *  @brief 		사용자가 정의한 시간만큼 device를 진동 시킨다.
 *  @param[in] 	this_gen	진동 시킬 Vibration 객체
 *  @param[in] 	period		진동 시킬 시간 (@a Millisecond)
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		사용자가 정의한 @c period 만큼 device를 진동시킨다. \n
 *  			시간 단위는 @a Millisecond 이다.
 *  @see 		NewVibration \n
 *  			VibrationShort \n
 *  			VibrationMiddle \n
 *  			VibrationLong
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/haptic
 */
bool VibrationCustom (Vibration this_gen, int period);

/*! @fn 		bool VibrationShort (Vibration this_gen)
 *  @brief 		짧은 시간만큼 device를 진동 시킨다. (@b 0.1초)
 *  @param[in] 	this_gen	진동 시킬 Vibration 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		짧은 시간만큼 device를 진동 시킨다. (@b 0.1초)
 *  @see 		NewVibration \n
 *  			VibrationCustom \n
 *  			VibrationMiddle \n
 *  			VibrationLong
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/haptic
 */
bool VibrationShort (Vibration this_gen);

/*! @fn 		bool VibrationMiddle (Vibration this_gen)
 *  @brief 		중간 시간만큼 device를 진동 시킨다. (@b 0.5초)
 *  @param[in] 	this_gen	진동 시킬 Vibration 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		중간 시간만큼 device를 진동 시킨다. (@b 0.5초)
 *  @see 		NewVibration \n
 *  			VibrationCustom \n
 *  			VibrationShort \n
 *  			VibrationLong
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/haptic
 */
bool VibrationMiddle (Vibration this_gen);

/*! @fn 		bool VibrationLong (Vibration this_gen)
 *  @brief 		긴 시간만큼 device를 진동 시킨다. (@b 1.5초)
 *  @param[in] 	this_gen	진동 시킬 Vibration 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		긴 시간만큼 device를 진동 시킨다. (@b 1.5초)
 *  @see 		NewVibration \n
 *  			VibrationCustom \n
 *  			VibrationShort \n
 *  			VibrationMiddle
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/haptic
 */
bool VibrationLong (Vibration this_gen);

typedef struct _VibrationExtend
{
    struct _Vibration vibration;
    haptic_device_h   handle;

} VibrationExtend;
/* Vibration */


/* Display*/
/*! @struct	_Display
 *  @brief	Display 모듈에 대한 구조체이다. Display 모듈은 다양한 방식으로 화면을 조절 할 수 있다.
 *  @note	Device Status의 Display 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewDisplay() 함수를 사용해야 하며 사용이 끝났을 때 DestroyDisplay() 함수를 꼭 사용해야 한다. 
 *  @see	[Tizen Native API Document - Display part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__DEVICE__DISPLAY__MODULE.html)                       
 *  @pre    @b privilege \n
 *          * http://tizen.org/privilege/display
 */
typedef struct _Display * Display;
struct _Display
{
    bool (* Lock) (Display this_gen);

    bool (* Unlock) (Display this_gen);

    bool (* Dim) (Display this_gen);

    int (* getBright) (Display this_gen);

    bool (* setBright) (Display this_gen, int bright);
};

/*!	@fn			Display NewDisplay (void)
 *  @brief		새로운 Display 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Display
 *  @note 		새로운 Display 객체를 생성한다. \n
 *  			Display 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyDisplay \n
 *  			DisplayLock \n
 *  			DisplayUnlock \n
 *  			DisplayDim \n
 *  			getDisplayBrightLevel \n
 *  			setDisplayBrightLevel
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/display
 *  @warning    사용이 끝났을 때 DestroyDisplay() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
Display NewDisplay (void)
{
    DisplayExtend * this = (DisplayExtend *)malloc (sizeof (DisplayExtend));

    this->display.Lock      = DisplayLock;
    this->display.Unlock    = DisplayUnlock;
    this->display.Dim       = DisplayDim;
    this->display.getBright = getDisplayBrightLevel;
    this->display.setBright = setDisplayBrightLevel;

    return &this->display;
}
 *	@endcode
 */
Display NewDisplay (void);

/*! @fn 		void DestroyDisplay (Display this_gen)
 *  @brief 		생성한 Display 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Display 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Display 객체를 소멸 시킨다. \n
 *  			Display 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewDisplay
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/display
 */
void DestroyDisplay (Display this_gen);

/*! @fn 		bool DisplayLock (Display this_gen)
 *  @brief 		Device의 화면을 강제로 끈다.(잠금)
 *  @param[in] 	this_gen	강제로 끌 Display 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Device의 화면을 강제로 끈다.
 *  @see 		NewDisplay \n
 *  			DisplayUnlock \n
 *  			DisplayDim \n
 *  			getDisplayBrightLevel \n
 *  			setDisplayBrightLevel
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/display
 */
bool DisplayLock (Display this_gen);

/*! @fn 		bool DisplayUnlock (Display this_gen)
 *  @brief 		Device의 꺼진 화면을 다시 켠다.
 *  @param[in] 	this_gen	다시 켤 Display 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Device의 꺼진 화면을 다시 켠다.
 *  @see 		NewDisplay \n
 *  			DisplayLock \n
 *  			DisplayDim \n
 *  			getDisplayBrightLevel \n
 *  			setDisplayBrightLevel
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/display
 */
bool DisplayUnlock (Display this_gen);

/*! @fn 		bool DisplayDim (Display this_gen)
 *  @brief 		Device의 화면을 어둡게 한다.
 *  @param[in] 	this_gen	어둡게 할 Display 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Device의 화면을 어둡게 한다. \n
 *  			이 때의 화면 밝기는 10% 이다.
 *  @see 		NewDisplay \n
 *  			DisplayLock \n
 *  			DisplayUnlock \n
 *  			getDisplayBrightLevel \n
 *  			setDisplayBrightLevel
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/display
 */
bool DisplayDim (Display this_gen);

/*! @fn 		int getDisplayBrightLevel (Display this_gen)
 *  @brief 		현재 화면의 밝기 값을 반환 한다.
 *  @param[in] 	this_gen	밝기 값을 반환 할 Display 객체
 *  @param[out] null
 *  @retval 	int 현재 화면 밝기(%)
 *  @note 		현재 화면의 밝기 값을 반환 한다. \n
 *  			밝기 값은 % 단위로 0 ~ 100의 값을 가진다.
 *  @see 		NewDisplay \n
 *  			DisplayLock \n
 *  			DisplayUnlock \n
 *  			DisplayDim \n
 *  			setDisplayBrightLevel
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/display
 */
int getDisplayBrightLevel (Display this_gen);

/*! @fn 		bool setDisplayBrightLevel (Display this_gen, int brightLevel)
 *  @brief 		현재 화면의 밝기 값을 설정 한다.
 *  @param[in] 	this_gen	밝기 값을 설정 할 Display 객체
 *  @param[in] 	brightLevel	밝기 값 (0 ~ 100)
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		현재 화면의 밝기 값을 설정 한다. \n
 *  			brightLevel은 % 단위로 0 ~ 100의 값을 가진다.
 *  @see 		NewDisplay \n
 *  			DisplayLock \n
 *  			DisplayUnlock \n
 *  			DisplayDim \n
 *  			getDisplayBrightLevel
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/display
 */
bool setDisplayBrightLevel (Display this_gen, int brightLevel);

typedef struct _DisplayExtend
{
    struct _Display display;
    int             brightLevel;
    display_state_e state;

} DisplayExtend;
/* Display*/


/* Battery */
/*! @struct	_Battery
 *  @brief	Battery 모듈에 대한 구조체이다. Battery 모듈은 배터리의 정보를 읽어 올 수 있다.
 *  @note	Device Status의 Battery 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewBattery() 함수를 사용해야 하며 사용이 끝났을 때 DestoryBattery() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Battery part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__DEVICE__BATTERY__MODULE.html)
 */
typedef struct _Battery * Battery;
struct _Battery
{
    int (* getLevel) (Battery this_gen);

    bool (* isCharging) (Battery this_gen);
};

/*!	@fn			Battery NewBattery (void)
 *  @brief		새로운 Battery 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Battery
 *  @note 		새로운 Battery 객체를 생성한다. \n
 *  			Battery 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestoryBattery \n
 *  			getBatteryRemainsPercent \n
 *  			isBatteryCharging
 *  @warning    사용이 끝났을 때 DestoryBattery() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
Battery NewBattery (void)
{
    BatteryExtend * this = (BatteryExtend *)malloc (sizeof (BatteryExtend));

    this->battery.getLevel   = getBatteryRemainsPercent;
    this->battery.isCharging = isBatteryCharging;

    return &this->battery;
}
 *	@endcode
 */
Battery NewBattery (void);

/*! @fn 		void DestoryBattery (Battery this_gen)
 *  @brief 		생성한 Battery 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Battery 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Battery 객체를 소멸 시킨다. \n
 *  			Battery 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewBattery
 */
void DestoryBattery (Battery this_gen);

/*! @fn 		int getBatteryRemainsPercent (Battery this_gen)
 *  @brief 		현재 배터리의 잔량을 반환 한다.
 *  @param[in] 	this_gen	배터리 잔량을 반환 할 Battery 객체
 *  @param[out] null
 *  @retval 	int 배터리 잔량은 % 단위로 @c 0 ~ @c 100의 값을 가진다.
 *  @note 		현재 배터리의 잔량을 반환 한다.
 *  @see 		NewBattery \n
 *  			isBatteryCharging
 */
int getBatteryRemainsPercent (Battery this_gen);

/*! @fn 		bool isBatteryCharging (Battery this_gen)
 *  @brief 		현재 배터리의 충전 상태 여부를 반환 한다.
 *  @param[in] 	this_gen	충전 상태 여부를 반환 할 Battery 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		현재 배터리의 충전 상태 여부를 반환 한다. \n
 *  			충전 중 이라면 @c true, 충전 중이 아니라면 @c false를 반환한다.
 *  @see 		NewBattery \n
 *  			getBatteryRemainsPercent
 */
bool isBatteryCharging (Battery this_gen);

typedef struct _BatteryExtend
{
    struct _Battery battery;
    int             batteryLevel;
    bool            charging;

} BatteryExtend;
/* Battery */


/* Flash */
/*! @struct	_Flash
 *  @brief	Flash 모듈에 대한 구조체이다. Flash 모듈은 Device의 플래시를 제어 할 수 있다.
 *  @note	Device Status의 Flash 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewFlash() 함수를 사용해야 하며 사용이 끝났을 때 DestoryFlash() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Flash(LED) part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__DEVICE__LED__MODULE.html)
 *  @pre    @b feature \n
 *          * http://tizen.org/feature/led \n
 *          * http://tizen.org/feature/camera.back.flash \n
 *  @pre    @b priviledge \n
 *          * http://tizen.org/privilege/led \n
 */
typedef struct _Flash * Flash;
struct _Flash
{
    bool (* On) (void);

    bool (* Off) (void);
};

/*!	@fn			Flash NewFlash (void)
 *  @brief		새로운 Flash 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Flash
 *  @note 		새로운 Flash 객체를 생성한다. \n
 *  			Display 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestoryFlash \n
 *  			onFlash \n
 *  			offFlash
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/led \n
 *              * http://tizen.org/feature/camera.back.flash \n
 *  @pre        @b priviledge \n
 *              * http://tizen.org/privilege/led \n
 *  @warning    사용이 끝났을 때 DestoryFlash() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
Flash NewFlash (void)
{
    Flash this = (Flash)malloc (sizeof (struct _Flash));

    this->On  = onFlash;
    this->Off = offFlash;

    return this;
}
 *	@endcode
 */
Flash NewFlash (void);

/*!	@fn			void DestoryFlash (Flash this_gen)
 *  @brief		생성한 Flash 객체를 소멸 시킨다.
 *  @param[in]	this_gen 소멸시킬 Flash 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Flash 객체를 소멸 시킨다. \n
 *  			Flash 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewFlash
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/led \n
 *              * http://tizen.org/feature/camera.back.flash \n
 *  @pre        @b priviledge \n
 *              * http://tizen.org/privilege/led \n
 */
void DestoryFlash (Flash this_gen);

/*!	@fn			void onFlash (void)
 *  @brief		후면 카메라의 플래시를 켠다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		후면 카메라의 플래시를 켠다. \n
 *  			이 때의 밝기는 최대 밝기로 켜진다.
 *  @see 		NewFlash \n
 *  			offFlash
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/led \n
 *              * http://tizen.org/feature/camera.back.flash \n
 *  @pre        @b priviledge \n
 *              * http://tizen.org/privilege/led \n
 */
bool onFlash (void);

/*!	@fn			void offFlash (void)
 *  @brief		후면 카메라의 플래시를 끈다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		후면 카메라의 플래시를 끈다.
 *  @see 		NewFlash \n
 *  			onFlash
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/led \n
 *              * http://tizen.org/feature/camera.back.flash \n
 *  @pre        @b priviledge \n
 *              * http://tizen.org/privilege/led \n
 */
bool offFlash (void);
/* Flash */


#ifdef __cplusplus
}
#endif

#endif //DIT_DEVICESTATUS_H
