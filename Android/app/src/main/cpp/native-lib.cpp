#include <jni.h>
#include <string>
#include <iostream>
#include "ph7.h"
#include "main.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_demensdeum_body_check_app_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject ) {

    main();

    std::string hello = "Hello from Twitch2";
    return env->NewStringUTF(hello.c_str());
}