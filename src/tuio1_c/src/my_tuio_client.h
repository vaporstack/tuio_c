//
//  my_tuio_client.h
//  tuio_c
//
//  Created by vs on 12/11/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef my_tuio_client_h
#define my_tuio_client_h


#ifdef __cplusplus
extern "C" {
#endif
	
	typedef void (*my_tuio_cursor_callback)(unsigned int cursor_id, long session_id, unsigned int source_id, double x, double y);
	typedef void (*my_tuio_cursor_rm_callback)(unsigned int cursor_id, long session_id, unsigned int source_id);

	 typedef struct MyTuioClientAttrs
	 {
		 my_tuio_cursor_callback cur_add;
		 my_tuio_cursor_callback cur_upd;
		 my_tuio_cursor_rm_callback cur_rem;
		 void* receiver;
		 void* dump;
		 
	 } MyTuioClientAttrs;
	
	
	void* my_tuio_client_create(MyTuioClientAttrs attr, unsigned int port);
	void  my_tuio_client_destroy(void* wrap);
	
#ifdef __cplusplus
}
#endif





#endif /* my_tuio_client_h */
