package com.example.myapplication

import android.annotation.SuppressLint
import android.content.Context
import android.media.AudioManager
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*


class MainActivity : AppCompatActivity() {

    @SuppressLint("SetTextI18n")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
        sample_text.text = stringFromJNI()

        editTextFreq.setText("432");

        buttonPlaySineWave.setOnClickListener {
            var freq = 0.0F;
            if (!editTextFreq.text.trim().isEmpty()) {
                freq = editTextFreq.text.toString().toFloat();
                val myAudioMgr = getSystemService(Context.AUDIO_SERVICE) as AudioManager
                val sampleRateStr = myAudioMgr.getProperty(AudioManager.PROPERTY_OUTPUT_SAMPLE_RATE)
                val defaultSampleRate = sampleRateStr.toInt()
                val framesPerBurstStr = myAudioMgr.getProperty(AudioManager.PROPERTY_OUTPUT_FRAMES_PER_BUFFER)
                val defaultFramesPerBurst = framesPerBurstStr.toInt()
                myOboeSinePlayerCaller(defaultSampleRate, defaultFramesPerBurst, freq);
            }

        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun myOboeSinePlayerCaller(sampleRate: Int, framesPerBurst: Int, freq: Float): Boolean

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
            System.loadLibrary("OboeSinePlayer")
        }
    }


}
