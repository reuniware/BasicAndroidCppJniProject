package com.example.myapplication

import android.Manifest
import android.annotation.SuppressLint
import android.content.Context
import android.content.pm.PackageManager
import android.media.AudioManager
import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
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
                myOboeSinePlayerCaller(defaultSampleRate, defaultFramesPerBurst, freq)

                //val devices = myAudioMgr.getDevices(AudioManager.GET_DEVICES_INPUTS) // 0 = mic ; 1 = telephony_rx (on Samsung A3)
                //Log.i("", "${devices.size}")
            }
        }

        buttonRecordAudio.setOnClickListener {

            val permission = ContextCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO)

            if (permission != PackageManager.PERMISSION_GRANTED) {
                Log.i("", "Permission to record denied")
                ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.RECORD_AUDIO), RECORD_REQUEST_CODE)
            } else {
                myOboeAudioRecorder()
            }

        }
    }

    val RECORD_REQUEST_CODE = 1234

    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<String>, grantResults: IntArray) {
        when (requestCode) {
            RECORD_REQUEST_CODE -> {
                if (grantResults.isEmpty() || grantResults[0] != PackageManager.PERMISSION_GRANTED) {
                    Log.i("", "Permission has been denied by user")
                } else {
                    Log.i("", "Permission has been granted by user")
                    myOboeAudioRecorder()
                }
            }
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun myOboeSinePlayerCaller(sampleRate: Int, framesPerBurst: Int, freq: Float): Boolean

    external fun myOboeAudioRecorder(): Boolean

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
            System.loadLibrary("OboeSinePlayer")
        }
    }


}
