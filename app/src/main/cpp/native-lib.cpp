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

extern "C" JNIEXPORT jboolean JNICALL
Java_com_example_myapplication_MainActivity_myOboeSinePlayerCaller(
        JNIEnv * env,
        jobject,
        jint sampleRate,
        jint framesPerBurst,
        jfloat freq) {

    oboe::DefaultStreamValues::SampleRate = (int32_t) sampleRate;
    oboe::DefaultStreamValues::FramesPerBurst = (int32_t) framesPerBurst;

    static int constexpr kChannelCount = 2;
    static int constexpr kSampleRate = 48000;
    // Wave params, these could be instance variables in order to modify at runtime
    float constexpr kAmplitude = 0.5f;
    float kFrequency = freq;
    static float constexpr kPI = M_PI;
    static float constexpr kTwoPi = kPI * 2;
    double mPhaseIncrement = kFrequency * kTwoPi / (double) kSampleRate;
    auto a = new OboeSinePlayer(kChannelCount, kSampleRate, kAmplitude, kFrequency, kPI, kTwoPi, mPhaseIncrement);

    return true;
}
