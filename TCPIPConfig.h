/*********************************************************************
 *
 *	Microchip TCP/IP Stack Demo Application Configuration Header Stub
 *
 *********************************************************************
 * FileName:        TCPIPConfig.h
 * Dependencies:    Microchip TCP/IP Stack
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.10 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.34 or higher
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
 * Howard Schlunder		09/21/2010	Converted to a stub
 ********************************************************************/
#ifndef TCPIPCONFIG_STUB_H
#define TCPIPCONFIG_STUB_H

// These definitions are set in the MPLAB Project settings.  If you are starting
// a new project, you should start by modifying one of the pre-existing .mcp 
// files.  To modify the macro used, in MPLAB IDE, click on Project -> Build 
// Options... -> Project -> MPLAB XXX C Compiler -> Preprocessor Macros -> 
// Add.... Note that you may also have to add this macro to the assembler 
// (MPLAB XXX Assembler tab).
#if		defined(PICDEMNET2_INTERNAL_ETHERNET) || \
		defined(PICDEMNET2_ONBOARD_ENC28J60) || \
		defined(PICDEMNET2_ENC28J60) || \
		defined(PIC18_EXPLORER_ENC28J60) || \
		defined(EXPLORER_16_ENC28J60)
			#if defined(TCP_200_PERFORMANCE)
				#include "Alternative Configurations/TCPIPConfig ENC28J60 ETH97J60 TCP_200_PERFORMANCE.h"
			#elif defined(TCP_2000_PERFORMANCE)
				#include "Alternative Configurations/TCPIPConfig ENC28J60 ETH97J60 TCP_2000_PERFORMANCE.h"
			#elif defined(UDP_PERFORMANCE)
				#include "Alternative Configurations/TCPIPConfig ENC28J60 ETH97J60 UDP_PERFORMANCE.h"
			#else
				#include "Alternative Configurations/TCPIPConfig ENC28J60 ETH97J60.h"
			#endif
#elif	defined(PICDEMNET2_ENC624J600) || \
		defined(PIC18_EXPLORER_ENC624J600) || \
		defined(EXPLORER_16_ENC624J600)
			#if defined(TCP_200_PERFORMANCE)
				#include "Alternative Configurations/TCPIPConfig ENCX24J600 TCP_200_PERFORMANCE.h"
			#elif defined(TCP_2000_PERFORMANCE)
				#include "Alternative Configurations/TCPIPConfig ENCX24J600 TCP_2000_PERFORMANCE.h"
			#elif defined(TCP_8000_PERFORMANCE)
				#include "Alternative Configurations/TCPIPConfig ENCX24J600 TCP_8000_PERFORMANCE.h"
			#elif defined(UDP_PERFORMANCE)
				#include "Alternative Configurations/TCPIPConfig ENCX24J600 UDP_PERFORMANCE.h"
			#else
				#include "Alternative Configurations/TCPIPConfig ENCX24J600.h"
			#endif
#elif	defined(PICDEMNET2_MRF24WB0M) || \
		defined(PIC18_EXPLORER_MRF24WB0M) || \
		defined(EXPLORER_16_MRF24WB0M)
			#if defined(TCP_200_PERFORMANCE)
				#include "Alternative Configurations/TCPIPConfig MRF24WB0M TCP_200_PERFORMANCE.h"
			#elif defined(TCP_2000_PERFORMANCE)
				#include "Alternative Configurations/TCPIPConfig MRF24WB0M TCP_2000_PERFORMANCE.h"
			#elif defined(TCP_8000_PERFORMANCE)
				#include "Alternative Configurations/TCPIPConfig MRF24WB0M TCP_8000_PERFORMANCE.h"
			#elif defined(UDP_PERFORMANCE)
				#include "Alternative Configurations/TCPIPConfig MRF24WB0M UDP_PERFORMANCE.h"
			#else
				#include "Hardware/TCPIPConfig MRF24WB0M.h"
			#endif
#elif	defined(PIC24FJ256DA210_DEV_BOARD_ENC28J60)
			#include "Alternative Configurations/TCPIPConfig ENC28J60 PIC24FJ256DA210_DEV_BOARD.h"
#elif	defined(PIC24FJ256DA210_DEV_BOARD_ENC624J600)
			#include "Alternative Configurations/TCPIPConfig ENCX24J600 PIC24FJ256DA210_DEV_BOARD.h"
#elif	defined(PIC24FJ256DA210_DEV_BOARD_MRF24WB0M)
			#include "Alternative Configurations/TCPIPConfig MRF24WB0M PIC24FJ256DA210_DEV_BOARD.h"
#elif	defined(PIC32_ENET_SK_DM320004_INTERNAL_ETHERNET)
			#if defined(TCP_200_PERFORMANCE)
				#include "Alternative Configurations/TCPIPConfig PIC32 Internal Ethernet TCP_200_PERFORMANCE.h"
			#elif defined(TCP_2000_PERFORMANCE)
				#include "Alternative Configurations/TCPIPConfig PIC32 Internal Ethernet TCP_2000_PERFORMANCE.h"
			#elif defined(TCP_8000_PERFORMANCE)
				#include "Alternative Configurations/TCPIPConfig PIC32 Internal Ethernet TCP_8000_PERFORMANCE.h"
			#elif defined(UDP_PERFORMANCE)
				#include "Alternative Configurations/TCPIPConfig PIC32 Internal Ethernet UDP_PERFORMANCE.h"
			#else
				#include "Alternative Configurations/TCPIPConfig PIC32 Internal Ethernet.h"
			#endif
#elif	defined(PIC32_GP_SK_DM320001_ENC28J60) || \
		defined(PIC32_USB_DM320003_1_ENC28J60) || \
		defined(PIC32_USB_SK_DM320003_2_ENC28J60)
			#include "Alternative Configurations/TCPIPConfig ENC28J60 PIC32 Starter Kits.h"
#elif	defined(PIC32_GP_SK_DM320001_ENC624J600) || \
		defined(PIC32_USB_DM320003_1_ENC624J600) || \
		defined(PIC32_USB_SK_DM320003_2_ENC624J600)
			#include "Alternative Configurations/TCPIPConfig ENCX24J600 PIC32 Starter Kits.h"
#elif	defined(PIC32_GP_SK_DM320001_MRF24WB0M) || \
		defined(PIC32_USB_DM320003_1_MRF24WB0M) || \
		defined(PIC32_USB_SK_DM320003_2_MRF24WB0M)
			#include "Alternative Configurations/TCPIPConfig MRF24WB0M PIC32 Starter Kits.h"
#else
			#error Missing project macro definition to select proper TCPIPConfig.h
#endif


#endif
