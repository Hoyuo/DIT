/*! @file   OngoingNotification.h
 *  @brief	Ongoing Notification API 를 사용하기 위해 포함해야 하는 헤더이다.
 *  @note	  Ongoing Notification의 Show / Hide / setTitle / setText / setIcon / setSound / setProgress / update Notification API를 제공한다.
 *  @see    [Tizen Native API](https://developer.tizen.org/development/api-references/native-application?redirect=https%3A//developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/index.html)
 */

#ifndef DIT_ONGOINGNOTIFICATION_H
#define DIT_ONGOINGNOTIFICATION_H

#include <stdbool.h>
#include <stdalign.h>

#include "dit.h"

#include <notification.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! @fn         const char * OngoingNotificationErrorCheck (int errCode)
 *  @brief      Ongoing Notification API에서 발생하는 Error Code들을 확인 해준다.
 *  @param[in]  errCode 확인 하고자 하는 Error Code
 *  @param[out] null
 *  @retval     NOTIFICATION_ERROR_NONE				 : Success
 *  @retval     NOTIFICATION_ERROR_INVALID_PARAMETER : Invalid parameter
 *  @retval     NOTIFICATION_ERROR_OUT_OF_MEMORY	 : Out of memory
 *  @retval     NOTIFICATION_ERROR_IO_ERROR			 : I/O error
 *  @retval     NOTIFICATION_ERROR_PERMISSION_DENIED : Permission denied
 *  @retval     NOTIFICATION_ERROR_FROM_DB			 : Error from DB query
 *  @retval     NOTIFICATION_ERROR_ALREADY_EXIST_ID	 : Already exist private ID
 *  @retval     NOTIFICATION_ERROR_FROM_DBUS		 : Error from DBus
 * 	@retval     NOTIFICATION_ERROR_NOT_EXIST_ID		 : Not exist private ID
 *  @retval     NOTIFICATION_ERROR_SERVICE_NOT_READY : No response from notification service
 *  @retval     NOTIFICATION_ERROR_UNKNOWN			 : Unknown error occurred
 *  @note 		  Ongoing Notification API에서 발생하는 Error Code들을 확인 해준다. \n
 *              Error의 내용은 Log를 통해 출력 된다.    \n
 *         			11가지의 Error Code들을 확인 가능 하다.
 *  @see        [Tizen Native API Document - Notification part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__NOTIFICATION__MODULE.html)
 */
const char * OngoingNotificationErrorCheck (int errCode);

/* Ongoing Notification */
/*! @struct	_OngoingNotification
 *  @brief  OngoingNotification 모듈에 대한 구조체이다. OngoingNotification 모듈은 다양한 방식으로 알림을 설정 할 수 있다.
 *  @note	  OngoingNotification 모듈에 대한 구조체이다. \n
    		    구조체를 사용하기 전에 NewOngoingNotification() 함수를 사용해야 하며 사용이 끝났을 때 DestroyOngoingNotification() 함수를 꼭 사용해야 한다.
 *  @see    [Tizen Native API Document - Notification part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__NOTIFICATION__MODULE.html)
 *  @pre    @b privilege \n
 *          * http://tizen.org/privilege/notification
 */
typedef struct _OngoingNotification * OngoingNotification;
struct _OngoingNotification
{
    bool (* Show) (OngoingNotification this_gen);

    bool (* Hide) (OngoingNotification this_gen);

    bool (* setTitle) (OngoingNotification this_gen, String title);

    bool (* setText) (OngoingNotification this_gen, String text);

    bool (* setIcon) (OngoingNotification this_gen, String imagePath);

    bool (* setSound) (OngoingNotification this_gen, String soundPath);

    bool (* setProgress) (OngoingNotification this_gen, double progress);

    bool (* update) (OngoingNotification this_gen);
};

/*!	@fn         OngoingNotification NewOngoingNotification (void)
 *  @brief      새로운 OngoingNotification 객체를 생성한다.
 *  @param[in]  void
 *  @param[out] null
 *  @retval     OngoingNotification
 *  @note       새로운 OngoingNotification 객체를 생성한다. \n
 *              OngoingNotification 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see        DestroyOngoingNotification \n
 *         			OngoingNotificationShow \n
 *  	       		OngoingNotificationHide \n
 *        			setOngoingNotificationTitle \n
 *        			setOngoingNotificationText \n
 *  	       		setOngoingNotificationIcon \n
 *        			setOngoingNotificationSound \n
 *        			setOngoingNotificationProgress \n
 *        			updateOngoingNotification
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/notification
 *  @warning    사용이 끝났을 때 DestroyOngoingNotification() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
OngoingNotification NewOngoingNotification (void)
{
    OngoingNotificationExtend * this;

    this = (OngoingNotificationExtend *)malloc (sizeof (OngoingNotificationExtend));

    this->Ongoingnotification.Show        = OngoingNotificationShow;
    this->Ongoingnotification.Hide        = OngoingNotificationHide;
    this->Ongoingnotification.setTitle    = setOngoingNotificationTitle;
    this->Ongoingnotification.setText     = setOngoingNotificationText;
    this->Ongoingnotification.setIcon     = setOngoingNotificationIcon;
    this->Ongoingnotification.setSound    = setOngoingNotificationSound;
    this->Ongoingnotification.setProgress = setOngoingNotificationProgress;
    this->Ongoingnotification.update      = updateOngoingNotification;

    this->ongoingnotification_handle = notification_create (NOTIFICATION_TYPE_ONGOING);
    this->title                      = NULL;
    this->text                       = NULL;
    this->imagePath                  = NULL;
    this->soundPath                  = NULL;
    this->visible                    = false;

    notification_set_display_applist (this->ongoingnotification_handle, NOTIFICATION_DISPLAY_APP_NOTIFICATION_TRAY | NOTIFICATION_DISPLAY_APP_TICKER);

    return &this->Ongoingnotification;
}
 *	@endcode
 */
OngoingNotification NewOngoingNotification (void);

/*! @fn         void DestroyOngoingNotification (OngoingNotification this_gen)
 *  @brief      생성한 OngoingNotification 객체를 소멸 시킨다.
 *  @param[in]  this_gen 소멸시킬 OngoingNotification 객체
 *  @param[out] null
 *  @retval     void
 *  @note       생성한 OngoingNotification 객체를 소멸 시킨다. \n
 *              OngoingNotification 객체를 사용한 후 반드시 호출해야 한다.
 *  @see        NewOngoingNotification
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/notification
 */
void DestroyOngoingNotification (OngoingNotification this_gen);

/*! @fn         bool OngoingNotificationShow (OngoingNotification this_gen)
 *  @brief      생성한 OngoingNotification을 Notification 바에 등록한다.
 *  @param[in]  this_gen Notification 바에 등록할 OngoingNotification 객체
 *  @param[out] null
 *  @retval     bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note       생성한 OngoingNotification을 Notification 바에 등록한다.  
 *  @see        NewOngoingNotification \n
 *  	       		DestroyOngoingNotification \n
 *              OngoingNotificationHide \n
 *              setOngoingNotificationTitle \n
 *              setOngoingNotificationText \n
 *              setOngoingNotificationIcon \n
 *              setOngoingNotificationSound \n
 *              setOngoingNotificationProgress \n
 *              updateOngoingNotification
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/notification
 *  @warning    이제 막 생성한 OngoingNotification은 Icon과 Sound 값에 기본 값이 설정되어 있지만 Title과 Text는 기본 값이 없기 때문에 \n
 *              사용하기 전에 setOngoingNotificationTitle() 과 setOngoingNotificationText() 을 통해 설정을 미리 해야한다.
 */
bool OngoingNotificationShow (OngoingNotification this_gen);

/*! @fn         bool OngoingNotificationHide (OngoingNotification this_gen)
 *  @brief      Notification 바에 등록되어 있는 OngoingNotification을 삭제한다.
 *  @param[in] 	this_gen Notification 바에서 삭제할 OngoingNotification 객체
 *  @param[out] null
 *  @retval     bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note       OngoingNotificationShow()를 통해 Notification 바에 등록 되어 있는 OngoingNotification을 삭제한다.
 *  @see        NewOngoingNotification \n
 *              DestroyOngoingNotification \n
 *              OngoingNotificationShow \n
 *              setOngoingNotificationTitle \n
 *              setOngoingNotificationText \n
 *              setOngoingNotificationIcon \n
 *              setOngoingNotificationSound \n
 *              setOngoingNotificationProgress \n
 *              updateOngoingNotification
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/notification
 */
bool OngoingNotificationHide (OngoingNotification this_gen);

/*! @fn         bool setOngoingNotificationTitle (OngoingNotification this_gen, String title)
 *  @brief      OngoingNotification 객체의 title을 설정 한다.
 *  @param[in] 	this_gen title을 설정할 OngoingNotification 객체
 *  @param[in] 	title OngoingNotification의 title
 *  @param[out] null
 *  @retval     bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note       OngoingNotification 객체의 @a title을 설정 한다. \n
 *         			기본으로 설정된 값은 없다. \n
 *  	       		현재 Notification 바에 등록되어 있는 OngoingNotification이라면 updateOngoingNotification()를 통해 업데이트 해야 적용된다.
 *  @see    		NewOngoingNotification \n
 *        			DestroyOngoingNotification \n
 *         			OngoingNotificationShow \n
 *         			OngoingNotificationHide \n
 *         			setOngoingNotificationText \n
 *        			setOngoingNotificationIcon \n
 *        			setOngoingNotificationSound \n
 *         			setOngoingNotificationProgress \n
 *         			updateOngoingNotification
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/notification
 */
bool setOngoingNotificationTitle (OngoingNotification this_gen, String title);

/*! @fn         bool setOngoingNotificationText (OngoingNotification this_gen, String text)
 *  @brief    	OngoingNotification 객체의 text를 설정 한다.
 *  @param[in] 	this_gen text를 설정할 OngoingNotification 객체
 *  @param[in] 	text OngoingNotification의 text
 *  @param[out] null
 *  @retval    	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note   		OngoingNotification 객체의 @a text을 설정 한다. \n
 *  	       		기본으로 설정된 값은 없다. \n
 *  	       		현재 Notification 바에 등록되어 있는 OngoingNotification이라면 updateOngoingNotification()를 통해 업데이트 해야 적용된다.
 *  @see    		NewOngoingNotification \n
 *         			DestroyOngoingNotification \n
 *         			OngoingNotificationShow \n
 *         			OngoingNotificationHide \n
 *         			setOngoingNotificationTitle \n
 *         			setOngoingNotificationIcon \n
 *         			setOngoingNotificationSound \n
 *         			setOngoingNotificationProgress \n
 *         			updateOngoingNotification
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/notification
 */
bool setOngoingNotificationText (OngoingNotification this_gen, String text);

/*! @fn         bool setOngoingNotificationIcon (OngoingNotification this_gen, String imagePath)
 *  @brief      OngoingNotification 객체의 아이콘 이미지를 설정 한다.
 *  @param[in] 	this_gen image를 설정할 OngoingNotification 객체
 *  @param[in] 	imagePath OngoingNotification의 image 파일 경로
 *  @param[out] null
 *  @retval   	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note     	OngoingNotification 객체의 아이콘 이미지를 설정 한다. \n
 *  	       		기본으로 설정된 값은 tizen logo이다. \n
 *        			현재 Notification 바에 등록되어 있는 OngoingNotification이라면 updateOngoingNotification()를 통해 업데이트 해야 적용된다.
 *  @see 	    	NewOngoingNotification \n
 *        			DestroyOngoingNotification \n
 *         			OngoingNotificationShow \n
 *         			OngoingNotificationHide \n
 *         			setOngoingNotificationTitle \n
 *         			setOngoingNotificationText \n
 *         			setOngoingNotificationSound \n
 *         			setOngoingNotificationProgress \n
 *         			updateOngoingNotification
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/notification
 */
bool setOngoingNotificationIcon (OngoingNotification this_gen, String imagePath);

/*! @fn         bool setOngoingNotificationSound (OngoingNotification this_gen, String soundPath)
 *  @brief  		OngoingNotification 객체의 알림음을 설정 한다.
 *  @param[in] 	this_gen 알림음을 설정할 OngoingNotification 객체
 *  @param[in] 	soundPath OngoingNotification의 sound 파일 경로
 *  @param[out] null
 *  @retval   	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note   		OngoingNotification 객체의 알림음을 설정 한다.\n
 *        			기본으로 설정된 값은 tizen 알림 기본음이다. \n
 *        			현재 Notification 바에 등록되어 있는 OngoingNotification이라면 updateOngoingNotification()를 통해 업데이트 해야 적용된다.
 *  @see    		NewOngoingNotification \n
 *         			DestroyOngoingNotification \n
 *         			OngoingNotificationShow \n
 *         			OngoingNotificationHide \n
 *         			setOngoingNotificationTitle \n
 *         			setOngoingNotificationText \n
 *         			setOngoingNotificationIcon \n
 *         			setOngoingNotificationProgress \n
 *         			updateOngoingNotification
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/notification
 */
bool setOngoingNotificationSound (OngoingNotification this_gen, String soundPath);

/*! @fn         bool setOngoingNotificationProgress (OngoingNotification this_gen, double progress)
 *  @brief  		OngoingNotification 객체의 진행률을 설정 한다.
 *  @param[in] 	this_gen 진행률을 설정할 OngoingNotification 객체
 *  @param[in] 	progress OngoingNotification의 진행률 (0.0 ~ 1.0)
 *  @param[out] null
 *  @retval   	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note   		OngoingNotification 객체의 진행률을 설정 한다.\n
 *        			@a progress은 @a 0.0 ~ @a 1.0의 값을 가진다. \n
 *        			현재 Notification 바에 등록되어 있는 OngoingNotification이라면 updateOngoingNotification()를 통해 업데이트 해야 적용된다.
 *  @see    		NewOngoingNotification \n
 *        			DestroyOngoingNotification \n
 *         			OngoingNotificationShow \n
 *         			OngoingNotificationHide \n
 *         			setOngoingNotificationTitle \n
 *         			setOngoingNotificationText \n
 *        			setOngoingNotificationIcon \n
 *         			setOngoingNotificationSound \n
 *         			updateOngoingNotification
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/notification
 */
bool setOngoingNotificationProgress (OngoingNotification this_gen, double progress);

/*! @fn     		bool updateOngoingNotification (OngoingNotification this_gen)
 *  @brief  		새로 설정한 OngoingNotification 객체의 정보들을 새로 적용 한다.
 *  @param[in] 	this_gen 정보를 새로 적용 할 OngoingNotsification 객체
 *  @param[out] null
 *  @retval   	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note   		새로 설정한 OngoingNotification 객체의 정보들을 새로 적용 한다. \n
 *  	       		현재 Notification 바에 등록되어 있는 OngoingNotification의 정보를 갱신할 때 사용한다.
 *  @see    		NewOngoingNotification \n
 *         			DestroyOngoingNotification \n
 *         			OngoingNotificationShow \n
 *         			OngoingNotificationHide \n
 *         			setOngoingNotificationTitle \n
 *         			setOngoingNotificationText \n
 *         			setOngoingNotificationIcon \n
 *         			setOngoingNotificationSound \n
 *         			setOngoingNotificationProgress
 *  @pre        @b privilege \n
 *              * http://tizen.org/privilege/notification
 */
bool updateOngoingNotification (OngoingNotification this_gen);

typedef struct _OngoingNotificationExtend
{
    struct _OngoingNotification Ongoingnotification;
    notification_h              ongoingnotification_handle;
    String                      title;
    String                      text;
    String                      imagePath;
    String                      soundPath;
    bool                        visible;
}    OngoingNotificationExtend;
/* Ongoing Notification */

#ifdef __cplusplus
}
#endif

#endif //DIT_OngoingNOTIFICATION_H
