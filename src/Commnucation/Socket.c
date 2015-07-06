#include "Commnucation/Socket.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <curl.h>
#include <system_info.h>

Socket* NewSocket() {
	SocketExtends* this = (SocketExtends*) malloc(sizeof(SocketExtends));

	this->socket.isAccessible = isSocketAccessible;
	this->socket.onConnect = onSocketConnect;
	this->socket.onDisconnect = onSocketDisconnect;
	this->socket.send = SocketMessageSend;
	this->socket.recv = SocketMessageRecv;

	this->url = NULL;
	this->port = 3000;

	this->access = false;
	this->conect = false;

	return &this->socket;
}

void DestorySocket(Socket* this_gen) {
	if (this_gen != NULL) {
		SocketExtends* this = (SocketExtends*) this_gen;

		if (this->url != NULL)
			free(this->url);

		free(this);
	}
}

bool isSocketAccessible(Socket* this_gen) {
	SocketExtends* this = (SocketExtends*) this_gen;
	bool check1, check2;

	system_info_get_platform_bool("http://tizen.org/feature/network.wifi",
			&check1);
	system_info_get_platform_bool("http://tizen.org/feature/network.telephony",
			&check2);

	this->access = check1 || check2;
	return this->access;
}

bool onSocketConnect(Socket* this_gen, char* url, int port) {
	SocketExtends* this = (SocketExtends*) this_gen;
}

bool onSocketDisconnect(Socket* this_gen) {
	SocketExtends* this = (SocketExtends*) this_gen;

	if (this->access) {
		if (this->url != NULL) {
			free(this->url);
			this->url = NULL;
		}

		this->conect = false;
		return true;
	} else {
		return false;
	}
}
