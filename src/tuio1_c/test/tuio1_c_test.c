//
//  tuio1_c_test.c
//  tuio_c
//
//  Created by vs on 12/11/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include <stdio.h>

#include "../src/tuio_c.h"
#include <unistd.h>

/*

 tcur->getCursorID()
 tcur->getSessionID()
 tcur->getTuioSourceID()
 tcur->getX()
 tcur->getY()

*/

static void cursor_add_cb(unsigned int cursor_id, long session_id, unsigned int source_id, double x, double y)
{
	printf("[add] %d %ld %d %f %f\n", cursor_id, session_id, source_id, x, y);
}

static void cursor_upd_cb(unsigned int cursor_id, long session_id, unsigned int source_id, double x, double y)
{
	printf("[upd] %d %ld %d %f %f\n", cursor_id, session_id, source_id, x, y);
}

static void cursor_rem_cb(unsigned int cursor_id, long session_id, unsigned int source_id)
{
	printf("[rem] %d %ld %d\n", cursor_id, session_id, source_id);

	
}

int main(int argc, char** argv)
{
	MyTuioClientAttrs attr;

	attr.cur_upd = cursor_upd_cb;
	attr.cur_add = cursor_add_cb;
	attr.cur_rem = cursor_rem_cb;
	void* wrap = my_tuio_client_create(attr, 3333);

	sleep(10);

	my_tuio_client_destroy(wrap);
	/*
	void* wrap = tuio_udp_receiver_create(3333);


	tuio_udp_receiver_destroy(wrap);
	*/
	return 0;
};
