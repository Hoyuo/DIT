#include "Device/Preference.h"

#include <stdlib.h>

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
        free (this);
    }
}

int getPreferenceInt (String key)
{
    bool exiting;
    preference_is_existing (key, &exiting);
    if ( exiting )
    {
        int ret;
        preference_get_int (key, &ret);
        return ret;
    }
}

double getPreferenceDouble (String key)
{
    bool exiting;
    preference_is_existing (key, &exiting);
    if ( exiting )
    {
        double ret;
        preference_get_double (key, &ret);
        return ret;
    }
}

bool getPreferenceBoolean (String key)
{
    bool exiting;
    preference_is_existing (key, &exiting);
    if ( exiting )
    {
        bool ret;
        preference_get_boolean (key, &ret);
        return ret;
    }
}

void getPreferenceString (String key, String * ret)
{
    bool exiting;
    preference_is_existing (key, &exiting);
    if ( exiting )
    {
        preference_get_string (key, ret);
    }
}

void setPreferenceInt (String key, int value)
{
    bool exiting;
    preference_is_existing (key, &exiting);
    if ( !exiting )
    {
        preference_set_int (key, value);
    }
}

void setPreferenceDouble (String key, double value)
{
    bool exiting;
    preference_is_existing (key, &exiting);
    if ( !exiting )
    {
        preference_set_double (key, value);
    }
}

void setPreferenceBoolean (String key, bool value)
{
    bool exiting;
    preference_is_existing (key, &exiting);
    if ( !exiting )
    {
        preference_set_boolean (key, value);
    }
}

void setPreferenceString (String key, String value)
{
    bool exiting;
    preference_is_existing (key, &exiting);
    if ( !exiting )
    {
        preference_set_string (key, value);
    }
}

void PreferenceRemove (String key)
{
    bool exiting;
    preference_is_existing (key, &exiting);
    if ( exiting )
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
        return "PREFERENCE_ERROR_UNKWON";
    }
}
