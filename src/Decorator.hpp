
#ifndef _DECORATOR_
#define _DECORATOR_

#include <X11/Xlib.h>
#include <cairo.h>


#include <string>

namespace com
{
	namespace toxiclabs
	{
		namespace bwm
		{
			class Decorator
			{
				private:
				
				Display * display;
				Window me;
				Window child;
				
				cairo_t * cairo;
				cairo_surface_t * surface;
				
				//status
				bool grabbed;
				
				//grab
				int grab_x;
				int grab_y;
				
				unsigned int width;
				unsigned int height;
				
				std::string name;
				
				void CreateContext();
				void Draw();
				
				public:
				
				Decorator(Display * display,Window child);
				~Decorator();
				
				Window GetWindow();
				Window GetChild();
				
				
				void Map();
				void UnMap();
				
				void OnExpose();
				void OnButtonPress(int x,int y,int rx,int ry,unsigned int button);
				void OnButtonRelease(int x,int y,int rx,int ry,unsigned int button);
				void OnMotion(int x,int y,int rx,int ry);
				
			};
		}
	}
}


#endif
