
/*******************************************************************************

* FileName:        mTouchCap_Adc.h
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
MC              22-Ian-2010 First release of ADCDriver.c, ADCDriver.h
                            Porting for PIC32MX795F512H

**************************************************************************************/

#ifndef MTOUCHCAP_ADC_H
#define MTOUCHCAP_ADC_H
/************************************************************************
		 Redefining ADC Register
**************************************************************************/
#define ADC_CHANNEL_SELECT 		AD1CHS

/************************************************************************
Macro       : Set_Adc_Enable_State
Overview    : This function enables or disable the ADC module depending upon the value.
Parameters  : None
Remarks     : None.
**************************************************************************/
#define Set_Adc_Enable_State(Value)          (AD1CON1bits.ADON = Value)

#define AD1_CHANNEL_SELECT(Value) 		AD1CHSbits.CH0SA = Value; 

/* initialization of ADC driver */
void InitADC1(void *ADC1CallBackISR);
void ADC1CallbackFunc(void);
#endif
