/*! @file	Socket.h
 *  @brief	Socket API 를 사용하기 위해 포함해야 하는 헤더이다.
 *  @note	Socket의 isAccessible / onConnect  / Send / Recv API를 제공한다.
 *  @see    [Tizen Native API](https://developer.tizen.org/development/api-references/native-application?redirect=https%3A//developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/index.html)
 */

#ifndef DIT_SOCKET_H
#define DIT_SOCKET_H

#include <stdbool.h>
#include <stdalign.h>

#include "dit.h"

#include <curl.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! @fn 		const char * SocketErrorCheck (CURLcode errorCode)
 *  @brief 		Socket API에서 발생하는 Error Code들을 확인 해준다.
 *  @param[in] 	errCode 확인 하고자 하는 Error Code
 *  @param[out]	null
 *  @retval		CURLE_OK
 *  @retval		CURLE_UNSUPPORTED_PROTOCOL
 *  @retval		CURLE_FAILED_INIT
 *  @retval 	CURLE_URL_MALFORMAT
 *  @retval 	CURLE_NOT_BUILT_IN
 *  @retval 	CURLE_COULDNT_RESOLVE_PROXY
 *  @retval 	CURLE_COULDNT_RESOLVE_HOST
 *  @retval 	CURLE_COULDNT_CONNECT
 *  @retval 	CURLE_FTP_WEIRD_SERVER_REPLY
 *  @retval 	CURLE_REMOTE_ACCESS_DENIED		: A service was denied by the server due to lack of access - when login fails this is not returned.
 *  @retval 	CURLE_FTP_ACCEPT_FAILED
 *  @retval 	CURLE_FTP_WEIRD_PASS_REPLY
 *  @retval 	CURLE_FTP_ACCEPT_TIMEOUT		: Timeout occurred accepting server
 *  @retval 	CURLE_FTP_WEIRD_PASV_REPLY
 *  @retval 	CURLE_FTP_WEIRD_227_FORMAT
 *  @retval 	CURLE_FTP_CANT_GET_HOST
 *  @retval 	CURLE_FTP_COULDNT_SET_TYPE
 *  @retval 	CURLE_PARTIAL_FILE
 *  @retval 	CURLE_FTP_COULDNT_RETR_FILE
 *  @retval 	CURLE_QUOTE_ERROR  				: Quote command failure
 *  @retval 	CURLE_HTTP_RETURNED_ERROR
 *  @retval 	CURLE_WRITE_ERROR
 *  @retval 	CURLE_UPLOAD_FAILED				: Failed upload "command"
 *  @retval 	CURLE_READ_ERROR				: Couldn't open/read from file
 *  @retval 	CURLE_OUT_OF_MEMORY
 *  @retval 	CURLE_OPERATION_TIMEDOUT		: The timeout time was reached
 *  @retval 	CURLE_FTP_PORT_FAILED			: FTP PORT operation failed
 *  @retval 	CURLE_FTP_COULDNT_USE_REST		: The REST command failed
 *  @retval 	CURLE_RANGE_ERROR RANGE 		: Command" didn't work
 *  @retval 	CURLE_HTTP_POST_ERROR
 *  @retval 	CURLE_SSL_CONNECT_ERROR			: Wrong when connecting with SSL
 *  @retval 	CURLE_BAD_DOWNLOAD_RESUME		: Couldn't resume download
 *  @retval 	CURLE_FILE_COULDNT_READ_FILE
 *  @retval 	CURLE_LDAP_CANNOT_BIND
 *  @retval 	CURLE_LDAP_SEARCH_FAILED
 *  @retval 	CURLE_FUNCTION_NOT_FOUND
 *  @retval 	CURLE_ABORTED_BY_CALLBACK
 *  @retval 	CURLE_BAD_FUNCTION_ARGUMENT
 *  @retval 	CURLE_INTERFACE_FAILED
 *  @retval 	CURLE_TOO_MANY_REDIRECTS		: Catch endless re-direct loops
 *  @retval 	CURLE_UNKNOWN_OPTION			: User specified an unknown option
 *  @retval 	CURLE_TELNET_OPTION_SYNTAX		: Malformed telnet option
 *  @retval 	CURLE_PEER_FAILED_VERIFICATION	: Peer's certificate or finger print wasn't verified fine
 *  @retval 	CURLE_GOT_NOTHING				: When this is a specific error
 *  @retval 	CURLE_SSL_ENGINE_NOTFOUND		: SSL crypto engine not found
 *  @retval 	CURLE_SSL_ENGINE_SETFAILED		: Can not set SSL crypto engine as default
 *  @retval 	CURLE_SEND_ERROR				: Failed sending network data
 *  @retval 	CURLE_RECV_ERROR				: Failure in receiving network data
 *  @retval 	CURLE_SSL_CERTPROBLEM			: Problem with the local certificate
 *  @retval 	CURLE_SSL_CIPHER				: Couldn't use specified cipher
 *  @retval 	CURLE_SSL_CACERT				: Problem with the CA cert
 *  @retval 	CURLE_BAD_CONTENT_ENCODING		: Unrecognized/bad encoding
 *  @retval 	CURLE_LDAP_INVALID_URL			: Invalid LDAP URL
 *  @retval 	CURLE_FILESIZE_EXCEEDED			: Maximum file size exceeded
 *  @retval 	CURLE_USE_SSL_FAILED			: Requested FTP SSL level failed
 *  @retval 	CURLE_SEND_FAIL_REWIND			: Sending the data requires a rewind that failed
 *  @retval 	CURLE_SSL_ENGINE_INITFAILED		: Failed to initialize ENGINE
 *  @retval 	CURLE_LOGIN_DENIED				: User, password or similar was not accepted and we failed to login
 *  @retval 	CURLE_TFTP_NOTFOUND				: File not found on server
 *  @retval 	CURLE_TFTP_PERM					: Permission problem on server
 *  @retval 	CURLE_REMOTE_DISK_FULL			: Out of disk space on server
 *  @retval 	CURLE_TFTP_ILLEGAL				: Illegal TFTP operation
 *  @retval 	CURLE_TFTP_UNKNOWNID			: Unknown transfer ID
 *  @retval 	CURLE_REMOTE_FILE_EXISTS		: File already exists
 *  @retval 	CURLE_TFTP_NOSUCHUSER			: No such user
 *  @retval 	CURLE_CONV_FAILED				: Conversion failed
 *  @retval 	CURLE_CONV_REQD					: Caller must register conversion callbacks using curl_easy_setopt options.
 *  @retval 	CURLE_SSL_CACERT_BADFILE		: Could not load CACERT file, missing or wrong format
 *  @retval 	CURLE_REMOTE_FILE_NOT_FOUND		: Remote file not found
 *  @retval 	CURLE_SSH						: Error from the SSH layer, somewhat generic so the error message will be of interest when this has happened
 *  @retval 	CURLE_SSL_SHUTDOWN_FAILED		: Failed to shut down the SSL connection
 *  @retval 	CURLE_AGAIN						: Socket is not ready for send/recv wait till it's ready and try again
 *  @retval 	CURLE_SSL_CRL_BADFILE			: Could not load CRL file, missing or wrong format
 *  @retval 	CURLE_SSL_ISSUER_ERROR			: Issuer check failed
 *  @retval 	CURLE_FTP_PRET_FAILED			: A PRET command failed
 *  @retval 	CURLE_RTSP_CSEQ_ERROR			: Mismatch of RTSP CSeq numbers
 *  @retval 	CURLE_RTSP_SESSION_ERROR		: Mismatch of RTSP Session Ids
 *  @retval 	CURLE_FTP_BAD_FILE_LIST			: Unable to parse FTP file list
 *  @retval 	CURLE_CHUNK_FAILED				: Chunk callback reported error
 *  @retval 	CURL_LAST
 *  @note 		Socket API에서 발생하는 Error Code들을 확인 해준다. \n
 *              Error의 내용은 Log를 통해 출력 된다.   \n
 *  @see 		[Libcurl Error Document](http://curl.haxx.se/libcurl/c/libcurl-errors.html)
 */
const char * SocketErrorCheck (CURLcode errorCode);

/* Socket */
/*! @struct	_Socket
 *  @brief	Socket 모듈에 대한 구조체이다. Socket 모듈은 다양한 방식으로 Socket 통신을 할 수 있다.
 *  @note	Socket의 Socket 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewSocket() 함수를 사용해야 하며 사용이 끝났을 때 DestorySocket() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - CURL part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__OPENSRC__CURL__FRAMEWORK.html)
 *  @pre	@b privilege \n
 *          * http://tizen.org/privilege/internet
 */
typedef struct _Socket * Socket;
struct _Socket
{
    bool (* isAccessible) (Socket this_gen);

    bool (* onConnect) (Socket this_gen, String url, int port);

    bool (* onDisconnect) (Socket this_gen);

    bool (* Send) (Socket this_gen, String msg);

    bool (* Recv) (Socket this_gen, String * msg);

};

/*!	@fn			Socket NewSocket (void)
 *  @brief		새로운 Socket 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Socket
 *  @note 		새로운 Socket 객체를 생성한다. \n
 *  			Socket 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestorySocket \n
 *  			isSocketAccessible \n
 *  			onSocketConnect \n
 *  			onSocketDisconnect \n
 *  			SocketMessageSend \n
 *  			SocketMessageRecv
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/internet
 *  @warning    사용이 끝났을 때 DestorySocket() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
Socket NewSocket (void)
{
    SocketExtends * this = (SocketExtends *)malloc (sizeof (SocketExtends));

    this->socket.isAccessible = isSocketAccessible;
    this->socket.onConnect    = onSocketConnect;
    this->socket.onDisconnect = onSocketDisconnect;
    this->socket.Send         = SocketMessageSend;
    this->socket.Recv         = SocketMessageRecv;

    this->curl   = NULL;
    this->access = false;
    this->conect = false;

    return &this->socket;
}
 *	@endcode
 */
Socket NewSocket (void);

/*! @fn 		void DestorySocket (Socket this_gen)
 *  @brief 		생성한 Socket 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Socket 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Socket 객체를 소멸 시킨다. \n
 *  			Socket 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewSocket
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/internet
 */
void DestorySocket (Socket this_gen);

/*! @fn 		bool isSocketAccessible (Socket this_gen)
 *  @brief 		TCP/UDP 연결 지원 여부를 반환한다.
 *  @param[in] 	this_gen 지원 여부를 반환 할 Socket 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		TCP/UDP 연결 지원 여부를 반환한다. \n
 *  			지원 가능 시 @c true, 불가능 시 @c false를 반환한다.
 *  @see 		NewSocket \n
 *  			DestorySocket \n
 *  			onSocketConnect \n
 *  			onSocketDisconnect \n
 *  			SocketMessageSend \n
 *  			SocketMessageRecv
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/internet
 */
bool isSocketAccessible (Socket this_gen);

/*! @fn 		bool onSocketConnect (Socket this_gen, String url, int port)
 *  @brief 		TCP/UDP 로 연결을 시도하며 이의 성공 여부를 반환한다.
 *  @param[in] 	this_gen 연결 성공 여부를 확인할 Socket 객체
 *  @param[in] 	url 연결을 시도할 URL
 *  @param[in] 	port 연결을 시도할 포트 번호
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		TCP/UDP 로 연결을 시도하며 이의 성공 여부를 반환한다. \n
 *  			연결에 성공하면 @c true, 실패하면 @c false를 반환한다.
 *  @see 		NewSocket \n
 *  			DestorySocket \n
 *  			isSocketAccessible \n
 *  			onSocketDisconnect \n
 *  			SocketMessageSend \n
 *  			SocketMessageRecv
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/internet
 */
bool onSocketConnect (Socket this_gen, String url, int port);

/*! @fn 		bool onSocketDisconnect (Socket this_gen)
 *  @brief 		TCP/UDP 로 연결 해제하며 이의 성공 여부를 반환한다.
 *  @param[in] 	this_gen 연결 해제 여부를 확인할 Socket 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		TCP/UDP 로 연결을 제하며 이의 성공 여부를 반환한다. \n
 *  			연결 해제에 성공하면 @c true, 실패하면 @c false를 반환한다.
 *  @see 		NewSocket \n
 *  			DestorySocket \n
 *  			isSocketAccessible \n
 *  			onSocketConnect \n
 *  			SocketMessageSend \n
 *  			SocketMessageRecv
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/internet
 */
bool onSocketDisconnect (Socket this_gen);

/*! @fn 		bool SocketMessageSend (Socket this_gen, String msg)
 *  @brief 		TCP/UDP 연결로 데이터를 송신하며 이의 성공 여부를 반환한다.
 *  @param[in] 	this_gen 데이터를 송신할 Socket 객체
 *  @param[in] 	msg 송신할 데이터
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		TCP/UDP 연결로 데이터를 송신하며 이의 성공 여부를 반환한다. \n
 *  			송신에 성공하면 @c true, 실패하면 @c false를 반환한다.
 *  @see 		NewSocket \n
 *  			DestorySocket \n
 *  			isSocketAccessible \n
 *  			onSocketConnect \n
 *  			onSocketDisconnect \n
 *  			SocketMessageRecv
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/internet
 */
bool SocketMessageSend (Socket this_gen, String msg);

/*! @fn 		bool SocketMessageRecv (Socket this_gen, String* msg)
 *  @brief 		TCP/UDP 연결로 데이터를 수신하며 이의 성공 여부를 반환한다.
 *  @param[in] 	this_gen 데이터를 수신할 Socket 객체
 *  @param[in] 	msg 수신할 데이터를 저장할 주소
 *  @param[out] msg 수신한 데이터
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		TCP/UDP 연결로 데이터를 수신하며 이의 성공 여부를 반환한다. \n
 *  			수신에 성공하면 @c true, 실패하면 @c false를 반환한다.
 *  @see 		NewSocket \n
 *  			DestorySocket \n
 *  			isSocketAccessible \n
 *  			onSocketConnect \n
 *  			onSocketDisconnect \n
 *  			SocketMessageSend
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/internet
 */
bool SocketMessageRecv (Socket this_gen, String * msg);

typedef struct _SocketExtends
{
    struct _Socket socket;
    CURL *         curl;
    bool           access;
    bool           conect;

} SocketExtends;
/* Socket */

#ifdef __cplusplus
}
#endif

#endif //DIT_SOCKET_H
