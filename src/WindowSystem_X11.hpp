#ifndef WINDOWSYSTEM_X11_HPP_INCLUDED
#define WINDOWSYSTEM_X11_HPP_INCLUDED

#include "WindowSystem.hpp"
extern "C"{
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/record.h>
}

#include <thread>

class WindowSystem_X11 : public WindowSystem
{
public:
	WindowSystem_X11();

	void ResizeWindow(unsigned long id, const Quad& newSize) override;

	///SHOULD NOT BE CALLED
	void EventCallback(XPointer priv, XRecordInterceptData *hook);

private:
	Display* m_coCtrl;
	Display* m_coData;

	std::thread* m_EventLoop;
	void EventLoop();

	bool m_bAltPressed;



};

#endif // WINDOWSYSTEM_X11_HPP_INCLUDED
