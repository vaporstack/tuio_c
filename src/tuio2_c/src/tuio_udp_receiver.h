//
//  tuio_udp_receiver.h
//  tuio_c
//
//  Created by vs on 12/11/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef tuio_udp_receiver_h
#define tuio_udp_receiver_h

#ifdef __cplusplus
extern "C" {
#endif
	/*
	typedef struct TuioUdpWrapper
	{
		void* data;
	}TuioUdpWrapper;
	*/
	
	void* tuio_udp_receiver_create(unsigned int port);
	void  tuio_udp_receiver_destroy(void* wrap);

#ifdef __cplusplus
}
#endif


#endif /* tuio_udp_receiver_h */
