/*! @file	Preference.c
 *  @brief	Preference API가 정의되어있다.
 *  @note	Preference API가 정의되어있다.
 *  @see	Preference.h
*/


#include "Device/Preference.h"
#include <stdlib.h>
#include <string.h>
#include <app_preference.h>

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

void DestroyPreference (Preference this_gen)
{
    if ( this_gen != NULL)
    {
        Preference * this = (Preference *)this_gen;

        preference_remove_all ();
        free (this);
    }
}

int getPreferenceInt (String key, int defValue)
{

        int ret;
        preference_error_e error=preference_get_int (key, &ret);
        if(error==PREFERENCE_ERROR_NONE)
        {
        	return ret;
        }else
        {
        	return defValue;
        }
}

double getPreferenceDouble (String key,double defValue)
{

        double ret;
        preference_error_e error=preference_get_double (key, &ret);
        if(error==PREFERENCE_ERROR_NONE)
        {
        	return ret;
        }
        else
        {
        	return defValue;
        }
}

bool getPreferenceBoolean (String key, bool defValue)
{
        bool ret;
        preference_error_e error=preference_get_boolean (key, &ret);
        if(error==PREFERENCE_ERROR_NONE)
        {
        	return ret;
        }
        else
        {
         	return defValue;
        }
}

/*
 *
 * @remark return value must be released by using free();\n
 * 		   whether return value equals defValue
 * */
String getPreferenceString (String key, String defValue)
{
	  String ret;
	  preference_error_e error=preference_get_string (key, &ret);
	  if(error==PREFERENCE_ERROR_NONE)
	  {
	  return ret;
	  }
	  else
	  {
	  	return strdup((const String)defValue);
	  }
}

void setPreferenceInt (String key, int value)
{
    preference_set_int (key, value);
}

void setPreferenceDouble (String key, double value)
{
    preference_set_double (key, value);
}

void setPreferenceBoolean (String key, bool value)
{
    preference_set_boolean (key, value);
}

void setPreferenceString (String key, String value)
{
    preference_set_string (key, value);
}

void PreferenceRemove (String key)
{
    bool existing;
    preference_is_existing (key, &existing);
    if ( existing )
    {
        preference_remove (key);
    }
}

void PreferenceClear (void)
{
    preference_remove_all ();
}

const char * PreferenceErrorCheck (int errCode)
{
    switch (errCode)
    {
    case PREFERENCE_ERROR_NONE:
        return "PREFERENCE_ERROR_NONE : Successful";

    case PREFERENCE_ERROR_INVALID_PARAMETER:
        return "PREFERENCE_ERROR_INVALID_PARAMETER : Invalid parameter";

    case PREFERENCE_ERROR_OUT_OF_MEMORY:
        return "PREFERENCE_ERROR_OUT_OF_MEMORY : Out of memory";

    case PREFERENCE_ERROR_NO_KEY:
        return "PREFERENCE_ERROR_NO_KEY : Required key not available";

    case PREFERENCE_ERROR_IO_ERROR:
        return "PREFERENCE_ERROR_IO_ERROR : Internal I/O Error";

    default:
        return "DEVICE_ERROR_NOT_UNKNOWN";
    }
}
