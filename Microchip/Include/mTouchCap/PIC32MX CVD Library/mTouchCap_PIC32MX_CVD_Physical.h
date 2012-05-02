
/*****************************************************************************
 * FileName:        mTouchCap_PIC32MX_CVD_Physical.h
 * Dependencies:
 * Processor:       PIC32MX
 * Compiler:       	C32
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * Copyright © 2010 Microchip Technology Inc.  
 * Microchip licenses this software to you solely for use with Microchip products, according to the terms of the  
 * accompanying click-wrap software license.  Microchip and its licensors retain all right, title and interest in 
 * and to the software.  All rights reserved. This software and any accompanying information is for suggestion only.  
 * It shall not be deemed to modify Microchip’s standard warranty for its products.  It is your responsibility to ensure 
 * that this software meets your requirements.

 * SOFTWARE IS PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, 
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS LICENSORS BE LIABLE 
 * FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO INCIDENTAL, 
 * SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, 
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, OR ANY CLAIMS BY THIRD PARTIES 
 * (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.  
 * The aggregate and cumulative liability of Microchip and its licensors for damages related to the use of the software 
 * will in no event exceed $1000 or the amount you paid Microchip for the software, whichever is greater.

 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS AND 
 * THE TERMS OF THE ACCOMPANYING CLICK-WRAP SOFTWARE LICENSE.
 * 
 *
 * Author               		Date        		Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Naveen. M				    14 Apr 2009			Version 1.0 Initial Draft
 * Sasha. M	/ Naveen. M			4 May 2009  		Version 1.0 Initial Draft
 * Sasha. M	/ Naveen. M			11 Nov 2009  		Version 1.0 Release
 * Sasha. M	/ Nithin. 			10 April 2010  		Version 1.20 Release
 * MC                           10 August 2010      Version 1.21 Release 
 *****************************************************************************/
 
#ifndef _MTOUCH_PIC32MX_CVD_PHYSICAL_H
#define _MTOUCH_PIC32MX_CVD_PHYSICAL_H

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Includes	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include 		"Config.h"
#include 		"HardwareProfile.h"		 
#include 		"mTouchCap_Timers.h"
#include 		"mTouchCap_Adc.h"
#include 		"GenericTypeDefs.h"

#ifdef __PIC32MX__

void mTouchCapPhy_AdcSetup(void);
void mTouchCapPhy_TickInit(void);
void mTouchCapPhy_InitCVD(void);
WORD mTouchCapPhy_ReadCVD(WORD ChannelNumber);
void mTouchCapPhy_ChannelSetup(WORD ChannelNum);
void mTouchCapPhy_StablizeChannelData(void);
void mTouchCapPhy_AverageData(WORD Index);

void mTouchCapApp_PortSetup(void);
void DynamicTripValueCalculation(WORD Index);

//////////////////////////////////////////////////////////////////////
// CHANNEL SELECTION DEFINITIONS
//////////////////////////////////////////////////////////////////////

#ifdef	USE_DIRECT_KEYS
	#define	DIRECTKEYS	    8		// 8 direct keys
#endif

#ifdef	USE_SLIDER_2CHNL
	#define SLDR2CHL	    4		// 4 slider keys enabled - only 2 are used though
#endif

#ifdef	USE_SLIDER_4CHNL
	#define SLDR4CHL	    4		// 4 slider keys enabled
#endif

#ifdef	USE_MATRIX_KEYS
	#define NUMROWS         4		// number of rows 4
	#define NUMCOLS         3		// number of colons 4
#endif	

#define DIGITAL                 1
#define ANALOG	                0

enum
{
	FILTER_METHOD_SLOWAVERAGE=0,
	FILTER_METHOD_GATEDAVERAGE,
	FILTER_METHOD_FASTAVERAGE
};

enum
{
	NOT_AN_ACTIVE_CHANNEL = -1,
	KEY_NOT_PRESSED,
	KEY_PRESSED	
};

enum
{
	DECODE_METHOD_MOST_PRESSED,		/* Future exapansion pending */
	DECODE_METHOD_MULTIPLE_PRESS,		/* Future exapansion pending */
	DECODE_METHOD_PRESS_AND_RELEASE,	/* Future exapansion pending */
	DECODE_METHOD_PRESS_ASSERT			/* Implemented */
//	DECODE_METHOD_KEY_PRESS_FREEZ		/* Future exapansion pending */
};

enum 
{
	CHANNEL_AN0 ,
	CHANNEL_AN1 ,
	CHANNEL_AN2 ,
	CHANNEL_AN3 ,
	CHANNEL_AN4 ,
	CHANNEL_AN5 ,
	CHANNEL_AN6 ,
	CHANNEL_AN7 ,
	CHANNEL_AN8 ,
	CHANNEL_AN9 ,
	CHANNEL_AN10 ,
	CHANNEL_AN11 ,
	CHANNEL_AN12 ,
    CHANNEL_AN13 ,		
	CHANNEL_AN14 ,		
	CHANNEL_AN15 ,
    CHANNEL_AN16 ,		
	CHANNEL_AN17 ,		
	CHANNEL_AN18 ,		
	CHANNEL_AN19 ,		
	CHANNEL_AN20 ,		
	CHANNEL_AN21 ,		
	CHANNEL_AN22 ,		
	CHANNEL_AN23 		 
	
};

#define TRIS_CHANNEL_AN0  		TRISBbits.TRISB0
#define TRIS_CHANNEL_AN1  		TRISBbits.TRISB1
#define TRIS_CHANNEL_AN2  		TRISBbits.TRISB2
#define TRIS_CHANNEL_AN3  		TRISBbits.TRISB3
#define TRIS_CHANNEL_AN4  		TRISBbits.TRISB4
#define TRIS_CHANNEL_AN5  		TRISBbits.TRISB5
#define TRIS_CHANNEL_AN6  		TRISBbits.TRISB6
#define TRIS_CHANNEL_AN7  		TRISBbits.TRISB7
#define TRIS_CHANNEL_AN8  		TRISBbits.TRISB8
#define TRIS_CHANNEL_AN9  		TRISBbits.TRISB9
#define TRIS_CHANNEL_AN10  		TRISBbits.TRISB10
#define TRIS_CHANNEL_AN11  		TRISBbits.TRISB11
#define TRIS_CHANNEL_AN12  		TRISBbits.TRISB12
#define TRIS_CHANNEL_AN13  		TRISBbits.TRISB13
#define TRIS_CHANNEL_AN14  		TRISBbits.TRISB14
#define TRIS_CHANNEL_AN15  		TRISBbits.TRISB15
#define TRIS_CHANNEL_AN16  		TRISCbits.TRISC4
#define TRIS_CHANNEL_AN17  		TRISGbits.TRISG6
#define TRIS_CHANNEL_AN18 		TRISGbits.TRISG7
#define TRIS_CHANNEL_AN19  		TRISGbits.TRISG8
#define TRIS_CHANNEL_AN20  		TRISGbits.TRISG9
#define TRIS_CHANNEL_AN21  		TRISEbits.TRISE9
#define TRIS_CHANNEL_AN22  		TRISAbits.TRISA7
#define TRIS_CHANNEL_AN23  		TRISAbits.TRISA6

#endif //#ifdef __PIC32MX__

#endif	// _MTOUCH_PIC32MX_CVD_PHYSICAL_H


