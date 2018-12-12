//
//  my_tuio_client.c
//  tuio_c
//
//  Created by vs on 12/11/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "my_tuio_client.h"

//	hacked up version of TuioDump.h

#include "TUIO/TcpReceiver.h"
#include "TUIO/TuioClient.h"
#include "TUIO/TuioListener.h"
#include "TUIO/UdpReceiver.h"
#include <math.h>

using namespace TUIO;

class TuioDump : public TuioListener
{

      public:
	void addTuioObject(TuioObject* tobj);
	void updateTuioObject(TuioObject* tobj);
	void removeTuioObject(TuioObject* tobj);

	void addTuioCursor(TuioCursor* tcur);
	void updateTuioCursor(TuioCursor* tcur);
	void removeTuioCursor(TuioCursor* tcur);

	void addTuioBlob(TuioBlob* tblb);
	void updateTuioBlob(TuioBlob* tblb);
	void removeTuioBlob(TuioBlob* tblb);

	void refresh(TuioTime frameTime);

	MyTuioClientAttrs attr;
};

static TuioDump* create_tuiodump(MyTuioClientAttrs _attr)
{
	TuioDump* td = new TuioDump();
	td->attr     = _attr;
	return td;
}

static std::string _address("localhost");
static bool	_udp  = true;
static int	 _port = 3333;

void TuioDump::addTuioObject(TuioObject* tobj)
{
	std::cout << "add obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << "/" << tobj->getTuioSourceID() << ") " << tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle() << std::endl;
}

void TuioDump::updateTuioObject(TuioObject* tobj)
{
	std::cout << "set obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << "/" << tobj->getTuioSourceID() << ") " << tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle()
		  << " " << tobj->getMotionSpeed() << " " << tobj->getRotationSpeed() << " " << tobj->getMotionAccel() << " " << tobj->getRotationAccel() << std::endl;
}

void TuioDump::removeTuioObject(TuioObject* tobj)
{
	std::cout << "del obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << "/" << tobj->getTuioSourceID() << ")" << std::endl;
}

void TuioDump::addTuioCursor(TuioCursor* tcur)
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

void TuioDump::updateTuioCursor(TuioCursor* tcur)
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

void TuioDump::removeTuioCursor(TuioCursor* tcur)
{
	//std::cout << "del cur " << tcur->getCursorID() << " (" << tcur->getSessionID() << "/" << tcur->getTuioSourceID() << ")" << std::endl;

	if (!attr.cur_rem)
		return;
	
	attr.cur_rem(tcur->getCursorID(),
		     tcur->getSessionID(),
		     tcur->getTuioSourceID()
		);

}

void TuioDump::addTuioBlob(TuioBlob* tblb)
{
	std::cout << "add blb " << tblb->getBlobID() << " (" << tblb->getSessionID() << "/" << tblb->getTuioSourceID() << ") " << tblb->getX() << " " << tblb->getY() << " " << tblb->getAngle() << " " << tblb->getWidth() << " " << tblb->getHeight() << " " << tblb->getArea() << std::endl;
}

void TuioDump::updateTuioBlob(TuioBlob* tblb)
{
	std::cout << "set blb " << tblb->getBlobID() << " (" << tblb->getSessionID() << "/" << tblb->getTuioSourceID() << ") " << tblb->getX() << " " << tblb->getY() << " " << tblb->getAngle() << " " << tblb->getWidth() << " " << tblb->getHeight() << " " << tblb->getArea()
		  << " " << tblb->getMotionSpeed() << " " << tblb->getRotationSpeed() << " " << tblb->getMotionAccel() << " " << tblb->getRotationAccel() << std::endl;
}

void TuioDump::removeTuioBlob(TuioBlob* tblb)
{
	std::cout << "del blb " << tblb->getBlobID() << " (" << tblb->getSessionID() << "/" << tblb->getTuioSourceID() << ")" << std::endl;
}

void TuioDump::refresh(TuioTime frameTime)
{
	//std::cout << "refresh " << frameTime.getTotalMilliseconds() << std::endl;
}

//		happy place

#ifdef __cplusplus
extern "C"
{
#endif

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
		TuioDump* dump = create_tuiodump(attr);

		TuioClient client(osc_receiver);
		client.addTuioListener(dump);
		client.connect(false);

		rec->receiver = osc_receiver;
		rec->dump     = dump;
		return rec;
	}

	void my_tuio_client_destroy(void* wrap)
	{
		MyTuioClientAttrs* client = (MyTuioClientAttrs*)wrap;

		OscReceiver* osc_receiver = (OscReceiver*)client->receiver;
		TuioDump*    dump	 = (TuioDump*)client->dump;
		delete osc_receiver;
		delete dump;
	}

#ifdef __cplusplus
}
#endif
