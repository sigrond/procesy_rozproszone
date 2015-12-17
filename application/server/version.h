#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "16";
	static const char MONTH[] = "12";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.12";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 0;
	static const long MINOR  = 1;
	static const long BUILD  = 15;
	static const long REVISION  = 77;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 57;
	#define RC_FILEVERSION 0,1,15,77
	#define RC_FILEVERSION_STRING "0, 1, 15, 77\0"
	static const char FULLVERSION_STRING [] = "0.1.15.77";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 15;
	

}
#endif //VERSION_H
