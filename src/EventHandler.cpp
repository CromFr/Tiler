#include "EventHandler.hpp"

#ifdef USE_WAYLAND
	#include "WindowSystem_Wayland.hpp"
#elifdef USE_MIR
	#include "WindowSystem_mir.hpp"
#else
	#include "WindowSystem_X11.hpp"
#endif

#include "coloring.h"
using namespace std;


EventHandler* EventHandler::Get()
{
	static EventHandler* inst = nullptr;
	if(inst==nullptr)
	{
		inst = new EventHandler;
	}
	return inst;
}

void EventHandler::SignalDragStart(unsigned long winID)
{
	winIDDragged=winID;
}
void EventHandler::SignalDragStop()
{
	winIDDragged=0;
}
void EventHandler::SignalResizeStart(const Coord2D& pos)
{
	posResizeStart = pos;
}
void EventHandler::SignalResizeStop(const Coord2D& pos)
{
	m_ws->ResizeWindow(winIDDragged, Quad(posResizeStart, pos));
}


EventHandler::EventHandler()
{
	cWar<<endl;
	#ifdef USE_WAYLAND

	#elifdef USE_MIR

	#else
		m_ws = new WindowSystem_X11;
	#endif

}
