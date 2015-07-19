#ifndef DIT_NFC_H
#define DIT_NFC_H

#include <stdbool.h>
#include <stdalign.h>

#include "dit.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    String tag;
    String msg;

} NDEF;

NDEF CreateNDEF (String tag, String msg);

void DeleteNDEF (NDEF * ndef);

typedef struct _nfc * NFC;

/**
	@struct NFC
	@brief NFC모듈에 대한 구조체이다.
	@note NFC모듈에 대한 구조체이다. 구조체를 사용하기전에 newNFC() 함수를 사용을 해야 하며 사용이 끝났을 때 deleteNFC()함수를 꼭 사용해야한다.
	@see https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__NETWORK__NFC__MODULE.html
 	@todo features add "http://tizen.org/feature/network.nfc"
 */
struct _nfc
{
    bool (* isAccessible) (NFC this_gen);

    bool (* onConnect) (NFC this_gen);

    bool (* onDisconnect) (NFC this_gen);

    void (* Send) (NFC this_gen, NDEF message);

    NDEF (* Recv) (NFC this_gen);
};

NFC  newNFC (void);
void deleteNFC (NFC this_gen);
bool isNFCAccessible (NFC this_gen);
bool onNFCConnect (NFC this_gen);
bool onNFCDisconnect (NFC this_gen);
void NFCSend (NFC this_gen, NDEF message);
NDEF NFCRecv (NFC this_gen);

/**
	@struct NFCExtends
	@brief NFC확장모듈에 대한 구조체이다.
	@note NFC확모장듈에 대한 구조체이다. 구조체에 NDEF 메세지를 추가해서 사용한다. 메세지를 담당하는 함수들은 내부적으로 추가가 된다.
	@see https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__NETWORK__NFC__MODULE.html
 	@todo features add "http://tizen.org/feature/network.nfc"
 */
typedef struct
{
    struct _nfc nfc;
    NDEF        ndefMessage;
    bool        access;

} NFCExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_NFC_H
