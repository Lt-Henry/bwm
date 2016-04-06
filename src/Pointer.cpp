
#include "Pointer.hpp"


using namespace std;
using namespace com::toxiclabs::bwm;

Display * Pointer::display;
std::map<std::string,Cursor> Pointer::cursors;

void Pointer::Init(Display * display)
{
	Pointer::display=display;
	
	Pointer::cursors["left_ptr"]=XcursorLibraryLoadCursor(display,"left_ptr");
}


void Pointer::SetCursor(Window w,string name)
{
	XDefineCursor(Pointer::display,w,Pointer::cursors[name]);
}

