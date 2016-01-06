#ifndef DEBUG_H
#define DEBUG_H


#ifdef DEBUG
        #include <iostream>
        #define DBG(x) std::cout << "DBG: " << x << std::endl;
#else
        #define DBG(x) //
#endif


#ifdef DEBUG_M
        #include <iostream>
        #define DBG_M(x) std::cout << "DBG: " << x << std::endl;
        #define DBG(x) //
#else

        #define DBG_M(x) //
#endif

#endif // DEBUG_H
