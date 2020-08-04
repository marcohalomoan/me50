package edu.harvard.cs50.kwotz;

import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class KwotzActivity extends AppCompatActivity {

    private String emotion;
    private TextView quotes1;
    private TextView quotes2;
    private TextView quotes3;
    private TextView quotes4;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_kwotz);
        emotion = getIntent().getStringExtra("emotion");
        quotes1 = findViewById(R.id.quotes1);
        quotes2 = findViewById(R.id.quotes2);
        quotes3 = findViewById(R.id.quotes3);
        quotes4 = findViewById(R.id.quotes4);
        if (emotion.equals("happy")) {
            quotes1.setText("Every day is a new day.");
            quotes2.setText("Thousands of candles can be lighted from a single candle, " +
                    "and the life of the candle will not be shortened. " +
                    "Happiness never decreases by being shared.\n-Buddha");
            quotes3.setText("It isn't what you have, or who you are, or where you are, " +
                    "or what you are doing that makes you happy or unhappy. " +
                    "It is what you think about.\n-Dale Carnegie");
            quotes4.setText("Time you enjoy wasting is not wasted time.\n-Marthe Troly-Curtin");
        }
        else if (emotion.equals("sad")) {
            quotes1.setText("Sadness flies away on the wings of time.\nJean de La Fontaine");
            quotes2.setText("Any fool can be happy. It takes a man with real heart to make beauty " +
                    "out of the stuff that makes us weep\n-Clive Barker");
            quotes3.setText("The word ‘happy’ would lose its meaning if it were not balanced by " +
                    "sadness.\n-Carl Jung");
            quotes4.setText("The first step toward change is awareness. The second step is " +
                    "acceptance.\n-Nathaniel Branden");
        }
        else if (emotion.equals("angry")) {
            quotes1.setText("Holding onto anger is like drinking poison and expecting others to die");
            quotes2.setText("Just because you're angry doesn't mean you have the right to be cruel");
            quotes3.setText("One minute of anger weakens the immune system for 4 to 5 hours. " +
                    "One minute of laughter boosts the immune system for 24 hours.");
            quotes4.setText("Speak when you are angry and you will make the best speech you will ever regret.");
        }
        else if (emotion.equals("afraid")) {
            quotes1.setText("Don't be afraid of being scared. To be afraid is a sign of common " +
                    "sense.\n-Carlos Ruiz Zafón");
            quotes2.setText("Always do what you're afraid to do.\n-E. Lockhart");
            quotes3.setText("I'm going to die whatever you do, but I'm not afraid.\n-Erin Hunter");
            quotes4.setText("Beethoven said that it's better to hit the wrong note confidently, " +
                    "than hit the right note unconfidently. Never be afraid to be wrong or to embarrass yourself; " +
                    "we are all students in this life, and there is always " +
                    "something more to learn.\n-Mike Norton");
        }
        else if (emotion.equals("embarrassed")) {
            quotes1.setText("It's only embarrassing if you care what other people think.");
            quotes2.setText("I don't get embarrassed easily, and I do silly things all the" +
                    "time!\n-Emily Osment");
            quotes3.setText("A momentary blush is better than a lifetime regret.");
            quotes4.setText("Anyone who isn’t embarrassed of who they were last year probably " +
                    "isn’t learning enough.");
        }
    }
}
