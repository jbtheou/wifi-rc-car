/******************************************************************************

  TMRDriver.h (Header File)

Description:
    This file contains function prototypes that are used in TMRDriver.c
*******************************************************************************/

/*******************************************************************************

* FileName:        TMRDriver.h
* Dependencies:    See included files, below.
* Processor:       PIC32MX795F512H
* Compiler:        C32
* Company:         Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the “Company”) for its PIC® Microcontroller is intended and
 supplied to you, the Company’s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

Change History:
Author          Date       Comments
---------------------------------------------------------------------------------------
BDB         	26-Jun-2008 Initial release
NK			 	24-Apr-2009 Porting for 18F46J50 Eval Board
MC              22-Ian-2010 First release of TMRDriver.c, TMRDriver.h
                            Porting for PIC32MX795F512H

**************************************************************************************/
#ifndef __MTOUCHCAP_TIMER_H
#define __MTOUCHCAP_TIMER_H

// state machine used in CVD technique
typedef enum {
    T_STATE_CHARGE_HOLD_CAP = 0, 
    T_STATE_CHARGE_SENSOR_CAP,
    T_STATE_START_CONVERSION
}T_STATE_ENUM; 

/* sampling delay - in between the C HOLD + C SENSOR voltage divider */
/* tradeof between charge/decharge of CHOLD and CSENSOR */
/* if sampling delay is set to 0, sampling begins immediately */
#define     SAMPLING_DELAY          0
#define     SAMPLING_DELAY_REF         1000 //some distant time
/* precharging delay - time necessary for charging C HOLD to VDD while */
/* floating C SENSOR is grounded */
#define     PRECHARGING_DELAY       250

//==========================================================
//--- PROTOTYPES
//==========================================================
void Timer4CallbackFunc(void);
void InitTimer4(void);
void SetPeriodTimer4(unsigned int time);

/************************************************************************
Macro       : Set_Timer4_IF_Bit_State(State) 
Overview    : setting or clearing T4 Interrupt Flag Bit 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
 
#define Set_ScanTimer_IF_Bit_State(State)   			(IFS0bits.T4IF = State)


/************************************************************************
Macro       : Set_T4_IE_Bit_State(State) 
Overview    : setting or clearing T4 Interrupt Enable Bit 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
 
#define Set_ScanTimer_IE_Bit_State(State)   			(IEC0bits.T4IE = State)


/************************************************************************
Macro       : Set_T4_ON_Bit_State(State) 
Overview    : setting or clearing T4 ON bit
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 

#define Set_ScanTimer_ON_Bit_State(State)   			(T4CONbits.TON = State) 

#endif //end of __MTOUCHCAP_TIMER_H
