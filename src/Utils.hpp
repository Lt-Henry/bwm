#ifndef _UTILS_
#define _UTILS_

#include <cairo.h>
#include <string>

namespace com
{
	namespace toxiclabs
	{
		namespace bwm
		{
			namespace color
			{
				void RGB(cairo_t * cairo,uint8_t r,uint8_t g,uint8_t b);
				void RGB(cairo_t * cairo,uint32_t hex);
			}
		}
	}
}


#endif

