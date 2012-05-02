/*********************************************************************
 *  Main Application Entry Point 
 *********************************************************************
 * FileName:        Main.c
 * Dependencies:    main.h
 * Processor:       PIC32MX795F512L
 * Compiler:        Microchip C32 v1.11A or higher
 *
 * Overview: Fichier principal du projet contenant le main, les ISR et les gestions des
 * exceptions (PIC32 Core) et des débordement de piles (freeRTOS kernel). 
 ********************************************************************/

/* Bits de configuration pour un PIC32MX795F512L (Core config) */
#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF
#pragma config FPBDIV = DIV_1, POSCMOD = XT, FNOSC = PRIPLL, CP = OFF

/* Header Dependencies */
#include "main.h"


/* Appel wrapper afin d'assurer les commutations de context de FreeRTOS (isr_wrapper.S) */
/* WRAPPER FreeRTOS : debut de sauvegarde dans la stack de la tâche interrompue		  	*/
/* la fin se fait toujours dans le tableau xISRStack[ configISR_STACK_SIZE ] (port.c)*/
/* Il s'agit d'une sorte de Tas ou se font les sauvegardes de contexte de FreeRTOS*/
void __ISR(_TIMER_3_VECTOR, ipl3) IntTimer3Wrapper(void);
void __ISR(_UART_1A_VECTOR, ipl2) IntUart1AWrapper(void);
void __ISR(_UART_3A_VECTOR,ipl1) IntUart3AWrapper(void);
/*********************************************************************
 * ISR (TIMER 3) :   void __ISR(_TIMER_3_VECTOR, ipl3) Timer3Wrapper(void)
 *
 *
 * Note:  Routine d'interruption appelée toutes les 500us et devant assurer
 * les acquisitions de trois grandeurs de mesures (position servomoteur , courant 
 * du moteur pour la propulsion et niveau alimentation de la batterie côté MCU). 
 * 500us est à la fois la fréquence d'échantillonnages des 
 * différentes grandeurs converties ainsi que la fréquence de découpage utilisée par les 
 * différents convertiiseurs statiques. Une fois les acquisition faites, elles 
 * sont postées par à la tâche dédiée au contrôle/commande/supervision
 * de l'application (Task_control.c) 
 ********************************************************************/
void IntTimer3Handler(void){
portBASE_TYPE xYieldRequired = pdFALSE; // Test pour l'appel du scheduler
volatile struct_mesures acquiData;      // Mesures postées à la tâches d'asservissement

	/* RAZ IRQ Flag du Timer 3 */
	INTClearFlag(INT_T3);

	/* Mesure POSITION (solution n°1) : Acquisition automatique après fin de conversion, mode scan sur broche AN6, AN10 et AN11 */
	/* valeurs converties stockées respectivement dans ADC_BUF0 (alim.), ADC_BUF1 (position) et ADC_BUF2 (courant)   */
	acquiData.sDirMeasure = (short) ReadADC10(1);  

	/* Mesure COURANT */
	acquiData.sCurrentMeasure = (short) ReadADC10(2);  

	/* Mesure NIVEAU ALIMENTATION */
	acquiData.sBattMeasure = (short) ReadADC10(0); 

	/* Post pour la tâche de contrôle/commande/supervision  (Task_control.c)  */
	xQueueSendFromISR( xQueueAcquiData, (void *) &acquiData, &xYieldRequired);

        /* Appel au scheduler en cas de besoin */
        portEND_SWITCHING_ISR( xYieldRequired );

	/* DEBUG : code pour le debug  */
	#if DEBUG_IS_ON
		PORTToggleBits(BROCHE_DEBUG); 		// clignotement d'une LED
	#endif
}

/*********************************************************************
 * ISR (UART1) :   void __ISR(_UART1_VECTOR, ipl2) IntUart1Wrapper(void)
 *
 *
 * Note:  Routine d'interruption déclanchée lors de la réception de
 * données via UART. Permet de récupérer une trame de réponse de la
 * CMUcam
 ********************************************************************/

void IntUart1AHandler(void)
{
    // Pour tester si nous devons réveiller une tache
    static portBASE_TYPE xYieldRequired = pdFALSE;
    // We use a state machine for processing in buffer fill
    static enum  {
		UART_FIRST_CHAR = 0,
                UART_FILL_BUFFER
    } UARTSM = UART_FIRST_CHAR;

    // We use a state machine for detect the begging of a frame (ACK)
    static enum {
		A = 0,
		AC,
                ACK,
                INIT
	} INIT_DETEC = A;
    // We use a state machine for detect the begging of frame for bad command (NCK)
    static enum {
		N = 0,
		NC,
                NCK,
                BAD
	} BAD_DETEC = N;

    // We use a state machine for detect the end of a frame (@FIN)
    static enum {
		TEST = 0,
		F,
		FI,
                FIN,
                END
	} FIN_DETEC = TEST;
    
    unsigned char rx;

    // Is this an RX interrupt?
    if(mU1RXGetIntFlag())
    {
        // Clear the RX interrupt Flag
        mU1RXClearIntFlag();

        // We read the receive character
        rx = (char)ReadUART1();
        switch(UARTSM)
        {
            case UART_FIRST_CHAR :
                count = 0;
                /* We test if is a beginning of a frame or wrong frame
                 * (print_ACK or print_NCK in CMUcam)
                */
                switch(rx)
                {
                    case 'A' : INIT_DETEC++;
                               break;
                    case 'N' : BAD_DETEC++;
                               break;
                    case 'C' : INIT_DETEC++;
                               BAD_DETEC++;
                               break;
                    case 'K' : INIT_DETEC++;
                               BAD_DETEC++;
                               break;
                    default  : INIT_DETEC=A;
                               BAD_DETEC=N;
                               break;
                }

                // If it's a new frame,
                if(INIT_DETEC == INIT)
                {
                    INIT_DETEC = A;
                    BAD_DETEC = N;
                    UARTSM = UART_FILL_BUFFER;
                    rxbuffer[0] = 'A';
                    rxbuffer[1] = 'C';
                    rxbuffer[2] = 'K';
                    count=3;
                }
                else if(BAD_DETEC == BAD)
                {
                    rxbuffer[0] = 'N';
                    rxbuffer[1] = 'C';
                    rxbuffer[2] = 'K';
                    count=3;
                    INIT_DETEC = A;
                    BAD_DETEC = N;
                    UARTSM = UART_FIRST_CHAR;
                    // On désactive l'interruption en RX de l'UART
                    DisableIntU1RX;
                    // We release the semaphore for UDP send
                    xSemaphoreGiveFromISR(xSemaphoreCMUcamTransmissionEnable,&xYieldRequired);
                    portEND_SWITCHING_ISR(xYieldRequired);
                }
                break;

            case UART_FILL_BUFFER :
                // We test if is a end of a frame (print(@FIN) in CMUcam)
                switch(rx)
                {
                    case '@' : FIN_DETEC++;
                               break;
                    case 'F' : FIN_DETEC++;
                               break;
                    case 'I' : FIN_DETEC++;
                               break;
                    case 'N' : FIN_DETEC++;
                               break;
                    default  : FIN_DETEC=TEST;
                               break;
                }
                if( (count >= RX_MAX) || FIN_DETEC == END)
                {
                    // We remove the last 3 char (@FI)
                    if(FIN_DETEC == END)
                        count = count - 3;
                    // We re init the FIN detector
                    FIN_DETEC = TEST;
                    // We re init the UART state machine
                    UARTSM = UART_FIRST_CHAR;
                    /* We disable the interruption from UART until all UDP packet was send
                     * We enable the interruption in UDP_server part
                    */
                    DisableIntU1RX;
                    // We release the semaphore for UDP send
                    xSemaphoreGiveFromISR(xSemaphoreCMUcamTransmissionEnable,&xYieldRequired);
                    portEND_SWITCHING_ISR(xYieldRequired);
                    break;
                }
                rxbuffer[count]=rx;
                count++;
                break;
        }
    }
}

/*********************************************************************
 * ISR (UART 3A) :   void __ISR(_UART_3A_VECTOR,ipl2) IntUart3AWrapper(void)
 *
 *
 * Note:  Routine d'interruption interfaçant l'UART 3A en réception du PIC32 avec le 
 * PC. Cette ISR n'est utilisée que pour du debug.
 ********************************************************************/
void IntUart3AHandler(void){
volatile char data;

	if (UARTReceivedDataIsAvailable(UART3A)){

		/* Lecture data et RAZ IRQ Flag de l'UART3A (côté UART avant côté CPU) */
		data = UARTGetDataByte(UART3A);
	
		/* RAZ IRQ Flag de l'UART3A (côté CPU) */
		INTClearFlag(INT_U3ARX);


		/* DEBUG : code pour le debug  */
		#if DEBUG_IS_ON	
			/* modification de la commande de direction */
			if(data == 'a'){
				ConsDir += 10;
			}
			else if (data == 'z'){
				ConsDir -= 10;
			}
		#endif
	}
}


/*********************************************************************
 * Function :   void _general_exception_handler(unsigned cause, unsigned status)
 *
 *@param cause	entier représentatif de la cause de l'exception (non géré)
 *
 *@param status	(non géré)
 *
 * Note:  fonction appelée si une exception arrive au niveau du CPU du
 * PIC32 (adress error, bus error, arithmetic overflow ...)
 ********************************************************************/
void _general_exception_handler(unsigned cause, unsigned status){

	for( ;; ){
		UARTputs("SYSTEM ERROR : MCU exception !\r");
	}
}


/*********************************************************************
 * Function :   void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed portCHAR *pcTaskName )
 *
 *@param pxTask	Handle (pointeur) sur la tâche ayant subit le débordement. Technique de référencement des tâches 
 * 				sous FreeRTOS
 *
 *@param pcTaskID	pointeur sur l'identifiant (string - configMAX_TASK_NAME_LEN) de la tâche définie dans la TCB
 *
 * Note:  fonction appelée si un débordement de pile associée à une tâche arrive
 * durant l'application
 ********************************************************************/
void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed portCHAR *pcTaskID ){

	for( ;; ){
		UARTputs("SYSTEM ERROR : FreeRTOS Stack Overflow with Task ---->>>  \r");
		UARTputs((char *)pcTaskID);
		UARTputs("  !\r");
	}
}



/*********************************************************************
 *********************************************************************
 *
 * MAIN Function :   Main application entry point.
 *
  *********************************************************************
 ********************************************************************/
int main(void){

	/* Configurations Pile et contrôleur Réseau */
	NetworkInit(); 		// ATTENTION : démasque les IT (Besoin d'un Timer durant la phase d'initialisation !)

	/* Configurations périphériques internes */
	HardwareInit();	

	

	/* Configurations Real Time Operating System */		
	RTOSInit();
        
        /* Configurations variables application */
	SoftwareInit();
        /* Démarrage mode multi-tâche */
#if DEBUG_IS_ON
        UARTputs("\r\n\n*** Starting WI-FI Car Application ***");
	UARTputs("\r\n*** IP Address :    ");
	UARTputsIP();
	UARTputs("    ***\r\n\n");
#endif
	vTaskStartScheduler();

	/* Si on revient ici ... gros soucis ! */
	while (1){
            UARTputs("SYSTEM ERROR : return to main !\r");
        }
}
