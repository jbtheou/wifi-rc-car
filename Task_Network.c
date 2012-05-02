/*********************************************************************
 * FileName:        Task_Network.c
 * Dependencies:    main.h
 * Processor:       PIC32MX795F512L
 * Compiler:        Microchip C32 v1.11A or higher
 *
 * Overview: Appel de la stack IP de Microchip (Tâche périodique)
 ********************************************************************/
#include "main.h"


/********************************************************************
 * Tache:        void TaskNetwork(void *pvParameters)
 *
 * Overview:     Tache responsable de l'appel de la stack IP et WIFI de Microchip
 *
 * Auteur               Date         Commentaire
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Théou Jean-Baptiste  7 avril 2011 Première version
 * Descoubes hugo  		16 mai  2011 vs 1.1              			                 
 *******************************************************************/
void TaskNetwork( void *pvParameters ){
    portTickType xLastWakeTime;
    const portTickType xFrequency = NETWORK_STACK_REFRESH_PERIOD;
    DWORD 	secondCount;
    DWORD 	dwLastIP;
    BOOL	IPmodifBOOL = TRUE;

	/* Initialisations */
        xLastWakeTime = xTaskGetTickCount();
	dwLastIP = AppConfig.MyIPAddr.Val;
	secondCount = xTaskGetTickCount();

	for( ;; ){

		/* Clignotement LED (IP activity) - période de 1s */
        if(xTaskGetTickCount() - secondCount >= configTICK_RATE_HZ){

            secondCount = xTaskGetTickCount();
#if DEV_CARD
            PORTToggleBits(IOPORT_A,BIT_0);
#endif
#if PROD_CARD
            PORTToggleBits(IOPORT_E,BIT_0);
#endif
        }

        // This task performs normal stack task including checking
        // for incoming packet, type of packet and calling
        // appropriate stack entity to process it. Uniquement mise à jour UDP, TCP, IP , ARP et MAC
        StackTask();

        // This tasks invokes each of the core stack application tasks
        StackApplications();

        /* Affichage de la nouvelle IP (via UART) si changement */
	if(dwLastIP != AppConfig.MyIPAddr.Val){
            
            dwLastIP = AppConfig.MyIPAddr.Val;
            xQueueSend(xQueueDebugPrintIP, &IPmodifBOOL, 0);		// non bloquant
	}
         /* Call UDP server */
#if CMUcam_IS_USE
        UDPServer_CMUcam();
#endif
        UDPServer_Cmd();
        UDPServer_Cmd_Acc();
	/* Bloque la tâche durant 10 Tick (Tick du noyau) */
         vTaskDelayUntil( &xLastWakeTime, xFrequency );
	}
}
