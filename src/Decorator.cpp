
#include "Decorator.hpp"
#include "Utils.hpp"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cairo-xlib.h>

#include <iostream>
#include <cmath>

using namespace std;
using namespace com::toxiclabs::bwm;


cairo_surface_t * Decorator::close = nullptr;
cairo_surface_t * Decorator::maximize = nullptr;
cairo_surface_t * Decorator::minimize = nullptr;

uint32_t Decorator::bg_color=0x00000000;
uint32_t Decorator::fg_color=0xffffffff;

void Decorator::LoadTheme()
{
	cairo_t * cr;
	
	//close surface
	close=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,16,16);
	
	cr=cairo_create(close);
	
	cairo_set_source_rgb(cr,1.0,1.0,1.0);
	cairo_set_line_width(cr,3.0);
	cairo_set_line_cap(cr,CAIRO_LINE_CAP_ROUND);
	cairo_move_to(cr,6.0,6.0);
	cairo_line_to(cr,10.0,10.0);
	cairo_stroke(cr);
	cairo_move_to(cr,6.0,10.0);
	cairo_line_to(cr,10.0,6.0);
	cairo_stroke(cr);
	
	cairo_destroy(cr);
	
	
	//maximize surface
	maximize=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,16,16);
	cr=cairo_create(maximize);
	
	cairo_set_source_rgb(cr,1.0,1.0,1.0);
	cairo_set_line_width(cr,2.0);
	cairo_set_line_cap(cr,CAIRO_LINE_CAP_ROUND);
	cairo_move_to(cr,4.0,4.0);
	cairo_line_to(cr,12.0,4.0);
	cairo_line_to(cr,12.0,12.0);
	cairo_line_to(cr,4.0,12.0);
	cairo_line_to(cr,4.0,4.0);
	cairo_stroke(cr);
	
	cairo_destroy(cr);
	
	//minimize surface
	minimize=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,16,16);
	cr=cairo_create(minimize);
	
	cairo_set_source_rgb(cr,1.0,1.0,1.0);
	cairo_set_line_width(cr,2.0);
	cairo_set_line_cap(cr,CAIRO_LINE_CAP_ROUND);
	cairo_move_to(cr,4.0,12.0);
	cairo_line_to(cr,12.0,12.0);
	cairo_stroke(cr);
	
	cairo_destroy(cr);
		
	
	
	Decorator::bg_color=0x9d9d9dff;
	Decorator::fg_color=0xe69858ff;
	
}

Decorator::Decorator(Display * display,Window child)
{
	this->display=display;
	this->child=child;
	
	this->width=320;
	this->height=240;
	
	grabbed=false;
	top=false;
	
		
	char* xname=nullptr;
	
	// create a x window
	me = XCreateSimpleWindow(display, XDefaultRootWindow(display), 20, 20,width,height,0, 0xffffffff, 0xffffffff);
	
	
	// get window title
	XFetchName(display,child,&xname);
	name=string(xname);
	
	// select events we want to receive
	XSelectInput(display,me,ExposureMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | SubstructureRedirectMask | SubstructureNotifyMask | StructureNotifyMask);

	
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
	
		
	color::RGBA(cairo,Decorator::bg_color);
	cairo_paint(cairo);
	
	float tx;
	float ty;
	
	tx=(width/2.0)-(te.width/2.0f);
	ty=fe.height+2.0f;
	
	
	color::RGB(cairo,240,240,240);
	
	
	
	cairo_move_to(cairo,tx,ty);
	cairo_show_text (cairo, name.c_str());
	
	/*
	color::RGB(cairo,0xe74c3c);
	draw::Circle(cairo,width-10,12,8);
	cairo_fill(cairo);
	*/
	
	
	if(btnClose.mouse_over)
	{
		color::RGBA(cairo,Decorator::fg_color);
		cairo_rectangle(cairo,btnClose.x,btnClose.y,24,24);
		//draw::Circle(cairo,width-20+8,4+8,8);
		cairo_fill(cairo);
	}
	
	if(btnMaximize.mouse_over)
	{
		color::RGBA(cairo,Decorator::fg_color);
		cairo_rectangle(cairo,btnMaximize.x,btnMaximize.y,24,24);
		cairo_fill(cairo);
	}
	
	if(btnMinimize.mouse_over)
	{
		color::RGBA(cairo,Decorator::fg_color);
		cairo_rectangle(cairo,btnMinimize.x,btnMinimize.y,24,24);
		cairo_fill(cairo);
	}
	
	
	cairo_set_source_surface(cairo,close,width-24+4,4);
	cairo_paint(cairo);
	
	cairo_set_source_surface(cairo,maximize,width-48+4,4);
	cairo_paint(cairo);
	
	cairo_set_source_surface(cairo,minimize,width-72+4,4);
	cairo_paint(cairo);


	

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
	
	btnClose=Rect(width-24,0,24,24);
	btnMaximize=Rect(width-48,0,24,24);
	btnMinimize=Rect(width-72,0,24,24);
	btnHandle=Rect(0,0,width-72,24);
	
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
	//XUnmapWindow(display,child);
}

void Decorator::OnExpose()
{
	Draw();
}

void Decorator::OnButtonPress(int x,int y,int rx,int ry,unsigned int button)
{
	
	
	if(btnHandle.mouse_over)
	{
	
		//raise window to the top
		XRaiseWindow(display,me);
	
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
	else
	{
		btnClose.PushMouse(x,y);
		btnMaximize.PushMouse(x,y);
		btnMinimize.PushMouse(x,y);
		btnHandle.PushMouse(x,y);
		
		
		if(btnClose.redraw or btnMaximize.redraw or btnMinimize.redraw)
		{
			Draw();
			btnClose.redraw=false;
			btnMaximize.redraw=false;
			btnMinimize.redraw=false;
		}
	}
}
