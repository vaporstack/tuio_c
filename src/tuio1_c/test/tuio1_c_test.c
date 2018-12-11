//
//  tuio1_c_test.c
//  tuio_c
//
//  Created by vs on 12/11/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include <stdio.h>

#include "../src/tuio_c.h"

int main(int argc, char** argv)
{
	
	void* wrap = tuio_udp_receiver_create(3333);
	
	
	tuio_udp_receiver_destroy(wrap);
	
	return 0;
};
