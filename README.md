# BasicAndroidCppJniProject
Just having fun learning JNI (Google OBOE) on Android !

I have started with the basic Android NDK C++ project generated by Android Studio.

Then I have followed the procedure "Option 2) Building from source" at https://github.com/google/oboe/blob/master/docs/GettingStarted.md

Then I have made all necessary changes to the Android project in order to have the OboeSinePlayer class work, that is given as an example on the same page in the Example section at  https://github.com/google/oboe/blob/master/docs/GettingStarted.md (*1)

After that, the work that has been done to have OBOE working is the following :

- Adding the class OboeSinePlayer.cpp (and the header OboeSinePlayer.h)
- Copying the code from the Example section (*1) to the OboeSinePlayer.cpp
- In the CMakeLists.txt, adding of the add_library command for OboeSinePlayer
- In the CMakeLists.txt, adding of OboeSinePlayer in the target_link_libraries command
- In native-lib.cpp, adding of the JNIEXPORT for MainActivity.myOboeSinePlayerCaller(JNIEnv * env, jobject MainActivity)

  MainActivity.myOboeSinePlayerCaller <=> Java_com_example_myapplication_MainActivity_myOboeSinePlayerCaller

  This function initializes the oboe::DefaultStreamValues SampleRate and FramesPerBurst
  And then instantiates the OboeSinePlayer() class
  
- Then in the default MainActivity generated by Android Studio, adding of the declaration of the external function myOboeSinePlayerCaller(), and adding of the System.loadLibrary("OboeSinePlayer") in the init of the companion object.

- Then in the default MainActivity, adding of the call of myOboeSinePlayerCaller() in the onCreate.

This is very rudimentary, very basic, but keep in mind that I have done all that in order to understand how to have Android NDK working, and to understand how to import an external C++ project (Google OBOE here) in an existing one.

I hope that I have forgotten nothing and that it will help you !

Feel free to contact me at investdatasystems@yahoo.com
