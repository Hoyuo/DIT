/*! @file	Preference.c
 *  @brief	Preference API가 정의되어있다.
 *  @note	Preference API가 정의되어있다.
 *  @see	Preference.h
*/


#include "Device/Preference.h"

#include <stdlib.h>
#include <string.h>
#include <app_preference.h>
#include <dlog.h>

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

        free (this);
    }
}

int getPreferenceInt (String key, int defValue)
{

    int ret;
    preference_error_e error = preference_get_int (key, &ret);
    if ( error == PREFERENCE_ERROR_NONE )
    {
        return ret;
    }
    else
    {
    	dlog_print(DLOG_INFO,"DIT","%s",PreferenceErrorCheck(ret));
        return defValue;
    }
}

double getPreferenceDouble (String key, double defValue)
{

    double  ret;
    preference_error_e error = preference_get_double (key, &ret);
    if ( error == PREFERENCE_ERROR_NONE )
    {
        return ret;
    }
    else
    {
    	dlog_print(DLOG_INFO,"DIT","%s",PreferenceErrorCheck(ret));
        return defValue;
    }
}

bool getPreferenceBoolean (String key, bool defValue)
{
    bool  ret;
    preference_error_e error = preference_get_boolean (key, &ret);
    if ( error == PREFERENCE_ERROR_NONE )
    {
        return ret;
    }
    else
    {
    	dlog_print(DLOG_INFO,"DIT","%s",PreferenceErrorCheck(ret));
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
    String             ret;
    preference_error_e error = preference_get_string (key, &ret);
    if ( error == PREFERENCE_ERROR_NONE )
    {
        return ret;
    }
    else
    {
    	dlog_print(DLOG_INFO,"DIT","%s",PreferenceErrorCheck(error));
        return strdup ((const String)defValue);
    }
}

bool setPreferenceInt (String key, int value)
{
	preference_error_e error =   preference_set_int (key, value);
	if(error != PREFERENCE_ERROR_NONE)
	{
		dlog_print(DLOG_INFO,"DIT","%s",PreferenceErrorCheck(error));
		return false;
	}
	return true;
}

bool setPreferenceDouble (String key, double value)
{
	preference_error_e error =  preference_set_double (key, value);
    if(error != PREFERENCE_ERROR_NONE)
    	{
    		dlog_print(DLOG_INFO,"DIT","%s",PreferenceErrorCheck(error));
    		return false;
    	}
    	return true;
}

bool setPreferenceBoolean (String key, bool value)
{
	preference_error_e error =  preference_set_boolean (key, value);
    if(error != PREFERENCE_ERROR_NONE)
    	{
    		dlog_print(DLOG_INFO,"DIT","%s",PreferenceErrorCheck(error));
    		return false;
    	}
    	return true;
}

bool setPreferenceString (String key, String value)
{
	preference_error_e error =   preference_set_string (key, value);
    if(error != PREFERENCE_ERROR_NONE)
    	{
    		dlog_print(DLOG_INFO,"DIT","%s",PreferenceErrorCheck(error));
    		return false;
    	}
    	return true;
}

bool PreferenceRemove (String key)
{
    bool existing;
    preference_error_e error = preference_is_existing (key, &existing);
    if ( existing )
    {
    		error = preference_remove (key);
    		if(error != PREFERENCE_ERROR_NONE)
    		{
    			return true;
    		}
    		else{
        		dlog_print(DLOG_INFO,"DIT","%s",PreferenceErrorCheck(error));
        		return false;
    		}
    }
    else
    {
    	dlog_print(DLOG_INFO,"DIT","Required key doesn't exist");
    	return false;
    }
}

bool PreferenceClear (void)
{
	preference_error_e error =   preference_remove_all ();
	   if(error != PREFERENCE_ERROR_NONE)
	    	{
	    		dlog_print(DLOG_INFO,"DIT","%s",PreferenceErrorCheck(error));
	    		return false;
	    	}
	    	return true;

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
