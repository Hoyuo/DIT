/*! @file	GPS.h
 *  @brief	GPS API 를 사용하기 위해 포함해야 하는 헤더이다.
 *  @note	GPS의 isAccessible / onConnect / onDisconnect / Recv API를 제공한다.
 *  @see    [Tizen Native API](https://developer.tizen.org/development/api-references/native-application?redirect=https%3A//developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/index.html)
 */

#ifndef DIT_GPS_H
#define DIT_GPS_H

#include <stdbool.h>
#include <stdalign.h>

#include <locations.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! @fn 		const char * GPSErrorChecker (int errCode)
 *  @brief 		GPS API에서 발생하는 Error Code들을 확인 해준다.
 *  @param[in] 	errCode 확인 하고자 하는 Error Code
 *  @param[out]	null
 *  @retval 	LOCATIONS_ERROR_NONE						 : Successful
 *  @retval 	LOCATIONS_ERROR_OUT_OF_MEMORY				 : Out of memory
 *  @retval 	LOCATIONS_ERROR_INVALID_PARAMETER			 : Invalid parameter
 *  @retval 	LOCATIONS_ERROR_ACCESSIBILITY_NOT_ALLOWED	 : Permission denied
 *  @retval 	LOCATIONS_ERROR_NOT_SUPPORTED				 : Not supported
 *  @retval 	LOCATIONS_ERROR_INCORRECT_METHOD			 : Location manager contains incorrect method for a given call
 *  @retval 	LOCATIONS_ERROR_NETWORK_FAILED				 : Network unavailable
 *  @retval 	LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE		 : Location service is not available
 *  @retval 	LOCATIONS_ERROR_GPS_SETTING_OFF				 : GPS/WPS setting is not enabled
 *  @retval 	LOCATIONS_ERROR_SECURITY_RESTRICTED			 : Restricted by security system policy
 *  @retval 	LOCATIONS_ERROR_UNKNWON						 : Unknown error occurred
 *  @note 		GPS API에서 발생하는 Error Code들을 확인 해준다. \n
 *              Error의 내용은 Log를 통해 출력 된다. \n
 *  			11가지의 Error Code들을 확인 가능 하다.
 *  @see        [Tizen Native API Document - GPS part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__LOCATION__GPS__STATUS__MODULE.html)
 */
const char * GPSErrorChecker (int errCode);

typedef struct _location
{
    double                    altitude;
    double                    latitude;
    double                    longitude;
    double                    climb;
    double                    direction;
    double                    speed;
    location_accuracy_level_e level;
    double                    horizontal;
    double                    vertical;
    time_t                    timestamp;
    bool                      validation;

} Location;

/* GPS */
/*! @struct	_gps
 *  @brief	GPS 모듈에 대한 구조체이다. GPS 모듈은 다양한 방식으로 GPS를 사용할 수 있다.
 *  @note	GPS의 GPS 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewGps() 함수를 사용해야 하며 사용이 끝났을 때 DestroyGps() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__LOCATION__GPS__STATUS__MODULE.html
 *  @pre    @b feature \n
 *          * http://tizen.org/feature/location \n
 *          * http://tizen.org/feature/location.gps
 */
typedef struct _gps * GPS;
struct _gps
{
    bool (* isAccessible) (GPS this_gen);

    bool (* onConnect) (GPS this_gen);

    bool (* onDisconnect) (GPS this_gen);

    Location (* Recv) (GPS this_gen);

};

/*!	@fn			GPS NewGps (void)
 *  @brief		새로운 GPS 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	GPS
 *  @note 		새로운 GPS 객체를 생성한다. \n
 *  			GPS 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyGps \n
 *  			isGPSAccessible \n
 *  			onGPSConnect \n
 *  			onGPSDisconnect \n
 *  			GPSRecv
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/location \n
 *              * http://tizen.org/feature/location.gps
 *  @warning    사용이 끝났을 때 DestroyGps() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
 *  GPS NewGps (void)
 *  {
 *      GPSExtends * this = (GPSExtends *)malloc (sizeof (GPSExtends));
 *
 *      this->gps.isAccessible = isGPSAccessible;
 *      this->gps.onConnect    = onGPSConnect;
 *      this->gps.onDisconnect = onGPSDisconnect;
 *      this->gps.Recv         = GPSRecv;
 *
 *      location_manager_create (LOCATIONS_METHOD_GPS, &this->manager);
 *
 *      this->state = LOCATIONS_SERVICE_DISABLED;
 *
 *      Location location = {0,};
 *      this->location = location;
 *      this->access   = false;
 *      this->connect  = false;
 *
 *      return &this->gps;
 *  }
 *  @endcode
 */
GPS NewGps (void);

/*! @fn 		void DestroyGps (GPS this_gen)
 *  @brief 		생성한 GPS 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 GPS 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 GPS 객체를 소멸 시킨다. \n
 *  			GPS 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewGps
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/location \n
 *              * http://tizen.org/feature/location.gps
 */
void DestroyGps (GPS this_gen);

/*! @fn 		bool isGPSAccessible (GPS this_gen)
 *  @brief 		현재 GPS 기능 지원 여부를 반환 한다.
 *  @param[in] 	this_gen 사용 가능 여부를 반환 할 GPS 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		현재 GPS 기능 지원 여부를 반환 한다. \n
 *  			지원 가능 이라면 @c true, 지원 가능이 아니라면 @c false를 반환한다.
 *  @see 		NewGps \n
 *  			DestroyGps \n
 *  			onGPSConnect \n
 *  			onGPSDisconnect \n
 *  			GPSRecv
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/location \n
 *              * http://tizen.org/feature/location.gps
 */
bool isGPSAccessible (GPS this_gen);

/*! @fn 		bool onGPSConnect (GPS this_gen)
 *  @brief 		GPS로 연결을 시도하며 이의 성공 여부를 반환한다.
 *  @param[in] 	this_gen 연결 성공 여부를 확인할 GPS 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		GPS로 연결을 시도하며 이의 성공 여부를 반환한다. \n
 *  			연결에 성공하면 @c true, 실패하면 @c false를 반환한다.
 *  @see 		NewGps \n
 *  			DestroyGps \n
 *  			isGPSAccessible \n
 *  			onGPSDisconnect \n
 *  			GPSRecv
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/location \n
 *              * http://tizen.org/feature/location.gps
 */
bool onGPSConnect (GPS this_gen);

/*! @fn 		bool onGPSDisconnect (GPS this_gen)
 *  @brief 		GPS로의 연결을 해제하며 이의 성공 여부를 반환한다.
 *  @param[in] 	this_gen 연결 해제 여부를 확인할 GPS 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		GPS로의 연결을 해제하며 이의 성공 여부를 반환한다. \n
 *  			연결 해제에 성공하면 @ true, 실패하면 @c false를 반환한다.
 *  @see 		NewGps \n
 *  			DestroyGps \n
 *  			isGPSAccessible \n
 *  			onGPSConnect \n
 *  			GPSRecv
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/location \n
 *              * http://tizen.org/feature/location.gps
 */
bool onGPSDisconnect (GPS this_gen);

/*! @fn 		Location GPSRecv (GPS this_gen)
 *  @brief 		GPS로 부터 위치 정보를 수신한다.
 *  @param[in] 	this_gen 데이터를 수신할 GPS 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		GPS로 부터 위치 정보를 수신한다.
 *  @see 		NewGps \n
 *  			DestroyGps \n
 *  			isGPSAccessible \n
 *  			onGPSConnect \n
 *  			onGPSDisconnect
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/location \n
 *              * http://tizen.org/feature/location.gps
 */
Location GPSRecv (GPS this_gen);

typedef struct _GPSExtends
{
    struct _gps              gps;
    location_manager_h       manager;
    location_service_state_e state;
    Location                 location;
    bool                     access;
    bool                     connect;

} GPSExtends;
/* GPS */

#ifdef __cplusplus
}
#endif

#endif //DIT_GPS_H
