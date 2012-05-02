package com.ensicaen.wificar;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

import com.ensicaen.wificar.R;


import android.util.Log;

/**
 * Classe pour la gestion de "l'activité" de commande sans la CMUcam, sans l'accéléromètre
 * @author Jean-Baptiste Théou
 * @version 0.1
 */

public class OldActivity extends Activity {

	// Tableau contenant la commande pour le microcontroleur
	static char[] commande = new char[5];
	
	/**
	 * Appelé lors de la création de l'activité
	 */
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // On charge le layout associé à cette activité
        setContentView(R.layout.old);
        // On initialise la commande 
        commande[0] = 0x0;
        commande[1] = 0x0;
        commande[2] = 0x0;
        commande[3] = 0x0;
        commande[4] = 0x0;
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

    // Gestion du clic sur les boutons
 	public void OnclickHandler(View view) throws Exception {
 		int server_port = 9761;
 		String server_ip = "192.168.1.1";
 		switch (view.getId()) {
 			case R.id.buttonForward:
 				
 				commande[0] = 0x1;
				break;
 			case R.id.buttonBackward:
 				commande[0] = 0x2;
 				break;
 			case R.id.buttonLeft:
 				commande[1] = 0x0;
 				commande[2] = 0x0;
 				commande[3] = 0x1;
 				commande[4] = 0x0;
 				break;
 			case R.id.buttonStop:
 				commande[0] = 0x0;
 		        commande[1] = 0x0;
 		        commande[2] = 0x0;
 		        commande[3] = 0x0;
 		        commande[4] = 0x0;
 				break;
 			case R.id.buttonRight:
 				commande[1] = 0x0;
 				commande[2] = 0x0;
 				commande[3] = 0x0;
 				commande[4] = 0x1;
 				break;
 			case R.id.buttonUp:
 				commande[1] = 0x1;
 				commande[2] = 0x0;
 				commande[3] = 0x0;
 		        commande[4] = 0x0;
 				break;
 			case R.id.buttonDown:
 				commande[1] = 0x0;
 				commande[2] = 0x1;
 				commande[3] = 0x0;
 		        commande[4] = 0x0;
 				break;
 		 }
 		sendUDPMessage(new String(commande),server_ip,server_port);
 		 
 	}
}