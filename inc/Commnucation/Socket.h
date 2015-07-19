#ifndef DIT_SOCKET_H
#define DIT_SOCKET_H

#include <stdbool.h>
#include <stdalign.h>
#include <stddef.h>

#include "dit.h"

#include <curl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Socket * Socket;

struct _Socket
{
    bool (* isAccessible) (Socket this_gen);

    bool (* onConnect) (Socket this_gen, String url, int port);

    bool (* onDisconnect) (Socket this_gen);

    bool (* Send) (Socket this_gen, String msg);

    bool (* Recv) (Socket this_gen, String msg);

};

/*
 * @privlevel public
 * @privilege %http://tizen.org/privilege/internet
 */
Socket NewSocket (void);
void   DestorySocket (Socket this_gen);
bool   isSocketAccessible (Socket this_gen);
bool   onSocketConnect (Socket this_gen, String url, int port);
bool   onSocketDisconnect (Socket this_gen);
bool   SocketMessageSend (Socket this_gen, String msg);
bool   SocketMessageRecv (Socket this_gen, String msg);

static int wait_on_socket (curl_socket_t sockfd, int for_recv, long timeout_ms);
const char * SocketErrorCheck (CURLcode errorCode);

typedef struct
{
    struct _Socket socket;
    String         url;
    int            port;
    bool           access;
    bool           conect;

} SocketExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_SOCKET_H
