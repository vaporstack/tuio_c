//
//  my_tuio_client.c
//  tuio_c
//
//  Created by vs on 12/11/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "my_tuio_client.h"

//	hacked up version of Tuio2Dump.h

#include "TUIO2/TcpReceiver.h"
#include "TUIO2/TuioClient.h"
#include "TUIO2/TuioListener.h"
#include "TUIO2/UdpReceiver.h"
#include <math.h>

using namespace TUIO2;

class Tuio2Dump : public TuioListener
{

      public:
	void tuioAdd(TuioObject *tobj);
	void tuioUpdate(TuioObject *tobj);
	void tuioRemove(TuioObject *tobj);
	void tuioRefresh(TuioTime frameTime);
	/*
	void addTuioObject(TuioObject* tobj);
	void updateTuioObject(TuioObject* tobj);
	void removeTuioObject(TuioObject* tobj);

	void addTuioCursor(TuioCursor* tcur);
	void updateTuioCursor(TuioCursor* tcur);
	void removeTuioCursor(TuioCursor* tcur);

	void addTuioBlob(TuioBlob* tblb);
	void updateTuioBlob(TuioBlob* tblb);
	void removeTuioBlob(TuioBlob* tblb);
*/
	void refresh(TuioTime frameTime);

};


void Tuio2Dump::tuioAdd(TuioObject *tobj) {
	
	if(tobj->containsNewTuioToken()) std::cout << "add tok " << tobj->getTuioToken()->getSessionID() << std::endl;
	if(tobj->containsNewTuioPointer()) std::cout << "add ptr " << tobj->getTuioPointer()->getSessionID() << std::endl;
	if(tobj->containsNewTuioBounds()) std::cout << "add bnd " << tobj->getTuioBounds()->getSessionID() << std::endl;
	if(tobj->containsNewTuioSymbol()) std::cout << "add sym " << tobj->getTuioSymbol()->getSessionID() << std::endl;
	//std::cout << "add obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << "/"<<  tobj->getTuioSourceID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle() << std::endl;
	std::cout << std::flush;
}

void Tuio2Dump::tuioUpdate(TuioObject *tobj) {
	if(tobj->containsTuioToken()) std::cout << "set tok " << tobj->getTuioToken()->getSessionID() << std::endl;
	if(tobj->containsTuioPointer()) std::cout << "set ptr " << tobj->getTuioPointer()->getSessionID() << std::endl;
	if(tobj->containsTuioBounds()) std::cout << "set bnd " << tobj->getTuioBounds()->getSessionID() << std::endl;
	if(tobj->containsTuioSymbol()) std::cout << "set sym " << tobj->getTuioSymbol()->getSessionID() << std::endl;
	//std::cout << "set obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << "/"<<  tobj->getTuioSourceID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle() << " " << tobj->getMotionSpeed() << " " << tobj->getRotationSpeed() << " " << tobj->getMotionAccel() << " " << tobj->getRotationAccel() << std::endl;
	std::cout << std::flush;
}

void Tuio2Dump::tuioRemove(TuioObject *tobj) {
	if(tobj->containsTuioToken()) std::cout << "del tok " << tobj->getSessionID() << std::endl;
	if(tobj->containsTuioPointer()) std::cout << "del ptr " << tobj->getSessionID() << std::endl;
	if(tobj->containsTuioBounds()) std::cout << "del bnd " << tobj->getSessionID() << std::endl;
	if(tobj->containsTuioSymbol()) std::cout << "del sym " << tobj->getSessionID() << std::endl;
	//std::cout << "del obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << "/"<<  tobj->getTuioSourceID() << ")" << std::endl;
	std::cout << std::flush;
}

void Tuio2Dump::tuioRefresh(TuioTime frameTime) {
	std::cout << "refresh " << frameTime.getFrameID() << " "<< frameTime.getTotalMilliseconds() << std::endl;
	std::cout << std::flush;
}

class MyTuio2Dump : public Tuio2Dump
{
public:
	MyTuio2Dump()
	{
		
	}
	~MyTuio2Dump()
	{
		
	}
	void addTuioObject(TuioObject* tobj)
	{
		
	}
	void updateTuioObject(TuioObject* tobj)
	{
		
	}
	void removeTuioObject(TuioObject* tobj)
	{
		
	}
	
	
	MyTuioClientAttrs attr;

};

static MyTuio2Dump* create_tuiodump(MyTuioClientAttrs _attr)
{
	MyTuio2Dump* td = new MyTuio2Dump();
	td->attr     = _attr;
	return td;
}

static std::string _address("localhost");
static bool	_udp  = true;
static int	 _port = 3333;
/*
void Tuio2Dump::addTuioObject(TuioObject* tobj)
{
	//std::cout << "add obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << "/" << tobj->getTuioSourceID() << ") " << tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle() << std::endl;
}

void Tuio2Dump::updateTuioObject(TuioObject* tobj)
{
	//std::cout << "set obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << "/" << tobj->getTuioSourceID() << ") " << tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle()
	//	  << " " << tobj->getMotionSpeed() << " " << tobj->getRotationSpeed() << " " << tobj->getMotionAccel() << " " << tobj->getRotationAccel() << std::endl;
}

void Tuio2Dump::removeTuioObject(TuioObject* tobj)
{
	//std::cout << "del obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << "/" << tobj->getTuioSourceID() << ")" << std::endl;
}
 

void Tuio2Dump::addTuioCursor(TuioCursor* tcur)
{
	//std::cout << "add cur " << tcur->getCursorID() << " (" << tcur->getSessionID() << "/" << tcur->getTuioSourceID() << ") " << tcur->getX() << " " << tcur->getY() << std::endl;
	
	if (!attr.cur_add)
		return;
	attr.cur_add(tcur->getCursorID(),
		     tcur->getSessionID(),
		     tcur->getTuioSourceID(),
		     tcur->getX(),
		     tcur->getY());
}

void Tuio2Dump::updateTuioCursor(TuioCursor* tcur)
{
	//std::cout << "set cur " << tcur->getCursorID() << " (" << tcur->getSessionID() << "/" << tcur->getTuioSourceID() << ") " << tcur->getX() << " " << tcur->getY()
	//	  << " " << tcur->getMotionSpeed() << " " << tcur->getMotionAccel() << " " << std::endl;
	if (!attr.cur_upd)
		return;

	attr.cur_upd(tcur->getCursorID(),
		     tcur->getSessionID(),
		     tcur->getTuioSourceID(),
		     tcur->getX(),
		     tcur->getY());
}

void Tuio2Dump::removeTuioCursor(TuioCursor* tcur)
{
	//std::cout << "del cur " << tcur->getCursorID() << " (" << tcur->getSessionID() << "/" << tcur->getTuioSourceID() << ")" << std::endl;

	if (!attr.cur_rem)
		return;
	
	attr.cur_rem(tcur->getCursorID(),
		     tcur->getSessionID(),
		     tcur->getTuioSourceID()
		);

}

void Tuio2Dump::addTuioBlob(TuioBlob* tblb)
{
	std::cout << "add blb " << tblb->getBlobID() << " (" << tblb->getSessionID() << "/" << tblb->getTuioSourceID() << ") " << tblb->getX() << " " << tblb->getY() << " " << tblb->getAngle() << " " << tblb->getWidth() << " " << tblb->getHeight() << " " << tblb->getArea() << std::endl;
}

void Tuio2Dump::updateTuioBlob(TuioBlob* tblb)
{
	std::cout << "set blb " << tblb->getBlobID() << " (" << tblb->getSessionID() << "/" << tblb->getTuioSourceID() << ") " << tblb->getX() << " " << tblb->getY() << " " << tblb->getAngle() << " " << tblb->getWidth() << " " << tblb->getHeight() << " " << tblb->getArea()
		  << " " << tblb->getMotionSpeed() << " " << tblb->getRotationSpeed() << " " << tblb->getMotionAccel() << " " << tblb->getRotationAccel() << std::endl;
}

void Tuio2Dump::removeTuioBlob(TuioBlob* tblb)
{
	std::cout << "del blb " << tblb->getBlobID() << " (" << tblb->getSessionID() << "/" << tblb->getTuioSourceID() << ")" << std::endl;
}
*/

void Tuio2Dump::refresh(TuioTime frameTime)
{
	//std::cout << "refresh " << frameTime.getTotalMilliseconds() << std::endl;
}

//		happy place

#ifdef __cplusplus
extern "C"
{
#endif
	void my_tuio_client_connect(void* wrap, bool blocking)
	{
		MyTuioClientAttrs* rec = (MyTuioClientAttrs*)wrap;

		//OscReceiver* osc_receiver = (OscReceiver*)client->receiver;
		TuioClient* client = (TuioClient*)rec->client;
		if ( blocking )
		{
			client->connect(true);
		}else{
			client->connect();
		}
		
	}
	
	void my_tuio_client_disconnect(void* wrap)
	{
		MyTuioClientAttrs* rec = (MyTuioClientAttrs*)wrap;
		
		printf("disconnecting client\n");
		TuioClient* client = (TuioClient*)rec->client;
		
		
		Tuio2Dump* dump = (Tuio2Dump*) rec->dump;
		dump->refresh(1);
		
		if ( client->isConnected())
		{
			client->disconnect();
			//printf("not connected, can't disconnect\n");
			//return;
		}
		
		OscReceiver* receiver = (OscReceiver*)rec->receiver;
		printf("disconnecting receiver\n");

		if ( receiver->isConnected() )
		{
			receiver->disconnect();
		}
		
	}
	void my_tuio_client_update(void* wrap)
	{
	}

	void* my_tuio_client_create(MyTuioClientAttrs attr, unsigned int port)
	{
		size_t			  sz  = sizeof(MyTuioClientAttrs);
		struct MyTuioClientAttrs* rec = (MyTuioClientAttrs*)malloc(sz);

		OscReceiver* osc_receiver;
		//if (_udp)
		osc_receiver = new UdpReceiver(_port);
		//else {
		//	if (_address=="incoming") osc_receiver = new TcpReceiver(_port);
		//	else osc_receiver = new TcpReceiver(_address.c_str(), _port);
		//}
		Tuio2Dump* dump = create_tuiodump(attr);

		TuioClient* client = new TuioClient(osc_receiver);
		client->addTuioListener(dump);
		//client->connect();
		
		rec->client = client;
		rec->receiver = osc_receiver;
		rec->dump     = dump;
		return rec;
	}

	void my_tuio_client_destroy(void* wrap)
	{
		MyTuioClientAttrs* rec = (MyTuioClientAttrs*)wrap;

		
		OscReceiver* osc_receiver = (OscReceiver*)rec->receiver;
		Tuio2Dump*    dump	 = (Tuio2Dump*)rec->dump;
		TuioClient* client = (TuioClient*)rec->client;
		
		delete osc_receiver;
		delete dump;
		delete client;
		free(rec);
	}

#ifdef __cplusplus
}
#endif
