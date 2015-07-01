#include "Device/Preference.h"

#include <stdlib.h>
#include <app_preference.h>

Preference* NewPreference() {
    Preference* this = (Preference*) malloc(sizeof(Preference));

    this->getInt = getPreferenceInt;
    this->getDouble = getPreferenceDouble;
    this->getBoolean = getPreferenceBoolean;
    this->getString = getPreferenceString;

    this->setInt = setPreferenceInt;
    this->setDouble = setPreferenceDouble;
    this->setBoolean = setPreferenceBoolean;
    this->setString = setPreferenceString;

    this->Remove = PreferenceRemove;
    this->Clear = PreferenceClear;

    return this;
}

void DestroyPreference(Preference* this_gen) {
    if (this_gen != NULL) {
        Preference* this = (Preference*) this_gen;
        free(this);
    }
}

int getPreferenceInt(char* key) {
    bool exiting;
    preference_is_existing(key, &exiting);
    if (exiting) {
        int ret;
        preference_get_int(key, &ret);
        return ret;
    }
}

double getPreferenceDouble(char* key) {
    bool exiting;
    preference_is_existing(key, &exiting);
    if (exiting) {
        double ret;
        preference_get_double(key, &ret);
        return ret;
    }
}

bool getPreferenceBoolean(char* key) {
    bool exiting;
    preference_is_existing(key, &exiting);
    if (exiting) {
        bool ret;
        preference_get_boolean(key, &ret);
        return ret;
    }
}

void getPreferenceString(char* key, char** ret) {
    bool exiting;
    preference_is_existing(key, &exiting);
    if (exiting) {
        preference_get_string(key, ret);
    }
}

void setPreferenceInt(char* key, int value) {
    bool exiting;
    preference_is_existing(key, &exiting);
    if (!exiting) {
        preference_set_int(key, value);
    }
}

void setPreferenceDouble(char* key, double value) {
    bool exiting;
    preference_is_existing(key, &exiting);
    if (!exiting) {
        preference_set_double(key, value);
    }
}

void setPreferenceBoolean(char* key, bool value) {
    bool exiting;
    preference_is_existing(key, &exiting);
    if (!exiting) {
        preference_set_boolean(key, value);
    }
}

void setPreferenceString(char* key, char* value) {
    bool exiting;
    preference_is_existing(key, &exiting);
    if (!exiting) {
        preference_set_string(key, value);
    }
}

void PreferenceRemove(char* key) {
    bool exiting;
    preference_is_existing(key, &exiting);
    if (exiting) {
        preference_remove(key);
    }
}

void PreferenceClear() {
    preference_remove_all();
}
