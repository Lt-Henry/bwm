#ifndef _FRAME_
#define _FRAME_

#include <gtkmm.h>
#include <gdk/gdkx.h>
#include <X11/Xlib.h>


namespace com
{
	namespace toxiclabs
	{
		namespace bwm
		{
			class Frame
			{
				private:
				
				bool grab;
				int gx,gy;
				int gx2,gy2;
				
				Display * display;
				Window me;
				Window child;
				
				Glib::RefPtr<Gdk::Window> gdk_me;
				Gtk::Window* wf;
				Gtk::Fixed* fixed;
				Gtk::HBox* box;
				Gtk::EventBox* lbl_title;
				Gtk::Button* btn_close;
				
				public:
				
				
				Frame(Display * display,Window child);
				
				bool OnButtonPress(GdkEventButton * event);
				bool OnButtonRelease(GdkEventButton * event);
				bool OnMotion(GdkEventMotion * event);
			};
		}
	}
}

#endif
