
#include "Decorator.hpp"
#include "Utils.hpp"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cairo-xlib.h>

#include <iostream>
#include <cmath>

using namespace std;
using namespace com::toxiclabs::bwm;



Decorator::Decorator(Display * display,Window child)
{
	this->display=display;
	this->child=child;
	
	this->width=320;
	this->height=240;
	
	grabbed=false;
	
	char* xname=nullptr;
	
	// create a x window
	me = XCreateSimpleWindow(display, XDefaultRootWindow(display), 20, 20,width,height,0, 0xffffffff, 0xffffffff);
	
	// get window title
	XFetchName(display,child,&xname);
	name=string(xname);
	
	// select events we want to receive
	XSelectInput(display,me,ExposureMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | SubstructureRedirectMask | SubstructureNotifyMask);

	
	// reparent child
	XReparentWindow(display,child,me,2,24);
		
		
	int cx;
	int cy;
	unsigned int cborder;
	unsigned int cdepth;
	Window croot;
	unsigned int cwidth;
	unsigned int cheight;
	
	
	XGetGeometry(display,child,&croot,&cx,&cy,&cwidth,&cheight,&cborder,&cdepth);
	
	
	width=cwidth+4+2;
	height=cheight+24+2+2;
	
	XResizeWindow(display,me,width,height);
	
	CreateContext();
	
	Draw();
}


Decorator::~Decorator()
{
	cairo_destroy(cairo);
	cairo_surface_destroy(surface);
	
	//XUnmapWindow(display,me);
	XDestroyWindow(display,me);
}



void Decorator::Draw()
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
	draw::Circle(cairo,width-10,12,8);
	cairo_fill(cairo);
	
	color::RGB(cairo,0xf39c12);
	draw::Circle(cairo,width-30,12,8);
	cairo_fill(cairo);
	
	color::RGB(cairo,0x27ae60);
	draw::Circle(cairo,width-50,12,8);
	cairo_fill(cairo);

	color::RGB(cairo,180,180,180);
	
	cairo_move_to(cairo,0,24);
	cairo_line_to(cairo,width,24);
	cairo_stroke(cairo);
	
	color::RGB(cairo,210,210,210);
	
	cairo_move_to(cairo,0,1);
	cairo_line_to(cairo,width,1);
	cairo_stroke(cairo);
	
	//fake child window
	
	color::RGB(cairo,230,230,230);
	cairo_rectangle(cairo,2,25,width-4,height-28);
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

Window Decorator::GetWindow()
{
	return me;
}

Window Decorator::GetChild()
{
	return child;
}

void Decorator::Map()
{
	XMapWindow(display,me);
	XMapWindow(display,child);
}

void Decorator::UnMap()
{
	XUnmapWindow(display,me);
	XUnmapWindow(display,child);
}

void Decorator::OnExpose()
{
	Draw();
}

void Decorator::OnButtonPress(int x,int y,int rx,int ry,unsigned int button)
{
	//raise window to the top
	XRaiseWindow(display,me);
	
	if(y<24)
	{
		cout<<"Window grabbed!"<<endl;
		grabbed=true;
		
		grab_x=-x;
		grab_y=-y;
	}
}

void Decorator::OnButtonRelease(int x,int y,int rx,int ry,unsigned int button)
{
	grabbed=false;
}

void Decorator::OnMotion(int x,int y,int rx,int ry)
{
	if(grabbed)
	{
		XMoveWindow(display,me,rx+grab_x,ry+grab_y);
	}
}
