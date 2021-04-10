#pragma once
#if defined(_MSC_VER)
// Windows
    #if defined(UNITY_WRAPPER_IMPORT)
        #define EXPORT_UNITY_WRAPPER __declspec(dllimport)
    #else
        #define EXPORT_UNITY_WRAPPER __declspec(dllexport)
    #endif
#elif defined(__GNUC__)
//  GCC
    #define EXPORT_UNITY_WRAPPER __attribute__((visibility("default")))
#else
    //  do nothing and hope for the best?
    #define EXPORT_UNITY_WRAPPER
    #pragma warning Unknown dynamic link import/export semantics.
#endif