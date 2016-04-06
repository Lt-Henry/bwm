
#include "Rect.hpp"

using namespace com::toxiclabs::bwm;

Rect::Rect()
{
	redraw=false;
	mouse_over=false;
}

Rect::Rect(float x,float y,float w,float h)
{
	this->x=x;
	this->y=y;
	this->w=w;
	this->h=h;
}


bool Rect::Check(float px,float py)
{
	bool f1,f2;
	
	f1 = (px>=x and px<=(x+w));
	f2 = (py>=y and py<=(y+h));
	
	return (f1 and f2);
}


void Rect::PushMouse(float mx,float my)
{
	if(Check(mx,my))
	{
		if(not mouse_over)
		{
			mouse_over=true;
			redraw=true;
		}
	}
	else
	{
		if(mouse_over)
		{
			mouse_over=false;
			redraw=true;
		}
	}
}

