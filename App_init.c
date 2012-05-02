/*********************************************************************
 * FileName:        App_init.c
 * Dependencies:    main.h
 * Processor:       PIC32MX795F512L
 * Compiler:        Microchip C32 v1.11A or higher
 *
 * Overview: Fichier contenant les fonction d'initialisation hardware et software de l'application.
 * Configuration périphériques et variables pour l'appli.
 ********************************************************************/
#include "main.h"


/********************************************************************
 * Function:        void HardwareInit(void)
 *
 * Overview:        Cette fonction initialise les périphériques de notre application (UART, ADC, PWM, etc)                
 *
 * Auteur               Date         Commentaire
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Théou Jean-Baptiste  7 avril 2011 Première version
 * Descoubes hugo  		16 mai  2011 vs 1.1                
 *******************************************************************/
void HardwareInit(void){

/*** UART Configuration ***/

			/* Configuration - UART3A (celle câblée sur la maquette EXPLORER 16) 		*/
			/* Broches Tx et RX uniquement, 8bits de données, pas de bit de parité,		*/
			/* 1 bit de stop, débit  9600Bauds, aucune gestion de la FIFO (default mode)*/
			UARTConfigure(UART3A, UART_ENABLE_PINS_TX_RX_ONLY);
			UARTSetLineControl(UART3A, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
  			UARTSetDataRate(UART3A, GetPeripheralClock(), DESIRED_BAUDRATE); // Le system performance est fait de le Network Init 
			
			/* Interrupt Configuration - démasquage IT propres à l'utilisation de l'UART3A */
			INTClearFlag(INT_U3ARX);
			INTSetVectorPriority(INT_UART_3A_VECTOR,INT_PRIORITY_LEVEL_1);		
			INTSetVectorSubPriority(INT_UART_3A_VECTOR,INT_SUB_PRIORITY_LEVEL_0);
			INTEnable(INT_SOURCE_UART_RX(UART3A),INT_ENABLED);

			/* Contrôle - Démarrage de l'UART3A et validation des broches Rx et Tx */
			UARTEnable(UART3A, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
#if CMUcam_IS_USE
                        /* Configuration - UART1 (Communication CMUcam)		*/
			/* Broches Tx et RX uniquement, 8bits de données, pas de bit de parité,		*/
			/* 1 bit de stop, débit  9600Bauds, aucune gestion de la FIFO (default mode)*/
                        UARTConfigure(UART1, UART_ENABLE_PINS_TX_RX_ONLY);
			UARTSetLineControl(UART1, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
  			UARTSetDataRate(UART1, GetPeripheralClock(), DESIRED_BAUDRATE_CMUCAM); // Le system performance est fait de le Network Init

			/* Interrupt Configuration - démasquage IT propres à l'utilisation de l'UART1 */
			INTClearFlag(INT_U1RX);
			INTSetVectorPriority(INT_UART_1_VECTOR,INT_PRIORITY_LEVEL_2);
			INTSetVectorSubPriority(INT_UART_1_VECTOR,INT_SUB_PRIORITY_LEVEL_0);
			INTEnable(INT_SOURCE_UART_RX(UART1),INT_ENABLED);

			/* Contrôle - Démarrage de l'UART1 et validation des broches Rx et Tx */
			UARTEnable(UART1, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
#endif
                        /*** ADC Configuration ***/

			/* Contrôle - Arrêt de l'ADC */
			CloseADC10();

			/* Paramétrage pour la configuration du module ADC */
				// Turn module on | output in integer | trigger mode auto | enable  autosample
				#define PARAM1  ADC_MODULE_ON | ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON
	
				// define setup parameters for OpenADC10
			    // ADC ref external    | disable offset test    | enable scan mode | perform 3 samples | use one buffer | use MUXA mode
	       		// note: to read X number of pins you must set ADC_SAMPLES_PER_INT_X
				#define PARAM2  ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_ON | ADC_SAMPLES_PER_INT_3 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF
	
				// define setup parameters for OpenADC10
				// use ADC internal clock | set sample time
				#define PARAM3  ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_15
	
				// define setup parameters for OpenADC10
				// set AN4 and AN5
				#define PARAM4	ENABLE_AN10_ANA | ENABLE_AN11_ANA | ENABLE_AN6_ANA
	
				// define setup parameters for OpenADC10
				// do not assign channels to scan
				#define PARAM5	SKIP_SCAN_AN0 | SKIP_SCAN_AN1 | SKIP_SCAN_AN2 | SKIP_SCAN_AN3 | SKIP_SCAN_AN4 | SKIP_SCAN_AN5 | SKIP_SCAN_AN7 | SKIP_SCAN_AN8 | SKIP_SCAN_AN9 | SKIP_SCAN_AN12 | SKIP_SCAN_AN13 | SKIP_SCAN_AN14 | SKIP_SCAN_AN15

	//			/* AUTRE CONFIUGRATION, SANS LE MODE SAMPLING */		
	//			/* Configuration - Format résultat (entier non-signé sur 16bits), référence sur compteur interne, SHA holding ... */
	//			#define PARAM1  ADC_FORMAT_INTG16 | ADC_CLK_MANUAL  | ADC_SAMP_OFF  | ADC_AUTO_SAMPLING_OFF						// ADC_CLK_AUTO |  ADC_AUTO_SAMPLING_ON
	//	
	//			/* Configuration - Vref+ = Vdd et Vref- = Vss, pas de calibration d'offset, pas de scan (uniquement sur côté/sample A) 	*/
	//			/* Le buffer est constitué d'un mot de 16bits, utilisation du côté/sample A seulement 									*/
	//			#define PARAM2  ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF | ADC_SCAN_OFF
	//
	//			/* Configuration - Référence de l'ADC sur RC interne, Temps d'échantillonnage 15Tad */
	//			#define PARAM3  ADC_CONV_CLK_PB | ADC_CONV_CLK_30Tcy 		// ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_15
	//
	//			/* Configuration port - Broches AN2 et AN4 en mode analogique (capteur de température et potentiomètre) */
	//			#define PARAM4 	ENABLE_AN10_ANA | ENABLE_AN11_ANA | ENABLE_AN6_ANA
	//
	//			/* Configuration scan - Pas de scan */
	//			#define PARAM5	0


			/* Configuration - MUX A canal 0, référence négative à la masse */
			SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF);
	
			/* Configuration - Configuration de l'ADC 10bits */
			OpenADC10( PARAM1, PARAM2, PARAM3, PARAM4, PARAM5 );

			/* Contrôle - Démararage du module ADC */		
			EnableADC10();		
			while ( ! mAD1GetIntFlag() ); // Attend la fin de la première conversion (avec éciture dans les registres de destination)

/*** GPI/O Configuration ***/			

                        /*Broche de sens, debug*/
                        PORTClearBits(IOPORT_A,  BIT_4 | BIT_5 | BIT_7 );
 			PORTSetPinsDigitalOut(IOPORT_A,  BIT_4 | BIT_5 | BIT_7);
#if PROD_CARD
                        PORTClearBits(IOPORT_E, BIT_3 | BIT_2 | BIT_1 | BIT_0);
 			PORTSetPinsDigitalOut(IOPORT_E, BIT_3 | BIT_2 | BIT_1 | BIT_0);
#endif
#if DEV_CARD
                        /* Configuration - broches RA0, RA4, RA5, RA7 en sortie TOR */
			PORTClearBits(IOPORT_A,  BIT_0);
 			PORTSetPinsDigitalOut(IOPORT_A,  BIT_0);
#endif

		
/*** TIMER Configuration ***/	

			/* Configuration - Timer 3 pour la partie acquisition, commande, supervision de l'application */
			OpenTimer3( T3_ON | T3_PS_1_1 | T3_SOURCE_INT, TIMER_TICK);

			/* Configuration - démasquage des IT pour le Timer 3 */
			ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_3);

/*** PWM Configuration ***/	

			/* Configuration - PWM 2 pour la partie direction (servomoteur) */
			/* Utilise la broche RD3										*/
			OpenOC2( OC_ON | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0); 

			/* Configuration - PWM 4 pour la partie propulsion 	*/
			/* Utilise la broche RD1							*/
			OpenOC4( OC_ON | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0); 

/*** INTERRUPT Configuration ***/
	
			/* Configuration - Les IT sont déjà configurées et démasquées dans la fonction NetworkInit()	*/
			/* Niveaux de priorité dans l'application :														*/
			/* FreeRTOS Tick Kernel 	-> 1  (priorité Max gérée par FreeRTOS -> 4)						*/
			/* TCP-IP Tick Stack 		-> 2																*/
			/* Timer 3 Application 		-> 3																*/
			/* UART Debug Link	 		-> 1																*/

			//INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
}


/********************************************************************
 * Function:        void SoftwareInit(void)
 *
 * Overview:        Cette fonction initialise les variables globales de notre application        
 *
 * Auteur               Date         Commentaire
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Théou Jean-Baptiste  7 avril 2011 Première version	
 * Descoubes hugo  	16 mai  2011 vs 1.1              
 *******************************************************************/
void SoftwareInit(void){
INFO_SAVE  info;

	/* Récupération et initialisation des butées pour la direction */
	ReadAuxVar(0, (BYTE*) &info, sizeof(info));  
	ZERO_BUTE = info.zero;
	HAUT_BUTE = info.haut;
	BAS_BUTE = info.bas;
        increment_direction = info.incdir;
        increment_vitesse = info.incvit;
	/* Initialisation */
	Vitesse = 0;  
	init_ok = 0;
        xSemaphoreTake(xSemaphoreCMUcamTransmissionEnable,portMAX_DELAY);
}
