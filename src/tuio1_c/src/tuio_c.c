//
//  tuio_c.c
//  tuio_c
//
//  Created by vs on 12/11/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "tuio_c.h"

static void* foo = NULL;
void tuio_c_init(void)
{
	MyTuioClientAttrs attr;
	attr.cur_add = NULL;
	attr.cur_upd = NULL;
	attr.cur_rem = NULL;
	
	foo = my_tuio_client_create(attr, 3333);
}

void tuio_c_deinit(void)
{
	my_tuio_client_destroy(foo);
	
}
