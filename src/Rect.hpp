
#ifndef _RECT_
#define _RECT_

namespace com
{
	namespace toxiclabs
	{
		namespace bwm
		{
			class Rect
			{
				
				public:
				
				float x;
				float y;
				float w;
				float h;
				
				bool redraw;
				bool mouse_over;
				
				
				Rect();
				Rect(float x,float y,float w,float h);
				
				bool Check(float px,float py);
				
				void PushMouse(float mx,float my);
			
			};
		}
	}
}

#endif
