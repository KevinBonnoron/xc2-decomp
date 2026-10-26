#include "fw/fw_pad.h"
#include "types.h"

namespace fw {

u32 PadFilterStd::filterBtn(u32 button) { return button & 0xffff; }

f32 PadFilterStd::filterALX(f32 x, f32 y) { return x; }

f32 PadFilterStd::filterALY(f32 x, f32 y) { return y; }

f32 PadFilterStd::filterARX(f32 x, f32 y) { return x; }

f32 PadFilterStd::filterARY(f32 x, f32 y) { return y; }

const char *PadFilterStd::getFilterName() const { return "PadFilterStd"; }

} // namespace fw
