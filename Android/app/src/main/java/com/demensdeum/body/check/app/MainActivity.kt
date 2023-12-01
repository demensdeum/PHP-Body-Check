package com.demensdeum.body.check.app

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.text.Editable
import android.text.TextWatcher
import android.util.Log
import android.widget.TextView
import com.demensdeum.body.check.app.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    private var weight: Int = 1;
    private var height: Int = 1;

    private fun calculateBodyStatus() {

        var weightText = binding.weight.text.toString()
        var heightText = binding.height.text.toString()

        if (
            weightText.toIntOrNull() == null ||
            heightText.toIntOrNull() == null
            )
        {
            return
        }
        if (weight < 1 || height < 1) {
            return
        }
        var bodyState = bodyStatus(height, weight)
        binding.bodyState.text = bodyState
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.weight.addTextChangedListener(object : TextWatcher {
            override fun beforeTextChanged(s: CharSequence?, start: Int, count: Int, after: Int) {
                Log.v("VerboseTag", "Weight Before Text Changed: $s, start: $start, count: $count, after: $after")
            }

            override fun onTextChanged(s: CharSequence?, start: Int, before: Int, count: Int) {
                try {
                    weight = s.toString().toInt();
                    Log.v("VerboseTag", weight.toString());
                    calculateBodyStatus()
                }
                catch(e: Exception) {

                }
            }

            override fun afterTextChanged(s: Editable?) {
                Log.v("VerboseTag", "Weight After Text Changed: $s")
            }
        })

        binding.height.addTextChangedListener(object : TextWatcher {
            override fun beforeTextChanged(s: CharSequence?, start: Int, count: Int, after: Int) {
                Log.v("VerboseTag", "Height Before Text Changed: $s, start: $start, count: $count, after: $after")
            }

            override fun onTextChanged(s: CharSequence?, start: Int, before: Int, count: Int) {
                try {
                    height = s.toString().toInt();
                    Log.v("VerboseTag", height.toString());
                    calculateBodyStatus()
                }
                catch (e: Exception) {
                    // handler
                }
            }

            override fun afterTextChanged(s: Editable?) {
                Log.v("VerboseTag", "Height After Text Changed: $s")
            }
        })
    }

    /**
     * A native method that is implemented by the 'app' native library,
     * which is packaged with this application.
     */
    external fun bodyStatus(height: Int, width: Int): String

    companion object {
        // Used to load the 'app' library on application startup.
        init {
            System.loadLibrary("app")
        }
    }
}