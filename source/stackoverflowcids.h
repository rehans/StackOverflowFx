//------------------------------------------------------------------------
// Copyright(c) 2022 My Plug-in Company.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace MyCompanyName {
//------------------------------------------------------------------------
static const Steinberg::FUID kStackOverflowFxProcessorUID (0x5A6A2AAB, 0xAF505D3A, 0x8B4AF67F, 0x5E9BE0C6);
static const Steinberg::FUID kStackOverflowFxControllerUID (0xC98EBB74, 0x4D6B5DC8, 0xB06266FA, 0x50E212F0);

#define StackOverflowFxVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace MyCompanyName
