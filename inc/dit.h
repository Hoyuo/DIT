/**
	@file CNFC.h
	@brief nfc모듈에 관한 파일
	@note TIZEN API nfc를 이용하여서 작성을 하였다. 간략화된 코드가 많기 때문에 좀 더 새부설정은 DIT Library보다는 TIZEN API를 참고하기 바란다.
	@see https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__NETWORK__NFC__MODULE.html
*/

#ifndef _DIT_H_
#define _DIT_H_

/**
 * This header file is included to define _EXPORT_.
 */
#include <stdbool.h>
#include <stdalign.h>
// This method is exported from dit.so
typedef struct {

} NDEF;

typedef struct _nfc NFC;

/**
	@struct NFC
	@brief NFC모듈에 대한 구조체이다.
	@note NFC모듈에 대한 구조체이다. 구조체를 사용하기전에 newNFC() 함수를 사용을 해야 하며 사용이 끝났을 때 deleteNFC()함수를 꼭 사용해야한다.
	@see https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__NETWORK__NFC__MODULE.html
 	@todo features add "http://tizen.org/feature/network.nfc"
 */
typedef struct _nfc {

	bool (*isAccessible)(NFC* this);
	bool (*onConnect)(NFC* this);
	bool (*onDisconnect)(NFC* this);
	void (*Send)(NFC* this, NDEF message);
	NDEF (*Recv)(NFC* this);
} NFC;

bool isNFCAccessible(NFC * this);
bool onNFCConnect(NFC * this);
bool onNFCDisconnect(NFC * this);
void NFCSend(NFC* this, NDEF message);
NDEF NFCRecv(NFC * this);

typedef struct {
	NFC nfc;

	NDEF ndefMessage;
} NFCExtends;

/*
	@name newNFC
	@brief NFC구조체를 사용하기 위해서 필수적으로 시작에 사용을 해야하는 함수이다.
	@param[in] NULL
	@param[out] NULL
	@return NFC pointer
	@note NFC구조체를 생성을 해주고, 기본적인 함수 연결과 변수들의 초기값을 설정한다.
	@see https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__NETWORK__NFC__MODULE.html
 	@todo features add "http://tizen.org/feature/network.nfc"
 *
 */
NFC* newNFC();
void deleteNFC(NFC* this_gen);

#endif // _DIT_H_
