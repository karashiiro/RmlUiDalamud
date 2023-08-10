﻿#pragma once
#include "DllUtils.h"

#include <RmlUi/Core.h>

extern "C" {
inline DllExport void RmlInitialise()
{
    Rml::Initialise();
}

inline DllExport void RmlShutdown()
{
    Rml::Shutdown();
}
}
