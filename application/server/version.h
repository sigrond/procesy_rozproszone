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
	static const long MAJOR  = 0;
	static const long MINOR  = 1;
	static const long BUILD  = 72;
	static const long REVISION  = 429;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 314;
	#define RC_FILEVERSION 0,1,72,429
	#define RC_FILEVERSION_STRING "0, 1, 72, 429\0"
	static const char FULLVERSION_STRING [] = "0.1.72.429";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 72;
	

}
#endif //VERSION_H
