/**
 * This file contains the exported symbol.
 */
#include "dit.h"
#include <stdlib.h>
#include <nfc.h>

bool isNFCAccessible(NFC * this) {
	return false;
}

bool onNFCConnect(NFC * this) {
	return false;
}

bool onNFCDisconnect(NFC * this) {
	return false;
}

void NFCSend(NFC* this, NDEF message) {

}

NDEF NFCRecv(NFC* this) {
	NDEF ret;
	return ret;
}

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

void deleteNFC(NFC* this_gen) {
	NFCExtends* this = (NFCExtends *) this_gen;
	free(this);
}
