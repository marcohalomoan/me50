package edu.harvard.cs50.pokedex;

import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.net.URL;

public class PokemonActivity extends AppCompatActivity {
    private TextView nameTextView;
    private TextView numberTextView;
    private TextView type1TextView;
    private TextView type2TextView;
    private ImageView imageView;
    private String url;
    private TextView desc;
    private RequestQueue requestQueue;
    private String name;
    public int id;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pokemon);
        requestQueue = Volley.newRequestQueue(getApplicationContext());
        url = getIntent().getStringExtra("url");
        name = getIntent().getStringExtra("name");
        nameTextView = findViewById(R.id.pokemon_name);
        numberTextView = findViewById(R.id.pokemon_number);
        type1TextView = findViewById(R.id.pokemon_type1);
        type2TextView = findViewById(R.id.pokemon_type2);
        imageView = findViewById(R.id.image_view);
        desc = findViewById(R.id.description);
        Button button = findViewById(R.id.button_id);
        boolean caught = getPreferences(Context.MODE_PRIVATE).getBoolean(name, false);
        if (caught) {
            button.setText("Release");
        } else {
            button.setText("Catch");
        }

        load();
    }

    public void toggleCatch(View view) {
        boolean state = getPreferences(Context.MODE_PRIVATE).getBoolean(name, false);
        Button button = findViewById(R.id.button_id);
        if (state) {
            button.setText("Catch");
            getPreferences(Context.MODE_PRIVATE).edit().putBoolean(name, false).commit();
        } else {
            button.setText("Release");
            getPreferences(Context.MODE_PRIVATE).edit().putBoolean(name, true).commit();
        }
    }

    public void load() {
        type1TextView.setText("");
        type2TextView.setText("");

        final JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                try {
                    id = response.getInt("id");
                    String urld = "https://pokeapi.co/api/v2/pokemon-species/" + Integer.toString(id) + "/";
                    final JsonObjectRequest requestd = new JsonObjectRequest(Request.Method.GET, urld, null, new Response.Listener<JSONObject>() {
                        @Override
                        public void onResponse(JSONObject response) {
                            try {
                                JSONArray jsonArrayd = response.getJSONArray("flavor_text_entries");
                                for (int i = 0; i < jsonArrayd.length(); i++) {
                                    String language = jsonArrayd.getJSONObject(i).getJSONObject("language").getString("name");
                                    if (language.equals("en")) {
                                        desc.setText(jsonArrayd.getJSONObject(i).getString("flavor_text"));
                                    }
                                }
                            } catch (JSONException e) {
                                Log.e("cs50", "Pokemon description error", e);
                            }
                        }
                    }, new Response.ErrorListener() {
                        @Override
                        public void onErrorResponse(VolleyError error) {
                            Log.e("cs50", "Pokemon details error", error);
                        }
                    });
                    requestQueue.add(requestd);

                    nameTextView.setText(response.getString("name"));
                    numberTextView.setText(String.format("#%03d", response.getInt("id")));
                    String urls = response.getJSONObject("sprites").getString("front_default");
                    new DownloadSpriteTask().execute(urls);

                    JSONArray typeEntries = response.getJSONArray("types");
                    for (int i = 0; i < typeEntries.length(); i++) {
                        JSONObject typeEntry = typeEntries.getJSONObject(i);
                        int slot = typeEntry.getInt("slot");
                        String type = typeEntry.getJSONObject("type").getString("name");

                        if (slot == 1) {
                            type1TextView.setText(type);
                        } else if (slot == 2) {
                            type2TextView.setText(type);
                        }
                    }
                } catch (JSONException e) {
                    Log.e("cs50", "Pokemon json error", e);
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("cs50", "Pokemon details error", error);
            }
        });

        requestQueue.add(request);
    }

    private class DownloadSpriteTask extends AsyncTask<String, Void, Bitmap> {
        @Override
        protected Bitmap doInBackground(String... strings) {
            try {
                URL url = new URL(strings[0]);
                return BitmapFactory.decodeStream(url.openStream());
            } catch (IOException e) {
                Log.e("cs50", "Download sprite error", e);
                return null;
            }
        }

        @Override
        protected void onPostExecute(Bitmap bitmap) {
            imageView.setImageBitmap(bitmap);
        }
    }
}
