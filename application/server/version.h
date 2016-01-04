#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "04";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2016";
	static const char UBUNTU_VERSION_STYLE[] =  "16.01";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 0;
	static const long BUILD  = 8;
	static const long REVISION  = 8;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 357;
	#define RC_FILEVERSION 1,0,8,8
	#define RC_FILEVERSION_STRING "1, 0, 8, 8\0"
	static const char FULLVERSION_STRING [] = "1.0.8.8";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 97;
	

}
#endif //VERSION_H
