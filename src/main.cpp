
#include "WindowManager.hpp"

#include <iostream>

using namespace std;
using namespace com::toxiclabs::bwm;


int main(int argc,char *argv[])
{
	cout<<"b window manager"<<endl;
	
	WindowManager wm(":2");
	
	wm.Run();
	
	return 0;
}
