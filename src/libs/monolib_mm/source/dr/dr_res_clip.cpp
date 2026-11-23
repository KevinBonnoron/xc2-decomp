#include "dr/dr_res_clip.h"

#include "dr/dr_calc_clip_work_view_plane.h"
#include "dr/dr_calc_view_work.h"
#include "mm_math/mm_vec3.h"

namespace ml {

DrResClip::DrResClip() : unknown08(0x60), unknown0c(0), unknown10(0) {}

DrResClip::~DrResClip() { releaseQuery(); }

bool DrResClip::clipChkOccOff(DrCalcViewWork *viewWork, const mm::Vec3 &position, f32 radius) {
  u32 flags = unknown08;
  unknown08 = flags & 0xffffff1e;
  unknown10 = 0;
  const mm::Vec3 &viewPos = viewWork->unknown400;
  f32 dx = viewPos.x - position.x;
  f32 dy = viewPos.y - position.y;
  f32 dz = viewPos.z - position.z;
  if (dx * dx + dy * dy + dz * dz <= radius * radius) {
    unknown08 = (flags & 0xffffff00) | 0xe;
    return false;
  }
  if (!viewWork->m_drCalcClipWorkViewPlane.clipTest(position, radius)) {
    unknown08 = 0;
    return true;
  }
  return false;
}

} // namespace ml

// The game builds DrResQueryAcc in the same unit as DrResClip: its constructor (0x71008693b8), releaseQuery (0x71008693d4) and getOccPixel (0x7100869608) sit
// between the functions of DrResClip (0x71008693a8 to 0x71008696e4; the game interleaves them, this file puts the included functions last). The destructor of
// DrResClip (0x71008693c0) holds the body of releaseQuery inline, 5 instructions: without this include it is a single branch to releaseQuery, 1 instruction, since
// clang only inlines a function whose definition it has seen in the unit. The constructor of DrResClip (0x71008693a8) fails the same way: 11 instructions, with a
// call to the base constructor, against the game's 4.
#include "dr_res_query_acc.cpp"
