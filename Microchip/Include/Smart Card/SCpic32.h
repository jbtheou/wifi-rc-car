/********************************************************************
 FileName:		SCpic32.h
 Dependencies:	See INCLUDES section
 Processor:		PIC32 Microcontrollers
 Hardware:		This demo is natively intended to be used on Exp 16 board.
 				This demo can be modified for use on other hardware platforms.
 Complier:  	Microchip C32 (for PIC32)
 Company:		Microchip Technology, Inc.

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

********************************************************************
 File Description:

 Change History:
  Rev   Description
  ----  -----------------------------------------
  1.02   Initial release
********************************************************************/

#ifndef __SC_DRV32_LIB__
#define __SC_DRV32_LIB__

#include "GenericTypeDefs.h"
#include "p32xxxx.h"

extern unsigned long baudRate;	// Baud Rate of Smart Card Transmission/Reception Data
extern unsigned long scReferenceClock; // Smart Card Reference Clock
extern unsigned int factorF;
extern BYTE factorDNumerator;
extern BYTE factorDdenominator;

extern void SC_Delay(unsigned int instructionCount);
extern void SCdrv_InitUART(void);
extern void SCdrv_CloseUART(void);
extern void SCdrv_SetBRG( BYTE speedCode );
extern BOOL SCdrv_GetRxData( BYTE* pDat, unsigned long nTrys );
extern void SCdrv_SendTxData( BYTE data );

#endif



