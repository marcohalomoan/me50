package edu.harvard.cs50.kwotz;

import android.Manifest;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

public class MainActivity extends AppCompatActivity {

    private TextView are_you;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 1);
        are_you = findViewById(R.id.are_you);
        are_you.setText("Are you?");
    }

    public void putExtras(String emotion, String emotion_state, View v) {
        Intent intent = new Intent(v.getContext(), KwotzActivity.class);
        intent.putExtra(emotion, emotion_state);

        v.getContext().startActivity(intent);
    }

    public void happy(View v) {
        putExtras("emotion", "happy", v);
    }

    public void sad(View v) {
        putExtras("emotion", "sad", v);
    }

    public void angry(View v) {
        putExtras("emotion", "angry", v);
    }

    public void afraid(View v) {
        putExtras("emotion", "afraid", v);
    }

    public void embarrassed (View v) {
        putExtras("emotion", "embarrassed", v);
    }
}
