/*********************************************************************
 *  Header Main Application Entry Point 
 *********************************************************************
 * FileName:        Main.h
 *
 * Overview: Fichier d'en-t�te principal pour l'application 
 ********************************************************************/

#ifndef _MAIN_H
#define _MAIN_H
	
/** INCLUDES *******************************************************/

	/* C32 includes */
	#include <p32xxxx.h>		// Fichier d'en-t�te g�n�rique pour la famille PIC32 (appel "p32mx795f512l.h" celui de notre MCU)
	#include <plib.h>			// Fichier d'en-t�te pour le gestion des p�riph�riques standards des PIC32MX
		
	/* RTOS includes */
	#include "FreeRTOS.h"
	#include "task.h"
	#include "queue.h"								
	#include "semphr.h"

	/* Microchip TCP-IP includes */	
	#include "TCPIP Stack/TCPIP.h"
	
	#if defined(STACK_USE_ZEROCONF_LINK_LOCAL)
		#include "TCPIP Stack/ZeroconfLinkLocal.h"
	#endif

	#if defined(STACK_USE_ZEROCONF_MDNS_SD)
		#include "TCPIP Stack/ZeroconfMulticastDNS.h"
	#endif

	/* Microchip Wi-Fi includes */		
	#if defined ( EZ_CONFIG_SCAN )
		#include "TCPIP Stack/WFEasyConfig.h"
	#endif

	#if defined( WF_CONSOLE )
		#include "TCPIP Stack/WFConsole.h"
		#include "IperfApp.h"
	#endif 	

	
/** MACROS *********************************************************/

	/* App et Harware */
	#define SYS_FREQ                   80000000		// Vitesse de travail du bus matrix (et du CPU)
	#define DESIRED_BAUDRATE           115200			// Vitesse de travail pour la communication s�rie asynchronne (RS232)
	#define PB_DIV                     2				// Le diviseur pour le bus p�riph�rique (ATTENTION : Ne pas modifier qu'ici)
	#define PRESCALE                   1				// La valeur du Prescale
	#define TOGGLES_PER_SEC            2000			// Le choix de la fr�quence d'�chantillonage et de d�coupage
	#define TIMER_TICK                 (SYS_FREQ/PB_DIV/PRESCALE/TOGGLES_PER_SEC) // R�glage pour le tick de timer (Ne pas modifier)
	#define MAX_CURRENT                14.0			// La valeur max admissible pour l'asservissement de courant
        #define RX_MAX                     11000
        #define UDP_LIMIT_SIZE             1472
	#define DESIRED_BAUDRATE_CMUCAM    (115200)
        #define MAX_COMMAND_SIZE           20
        #define FORWARD                    1
        #define BACKWARD                   2
	/* TCP-IP */
	#define NETWORK_DATA_REFRESH_PERIOD	3	// p�riode de rafrachissement des data r�seau en nb de tick du noyau
	#define NETWORK_STACK_REFRESH_PERIOD	10	// p�riode de rafrachissement de la stack IP en nb de tick du noyau
        #define SERVER_PORT_CMUCAM              9760
        #define SERVER_PORT_CMD                 9761
        #define SERVER_PORT_CMD_ACC             9762
	/* Command/control */
	#define PROPULSION_CONTROL  	1
	#define PROPULSION_PWM  		2
	#define DIRECTION_CONTROL  		3
	#define DIRECTION_PWM  			4
	#define POWER_SUPERVIOR   		5
	#define Ti 						30.0 	//Constante d'int�gration; 
	#define Kp 						1.0 	// Gain du r�gulateur
	#define OutputMin 				0 		// min saturation de l'actionneur
	#define OutputMax 				97		// max saturation de l'actionneur

	/* Debug */
	#define BROCHE_DEBUG         IOPORT_A, BIT_7  // La broche pour les sorties de Debug
	#define BROCHE_DIR_DIRECTION IOPORT_A, BIT_5  // La broche pour la "direction" de la direction
	#define BROCHE_DIR_VITESSE   IOPORT_A, BIT_4  // La broche pour la "direction" de la vitesse
	#define ISR_DELAY            1                // Temps du toggle dans l'ISR d'acquisition
	#define DEBUG_IS_ON          1                  // Ajout de code pour le debug (d�pendance : ISR Timer3 )
	#define COMMANDE_DELAY       0				  // Temps de la tache d'asservissement
	#define UART_DELAY           0				  // Temps de l'envoie via UART
        #define PROD_CARD            0                              // Configuration des LEDS pour la carte de prod
        #define DEV_CARD             1
	/* Wi-Fi */
	#define WF_MODULE_NUMBER     WF_MODULE_MAIN_DEMO		// Used for Wi-Fi assertions

        /* CMUcam */
        #define CMUcam_IS_USE        1                 // Pour activer la communication vers la CMUcam

	
/** VARIABLES *********************************************/

	/* App. User prototypes */	
	short ConsDir; 				 // Consigne (position potentiom�tre) pour la direction
	short resultat_courant; 	 // Resultat du courant
	short Vitesse; 				 // Valeur de la PWM de puissance
	short resultat; 		     // Resultat du potentiom�tre
	char  Marche_Avant_Arriere;  // Marche avant ou arri�re 
	char  Change_Vitesse_up;
	char  Change_Vitesse_down;
	char  Change_Direction_up;
	char  Change_Direction_down;
	short ZERO_BUTE; 			 // Le zero de la direction
	short HAUT_BUTE;			 // Le haut de la bute
	short BAS_BUTE;				 // Le bas de la bute
	char  init_ok;				 // Le bas de la bute
	char  increment_direction;
	char  increment_vitesse;



	WORD  MemoryIndexVar[4]; 	// L'index pour les variables	
					 
	/* RTOS prototypes */
	xQueueHandle xQueueAcquiData;
	xQueueHandle xQueueDebugPrint;
	xQueueHandle xQueueDebugPrintIP;
        xQueueHandle xQueueCMUcam;
        
        xSemaphoreHandle xSemaphoreVitesse;
	xSemaphoreHandle xSemaphoreConsDir;
	xSemaphoreHandle xSemaphoreCMUcamTransmissionEnable;

        /* UART CMUcam comm variables*/
        volatile BYTE rxbuffer[RX_MAX];
        int count;
	
        /* TCP-IP variable */
	APP_CONFIG AppConfig;										// Declare AppConfig structure and some other supporting stack variables
	volatile static unsigned short wOriginalAppConfigChecksum;	// Checksum of the ROM defaults for AppConfig
	BYTE AN0String[8];
	
/** STRUCTURES and ENUM *****************************************************/

	/* Grandeurs � afficher pour le debug */
	/* Use : debug task and command task */
	typedef struct struct_DebugPrint {
		short consigneDir;
		short mesureDir;
		short commandeDir;

		float consigneMove;
		float mesureMove;
		short commandeMove;

		short mesurePower;
		short varTest1;		// Variables pour le Debug
		short varTest2;		// Variables pour le Debug
	} struct_DebugPrint;

	/* Mesures � transmettre depuis l'ISR */	
	/* Use : ISR Timer3 and command task */
	typedef struct struct_mesures {
		short sDirMeasure;
		short sCurrentMeasure;
		short sBattMeasure;
	} struct_mesures;

	/* Sauvegarde des bornes pour l'asservissement de position*/
	 typedef struct info_bute { 
	    short zero;
	    short haut;
            short bas;
            char incvit;
            char incdir;
	 } INFO_SAVE ;

        /* Sauvegarde des bornes pour l'asservissement de position*/
	 typedef struct cmd_car {
            char for_back;
            char speed_up;
            char speed_down;
            char dir_up;
            char dir_down;
	 } CMD_CAR ;

         /* Sauvegarde des bornes pour l'asservissement de position*/
	 typedef struct cmd_car_acc {
            char active;
            char fb;
            char speed;
            char signe;
            char dir;
	 } CMD_CAR_ACC ;
	        
/** FUNCTIONS and TASKS *********************************************/

	/* App. User prototypes */
	void HardwareInit(void);
	void SoftwareInit(void);
	void UARTputs(char *buffer);
	void UARTputsIP(void);
	short directionCommand(short consigne, short mesure);
	short propulsionCommand (short ConsignePIF,float MesurePIF);
        void putrsUART2(unsigned char * String);

	/* RTOS prototypes */
	void RTOSInit(void);
	void NetworkInit(void);

        /* Network prototypes*/
        void UDPServer_CMUcam(void);
        void UDPServer_Cmd(void);
        void UDPServer_Cmd_Acc(void);
        void Large_UDP_Packet(int value,UDP_SOCKET MySocket);
        void Update_CMD(CMD_CAR car_info);
        void Update_CMD_Acc(CMD_CAR_ACC car_info);
        
	/* Task prototypes */
	void TaskDebugUart(void *pvParameters);
	void TaskControl(void *pvParameters);
	void TaskNetwork( void *pvParameters );
	//void TaskRefresh(void *pvParameters);
	void TaskCMUcam(void *pvParameters);

	/* TCP-IP prototypes */
	void InitAppConfig(void);
	void InitializeBoard(void);
	void WF_Connect(void);

	/* Modification (http://www.microchip.com/forums/tm.aspx?m=526126&mpage=&settheme=Mobile)
	Permet de stocker des variables dans l'EEPROM (En tenant compte du MPFS) */
	extern void ReadAuxVar(BYTE n, BYTE *var, BYTE size);
	extern void SaveAuxVar(BYTE n, BYTE *var, BYTE size);  
#endif
