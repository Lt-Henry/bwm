
#include "WindowManager.hpp"

#include <iostream>

using namespace std;
using namespace com::toxiclabs::bwm;

WindowManager::WindowManager(string name)
{
	display=XOpenDisplay(name.c_str());
	root=DefaultRootWindow(display);
}

WindowManager::~WindowManager()
{
	XCloseDisplay(display);
}


void WindowManager::Run()
{
	bool quit_requested=false;
	
	XSelectInput(display,root,SubstructureRedirectMask | SubstructureNotifyMask);
	
	XSync(display, false);
	
	while(not quit_requested)
	{
		XEvent event;
		Window window;
		
		XNextEvent(display,&event);
		
		switch(event.type)
		{
			case MapNotify:
				cout<<"Mapped window"<<endl;
				
			break;
		
			case CreateNotify:
				cout<<"create window"<<endl;
			break;
			
			case DestroyNotify:
				cout<<"destroyed window"<<endl;
			break;
			
			case ReparentNotify:
				cout<<"reparented window"<<endl;
			break;
		}
	}
}
