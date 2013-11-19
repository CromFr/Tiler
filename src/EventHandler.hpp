#ifndef EVENTHANDLER_HPP_INCLUDED
#define EVENTHANDLER_HPP_INCLUDED

#include "Quad.hpp"
class WindowSystem;

class EventHandler
{
public:
	static EventHandler* Get();

	void SignalDragStart(unsigned long winID);
	void SignalDragStop();
	void SignalResizeStart(const Coord2D& pos);
	void SignalResizeStop(const Coord2D& pos);

private:
	EventHandler();

	WindowSystem* m_ws;

	unsigned long winIDDragged;
	Coord2D posResizeStart;


};

#endif // EVENTHANDLER_HPP_INCLUDED
