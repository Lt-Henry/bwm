
#ifndef _WINDOW_MANAGER_
#define _WINDOW_MANAGER_

#include <gtkmm.h>

#include "Decorator.hpp"


#include <X11/Xlib.h>

#include <string>
#include <map>

namespace com
{
	namespace toxiclabs
	{
		namespace bwm
		{
			class WindowManager
			{
				private:
				
				Display * display;
				Window root;
				Glib::RefPtr<Gtk::Application> application;
				
				std::map<Window,Decorator *> frames;
				std::map<Window,Decorator *> clients;
				
				public:
				
				WindowManager(int argc,char * argv[]);
				~WindowManager();
				
				void Run();
				void Run2();
			};
		}
	}
}

#endif
