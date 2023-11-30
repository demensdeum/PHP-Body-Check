#include <jni.h>
#include <string>
#include <iostream>
#include "ph7.h"
#include "main.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_demensdeum_body_check_app_MainActivity_bodyStatus(
        JNIEnv* env,
        jobject ,
        jint height,
        jint weight) {

    auto result = bodyStatus(height, weight);

    return env->NewStringUTF(result);
}