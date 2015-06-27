//
// Created by Park SangHyun on 2015. 6. 27..
//

#ifndef DIT_PREFERENCE_H
#define DIT_PREFERENCE_H

#include <stdbool.h>
#include "dit.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct _Preference Preference;
typedef struct _Preference {
    int (* getInt)(Preference* this_gen, char* key);

    double (* getDouble)(Preference* this_gen, char* key);

    bool (* getBoolean)(Preference* this_gen, char* key);

    void (* getString)(Preference* this_gen, char* key, char* ret);

    void (* setInt)(Preference* this_gen, char* key, int value);

    void (* setDouble)(Preference* this_gen, char* key, double value);

    void (* setBoolean)(Preference* this_gen, char* key, bool value);

    void (* setString)(Preference* this_gen, char* key, char* value);

    void (* Clear)(Preference* this_gen);

} Preference;

Preference* NewPreference();

void DestroyPreference(Preference* this_gen);

int getPreferenceInt(Preference* this_gen, char* key);

double getPreferenceDouble(Preference* this_gen, char* key);

bool getPreferenceBoolean(Preference* this_gen, char* key);

void getPreferenceString(Preference* this_gen, char* key, char* ret);

void setPreferenceInt(Preference* this_gen, char* key, int value);

void setPreferenceDouble(Preference* this_gen, char* key, double value);

void setPreferenceBoolean(Preference* this_gen, char* key, bool value);

void setPreferenceString(Preference* this_gen, char* key, char* value);

void PreferenceClear(Preference* this_gen);

#ifdef __cplusplus
}
#endif

#endif //DIT_PREFERENCE_H
