#ifndef DIT_PREFERENCE_H
#define DIT_PREFERENCE_H

#include <stdbool.h>
#include <stdalign.h>

#include "dit.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Preference * Preference;

struct _Preference
{
    int (* getInt) (String key,int defValue);

    double (* getDouble) (String key,double defValue);

    bool (* getBoolean) (String key,bool defValue);

    String (* getString) (String key, String defValue);

    void (* setInt) (String key, int value);

    void (* setDouble) (String key, double value);

    void (* setBoolean) (String key, bool value);

    void (* setString) (String key, String value);

    void (* Remove) (String key);

    void (* Clear) ();

};

Preference NewPreference (void);
void       DestroyPreference (Preference this_gen);
int        getPreferenceInt (String key, int defValue);
double     getPreferenceDouble (String key, double defValue);
bool       getPreferenceBoolean (String key, bool defValue);
String     getPreferenceString (String key, String defValue);
void       setPreferenceInt (String key, int value);
void       setPreferenceDouble (String key, double value);
void       setPreferenceBoolean (String key, bool value);
void       setPreferenceString (String key, String value);
void       PreferenceRemove (String key);
void       PreferenceClear (void);

const char * PreferenceErrorCheck (int errCode);

#ifdef __cplusplus
}
#endif

#endif //DIT_PREFERENCE_H
