/*! @file	Preference.h
 *  @brief	Preference API 를 사용하기 위해 포함해야 하는 헤더이다.
 *  @note	Preference의 get Preference / set Preference / Remove / Clear 관련 Preference API를 제공한다.
 *  @see    [Tizen Native API](https://developer.tizen.org/development/api-references/native-application?redirect=https%3A//developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/index.html)
 */

#ifndef DIT_PREFERENCE_H
#define DIT_PREFERENCE_H

#include <stdbool.h>
#include <stdalign.h>

#include "dit.h"

#ifdef __cplusplus
extern "C" {
#endif

const char * PreferenceErrorCheck (int errCode);

/*! @fn 		const char * PreferenceErrorCheck (int errCode)
 *  @brief 		Preference API에서 발생하는 Error Code들을 확인 해준다.
 *  @param[in] 	errCode 확인 하고자 하는 Error Code
 *  @param[out]	null
 *  @retval 	PREFERENCE_ERROR_NONE				 : Successful
 *  @retval		PREFERENCE_ERROR_INVALID_PARAMETER	 : Invalid parameter
 *  @retval 	PREFERENCE_ERROR_OUT_OF_MEMORY		 : Out of memory
 *  @retval 	PREFERENCE_ERROR_NO_KEY				 : Required key not available
 *  @retval 	PREFERENCE_ERROR_IO_ERROR			 : Internal I/O Error
 *  @retval 	DEVICE_ERROR_NOT_UNKNOWN			 : Unknown error occurred
 *  @note 		Preference API에서 발생하는 Error Code들을 확인 해준다. \n
 *              Error의 내용은 Log를 통해 출력 된다. \n
 *  			6가지의 Error Code들을 확인 가능 하다.
 *  @see 		[Tizen Native API Document - Preference part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__PREFERENCE__MODULE.html)
 */
const char * PreferenceErrorCheck (int errCode);

/* Preference */
/*! @struct	_Preference
 *  @brief	Preference 모듈에 대한 구조체이다. Preference 모듈은 다양한 형식으로 key값을 제어 할 수 있다.
 *  @note	Preference 모듈에 대한 구조체이다. \n
    		구조체를 사용하기 전에 NewPreference() 함수를 사용해야 하며 사용이 끝났을 때 DestroyPreference() 함수를 꼭 사용해야 한다.
 *  @see	[Tizen Native API Document - Preference part](https://developer.tizen.org/dev-guide/2.3.0/org.tizen.native.mobile.apireference/group__CAPI__PREFERENCE__MODULE.html)
 */
typedef struct _Preference * Preference;
struct _Preference
{
    int (* getInt) (String key, int defValue);

    double (* getDouble) (String key, double defValue);

    bool (* getBoolean) (String key, bool defValue);

    String (* getString) (String key, String defValue);

    bool (* setInt) (String key, int value);

    bool (* setDouble) (String key, double value);

    bool (* setBoolean) (String key, bool value);

    bool (* setString) (String key, String value);

    bool (* Remove) (String key);

    bool (* Clear) (void);

};

/*!	@fn			Preference NewPreference (void)
 *  @brief		새로운 Preference 객체를 생성한다.
 *  @param[in]	void
 *  @param[out] null
 *  @retval 	Preference
 *  @note 		새로운 Preference 객체를 생성한다. \n
 *  			Preference 객체를 사용하기 전에 반드시 호출해야 한다.
 *  @see 		DestroyPreference \n
 *  			getPreferenceInt \n
 *  			getPreferenceDouble \n
 *  			getPreferenceBoolean \n
 *  			getPreferenceString \n
 *  			setPreferenceInt \n
 *  			setPreferenceDouble \n
 *  			setPreferenceBoolean \n
 *  			setPreferenceString \n
 *  			PreferenceRemove \n
 *  			PreferenceClear
 *  @warning    사용이 끝났을 때 DestroyPreference() 함수를 꼭 사용해야 한다.
 *
 *  @code{.c}
Preference NewPreference (void)
{
    Preference this = (Preference)malloc (sizeof (struct _Preference));

    this->getInt     = getPreferenceInt;
    this->getDouble  = getPreferenceDouble;
    this->getBoolean = getPreferenceBoolean;
    this->getString  = getPreferenceString;

    this->setInt     = setPreferenceInt;
    this->setDouble  = setPreferenceDouble;
    this->setBoolean = setPreferenceBoolean;
    this->setString  = setPreferenceString;

    this->Remove = PreferenceRemove;
    this->Clear  = PreferenceClear;

    return this;
}
 *	@endcode
 */
Preference NewPreference (void);

/*!	@fn			void DestroyPreference (Preference this_gen)
 *  @brief		생성한 Preference 객체를 소멸 시킨다.
 *  @param[in]	this_gen 소멸시킬 Preference 객체
 *  @param[out] null
 *  @retval 	void
 *  @note 		생성한 Preference 객체를 소멸 시킨다. \n
 *  			Preference 객체를 사용한 후 반드시 호출해야 한다.
 *  @see 		NewPreference
 */
void DestroyPreference (Preference this_gen);

/*! @fn 		int getPreferenceInt (String key, int defValue)
 *  @brief 		키 값에 대응하는 Preference의 @c int 값을 반환한다.
 *  @param[in] 	key	키 값
 *  @param[in] 	defValue 키 값에 대응하는 @c int 값
 *  @param[out] null
 *  @retval 	int Preference의 @c int 값
 *  @note 		키 값에 대응하는 Preference의 @c int 값을 반환한다.
 *  @see		NewPreference \n
 *  			DestroyPreference \n
 *  			getPreferenceDouble \n
 *  			getPreferenceBoolean \n
 *  			getPreferenceString \n
 *  			setPreferenceInt \n
 *  			setPreferenceDouble \n
 *  			setPreferenceBoolean \n
 *  			setPreferenceString \n
 *  			PreferenceRemove \n
 *  			PreferenceClear
 */
int getPreferenceInt (String key, int defValue);

/*! @fn 		double getPreferenceDouble (String key, double defValue)
 *  @brief 		키 값에 대응하는 Preference의 @c double 값을 반환한다.
 *  @param[in] 	key	키 값
 *  @param[in] 	defValue 키 값에 대응하는 @c double 값
 *  @param[out] null
 *  @retval 	double Preference의 @c double 값
 *  @note 		키 값에 대응하는 Preference의 @c double 값을 반환한다.
 *  @see		NewPreference \n
 *  			DestroyPreference \n
 *  			getPreferenceInt \n
 *  			getPreferenceBoolean \n
 *  			getPreferenceString \n
 *  			setPreferenceInt \n
 *  			setPreferenceDouble \n
 *  			setPreferenceBoolean \n
 *  			setPreferenceString \n
 *  			PreferenceRemove \n
 *  			PreferenceClear
 */
double getPreferenceDouble (String key, double defValue);

/*! @fn 		bool getPreferenceBoolean (String key, bool defValue)
 *  @brief 		키 값에 대응하는 Preference의 @c boolean 값을 반환한다.
 *  @param[in] 	key	키 값
 *  @param[in] 	defValue 키 값에 대응하는 @c boolen 값
 *  @param[out] null
 *  @retval 	boolen Preference의 @c boolen 값
 *  @note 		키 값에 대응하는 Preference의 @c boolen 값을 반환한다.
 *  @see		NewPreference \n
 *  			DestroyPreference \n
 *  			getPreferenceInt \n
 *  			getPreferenceDouble \n
 *  			getPreferenceString \n
 *  			setPreferenceInt \n
 *  			setPreferenceDouble \n
 *  			setPreferenceBoolean \n
 *  			setPreferenceString \n
 *  			PreferenceRemove \n
 *  			PreferenceClear
 */
bool getPreferenceBoolean (String key, bool defValue);

/*! @fn 		String getPreferenceString (String key, String defValue)
 *  @brief 		키 값에 대응하는 Preference의 @c string 값을 반환한다.
 *  @param[in] 	key	키 값
 *  @param[in] 	defValue 키 값에 대응하는 @c string 값
 *  @param[out] null
 *  @retval 	string Preference의 @c string 값
 *  @note 		키 값에 대응하는 Preference의 @c string 값을 반환한다.
 *  @see		NewPreference \n
 *  			DestroyPreference \n
 *  			getPreferenceInt \n
 *  			getPreferenceDouble \n
 *  			getPreferenceBoolean \n
 *  			setPreferenceInt \n
 *  			setPreferenceDouble \n
 *  			setPreferenceBoolean \n
 *  			setPreferenceString \n
 *  			PreferenceRemove \n
 *  			PreferenceClear
 *  @warning    반환된 @c string 값은 이후 반드시 @a free()를 통해 메모리 해제를 해야 한다.
 */
String getPreferenceString (String key, String defValue);

/*! @fn 		bool setPreferenceInt (String key, int value)
 *  @brief 		키 값에 대응하는 Preference에 @c int 값을 저장한다.
 *  @param[in] 	key	키 값
 *  @param[in] 	value 키 값에 대응하는 Preference에 저장할 @c int 값
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		키 값에 대응하는 Preference의 @c int 값을 저장한다.
 *  @see		NewPreference \n
 *  			DestroyPreference \n
 *  			getPreferenceInt \n
 *  			getPreferenceDouble \n
 *  			getPreferenceBoolean \n
 *  			getPreferenceString \n
 *  			setPreferenceDouble \n
 *  			setPreferenceBoolean \n
 *  			setPreferenceString \n
 *  			PreferenceRemove \n
 *  			PreferenceClear
 */
bool setPreferenceInt (String key, int value);

/*! @fn 		bool setPreferenceDouble (String key, double value)
 *  @brief 		키 값에 대응하는 Preference에 @c double 값을 저장한다.
 *  @param[in] 	key	키 값
 *  @param[in] 	value 키 값에 대응하는 Preference에 저장할 @c double 값
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		키 값에 대응하는 Preference에 @c double 값을 저장한다.
 *  @see		NewPreference \n
 *  			DestroyPreference \n
 *  			getPreferenceInt \n
 *  			getPreferenceDouble \n
 *  			getPreferenceBoolean \n
 *  			getPreferenceString \n
 *  			setPreferenceInt \n
 *  			setPreferenceBoolean \n
 *  			setPreferenceString \n
 *  			PreferenceRemove \n
 *  			PreferenceClear
 */
bool setPreferenceDouble (String key, double value);

/*! @fn 		bool setPreferenceBoolean (String key, bool value)
 *  @brief 		키 값에 대응하는 Preference에 @c boolean 값을 저장한다.
 *  @param[in] 	key	키 값
 *  @param[in] 	value 키 값에 대응하는 Preference에 저장할 @c boolean 값
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		키 값에 대응하는 Preference에 @c boolean 값을 저장한다.
 *  @see		NewPreference \n
 *  			DestroyPreference \n
 *  			getPreferenceInt \n
 *  			getPreferenceDouble \n
 *  			getPreferenceBoolean \n
 *  			getPreferenceString \n
 *  			setPreferenceInt \n
 *  			setPreferenceDouble \n
 *  			setPreferenceString \n
 *  			PreferenceRemove \n
 *  			PreferenceClear
 */
bool setPreferenceBoolean (String key, bool value);

/*! @fn 		bool setPreferenceString (String key, String value)
 *  @brief 		키 값에 대응하는 Preference에 @c string 값을 저장한다.
 *  @param[in] 	key	키 값
 *  @param[in] 	value 키 값에 대응하는 Preference에 저장할 @c string 값
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		키 값에 대응하는 Preference에 @c string 값을 저장한다.
 *  @see		NewPreference \n
 *  			DestroyPreference \n
 *  			getPreferenceInt \n
 *  			getPreferenceDouble \n
 *  			getPreferenceBoolean \n
 *  			setPreferenceBoolean \n
 *  			setPreferenceInt \n
 *  			setPreferenceDouble \n
 *  			setPreferenceBoolean \n
 *  			PreferenceRemove \n
 *  			PreferenceClear 
 */
bool setPreferenceString (String key, String value);

/*! @fn 		bool PreferenceRemove (String key)
 *  @brief 		키 값에 대응하는 Preference의 값을 삭제한다.
 *  @param[in] 	key	키 값
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		키 값에 대응하는 Preference의 값을 삭제한다.
 *  @see		NewPreference \n
 *  			DestroyPreference \n
 *  			getPreferenceInt \n
 *  			getPreferenceDouble \n
 *  			getPreferenceBoolean \n
 *  			setPreferenceBoolean \n
 *  			setPreferenceInt \n
 *  			setPreferenceDouble \n
 *  			setPreferenceBoolean \n
 *  			setPreferenceString \n
 *  			PreferenceClear
 */
bool PreferenceRemove (String key);

/*! @fn 		bool PreferenceClear (void)
 *  @brief 		모든 Preference의 값을 삭제한다.
 *  @param[in] 	void
 *  @param[out] null
 *  @retval 	bool \n
 *              함수의 성공 여부를 반환한다. \n
 *              실패시 @c false를 반환하며 상세한 원인을 Log로 출력한다.
 *  @note 		모든 Preference의 값을 삭제한다.
 *  @see		NewPreference \n
 *  			DestroyPreference \n
 *  			getPreferenceInt \n
 *  			getPreferenceDouble \n
 *  			getPreferenceBoolean \n
 *  			setPreferenceBoolean \n
 *  			setPreferenceInt \n
 *  			setPreferenceDouble \n
 *  			setPreferenceBoolean \n
 *  			setPreferenceString \n
 *  			PreferenceRemove
 */
bool PreferenceClear (void);
/* Preference */

#ifdef __cplusplus
}
#endif

#endif //DIT_PREFERENCE_H
