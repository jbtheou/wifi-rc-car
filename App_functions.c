/*********************************************************************
 * FileName:        App_functions.c
 * Dependencies:    main.h
 * Processor:       PIC32MX795F512L
 * Compiler:        Microchip C32 v1.11A or higher
 *
 * Overview: Fichier contenant les fonctions utilisateurs propres à l'application
 ********************************************************************/
#include "main.h"


/******************************************************************************
 * Function:       short directionCommand(short consigne, short mesure)
 *
 * Overview:       "Algorithme" ( :) ) de controle avec par action proportionel
 *
 * Auteur               Date         Commentaire
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Théou Jean-Baptiste  7 avril 2011 Première version   
 * Descoubes hugo  		16 mai  2011 vs 1.1                           
 *****************************************************************************/
short directionCommand(short consigne, short mesure){
short erreur;

	erreur = (consigne - mesure);
	
return erreur*2;
}


/******************************************************************************
 * Function:      short propulsionCommand (short consigne, float mesure)
 *
 * Overview:      Loi de commande pour l'asservissement de courant (action PI)
 *
 * Auteur               Date         Commentaire
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Théou Jean-Baptiste	avril	2011
 * Descoubes hugo  		16 mai  2011 vs 1.1                               
 *****************************************************************************/
short propulsionCommand (short consigne, float mesure){
	   	float Commande; 			// Commande calculée actuelle
	   	float DeltaCommande; 		// Variation de la commande
	   	float DeltaEpsilon; 		// Variation de la commande
	   	short Output	 ;			// Sortie actuelle du régulateur
	   	float Epsilon	; 			// Sortie actuelle du régulateur
		float floatOutput;
static 	float LastCommande=0.0; 	// commande calculée passée d'une période d'échantillonage
static 	float LastEpsilon=0.0;	 	// commande passée du régulateur


	//Erreur de sortie Consigne
	Epsilon =  ( (float) consigne / 10.0 ) - mesure;
	
	// Varitaion de l'erreur
	DeltaEpsilon= Epsilon - LastEpsilon;
	
	//Variation de la commande
	DeltaCommande = Kp * ( Epsilon + ( Ti*DeltaEpsilon ));
	
	//Calcul de la commande
	Commande = LastCommande + DeltaCommande;
	
	// Remise à l'echelle de la commnande en sortie du régulateur
	floatOutput =( Commande / Ti );
	Output = (short) floatOutput;
	
	//Gestion de la saturation
	if (Output<OutputMin) 	
	{
		Output=OutputMin;
		Commande = (float) OutputMin * Ti;
	}
	else if (Output>OutputMax) 
	{
		Output=OutputMax;
		Commande = (float) OutputMax * Ti;
	}
	
	//Mis à jour des données static
	LastEpsilon=Epsilon;
	LastCommande=Commande;

return Output;
}



/******************************************************************************
 * Function:        short AssServoFloat(short consigne_send, short mesure_send)
 *
 * Overview:        Algorithme de controle RST pour la commande de direction
 *
 * Auteur               Date         Commentaire
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Théou Jean-Baptiste  7 avril 2011 Première version
 * Descoubes hugo  		16 mai  2011 vs 1.1                                    
 *****************************************************************************/
//short AssServoFloat(short consigne_send, short mesure_send)
//{
//	static float Rp[3] = {0.0012,0.0,0.0};
//	static float Rn[4] = {99.94500,-249.1903,198.8978,-49.6512};
//	static float Rd[4] = {1.0,-2.9930,2.9860,-0.9930};
//    static float consigne[3] = {0,0,0}; // Consigne t,t-1,t-2
//	static float mesure[4]	= {0,0,0,0}; // Mesure t,t-1,t-2,t-3
//	static float commande[4] = {0,0,0,0}; // Commande t,t-1,t-2,t-3
//    static float erreur;
//
//
//	/***  Décalage des données ***/
//
//	// Consigne : 
//	consigne[2] = consigne[1];
//	consigne[1] = consigne[0];
//	consigne[0] = (float)consigne_send;
//	// Mesure :
//	mesure[3] = mesure[2];
//	mesure[2] = mesure[1];
//	mesure[1] = mesure[0];
//	mesure[0] = (float) mesure_send;
//	// commande :
//	commande[3] = commande[2];
//	commande[2] = commande[1];
//	commande[1] = commande[0];
//
//	/*** Calcul de la commande ***/
//
//	erreur = (Rp[0]*consigne[0] + Rp[1]*consigne[1] + Rp[2]*consigne[2]) - (Rn[0]*mesure[0] + Rn[1]*mesure[1] + Rn[2]*mesure[2] + Rn[3]*mesure[3] );
//	commande[0] = (erreur/100.0 - (Rd[1]*commande[1] + Rd[2]*commande[2] + Rd[3]*commande[3]));
//
//	return (short)commande[0];
//}


/******************************************************************************
 * Function:       void SaveAuxVar(BYTE n, BYTE *var, BYTE size)  
 *
 * Overview:      Sauvegarde de variables dans l'EEPROM
 *
 * Auteur               Date         Commentaire
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * skynet78             2010		http://www.microchip.com/forums/tm.aspx?m=526126&mpage=&settheme=Mobile    
 * Descoubes hugo  		16 mai  2011 vs 1.1                               
 *****************************************************************************/
void SaveAuxVar(BYTE n, BYTE *var, BYTE size)  
{  
	#if defined(STACK_USE_MPFS) || defined(STACK_USE_MPFS2)  
	if( (MemoryIndexVar[n] + size +1) > MPFS_RESERVE_BLOCK)  
		UARTputs("SYSTEM ERROR : Memory out of MPFS Reserved Block\r\n");  
	else  
	{    
	   	XEEBeginWrite(MemoryIndexVar[n]);  
	   	XEEWrite(0x60);  
	   	XEEWriteArray((BYTE*)var, size);  
	}  
	MemoryIndexVar[n+1] = MemoryIndexVar[n] + size + 1;  
	#endif  
}  

/******************************************************************************
 * Function:       void ReadAuxVar(BYTE n, BYTE *var, BYTE size)  
 *
 * Overview:       Lecture de variables dans l'EEPROM
 *
 * Auteur               Date         Commentaire
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * skynet78             2010		http://www.microchip.com/forums/tm.aspx?m=526126&mpage=&settheme=Mobile                                 
 *****************************************************************************/
void ReadAuxVar(BYTE n, BYTE *var, BYTE size)  
{  
	BYTE c;  
	XEEReadArray(MemoryIndexVar[n], &c, 1);  
    if(c == 0x60u)  
   		XEEReadArray(MemoryIndexVar[n]+1, (BYTE*)var, size); 	
} 



/********************************************************************
 * Function:        void UARTputs(unsigned char * buffer)
 *
 * Overview:        Envoi d'une chaine de charactère au PC via UART (par polling)
 *
 * Auteur               Date         Commentaire
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Théou Jean-Baptiste  7 avril 2011 Première version                                
 *******************************************************************/
void UARTputs(char * buffer){

	while(*buffer != '\0'){

		while(!UARTTransmitterIsReady(UART3A));
		UARTSendDataByte(UART3A, *buffer++);
	}
}


/********************************************************************
 * Function:        void UARTputsIP(void)
 *
 * Overview:        Envoi l'addresse IP de l'application au PC via UART
 *
 * Auteur               Date         Commentaire
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Théou Jean-Baptiste  7 avril 2011 Première version                                
 *******************************************************************/
void UARTputsIP(void){
unsigned char IPField[4];
unsigned char i;

	for(i = 0; i < (unsigned char) sizeof(IP_ADDR); i++){

	    uitoa( (WORD) AppConfig.MyIPAddr.v[i], (BYTE*) IPField);
		UARTputs(IPField);
		if (i < (unsigned char) sizeof(IP_ADDR) - 1) UARTputs(".");
	}
}



/********************************************************************
 * Function:        void putrsUART2(unsigned char * String)
 *
 * Overview:        Envoi d'une chaine de charactère au PC via UART 
 *					Fonction utilisée par défaut dans la stack IP Microchip
 *
 * Auteur               Date         Commentaire
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Théou Jean-Baptiste  7 avril 2011 Première version     
 * Descoubes hugo  		16 mai  2011 vs 1.1                               
 *******************************************************************/
void putrsUART2(unsigned char * String){

	UARTputs("MICROCHIP UARTPuts hook : ");
	UARTputs(String);
}


