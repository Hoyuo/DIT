/*! @file	Http.h
 *  @brief	HTTP API 를 사용하기 위해 포함해야 하는 헤더이다.
 *  @note	HTTP의 isAccessible / onConnect / onDisconnect / Download / Post / Get API를 제공한다.
 *  @see    [Tizen Native API](https://developer.tizen.org/development/api-references/native-application?redirect=https%3A//developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/index.html)
 */

#ifndef DIT_HTTP_H
#define DIT_HTTP_H

#include <stdbool.h>
#include <stdalign.h>

#include "dit.h"

#include <curl.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! @fn 		const char * HttpErrorCheck (CURLcode errorCode)
 *  @brief 		Http API에서 발생하는 Error Code들을 확인 해준다.
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
 *  @note 		Http API에서 발생하는 Error Code들을 확인 해준다. \n
 *              Error의 내용은 Log를 통해 출력 된다.
 *  @see 		[Libcurl Error Document](http://curl.haxx.se/libcurl/c/libcurl-errors.html)
 */
const char * HttpErrorCheck (CURLcode errorCode);

/* Http */
/*! @struct	_Http
 *  @brief	Http 모듈에 대한 구조체이다. Http 모듈은 다양한 방식으로 Http 통신을 할 수 있다.
 *  @note	Http의 Http 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewHttp() 함수를 사용해야 하며 사용이 끝났을 때 DestoryHttp() 함수를 꼭 사용해야 한다.
 *  @see    [Tizen Native API Document - HTTP part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__OPENSRC__CURL__FRAMEWORK.html)
 *  @pre	@b privilege \n
 *          * http://tizen.org/privilege/internet
 */
typedef struct _Http * Http;
struct _Http
{
    bool (* isAccessible) (Http this_gen);

    bool (* onConnect) (Http this_gen, String url, int port);

    bool (* onDisconnect) (Http this_gen);

    bool (* Download) (Http this_gen, String filename);

    bool (* Post) (Http this_gen, String res, String * req);

    bool (* Get) (Http this_gen, String res, String * req);

};

/*!	@fn			Http NewHttp (void)
 *  @brief		새로운 Http 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Http
 *  @note 		새로운 Http 객체를 생성한다. \n
 *  			Http 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestoryHttp \n
 *  			isHttpAccessible \n
 *  			onHttpConnect \n
 *  			onHttpDisconnect \n
 *  			HttpDownload \n
 *  			HttpExcutePost \n
 * 				HttpExcuteGet
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/internet
 *  @warning    사용이 끝났을 때 DestoryHttp() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
Http NewHttp (void)
{
    HttpExtends * this = (HttpExtends *)malloc (sizeof (HttpExtends));

    this->http.isAccessible = isHttpAccessible;
    this->http.onConnect    = onHttpConnect;
    this->http.onDisconnect = onHttpDisconnect;
    this->http.Download     = HttpDownload;
    this->http.Get          = HttpExcuteGet;
    this->http.Post         = HttpExcutePost;

    this->url  = NULL;
    this->port = 80;

    this->access = false;
    this->conect = false;

    return &this->http;
}
 *	@endcode
 */
Http NewHttp (void);

/*! @fn 		void DestoryHttp (Http this_gen)
 *  @brief 		생성한 Http 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Http 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Http 객체를 소멸 시킨다. \n
 *  			Http 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewHttp
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/internet
 */
void DestoryHttp (Http this_gen);

/*! @fn 		bool isHttpAccessible (Http this_gen)
 *  @brief 		현재 Http 기능 지원 여부를 반환 한다.
 *  @param[in] 	this_gen 사용 가능 여부를 반환 할 Http 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		현재 Http 기능 지원 여부를 반환 한다. \n
 *  			지원 가능 이라면 @c true, 지원 가능이 아니라면 @c false를 반환한다.
 *  @see 		NewHttp \n
 *  			DestoryHttp \n
 *  			onHttpConnect \n
 *  			onHttpDisconnect \n
 *  			HttpDownload \n
 *  			HttpExcutePost \n
 * 				HttpExcuteGet
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/internet
 */
bool isHttpAccessible (Http this_gen);

/*! @fn 		bool onHttpConnect (Http this_gen, String url, int port)
 *  @brief 		Http로 연결을 시도하며 이의 성공 여부를 반환한다.
 *  @param[in] 	this_gen 연결 성공 여부를 확인할 Http 객체
 *  @param[in] 	url 연결을 시도할 URL
 *  @param[in] 	port 연결을 시도할 포트 번호
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Http로 연결을 시도하며 이의 성공 여부를 반환한다. \n
 *  			연결에 성공하면 @c true, 실패하면 @c false를 반환한다.
 *  @see 		NewHttp \n
 *  			DestoryHttp \n
 *  			isHttpAccessible \n
 *  			onHttpDisconnect \n
 *  			HttpDownload \n
 *  			HttpExcutePost \n
 * 				HttpExcuteGet
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/internet
 */
bool onHttpConnect (Http this_gen, String url, int port);

/*! @fn 		bool onHttpDisconnect (Http this_gen)
 *  @brief 		Http로의 연결을 해제하며 이의 성공 여부를 반환한다.
 *  @param[in] 	this_gen 연결 해제 여부를 확인할 Http 객체
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Http기기로 연결을 해제하며 이의 성공 여부를 반환한다. \n
 *  			연결 해제에 성공하면 @c true, 실패하면 @c false를 반환한다.
 *  @see 		NewHttp \n
 *  			DestoryHttp \n
 *  			isHttpAccessible \n
 *  			onHttpConnect \n
 *  			HttpDownload \n
 *  			HttpExcutePost \n
 * 				HttpExcuteGet
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/internet
 */
bool onHttpDisconnect (Http this_gen);

/*! @fn 		bool HttpDownload (Http this_gen, String filename)
 *  @brief 		Http로부터 데이터를 수신 받는다.
 *  @param[in] 	this_gen 데이터를 수신 받을 Http 객체
 *  @param[in] 	filename 수신 받을 데이터 파일 이름
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		Http로부터 데이터를 수신 받는다. \n
 *  @see 		NewHttp \n
 *  			DestoryHttp \n
 *  			isHttpAccessible \n
 *  			onHttpConnect \n
 *  			onHttpDisconnect \n
 *  			HttpExcutePost \n
 * 				HttpExcuteGet
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/internet \n
 *              * http://tizne.org/privileges/mediastorage \n
 *              * http://tizne.org/privileges/download
 */
bool HttpDownload (Http this_gen, String filename);

/*! @fn 		bool HttpExcutePost (Http this_gen, String req, String * res)
 *  @brief 		@b POST 방식을 사용하여 연결된 세션으로 @c req와 @c res를 입력해서 결과를 @c res로 받는다.
 *  @param[in] 	this_gen 연결된 세션의 Http 객체
 *  @param[in] 	req 요청을 하는 request buffer
 *  @param[in] 	res 결과를 받을 response buffer 주소
 *  @param[out] res 요청에 따른 결과 값
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		@b POST 방식을 사용하여 연결된 세션으로 @c req와 @c res를 입력해서 결과를 @c res로 받는다. \n
 *  @see 		NewHttp \n
 *  			DestoryHttp \n
 *  			isHttpAccessible \n
 *  			onHttpConnect \n
 *  			onHttpDisconnect \n
 *  			HttpDownload \n
 * 				HttpExcuteGet
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/internet
 */
bool HttpExcutePost (Http this_gen, String req, String * res);

/*! @fn 		bool HttpExcuteGet (Http this_gen, String req, String * res)
 *  @brief 		@b GET 방식을 사용하여 연결된 세션으로 @c req와 @c res를 입력해서 결과를 @c res로 받는다.
 *  @param[in] 	this_gen 연결된 세션의 Http 객체
 *  @param[in] 	req 요청을 하는 request buffer
 *  @param[in] 	res 결과를 받을 response buffer 주소
 *  @param[out] res 요청에 따른 결과 값
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		@b GET 방식을 사용하여 연결된 세션으로 @c req와 @c res를 입력해서 결과를 @c res로 받는다. \n
 *  @see 		NewHttp \n
 *  			DestoryHttp \n
 *  			isHttpAccessible \n
 *  			onHttpConnect \n
 *  			onHttpDisconnect \n
 *  			HttpDownload \n
 * 				HttpExcutePost
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/internet
 */
bool HttpExcuteGet (Http this_gen, String req, String * res);

typedef struct _HttpExtends
{
    struct _Http http;
    String       url;
    int          port;
    bool         access;
    bool         conect;

} HttpExtends;
/* Http */

#ifdef __cplusplus
}
#endif

#endif //DIT_HTTP_H
