#ifndef WINDOWSYSTEM_HPP_INCLUDED
#define WINDOWSYSTEM_HPP_INCLUDED

#include "Quad.hpp"
#include "EventHandler.hpp"

class WindowSystem
{
public:


	virtual void ResizeWindow(unsigned long id, const Quad& newSize)=0;


protected:


};

#endif // WINDOWSYSTEM_HPP_INCLUDED
