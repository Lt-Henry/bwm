
#ifndef _WINDOW_MANAGER_
#define _WINDOW_MANAGER_

#include <X11/Xlib.h>

#include <string>

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
				
				public:
				
				WindowManager(std::string name);
				~WindowManager();
				
				void Run();
			};
		}
	}
}

#endif
