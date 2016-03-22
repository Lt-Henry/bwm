
#include "WindowManager.hpp"
#include "Decorator.hpp"

#include <iostream>

using namespace std;
using namespace com::toxiclabs::bwm;

WindowManager::WindowManager(string name)
{
	display=XOpenDisplay(name.c_str());
	root=DefaultRootWindow(display);
	
	cout<<"root: "<<root<<endl;
}

WindowManager::~WindowManager()
{
	XCloseDisplay(display);
}


void WindowManager::Run()
{
	
	Decorator * tab=new Decorator(display,root,"Hello world");
	
	bool quit_requested=false;
	
	XSelectInput(display,root,SubstructureRedirectMask | SubstructureNotifyMask | ExposureMask);
	
	XSync(display, false);
	
	while(not quit_requested)
	{
		XEvent event;
		Window window;
		
		XWindowChanges changes;
		
		XNextEvent(display,&event);
		
		switch(event.type)
		{
			
			case Expose:
				cout<<"Exposure!"<<endl;
			break;
			
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
				
				tab->Update();
				
			break;
			
			case ButtonPress:
				cout<<"Button pressed"<<endl;
				cout<<"window: "<<event.xbutton.window<<endl;
				cout<<"x: "<<event.xbutton.x<<endl;
				cout<<"y: "<<event.xbutton.y<<endl;
			break;
			
			case ButtonRelease:
				cout<<"Button released"<<endl;
				cout<<"window: "<<event.xbutton.window<<endl;
			break;
			
			case MotionNotify:
				/*
				cout<<"motion"<<endl;
				cout<<"x: "<<event.xmotion.x<<endl;
				cout<<"y: "<<event.xmotion.y<<endl;
				*/ 
			break;
		}
	}
}
