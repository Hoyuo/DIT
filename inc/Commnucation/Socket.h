#ifndef DIT_SOCKET_H
#define DIT_SOCKET_H

#include <stdbool.h>
#include <stdalign.h>
#include <stddef.h>
#include <curl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Socket Socket;

typedef struct _Socket {
	bool (*isAccessible)(Socket* this_gen);

	bool (*onConnect)(Socket* this_gen, char* url, int port);

	bool (*onDisconnect)(Socket* this_gen);

	bool (*send)(Socket* this_gen, char* msg);

	bool (*recv)(Socket* this_gen, char* msg);

} Socket;

/*
 * @privlevel public
 * @privilege %http://tizen.org/privilege/internet
 */
Socket* NewSocket();

void DestorySocket(Socket* this_gen);

bool isSocketAccessible(Socket* this_gen);

bool onSocketConnect(Socket* this_gen, char* url, int port);

bool onSocketDisconnect(Socket* this_gen);

bool SocketMessageSend(Socket* this_gen, char* msg);

bool SocketMessageRecv(Socket* this_gen, char* msg);

typedef struct {
	Socket socket;
	char* url;
	int port;bool access;bool conect;
} SocketExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_SOCKET_H
