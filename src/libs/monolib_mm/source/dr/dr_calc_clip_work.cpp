#include "dr/dr_calc_clip_work.h"

namespace ml {

bool DrCalcClipWork::clipLineTest(const mm::Vec3 &start, const mm::Vec3 &end, f32 radius) const { return false; }

bool DrCalcClipWork::clipTest(const f32 *min, const f32 *max) const { return false; }

bool DrCalcClipWork::clipTest(const mm::Vec3 *points, int count) const { return false; }

void DrCalcClipWork::debugDraw() {}

bool DrCalcClipWork::clipTest(const mm::Vec3 &position, f32 radius) const { return false; }

int DrCalcClipWork::clipTypeTest(const mm::Vec3 &position, f32 radius) const { return 0; }

} // namespace ml
