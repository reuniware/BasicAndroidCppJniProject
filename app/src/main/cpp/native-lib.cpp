#include <jni.h>
#include <string>
#include <oboe/Oboe.h>
#include <android/log.h>
#include "OboeSinePlayer.h"
#include "OboeSinePlayer.cpp"
#include "oboe/samples/RhythmGame/src/main/cpp/utils/UtilityFunctions.h"

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


extern "C" JNIEXPORT jboolean JNICALL
Java_com_example_myapplication_MainActivity_myOboeAudioRecorder(
        JNIEnv * env,
        jobject MainActivity
        ) {

    oboe::AudioStreamBuilder builder;
    builder.setDirection(oboe::Direction::Input);
    builder.setPerformanceMode(oboe::PerformanceMode::LowLatency);
    builder.setDeviceId(0);
    /*builder.setSampleRate(48000);
    builder.setSharingMode(oboe::SharingMode::Exclusive);
    builder.setAudioApi(oboe::AudioApi::Unspecified);*/

    oboe::AudioStream *stream;
    oboe::Result r = builder.openStream(&stream);
    if (r != oboe::Result::OK) {
        __android_log_print(ANDROID_LOG_ERROR,
                            "AudioEngine",
                            "Error opening stream %s",
                            convertToText(r));
        return false;
    }

    r = stream->requestStart();
    if (r != oboe::Result::OK) {
        __android_log_print(ANDROID_LOG_ERROR,
                            "AudioEngine",
                            "Error requestStart %s",
                            convertToText(r));
        return false;
    }

    constexpr int kMillisecondsToRecord = 2;
    const auto requestedFrames = (int32_t)(kMillisecondsToRecord * (stream->getSampleRate() / kMillisecondsToRecord));
    int16_t mybuffer[requestedFrames];

    constexpr int64_t kTimeoutValue = 3 * kNanosecondsInMillisecond;
    int framesRead = 0;
    do {
        auto result = stream->read(mybuffer, stream->getBufferSizeInFrames(), 0);
        if (result != oboe::Result::OK) break;
        framesRead = result.value();
    } while (framesRead != 0);

    bool isRecording = true;
    while (isRecording) {
        oboe::Result result = stream->read(mybuffer, requestedFrames, kTimeoutValue);
        if (result == oboe::Result::OK) {
        } else {
            __android_log_print(ANDROID_LOG_ERROR,
                                "AudioEngine",
                                "Error recording %s",
                                convertToText(result));
        }
    }

    stream->close();

    return true;
}
