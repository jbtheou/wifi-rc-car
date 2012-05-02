

/********************************************************************
 * File    :       UDP_server.c
 *
 * Overview:       A simple UDP server to communicate
 *                 with PC
 *
 * Auteur               Date         Commentaire      E-Mail
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Théou Jean-Baptiste  10/05/11     Initial version  jbtheou@gmail.com
 *******************************************************************/

#include "main.h"


extern NODE_INFO remoteNode;

/*****************************************************************************
  Function:
	void UDPServer_CMUcam(void)
  Summary:
	Implements a simple UDP Server (CMUcam communication).

  Description:
        Based on Microchip exemple available on M.A.L

  Precondition:
	UDP is initialized.

  Parameters:
	None

  Returns:
  	None
  ***************************************************************************/

void UDPServer_CMUcam(void)
{
	static enum {
		UDP_REQUEST_HOME = 0,
		UDP_REQUEST_LISTEN,
		UDP_REQUEST_RECEIVED
	} UDPRequestSM = UDP_REQUEST_HOME;

        char buffer[6];

        static UDP_SOCKET	MySocket;
        BYTE                    i[MAX_COMMAND_SIZE];
        BYTE                    size;
        BYTE *                  command;
	switch(UDPRequestSM)
	{
            case UDP_REQUEST_HOME :
			// Open a UDP socket for inbound and outbound transmission
			// Since we expect to only receive broadcast packets and
			// only send unicast packets directly to the node we last
			// received from, the remote NodeInfo parameter can be anything
			MySocket = UDPOpen(SERVER_PORT_CMUCAM, NULL, SERVER_PORT_CMUCAM);

			if(MySocket == INVALID_UDP_SOCKET)
				return;
			else
				UDPRequestSM++;
			break;

		case UDP_REQUEST_LISTEN :
                        // Do nothing if no data is waiting
			if(!UDPIsGetReady(MySocket))
				return;

			// Receive the command
			size = UDPGetArray((BYTE *)i,MAX_COMMAND_SIZE);
                        // Alloc command variable
                      
                        /*
                         * (!!! You must allocate an heap space on C32 linker option !!!)
                         */

                        command = (BYTE *)malloc(size*sizeof(BYTE));
                        // Define command variable
                        strncpy(command,i,size);
                        // Send command to CMUcam
                            
                        putsUART1(command);
                        free(command);
                        UDPDiscard();

                        // No break, we must continue without re-loop
                       
			// Change the destination to the unicast address of the last received packet
                        memcpy((void*)&UDPSocketInfo[MySocket].remoteNode, (const void*)&remoteNode, sizeof(remoteNode));

		case UDP_REQUEST_RECEIVED:
			if(!UDPIsPutReady(MySocket))
				return;
                        xSemaphoreTake(xSemaphoreCMUcamTransmissionEnable,5000);
                        {
                            sprintf(buffer,"%d",count);
                            UDPPutArray((BYTE *)buffer,6);
                            UDPFlush();
                            while(!UDPIsPutReady(MySocket));
                            // We need to split the data, because of UDP packet size limit
                            Large_UDP_Packet(count,MySocket);
                        }
                        // Just if we cannot detect the end of frame
                        count = 0;
			/* Not useful here (No break before and no ++ on the SM)
                         * Just to be clear */
                        UDPRequestSM = UDP_REQUEST_LISTEN;
                        EnableIntU1RX;
                        break;

	}
}



/*****************************************************************************
  Function:
	void UDPServer_Cmd(void)
  Summary:
	Implements a simple UDP Server (Control communication without accelerometre).

  Description:
        Based on Microchip exemple available on M.A.L

  Precondition:
	UDP is initialized.

  Parameters:
	None

  Returns:
  	None
  ***************************************************************************/

void UDPServer_Cmd(void)
{
	static enum {
		UDP_REQUEST_HOME = 0,
		UDP_REQUEST_LISTEN,
		UDP_REQUEST_RECEIVED
	} UDPRequestSM = UDP_REQUEST_HOME;

        char buffer[20];
        static UDP_SOCKET	MySocket;
        BYTE                    i[MAX_COMMAND_SIZE];
        BYTE                    size;
        CMD_CAR                 UDP_frame;
	switch(UDPRequestSM)
	{
            case UDP_REQUEST_HOME :
			// Open a UDP socket for inbound and outbound transmission
			// Since we expect to only receive broadcast packets and
			// only send unicast packets directly to the node we last
			// received from, the remote NodeInfo parameter can be anything
			MySocket = UDPOpen(SERVER_PORT_CMD, NULL, SERVER_PORT_CMD);

			if(MySocket == INVALID_UDP_SOCKET)
				return;
			else
				UDPRequestSM++;
			break;

		case UDP_REQUEST_LISTEN :
                        // Do nothing if no data is waiting
			if(!UDPIsGetReady(MySocket))
                        {
                           return;
                        }
				

			// Receive the command
			size = UDPGetArray((BYTE *)i,MAX_COMMAND_SIZE);
                        /* Trame from UDP
                         * Bytes | Bytes | etc
                         * 
                         */

                        UDP_frame.for_back   =i[0];
                        UDP_frame.speed_up   =i[1];
                        UDP_frame.speed_down =i[2];
                        UDP_frame.dir_up     =i[3];
                        UDP_frame.dir_down   =i[4];
                        
                        Update_CMD(UDP_frame);
                        UDPDiscard();

                        // No break, we must continue without re-loop

			// Change the destination to the unicast address of the last received packet
                        memcpy((void*)&UDPSocketInfo[MySocket].remoteNode, (const void*)&remoteNode, sizeof(remoteNode));

		case UDP_REQUEST_RECEIVED:
			if(!UDPIsPutReady(MySocket))
				return;
                        sprintf(buffer,"V : %d, D : %d",Vitesse, ConsDir);
                        UDPPutArray((BYTE *)buffer,20);
                        UDPFlush();
                        UDPRequestSM = UDP_REQUEST_LISTEN;
                        break;

	}
}

/*****************************************************************************
  Function:
	void UDPServer_Cmd_Acc(void)
  Summary:
	Implements a simple UDP Server (Control communication with accelerometer).

  Description:
        Based on Microchip exemple available on M.A.L

  Precondition:
	UDP is initialized.

  Parameters:
	None

  Returns:
  	None
  ***************************************************************************/

void UDPServer_Cmd_Acc(void)
{
	static enum {
		UDP_REQUEST_HOME = 0,
		UDP_REQUEST_LISTEN,
		UDP_REQUEST_RECEIVED
	} UDPRequestSM = UDP_REQUEST_HOME;

        char buffer[20];
        static UDP_SOCKET	MySocket;
        BYTE                    i[MAX_COMMAND_SIZE];
        BYTE                    size;
        CMD_CAR_ACC             UDP_frame;
	switch(UDPRequestSM)
	{
            case UDP_REQUEST_HOME :
			// Open a UDP socket for inbound and outbound transmission
			// Since we expect to only receive broadcast packets and
			// only send unicast packets directly to the node we last
			// received from, the remote NodeInfo parameter can be anything
			MySocket = UDPOpen(SERVER_PORT_CMD_ACC, NULL, SERVER_PORT_CMD_ACC);

			if(MySocket == INVALID_UDP_SOCKET)
                        {
                            return;
                        }
			else
				UDPRequestSM++;
			break;

		case UDP_REQUEST_LISTEN :
                        // Do nothing if no data is waiting
			if(!UDPIsGetReady(MySocket))
                        {
                           return;
                        }

			// Receive the command
			size = UDPGetArray((BYTE *)i,MAX_COMMAND_SIZE);
                        /* Trame from UDP
                         * Bytes | Bytes | etc
                         *
                         */
                        UDP_frame.active    =i[0];
                        UDP_frame.fb        =i[1];
                        UDP_frame.speed     =i[2];
                        UDP_frame.signe     =i[3];
                        UDP_frame.dir       =i[4];
                        
                        Update_CMD_Acc(UDP_frame);
                        UDPDiscard();

                        // No break, we must continue without re-loop

			// Change the destination to the unicast address of the last received packet
                        memcpy((void*)&UDPSocketInfo[MySocket].remoteNode, (const void*)&remoteNode, sizeof(remoteNode));


		case UDP_REQUEST_RECEIVED:
			if(!UDPIsPutReady(MySocket))
				return;
                        sprintf(buffer,"V : %d, D : %d",Vitesse, ConsDir);
                        UDPPutArray((BYTE *)buffer,20);
                        UDPFlush();
                        UDPRequestSM = UDP_REQUEST_LISTEN;
                        break;

	}
}

/*****************************************************************************
  Function:
	void Update_CMD_Acc(CMD_CAR_ACC car_info)
  Summary:
	Implements a simple UDP Server (Control communication with accelerometer).

  Description:
        Based on Microchip exemple available on M.A.L

  Precondition:
	UDP is initialized.

  Parameters:
	None

  Returns:
  	None
  ***************************************************************************/

void Update_CMD_Acc(CMD_CAR_ACC car_info)
{
    float div=1;
    if(car_info.active != 0){

                /* Mise à jour sens d'avancement (avant/arrière) */
                if(car_info.fb == 1){
                    PORTClearBits(BROCHE_DIR_VITESSE);
                }
                else if(car_info.fb == 0){
                    PORTSetBits(BROCHE_DIR_VITESSE);
                }

                /* Gestion de la consigne de courant (couple -> vitesse) */
                /* Protection Vitesse */
                xSemaphoreTake(xSemaphoreVitesse,portMAX_DELAY);
                {
                    Vitesse = car_info.speed*10;

                    if(Vitesse > 100)
                    {
                        Vitesse = 100;
                    }
                    if(Vitesse < 0)
                    {
                        Vitesse = 0;
                    }
                }
                xSemaphoreGive(xSemaphoreVitesse);

                /* Gestion de la consigne de direction */

                /* Protection ConsDir */
                xSemaphoreTake(xSemaphoreConsDir,portMAX_DELAY);
                {
                    if(car_info.dir > 5)
                        car_info.dir = 5;
                    div = car_info.dir/10.0;
                    if(car_info.signe == 0){
                        ConsDir = ZERO_BUTE+(short)((HAUT_BUTE-ZERO_BUTE)*div);
                    }
                    else if(car_info.signe  == 1){
                        ConsDir = ZERO_BUTE-(short)((ZERO_BUTE-BAS_BUTE)*div);
                    }
                    if(ConsDir > HAUT_BUTE)
                    {
                        ConsDir = HAUT_BUTE-10;
                    }
                    if(ConsDir < BAS_BUTE)
                    {
                        ConsDir = BAS_BUTE+10;
                    }
                }
                xSemaphoreGive(xSemaphoreConsDir);
            }
            /* Fin Action de l'utilisateur (avant ou arrière) */
            else{
            /* Protection Vitesse*/
                xSemaphoreTake(xSemaphoreVitesse,portMAX_DELAY);
                {
                    Vitesse = 0;
                }
                xSemaphoreGive(xSemaphoreVitesse);
                /* Protection ConsDir */
                xSemaphoreTake(xSemaphoreConsDir,portMAX_DELAY);
                {
                    ConsDir = ZERO_BUTE;
                }
                xSemaphoreGive(xSemaphoreConsDir);
            }
}

void Update_CMD(CMD_CAR car_info)
{
    if(car_info.for_back == FORWARD || car_info.for_back == BACKWARD){

                /* Mise à jour sens d'avancement (avant/arrière) */
                if(car_info.for_back == FORWARD){
                    PORTClearBits(BROCHE_DIR_VITESSE);
                }
                else if(car_info.for_back == BACKWARD){
                    PORTSetBits(BROCHE_DIR_VITESSE);
                }

                /* Gestion de la consigne de courant (couple -> vitesse) */
                /* Protection Vitesse */
                xSemaphoreTake(xSemaphoreVitesse,portMAX_DELAY);
                {
                    if(car_info.speed_up == 1){
                        Vitesse += increment_vitesse;
                    }
                    else if(car_info.speed_down == 1){
                        Vitesse -= increment_vitesse;
                    }
                    if(Vitesse > 100)
                    {
                        Vitesse = 100;
                    }
                    else if( Vitesse<0)
                    {
                        Vitesse =0;
                    }
                }
                xSemaphoreGive(xSemaphoreVitesse);

                /* Gestion de la consigne de direction */

                /* Protection ConsDir */
                xSemaphoreTake(xSemaphoreConsDir,portMAX_DELAY);
                {
                    if(car_info.dir_up == 1){
                        ConsDir += increment_direction;
                    }
                    else if(car_info.dir_down == 1){
                        ConsDir -= increment_direction;
                    }
                    if(ConsDir > HAUT_BUTE)
                    {
                        ConsDir = HAUT_BUTE-10;
                    }
                    if(ConsDir < BAS_BUTE)
                    {
                        ConsDir = BAS_BUTE+10;
                    }
                }
                xSemaphoreGive(xSemaphoreConsDir);
            }
            /* Fin Action de l'utilisateur (avant ou arrière) */
            else{
            /* Protection Vitesse*/
                xSemaphoreTake(xSemaphoreVitesse,portMAX_DELAY);
                {
                    Vitesse = 0;
                }
                xSemaphoreGive(xSemaphoreVitesse);
                /* Protection ConsDir */
                xSemaphoreTake(xSemaphoreConsDir,portMAX_DELAY);
                {
                    ConsDir = ZERO_BUTE;
                }
                xSemaphoreGive(xSemaphoreConsDir);
            }
}

void Large_UDP_Packet(int value, UDP_SOCKET MySocket)
{
    int number_packet =0;
    int final_length  =0;
    int ind;
    int cnt=0;
    int j=0;

    // We testing if buffer need to be split
    if(value >= UDP_LIMIT_SIZE)
    {
        // The number of packet who need to send
        number_packet = (int)value/UDP_LIMIT_SIZE;
        // The length of the last packet
        final_length  = value%UDP_LIMIT_SIZE;
        // We send the first packet
        UDPPutArray((BYTE *)rxbuffer,UDP_LIMIT_SIZE);
        UDPFlush();
        /* Testing if we need to send more than two packets
         * (One of UDP_LIMIT_SIZE and an other to final_length)
         */
        if(number_packet > 1)
        {
            for(cnt=1;cnt<number_packet;cnt++)
            {
                /* Here, we moving data inside the bufffer
                 * to not use an other buffer (save space), and sending
                 * the data, until we need to send the last packet
                 */
                for(j=0;j<UDP_LIMIT_SIZE;j++)
                {
                    rxbuffer[j] = rxbuffer[cnt*UDP_LIMIT_SIZE+j];
                }
                // We waiting for hardware buffer
                while(!UDPIsPutReady(MySocket));
                UDPPutArray((BYTE *)rxbuffer,UDP_LIMIT_SIZE);
                UDPFlush();
            }
            // We sending the last packet
            for(ind=0;ind<final_length;ind++)
            {
                rxbuffer[ind] = rxbuffer[cnt*UDP_LIMIT_SIZE+j+1+ind];
            }
            while(!UDPIsPutReady(MySocket));
            UDPPutArray((BYTE *)rxbuffer,final_length);
            UDPFlush();
        }
        else
        {
            for(ind=0;ind<final_length;ind++)
            {
                rxbuffer[ind] = rxbuffer[UDP_LIMIT_SIZE+ind];
            }
            while(!UDPIsPutReady(MySocket));
            UDPPutArray((BYTE *)rxbuffer,final_length);
            UDPFlush();
        }
    }
    else
    {
        UDPPutArray((BYTE *)rxbuffer,value);
        UDPFlush();
    }
}