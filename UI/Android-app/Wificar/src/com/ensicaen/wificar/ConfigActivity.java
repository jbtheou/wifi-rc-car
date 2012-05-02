package com.ensicaen.wificar;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

import com.ensicaen.wificar.R;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.Toast;

/**
 * Classe pour la gestion de "l'activité" de configuration
 * @author Jean-Baptiste Théou
 * @version 0.1
 */

public class ConfigActivity extends Activity {
	void showToast(CharSequence msg) {
        Toast.makeText(this, msg, Toast.LENGTH_SHORT).show();
    }

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.config);
        Spinner spinner1 = (Spinner) findViewById(R.id.spinner1);
        Spinner spinner2 = (Spinner) findViewById(R.id.spinner2);
        ArrayAdapter<CharSequence> adapter1 = ArrayAdapter.createFromResource(this,
            R.array.increment_array,android.R.layout.simple_spinner_item);
        adapter1.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner1.setAdapter(adapter1);
        spinner1.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener(){

            @Override
            public void onItemSelected(AdapterView<?> parent, View view,
                    int pos, long id) {
            	HttpClient httpClient = new DefaultHttpClient();
                Toast.makeText(parent.getContext(), "Pas de vitesse : " +
                parent.getItemAtPosition(pos).toString(), Toast.LENGTH_SHORT).show();
                StringBuilder uriBuilder = new StringBuilder("http://192.168.1.1/initialisation.html");
                uriBuilder.append("?incvit=" + parent.getItemAtPosition(pos).toString());
                HttpGet request = new HttpGet(uriBuilder.toString());
                HttpResponse response = null;
				try {
					response = httpClient.execute(request);
				} catch (ClientProtocolException e) {
					return;
				} catch (IOException e) {
					return;
				}
				
                int status = response.getStatusLine().getStatusCode();

                // we assume that the response body contains the error message
                if (status != HttpStatus.SC_OK) {
                    ByteArrayOutputStream ostream = new ByteArrayOutputStream();
                    Log.e("HTTP CLIENT", ostream.toString());
                } else {
                    InputStream content;
					try {
						content = response.getEntity().getContent();
					} catch (IllegalStateException e) {
						// TODO Auto-generated catch block
						return;
					} catch (IOException e) {
						// TODO Auto-generated catch block
						return;
					}
					try {
						content.close();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						return;
					}
                }

            }

            @Override
            public void onNothingSelected(AdapterView<?> arg0) {

            			
			}});

        ArrayAdapter<CharSequence> adapter2 = ArrayAdapter.createFromResource(this,
                R.array.increment_array,android.R.layout.simple_spinner_item);
        adapter2.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner2.setAdapter(adapter2);
        spinner2.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener(){

            @Override
            public void onItemSelected(AdapterView<?> parent, View view,
                    int pos, long id) {
            	HttpClient httpClient = new DefaultHttpClient();
                Toast.makeText(parent.getContext(), "Pas de direction : " +
                          parent.getItemAtPosition(pos).toString(), Toast.LENGTH_SHORT).show();
                StringBuilder uriBuilder = new StringBuilder("http://192.168.1.1/initialisation.html");
                uriBuilder.append("?incdir=" + parent.getItemAtPosition(pos).toString());
                HttpGet request = new HttpGet(uriBuilder.toString());
                HttpResponse response = null;
				try {
					response = httpClient.execute(request);
				} catch (ClientProtocolException e) {
					return;
				} catch (IOException e) {
					return;
				}
				
                int status = response.getStatusLine().getStatusCode();

                // we assume that the response body contains the error message
                if (status != HttpStatus.SC_OK) {
                    ByteArrayOutputStream ostream = new ByteArrayOutputStream();
                    Log.e("HTTP CLIENT", ostream.toString());
                } else {
                    InputStream content;
					try {
						content = response.getEntity().getContent();
					} catch (IllegalStateException e) {
						// TODO Auto-generated catch block
						return;
					} catch (IOException e) {
						// TODO Auto-generated catch block
						return;
					}
					try {
						content.close();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						return;
					}
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> arg0) {

            			
			}});
    }
    public void OnclickHandler(View view) throws Exception {
    	Context context = getApplicationContext();
    	HttpClient httpClient = new DefaultHttpClient();
        StringBuilder uriBuilder = new StringBuilder("http://192.168.1.1/initialisation.html");
    	switch (view.getId()) {
			case R.id.buttonLeft:
				uriBuilder.append("?save_value=1" );
			case R.id.buttonRight:
				uriBuilder.append("?save_value=0" );
			case R.id.buttonCenter:
				uriBuilder.append("?save_value=2" );
    	}
        HttpGet request = new HttpGet(uriBuilder.toString());
        HttpResponse response = null;
		try {
			response = httpClient.execute(request);
		} catch (ClientProtocolException e) {
			return;
		} catch (IOException e) {
			return;
		}
		
        int status = response.getStatusLine().getStatusCode();

        // we assume that the response body contains the error message
        if (status != HttpStatus.SC_OK) {
            ByteArrayOutputStream ostream = new ByteArrayOutputStream();
            Log.e("HTTP CLIENT", ostream.toString());
        } else {
            InputStream content;
			try {
				content = response.getEntity().getContent();
			} catch (IllegalStateException e) {
				// TODO Auto-generated catch block
				return;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				return;
			}
			try {
				content.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				return;
			}
        }
        Toast.makeText(context, "Valeur butée sauvée", Toast.LENGTH_SHORT).show();
        
    }
    
}