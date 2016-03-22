
#include "Decorator.hpp"
#include "Utils.hpp"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cairo-xlib.h>

#include <iostream>
#include <cmath>

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
				
		
	CreateContext();
	
	Update();
}


Decorator::~Decorator()
{
	
}


void Decorator::Update()
{
	cairo_text_extents_t te;
	cairo_font_extents_t fe;

	cairo_select_font_face (cairo, "Ubuntu", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size (cairo, 14.0);
	cairo_text_extents (cairo, name.c_str(), &te);
	cairo_font_extents (cairo, &fe);
	
		
	
	color::RGB(cairo,0xbdc3c7);
	cairo_paint(cairo);
	
	float tx;
	float ty;
	
	tx=(width/2.0)-(te.width/2.0f);
	ty=fe.height+2.0f;
	
	color::RGB(cairo,16,16,16);
	
	cairo_move_to(cairo,tx,ty);
	cairo_show_text (cairo, name.c_str());
	
	color::RGB(cairo,0xe74c3c);
	cairo_arc(cairo,width-10,10,8,0,2.0f*M_PI);
	cairo_fill(cairo);
	
	color::RGB(cairo,0xf39c12);
	cairo_arc(cairo,width-30,10,8,0,2.0f*M_PI);
	cairo_fill(cairo);
	
	color::RGB(cairo,0x27ae60);
	cairo_arc(cairo,width-50,10,8,0,2.0f*M_PI);
	cairo_fill(cairo);

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
	
	surface = cairo_xlib_surface_create(display, me, DefaultVisual(display, 0), width, height);
    cairo_xlib_surface_set_size(surface, width, height);
    cairo=cairo_create(surface);
	
}
