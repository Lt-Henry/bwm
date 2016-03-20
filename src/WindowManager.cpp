
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
		
		XWindowChanges changes;
		
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
			
			case MapRequest:
				cout<<"map request"<<endl;
				window=event.xmaprequest.window;
				XMapWindow(display,window);
			break;
			
			case ConfigureNotify:
				cout<<"configure notify"<<endl;
			break;
			
			case ConfigureRequest:
				cout<<"configure request"<<endl;
				
				
				changes.x=event.xconfigurerequest.x;
				changes.y=event.xconfigurerequest.y;
				changes.width=event.xconfigurerequest.width;
				changes.height=event.xconfigurerequest.height;
				changes.border_width=0;
				changes.sibling=event.xconfigurerequest.above;
				changes.stack_mode=event.xconfigurerequest.detail;
				
				window=event.xconfigurerequest.window;
				XConfigureWindow(display,window,event.xconfigurerequest.value_mask,&changes);
			break;
		}
	}
}
