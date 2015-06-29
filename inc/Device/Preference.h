//
// Created by Park SangHyun on 2015. 6. 27..
//

#ifndef DIT_PREFERENCE_H
#define DIT_PREFERENCE_H

#include <stdbool.h>
#include <stdalign.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Preference Preference;

typedef struct _Preference {
	int (*getInt)(char* key);

	double (*getDouble)(char* key);

	bool (*getBoolean)(char* key);

	void (*getString)(char* key, char** ret);

	void (*setInt)(char* key, int value);

	void (*setDouble)(char* key, double value);

	void (*setBoolean)(char* key, bool value);

	void (*setString)(char* key, char* value);

	void (*Remove)(char* key);

	void (*Clear)();

} Preference;

Preference* NewPreference();

void DestroyPreference(Preference* this_gen);

int getPreferenceInt(char* key);

double getPreferenceDouble(char* key);

bool getPreferenceBoolean(char* key);

void getPreferenceString(char* key, char** ret);

void setPreferenceInt(char* key, int value);

void setPreferenceDouble(char* key, double value);

void setPreferenceBoolean(char* key, bool value);

void setPreferenceString(char* key, char* value);

void PreferenceRemove(char* key);

void PreferenceClear();

#ifdef __cplusplus
}
#endif

#endif //DIT_PREFERENCE_H
