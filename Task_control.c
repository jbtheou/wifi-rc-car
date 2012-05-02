/*********************************************************************
 * FileName:        Task_control.c
 * Dependencies:    main.h
 * Processor:       PIC32MX795F512L
 * Compiler:        Microchip C32 v1.11A or higher
 *
 * Overview: T�che responsable des diff�rents lois de commande
 ********************************************************************/
#include "main.h"


/********************************************************************
 * Tache:        void TaskControl(void *pvParameters)
 *
 * Overview:      	T�che responsable des diff�rents lois de commande.
 * 					Asservissement de position pour la direction, asservissement de 
 *					courant (couple) pour la propulsion et supervision du niveau de 
 *					batterie. Une fois les traitement fais, elle est responsable du 
 *					post des grandeurs interm�daire pour le debug � la t�che d'affichage
 *
 * Auteur               Date         Commentaire
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Th�ou Jean-Baptiste  7 avril 2011 Premi�re version
 * Descoubes hugo  		16 mai  2011 vs 1.1              			                 
 *******************************************************************/
void TaskControl(void *pvParameters){	
/* asservissement de position */
short sDirMeasure; 	   				// Mesure de position (servomoteur). Unsigned integer sur 10 bits
short sDirConsigne; 	   			// Consigne de position (servomoteur). Unsigned integer sur 10 bits
short sDirCommand; 	   				// Commande de position (servomoteur). entier compris entre 0 et 100, rapport cyclique pour PWM
  				
/* asservissement de courant */
float fPropMeasure; 	   			// Mesure image du courant absorb� par la MCC (propulsion).
short sPropConsigne; 	   			// Consigne de courant(propulsion). Unsigned integer sur 10 bits
short sPropCommand; 				// Commande de courant (propulsion). entier compris entre 0 et 100, rapport cyclique pour PWM	   				

short sPowerMeasure; 					// Mesure du niveau de batterie. Unsigned integer sur 10 bits
char  stateControl = PROPULSION_CONTROL;// machnie d'�tat pour la commande
struct_DebugPrint 	printData;  		// Donn�es � afficher (debug)
struct_mesures 		measuresReceive;	// Mesures re�ues depuis l'ISR du timer 3

	for( ;; ){

		/* R�cup�ration des grandeurs de mesures pour les lois de commande */
		xQueueReceive( xQueueAcquiData, &measuresReceive, portMAX_DELAY); 	// fonction bloquante

		/* Mise � jour mesures */
		sDirMeasure 	= measuresReceive.sDirMeasure;
		fPropMeasure	= (float) measuresReceive.sCurrentMeasure / 35.0;		// 35 = facteur d'�chelle (capteur + conditionneur + ADC)
		sPowerMeasure	= measuresReceive.sBattMeasure;

		/* Mise � jour mesures - Affichage par le r�seau */
		resultat = sDirMeasure;									// Mise � jour var. globale r�seau
		resultat_courant = measuresReceive.sCurrentMeasure;		// Mise � jour var. globale r�seau

		/* Mise � jour consignes */

		/* Protection Vitesse*/
		xSemaphoreTake(xSemaphoreVitesse,portMAX_DELAY);
		{
			sPropConsigne	= Vitesse;							// r�cup�ration var. globale r�seau	
		}
		xSemaphoreGive(xSemaphoreVitesse);

		/* Protection ConsDir */
		xSemaphoreTake(xSemaphoreConsDir,portMAX_DELAY);
		{
			sDirConsigne	= ConsDir;							// r�cup�ration var. globale r�seau
		}
		xSemaphoreGive(xSemaphoreConsDir);


		/* Machine d'�tat - t�che contr�le/commande/supervision */
		switch(stateControl){

			case PROPULSION_CONTROL :
		
					/* Protection Consigne courant */
					if(sPropConsigne > 100){

						sPropConsigne = 100;
					}
					else if(sPropConsigne < 0){

						sPropConsigne = 0;
					}

					/* Asservissement de courant (couple). R�gulation PI (mod�le non-lin�aire) 	*/
					/* Calcul fais avec des flottant - temps de traitement long					*/
					sPropCommand = propulsionCommand (sPropConsigne , fPropMeasure);
					
			case PROPULSION_PWM :
			
					if((fPropMeasure < 0.0) || (fPropMeasure > MAX_CURRENT) ){
	
						sPropCommand = 0;
					}
                                       
					/* Mise � jour rapport cyclique pour module PWM propulsion */

                                        /* Protection au niveau des erreurs de calculs */
                                        if(sPropCommand < 10)
                                        {
                                            sPropCommand = 0;
                                        }
					SetDCOC4PWM(ReadPeriod3() * sPropCommand / 100 );
			
			case DIRECTION_CONTROL :

					/* Protection Consigne direction */
					if(sDirConsigne > HAUT_BUTE){
	
						sDirConsigne = HAUT_BUTE;
					}
					else if(sDirConsigne < BAS_BUTE){
	
						sDirConsigne = BAS_BUTE;
					}
	
					/* Limitation sur la var globale ConsDir fait localement sur le MCU ... pour le moment ! */
						
					/* Protection ConsDir */
					xSemaphoreTake(xSemaphoreConsDir,portMAX_DELAY);
					{
						ConsDir	= sDirConsigne;
					}
					xSemaphoreGive(xSemaphoreConsDir);

					/* Asservissement de position. R�gulation proporionnelle (mod�le grandement non-lin�aire) */
					sDirCommand = directionCommand(sDirConsigne, sDirMeasure);

			
			case DIRECTION_PWM :
		
					/* V�rification but�es direction */
					if( sDirMeasure < HAUT_BUTE && sDirMeasure > BAS_BUTE){
	
						if(init_ok == 0){

							/* Attendre initialisation utilisateur via r�seau */
							sDirCommand = 0;
						}
						else{
	
							/* valeur absolue et sens de rotation - PWM comprise entre 0 et 100 */
							if ( sDirCommand < 0 ){
								/* Sens de rotation pour le driver de bras de pont */
								PORTSetBits(BROCHE_DIR_DIRECTION);
								sDirCommand = -sDirCommand;
							}
							else{
								/* Sens de rotation pour le driver de bras de pont */
								PORTClearBits(BROCHE_DIR_DIRECTION);
							}
	
							/* Protection et limitation Commande */
							if(sDirCommand < 20){
								sDirCommand = 0;			// Pas de commande si dans dead zone
							}
							else if(sDirCommand < 30){
								sDirCommand = 40;			// compensation dead zone
							}
							else if (sDirCommand > 100){
								sDirCommand = 100;			// limitation PWM
							}				
						}
					}
					else{
	
						sDirCommand = 0;
					}

					/* Mise � jour rapport cyclique pour module PWM direction */
					SetDCOC2PWM(ReadPeriod3() * sDirCommand / 100 );

			case POWER_SUPERVIOR :

					break;
						
			default:
					break;
		}

		/* Post les valeurs � afficher pour le debug vers la t�che d'affichage */
		printData.commandeDir 	= sDirCommand;
		printData.mesureDir   	= sDirMeasure;
		printData.consigneDir 	= sDirConsigne;
		printData.consigneMove = (float) sPropConsigne;
		printData.mesureMove   = fPropMeasure;
		printData.commandeMove = sPropCommand;
		printData.mesurePower 	= sPowerMeasure;

		xQueueSend(xQueueDebugPrint, &printData, 0);
	}
}
