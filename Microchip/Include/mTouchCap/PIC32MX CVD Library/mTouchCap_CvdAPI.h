/**************************************************************************************

* FileName:        mTouchCap_CvdAPI.h
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
BDB         26-Jun-2008 Initial release
NMS/NK		10-Feb-2009 Folder/Files restructuring
NK			24-Apr-2009 Porting for 18F46J50 Eval Board
MC          22-Ian-2009 Porting for PIC32MX795F512H

*************************************************************************************/
#ifndef __MTOUCHCAP_CVDAPI_H     
#define __MTOUCHCAP_CVDAPI_H  

//////////////////////////////////////////////////////////////////////
// FILE INCLUDES
//////////////////////////////////////////////////////////////////////
#include	"config.h"	
#include 	"GenericTypeDefs.h"			


//////////////////////////////////////////////////////////////////////
// CVD TECHNIQUE CALIBRATION DEFINITIONS
//////////////////////////////////////////////////////////////////////

#define MATRIX_SINGLE_KEY_CH  2		// 2 channels are multiplexed to form a single Matrix key
#define FOUR_CH_SLIDER		  4		// 4 channels are used in a 4 channel slider
#define TWO_CH_SLIDER		  2		// 2 channels are used in a 2 channel slider

//////////////////////////////////////////////////////////////////////
// END
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
// ENUMS, TYPEDEFS
//////////////////////////////////////////////////////////////////////

typedef struct{
	
	          	BYTE Channel_Num;                              // Channel Used by the Directkey
				WORD TripValue;                  		// Trip value for each channel
				WORD hystValue;	 	  					 // Hystersis value 
		        BYTE FilterType;                          //  Stores Filter for each channel
		        BYTE DecodeMethod;                         //  Decode Method for each Channel
	
}DirectKey;

// Structure which stores the members associated with the Matrix key.

typedef struct{
	
	          	BYTE Channel_Num[MATRIX_SINGLE_KEY_CH];               // Channel Used by the Matrixkey
				WORD TripValue;                 	// Trip value for each key( includes 2 channels)
				WORD hystValue;	 	  				// Hystersis value for each key( includes 2 channels)
		        BYTE FilterType;                //  Stores Filter for each key( includes 2 channels)
		        BYTE DecodeMethod;              //  Decode Method for each key( includes 2 channels)
	
}MatrixKey;

// Structure which stores the members associated with the 2 channel sliders.
typedef struct{
	
	          	BYTE Channel_Num[TWO_CH_SLIDER];               // Channel sUsed by the Sliders
				WORD TripValue;                 	// Trip value for each key( includes 2 channels)
				WORD hystValue;	 	  				// Hystersis value for each key( includes 2 channels)
		        BYTE FilterType;                //  Stores Filter for each key( includes 2 channels)
		        BYTE DecodeMethod;              //  Decode Method for each key( includes 2 channels)
	
}Slider2Ch;

// Structure which stores the members associated with the 4 channel sliders.

typedef struct{
	
	          	BYTE Channel_Num[FOUR_CH_SLIDER];               // Channel sUsed by the Sliders
				WORD TripValue;                 	// Trip value for each key( includes 2 channels)
				WORD hystValue;	 	  				// Hystersis value for each key( includes 2 channels)
		        BYTE FilterType;                //  Stores Filter for each key( includes 2 channels)
		        BYTE DecodeMethod;              //  Decode Method for each key( includes 2 channels)
	
}Slider4Ch;

enum
{
	RELEASE=0,
	PRESS
};

enum
{
	DISABLE=0,
	ENABLE
};

enum
{
	OUTPUT=0,
	INPUT
};




//////////////////////////////////////////////////////////////////////
// FUNCTION PROTOTYPES
//////////////////////////////////////////////////////////////////////


void mTouchCap_Init(void);
void LoadChannelNumber (BYTE Channel_Number_Passed);
void mTouchCapAPI_SetUpCVD_Default(WORD ChannelNumber);
BYTE mTouchCapAPI_getChannelTouchStatus(WORD ChIndex, BYTE Decode_Method);
BYTE mTouchCapAPI_SetUpChannelDirectKey(DirectKey *Button,BYTE Channel_number, WORD Trip_Value, WORD Decode_Method, WORD Filter_Method);
BYTE mTouchCapAPI_GetStatusDirectButton (DirectKey *Button);
BYTE mTouchCapAPI_SetUpChannelMatrixKey(MatrixKey *Button,BYTE Row_Channel_Number,BYTE Col_Channel_Number, WORD Trip_Value, WORD Decode_Method, WORD Filter_Method);
BYTE mTouchCapAPI_GetStatusMatrixButton (MatrixKey *Button);
BYTE mTouchCapAPI_SetUpChannelSlider2Ch(Slider2Ch *Slider, BYTE Slider_Channel1_Number,BYTE Slider_Channel2_Number, WORD Trip_Value, BYTE Decode_Method, BYTE Filter_Method);
SHORT mTouchCapAPI_GetStatusSlider2Ch (Slider2Ch *Slider);
BYTE mTouchCapAPI_SetUpChannelSlider4Ch(Slider4Ch *Slider, BYTE Slider_Channel1_Number,BYTE Slider_Channel2_Number, BYTE Slider_Channel3_Number,BYTE Slider_Channel4_Number,WORD Trip_Value, BYTE Decode_Method, BYTE Filter_Method);
SHORT mTouchCapAPI_GetStatusSlider4Ch (Slider4Ch *Slider);



#endif    // end of #ifndef __MTOUCHCAP_CVDAPI_H 
