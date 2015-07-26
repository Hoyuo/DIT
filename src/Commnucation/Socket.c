#include "Commnucation/Socket.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <curl.h>
#include <system_info.h>

static int wait_on_socket(curl_socket_t sockfd, int for_recv, long timeout_ms);

Socket NewSocket(void) {
	SocketExtends * this = (SocketExtends *) malloc(sizeof(SocketExtends));

	this->socket.isAccessible = isSocketAccessible;
	this->socket.onConnect = onSocketConnect;
	this->socket.onDisconnect = onSocketDisconnect;
	this->socket.Send = SocketMessageSend;
	this->socket.Recv = SocketMessageRecv;

	this->curl = NULL;
	this->access = false;
	this->conect = false;

	return &this->socket;
}

void DestorySocket(Socket this_gen) {
	if (this_gen != NULL) {
		SocketExtends * this = (SocketExtends *) this_gen;

		if (this->curl != NULL) {
			curl_easy_cleanup(this->curl);
		}

		free(this);
	}
}

bool isSocketAccessible(Socket this_gen) {
	if (this_gen != NULL) {
		SocketExtends * this = (SocketExtends *) this_gen;

		bool check1, check2;

		system_info_get_platform_bool("http://tizen.org/feature/network.wifi",
				&check1);
		system_info_get_platform_bool(
				"http://tizen.org/feature/network.telephony", &check2);

		this->access = check1 || check2;
		return this->access;
	}
	return false;
}

bool onSocketConnect(Socket this_gen, String url, int port) {
	if (this_gen != NULL) {
		SocketExtends * this = (SocketExtends *) this_gen;

		if (this->access) {
			CURLcode r;
			curl_global_init(CURL_GLOBAL_ALL);

			if (this->curl != NULL) {
				curl_easy_cleanup(this->curl);
				this->curl = NULL;
			}

			this->curl = curl_easy_init();
			if (this->curl) {
				curl_easy_setopt(this->curl, CURLOPT_URL, url);
				curl_easy_setopt(this->curl, CURLOPT_PORT, port);
				curl_easy_setopt(this->curl, CURLOPT_CONNECT_ONLY, 1L);

				r = curl_easy_perform(this->curl);

				if (r == CURLE_OK) {
					this->conect = true;
					return true;
				}
			}
		}
	}
	return false;
}

bool onSocketDisconnect(Socket this_gen) {
	if (this_gen != NULL) {
		SocketExtends * this = (SocketExtends *) this_gen;

		if (this->access) {
			if (this->curl != NULL) {
				curl_easy_cleanup(this->curl);
				this->curl = NULL;
			}

			this->conect = false;
			return true;
		}
	}
	return false;
}

bool SocketMessageSend(Socket this_gen, String msg) {
	if (this_gen != NULL) {
		SocketExtends * this = (SocketExtends *) this_gen;

		if (this->conect) {
			CURLcode res;

			size_t iolen = 0;

			res = curl_easy_send(this->curl, msg, strlen(msg) + 1, &iolen);

			if (res == CURLE_OK) {
				return true;
			}
		}
	}
	return false;
}

bool SocketMessageRecv(Socket this_gen, String* msg) {
	if (this_gen != NULL) {
		SocketExtends * this = (SocketExtends *) this_gen;

		if (this->conect) {
			CURLcode res;

				curl_socket_t sockfd;
				long sockextr;
				res = curl_easy_getinfo(this->curl, CURLINFO_LASTSOCKET, &sockextr);
				sockfd = sockextr;

				wait_on_socket(sockfd, 1, 10000L);

				char buf[1024];
				size_t iolen = 0;
				res = curl_easy_recv(this->curl, buf, 1024, &iolen);
				if (res) {
					return false;
				}

				*msg = (String) malloc(iolen + 1);
				strcpy(*msg, buf);

				return true;
			}
		}
		return false;

}

static int wait_on_socket(curl_socket_t sockfd, int for_recv, long timeout_ms) {
	struct timeval tv;
	fd_set infd, outfd, errfd;
	int res;

	tv.tv_sec = timeout_ms / 1000;
	tv.tv_usec = (timeout_ms % 1000) * 1000;

	FD_ZERO(&infd);
	FD_ZERO(&outfd);
	FD_ZERO(&errfd);

	FD_SET(sockfd, &errfd);

	if (for_recv) {
		FD_SET(sockfd, &infd);
	} else {
		FD_SET(sockfd, &outfd);
	}

	res = select(sockfd + 1, &infd, &outfd, &errfd, &tv);
	return res;
}

const char * SocketErrorCheck(CURLcode errorCode) {
	return curl_easy_strerror(errorCode);
}
