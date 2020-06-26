#include <jni.h>
#include <string>
#include <oboe/Oboe.h>
#include "OboeSinePlayer.h"
#include "OboeSinePlayer.cpp"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jboolean JNICALL
        Java_com_example_myapplication_MainActivity_myOboeSinePlayerCaller(
                JNIEnv * env,
                jobject) {
// TODO: implement myOboeSinePlayerCaller()

    oboe::DefaultStreamValues::SampleRate = (int32_t) 48000;
    oboe::DefaultStreamValues::FramesPerBurst = (int32_t) 16;

    auto a = new OboeSinePlayer();

    return true;
}
