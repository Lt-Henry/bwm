
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
	
	Decorator * frame;
	
	
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
			
			case Expose:
				if(frames.find(event.xexpose.window)!=frames.end())
				{
					frames[event.xexpose.window]->OnExpose();
				}
			break;
			
			case MapRequest:
				cout<<"map request"<<endl;
				cout<<"id:"<<event.xmaprequest.window<<endl;
				
				if(clients.find(event.xmaprequest.window)==clients.end())
				{
					cout<<"creating a new decorator"<<endl;
					frame=new Decorator(display,event.xmaprequest.window);
					frames[frame->GetWindow()]=frame;
					clients[event.xmaprequest.window]=frame;
					
					frame->Map();
				}
				else
				{
					cout<<"window already is decorated"<<endl;
					clients[event.xmaprequest.window]->Map();
				}
				
			break;
			
			case MapNotify:
				cout<<"mapping window"<<endl;
				cout<<"id:"<<event.xmap.window<<endl;
			break;
			
			case UnmapNotify:
				cout<<"unmapping window"<<endl;
				cout<<"id:"<<event.xunmap.window<<endl;
				
				if(clients.find(event.xunmap.window)!=clients.end())
				{
					clients[event.xunmap.window]->UnMap();
				}
				
			break;
		
			case CreateNotify:
				cout<<"create window"<<endl;
				cout<<"id:"<<event.xcreatewindow.window<<endl;
				
			break;
			
			case DestroyNotify:
				cout<<"destroyed window"<<endl;
				cout<<"id:"<<event.xdestroywindow.window<<endl;
				
				
			break;
			
			case ReparentNotify:
				cout<<"reparented window"<<endl;
			break;
			
			
			case ConfigureNotify:
				//cout<<"configure notify"<<endl;
			break;
			
			case ConfigureRequest:
								
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
			
			case ButtonPress:
				
				if(frames.find(event.xbutton.window)!=frames.end())
				{
					frames[event.xbutton.window]->OnButtonPress(event.xbutton.x,event.xbutton.y,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.button);
				}
				
			break;
			
			case ButtonRelease:
				
				if(frames.find(event.xbutton.window)!=frames.end())
				{
					frames[event.xbutton.window]->OnButtonRelease(event.xbutton.x,event.xbutton.y,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.button);
				}

			break;
			
			case MotionNotify:
				
				if(frames.find(event.xbutton.window)!=frames.end())
				{
					frames[event.xbutton.window]->OnMotion(event.xbutton.x,event.xbutton.y,event.xbutton.x_root,event.xbutton.y_root);
				}
			break;
		}
	}
}
