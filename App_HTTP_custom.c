/*********************************************************************
 *
 *  Application to Demo HTTP2 Server
 *  Support for HTTP2 module in Microchip TCP/IP Stack
 *	 -Implements the application 
 *	 -Reference: RFC 1002
 *********************************************************************
 * FileName:        CustomHTTPApp.c
 * Dependencies:    TCP/IP stack
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.30 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2010 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Elliott Wood     	6/18/07	    Original
 * Brad Rex             04 Apr 2010 Updated for MRF24WB0M
 ********************************************************************/




/*********************************************************************	
 * Réalisation du server HTTP pour le projet robot - ENSICAEN
 * 
 * Auteur               Date         Commentaire
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Théou Jean-Baptiste  7 avril 2011 Première version
 * 
**********************************************************************/



#define __CUSTOMHTTPAPP_C

#include "TCPIPConfig.h"
#include "main.h"
#if defined(STACK_USE_HTTP2_SERVER)
#include "TCPIP Stack/TCPIP.h"
#endif
/****************************************************************************
  Section:
	Function Prototypes and Memory Globalizers
  ***************************************************************************/


// Sticky status message variable.
// This is used to indicated whether or not the previous POST operation was 
// successful.  The application uses these to store status messages when a 
// POST operation redirects.  This lets the application provide status messages
// after a redirect, when connection instance data has already been lost.
static BOOL lastSuccess = FALSE;

// Stick status message variable.  See lastSuccess for details.
static BOOL lastFailure = FALSE;

char etat_save_info = 0;
/****************************************************************************
  Section:
	Authorization Handlers
  ***************************************************************************/

/****************************************************************************
  Section:
	GET Form Handlers
  ***************************************************************************/
  
/*****************************************************************************
  Function:
	HTTP_IO_RESULT HTTPExecuteGet(void)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
HTTP_IO_RESULT HTTPExecuteGet(void)
{
	BYTE *ptr,*ptr2,*ptr3;
	BYTE filename[20];

	
	INFO_SAVE  info;
	// Load the file name
	// Make sure BYTE filename[] above is large enough for your longest name
	MPFSGetFilename(curHTTP.file, filename, 20);
	
	
	if(!memcmppgm2ram(filename, "initialisation.html", 19))
	{
		// Determine which "BUTEE" was choose
		ptr = HTTPGetArg(curHTTP.data, (BYTE *)"save_value");
                ptr2 = HTTPGetArg(curHTTP.data, (BYTE *)"incdir");
                ptr3 = HTTPGetArg(curHTTP.data, (BYTE *)"incvit");
                if (ptr)
                {
                    switch(*ptr) {
			case '2':
				ZERO_BUTE = resultat;
				ConsDir   = ZERO_BUTE; // On initialise la consigne au "centre"
				init_ok = 1;
				break;
			case '1':
				HAUT_BUTE = resultat;
				break;
			case '0':
				BAS_BUTE = resultat;
				break;
                    }
                }
                else if(ptr2)
                {
                    switch(*ptr2){
                        case '9' :
                                increment_direction = 9;
                                break;
                        case '8' :
                                increment_direction = 8;
                                break;
                        case '7' :
                                increment_direction = 7;
                                break;
                        case '6' :
                                increment_direction = 6;
                                break;
                        case '5' :
                                increment_direction = 5;
                                break;
                        case '4' :
                                increment_direction = 4;
                                break;
                        case '3' :
                                increment_direction = 3;
                                break;
                        case '2' :
                                increment_direction = 2;
                                break;
                        case '1' :
                                increment_direction = 1;
                                break;
                        case '0' :
                                increment_direction = 0;
                                break;
                    }
                    
                }
                else if(ptr3)
                {
                    switch(*ptr3){
                        case '9' :
                                increment_vitesse = 9;
                                break;
                        case '8' :
                                increment_vitesse = 8;
                                break;
                        case '7' :
                                increment_vitesse = 7;
                                break;
                        case '6' :
                                increment_vitesse = 6;
                                break;
                        case '5' :
                                increment_vitesse = 5;
                                break;
                        case '4' :
                                increment_vitesse = 4;
                                break;
                        case '3' :
                                increment_vitesse = 3;
                                break;
                        case '2' :
                                increment_vitesse = 2;
                                break;
                        case '1' :
                                increment_vitesse = 1;
                                break;
                        case '0' :
                                increment_vitesse = 0;
                                break;
                    }
                }
		// Toggle the specified LED
		
	}
	else if(!memcmppgm2ram(filename, "eeprom.htm", 10))
	{
		// Determine which LED to toggle
		ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"objet");
		
		// Toggle the specified LED
		switch(*ptr) {
			case '1':
				info.zero = ZERO_BUTE;
				info.haut = HAUT_BUTE;
				info.bas = BAS_BUTE;
                                info.incvit = increment_vitesse;
                                info.incdir = increment_direction;
				SaveAuxVar(0, (BYTE*)&info, sizeof(info));  
				etat_save_info = 1;
				break;
			case '2':
				ReadAuxVar(0, (BYTE*)&info, sizeof(info));  
				ZERO_BUTE = info.zero;
                                HAUT_BUTE = info.haut;
                                BAS_BUTE = info.bas;
                                increment_direction = info.incdir;
                                increment_vitesse = info.incvit;
				etat_save_info = 2;
				break;
		}
	}
	else
	{
	}		
	
	return HTTP_IO_DONE;
}


/****************************************************************************
  Section:
	POST Form Handlers
  ***************************************************************************/
#if defined(HTTP_USE_POST)
/*****************************************************************************
  Function:
	HTTP_IO_RESULT HTTPExecutePost(void)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
HTTP_IO_RESULT HTTPExecutePost(void)
{
	// Resolve which function to use and pass along
	BYTE filename[20];
	
	// Load the file name
	// Make sure BYTE filename[] above is large enough for your longest name
	MPFSGetFilename(curHTTP.file, filename, sizeof(filename));

	return HTTP_IO_DONE;
}



/****************************************************************************
  Section:
	Dynamic Variable Callback Functions
  ***************************************************************************/

/*****************************************************************************
  Function:
	void HTTPPrint_varname(void)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/


void HTTPPrint_zero_bute(void)
{
	char buffer[5];
	sprintf(buffer,"%d",ZERO_BUTE);
	TCPPutROMString(sktHTTP,(ROM BYTE*)buffer);
}

void HTTPPrint_haut_bute(void)
{
	char buffer[5];
	sprintf(buffer,"%d",HAUT_BUTE);
	TCPPutROMString(sktHTTP,(ROM BYTE*)buffer);
}

void HTTPPrint_bas_bute(void)
{
	char buffer[5];
	sprintf(buffer,"%d",BAS_BUTE);
	TCPPutROMString(sktHTTP,(ROM BYTE*)buffer);
}

void HTTPPrint_pot_value(void)
{
	char buffer[5];
	sprintf(buffer,"%d",resultat);
	TCPPutROMString(sktHTTP,(ROM BYTE*)buffer);
}

void HTTPPrint_etat_save(void)
{
	char buffer[20];
	if(etat_save_info == 0)
	{
		sprintf(buffer,"A faire");
		TCPPutROMString(sktHTTP,(ROM BYTE*)buffer);	
	}
	else if(etat_save_info == 1)
	{
		sprintf(buffer,"Save OK");
		TCPPutROMString(sktHTTP,(ROM BYTE*)buffer);	
		etat_save_info = 0;
	}
	else if(etat_save_info == 2)
	{
		sprintf(buffer,"Read OK");
		TCPPutROMString(sktHTTP,(ROM BYTE*)buffer);	
		etat_save_info = 0;
	}
}

void HTTPPrint_incdir(void)
{
	char buffer[5];
	sprintf(buffer,"%d",increment_direction);
	TCPPutROMString(sktHTTP,(ROM BYTE*)buffer);
}

void HTTPPrint_incvit(void)
{
	char buffer[5];
	sprintf(buffer,"%d",increment_vitesse);
	TCPPutROMString(sktHTTP,(ROM BYTE*)buffer);
}

#endif