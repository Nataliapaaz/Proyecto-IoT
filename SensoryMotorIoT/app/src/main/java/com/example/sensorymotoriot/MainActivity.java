package com.example.sensorymotoriot;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.loopj.android.http.AsyncHttpClient;
import com.loopj.android.http.AsyncHttpResponseHandler;

import org.json.JSONArray;
import org.json.JSONObject;

import cz.msebera.android.httpclient.Header;

public class MainActivity extends AppCompatActivity {

    private static final String url_read = "https://api.thingspeak.com/channels/2380517/fields/1.json?results=1";
    private TextView txt;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        txt = findViewById(R.id.valores);
        readJSON();
    }

    public void refresh(View view){
        readJSON();
    }

    public void readJSON(){

        AsyncHttpClient client = new AsyncHttpClient();
        client.get(url_read, new AsyncHttpResponseHandler() {
            @Override
            public void onSuccess(int statusCode, Header[] headers, byte[] responseBody) {
                if (statusCode==200){
                    String response = new String (responseBody);
                    processJSON(response);

                }
            }

            @Override
            public void onFailure(int statusCode, Header[] headers, byte[] responseBody, Throwable error) {

            }
        });

    }

    private void processJSON(String json){
        try{
            JSONObject root = new JSONObject(json);
            JSONArray feeds = root.getJSONArray("feeds");
            String valor_sensor, texto="";
            for(int i=0; i<feeds.length(); i++){
                valor_sensor = feeds.getJSONObject(i).getString("field1");
                texto = texto + valor_sensor + "\n";
            }
            txt.setText(texto);

        }catch(Exception e){
            e.printStackTrace();
        }

    }

    public void bombaOn(View view){
        String url="https://api.thingspeak.com/update?api_key=DCWZL0XSRF7LGE53&field2=1";
        AsyncHttpClient client = new AsyncHttpClient();
        client.get(url, new AsyncHttpResponseHandler() {
            @Override
            public void onSuccess(int statusCode, Header[] headers, byte[] responseBody) {
                if (statusCode==200){
                    String response = new String(responseBody);
                    Toast.makeText(MainActivity.this, response, Toast.LENGTH_SHORT).show();
                }
            }

            @Override
            public void onFailure(int statusCode, Header[] headers, byte[] responseBody, Throwable error) {

            }
        });

    }

    public void bombaOff(View view){
        String url="https://api.thingspeak.com/update?api_key=DCWZL0XSRF7LGE53&field2=0";
        AsyncHttpClient client = new AsyncHttpClient();
        client.get(url, new AsyncHttpResponseHandler() {
            @Override
            public void onSuccess(int statusCode, Header[] headers, byte[] responseBody) {
                if (statusCode==200){
                    String response = new String(responseBody);
                    Toast.makeText(MainActivity.this, response, Toast.LENGTH_SHORT).show();
                }
            }

            @Override
            public void onFailure(int statusCode, Header[] headers, byte[] responseBody, Throwable error) {

            }
        });
    }
}