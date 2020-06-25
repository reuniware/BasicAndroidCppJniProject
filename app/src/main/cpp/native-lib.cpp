#include <jni.h>
#include <string>
#include <oboe/Oboe.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    //OboeSinePlayer a;

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

/*extern "C" JNIEXPORT void JNICALL
Java_com_google_sample_oboe_hellooboe_MainActivity_native_1setDefaultStreamValues(JNIEnv *env,
                                                                                  jclass type,
                                                                                  jint sampleRate,
                                                                                  jint framesPerBurst) {
    oboe::DefaultStreamValues::SampleRate = (int32_t) sampleRate;
    oboe::DefaultStreamValues::FramesPerBurst = (int32_t) framesPerBurst;
}*/

