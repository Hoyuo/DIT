#include "Commnucation/NFC.h"
#include <stdlib.h>
#include <nfc.h>
#include <app_control.h>
#include <string.h>

NDEF CreateNDEF(char* tag, char* msg) {
	NDEF ndef = { 0, 0 };
	ndef.tag = (char*) malloc(strlen(tag) + 1);
	strcpy(ndef.tag, tag);
	ndef.msg = (char*) malloc(strlen(msg) + 1);
	strcpy(ndef.msg, msg);
	return ndef;
}

void DeleteNDEF(NDEF* ndef) {
	free(ndef->tag);
	free(ndef->msg);
}

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
bool isNFCAccessible(NFC* this) {
	bool ret;
	system_info_get_platform_bool("http://tizen.org/feature/network.nfc", &ret);
	if (ret == true) {
		nfc_manager_set_tag_filter(NFC_TAG_FILTER_ALL_ENABLE);
	}
	((NFCExtends*) this)->access = ret;
	return ret;
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
bool onNFCConnect(NFC* this) {
	bool access = ((NFCExtends*) this)->access;
	bool ret = true;

	if (access == false) {
		int r;
		nfc_manager_initialize();
		nfc_manager_is_supported();

		//NFC 메니저 생성
		app_control_h service = NULL;
		app_control_create(&service);
		//app_control 생성
		app_control_set_operation(service,
				"http://tizen.org/appcontrol/operation/setting/nfc");
		app_control_add_extra_data(service, "type", "nfc");
		r = app_control_send_launch_request(service, NULL, NULL);
		//NFC 켜기
		if (r != APP_CONTROL_ERROR_NONE) {
			ret = false;
		}
		app_control_destroy(service);

		nfc_manager_set_tag_filter(NFC_TAG_FILTER_ALL_ENABLE);

		if (nfc_manager_is_system_handler_enabled() != true) {
			if (nfc_manager_set_system_handler_enable(true) == NFC_ERROR_NONE) {
				ret = true;
			} else {
				ret = false;
			}
		}
	}

	return ret;
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
bool onNFCDisconnect(NFC* this) {
	bool access = ((NFCExtends*) this)->access;
	bool ret = false;

	if (access == true) {
		nfc_manager_deinitialize();
		ret = true;
	}

	return ret;
}

/**
 @name NFCSend
 @brief
 @param[in]
 @param[out]
 @return
 @note
 @see
 @todo features add "http://tizen.org/feature/network.nfc" privilege add "http://tizen.org/privilege/nfc"
 */
void NFCSend(NFC* this, NDEF message) {
	bool access = ((NFCExtends*) this)->access;
	bool ret = true;

	if (access == true) {
		nfc_ndef_message_h ndef_message = NULL;
		nfc_ndef_message_create(&ndef_message);

		if (strcmp(message.tag, "TEXT") == 0) {
			nfc_ndef_record_create_text(&ndef_message, message.msg, "en-US",
					NFC_ENCODE_UTF_8);
		} else if (strcmp(message.tag, "URI") == 0) {
			nfc_ndef_record_create_uri(&ndef_message, message.msg);
		} else if (strcmp(message.tag, "MIME") == 0) {
			nfc_ndef_record_create_mime(&ndef_message, "image/jpeg",
					message.msg, sizeof(message.msg));
		} else {
			return;
		}

		nfc_tag_h tag;
		nfc_tag_write_ndef(tag, ndef_message, NULL, NULL);

		nfc_ndef_record_destroy(&ndef_message);
	}
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
void onNFCRecvData(nfc_ndef_message_h message, void* user_data) {
	int count, i;
	unsigned int size;
	unsigned char* payload;
	nfc_ndef_record_h record;

	nfc_ndef_message_get_record_count(message, &count);

	for (i = 0; i < count; i++) {
		nfc_ndef_message_get_record(message, i, &record);
		nfc_ndef_record_get_payload(record, &payload, &size);
	}
}

NDEF NFCRecv(NFC* this) {
	NDEF ret = { 0, 0 };
	bool access = ((NFCExtends*) this)->access;

	if (access == true) {
		nfc_tag_h tag;
		nfc_tag_read_ndef(tag, NULL, NULL);

		char tagChar[1000];
		int tagLength;
		//todo Correct
		nfc_ndef_record_get_type(NULL, &tagChar, &tagLength);
		ret.tag = (char*) malloc(tagLength + 1);
		strcpy(ret.tag, tagChar);

		char msgChar[1000];
		int msgLength;
		//todo Correct
		nfc_ndef_record_get_type(NULL, &msgChar, &msgLength);
		ret.tag = (char*) malloc(msgLength + 1);
		strcpy(ret.msg, msgChar);

	}
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
	if (this_gen != NULL) {
		NFCExtends* this = (NFCExtends*) this_gen;
		free(this);
	}
}
