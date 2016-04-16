
#include "Frame.hpp"

#include <iostream>

using namespace com::toxiclabs::bwm;
using namespace std;



Frame::Frame(Display * display,Window child)
{
/*
	me = XCreateSimpleWindow(display, XDefaultRootWindow(display), 20, 20,320,240,0, 0xffffffff, 0xffffffff);
	
	GdkDisplay * gdisplay;
	GdkWindow * gme;
	
	gdisplay=gdk_x11_lookup_xdisplay(display);
	cout<<"display "<<gdisplay<<endl;
	
	gme=gdk_x11_window_foreign_new_for_display(gdisplay,me);
	
	gdk_me=Glib::wrap(gme);
	
	XMapWindow(display,me);
	*/
	
	grab=false;
	
	int cx;
	int cy;
	unsigned int cborder;
	unsigned int cdepth;
	Window croot;
	unsigned int cwidth;
	unsigned int cheight;

	XGetGeometry(display,child,&croot,&cx,&cy,&cwidth,&cheight,&cborder,&cdepth);
	
	wf=new Gtk::Window();
	wf->resize(cwidth,cheight+36);
	fixed=new Gtk::Fixed();
	
	box=new Gtk::HBox();
	box->set_size_request(cwidth,32);
	box->set_border_width(2);
	
	fixed->put(*box,0,0);
	
	
	lbl_title=new Gtk::EventBox();
	lbl_title->add_label("xterm",false);
	
	btn_close=new Gtk::Button();
	btn_close->set_image_from_icon_name("gtk-close");
	
	box->pack_start(*lbl_title);
	box->pack_end(*btn_close,false,false);
	
	
	wf->add(*fixed);
	
	lbl_title->set_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::POINTER_MOTION_MASK);
	lbl_title->signal_button_press_event().connect(
sigc::mem_fun(*this,&Frame::OnButtonPress));
	lbl_title->signal_button_release_event().connect(
sigc::mem_fun(*this,&Frame::OnButtonRelease));
	lbl_title->signal_motion_notify_event().connect(
sigc::mem_fun(*this,&Frame::OnMotion));


	
	wf->show_all();
	me=GDK_WINDOW_XID(wf->get_window()->gobj());
	XReparentWindow(display,child,me,1,36);
	
	XMapWindow(display,me);
	XMapWindow(display,child);
}


bool Frame::OnButtonPress(GdkEventButton * event)
{
	
	grab=true;
	
	wf->get_position(gx,gy);
	gx2=event->x_root;
	gy2=event->y_root;
	
	return true;
}

bool Frame::OnButtonRelease(GdkEventButton * event)
{
	
	grab=false;
	
	return true;
}

bool Frame::OnMotion(GdkEventMotion * event)
{
	if(grab)
	{
		wf->move(gx+(event->x_root-gx2),gy+(event->y_root-gy2));
	}
}
