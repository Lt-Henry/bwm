
#ifndef _WINDOW_MANAGER_
#define _WINDOW_MANAGER_

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
				
				std::map<Window,Decorator *> frames;
				std::map<Window,Decorator *> clients;
				
				public:
				
				WindowManager(std::string name);
				~WindowManager();
				
				void Run();
			};
		}
	}
}

#endif
