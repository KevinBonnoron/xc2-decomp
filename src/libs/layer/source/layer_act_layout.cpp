#include "layer/layer_act_layout.h"

#include <stddef.h>

#include "layer/layer_act_base.h"

namespace layer {

namespace {

struct unknown004 {
  u8 _00[0x02];
  u16 unknown02; // Inferred role: command value count; original member name unknown.
};

static_assert(offsetof(unknown004, unknown02) == 0x02, "");

} // namespace

u32 LayerActLayout::calcLayoutActionWorkSize(const u8 *data) { return sizeof(LayerActWork) + reinterpret_cast<const LyrActionHeader *>(data)->actionNum * sizeof(u32); }

void LayerActLayout::setupLayoutAction(u8 *work, const u8 *data) { setupAction(work, data); }

bool LayerActLayout::actcmd_notcmd01(const u8 *&cmd) {
  cmd += 4;
  return false;
}

bool LayerActLayout::actcmd_notcmd02(const u8 *&cmd) {
  cmd += 8;
  return false;
}

bool LayerActLayout::actcmd_notcmd03(const u8 *&cmd) {
  cmd += reinterpret_cast<const unknown004 *>(cmd)->unknown02 * 2 + 12;
  return false;
}

} // namespace layer
