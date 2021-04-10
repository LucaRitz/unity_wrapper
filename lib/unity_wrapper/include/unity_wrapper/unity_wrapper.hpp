#pragma once

#include "macro_definition.hpp"
#include "type.hpp"

extern "C" {

    EXPORT_UNITY_WRAPPER void onStart();
    EXPORT_UNITY_WRAPPER void onTearDown();
    EXPORT_UNITY_WRAPPER void processEvents();

    ///////////////////////////////////////////////////////
    //// Events
    ///////////////////////////////////////////////////////

    EXPORT_UNITY_WRAPPER void onCountEvent(CountEventCallback callback);

    ///////////////////////////////////////////////////////
    //// Debugging
    ///////////////////////////////////////////////////////
    EXPORT_UNITY_WRAPPER void debug(DebugCallback callback);
}