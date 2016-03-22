
#include "Utils.hpp"
#include <cmath>


void com::toxiclabs::bwm::color::RGB(cairo_t * cairo,uint8_t r,uint8_t g,uint8_t b)
{
	double dr,dg,db,df;
	
	df=1.0/255.0;
	dr=(double)r*df;
	dg=(double)g*df;
	db=(double)b*df;
	
	cairo_set_source_rgb(cairo,dr,dg,db);
}

void com::toxiclabs::bwm::color::RGB(cairo_t * cairo,uint32_t hex)
{
	double dr,dg,db,df;
	int r,g,b;
	
	r=(hex & 0x00FF0000) >> 16;
	g=(hex & 0x0000FF00) >> 8;
	b=(hex & 0x000000FF);
	
	df=1.0/255.0;
	dr=r*df;
	dg=g*df;
	db=b*df;
	
	cairo_set_source_rgb(cairo,dr,dg,db);
}

void com::toxiclabs::bwm::draw::Circle(cairo_t * cairo,double x,double y,double r)
{
	cairo_arc(cairo,x,y,r,0,M_PI*2.0);
}
