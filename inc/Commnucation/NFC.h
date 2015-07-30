/*! @file	NFC.h
 *  @brief	NFC API 를 사용하기 위해 포함해야 하는 헤더이다.
 *  @note	NFC의 CreateNDEF / DeleteNDEF / isAccessible / onConnect / isConnected / onDisconnect / Send / Recv API를 제공한다.
 *  @see    [Tizen Native API](https://developer.tizen.org/development/api-references/native-application?redirect=https%3A//developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/index.html)
 */

#ifndef DIT_NFC_H
#define DIT_NFC_H

#include <stdbool.h>
#include <stdalign.h>

#include "dit.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! @fn         const char * NFCErrorChecker (int errCode)
 *  @brief      NFCErrorChecker API에서 발생하는 Error Code들을 확인 해준다.
 *  @param[in]  errCode 확인 하고자 하는 Error Code
 *  @param[out] null
 *  @retval     NFC_ERROR_NONE                  : Successful
 *  @retval     NFC_ERROR_OUT_OF_MEMORY         : Out of memory
 *  @retval     NFC_ERROR_OPERATION_FAILED      : Operation failed
 *  @retval     NFC_ERROR_INVALID_PARAMETER     : Invalid parameter
 *  @retval     NFC_ERROR_INVALID_NDEF_MESSAGE  : Invalid NDEF message
 *  @retval     NFC_ERROR_INVALID_RECORD_TYPE   : Invalid record type
 *  @retval     NFC_ERROR_TIMED_OUT             : Timeout error, no answer
 *  @retval     NFC_ERROR_DEVICE_BUSY           : Previous operation is not finished still busy
 *  @retval     NFC_ERROR_NO_DEVICE             : No device
 *  @retval     NFC_ERROR_NOT_ACTIVATED         : NFC is not activated
 *  @retval     NFC_ERROR_NOT_SUPPORTED         : Not supported
 *  @retval     NFC_ERROR_ALREADY_ACTIVATED     : Already activated
 *  @retval     NFC_ERROR_ALREADY_DEACTIVATED   : Already deactivated
 *  @retval     NFC_ERROR_READ_ONLY_NDEF        : Read only tag
 *  @retval     NFC_ERROR_NO_SPACE_ON_NDEF      : No enough space on tag
 *  @retval     NFC_ERROR_NO_NDEF_MESSAGE       : No NDEF Message on Tag
 *  @retval     NFC_ERROR_NOT_NDEF_FORMAT       : Not NDEF format Tag
 *  @retval     NFC_ERROR_SECURITY_RESTRICTED   : Restricted by access control
 *  @retval     NFC_ERROR_PERMISSION_DENIED     : Restricted by Smack
 *  @retval     NFC_ERROR_ILLEGAL_STATE         : The state is wrong
 *  @retval     NFC_ERROR_NOT_INITIALIZED       : NFC is not initialized
 *  @retval     NFC_ERROR_TAG_NOT_SUPPORTED     : Tag is not supported
 *  @retval     NFC_ERROR_UNKNOWN               : Unknown error occurred
 *  @note       NFC API에서 발생하는 Error Code들을 확인 해준다. \n
 *              Error의 내용은 Log를 통해 출력 된다. \n   
 *              23가지의 Error Code들을 확인 가능 하다.
 *  @see        [Tizen Native API Document - NFC part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__NETWORK__NFC__MANAGER__MODULE.html#ga32702c7145a8871aec23069f95c7d132)
 */
const char * NFCErrorChecker (int errorcode);


/* NDEF */
/*! @struct	NDEF
 *  @brief	NFC통신에 필요한 NDEF (NFC Data Exchange Format)에 대한 구조체이다.
 *  @note	NFC통신에 필요한 NDEF (NFC Data Exchange Format)에 대한 구조체이다. \n
    		구조체를 사용하기 전에 CreateNDEF() 함수를 사용해야 하며 사용이 끝났을 때 DeleteNDEF() 함수를 꼭 사용해야 한다.
 *  @see    [Tizen Native API Document - NDEF part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__NETWORK__NFC__NDEF__MODULE.html)
 *  @pre    @b feature \n
 *          * http://tizen.org/feature/network.nfc \n
 */
typedef struct NDEF
{
    String tag;
    String msg;

} NDEF;

/*!	@fn			NDEF CreateNDEF (String tag, String msg)
 *  @brief		새로운 Bluetooth 객체를 생성한다.
 *  @param[in]	tag NDEF에 저장 할 태그
 *  @param[in]	msg NDEF에 저장 할 메세지
 *  @param[out] null
 *  @retval 	NDEF
 *  @note 		새로운 NDEF 객체를 생성한다. \n
 *  			NDEF 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DeleteNDEF
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/network.nfc \n
 *  @warning    사용이 끝났을 때 DeleteNDEF() 함수를 꼭 사용해야 한다.
 */
NDEF CreateNDEF (String tag, String msg);

/*! @fn 		void DeleteNDEF (NDEF * ndef)
 *  @brief 		생성한 NDEF 객체를 소멸 시킨다.
 *  @param[in] 	ndef 소멸시킬 NDEF 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 NDEF 객체를 소멸 시킨다. \n
 *  			NDEF 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		CreateNDEF
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/network.nfc \n
 */
void DeleteNDEF (NDEF * ndef);
/* NDEF */


/* NFC */
/*! @struct _NFC
 *  @brief  NFC모듈에 대한 구조체이다.
 *  @note   NFC모듈에 대한 구조체이다. 구조체를 사용하기전에 NewNFC() 함수를 사용 해야 하며 사용이 끝났을 때 DestroyNFC()함수를 꼭 사용해야한다.
 *  @see    [Tizen Native API Document - NFC part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__NETWORK__NFC__MODULE.html)
 *  @pre    @b features \n
 *          * http://tizen.org/feature/network.nfc
 */
typedef struct _NFC * NFC;
struct _NFC
{
    bool (* isAccessible) (NFC this_gen);

    bool (* onConnect) (NFC this_gen);

    bool (* onDisconnect) (NFC this_gen);

    bool (* Send) (NFC this_gen, NDEF message);

    NDEF (* Recv) (NFC this_gen);
};

/*!	@fn			NFC NewNFC (void)
 *  @brief		새로운 NFC 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	NFC
 *  @note 		새로운 NFC 객체를 생성한다. \n
 *  			NFC 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyNFC \n
 *  			isNFCAccessible \n
 *  			onNFCConnect \n
 *  			onNFCDisconnect \n
 *  			NFCSend \n
 * 				NFCRecv
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/network.nfc
 *  @warning    사용이 끝났을 때 DestroyNFC()함수를 꼭 사용해야한다.
 *
 *  @code{.c}
NFC NewNFC (void)
{
    NFCExtends * this = (NFCExtends *)malloc (sizeof (NFCExtends));

    this->nfc.isAccessible = isNFCAccessible;
    this->nfc.onConnect    = onNFCConnect;
    this->nfc.onDisconnect = onNFCDisconnect;
    this->nfc.Send         = NFCSend;
    this->nfc.Recv         = NFCRecv;

    return &this->nfc;
}
 *	@endcode
 */
NFC NewNFC (void);

/*! @fn 		void DestroyNFC (NFC this_gen)
 *  @brief 		생성한 NFC 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 NFC 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 NFC 객체를 소멸 시킨다. \n
 *  			NFC 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewNFC
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/network.nfc
 */
void DestroyNFC (NFC this_gen);

/*! @fn 		bool isNFCAccessible (NFC this_gen)
 *  @brief 		현재 NFC 기능 지원 여부를 반환 한다.
 *  @param[in] 	this_gen 사용 가능 여부를 반환 할 NFC 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		현재 NFC 기능 지원 여부를 반환 한다. \n
 *  			지원 가능 이라면 @c true, 지원 가능이 아니라면 @c false를 반환한다.
 *  @see 		NewNFC \n
 *  			DestroyNFC \n
 *  			onNFCConnect \n
 *  			onNFCDisconnect \n
 *  			NFCSend \n
 * 				NFCRecv
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/network.nfc
 */
bool isNFCAccessible (NFC this_gen);

/*! @fn 		bool onNFCConnect (NFC this_gen)
 *  @brief 		NFC 장치 활성화를 시도하며 이의 성공 여부를 반환한다.
 *  @param[in] 	this_gen 활성화 성공 여부를 확인할 NFC 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		NFC 장치 활성화를 시도하며 이의 성공 여부를 반환한다. \n
 *  			연결에 성공하면 @c true, 실패하면 @c false를 반환한다.
 *  @see 		NewNFC \n
 *  			DestroyNFC \n
 *  			isNFCAccessible \n
 *  			onNFCDisconnect \n
 *  			NFCSend \n
 * 				NFCRecv
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/network.nfc
 */
bool onNFCConnect (NFC this_gen);

/*! @fn 		bool onNFCDisconnect (NFC this_gen)
 *  @brief 		NFC 장치 비활성화를 시도하며 이의 성공 여부를 반환한다.
 *  @param[in] 	this_gen 비활성화 성공 여부를 확인할 NFC 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		NFC 장치 비활성화를 시도하며 이의 성공 여부를 반환한다. \n
 *  			연결에 성공하면 @c true, 실패하면 @c false를 반환한다.
 *  @see 		NewNFC \n
 *  			DestroyNFC \n
 *  			isNFCAccessible \n
 *  			onNFCConnect \n
 *  			NFCSend \n
 * 				NFCRecv
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/network.nfc
 */
bool onNFCDisconnect (NFC this_gen);

/*! @fn 		void NFCSend (NFC this_gen, NDEF message)
 *  @brief 		NFC 장치에 생성한 NDEF를 기록한다.
 *  @param[in] 	this_gen NDEF를 기록할 NFC 객체
 *  @param[in] 	message 기록할 NDEF
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		NFC 장치에 생성한 NDEF를 기록한다.
 *  @see 		NewNFC \n
 *  			DestroyNFC \n
 *  			isNFCAccessible \n
 *  			onNFCConnect \n
 *  			onNFCDisconnect \n
 * 				NFCRecv
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/network.nfc
 */
bool NFCSend (NFC this_gen, NDEF message);

/*! @fn 		NDEF NFCRecv (NFC this_gen)
 *  @brief 		NFC 장치에서 NDEF를 읽어온다.
 *  @param[in] 	this_gen NDEF를 읽어 올 NFC 객체
 *  @param[out] null
 *  @retval 	NDEF
 *  @note 		NFC 장치에서 NDEF를 읽어온다.
 *  @see 		NewNFC \n
 *  			DestroyNFC \n
 *  			isNFCAccessible \n
 *  			onNFCConnect \n
 *  			onNFCDisconnect \n
 * 				NFCSend
 *  @pre        @b feature \n
 *              * http://tizen.org/feature/network.nfc
 */
NDEF NFCRecv (NFC this_gen);

typedef struct _NFCExtends
{
    struct _NFC nfc;
    NDEF        ndefMessage;
    bool        access;

} NFCExtends;
/* NFC */

#ifdef __cplusplus
}
#endif

#endif //DIT_NFC_H
