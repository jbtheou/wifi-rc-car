
/*****************************************************************************
 * FileName:        mTouchCap_PIC24_CTMU_Physical.h
 * Dependencies:
 * Processor:       PIC24
 * Compiler:       	C30
 * Linker:          MPLAB LINK30
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
 * Naveen. M				    14 Apr 2009			Version 1.0 Initial Draft
 * Sasha. M	/ Naveen. M			4 May 2009  		Version 1.0 Initial Draft
 * Sasha. M	/ Naveen. M			11 Nov 2009  		Version 1.0 Release
 * Sasha. M	/ Nithin. 			10 April 2010  		Version 1.20 Release
  * Nithin M						11 Aug 2010	Implemetation of Low Power Demo 
 *****************************************************************************/
#ifndef _MTOUCH_PIC24_CTMU_PHYSICAL_H
#define _MTOUCH_PIC24_CTMU_PHYSICAL_H

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Includes	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include 		"Config.h"
#ifdef USE_MTOUCH_AND_GRAPHICS
	#include 		"mTouchCap_Config.h"
	#include 		"mTouchCap_HardwareProfile.h"
#else
	#include 		"HardwareProfile.h"	
#endif	 
#ifndef			USE_MTOUCH_AND_GRAPHICS
	#include 		"mTouchCap_Timers.h"
#endif
#include 		"mTouchCap_Adc.h"
#include 		"GenericTypeDefs.h"

#ifdef __PIC24F__

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Constants	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


/***********************************************************************/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Variables  	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Externs  	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
extern WORD curBigData		[MAX_ADC_CHANNELS];
extern WORD	curRawData		[MAX_ADC_CHANNELS];	//Storage for CTMU channel values
extern WORD	tripValue   	[MAX_ADC_CHANNELS];	//Storage for the trip point for each channel	
extern WORD	hystValue   	[MAX_ADC_CHANNELS];	//Storage for the hysterisis value for each channel
extern WORD	pressedCount   	[MAX_ADC_CHANNELS];	//Storage for count of pressed value for each channel
extern WORD	unpressedCount  [MAX_ADC_CHANNELS];	//Storage for count of unpressed value for each channel
extern WORD	avg_delay 		[MAX_ADC_CHANNELS];//Storage for count for average update for each channel	
extern WORD	averageData 	[MAX_ADC_CHANNELS];	// running average of CTMU channels	
extern WORD	smallAvg		[MAX_ADC_CHANNELS];	// current button smallavg
extern WORD	actualValue		[MAX_ADC_CHANNELS];	// actual raw A/D counts for each channel
extern WORD	channel_TRIM_value	[MAX_ADC_CHANNELS];
extern WORD	channel_IRNG_value	[MAX_ADC_CHANNELS];
extern BYTE	chFilterType	[MAX_ADC_CHANNELS];	// Channel filter type
extern BYTE	chDecodeMethod	[MAX_ADC_CHANNELS];	// decode method type
extern BYTE Press_State [MAX_ADC_CHANNELS];
extern SHORT	startupCount;				// variable to 'discard' first N samples
extern SHORT loopCount;
extern WORD	immediateValue;			// current button value
extern WORD	scaledBigValue;				// current button bigval

/* array for different analog channels */
extern WORD channelIndex[MAX_ADC_CHANNELS];
extern BYTE 	Channel_Pressed_Status[MAX_ADC_CHANNELS];
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Function Prototypes  ~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void mTouchCapPhy_Init(void);	 
void mTouchCapApp_PortSetup(void);
void mTouchCapPhy_CTMUSetup(void);
void mTouchCapPhy_AdcSetup(void);
void mTouchCapPhy_ReadCTMU(WORD Index);
void mTouchCapPhy_ChannelSetup(WORD ChannelNum);
void mTouchCapPhy_InitCTMU(void);
void mTouchCapPhy_ChargeTimeInit(void);
void mTouchCapPhy_Init(void);
void mTouchCapPhy_SequenceChannels(void);	
void mTouchCapPhy_SetupCurrentSourceRange(WORD CurrentSourceRange);
void mTouchCapPhy_SetTrimValue( WORD TrimValue);
void mTouchCapPhy_Discharge_Current (void);
void mTouchCapPhy_Charge_Current (void);
WORD mTouchCapPhy_Read_ADC();
void CTMU_Current_trim_config(int channel_no);
void DynamicTripValueCalculation(WORD Index);
void mTouchCapPhy_AverageData(WORD Index);
void mTouchCapPhy_StablizeChannelData(void);
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~	Enums      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  	*/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/***********************************************************************/
/********************	End of PORTS  	*****************************************/
/***********************************************************************/
/***********************************************************************/


/***********************************************************************/
/********************ANALOG CHANNELS TRISBITS DEFINITION*****************************************/
/***********************************************************************/
#ifdef  ADC_LEGACY

#define DIGITAL                 1
#define ANALOG	                0

#define TRIS_CHANNEL_AN0		TRISBbits.TRISB0
#define TRIS_CHANNEL_AN1  		TRISBbits.TRISB1
#define TRIS_CHANNEL_AN2  		TRISBbits.TRISB2
#define TRIS_CHANNEL_AN3  		TRISBbits.TRISB3
#define TRIS_CHANNEL_AN4  		TRISBbits.TRISB4
#define TRIS_CHANNEL_AN5  		TRISBbits.TRISB5
#define TRIS_CHANNEL_AN6  		TRISBbits.TRISB6
#define TRIS_CHANNEL_AN7  		TRISBbits.TRISB7
#define TRIS_CHANNEL_AN8  		TRISBbits.TRISB8
#define TRIS_CHANNEL_AN9  		TRISBbits.TRISB9
#define TRIS_CHANNEL_AN1O  		TRISBbits.TRISB10
#define TRIS_CHANNEL_AN11  		TRISBbits.TRISB11
#define TRIS_CHANNEL_AN12  		TRISBbits.TRISB12
#define TRIS_CHANNEL_AN13  		TRISBbits.TRISB13
#define TRIS_CHANNEL_AN14  		TRISBbits.TRISB14
#define TRIS_CHANNEL_AN15  		TRISBbits.TRISB15


#define ADPCF_CHANNEL_AN0(Value) 		AD1PCFGbits.PCFG0 = Value;
#define ADPCF_CHANNEL_AN1(Value) 		AD1PCFGbits.PCFG1 = Value;
#define ADPCF_CHANNEL_AN2(Value) 		AD1PCFGbits.PCFG2 = Value;
#define ADPCF_CHANNEL_AN3(Value) 		AD1PCFGbits.PCFG3 = Value;
#define ADPCF_CHANNEL_AN4(Value) 		AD1PCFGbits.PCFG4 = Value;
#define ADPCF_CHANNEL_AN5(Value) 		AD1PCFGbits.PCFG5 = Value;
#define ADPCF_CHANNEL_AN6(Value) 		AD1PCFGbits.PCFG6 = Value;
#define ADPCF_CHANNEL_AN7(Value) 		AD1PCFGbits.PCFG7 = Value;
#define ADPCF_CHANNEL_AN8(Value) 		AD1PCFGbits.PCFG8 = Value;
#define ADPCF_CHANNEL_AN9(Value) 		AD1PCFGbits.PCFG9 = Value;
#define ADPCF_CHANNEL_AN10(Value)		AD1PCFGbits.PCFG10 = Value;
#define ADPCF_CHANNEL_AN11(Value)		AD1PCFGbits.PCFG11 = Value;
#define ADPCF_CHANNEL_AN12(Value)		AD1PCFGbits.PCFG12 = Value;
#define ADPCF_CHANNEL_AN13(Value)		AD1PCFGbits.PCFG13 = Value;
#define ADPCF_CHANNEL_AN14(Value)		AD1PCFGbits.PCFG14 = Value;
#define ADPCF_CHANNEL_AN15(Value)		AD1PCFGbits.PCFG15 = Value;

#endif


#ifdef  ADC_NEW

#define DIGITAL                 0
#define ANALOG	                1

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
#define TRIS_CHANNEL_AN1O  		TRISBbits.TRISB10
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



#define ADPCF_CHANNEL_AN0(Value) 		ANSBbits.ANSB0 = Value;
#define ADPCF_CHANNEL_AN1(Value) 		ANSBbits.ANSB1 = Value;
#define ADPCF_CHANNEL_AN2(Value) 		ANSBbits.ANSB2 = Value;
#define ADPCF_CHANNEL_AN3(Value) 		ANSBbits.ANSB3 = Value;
#define ADPCF_CHANNEL_AN4(Value) 		ANSBbits.ANSB4 = Value;
#define ADPCF_CHANNEL_AN5(Value) 		ANSBbits.ANSB5 = Value;
#define ADPCF_CHANNEL_AN6(Value) 		ANSBbits.ANSB6 = Value;
#define ADPCF_CHANNEL_AN7(Value) 		ANSBbits.ANSB7 = Value;
#define ADPCF_CHANNEL_AN8(Value) 		ANSBbits.ANSB8 = Value;
#define ADPCF_CHANNEL_AN9(Value) 		ANSBbits.ANSB9 = Value;
#define ADPCF_CHANNEL_AN10(Value)		ANSBbits.ANSB10 = Value;
#define ADPCF_CHANNEL_AN11(Value)		ANSBbits.ANSB11= Value;
#define ADPCF_CHANNEL_AN12(Value)		ANSBbits.ANSB12= Value;
#define ADPCF_CHANNEL_AN13(Value)		ANSBbits.ANSB13= Value;
#define ADPCF_CHANNEL_AN14(Value)		ANSBbits.ANSB14= Value;
#define ADPCF_CHANNEL_AN15(Value)		ANSBbits.ANSB15= Value;

#define ADPCF_CHANNEL_AN16(Value)		ANSCbits.ANSC4 = Value;
#define ADPCF_CHANNEL_AN17(Value)		ANSGbits.ANSG6 = Value;
#define ADPCF_CHANNEL_AN18(Value)		ANSGbits.ANSG7 = Value;
#define ADPCF_CHANNEL_AN19(Value)		ANSGbits.ANSG8 = Value;

#define ADPCF_CHANNEL_AN20(Value)		ANSGbits.ANSG9 = Value;
#define ADPCF_CHANNEL_AN21(Value)		ANSEbits.ANSE9 = Value;
#define ADPCF_CHANNEL_AN22(Value)		ANSAbits.ANSA7 = Value;
#define ADPCF_CHANNEL_AN23(Value)		ANSAbits.ANSA6 = Value;

#endif


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
#define EnableIntADC1                (IEC0bits.AD1IE = 1)

/***********************************************************************
Macro      : DisableIntADC1
Overview   : This macro disables the ADC interrupt.
Parameters : None
Remarks    : This macro clears ADC Interrupt Enable bit of Interrupt
             Enable Control register.
************************************************************************/
#define DisableIntADC1                (IEC0bits.AD1IE = 0)

/***********************************************************************
Macro      : SetPriorityIntADC1(priority)
Overview   : This macro sets priority for ADC interrupt.
Parameters : priority - This input parameter is the level of interrupt priority
Remarks    : This macro sets ADC Interrupt Priority bits of Interrupt
             Priority Control register.
************************************************************************/
#define SetPriorityIntADC1(priority)     (IPC3bits.AD1IP = priority)

/*******************************************************************
Macro       : ADC1_Clear_Intr_Status_Bit
Overview    : Macro to Clear ADC Interrupt Status bit
Parameters  : None
Remarks     : None
*******************************************************************/
#define ADC1_Clear_Intr_Status_Bit (IFS0bits.AD1IF = 0)

/*******************************************************************
Macro       : ADC1_IF_Bit
Overview    : returns ADC1 Interrupt Flag
Parameters  : None
Remarks     : None
*******************************************************************/
#define ADC1_IF_Bit (IFS0bits.AD1IF)


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
#define DisableADC1                (AD1CON1bits.ADON = 0)

/************************************************************************
Macro       : Set_Adc_Enable_State
Overview    : This function enables or disable the ADC module depending upon the value.
Parameters  : None
Remarks     : None.
**************************************************************************/
#define Set_Adc_Enable_State(Value)          (AD1CON1bits.ADON = Value)


/************************************************************************
Macro       : Enable_ADC_Sampling
Overview    : This function starts the A/D conversion.
Parameters  : None
Remarks     : None.
**************************************************************************/
#define Enable_ADC_Sampling       (AD1CON1bits.SAMP = 1)


/************************************************************************
Macro       : Disable_ADC_Sampling
Overview    : This function starts the A/D conversion.
Parameters  : None
Remarks     : None.
**************************************************************************/
#define Disable_ADC_Sampling       (AD1CON1bits.SAMP = 0)

/************************************************************************
Macro       : ADC_Done_Bit
Overview    : This function declares the AD1CON1bits.DONE.
Parameters  : None
Remarks     : None.
**************************************************************************/
#define ADC_Done_Bit       			 (AD1CON1bits.DONE)

/************************************************************************
Macro       : Adc_Port_Configuration
Overview    : Configure ADC Port pin as Analog or Digital
Parameters  : None
Remarks     : None.
**************************************************************************/
#ifdef ADC_LEGACY
#define Adc_Port_Configuration(Value)	(AD1PCFGL = Value)
#endif

#ifdef ADC_NEW
#define Adc_PortA_Configuration(Value)	(ANSA = Value)
#define Adc_PortB_Configuration(Value)	(ANSB = Value)
#define Adc_PortC_Configuration(Value)	(ANSC = Value)
#define Adc_PortD_Configuration(Value)	(ANSD = Value)
#define Adc_PortE_Configuration(Value)	(ANSE = Value)
#define Adc_PortF_Configuration(Value)	(ANSF = Value)
#define Adc_PortG_Configuration(Value)	(ANSG = Value)
#endif

/************************************************************************

		 Redefining ADC Register

**************************************************************************/
#define ADC_CHANNEL_SELECT 		AD1CHS
#define ADCSSL					AD1CSSL
#define ADCON3  				AD1CON3
#define ADCON2					AD1CON2
#define ADCON1					AD1CON1
#define ADCBUF					ADC1BUF0


/*Registers Defaults*/
#define ADCSSL_VAL    				 0x0000
#define ADCON3_VAL    				 0x0000
#define ADCON2_VAL    				 0x0000
#define ADCON1_VAL    				 0x0000
#define ADC_PRIORITY					0x00
#define ADC_PORT_CONFIG_DEFAULT_VALUE 	0x0000			// Default Value of ADC Port Configuration Register.

#define ADC_PORTA_CONFIG_DEFAULT_VALUE 	0x00C0			// Default Value of ADC Port Configuration Register.
#define ADC_PORTB_CONFIG_DEFAULT_VALUE 	0xFFFF
#define ADC_PORTC_CONFIG_DEFAULT_VALUE 	0x0010
#define ADC_PORTE_CONFIG_DEFAULT_VALUE 	0x0200
#ifdef  USE_MTOUCH_AND_GRAPHICS
	#define ADC_PORTG_CONFIG_DEFAULT_VALUE 	0x0180
#else
	#define ADC_PORTG_CONFIG_DEFAULT_VALUE 	0x03C0
#endif

/*AD1CON1 register definition*/
#define ADC_MODULE_ON               0x8000 /* A/D Converter on */
#define ADC_MODULE_OFF              0x0000 /* A/D Converter off */
#define ADC_MODULE_MASK             (~ADC_MODULE_ON)  /* A/D Converter mask*/
#define ADC_IDLE_CONTINUE           0x0000 /* A/D Operate in Idle mode */
#define ADC_IDLE_STOP               0x2000 /* A/D Stop in Idle mode */
#define ADC_IDLE_MASK               (~ADC_IDLE_CONTINUE) /* A/D Idle mode mask */
#define ADC_FORMAT_SIGN_FRACT       0x0300 /* A/D data format signed fractional */
#define ADC_FORMAT_FRACT            0x0200 /* A/D data format fractional */
#define ADC_FORMAT_SIGN_INT         0x0100 /* A/D data format signed integer */
#define ADC_FORMAT_INTG             0x0000 /* A/D data format integer */
#define ADC_FORMAT_MASK             (~ADC_FORMAT_SIGN_FRACT)/* A/D format mask */
#define ADC_CLK_AUTO                0x00E0 /* Internal counter ends sampling and starts conversion (Auto convert) */
#define ADC_CLK_CTMU                0x0080 /* CTMU event ends sampling and starts conversion */
#define ADC_CLK_TMR5                0x0060 /* Timer5 compare ends sampling and starts conversion */
#define ADC_CLK_TMR3                0x0040 /* Timer3 compare ends sampling and starts conversion */
#define ADC_CLK_INT0                0x0020 /* Active transition on INT0 ends sampling and starts conversion */
#define ADC_CLK_MANUAL              0x0000 /* Clearing sample (SAMP) bit ends sampling and starts conversion */
#define ADC_CLK_MASK                (~ADC_CLK_AUTO) /* A/D clock mask */
#define ADC_AUTO_SAMPLING_ON        0x0004 /* Sampling begins immediately after last conversion */
#define ADC_AUTO_SAMPLING_OFF       0x0000 /* Sampling begins when SAMP bit is set */
#define ADC_AUTO_SAMPLING_MASK      (~ADC_AUTO_SAMPLING_ON) /* A/D auto sampling mask */
#define ADC_SAMP_ON                 0x0002 /* sample / hold amplifiers are sampling */
#define ADC_SAMP_OFF                0x0000 /* sample / hold amplifiers are holding */
#define ADC_SAMP_MASK               (~ADC_SAMP_ON) /* A/D sampling mask */

/*AD1CON2 control register definition*/
#define ADC_VREF_EXT_AVSS           0x2000 /* A/D Voltage reference configuration Vref+ external and Vref- is AVss */
#define ADC_VREF_AVDD_EXT           0x4000 /* A/D Voltage reference configuration Vref+ AVdd and Vref- external */
#define ADC_VREF_EXT_EXT            0x6000 /* A/D Voltage reference configuration both Vref+ and Vref- are external */
#define ADC_VREF_AVDD_AVSS          0x8000 /* A/D Voltage reference configuration Vref+ is AVdd and Vref- is AVss */
#define ADC_VREF_MASK               (~(ADC_VREF_AVDD_AVSS | ADC_VREF_EXT_EXT)) /* A/D Vref  mask */
#define ADC_SCAN_ON                 0x0400 /* A/D Scan Input Selections for CH0 during SAMPLE A */
#define ADC_SCAN_OFF                0x0000 /* A/D Do notScan Input Selections for CH0+ during SAMPLE A */
#define ADC_SCAN_ON_OFF_MASK        (~ADC_SCAN_ON) /* A/D scan input mask */

#define ADC_INTR_CONV             	0x0000 /* Interrupts at the completion of conversion of 2 samples */

#define ADC_ALT_BUF_ON              0x0002 /* Buffer configured as 2 8-word buffers */
#define ADC_ALT_BUF_OFF             0x0000 /* Buffer configured as 1 16-word buffer */
#define ADC_ALT_BUF_MASK            (~ADC_ALT_BUF_ON) /* A/D alternate buffer mask */
/* A/D Uses channel input selects for SAMPLE A on first sample and SAMPLE B on next sample */
#define ADC_ALT_INPUT_ON            0x0001 /* alternate between MUXA and MUXB */
/* A/D Always uses channel input selects for SAMPLE A */
#define ADC_ALT_INPUT_OFF           0x0000 /* use MUXA only */
#define ADC_ALT_MASK                (~ADC_ALT_INPUT_ON) /* A/D alternate input mask */

/*AD1CON3 register definition*/
#define ADC_CONV_CLK_INTERNAL_RC    0x8000 /* A/D internal RC clock */
#define ADC_CONV_CLK_SYSTEM         0x0000 /* Clock derived from system clock */
#define ADC_CONV_CLK_SOURCE_MASK    (~ADC_CONV_CLK_INTERNAL_RC) /* A/D conversion clock mask */

#define ADC_SAMPLE_TIME           	0x0000 /* A/D Auto Sample Time 0 Tad */
#define ADC_CONV_CLK_Tcy          	0x0000 /* A/D Conversion Clock is 1*Tcy */

/*AD1CSSL control register definition*/
#define ADC_SCAN_AN      			0x0000 /*Enable Input Scan AN0 */


#define ADC_CONFIG_ADCON1  (ADCON1_VAL | ADC_MODULE_OFF | ADC_IDLE_CONTINUE | ADC_FORMAT_INTG | ADC_CLK_MANUAL | ADC_AUTO_SAMPLING_OFF | ADC_SAMP_OFF) 
#define ADC_CONFIG_ADCON2  (ADCON2_VAL | ADC_VREF_AVDD_AVSS | ADC_SCAN_OFF | ADC_INTR_CONV | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF) 
#define ADC_CONFIG_ADCON3  (ADCON3_VAL | ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME | ADC_CONV_CLK_Tcy) 
#define ADC_CONFIG_ADCSSL  (ADCSSL_VAL | ADC_SCAN_AN)


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
#define CMP_CMCON_Ouput_Bit				CM2CONbits.COUT
#define CMP_Trigger_Select_HighBit			CM2CONbits.EVPOL1
#define CMP_Trigger_Select_LowBit			CM2CONbits.EVPOL0
#define CMP_Reference_Select_Bit				CM2CONbits.CREF
#define CMP_Channel_Select_HighBit			CM2CONbits.CCH1
#define CMP_Channel_Select_LowBit			CM2CONbits.CCH0
#define CMP_Trigger_Select_Bits				CM2CONbits.EVPOL
#define CMP_Channel_Select_Bits				CM2CONbits.CCH

/*CMSTAT register bit definition*/
#define CMP_Ouput_Bit						CMSTATbits.C2OUT

/*CMCON interrupt register bit definition*/

#define CMP_Interrupt_Flag_Bit			IFS1bits.CMIF
#define CMP_Interrupt_Enable_Bit			IEC1bits.CMIE
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
 
 #define CTMU_INT_PRI                	0x0000 /*CTMU interrupt priority is 0*/
 
 #define CTMU_INT_ENABLE               0x0008 /* Enable CTMU interrupts */
 #define CTMU_INT_DISABLE              0x0000 /* Disable CTMU interrupts */


/************************************************************************
Macro       : Set_CTMU_ENABLE_Status 
Overview    : setting or clearing CTMU Enable Module Bit 
Parameters  : ENABLE '1' or DISABLE '0'
Remarks     : None.
**************************************************************************/ 
#define Set_CTMU_ENABLE_Status(State)   			(CTMUCONbits.CTMUEN = State)

/************************************************************************
Macro       : Idle_Mode_CTMU_Operation 
Overview    : CTMU Operation in Idle 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
#define Idle_Mode_CTMU_Operation(State)   			(CTMUCONbits.CTMUSIDL = State)

/************************************************************************
Macro       : Set_CTMU_Time_Generation 
Overview    : setting or clearing CTMU TIME Generation Bit 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
#define Set_CTMU_Time_Generation(State)   			(CTMUCONbits.TGEN = State)


/************************************************************************
Macro       : Enable_Disable_CTMU_Time_Generation 
Overview    : setting or clearing CTMU TIME Generation Bit 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
#define Block_CTMU_Edge(State)   			(CTMUCONbits.EDGEN = 0)

/************************************************************************
Macro       : Enable_Disable_CTMU_Time_Generation 
Overview    : setting or clearing CTMU TIME Generation Bit 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
#define Unblock_CTMU_Edge(State)   			(CTMUCONbits.EDGEN = 1)


/************************************************************************
Macro       : Set_CTMU_Edge_Sequence 
Overview    : setting or clearing CTMU Edge Sequence Bit 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
#define Set_Edge_Sequence(State)   			(CTMUCONbits.EDGSEQEN = State)


/************************************************************************
Macro       : Enable_CTMU_CurrentDischarge 
Overview    : setting the CTMU Current Discharge  Bit 
Parameters  : None
Remarks     : None.
**************************************************************************/ 
#define Enble_CTMU_CurrentDischarge   			(CTMUCONbits.IDISSEN = 1)

/************************************************************************
Macro       : Disable_CTMU_CurrentDischarge 
Overview    : Clearing the CTMU Current Discharge  Bit 
Parameters  : None
Remarks     : None.
**************************************************************************/ 
#define Disble_CTMU_CurrentDischarge   			(CTMUCONbits.IDISSEN = 0)



/************************************************************************
Macro       : Set_CTMU_Trigger_Control 
Overview    : setting or clearing CTMU Trigger Control Bit 
Parameters  : ENABLE '1' or DISABLE '0' 
Remarks     : None.
**************************************************************************/ 
#define Set_CTMU_Trigger_Control(State)   			(CTMUCONbits.CTTRIG = State)



/************************************************************************
Macro       : Enble_CTMU_Positive_Edge2_Polarity
Overview    : By setting Edge 2 Polarity Select bit 
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Enble_CTMU_Positive_Edge2_Polarity				(CTMUCONbits.EDG2POL = 1)


/************************************************************************
Macro       : Enble_CTMU_Negative_Edge2_Polarity
Overview    : By setting Edge 2 Polarity Select bit 
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Enble_CTMU_Negative_Edge2_Polarity				(CTMUCONbits.EDG2POL = 0)


/************************************************************************
Macro       : Enble_CTMU_Positive_Edge1_Polarity
Overview    : By setting Edge 1 Polarity Select bit 
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Enble_CTMU_Positive_Edge1_Polarity				(CTMUCONbits.EDG1POL = 1)


/************************************************************************
Macro       : Enble_CTMU_Negative_Edge1_Polarity
Overview    : By setting Edge 1 Polarity Select bit 
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Enble_CTMU_Negative_Edge1_Polarity				(CTMUCONbits.EDG1POL = 0)


/************************************************************************
Macro       : CTMU_Edge1_Source_Select 
Overview    : Edge 1 Source Select bits 
Parameters  :  State
Remarks     : None.
**************************************************************************/ 
#define CTMU_Edge1_Source_Select(State)   	(CTMUCONbits.EDG1SEL = State)


/************************************************************************
Macro       : CTMU_Edge2_Source_Select 
Overview    : Edge 2 Source Select bits 
Parameters  :  TRIGGER_SOURCE_TIMER1=0,
			TRIGGER_SOURCE_OC,
			TRIGGER_SOURCE_EXTERNAL2,
			TRIGGER_SOURCE_EXTERNAL1
Remarks     : None.
**************************************************************************/ 
#define CTMU_Edge2_Source_Select(State)   	(CTMUCONbits.EDG2SEL = State)


/************************************************************************
Macro       : Enble_CTMUEdge1
Overview    : By setting edge1 status bit current source enables  
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Enble_CTMUEdge1  				(CTMUCONbits.EDG1STAT = 1)


/************************************************************************
Macro       : Enble_CTMUEdge2
Overview    : By setting edge2 status bit current source enables  
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Enble_CTMUEdge2 				(CTMUCONbits.EDG2STAT = 1)


/************************************************************************
Macro        :Disbl_CTMUEdge1
Overview    : By clearing edge1 status bit disable the current source
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Disbl_CTMUEdge1 				(CTMUCONbits.EDG1STAT = 0)


/************************************************************************
Macro       :Disbl_CTMUEdge2
Overview    : By clearing edge2 status bit disable the current source 
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Disbl_CTMUEdge2				(CTMUCONbits.EDG2STAT = 0)


/************************************************************************
Macro       : Disbl_Currentsource
Overview    : By clearing EDGSTAT bit disable the source.
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Disbl_CurrentSource   		( CTMUCONbits.EDG1STAT = 0 , CTMUCONbits.EDG2STAT = 0 )


/************************************************************************
Macro       : Enabl_Currentsource
Overview    : By setting EDGSTAT bit disable the source.
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define Enble_CurrentSource   		(CTMUCONbits.EDG1STAT = 1 , CTMUCONbits.EDG2STAT = 1 )


/************************************************************************
Macro       : CTMUEdge1_Status
Overview    : Returns the status of CTMU edge1  
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define CTMUEdge1_Status      		CTMUCONbits.EDG1STAT

/************************************************************************
Macro       : CTMUEdge2_Status
Overview    : Returns the status of CTMU edge2 
Parameters  : None 
Remarks     : None.
**************************************************************************/ 
#define CTMUEdge2_Status  	 		CTMUCONbits.EDG2STAT


/************************************************************************
Macro       : CTMU_Trim_Value 
Overview    : Sets the Trim Value for CTMU
Parameters  : Singed data Range (011111) i.e +31 to (100001) i.e -1
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


#endif //#ifdef __PIC24F__

#endif	// _MTOUCH_PIC24_CTMU_PHYSICAL_H


