/*! @file	DeviceStatus.h
 *  @brief	Device Status API 를 사용하기 위해 포함해야 하는 헤더이다.
 *  @note	Device의 Vibration / Display / Battery / Flash 관련 API를 제공한다.
 *  @see	https://developer.tizen.org/development/api-references/native-application?redirect=https%3A//developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/index.html
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
 *  @retval 	String
 *  @note 		Device Status API에서 발생하는 Error Code들을 확인 해준다. \n
 *  			8가지의 Error Code들을 확인 가능 하다.
 *  @see 		https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__DEVICE__MODULE.html#ggaa7466207772dc4d17f6cb814d79cb789abeb24a4c3efe6ca49702f99a72217153
*/
const char * DeviceStatusErrorCheck (int errCode);

/* Vibration */
/*! @struct	_Vibration
 *  @brief	Vibration 모듈에 대한 구조체이다. Vibration 모듈은 다양한 방식으로 진동을 조절 할 수 있다.
 *  @note	Device Status의 Vibration 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewVibration() 함수를 사용해야 하며 사용이 끝났을 때 DestroyVibration() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__DEVICE__HAPTIC__MODULE.html
 *  @todo	privilege에 "http://tizen.org/privilege/haptic" 을 반드시 추가해야 한다.
*/
typedef struct _Vibration * Vibration;
struct _Vibration
{
    void (* Custom) (Vibration this_gen, int period);

    void (* Short) (Vibration this_gen);

    void (* Middle) (Vibration this_gen);

    void (* Long) (Vibration this_gen);
};

/*!	@fn			Vibration NewVibration (void)
 *  @brief		새로운 Vibration 모듈을 생성한다.
 *  @param[in]	null
 *  @param[out] null
 *  @retval 	Vibration
 *  @note 		새로운 Vibration 모듈을 생성한다. Vibration 구조체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyVibration \n
 *  			VibrationCustom \n
 *  			VibrationShort \n
 *  			VibrationMiddle \n
 *  			VibrationLong
 *  @remark 	privilege	: http://tizen.org/privilege/haptic
*/
Vibration NewVibration (void);

/*! @fn 		void DestroyVibration (Vibration this_gen)
 *  @brief 		생성한 Vibration 모듈을 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Vibration 모듈
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Vibration 모듈을 소멸 시킨다. Vibration 구조체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewVibration
 *  @remark 	privilege	: http://tizen.org/privilege/haptic
 */
void      DestroyVibration (Vibration this_gen);

/*! @fn 		void VibrationCustom (Vibration this_gen, int period)
 *  @brief 		사용자가 정의한 시간만큼 진동한다.
 *  @param[in] 	this_gen	진동 시킬 Vibration 모듈
 *  @param[in] 	period		진동 시킬 시간 (Millisecond)
 *  @param[out] null
 *  @retval 	void
 *  @note 		Vibration 모듈을 period 만큼 진동 시킨다. 시간 단위는 Millisecond 이다.
 *  @see 		NewVibration \n
 *  			VibrationShort \n
 *  			VibrationMiddle \n
 *  			VibrationLong
 *  @remark 	privilege	: http://tizen.org/privilege/haptic
 */
void      VibrationCustom (Vibration this_gen, int period);

/*! @fn 		void VibrationShort (Vibration this_gen)
 *  @brief 		짧은 시간만큼 진동한다. (0.1초)
 *  @param[in] 	this_gen	진동 시킬 Vibration 모듈
 *  @param[out] null
 *  @retval 	void
 *  @note 		Vibration 모듈을 짧은 시간만큼 진동 시킨다. (0.1초)
 *  @see 		NewVibration \n
 *  			VibrationCustom \n
 *  			VibrationMiddle \n
 *  			VibrationLong
 *  @remark 	privilege	: http://tizen.org/privilege/haptic
 */
void      VibrationShort (Vibration this_gen);

/*! @fn 		void VibrationMiddle (Vibration this_gen)
 *  @brief 		중간 시간만큼 진동한다. (0.5초)
 *  @param[in] 	this_gen	진동 시킬 Vibration 모듈
 *  @param[out] null
 *  @retval 	void
 *  @note 		Vibration 모듈을 중간 시간만큼 진동 시킨다. (0.5초)
 *  @see 		NewVibration \n
 *  			VibrationCustom \n
 *  			VibrationShort \n
 *  			VibrationLong
 *  @remark 	privilege	: http://tizen.org/privilege/haptic
 */
void      VibrationMiddle (Vibration this_gen);

/*! @fn 		void VibrationLong (Vibration this_gen)
 *  @brief 		긴 시간만큼 진동한다. (1.5초)
 *  @param[in] 	this_gen	진동 시킬 Vibration 모듈
 *  @param[out] null
 *  @retval 	void
 *  @note 		Vibration 모듈을 긴 시간만큼 진동 시킨다. (1.5초)
 *  @see 		NewVibration \n
 *  			VibrationCustom \n
 *  			VibrationShort \n
 *  			VibrationMiddle
 *  @remark 	privilege	: http://tizen.org/privilege/haptic
 */
void      VibrationLong (Vibration this_gen);

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
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__DEVICE__DISPLAY__MODULE.html
 *  @todo	privilege에 "http://tizen.org/privilege/display" 를 반드시 추가해야 한다.
*/
typedef struct _Display * Display;
struct _Display
{
    void (* Lock) (Display this_gen);

    void (* Unlock) (Display this_gen);

    void (* Dim) (Display this_gen);

    int (* getBright) (Display this_gen);

    void (* setBright) (Display this_gen, int bright);
};

/*!	@fn			Display NewDisplay (void)
 *  @brief		새로운 Display 모듈을 생성한다.
 *  @param[in]	null
 *  @param[out] null
 *  @retval 	Display
 *  @note 		새로운 Display 모듈을 생성한다. Display 구조체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyDisplay \n
 *  			DisplayLock \n
 *  			DisplayUnlock \n
 *  			DisplayDim \n
 *  			getDisplayBrightLevel \n
 *  			setDisplayBrightLevel
 *  @remark 	privilege	: http://tizen.org/privilege/display
*/
Display NewDisplay (void);

/*! @fn 		void DestroyDisplay (Display this_gen)
 *  @brief 		생성한 Display 모듈을 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Display 모듈
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Display 모듈을 소멸 시킨다. Display 구조체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewDisplay
 *  @remark 	privilege	: http://tizen.org/privilege/display
 */
void    DestroyDisplay (Display this_gen);

/*! @fn 		void DisplayLock (Display this_gen)
 *  @brief 		Device의 화면을 강제로 끈다.(잠금)
 *  @param[in] 	this_gen	강제로 끌 Display 모듈
 *  @param[out] null
 *  @retval 	void
 *  @note 		Device의 화면을 강제로 끈다.
 *  @see 		NewDisplay \n
 *  			DisplayUnlock \n
 *  			DisplayDim \n
 *  			getDisplayBrightLevel \n
 *  			setDisplayBrightLevel
 *  @remark 	privilege	: http://tizen.org/privilege/display
 */
void    DisplayLock (Display this_gen);

/*! @fn 		void DisplayUnlock (Display this_gen)
 *  @brief 		Device의 꺼진 화면을 다시 켠다.
 *  @param[in] 	this_gen	다시 켤 Display 모듈
 *  @param[out] null
 *  @retval 	void
 *  @note 		Device의 꺼진 화면을 다시 켠다.
 *  @see 		NewDisplay \n
 *  			DisplayLock \n
 *  			DisplayDim \n
 *  			getDisplayBrightLevel \n
 *  			setDisplayBrightLevel
 *  @remark 	privilege	: http://tizen.org/privilege/display
 */
void    DisplayUnlock (Display this_gen);

/*! @fn 		void DisplayDim (Display this_gen)
 *  @brief 		Device의 화면을 어둡게 한다.
 *  @param[in] 	this_gen	어둡게 할 Display 모듈
 *  @param[out] null
 *  @retval 	void
 *  @note 		Device의 화면을 어둡게 한다. 이 때의 밝기는 10% 이다.
 *  @see 		NewDisplay \n
 *  			DisplayLock \n
 *  			DisplayUnlock \n
 *  			getDisplayBrightLevel \n
 *  			setDisplayBrightLevel
 *  @remark 	privilege	: http://tizen.org/privilege/display
 */
void    DisplayDim (Display this_gen);

/*! @fn 		int getDisplayBrightLevel (Display this_gen)
 *  @brief 		현재 화면의 밝기 값을 반환 한다.
 *  @param[in] 	this_gen	밝기 값을 반환 할 Display 모듈
 *  @param[out] null
 *  @retval 	int 밝기 값은 % 단위로 0 ~ 100의 값을 가진다.
 *  @note 		현재 화면의 밝기 값을 반환 한다.
 *  @see 		NewDisplay \n
 *  			DisplayLock \n
 *  			DisplayUnlock \n
 *  			DisplayDim \n
 *  			setDisplayBrightLevel
 *  @remark 	privilege	: http://tizen.org/privilege/display
 */
int     getDisplayBrightLevel (Display this_gen);

/*! @fn 		int setDisplayBrightLevel (Display this_gen, int brightLevel)
 *  @brief 		현재 화면의 밝기 값을 설정 한다.
 *  @param[in] 	this_gen	밝기 값을 설정 할 Display 모듈
 *  @param[in] 	brightLevel	밝기 값 (0 ~ 100)
 *  @param[out] null
 *  @retval 	int
 *  @note 		현재 화면의 밝기 값을 설정 한다. brightLevel은 % 단위로 0 ~ 100의 값을 가진다.
 *  @see 		NewDisplay \n
 *  			DisplayLock \n
 *  			DisplayUnlock \n
 *  			DisplayDim \n
 *  			getDisplayBrightLevel
 *  @remark 	privilege	: http://tizen.org/privilege/display
 */
void    setDisplayBrightLevel (Display this_gen, int brightLevel);

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
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__DEVICE__BATTERY__MODULE.html
*/
typedef struct _Battery * Battery;
struct _Battery
{
    int (* getLevel) (Battery this_gen);

    bool (* isCharging) (Battery this_gen);
};

/*!	@fn			Battery NewBattery (void)
 *  @brief		새로운 Battery 모듈을 생성한다.
 *  @param[in]	null
 *  @param[out] null
 *  @retval 	Battery
 *  @note 		새로운 Battery 모듈을 생성한다. \n
 *  			Battery 구조체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestoryBattery \n
 *  			getBatteryRemainsPercent \n
 *  			isBatteryCharging
*/
Battery NewBattery (void);

/*! @fn 		void DestoryBattery (Battery this_gen)
 *  @brief 		생성한 Battery 모듈을 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Battery 모듈
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Battery 모듈을 소멸 시킨다. \n
 *  			Battery 구조체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewBattery
*/
void    DestoryBattery (Battery this_gen);

/*! @fn 		int getBatteryRemainsPercent (Battery this_gen)
 *  @brief 		현재 배터리의 잔량을 반환 한다.
 *  @param[in] 	this_gen	배터리 잔량을 반환 할 Battery 모듈
 *  @param[out] null
 *  @retval 	int 배터리 잔량은 % 단위로 0 ~ 100의 값을 가진다.
 *  @note 		현재 배터리의 잔량을 반환 한다.
 *  @see 		NewBattery \n
 *  			isBatteryCharging
 */
int     getBatteryRemainsPercent (Battery this_gen);

/*! @fn 		bool isBatteryCharging (Battery this_gen)
 *  @brief 		현재 배터리의 충전 상태 여부를 반환 한다.
 *  @param[in] 	this_gen	충전 상태 여부를 반환 할 Battery 모듈
 *  @param[out] null
 *  @retval 	bool
 *  @note 		현재 배터리의 충전 상태 여부를 반환 한다. \n
 *  			충전 중 이라면 true, 충전 중이 아니라면 false를 반환한다.
 *  @see 		NewBattery \n
 *  			getBatteryRemainsPercent
 */
bool    isBatteryCharging (Battery this_gen);

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
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__SYSTEM__DEVICE__LED__MODULE.html
 *  @todo	privilege에 "http://tizen.org/privilege/led" 를 반드시 추가해야 한다. \n
 *			features에 "http://tizen.org/feature/led" 를 반드시 추가한다. \n
 *			features에 "http://tizen.org/feature/camera.back.flash" 를 반드시 추가한다.
*/
typedef struct _Flash * Flash;
struct _Flash
{
    void (* On) (void);

    void (* Off) (void);
};

/*!	@fn			Flash NewFlash (void)
 *  @brief		새로운 Flash 모듈을 생성한다.
 *  @param[in]	null
 *  @param[out] null
 *  @retval 	Flash
 *  @note 		새로운 Flash 모듈을 생성한다. \n
 *  			Display 구조체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestoryFlash \n
 *  			onFlash \n
 *  			offFlash
 *  @remark 	privilege	: http://tizen.org/privilege/led \n
 *				features	: http://tizen.org/feature/led \n
 *				features	: http://tizen.org/feature/camera.back.flash
*/
Flash NewFlash (void);

/*!	@fn			void DestoryFlash (Flash this_gen)
 *  @brief		생성한 Flash 모듈을 소멸 시킨다.
 *  @param[in]	this_gen 소멸시킬 Flash 모듈
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Flash 모듈을 소멸 시킨다. \n
 *  			Flash 구조체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewFlash
 *  @remark 	privilege	: http://tizen.org/privilege/led \n
 *				features	: http://tizen.org/feature/led \n
 *				features	: http://tizen.org/feature/camera.back.flash
*/
void  DestoryFlash (Flash this_gen);

/*!	@fn			void onFlash (void)
 *  @brief		후면 카메라의 플래시를 켠다.
 *  @param[in]	null
 *  @param[out] null
 *  @retval 	void
 *  @note 		후면 카메라의 플래시를 켠다. \n
 *  			이 때의 밝기는 최대 밝기로 켜진다.
 *  @see 		NewFlash \n
 *  			offFlash
 *  @remark 	privilege	: http://tizen.org/privilege/led \n
 *				features	: http://tizen.org/feature/led \n
 *				features	: http://tizen.org/feature/camera.back.flash
*/
void  onFlash (void);

/*!	@fn			void offFlash (void)
 *  @brief		후면 카메라의 플래시를 끈다.
 *  @param[in]	null
 *  @param[out] null
 *  @retval 	void
 *  @note 		후면 카메라의 플래시를 끈다.
 *  @see 		NewFlash \n
 *  			onFlash
 *  @remark 	privilege	: http://tizen.org/privilege/led \n
 *				features	: http://tizen.org/feature/led \n
 *				features	: http://tizen.org/feature/camera.back.flash
*/
void  offFlash (void);

/* Flash */

#ifdef __cplusplus
}
#endif

#endif //DIT_DEVICESTATUS_H
