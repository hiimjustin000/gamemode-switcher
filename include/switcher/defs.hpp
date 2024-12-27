#ifndef DEFS_HPP
#define DEFS_HPP

#include <Geode/DefaultInclude.hpp>

#ifdef GEODE_IS_WINDOWS
    #ifdef SWITCHER_EXPORTING
        #define SWITCHER_DLL __declspec(dllexport)
    #else
        #define SWITCHER_DLL __declspec(dllimport)
    #endif
#else
    #define SWITCHER_DLL __attribute__((visibility("default")))
#endif
#endif