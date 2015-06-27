//
// Created by Park SangHyun on 2015. 6. 27..
//

#include <stdlib.h>
#include <app_preference.h>
#include "Device/Preference.h"

Preference* NewPreference() {
    Preference* this = (Preference *)malloc(sizeof(Preference));

    this->getInt = getPreferenceInt;
    this->getDouble = getPreferenceDouble;
    this->getBoolean = getPreferenceBoolean;
    this->getString = getPreferenceString;

    this->setInt = setPreferenceInt;
    this->setDouble = setPreferenceDouble;
    this->setBoolean = setPreferenceBoolean;
    this->setString = setPreferenceString;

    this->Clear = PreferenceClear;

    return this;
}

void DestroyPreference(Preference* this_gen) {
    if(this_gen != NULL) {
        Preference* this = (Preference *)this_gen;
        free(this);
    }
}

int getPreferenceInt(Preference* this_gen, char* key) {
    int ret;
    preference_get_int(key, &ret);
    return ret;
}

double getPreferenceDouble(Preference* this_gen, char* key) {
    double ret;
    preference_get_double (key, &ret);
    return ret;
}

bool getPreferenceBoolean(Preference* this_gen, char* key) {
    bool ret;
    preference_get_boolean(key, &ret);
    return ret;
}

void getPreferenceString(Preference* this_gen, char* key, char* ret) {
    preference_get_string(key, &ret);
}

void setPreferenceInt(Preference* this_gen, char* key, int value) {
    preference_set_int(key, value);
}

void setPreferenceDouble(Preference* this_gen, char* key, double value) {
    preference_set_double(key, value);
}

void setPreferenceBoolean(Preference* this_gen, char* key, bool value) {
    preference_set_boolean(key, value);
}

void setPreferenceString(Preference* this_gen, char* key, char* value) {
    preference_set_string(key, value);
}

void PreferenceClear(Preference* this_gen) {
    preference_remove_all();
}
