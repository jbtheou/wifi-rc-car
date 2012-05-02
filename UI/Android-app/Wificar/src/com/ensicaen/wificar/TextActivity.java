package com.ensicaen.wificar;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

import com.ensicaen.wificar.R;


import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

/**
 * Classe pour la gestion de "l'activité" de commande sans la CMUcam, avec l'accéléromètre
 * @author Jean-Baptiste Théou
 * @version 0.1
 */

public class TextActivity extends Activity {
	// Pour gérer l'accéléromètre
	private SensorManager mSensorManager;
	// Champ de texte pour la direction
	private TextView text_dir;
	// Champ de texte pour la vitesse
	private TextView text_vit;
	// Tableau contenant la commande pour le microcontroleur
	static byte[] commande = new byte[5];
	
	/**
	 * Appelé lors de la création de l'activité
	 */
	
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // On charge le layout associé à cette activité
        setContentView(R.layout.text);
        // On se connecte à l'accéléromètre
        mSensorManager = (SensorManager)getSystemService(Context.SENSOR_SERVICE); 
        mSensorManager.registerListener(mSensorListener, mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER), 
        SensorManager.SENSOR_DELAY_NORMAL); 
        // On se connecte au champs textes
        text_dir = (TextView) findViewById(R.id.textDir);
        text_vit = (TextView) findViewById(R.id.textVit);
        // On initialise la commande 
    	commande[0] = 0x0;
        commande[1] = 0x0;
        commande[2] = 0x0;
        commande[3] = 0x0;
        commande[4] = 0x0;
    }
    
    /**
     * Met à jour l'affichage avec les nouvelles valeurs
     * @param iY   La position en Y (Direction)
     * @param iZ   La position en Z (Vitesse)
     * @return void
     */

    public void Position( float iY, float iZ)
    {  
    	text_dir.setText(" "+(byte)iY);
    	text_vit.setText(" "+(byte)iZ);
    }
    
    // Permet de détecter les modifications au niveau de l'accéléromètre
    
    private final SensorEventListener mSensorListener = new SensorEventListener() { 
        
    	// En cas de changement 
        public void onSensorChanged(SensorEvent se)
        { 
        	// On récupère la valeur en y
            float y = se.values[1]; 
            // On récupère la valeur en z
            float z = se.values[2];
            
            /* On étudie les cas possibles : 
             *  -> Si la valeur est positive, on transmet la commande "Forward"
             *  -> Si la valeur est négative, on transmet la commande "Backward", et 
             *     on prend la valeur absolue de la mesure
             */
            if(z>0)
            	commande[1] = 0x1;
            else
            {
            	commande[1] = 0x0;
            	z=-z;
            }
            commande[2] = (byte)z;
            
            /* On étudie les cas possibles : 
             *  -> Si la valeur est positive, on transmet la commande "Right"
             *  -> Si la valeur est négative, on transmet la commande "Left", et 
             *     on prend la valeur absolue de la mesure
             */
            if(y > 0)
            	commande[3] = 0x1;
            else
            {
            	commande[3] = 0x0;
            	y = -y;
            }
            commande[4] = (byte)y;
            // On met à jour les valeurs sur l'écran
            Position(y,z);
            // On teste si l'on a validé la commande (Appuie sur GO)
            if(commande[0] != 0x0)
            {
            	// On envoie la commande via UDP sur le serveur (Port 9762 pour le
            	// serveur gérant l'accéléromètre)
	            int server_port = 9762;
	        	String server_ip = "192.168.1.1";
	        	try {
					sendUDPMessage(new String(commande),server_ip,server_port);
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
            }  
        }

		@Override
		public void onAccuracyChanged(Sensor sensor, int accuracy) {
			// TODO Auto-generated method stub
			
		}         
   }; 
    
   @Override 
   protected void onResume() 
   { 
        super.onResume(); 
        mSensorManager.registerListener(mSensorListener, mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_NORMAL); 
   } 
    
   @Override 
   protected void onStop() 
   { 
        mSensorManager.unregisterListener(mSensorListener); 
        super.onStop(); 
   } 
   
   // Gestion du clic sur les boutons
   public void OnclickHandler(View view) throws Exception {
	   // On test le bouton mis en jeu :
	   switch (view.getId()) {
	   		// Si le bouton est le bouton GO, on valide la commande
	   		case R.id.buttonGo: 
	   			commande[0]=0x1;
	   			break;
	   		// Si le bouton est le bouton STOP, on annule la commande
	   		// et on envoie un paquet pour notifier l'annulation au microcontroleur
	   			
	   		case R.id.buttonStop:
	   			commande[0]=0x0;
	   			int server_port = 9762;
	        	String server_ip = "192.168.1.1";
	        	try {
					sendUDPMessage(new String(commande),server_ip,server_port);
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
	   			break;
	   }
   }
   // Méthode pour envoyer un paquet UDP
   public void sendUDPMessage(String messageStr,String server_ip,int server_port) throws Exception {
   	try {
		     DatagramSocket s = new DatagramSocket();
		     InetAddress local = InetAddress.getByName(server_ip);
		     int msg_length=messageStr.length();
		     byte[] message = messageStr.getBytes();
		     DatagramPacket p = new DatagramPacket(message, msg_length,local,server_port);
		     s.send(p);
		     s.close();
		     Log.d("UDP", "***Packet sent from server");
		}
		catch (Exception e)
		{
			Log.d("UDP", "***Fail");
		}
   }
}