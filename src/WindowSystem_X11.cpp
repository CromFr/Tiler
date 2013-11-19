#include "WindowSystem_X11.hpp"

extern "C"{
#include <X11/Xlibint.h>
#include <X11/keysymdef.h>
#include <X11/keysym.h>
}

#include <functional>
using namespace std;

/* for this struct, refer to libxnee */
typedef union
{
	unsigned char    type ;
	xEvent           event ;
	xResourceReq     req   ;
	xGenericReply    reply ;
	xError           error ;
	xConnSetupPrefix setup;
} XRecordDatum;


WindowSystem_X11* pLastInstance = nullptr;
void EventCallbackWrapper(XPointer priv, XRecordInterceptData *hook)
{
	pLastInstance->EventCallback(priv, hook);
}


//====================================================================
WindowSystem_X11::WindowSystem_X11() : m_bAltPressed(false)
{
	pLastInstance=this;

	m_coData = XOpenDisplay("");
	m_coCtrl = XOpenDisplay("");

	if(!m_coCtrl || !m_coData)
	{
		cErr<<"Cannot open connection to X11 display server"<<endl;
		exit(1);
	}
	XSynchronize(m_coCtrl,True);


	int maj, min;
	if(!XRecordQueryVersion(m_coCtrl, &maj, &min))
	{
		cErr<<"X11 record extension not supported"<<endl;
		exit(2);
	}
	cInf<<"X11 record extension v"<<maj<<"."<<min<<endl;

	XRecordRange* rr = XRecordAllocRange();
	rr->device_events.first = KeyPress;
	rr->device_events.last = ButtonRelease;
	//#define KeyPress		2
	//#define KeyRelease		3
	//#define ButtonPress		4
	//#define ButtonRelease		5

	XRecordClientSpec rcs = XRecordAllClients;

	XRecordContext rc = XRecordCreateContext(m_coCtrl, 0, &rcs, 1, &rr, 1);
	if(!rc)
	{
		cErr<<"Could not create record context"<<endl;
		exit(3);
	}

	//(void*(XPointer,XRecordInterceptData*))
	//function<void(XPointer,XRecordInterceptData)> fun = bind(&WindowSystem_X11::EventCallback, this);
	if(!XRecordEnableContext(m_coData, rc, EventCallbackWrapper, NULL))
	{
		cErr<<"Cound not enable record context"<<endl;
		exit(4);
	}

	m_EventLoop = new thread(bind(&WindowSystem_X11::EventLoop, this));


}

//====================================================================
void WindowSystem_X11::ResizeWindow(unsigned long id, const Quad& newSize)
{
	XMoveResizeWindow(m_coCtrl, (Window)id,
					newSize.GetLeft(), newSize.GetTop(), newSize.GetWidth(), newSize.GetHeight());
}

void WindowSystem_X11::EventLoop()
{
	while(true)
	{
		XRecordProcessReplies(m_coData);
	}
}
void WindowSystem_X11::EventCallback(XPointer priv, XRecordInterceptData *hook)
{
	//Discard not-server events
	if(hook->category != XRecordFromServer)
	{
		cFai<<"Event discarded"<<endl;
		XRecordFreeData(hook);
		return;
	}

	XRecordDatum* data = (XRecordDatum*) hook->data;

	int event_type = data->type;
	BYTE btncode, keycode;
	btncode = keycode = data->event.u.u.detail;

	int rootX = data->event.u.keyButtonPointer.rootX;
	int rootY = data->event.u.keyButtonPointer.rootY;

	switch(event_type)
	{
		case KeyPress:{
			cInf<<"KeyPress: "<<hex<<(int)keycode<<endl;
			if(keycode == 0x40)//Left ALT
				m_bAltPressed = true;
			break;
			}
		case KeyRelease:
			cInf<<"KeyRelease: "<<hex<<(int)keycode<<endl;
			if(keycode == 0x40)//Left ALT
				m_bAltPressed = false;
			break;
		case ButtonPress:
			cInf<<"ButtonPress: "<<hex<<(int)keycode<<" at "<<dec<<rootX<<"-"<<rootY<<endl;
			if(keycode == 0x1)//Left click
			{
				if(m_bAltPressed)
				{
					Window root, child;
					int rootX, rootY, winX, winY;
					unsigned int mask;
					XQueryPointer(m_coCtrl,DefaultRootWindow(m_coCtrl),&root,&child,
							&rootX,&rootY,&winX,&winY,&mask);

					EventHandler::Get()->SignalDragStart((unsigned long)child);
				}
			}
			else if(keycode == 0x2)//Middle click
			{
				EventHandler::Get()->SignalResizeStart(Coord2D(rootX, rootY));
			}
			break;
		case ButtonRelease:
			cInf<<"ButtonRelease: "<<hex<<(int)keycode<<" at "<<dec<<rootX<<"-"<<rootY<<endl;
			if(keycode == 0x1)//Left click
			{
				EventHandler::Get()->SignalDragStop();
			}
			else if(keycode == 0x2)//Middle click
			{
				EventHandler::Get()->SignalResizeStop(Coord2D(rootX, rootY));
			}
			break;
			break;
		default:
			cInf<<"default"<<endl;
			break;
	}
	XRecordFreeData(hook);
}
















