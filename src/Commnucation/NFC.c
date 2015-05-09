#include "Commnucation/NFC.h"
#include <stdlib.h>
#include <nfc.h>

/**
	@name isNFCAccessible
	@brief
	@param[in]
	@param[out]
	@return
	@note
	@see
 	@todo features add "http://tizen.org/feature/network.nfc"
 */
bool isNFCAccessible(NFC * this) {
    return false;
}

/**
	@name onNFCConnect
	@brief
	@param[in]
	@param[out]
	@return
	@note
	@see
 	@todo features add "http://tizen.org/feature/network.nfc"
 */
bool onNFCConnect(NFC * this) {
    return false;
}

/**
	@name onNFCDisconnect
	@brief
	@param[in]
	@param[out]
	@return
	@note
	@see
 	@todo features add "http://tizen.org/feature/network.nfc"
 */
bool onNFCDisconnect(NFC * this) {
    return false;
}

/**
	@name NFCSend
	@brief
	@param[in]
	@param[out]
	@return
	@note
	@see
 	@todo features add "http://tizen.org/feature/network.nfc"
 */
void NFCSend(NFC* this, NDEF message) {

}

/**
	@name NFCRecv
	@brief
	@param[in]
	@param[out]
	@return
	@note
	@see
 	@todo features add "http://tizen.org/feature/network.nfc"
 */
NDEF NFCRecv(NFC* this) {
    NDEF ret;
    return ret;
}

/**
	@name newNFC
	@brief NFC구조체를 사용하기 위해서 필수적으로 시작에 사용을 해야하는 함수이다.
	@param[in] NULL
	@param[out] NULL
	@return NFC pointer
	@note NFC구조체를 생성을 해주고, 기본적인 함수 연결과 변수들의 초기값을 설정한다.
	@see https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__NETWORK__NFC__MODULE.html
 	@todo features add "http://tizen.org/feature/network.nfc"
 */
NFC* newNFC() {
    NFCExtends* this;

    this = (NFCExtends*) malloc(sizeof(NFCExtends));

    this->nfc.isAccessible = isNFCAccessible;
    this->nfc.onConnect = onNFCConnect;
    this->nfc.onDisconnect = onNFCDisconnect;
    this->nfc.Send = NFCSend;
    this->nfc.Recv = NFCRecv;

    return &this->nfc;
}

/**
	@name deleteNFC
	@brief NFC구조체를 사용하고 마무리 하기 위해서 사용을 해야하는 함수이다. newNFC와 짝을 이루어서 반드시 사용해야한다.
	@param[in] NFC Module
	@param[out] NULL
	@return NULL
	@note NFC 구조체를 삭제 한다. NFC 사용 마무리시 반드시 해야한다.
	@see https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__NETWORK__NFC__MODULE.html
 	@todo features add "http://tizen.org/feature/network.nfc"
 */
void deleteNFC(NFC* this_gen) {
    if(this_gen != NULL) {
        NFCExtends* this = (NFCExtends*) this_gen;
        free(this);
    }
}
