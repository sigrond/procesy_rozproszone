#ifndef DEBUG_H
#define DEBUG_H


#ifdef DEBUG
        #include <iostream>
        #define DBG(x) std::cout << "DBG: " << x << std::endl;
#else
        #define DBG(x) //
#endif


#endif // DEBUG_H
