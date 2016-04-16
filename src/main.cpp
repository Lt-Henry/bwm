
#include "WindowManager.hpp"

#include <iostream>

using namespace std;
using namespace com::toxiclabs::bwm;


int main(int argc,char *argv[])
{
	cout<<"b window manager"<<endl;
	
	WindowManager wm(argc,argv);
	
	wm.Run2();
	
	return 0;
}
