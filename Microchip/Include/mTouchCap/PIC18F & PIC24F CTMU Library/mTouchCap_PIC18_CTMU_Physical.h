
/*****************************************************************************
 * FileName:        mTouchCap_PIC18_CTMU_Physical.h
 * Dependencies:
 * Processor:       PIC18
 * Compiler:       	C18
 * Linker:          MPLINK
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
 * Author               		Date        		Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Naveen. M				    14 Apr 2009			Version 0.1 Initial Draft
 * Nithin Kumar. M			    14 May 2009			Version 0.2 Updates
 * Sasha. M	/ Naveen. M	      	4 June 2009  		Version 0.3 Updates
 * Sasha. M	/ Naveen. M			11 Nov 2009  		Version 1.0 Release
 * Sasha. M	/ Nithin. 			10 April 2010  		Version 1.20 Release
 *****************************************************************************
 *
 *****************************************************************************/
#ifndef _MTOUCH_PIC18_CTMU_PHY_H
#define _MTOUCH_PIC18_CTMU_PHY_H

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Includes	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include 		"Config.h"
#include 		"HardwareProfile.h"		 
#include 		"mTouchCap_Timers.h"
#include 		"mTouchCap_Adc.h"

#include 	"GenericTypeDefs.h"
#ifdef __18CXX

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Constants	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */




/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Variables  	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Variables  	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Externs  	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
extern WORD	curRawData		[MAX_ADC_CHANNELS];	//Storage for CTMU channel values
extern WORD	tripValue   		[MAX_ADC_CHANNELS];	//Storage for the trip point for each channel	
extern WORD	hystValue   		[MAX_ADC_CHANNELS];	//Storage for the hysterisis value for each channel
extern WORD	pressedCount   	[MAX_ADC_CHANNELS];	//Storage for count of pressed value for each channel
extern WORD	unpressedCount  [MAX_ADC_CHANNELS];	//Storage for count of unpressed value for each channel
extern WORD	avg_delay 		[MAX_ADC_CHANNELS];//Storage for count for average update for each channel	
extern WORD	averageData 	[MAX_ADC_CHANNELS];	// running average of CTMU channels	
extern WORD	smallAvg		[MAX_ADC_CHANNELS];	// current button smallavg
extern WORD	actualValue		[MAX_ADC_CHANNELS];	// actual raw A/D counts for each channel
extern WORD	channel_TRIM_value	[MAX_ADC_CHANNELS];
extern WORD	channel_IRNG_value	[MAX_ADC_CHANNELS];
extern BYTE	chFilterType	[MAX_ADC_CHANNELS];	// Channel filter type
//extern BYTE	chDecodeMethod	[MAX_ADC_CHANNELS];	// decode method type
extern BYTE Press_State [MAX_ADC_CHANNELS];
extern SHORT startupCount;				// variable to 'discard' first N samples
extern SHORT loopCount;
extern WORD	immediateValue;			// current button value
extern WORD	scaledBigValue;				// current button bigval

extern  WORD ScanChannels[MAX_ADC_CHANNELS];
extern BYTE 	Channel_Pressed_Status[MAX_ADC_CHANNELS];
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Function Prototypes  ~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void mTouchCapPhy_Init(void);	 
void mTouchCapPhy_InitCTMU(void);
void mTouchCapPhy_ChannelSetup(WORD ChannelNum);
void	mTouchCapApp_PortSetup(void);
WORD mTouchCapPhy_Read_ADC(void);
void mTouchCapPhy_ReadCTMU(WORD ChannelNumber);
void	mTouchCapPhy_CTMUSetup(void);
void	mTouchCapPhy_AdcSetup(void);
void mTouchCapPhy_ChargeTimeInit(void);
void mTouchCapPhy_SetupCurrentSourceRange(WORD CurrentSourceRange);
void	mTouchCapPhy_SetTrimValue( WORD TrimValue);
void mTouchCapPhy_Discharge_Current (void);
void mTouchCapPhy_Charge_Current (void);
WORD mTouchCapPhy_Read_ADC();
void mTouchCapPhy_StablizeChannelData(void);

void CTMU_Current_trim_config(int channel_no);
void DynamicTripValueCalculation(WORD Index);
void mTouchCapPhy_AverageData(WORD Index);
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Enums      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
 


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Constants / Macros ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#define PLL_ENABLED
#define PLL_EN_BIT     OSCTUNEbits.PLLEN


//================pLIB=================================

/***********************************************************************/
/********************ANALOG CHANNELS TRISBITS DEFINITION*****************************************/
/***********************************************************************/
#define DIGITAL                 1
#define ANALOG	                0


#define TRIS_CHANNEL_AN0		TRISAbits.TRISA0
#define TRIS_CHANNEL_AN1  		TRISAbits.TRISA1
#define TRIS_CHANNEL_AN2  		TRISAbits.TRISA2
#define TRIS_CHANNEL_AN3  		TRISAbits.TRISA3
#define TRIS_CHANNEL_AN4  		TRISAbits.TRISA5
#define TRIS_CHANNEL_AN5  		TRISEbits.TRISE0
#define TRIS_CHANNEL_AN6  		TRISEbits.TRISE1
#define TRIS_CHANNEL_AN7  		TRISEbits.TRISE2
#define TRIS_CHANNEL_AN8  		TRISBbits.TRISB2
#define TRIS_CHANNEL_AN9  		TRISBbits.TRISB3
#define TRIS_CHANNEL_AN1O  		TRISBbits.TRISB1
#define TRIS_CHANNEL_AN11  		TRISCbits.TRISC2
#define TRIS_CHANNEL_AN12  		TRISBbits.TRISB0

#define ADPCF_CHANNEL_AN0(Value) 		ANCON0bits.PCFG0 = Value;
#define ADPCF_CHANNEL_AN1(Value) 		ANCON0bits.PCFG1 = Value;
#define ADPCF_CHANNEL_AN2(Value) 		ANCON0bits.PCFG2 = Value;
#define ADPCF_CHANNEL_AN3(Value) 		ANCON0bits.PCFG3 = Value;
#define ADPCF_CHANNEL_AN4(Value) 		ANCON0bits.PCFG4 = Value;
#define ADPCF_CHANNEL_AN5(Value) 		ANCON0bits.PCFG5 = Value;
#define ADPCF_CHANNEL_AN6(Value) 		ANCON0bits.PCFG6 = Value;
#define ADPCF_CHANNEL_AN7(Value) 		ANCON0bits.PCFG7 = Value;
#define ADPCF_CHANNEL_AN8(Value) 		ANCON1bits.PCFG8 = Value;
#define ADPCF_CHANNEL_AN9(Value) 		ANCON1bits.PCFG9 = Value;
#define ADPCF_CHANNEL_AN10(Value)		ANCON1bits.PCFG10 = Value;
#define ADPCF_CHANNEL_AN11(Value)		ANCON1bits.PCFG11 = Value;
#define ADPCF_CHANNEL_AN12(Value)		ANCON1bits.PCFG12 = Value;

/***********************************************************************/
/********************A   D    C*****************************************/
/***********************************************************************/
/***********************************************************************/
#define 	INIT_AD1PCFGL_VALUE		0x0000
#define 	INIT_AD1CON1_VALUE		0x0000
#define 	INIT_AD1CHS_VALUE		0x0000				//select the analog channel 0

/***********************************************************************
Macro      : EnableIntADC1
Overview   : This macro enables the ADC interrupt.
Parameters : None
Remarks    : This macro sets ADC Interrupt Enable bit of Interrupt
             Enable Control Register.
************************************************************************/
#define EnableIntADC1                (PIE1bits.ADIE = 1)

/***********************************************************************
Macro      : DisableIntADC1
Overview   : This macro disables the ADC interrupt.
Parameters : None
Remarks    : This macro clears ADC Interrupt Enable bit of Interrupt
             Enable Control register.
************************************************************************/
#define DisableIntADC1                (PIE1bits.ADIE = 0)

/***********************************************************************
Macro      : SetPriorityIntADC1(priority)
Overview   : This macro sets priority for ADC interrupt.
Parameters : priority - This input parameter is the level of interrupt priority
Remarks    : This macro sets ADC Interrupt Priority bits of Interrupt
             Priority Control register.
************************************************************************/
#define SetPriorityIntADC1(priority)   //STD: set prio  (IPC3bits.AD1IP = priority)

/*******************************************************************
Macro       : ADC1_Clear_Intr_Status_Bit
Overview    : Macro to Clear ADC Interrupt Status bit
Parameters  : None
Remarks     : None
*******************************************************************/
#define ADC1_Clear_Intr_Status_Bit ( PIR1bits.ADIF = 0)	//PIC18

/*******************************************************************
Macro       : ADC1_IF_Bit
Overview    : returns ADC1 Interrupt Flag
Parameters  : None
Remarks     : None
*******************************************************************/
#define ADC1_IF_Bit (PIR1bits.ADIF)


/************************************************************************
Macro       : BusySampADC1
Overview    : This function is identical to ConvertADC10
Parameters  : None
Remarks     : This macro clears the ADCON1<SAMP> bit and thus stops sampling
              and starts conversion.
**************************************************************************/
#define BusySampADC1              !(AD1CON1bits.SAMP)

/************************************************************************
Macro       : EnableADC1
Overview    : This function enables the ADC module
Parameters  : None
Remarks     : None.
**************************************************************************/
#define EnableADC1                (AD1CON1bits.ADON = 1)

/************************************************************************
Macro       : DisableADC1
Overview    : This function disables the ADC module
Parameters  : None
Remarks     : None.
**************************************************************************/
#define DisableADC1                (ADCON0bits.ADON = 0)

/************************************************************************
Macro       : Set_Adc_Enable_State
Overview    : This function enables or disable the ADC module depending upon the value.
Parameters  : None
Remarks     : None.
**************************************************************************/
#define Set_Adc_Enable_State(Value)          (ADCON0bits.ADON = Value) //PIC18


/************************************************************************
Macro       : Enable_ADC_Sampling
Overview    : This function starts the A/D conversion.
Parameters  : None
Remarks     : None.
**************************************************************************/
#define Enable_ADC_Sampling       (ADCON0bits.GO = 1)	//PIC18


/************************************************************************
Macro       : Disable_ADC_Sampling
Overview    : This function starts the A/D conversion.
Parameters  : None
Remarks     : None.
**************************************************************************/
#define Disable_ADC_Sampling       (ADCON0bits.GO = 0) //PIC18
 

/************************************************************************
Macro       : ADC_GO_Bit 
Overview    : This function declares the AD1CON1bits.DONE.
Parameters  : None
Remarks     : None.
**************************************************************************/
#define ADC_GO_Bit       			 (ADCON0bits.GO)
 

/************************************************************************
Macro       : ADC_Done_Bit
Overview    : This function declares the AD1CON1bits.DONE.
Parameters  : None
Remarks     : None.
**************************************************************************/
#define ADC_Done_Bit       			 (ADCON0bits.DONE)	//PIC18

/************************************************************************
Macro       : Adc_Port_Configuration1
Overview    : Configure ADC Port pin as Analog or Digital for register0
Parameters  : None
Remarks     : None.
**************************************************************************/
#define Adc_Port_Configuration1(Value)	(ANCON0 = Value)	//PIC18

/************************************************************************
Macro       : Adc_Port_Configuration1
Overview    : Configure ADC Port pin as Analog or Digital for register1
Parameters  : None
Remarks     : None.
**************************************************************************/
#define Adc_Port_Configuration2(Value)	(ANCON1 = Value)	//PIC18
/************************************************************************

		 Redefining ADC Register

**************************************************************************/
#define ADC_CHANNEL_SELECT 		ADCON0bits.CHS  
#define ADCSSL						//AD1CSSL PIC18
#define AD_CON_REG1						ADCON1
#define AD_CON_REG0						ADCON0
#define ADCBUF						    ADC1BUF0


/*Registers Defaults*/
#define ADCSSL_VAL    				 0x00
#define ADCON1_VAL    				 0x00
#define ADCON0_VAL    				 0x00
#define ADC_PRIORITY					0x00
#define ADC_PORT_CONFIG_DEFAULT_VALUE 	0x00		// Default Value of ADC Port Configuration Register.


/*AD1CON0 register definition*/
//************** Voltage Reference Configuration ****************************** 
#define ADC_REF_VDD_VREFMINUS   	0b00000010 	// ADC voltage source VREF+ = VDD and VREF- = ext.source at VREF-
#define ADC_REF_VREFPLUS_VREFMINUS  0b00000011 	// ADC voltage source VREF+ = ext.source at VREF+ and VREF- = ext.source at VREF-
#define ADC_REF_VREFPLUS_VSS		0b00000001 	// ADC voltage source VREF+ = ext.source at VREF+ and VREF- = VSS
#define	ADC_REF_VDD_VSS  		    0b00000000 	// ADC voltage source VREF+ = VDD and VREF- = VSS


//**************** channel selection ******************************************
#define ADC_CH0          0b10000111  			//Select Channel 0
#define ADC_CH1          0b10001111  			//Select Channel 1
#define ADC_CH2          0b10010111  			//Select Channel 2
#define ADC_CH3          0b10011111  			//Select Channel 3
#define ADC_CH4          0b10100111  			//Select Channel 4
#define ADC_CH5          0b10101111  			//Select Channel 5
#define ADC_CH6          0b10110111  			//Select Channel 6
#define ADC_CH7          0b10111111  			//Select Channel 7
#define ADC_CH8          0b11000111  			//Select Channel 8
#define ADC_CH9          0b11001111  			//Select Channel 9
#define ADC_CH10         0b11010111  			//Select Channel 10
#define ADC_CH11         0b11011111  			//Select Channel 11
#define ADC_CH12         0b11100111  			//Select Channel 12


/*AD1CON1 control register definition*/
//*************** A/D Conversion Clock Select *****************************
#define ADC_FOSC_2       0b00000000 			//A/D conversion clock source is Fosc/2
#define ADC_FOSC_4       0b00000100 			//A/D conversion clock source is Fosc/4
#define ADC_FOSC_8       0b00000001 			//A/D conversion clock source is Fosc/8
#define ADC_FOSC_16      0b00000101 			//A/D conversion clock source is Fosc/16
#define ADC_FOSC_32      0b00000010 			//A/D conversion clock source is Fosc/32
#define ADC_FOSC_64      0b00000110 			//A/D conversion clock source is Fosc/64
#define ADC_FOSC_RC      0b00000111			//A/D conversion clock source is Internal RC OSC


//************** A/D Acquisition Time Selection *******************************
#define ADC_0_TAD        0b00000000				//A/D Acquisition Time is 0 TAD
#define ADC_2_TAD        0b00001000				//A/D Acquisition Time is 2 TAD
#define ADC_4_TAD        0b00010000				//A/D Acquisition Time is 4 TAD
#define ADC_6_TAD        0b00011000				//A/D Acquisition Time is 6 TAD
#define ADC_8_TAD        0b00100000				//A/D Acquisition Time is 8 TAD
#define ADC_12_TAD       0b00101000				//A/D Acquisition Time is 12 TAD
#define ADC_16_TAD       0b00110000				//A/D Acquisition Time is 16 TAD
#define ADC_20_TAD       0b00111000				//A/D Acquisition Time is 20 TAD


//*************** A/D Result Format Select ***********************************
#define ADC_RIGHT_JUST   0b10000000 			// Right justify A/D result
#define ADC_LEFT_JUST    0b00000000 			// Left justify A/D result

/***********************************************************************************
Macro       : ADC_CALIB()
Overview : Macro performs the Calibration on next A/D conversion
Parameters   : None
Remarks     : None
***********************************************************************************/
#define	ADC_CALIB()	    (ADCON1bits.ADCAL=1)

/***********************************************************************************
Macro       : ADC_NO_CALIB()
Overview : Macro performs the Normal A/D converter operation with no Calibration
Parameters   : None
Remarks     : None
***********************************************************************************/
#define ADC_NO_CALIB()	(ADCON1bits.ADCAL=0)

/*ADCON0 and ADCON1 register Values*/

#define ADC_CONFIG_ADCON0  (ADCON0_VAL | ADC_REF_VDD_VSS) 
#define ADC_CONFIG_ADCON1  (ADCON1_VAL | ADC_RIGHT_JUST | ADC_FOSC_4 | ADC_2_TAD)


/***********************************************************************/
/********************C O M P A R A T O R********************************/
/***********************************************************************/
/***********************************************************************/
/*Comparator register definition*/
 #define CMP_CMCON		    				 CM2CON
 #define CMP_CVRCON		    				 CVRCON
      
/*CMCON control register bit definition*/
#define CMP_Enable_Disable_Bit				CM2CONbits.CON
#define CMP_Output_Enable_Disable_Bit		CM2CONbits.COE
#define CMP_Output_Polarity_Bit				CM2CONbits.CPOL
#define CMP_Event_Bit						CM2CONbits.CEVT
#define CMP_CMCON_Ouput_Bit					CM2CONbits.COUT
#define CMP_Trigger_Select_HighBit			CM2CONbits.EVPOL1
#define CMP_Trigger_Select_LowBit			CM2CONbits.EVPOL0
#define CMP_Reference_Select_Bit			CM2CONbits.CREF
#define CMP_Channel_Select_HighBit			CM2CONbits.CCH1
#define CMP_Channel_Select_LowBit			CM2CONbits.CCH0
#define CMP_Trigger_Select_Bits				CM2CONbits.EVPOL
#define CMP_Channel_Select_Bits				CM2CONbits.CCH

/*CMSTAT register bit definition*/
#define CMP_Ouput_Bit						CMSTATbits.C2OUT

/*CMCON interrupt register bit definition*/

#define CMP_Interrupt_Flag_Bit			IFS1bits.CMIF
#define CMP_Interrupt_Enable_Bit		IEC1bits.CMIE
#define CMP_Interrupt_Priority_Bits		IPC4bits.CMIP

/******************************************************************************
 Macro      : CMP_EnblDsbl(state)
 Overview   : Macro Enables/Disables the Comparator 
 Parameter  : state - *1 Comparator is enabled 
                      *0 Comparator is disabled
 Remarks    : None
 *****************************************************************************/
#define CMP_EnblDsbl(state)      		(CMP_Enable_Disable_Bit = state)

/******************************************************************************
 Macro       : CMP_Output_EnblDsbl(state) 
 Overview    : Macro Enables/Disables Comparator output on the output pad 
 Parameter   : state -  *1 Comparator output driven on the output pad 
                        *0 Comparator output is not driven on the output pad
 Remarks     : None
*****************************************************************************/
#define CMP_Output_EnblDsbl(state)    (CMP_Output_Enable_Disable_Bit = state)

/******************************************************************************
 Macro       : CMP_Output_Polarity(state) 
 Overview    : 
 Parameter   : state -  *1 
                        *0 
 Remarks     : None
*****************************************************************************/
#define CMP_Output_Polarity(state)    (CMP_Output_Polarity_Bit = state)


/******************************************************************************
 Macro       : CMP_Output_Polarity(state) 
 Overview    : 
 Parameter   : state -  *1 
                        *0 
 Remarks     : None
*****************************************************************************/
#define CMP_Event(state)    (CMP_Event_Bit = state)


/******************************************************************************
 Macro       : CMP_Trigger_Select(state) 
 Overview    : 
 Parameter   : state -  *1 
                        *0 
 Remarks     : None
*****************************************************************************/
#define CMP_Trigger_Select(state)    (CMP_Trigger_Select_Bits = state)


/******************************************************************************
 Macro       : CMP_Trigger_Select(state) 
 Overview    : 
 Parameter   : state -  *1 
                        *0 
 Remarks     : None
*****************************************************************************/
#define CMP_Reference_Select(state)    (CMP_Reference_Select_Bit = state)


/******************************************************************************
 Macro       : CMP_Channel_Select(state) //n1:
 Overview    : 
 Parameter   : state -  *1 
                        *0 
 Remarks     : None
*****************************************************************************/
#define CMP_Channel_Select(state)    (CMP_Channel_Select_Bits = state)

/******************************************************************************
 Macro       : CMP_Get_STATE() 
 Overview    : Macro Returns state of Comparator output
              When  C2INV = 0:
               1 = C2 VIN+ > C2 VIN-
               0 = C2 VIN+ < C2 VIN
              When   C2INV = 1:
               0 = C2 VIN+ > C2 VIN-
               1 = C2 VIN+ < C2 VIN- 
 Parameter   : None 
 Remarks     : State of Comparator depends on Inverse selection  bit in 
              control register
 *****************************************************************************/
#define CMP_Get_STATE()      			(CMP_Ouput_Bit)

/***********************************************************************
Macro      : EnableIntCMP
Overview   : This macro enables the comparator interrupt. 
Parameter  : None 
Remarks    : This macro sets comparator Interrupt Enable bit of Interrupt 
             Enable Control Register.
************************************************************************/ 
#define EnableIntCMP               (CMP_Interrupt_Enable_Bit = 1)

/***********************************************************************
Macro      : DisableIntCMP
Overview   : This macro disables the comparator interrupt.
Parameter  : None
Remarks    : This macro clears comparator Interrupt Enable bit of Interrupt 
             Enable Control register.
************************************************************************/ 
#define DisableIntCMP                (CMP_Interrupt_Enable_Bit = 0)

/***********************************************************************
Macro      : SetPriorityIntCMP (priority)
Overview   : This macro sets priority for comparator interrupt. 
Parameter  : priority - This input parameter is the level of interrupt priority 
Remarks    : This macro sets comparator Interrupt Priority bits of Interrupt 
             Priority Control register.
************************************************************************/  
#define SetPriorityIntCMP(priority)     (CMP_Interrupt_Priority_Bits = priority)

/*******************************************************************
Macro       : CMP_Clear_Intr_Status_Bit
Overview    : Macro to Clear Comparator Interrupt Status bit 
Parameter   : None 
Remarks     : None 
*******************************************************************/
#define CMP_Clear_Intr_Status_Bit     (CMP_Interrupt_Flag_Bit = 0)


/*CMxCON register definition*/
#define CMP_ENABLE                  	 0x8000 /* Comparator is enabled */
#define CMP_DISABLE                      0x0000 /* Comparator is disabled */
#define CMP_ENBL_DSBL_MASK               (~CMP_ENABLE)
#define CMP_OUTPUT_ENABLE                0x4000 /* Comparator output present on the CXOUT pin */
#define CMP_OUTPUT_DISABLE               0x0000 /* Comparator output is internal only */
#define CMP_OUTPUT_MASK                  (~CMP_OUTPUT_ENABLE)
#define CMP_OUTPUT_INVERT    	         0x2000 /* Comparator output inverted */
#define CMP_OUTPUT_NOT_INVERT            0x0000 /* Comparator output not inverted */
#define CMP_OUTPUT_INVERT_MASK           (~CMP_OUTPUT_INVERT)
#define CMP_CHANGE_STATE                 0x0200 /* Comparator output changed states */
#define CMP_NO_CHANGE                    0x0000 /* Comparator output did not change states */
#define CMP_STATE_MASK                   (~CMP_CHANGE_STATE )
#define CMP_INTERRUPT_ON_ANY_EDGE		 0X00C0 /* Comparator interrupt generated on any edge of the selected comparator output*/
#define CMP_INTERRUPT_ON_FALLING_EDGE	 0X0080 /* Comparator interrupt generated only on falling edge of the selected comparator output*/
#define CMP_INTERRUPT_ON_RISING_EDGE	 0X0040 /* Comparator interrupt generated only on rising edge of the selected comparator output*/
#define CMP_INTERRUPT_DISABLED			 0X0000  /* Comparator interrupt generation is disabled */
#define CMP_INTERRUP_EDGE_MASK           (~CMP_INTERRUPT_ON_ANY_EDGE) 
#define CMP_POS_IP_CV_Ref                0x0010 /* Input is connected to internal CVref voltage */ 
#define CMP_POS_IP_CXINA 	             0x0000 /* Input is connected to CXINA pin */
#define CMP_POS_IP_MASK                  (~CMP_POS_IP_CV_Ref)
#define CMP_NEG_IP_CXINB				 0X0000 /* Input is connected to CXINB pin */
#define CMP_NEG_IP_CXINC			     0X0001 /* Input is connected to CXINC pin */
#define CMP_NEG_IP_CXIND			     0X0002 /* Input is connected to CXIND pin */

/*CVRCON register definition*/
#define CMP_VRef_Enable                  0x0080 /* CVREF circuit powered on */
#define CMP_VRef_Disable                 0x0000 /* CVREF circuit powered down */
#define CMP_VRef_MASK                   (~CMP_VRef_Enable)
#define CMP_VRef_OUTPUT_Enable           0x0040 /* CVREF voltage level is output on CVREF pin */
#define CMP_VRef_OUTPUT_Disable          0x0000 /* CVREF voltage level is disconnected from CVREF pin */
#define CMP_VRef_OUTPUT_MASK             (~CMP_VRef_OUTPUT_Enable)
#define CMP_VRef_SELECT_24_STEPS   	 	 0x0020 /* 0 to 0.67 CVRSRC, with CVRSRC/24 step size */
#define CMP_VRef_SELECT_32_STEPS         0x0000 /* 0.25 CVRSRC to 0.75 CVRSRC, with CVRSRC/32 step size */
#define CMP_VRef_STEP_SELECT_MASK        (~CMP_VRef_SELECT_24_STEPS)
#define CMP_Vrsrc_Vref_Vref        		 0x0010 /* Comparator reference source CVRSRC = VREF+ – VREF- */
#define CMP_Vrsrc_AVDD_AVSS        		 0x0000 /* Comparator reference source CVRSRC = AVDD – AVSS */
#define CMP_Vrsrc_MASK                   (~CMP_Vrsrc_Vref_Vref)
#define CMP_CVrsrc      				 0x000F /* 0 CVRSRC with CVRSRC/24 step size, 0.25 CVRSRC with CVRSRC/32 step size */

/*Registers Defaults*/
#define CMP_CMCON_VAL    				 0x0000
#define CVREF_VAL    				 	 0x0000


#define CMP_CONFIG_CMCON 			(CMP_CMCON_VAL | CMP_ENABLE | CMP_OUTPUT_DISABLE | CMP_OUTPUT_NOT_INVERT  \
									 | CMP_NO_CHANGE | CMP_INTERRUPT_DISABLED | CMP_POS_IP_CV_Ref | CMP_NEG_IP_CXINB)

#define CMP_CONFIG_CVRCON			(CVREF_VAL | CMP_VRef_Enable | CMP_VRef_OUTPUT_Enable | CMP_VRef_SELECT_32_STEPS \
									 | CMP_Vrsrc_AVDD_AVSS | CMP_CVrsrc)	



/***********************************************************************/
/********************C T M U********************************************/
/***********************************************************************/
/************************************************************************/
 /*CTMUCON Control Register*/
 #define CTMU_ENABLE       			   0x8000 /*CTMU is Enabled*/
 #define CTMU_DISABLE      			   0x0000 /*CTMU is Disabled*/
 #define CTMU_ENBL_DISBL_MASK          (~CTMU_ENABLE)
 
 #define CTMU_IDLE_STOP                0x2000 /*CTMU discontinue module operation in Idle mode*/
 #define CTMU_IDLE_CONTINUE            0x0000 /*CTMU Operate in Idle mode*/
 #define CTMU_IDLE_MASK                (~CTMU_IDLE_STOP)
 
 #define CTMU_TIME_GEN_ENABLE          0x1000 /*CTMU enables edge delay generation*/
 #define CTMU_TIME_GEN_DISABLE         0x0000 /*CTMU disables edge delay generation*/
 #define CTMU_TIME_GEN_MASK            (~CTMU_TIME_GEN_ENABLE)
 
 #define CTMU_EDGE_ENABLE              0x0800 /*CTMU edges are not blocked*/
 #define CTMU_EDGE_DISABLE             0x0000 /*CTMU edges are blocked*/
 #define CTMU_EDGE_MASK                (~CTMU_EDGE_ENABLE)
 
 #define CTMU_EDGE_SEQUENCE_ON         0x0400 /*Edge1 event must occur before edge2 event can occur*/
 #define CTMU_EDGE_SEQUENCE_OFF        0x0000 /*No edge sequence os needed*/
 #define CTMU_EDGE_SEQUENCE_MASK       (~CTMU_EDGE_SEQUENCE)
 
 #define CTMU_ANA_CURR_SOURCE_GND      0x0200 /*CTMU Analog current source output is grounded*/
 #define CTMU_ANA_CURR_SOURCE_NOT_GND  0x0000 /*CTMU Analog current source output is not grounded*/
 #define CTMU_ANA_CURR_SOURCE_MASK     (~CTMU_ANA_CURR_SOURCE_GND)
 
 #define CTMU_TRIG_OUTPUT_ENABLE       0x0100 /*Trigger output is enabled*/
 #define CTMU_TRIG_OUTPUT_DISABLE      0x0000 /*Trigger output is disabled*/
 #define CTMU_TRIG_OUTPUT_MASK         (~CTMU_TRIG_OUTPUT)

 #define CTMU_EDGE1_POLARITY_POS       0x0010 /*Edge 1 programmed for a positive edge response*/
 #define CTMU_EDGE1_POLARITY_NEG       0x0000 /*Edge 1 programmed for a negative edge response*/
 #define CTMU_EDGE1_POLARITY_MASK      (~CTMU_EDGE2_POS_POLARITY)
 
 #define CTMU_EDGE1_SOURCE_CTED1       0x000C /*CTED1 is a source select for Edge1*/
 #define CTMU_EDGE1_SOURCE_CTED2       0x0008 /*CTED2 is a source select for Edge1*/
 #define CTMU_EDGE1_SOURCE_OC1         0x0004 /*OC1 is a source select for Edge1*/
 #define CTMU_EDGE1_SOURCE_TIMER1      0x0000 /*TIMER1 is a source select for Edge1*/
 #define CTMU_EDGE1_SOURCE_MASK        (~CTMU_EDGE2_SOURCE_CTED1)
 
 #define CTMU_EDGE2_POLARITY_POS       0x0080 /*Edge 2 programmed for a positive edge response*/
 #define CTMU_EDGE2_POLARITY_NEG       0x0000 /*Edge 2 programmed for a negative edge response*/
 #define CTMU_EDGE2_POLARITY_MASK      (~CTMU_EDGE2_POS_POLARITY)
 
 #define CTMU_EDGE2_SOURCE_CTED1       0x0060 /*CTED1 is a source select for Edge2*/
 #define CTMU_EDGE2_SOURCE_CTED2       0x0040 /*CTED2 is a source select for Edge2*/
 #define CTMU_EDGE2_SOURCE_OC1         0x0020 /*OC1 is a source select for Edge2*/
 #define CTMU_EDGE2_SOURCE_TIMER1      0x0000 /*TIMER1 is a source select for Edge2*/
 #define CTMU_EDGE2_SOURCE_MASK        (~CTMU_EDGE2_SOURCE_CTED1) 
 
 /*CTMU1CON Current Control register*/ 
 #define CTMU_POS_CURR_TRIM		       0x0400 /*2% of Positive change from nominal current*/
 #define CTMU_NEG_CURR_TRIM          0xFC00 /*2% of Negative change from nominal current*/
 #define CTMU_NOMINAL_CURRENT          0x0000 /*Nominal Current output specified by IRNG1:IRNG0*/
 #define CTMU_CURR_RANGE_100_BASE_CURR 0x0300 /*Current source Range is 100*Base current (55uA) */
 #define CTMU_CURR_RANGE_10_BASE_CURR  0x0200 /*Current source Range is 10*Base current (5.5uA)*/
 #define CTMU_CURR_RANGE_BASE_CURR     0x0100 /*Current source Range is Base current (0.55uA)*/
 #define CTUM_CURR_SOURCE_DISABLE      0x0000 /*Current source disabled*/

 
 #define CTMU_INT_PRI                	0x0000 /*CTMU interrupt priority is 0*/
 
 #define CTMU_INT_ENABLE               0x0008 /* Enable CTMU interrupts */
 #define CTMU_INT_DISABLE              0x0000 /* Disable CTMU interrupts */


/************************************************************************
Macro       : Set_CTMU_ENABLE_Status 
Overview    : setting or clearing CTMU Enable Module Bit 
Parameters  : ENABLE '1' or DISABLE '0'
Remarks     : None.
**************************************************************************/ 
#define Set_CTMU_ENABLE_Status(State)   			(CTMUCONHbits.CTMUEN = State)

/************************************************************************
Macro       : Idle_Mode_CTMU_Operation 
Overview    : CTMU Operation in Idle 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
#define Idle_Mode_CTMU_Operation(State)   			(CTMUCONHbits.CTMUSIDL = State)

/************************************************************************
Macro       : Set_CTMU_Time_Generation 
Overview    : setting or clearing CTMU TIME Generation Bit 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
#define Set_CTMU_Time_Generation(State)   			(CTMUCONHbits.TGEN = State)


/************************************************************************
Macro       : Enable_Disable_CTMU_Time_Generation 
Overview    : setting or clearing CTMU TIME Generation Bit 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
#define Block_CTMU_Edge(State)   			(CTMUCONHbits.EDGEN = 0)

/************************************************************************
Macro       : Enable_Disable_CTMU_Time_Generation 
Overview    : setting or clearing CTMU TIME Generation Bit 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
#define Unblock_CTMU_Edge(State)   			(CTMUCONHbits.EDGEN = 1)


/************************************************************************
Macro       : Set_CTMU_Edge_Sequence 
Overview    : setting or clearing CTMU Edge Sequence Bit 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
#define Set_Edge_Sequence(State)   			(CTMUCONHbits.EDGSEQEN = State)


/************************************************************************
Macro       : Enable_CTMU_CurrentDischarge 
Overview    : setting the CTMU Current Discharge  Bit 
Parameters  : None
Remarks     : None.
**************************************************************************/ 
#define Enable_CTMU_CurrentDischarge   			(CTMUCONHbits.IDISSEN = 1)

/************************************************************************
Macro       : Disable_CTMU_CurrentDischarge 
Overview    : Clearing the CTMU Current Discharge  Bit 
Parameters  : None
Remarks     : None.
**************************************************************************/ 
 
#define Disable_CTMU_CurrentDischarge   			(CTMUCONHbits.IDISSEN = 0)


/************************************************************************
Macro       : Set_CTMU_Trigger_Control 
Overview    : setting or clearing CTMU Trigger Control Bit 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
#define Set_CTMU_Trigger_Control(State)   			(CTMUCONHbits.CTTRIG = State)



/************************************************************************
Macro       : Enable_CTMU_Positive_Edge2_Polarity
Overview    : By setting Edge 2 Polarity Select bit 
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Enable_CTMU_Positive_Edge2_Polarity				(CTMUCONLbits.EDG2POL = 1)


/************************************************************************
Macro       : Enable_CTMU_Negative_Edge2_Polarity
Overview    : By setting Edge 2 Polarity Select bit 
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Enable_CTMU_Negative_Edge2_Polarity				(CTMUCONLbits.EDG2POL = 0)


/************************************************************************
Macro       : Enable_CTMU_Positive_Edge1_Polarity
Overview    : By setting Edge 1 Polarity Select bit 
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Enable_CTMU_Positive_Edge1_Polarity				(CTMUCONLbits.EDG1POL = 1)


/************************************************************************
Macro       : Enable_CTMU_Negative_Edge1_Polarity
Overview    : By setting Edge 1 Polarity Select bit 
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Enable_CTMU_Negative_Edge1_Polarity				(CTMUCONLbits.EDG1POL = 0)


/************************************************************************
Macro       : CTMU_Edge1_Source_Select 
Overview    : Edge 1 Source Select bits 
Parameters  :  State
Remarks     : None.
**************************************************************************/ 
//PIC18
#define CTMU_Edge1_Source_Select(State)   	(CTMUCONLbits.EDG1SEL0 = (State&0x01) && (CTMUCONLbits.EDG1SEL1 = (State&0x02)>>1))


/************************************************************************
Macro       : CTMU_Edge2_Source_Select 
Overview    : Edge 2 Source Select bits 
Parameters  :  
Remarks     : None.
**************************************************************************/ 
//PIC18
#define CTMU_Edge2_Source_Select(State)   	(CTMUCONLbits.EDG2SEL0 = (State&0x01) && (CTMUCONLbits.EDG2SEL1 = (State&0x02)>>1))


/************************************************************************
Macro       : Enable_CTMUEdge1
Overview    : By setting edge1 status bit current source enables  
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Enable_CTMUEdge1  				(CTMUCONLbits.EDG1STAT = 1)


/************************************************************************
Macro       : Enable_CTMUEdge2
Overview    : By setting edge2 status bit current source enables  
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Enable_CTMUEdge2 				(CTMUCONLbits.EDG2STAT = 1)


/************************************************************************
Macro        :Disbl_CTMUEdge1
Overview    : By clearing edge1 status bit disable the current source
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Disbl_CTMUEdge1 				(CTMUCONLbits.EDG1STAT = 0)


/************************************************************************
Macro       :Disbl_CTMUEdge2
Overview    : By clearing edge2 status bit disable the current source 
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Disbl_CTMUEdge2				(CTMUCONLbits.EDG2STAT = 0)


/************************************************************************
Macro       : Disbl_Currentsource
Overview    : By clearing EDGSTAT bit disable the source.
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Disbl_CurrentSource   		( CTMUCONLbits.EDG1STAT = 0 , CTMUCONLbits.EDG2STAT = 0 )


/************************************************************************
Macro       : Enabl_Currentsource
Overview    : By setting EDGSTAT bit disable the source.
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Enable_CurrentSource   		(CTMUCONLbits.EDG1STAT = 1 , CTMUCONLbits.EDG2STAT = 1 )


/************************************************************************
Macro       : CTMUEdge1_Status
Overview    : Returns the status of CTMU edge1  
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define CTMUEdge1_Status      		CTMUCONLbits.EDG1STAT

/************************************************************************
Macro       : CTMUEdge2_Status
Overview    : Returns the status of CTMU edge2 
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define CTMUEdge2_Status  	 		CTMUCONLbits.EDG2STAT


/************************************************************************
Macro       : CTMU_Trim_Value 
Overview    : Sets the Trim Value for CTMU
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define CTMU_Trim_Value(Value)	 		CTMUICONbits.ITRIM = (Value)



/************************************************************************
Macro          : CTMU_Select_Current_Source
Overview     : Sets the current source range Value for CTMU
Parameters  : 				CURRENT_RANGE_100XBASE_CURRENT //urrent source Range is 100*Base current (55uA) 
 *						 CURRENT_RANGE_10XBASE_CURRENT  //Current source Range is 10*Base current (5.5uA)
 *						 CURRENT_RANGE_BASE_CURRENT     //Current source Range is Base current (0.55uA)
 *						 CURRENT_SRC_DISABLED      //Current source disabled
 * 
Remarks      : None.
**************************************************************************/ 
#define CTMU_Select_Current_Source(Value)	 		CTMUICONbits.IRNG = (Value)


/************************************************************************
Macro          : CTMU_Get_Current_Source
Overview     : Gets the Current Source range value
Parameters  : None 
Remarks      : None.
**************************************************************************/ 
#define CTMU_Get_Current_Source	 		CTMUICONbits.IRNG


/***********************************************************************
Macro      : EnableIntCTMU 
Overview   : This macro enables the CTMU interrupt. 
Parameters : None 
Remarks    : This macro sets CTMU Interrupt Enable bit of Interrupt 
                  Enable Control Register.
************************************************************************/ 
#define EnableIntCTMU                (IEC4bits.CTMUIE = 1)

/***********************************************************************
Macro      : DisableIntCTMU 
Overview   : This macro disables the CTMU interrupt.
Parameters : None
Remarks    : This macro clears CTMU Interrupt Enable bit of Interrupt 
             Enable Control register.
************************************************************************/ 
#define DisableIntCTMU               (IEC4bits.CTMUIE = 0)

/***********************************************************************
Macro      : SetPriorityIntCTMU(priority) 
Overview   : This macro sets priority for CTMU interrupt. 
Parameters : priority - This input parameter is the level of interrupt priority 
Remarks    : This macro sets CTMU Interrupt Priority bits of Interrupt 
             Priority Control register.
************************************************************************/  
#define SetPriorityIntCTMU(priority)    (IPC19bits.CTMUIP = priority)

/*******************************************************************
Macro       : CTMU_Clear_Intr_Status_Bit 
Overview    : Macro to Clear CTMU Interrupt Status bit 
Parameters  : None 
Remarks     : None 
*******************************************************************/
#define CTMU_Clear_Intr_Status_Bit    (IFS4bits.CTMUIF = 0) 



#endif //#ifdef __18CXX


#endif	// _MTOUCH_PIC18_CTMU_PHY_H




