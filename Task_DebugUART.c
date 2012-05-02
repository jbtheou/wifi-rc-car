/*********************************************************************
 * FileName:        Task_DebugUART.c
 * Dependencies:    main.h
 * Processor:       PIC32MX795F512L
 * Compiler:        Microchip C32 v1.11A or higher
 *
 * Overview: Code de la t�che pour le debug (communication via l'UART)
 ********************************************************************/

#include "main.h"

/********************************************************************
 * Tache:        void TaskDebugUart(void *pvParameters)
 *
 * Overview:     Tache responsable de l'affichage via UART (debug) 
 * 				 m�me 115200 Baud/s	le temps de traitement de cette t�che est long
 * 				d'ou sa priorit� (faible)
 *
 * Auteur               Date         Commentaire
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Th�ou Jean-Baptiste  7 avril 2011 Premi�re version
 * Descoubes hugo  		16 mai  2011 vs 1.1              			                 
 *******************************************************************/
void TaskDebugUart(void *pvParameters){
    struct_DebugPrint affichage_resultat; // Structure avec les diff�rentes informations (main.h)
    char buffer[100];                   // Buffer pour l'envoi de la s�quence via UART
    BOOL IPreceiveBOOL = FALSE;

	for( ;; ){

		/* R�cup�ration data */
		xQueueReceive( xQueueDebugPrint, &affichage_resultat, portMAX_DELAY);	// Function Bloquante
		xQueueReceive( xQueueDebugPrintIP, &IPreceiveBOOL, 0);					// Function non Bloquante

		UARTputs("[DIRECTION >> ");
		sprintf(buffer,"cons.: %d, Mes.: %d, Com.: %d]  ",affichage_resultat.consigneDir, affichage_resultat.mesureDir, affichage_resultat.commandeDir);
		UARTputs(buffer);


		UARTputs("[PROPULSION >> ");
		sprintf(buffer,"cons.: %2.1f, Mes.: %2.1f, Com.: %d]  ",affichage_resultat.consigneMove / 10.0, affichage_resultat.mesureMove, affichage_resultat.commandeMove);
		UARTputs(buffer);


		UARTputs("[POWER and TEST >> ");
		sprintf(buffer,"power : %d]\r",affichage_resultat.mesurePower);
		UARTputs(buffer);

		/* Affichage de la nouvelle IP de l'application si modifcation */
		if(IPreceiveBOOL == TRUE){

			IPreceiveBOOL = FALSE;
			UARTputs("\r\n*** IP Address Modification :    ");
			UARTputsIP();
			UARTputs("    ***\r\n");
		}
	}	
}
