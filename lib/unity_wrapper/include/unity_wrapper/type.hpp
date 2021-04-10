#pragma once

#include "macro_definition.hpp"

extern "C" {
    struct CountEvent;

    ///////////////////////////////////////////////////////
    //// Callbacks
    ///////////////////////////////////////////////////////
    typedef void (__stdcall* CountEventCallback)(CountEvent);
    typedef void (__stdcall* DebugCallback)(const char*);

    ///////////////////////////////////////////////////////
    //// Events
    ///////////////////////////////////////////////////////
    struct EXPORT_UNITY_WRAPPER CountEvent {
        explicit CountEvent(int value = 0);

        int _value;
    };
}