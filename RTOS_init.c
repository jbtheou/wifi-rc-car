/*********************************************************************
 * FileName:        RTOS_init.c
 * Dependencies:    main.h
 * Processor:       PIC32MX795F512L
 * Compiler:        Microchip C32 v1.11A or higher
 *
 * Overview: Fichier contenant les initialisations du Kernel (T�ches, outils de synchronistaion ...)
 ********************************************************************/

#include "main.h"

/********************************************************************
 * Function:        void RTOSInit(void)
 *
 * Overview:        Cette fonction initialise notre noyau avant l'appel du scheduler
 * 					(cr�ations t�ches, cr�ations files d'attente, s�maphores ...)    
 *
 * Auteur               Date         Commentaire
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Th�ou Jean-Baptiste  7 avril 2011 Premi�re version
 * Descoubes hugo  		16 mai  2011 vs 1.1                                
 *******************************************************************/

void RTOSInit(void){
/*** QUEUE Create ***/	
	xQueueAcquiData = xQueueCreate( 1, sizeof(struct_mesures)); 	// Post des mesures depuis l'ISR vers la t�che pour la commande/contr�le/supervision
	xQueueDebugPrint = xQueueCreate(1, sizeof(struct_DebugPrint)); 	// Post de grandeurs int�merdiaires pour le debug vers la t�che d'affichage
	xQueueDebugPrintIP = xQueueCreate(1, sizeof(BOOL)); 		// Post de la nouvelle IP en cas de changement
        xQueueCMUcam = xQueueCreate(10, sizeof(char));                  // Post des data venant de la CMUcam

        /*** SEMAPHORE Create ***/


	vSemaphoreCreateBinary(xSemaphoreVitesse); 			// Protection variable globale vitesse
	vSemaphoreCreateBinary(xSemaphoreConsDir); 			// Protection variable globale de consigne de direction "consDir"
        vSemaphoreCreateBinary(xSemaphoreCMUcamTransmissionEnable);

/*** TASK Create ***/
	
	/* Task Scheduling Priority :           */
	/* Task Command 		-> 3	*/	
	/* Task Debug 			-> 0	*/
	/* Task Network 		-> 2	*/
        
	xTaskCreate(TaskControl, "Task Control", configASSERVISSEMENT_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, NULL);
	xTaskCreate(TaskDebugUart, "Task Debug", configAFFICHAGE_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(TaskNetwork, "Task Network", configRESEAU_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);

}
