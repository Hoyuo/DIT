/**
	@file CNFC.h
	@brief nfc모듈에 관한 파일
	@note TIZEN API nfc를 이용하여서 작성을 하였다. 간략화된 코드가 많기 때문에 좀 더 새부설정은 DIT Library보다는 TIZEN API를 참고하기 바란다.
	@see https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__NETWORK__NFC__MODULE.html
*/

#ifndef DIT_NFC_H
#define DIT_NFC_H
#include <stdbool.h>
#include <stdalign.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct { } NDEF;

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
}NFC;

NFC* newNFC();
void deleteNFC(NFC* this_gen);

bool isNFCAccessible(NFC * this);
bool onNFCConnect(NFC * this);
bool onNFCDisconnect(NFC * this);
void NFCSend(NFC* this, NDEF message);
NDEF NFCRecv(NFC * this);

/**
	@struct NFCExtends
	@brief NFC확장모듈에 대한 구조체이다.
	@note NFC확모장듈에 대한 구조체이다. 구조체에 NDEF 메세지를 추가해서 사용한다. 메세지를 담당하는 함수들은 내부적으로 추가가 된다.
	@see https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__NETWORK__NFC__MODULE.html
 	@todo features add "http://tizen.org/feature/network.nfc"
 */
typedef struct {
    NFC nfc;
	NDEF ndefMessage;
} NFCExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_NFC_H
