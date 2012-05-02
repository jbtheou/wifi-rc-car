

package com.ensicaen.wificar;

import com.ensicaen.wificar.R;
import android.app.Activity;
import android.os.Bundle;

/**
 * Classe pour la gestion de "l'activit�" avec la CMUcam, avec l'acc�l�rom�tre 
 * @author Jean-Baptiste Th�ou
 * @version 0.1
 */

public class CMUcamActivity extends Activity {
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // On charge le layout pour la CMUcam
        setContentView(R.layout.cmucam);
    }
}