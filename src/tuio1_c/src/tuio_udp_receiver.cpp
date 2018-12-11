//
//  tuio_udp_receiver.c
//  tuio_c
//
//  Created by vs on 12/11/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "tuio_udp_receiver.h"


#include "TUIO/UdpReceiver.h"
#include <stdlib.h>

//	Unrestricted c++ land

TUIO::UdpReceiver* create_recv(unsigned int port)
{
	TUIO::UdpReceiver* recv = new TUIO::UdpReceiver(port);
	
	return recv;

}



#ifdef __cplusplus
extern "C" {
#endif
	
void* tuio_udp_receiver_create(unsigned int port)
{
	TUIO::UdpReceiver* recv = create_recv(port);
	
	recv->connect();
	
	void* wrap = recv;
	
	
	//TUIO::UdpReceiver myServer();
	
	return wrap;
}

void tuio_udp_receiver_destroy(void* wrap)
{
	TUIO::UdpReceiver* recv = (TUIO::UdpReceiver*) wrap;
	if(recv->isConnected())
	{
		printf("Disconnecting.\n");
		recv->disconnect();
	}else{
		printf("Wasn't connected.\n");
	}
}


#ifdef __cplusplus
}
#endif
