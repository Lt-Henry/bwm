
#ifndef _POINTER_
#define _POINTER_

#include <X11/Xlib.h>
#include <X11/Xcursor/Xcursor.h>

#include <string>
#include <map>


namespace com
{
	namespace toxiclabs
	{
		namespace bwm
		{
			class Pointer
			{
				private:
				
				static Display * display;
				
				
				static std::map<std::string,Cursor> cursors;
				
				public:
				
				static void Init(Display * display);
				
				static void SetCursor(Window w,std::string name);
			};
		}
	}
}


#endif
