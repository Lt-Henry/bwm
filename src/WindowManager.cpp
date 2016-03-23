
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
	
	Decorator * tab;
		
	
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
				if(tabs.find(event.xexpose.window)!=tabs.end())
				{
					tabs[event.xexpose.window]->OnExpose();
				}
			break;
			
			case MapNotify:
				
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
				
				if(tabs.find(event.xmaprequest.window)!=tabs.end())
				{
					cout<<"decorator already mapped"<<endl;
				}
				else
				{
					tab=new Decorator(display,event.xmaprequest.window,"Window");
					tabs[tab->GetWindow()]=tab;
					
					XMapWindow(display,tab->GetWindow());
					XMapWindow(display,event.xmaprequest.window);
					
				}
				
				
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
				
				if(tabs.find(event.xbutton.window)!=tabs.end())
				{
					tabs[event.xbutton.window]->OnButtonPress(event.xbutton.x,event.xbutton.y,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.button);
				}
				
			break;
			
			case ButtonRelease:
				
				if(tabs.find(event.xbutton.window)!=tabs.end())
				{
					tabs[event.xbutton.window]->OnButtonRelease(event.xbutton.x,event.xbutton.y,event.xbutton.x_root,event.xbutton.y_root,event.xbutton.button);
				}

			break;
			
			case MotionNotify:
				
				if(tabs.find(event.xbutton.window)!=tabs.end())
				{
					tabs[event.xbutton.window]->OnMotion(event.xbutton.x,event.xbutton.y,event.xbutton.x_root,event.xbutton.y_root);
				}
			break;
		}
	}
}
