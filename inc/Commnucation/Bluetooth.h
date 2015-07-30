/*! @file	Bluetooth.h
 *  @brief	Bluetooth API 를 사용하기 위해 포함해야 하는 헤더이다.
 *  @note	Bluetooth의 isAccessible / onConnect / isConnected / onDisconnect / FileSend / FileRecv API를 제공한다.
 *  @see	[Tizen Native API](https://developer.tizen.org/development/api-references/native-application?redirect=https%3A//developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/index.html)
 */

#ifndef DIT_BLUETOOTH_H
#define DIT_BLUETOOTH_H

#include <stdbool.h>
#include <stdalign.h>

#include "dit.h"

#include <glib.h>
#include <bluetooth.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! @fn 		const char * BluetoothErrorCheck (int errCode)
 *  @brief 		Bluetooth API에서 발생하는 Error Code들을 확인 해준다.
 *  @param[in] 	errCode 확인 하고자 하는 Error Code
 *  @param[out]	null
 *  @retval 	BT_ERROR_NONE						 : Successful
 *  @retval 	BT_ERROR_CANCELLED					 : Operation cancelled
 *  @retval 	BT_ERROR_INVALID_PARAMETER			 : Invalid parameter
 *  @retval 	BT_ERROR_OUT_OF_MEMORY				 : Out of memory
 *  @retval 	BT_ERROR_RESOURCE_BUSY				 : Device or resource busy
 *  @retval 	BT_ERROR_TIMED_OUT					 : Timeout error
 *  @retval 	BT_ERROR_NOW_IN_PROGRESS			 : Operation now in progress
 *  @retval 	BT_ERROR_NOT_SUPPORTED				 : Not Supported
 *  @retval 	BT_ERROR_PERMISSION_DENIED			 : Permission denied
 *  @retval 	BT_ERROR_QUOTA_EXCEEDED				 : Quota exceeded
 *  @retval 	BT_ERROR_NOT_INITIALIZED			 : Local adapter not initialized
 *  @retval 	BT_ERROR_NOT_ENABLED				 : Local adapter not enabled
 *  @retval 	BT_ERROR_ALREADY_DONE				 : Operation already done
 *  @retval 	BT_ERROR_OPERATION_FAILED			 : Operation failed
 *  @retval 	BT_ERROR_NOT_IN_PROGRESS			 : Operation not in progress
 *  @retval 	BT_ERROR_REMOTE_DEVICE_NOT_BONDED	 : Remote device not bonded
 *  @retval 	BT_ERROR_AUTH_REJECTED				 : Authentication rejected
 *  @retval 	BT_ERROR_AUTH_FAILED				 : Authentication failed
 *  @retval 	BT_ERROR_REMOTE_DEVICE_NOT_FOUND	 : Remote device not found
 *  @retval 	BT_ERROR_SERVICE_SEARCH_FAILED		 : Service search failed
 *  @retval 	BT_ERROR_REMOTE_DEVICE_NOT_CONNECTED : Remote device is not connected
 *  @retval 	BT_ERROR_AGAIN						 : Resource temporarily unavailable
 *  @retval 	BT_ERROR_SERVICE_NOT_FOUND			 : Service Not Found
 *  @retval 	BT_ERROR_UNKNWON					 : Unknown error occurred
 *  @note 		Bluetooth API에서 발생하는 Error Code들을 확인 해준다. \n
 *              Error의 내용은 Log를 통해 출력 된다.  \n
 *  			24가지의 Error Code들을 확인 가능 하다.
 *  @see 		[Tizen Native API Document - Bluetooth part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__NETWORK__BLUETOOTH__MODULE.html)
 */
const char * BluetoothErrorCheck (int errCode);

/* Bluetooth */
/*! @struct	_Bluetooth
 *  @brief	Bluetooth 모듈에 대한 구조체이다. Bluetooth 모듈은 다양한 방식으로 Bluetooth 통신을 할 수 있다.
 *  @note	Bluetooth의 Bluetooth 모듈에 대한 구조체이다. \n
 *    		구조체를 사용하기 전에 NewBluetooth() 함수를 사용해야 하며 사용이 끝났을 때 DestroyBluetooth() 함수를 꼭 사용해야 한다.
 *  @see    [Tizen Native API Document - Bluetooth part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__NETWORK__BLUETOOTH__MODULE.html)
 *  @pre	@b feature \n
 *          * http://tizen.org/feature/network.bluetooth
 */
typedef struct _Bluetooth * Bluetooth;
struct _Bluetooth
{
    bool (* isAccessible) (Bluetooth this_gen);

    bool (* onConnect) (Bluetooth this_gen);

    bool (* isConnected) (Bluetooth this_gen);

    bool (* onDisconnect) (Bluetooth this_gen);

    bool (* FileSend) (Bluetooth this_gen, String sendBuffer);

    bool (* FileRecv) (Bluetooth this_gen, String * recvBuffer);

};

/*!	@fn			Bluetooth NewBluetooth (void)
 *  @brief		새로운 Bluetooth 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Bluetooth
 *  @note 		새로운 Bluetooth 객체를 생성한다. \n
 *  			Bluetooth 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyBluetooth \n
 *  			isBluetoothAccessible \n
 *  			onBluetoothConnect \n
 *  			isBluetoothConnected \n
 *  			onBluetoothDisconnect \n
 *  			BluetoothFileSend \n
 * 				BluetoothFileRecv
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/network.bluetooth
 *  @warning    사용이 끝났을 때 DestroyBluetooth() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
 *  Bluetooth NewBluetooth (void)
 *  {
 *  	BluetoothExtends * this = malloc (sizeof (BluetoothExtends));
 *  	this->bluetooth.isAccessible = isBluetoothAccessible;
 *  	this->bluetooth.onConnect    = onBluetoothConnect;
 *  	this->bluetooth.isConnected  = isBluetoothConnected;
 *  	this->bluetooth.onDisconnect = onBluetoothDisconnect;
 *  	this->bluetooth.FileRecv     = BluetoothFileRecv;
 *  	this->bluetooth.FileSend     = BluetoothFileSend;
 *
 *  	this->connected     = false;
 *  	this->accessible    = false;
 *  	this->remoteMACAddr = NULL;
 *
 *  	return &this->bluetooth;
 *  }
 *  @endcode
 */
Bluetooth NewBluetooth (void);

/*! @fn 		void DestroyBluetooth (Bluetooth this_gen)
 *  @brief 		생성한 Bluetooth 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Bluetooth 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Bluetooth 객체를 소멸 시킨다. \n
 *  			Bluetooth 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewBluetooth
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/network.bluetooth
 */
void DestroyBluetooth (Bluetooth this_gen);

/*! @fn 		bool isBluetoothAccessible (Bluetooth this_gen)
 *  @brief 		현재 Bluetooth 기능 지원 여부를 반환 한다.
 *  @param[in] 	this_gen 사용 가능 여부를 반환 할 Bluetooth 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		현재 Bluetooth 기능 지원 여부를 반환 한다. \n
 *  			지원 가능 이라면 @c true, 지원 가능이 아니라면 @c false를 반환한다.
 *  @see 		NewBluetooth \n
 *  			DestroyBluetooth \n
 *  			onBluetoothConnect \n
 *  			isBluetoothConnected \n
 *  			onBluetoothDisconnect \n
 *  			BluetoothFileSend \n
 * 				BluetoothFileRecv
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/network.bluetooth
 */
bool isBluetoothAccessible (Bluetooth this_gen);

/*! @fn 		bool onBluetoothConnect (Bluetooth this_gen)
 *  @brief 		Bluetooth기기로 연결을 시도하며 이의 성공 여부를 반환한다.
 *  @param[in] 	this_gen 연결 성공 여부를 확인할 Bluetooth 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Bluetooth기기로 연결을 시도하며 이의 성공 여부를 반환한다. \n
 *  			연결에 성공하면 @c true, 실패하면 @c false를 반환한다.
 *  @see 		NewBluetooth \n
 *  			DestroyBluetooth \n
 *  			isBluetoothAccessible \n
 *  			isBluetoothConnected \n
 *  			onBluetoothDisconnect \n
 *  			BluetoothFileSend \n
 * 				BluetoothFileRecv
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/network.bluetooth
 */
bool onBluetoothConnect (Bluetooth this_gen);

/*! @fn 		bool isBluetoothConnected (Bluetooth this_gen)
 *  @brief 		Bluetooth기기와의 연결 상태를 확인한다.
 *  @param[in] 	this_gen 연결 상태를 확인할 Bluetooth 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Bluetooth기기와의 연결 상태를 확인한다. \n
 *  			연결되어 있다면 @c true, 연결되어 있지 않다면 @c false를 반환한다.
 *  @see 		NewBluetooth \n
 *  			DestroyBluetooth \n
 *  			isBluetoothAccessible \n
 *  			onBluetoothConnect \n
 *  			onBluetoothDisconnect \n
 *  			BluetoothFileSend \n
 * 				BluetoothFileRecv
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/network.bluetooth
 */
bool isBluetoothConnected (Bluetooth this_gen);

/*! @fn 		bool onBluetoothDisconnect (Bluetooth this_gen)
 *  @brief 		Bluetooth기기로 연결을 해제하며 이의 성공 여부를 반환한다.
 *  @param[in] 	this_gen 연결 해제 여부를 확인할 Bluetooth 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Bluetooth기기로 연결을 해제하며 이의 성공 여부를 반환한다. \n
 *  			연결 해제에 성공하면 @c true, 실패하면 @c false를 반환한다.
 *  @see 		NewBluetooth \n
 *  			DestroyBluetooth \n
 *  			isBluetoothAccessible \n
 *  			onBluetoothConnect \n
 *  			isBluetoothConnected \n
 *  			BluetoothFileSend \n
 * 				BluetoothFileRecv
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/network.bluetooth
 */
bool onBluetoothDisconnect (Bluetooth this_gen);

/*! @fn 		bool BluetoothFileSend (Bluetooth this_gen, String sendbuffer)
 *  @brief 		Bluetooth기기로 데이터를 송신한다.
 *  @param[in] 	this_gen 데이터를 송신할 Bluetooth 객체
 *  @param[in] 	sendbuffer 송신할 파일 path
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Bluetooth기기로 데이터를 송신한다. \n
 *  @see 		NewBluetooth \n
 *  			DestroyBluetooth \n
 *  			isBluetoothAccessible \n
 *  			onBluetoothConnect \n
 *  			isBluetoothConnected \n
 *  			onBluetoothDisconnect \n
 * 				BluetoothFileRecv
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/network.bluetooth
 */
bool BluetoothFileSend (Bluetooth this_gen, String sendbuffer);

/*! @fn 		bool BluetoothFileRecv (Bluetooth this_gen, String * recvBuffer)
 *  @brief 		Bluetooth기기로 부터 데이터를 수신한다.
 *  @param[in] 	this_gen 데이터를 수신할 Bluetooth 객체
 *  @param[in] 	recvBuffer 수신할 데이터 주소
 *  @param[out] recvBuffer 수신한 데이터
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Bluetooth기기로 부터 데이터를 수신한다.
 *  @see 		NewBluetooth \n
 *  			DestroyBluetooth \n
 *  			isBluetoothAccessible \n
 *  			onBluetoothConnect \n
 *  			isBluetoothConnected \n
 *  			onBluetoothDisconnect \n
 * 				BluetoothFileSend
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/network.bluetooth
 */
bool BluetoothFileRecv (Bluetooth this_gen, String * recvBuffer);

typedef struct _BluetoothExtends
{
    struct _Bluetooth bluetooth;
    bool              connected;
    bool              accessible;
    String            remoteMACAddr;

} BluetoothExtends;
/* Bluetooth */

#ifdef __cplusplus
}
#endif

#endif //DIT_BLUETOOTH_H
