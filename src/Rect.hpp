
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
				
				
				Rect();
				Rect(float x,float y,float w,float h);
				
				bool Check(float px,float py);
			
			};
		}
	}
}

#endif
