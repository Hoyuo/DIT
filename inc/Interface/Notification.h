/*! @file	Notification.h
 *  @brief	Notification API 를 사용하기 위해 포함해야 하는 헤더이다.
 *  @note	Notification의 Show / Hide / setTitle / setText / setIcon / setSound / update Notification API를 제공한다.
 *  @see	https://developer.tizen.org/development/api-references/native-application?redirect=https%3A//developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/index.html
 */

#ifndef DIT_NOTIFICATION_H
#define DIT_NOTIFICATION_H

#include <stdbool.h>
#include <stdalign.h>

#include "dit.h"

#include <notification.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! @fn 		const char * NotificationErrorCheck (int errCode)
 *  @brief 		Notification API에서 발생하는 Error Code들을 확인 해준다.
 *  @param[in] 	errCode 확인 하고자 하는 Error Code
 *  @param[out]	null
 *  @retval 	NOTIFICATION_ERROR_NONE				 : Success
 *  @retval 	NOTIFICATION_ERROR_INVALID_PARAMETER : Invalid parameter
 *  @retval 	NOTIFICATION_ERROR_OUT_OF_MEMORY	 : Out of memory
 *  @retval 	NOTIFICATION_ERROR_IO_ERROR			 : I/O error
 *  @retval 	NOTIFICATION_ERROR_PERMISSION_DENIED : Permission denied
 *  @retval 	NOTIFICATION_ERROR_FROM_DB			 : Error from DB query
 *  @retval 	NOTIFICATION_ERROR_ALREADY_EXIST_ID	 : Already exist private ID
 *  @retval 	NOTIFICATION_ERROR_FROM_DBUS		 : Error from DBus
 * 	@retval		NOTIFICATION_ERROR_NOT_EXIST_ID		 : Not exist private ID
 *  @retval 	NOTIFICATION_ERROR_SERVICE_NOT_READY : No response from notification service
 *  @retval 	NOTIFICATION_ERROR_UNKNOWN			 : Unknown error occurred
 *  @note 		Notification API에서 발생하는 Error Code들을 확인 해준다. \n
 *  			11가지의 Error Code들을 확인 가능 하다.
 *  @see 		https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__NOTIFICATION__MODULE.html#gga59877a522577b6129d8a6175816a0867ace8d6426fa0e542f22d36e7b87bfe6c4
 */
const char * NotificationErrorCheck (int errCode);

/* Notification */
/*! @struct	_Notification
 *  @brief	Notification 모듈에 대한 구조체이다. Notification 모듈은 다양한 방식으로 알림을 설정 할 수 있다.
 *  @note	Notification 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewNotification() 함수를 사용해야 하며 사용이 끝났을 때 DestroyNotification() 함수를 꼭 사용해야 한다.
 *  @see	https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__NOTIFICATION__MODULE.html
 *  @todo	privilege에 "http://tizen.org/privilege/notification" 을 반드시 추가해야 한다.
 */
typedef struct _Notification * Notification;
struct _Notification
{
    void (* Show) (Notification this_gen);

    void (* Hide) (Notification this_gen);

    void (* setTitle) (Notification this_gen, String title);

    void (* setText) (Notification this_gen, String text);

    void (* setIcon) (Notification this_gen, String imagePath);

    void (* setSound) (Notification this_gen, String soundPath);

    void (* update) (Notification this_gen);
};

/*!	@fn			Notification NewNotification (void)
 *  @brief		새로운 Notification 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Notification
 *  @note 		새로운 Notification 객체를 생성한다. \n
 *  			Notification 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyNotification \n
 *  			NotificationShow \n
 *  			NotificationHide \n
 *  			setNotificationTitle \n
 *  			setNotificationText \n
 *  			setNotificationIcon \n
 *  			setNotificationSound \n
 *  			updateNotification
 *  @remark 	privilege	: http://tizen.org/privilege/notification
 */
Notification NewNotification (void);

/*! @fn 		void DestroyNotification (Notification this_gen)
 *  @brief 		생성한 Notification 객체를 소멸 시킨다.
 *  @param[in] 	this_gen 소멸시킬 Notification 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Notification 객체를 소멸 시킨다. \n
 *  			Notification 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewNotification
 *  @remark 	privilege	: http://tizen.org/privilege/notification
 */
void	DestroyNotification (Notification this_gen);

/*! @fn 		void NotificationShow (Notification this_gen)
 *  @brief 		생성한 Notification을 Notification 바에 등록한다.
 *  @param[in] 	this_gen Notification 바에 등록할 Notification 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Notification을 Notification 바에 등록한다. \n
 *  			이제 막 생성한 Notification은 Icon과 Sound 값에 기본 값이 설정되어 있지만 Title과 Text는 기본 값이 없기 때문에 \n
 *  			사용하기 전에 setNotificationTitle() 과 setNotificationText() 을 통해 설정을 미리 해야한다.
 *  @see 		NewNotification \n
 *  			DestroyNotification \n
 *  			NotificationHide \n
 *  			setNotificationTitle \n
 *  			setNotificationText \n
 *  			setNotificationIcon \n
 *  			setNotificationSound \n
 *  			updateNotification
 *  @remark 	privilege	: http://tizen.org/privilege/notification
 */
void	NotificationShow (Notification this_gen);

/*! @fn 		void NotificationHide (Notification this_gen)
 *  @brief 		Notification 바에 등록되어 있는 Notification을 삭제한다.
 *  @param[in] 	this_gen Notification 바에서 삭제할 Notification 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		NotificationShow()를 통해 Notification 바에 등록 되어 있는 Notification을 삭제한다.
 *  @see 		NewNotification \n
 *  			DestroyNotification \n
 *  			NotificationShow \n
 *  			setNotificationTitle \n
 *  			setNotificationIcon \n
 *  			setNotificationSound \n
 *  			updateNotification
 *  @remark 	privilege	: http://tizen.org/privilege/notification
 */
void	NotificationHide (Notification this_gen);

/*! @fn 		setNotificationTitle (Notification this_gen, String title)
 *  @brief 		Notification 객체의 title을 설정 한다.
 *  @param[in] 	this_gen title을 설정할 Notification 객체
 *  @param[in] 	title Notification의 title
 *  @param[out] null
 *  @retval 	void
 *  @note 		Notification 객체의 title을 설정 한다. \n
 *  			기본으로 설정된 값은 없다. \n
 *  			현재 Notification 바에 등록되어 있는 Notification이라면 updateNotification()를 통해 업데이트 해줘야 적용된다.
 *  @see 		NewNotification \n
 *   			DestroyNotification \n
 *  			NotificationShow \n
 *  			NotificationHide \n
 *  			setNotificationText \n
 *  			setNotificationIcon \n
 *  			setNotificationSound \n
 *  			updateNotification
 *  @remark 	privilege	: http://tizen.org/privilege/notification
 */
void	setNotificationTitle (Notification this_gen, String title);

/*! @fn 		setNotificationText (Notification this_gen, String text)
 *  @brief 		Notification 객체의 text를 설정 한다.
 *  @param[in] 	this_gen text를 설정할 Notification 객체
 *  @param[in] 	text Notification의 text
 *  @param[out] null
 *  @retval 	void
 *  @note 		Notification 객체의 text을 설정 한다. \n
 *  			기본으로 설정된 값은 없다. \n
 *  			현재 Notification 바에 등록되어 있는 Notification이라면 updateNotification()를 통해 업데이트 해줘야 적용된다.
 *  @see 		NewNotification \n
 *   			DestroyNotification \n
 *  			NotificationShow \n
 *  			NotificationHide \n
 *  			setNotificationTitle \n
 *  			setNotificationIcon \n
 *  			setNotificationSound \n
 *  			updateNotification
 *  @remark 	privilege	: http://tizen.org/privilege/notification
 */
void	setNotificationText (Notification this_gen, String text);

/*! @fn 		setNotificationIcon (Notification this_gen, String imagePath)
 *  @brief 		Notification 객체의 아이콘 이미지를 설정 한다.
 *  @param[in] 	this_gen image를 설정할 Notification 객체
 *  @param[in] 	imagePath Notification의 image 파일 경로
 *  @param[out] null
 *  @retval 	void
 *  @note 		Notification 객체의 아이콘 이미지를 설정 한다. \n
 *  			기본으로 설정된 값은 tizen logo이다. \n
 *  			현재 Notification 바에 등록되어 있는 Notification이라면 updateNotification()를 통해 업데이트 해줘야 적용된다.
 *  @see 		NewNotification \n
 *   			DestroyNotification \n
 *  			NotificationShow \n
 *  			NotificationHide \n
 *  			setNotificationTitle \n
 *  			setNotificationText \n
 *  			setNotificationSound \n
 *  			updateNotification
 *  @remark 	privilege	: http://tizen.org/privilege/notification
 */
void	setNotificationIcon (Notification this_gen, String imagePath);

/*! @fn 		setNotificationSound (Notification this_gen, String soundPath)
 *  @brief 		Notification 객체의 알림음을 설정 한다.
 *  @param[in] 	this_gen 알림음을 설정할 Notification 객체
 *  @param[in] 	soundPath Notification의 sound 파일 경로
 *  @param[out] null
 *  @retval 	void
 *  @note 		Notification 객체의 알림음을 설정 한다.\n
 *  			기본으로 설정된 값은 tizen 알림 기본음이다. \n
 *  			현재 Notification 바에 등록되어 있는 Notification이라면 updateNotification()를 통해 업데이트 해줘야 적용된다.
 *  @see 		NewNotification \n
 *   			DestroyNotification \n
 *  			NotificationShow \n
 *  			NotificationHide \n
 *  			setNotificationTitle \n
 *  			setNotificationText \n
 *  			setNotificationIcon \n
 *  			updateNotification
 *  @remark 	privilege	: http://tizen.org/privilege/notification
 */
void	setNotificationSound (Notification this_gen, String soundPath);

/*! @fn 		updateNotification (Notification this_gen)
 *  @brief 		새로 설정한 Notification 객체의 정보들을 새로 적용 한다.
 *  @param[in] 	this_gen 정보를 새로 적용 할 Notification 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		새로 설정한 Notification 객체의 정보들을 새로 적용 한다. \n
 *  			현재 Notification 바에 등록되어 있는 Notification의 정보를 갱신할 때 사용한다.
 *  @see 		NewNotification \n
 *   			DestroyNotification \n
 *  			NotificationShow \n
 *  			NotificationHide \n
 *  			setNotificationTitle \n
 *  			setNotificationText \n
 *  			setNotificationIcon \n
 *  			setNotificationSound
 *  @remark 	privilege	: http://tizen.org/privilege/notification
 */
void	updateNotification (Notification this_gen);

typedef struct
{
    struct _Notification notification;
    notification_h       notification_handle;
    String               title;
    String               text;
    String               imagePath;
    String               soundPath;
    bool                 visible;
} NotificationExtend;
/* Notification */

#ifdef __cplusplus
}
#endif

#endif //DIT_NOTIFICATION_H