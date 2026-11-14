#pragma once
#include "types.h"

namespace gf {
class GfComAsm;

namespace DebugAsmUtil {

u32 getFrameCount(const GfComAsm *comAsm, const char *state);
f32 getCurrentClipFrame(const GfComAsm *comAsm, u32 layer);

} // namespace DebugAsmUtil
} // namespace gf
