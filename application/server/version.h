#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "05";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2016";
	static const char UBUNTU_VERSION_STYLE[] =  "16.01";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 1;
	static const long BUILD  = 20;
	static const long REVISION  = 4;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 376;
	#define RC_FILEVERSION 1,1,20,4
	#define RC_FILEVERSION_STRING "1, 1, 20, 4\0"
	static const char FULLVERSION_STRING [] = "1.1.20.4";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 9;
	

}
#endif //VERSION_H
