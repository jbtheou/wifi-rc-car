
/*****************************************************************************
 * FileName:        mTouchCap_Timers.h
 * Dependencies:
 * Processor:       PIC18, PIC24
 * Compiler:       	C18, C30
 * Linker:          MPLINK,MPLAB LINK30
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * Copyright © 2009 Microchip Technology Inc.  
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
 * Author               			Date        		Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * BDB          					26-Jun-2008 		First release
 * Naveen. M						14 Apr 2009			Version 0.1 Initial Draft
 * Nithin Kumar. M			     	14 May 2009			Version 0.2 Updates
 * Sasha. M	/ Naveen. M				4 June 2009  		Version 0.3 Updates
 * Sasha. M	/ Naveen. M				11 Nov 2009  		Version 1.0 Release
 * Sasha. M	/ Nithin. 				10 April 2010  		Version 1.20 Release
  * Nithin M						11 Aug 2010	Implemetation of Low Power Demo 
 *
 *****************************************************************************/
#ifndef _MTOUCH_TIMERS_H
#define _MTOUCH_TIMERS_H
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Includes	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
//#include	"mTouchCap_Config.h"
#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "HardwareProfile.h"
#include "mTouchCap_CtmuAPI.h"

#ifdef __PIC24F__
		#include "mTouchCap_PIC24_CTMU_Physical.h"
#else
		#include "mTouchCap_PIC18_CTMU_Physical.h"
#endif
#ifdef GUI_USB_INTERFACE
	#ifdef __PIC24F__			//USB GUI
		#include	"mTouchCap_PIC24F_GUI_commn.h"
	#else
		#include	"mTouchCap_PIC18F_GUI_commn.h"
	
	#endif
#endif //end of #ifdef GUI_USB_INTERFACE
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Externs  	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/** External Variables **/
extern CHAR 	dataReadyCTMU; //nsc
#ifdef LOW_POWER_DEMO_ENABLE
	extern WORD			Timeout_Counter;	//counter for a 10sec timeout
	extern BYTE Clock_Switch_Enable_Flag;	//FRC clock mode enable
#endif


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Function Prototypes  ~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#ifdef GUI_USB_INTERFACE
void T1Init(void);
void mTouchCapPhy_Timer1Set(WORD time);
#endif
void timer1_wait(WORD time);
void mTouchCapPhy_TickInit( void);
void InterruptHandlerHigh (void);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Enums      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Constants / Macros ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// Sample clock speed for PIC18
#if defined (__18CXX)
    #define GetPeripheralClock()    GetSystemClock()                // Peripheral clock freq.
    #define GetInstructionClock()   (GetSystemClock() / 4)       // Instruction clock freq. Four osc cycle are required for a instruction execution in PIC18
// Sample clock speed for a 16-bit processor
#elif defined (__C30__)
       #define GetPeripheralClock()    GetSystemClock()		// Peripheral clock freq.
    #define GetInstructionClock()   (GetSystemClock() / 2)		// Instruction clock freq. Two osc cycle are required for a instruction execution in PIC24
#endif

/* Derive the TIMER PR register value based on Instruction clock, Prescale value, and Timer interrupt time expected */
#if defined (__18CXX)
	#define TIMER_PERIOD   			((GetInstructionClock()) / ((DWORD)(TIMER_POSTSCALER_VALUE)*(TIMER_PRESCALER_VALUE)*(TIMER_INTERRUPT_TIME)))
#elif defined (__C30__)	
	#define TIMER_PERIOD   			((GetInstructionClock()) / ((DWORD)(TIMER_PRESCALER_VALUE)*(TIMER_INTERRUPT_TIME)))
#endif


#define	TIMER_PERIOD_WITH_FRC	125	//PR4 value when the FRC clock is selected 


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Delay Generation: Macros */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
// Description: A delay prescaler
#define DELAY_PRESCALER   (BYTE)      8

// Description: An approximation of the number of cycles per delay loop of overhead
#define DELAY_OVERHEAD    (BYTE)      5

// Description: An approximate calculation of how many times to loop to delay 1 ms in the Delayms function
#define MILLISECDELAY   (WORD)      ((GetInstructionClock()/DELAY_PRESCALER/(WORD)1000) - DELAY_OVERHEAD)


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Timer4 is used for tick generation in PIC24. */
/* Timer2 is used for tick generation in PIC18. */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#ifdef __PIC24F__

	#define STOP_TIMER_IN_IDLE_MODE     0x2000
	#define TIMER_SOURCE_INTERNAL       	0x0000
	#define TIMER_ON                    			0x8000
	#define GATED_TIME_DISABLED         	0x0000
	#define TIMER_16BIT_MODE            	0x0000
	#define TIMER_PRESCALER_1           	0x0000
	#define TIMER_PRESCALER_8           	0x0010
	#define TIMER_PRESCALER_64          	0x0020
	#define TIMER_PRESCALER_256         	0x0030
	#define TIMER_INTERRUPT_PRIORITY    0x1000
	
	#define TIMER4_PRESCALER			TIMER_PRESCALER_64		  // User needs notto modify these two variables for different prescalar	
	#define TIMER_PRESCALER_VALUE		64                         // This value is used to calculate TIMER_PERIOD 
	#define TIMER3_PERIOD				500

#else //(__18CXX)

	#define TIMER_ON                    			0x04					 //Timer2 is on
	#define TIMER_PRESCALER_4           	0x01					 //Prescaler is 4
	#define TIMER_POSTSCALER            	0x78					 //1:16 Postscale

	#define TIMER_PRESCALER_VALUE		4
	#define TIMER_POSTSCALER_VALUE	16

#endif




/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Timer1 can be used for mTouch GUI */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#ifdef __PIC24F__  //PIC24F related definitions
	//--- CONFIGURATION: CLK:FOSC/2/256
	#define  TIMER1_T1CON_ON   0x8030
	#define  TIMER1_T1CON_OFF  0x0030
	
	#define  TIMER1_USEC       (128.0)
	#define  TIMER1_MSEC       (TIMER1_USEC * 1000)
	
	#define  TIMER1_IF         IFS0bits.T1IF
#else //(__18CXX) //PIC18F related definitions
	//--- CONFIGURATION:
	#define  TIMER1_T1CON_ON   0x31  //TMR1ON =1;TMR1CS = FOsc/4;
	#define  TIMER1_T1CON_OFF  0x30  //TMRON =0; --> off
	#define  TIMER1_ON		   0x01	 //TMR0N =1
	#define  TIMER1_CLK		   0x00	 //FOsc/4
  	#define  TIMER1_OFF		   0x00	 //TIMER1 is disabled
	
	#define  TIMER1_USEC       (128.0)
	#define  TIMER1_MSEC       (TIMER1_USEC * 1000)
	
	#define  TIMER1_IF         PIR1bits.TMR1IF
#endif // __TIMER1_H


/************************************************************************
************************************************************************
						MACROs
************************************************************************
**************************************************************************/ 
#ifdef __PIC24F__


/************************************************************************
Macro       : Set_Timer4_IF_Bit_State(State) 
Overview    : setting or clearing T4 Interrupt Flag Bit 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
 
#define Set_ScanTimer_IF_Bit_State(State)   			(IFS1bits.T4IF = State)


/************************************************************************
Macro       : Set_T4_IE_Bit_State(State) 
Overview    : setting or clearing T4 Interrupt Enable Bit 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
 
#define Set_ScanTimer_IE_Bit_State(State)   			(IEC1bits.T4IE = State)


/************************************************************************
Macro       : Set_T4_ON_Bit_State(State) 
Overview    : setting or clearing T4 ON bit
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
 
#define Set_ScanTimer_ON_Bit_State(State)   			(T4CONbits.TON = State)

/************************************************************************
Macro       : Wait_Till_Timer_Flag_SET
Overview    : wait till T1 Status bit is set
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
#define Wait_Till_Timer_Flag_SET 				(IFS0bits.T1IF == 0)

/************************************************************************
Macro       : Wait_Till_OC_Flag_SET
Overview    : Wait till OC1 Status bit is set
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
#define Wait_Till_OC_Flag_SET 					(IFS0bits.OC1IF == 0)


#else
/************************************************************************
Macro       : Set_Timer2_IF_Bit_State(State) 
Overview    : setting or clearing T4 Interrupt Flag Bit 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
 
#define Set_ScanTimer_IF_Bit_State(State)   			(PIR1bits.TMR2IF = State)

/************************************************************************
Macro       : Set_T2_IE_Bit_State(State) 
Overview    : setting or clearing T4 Interrupt Enable Bit 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
 
#define Set_ScanTimer_IE_Bit_State(State)   			(PIE1bits.TMR2IE = State)

/************************************************************************
Macro       : Set_T2_ON_Bit_State(State) 
Overview    : setting or clearing T4 ON bit
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
 
#define Set_ScanTimer_ON_Bit_State(State)   			(T2CONbits.TMR2ON = State)

/************************************************************************
Macro       : Wait_Till_Timer_Flag_SET
Overview    : wait till T1 Status bit is set
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
#define Wait_Till_Timer_Flag_SET 				(INTCON3bits.INT1IF == 0)

/************************************************************************
Macro       : Wait_Till_OC_Flag_SET
Overview    : Wait till OC1 Status bit is set
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
#define Wait_Till_OC_Flag_SET 					(IFS0bits.OC1IF == 0)

 
///************************************************************************
//Macro       : Set_Timer4_IF_Bit_State(State) 
//Overview    : setting or clearing T4 Interrupt Flag Bit 
//Parameters  : ENABLE '1' or DISABLE '0' 
//Remarks     : None.
//**************************************************************************/ 
//#define Set_ScanTimer_IF_Bit_State(State)   			(PIR3bits.TMR4IF = State)
//
///************************************************************************
//Macro       : Set_T4_IE_Bit_State(State) 
//Overview    : setting or clearing T4 Interrupt Enable Bit 
//Parameters  : ENABLE '1' or DISABLE '0' 
//Remarks     : None.
//**************************************************************************/ 
//#define Set_ScanTimer_IE_Bit_State(State)   			(PIE3bits.TMR4IE = State)
//
///************************************************************************
//Macro       : Set_T4_ON_Bit_State(State) 
//Overview    : setting or clearing T4 ON bit
//Parameters  : ENABLE '1' or DISABLE '0' 
//Remarks     : None.
//**************************************************************************/ 
//#define Set_ScanTimer_ON_Bit_State(State)   			(T4CONbits.TMR4ON = State)
//
#endif //PIC18




#endif	// _MTOUCH_TIMERS_H


