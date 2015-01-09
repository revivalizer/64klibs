#include "pch.h"

extern "C" const int _fltused = 0;

extern int main(int argc, char* argv[]);

extern "C" void __cdecl mainCRTStartup()
{
    // set up our minimal cheezy atexit table
    _atexit_init();

    // Call C++ constructors
    _initterm( __xc_a, __xc_z );

    //mainret = main( argc, _ppszArgv, 0 );
    int mainret = main(0, nullptr);

    _DoExit();

    ExitProcess(mainret);
}

extern "C" int __cdecl _purecall(void)  
{  
    return 0;  
}  

