
#include "Decorator.hpp"

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <iostream>

using namespace std;
using namespace com::toxiclabs::bwm;



Decorator::Decorator(Display * display,Window child,string name)
{
	this->display=display;
	this->child=child;
	this->name=name;
	
	this->width=320;
	this->height=240;
	
	me = XCreateSimpleWindow(display, XDefaultRootWindow(display), 20, 20,width,height,0, 0xffffffff, 0xffffffff);
	
	/* Set window title */
	XStoreName(display,me,name.c_str());
	
	XMapWindow(display, me);
      
	XGrabPointer(
		display,
		me,
		false,
		PointerMotionMask | ButtonPressMask | ButtonReleaseMask,
		GrabModeAsync,
		GrabModeAsync,
		me,
		None,
		CurrentTime);
		
		cairo=nullptr;
		surface=nullptr;
		buffer=nullptr;
		
		gc = XCreateGC(display, me, 0, nullptr);
		
		CreateContext();
		
		Update();
}


Decorator::~Decorator()
{
	
}


void Decorator::Update()
{
	
		cairo_set_source_rgb(cairo, 0.6, 0.2, 0.2);
		cairo_paint(cairo);
	
		XPutImage(display,me,gc,xbuffer,0,0,0,0,width,height);
		XFlush(display);	
		
}

void Decorator::CreateContext()
{
	int x;
	int y;
	unsigned int border;
	unsigned int depth;
	Window root;
	
	
	XGetGeometry(display,me,&root,&x,&y,&this->width,&this->height,&border,&depth);
	
	cout<<"New size: "<<width<<","<<height<<endl;	
	
	if(surface!=nullptr)
	{
		cairo_surface_destroy(surface);
		XDestroyImage(xbuffer);
		cairo_destroy(cairo);
	}
	
	buffer=new uint8_t[width*height*4];
	surface=cairo_image_surface_create_for_data(buffer,CAIRO_FORMAT_ARGB32,width,height,width*4);
	cairo=cairo_create(surface);
	
	xbuffer = XCreateImage(display,DefaultVisual(display,0),24,ZPixmap,0,(char *)buffer,width,height,32,4*width);
}
