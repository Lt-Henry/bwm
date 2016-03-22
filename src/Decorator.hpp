
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
				
				unsigned int width;
				unsigned int height;
				
				std::string name;
				
				void CreateContext();
				
				public:
				
				Decorator(Display * display,Window child,std::string name);
				~Decorator();
				
				void Update();
				
			};
		}
	}
}


#endif
