#pragma once
#include "gf/event/gf_event.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

class GfSequentialPlay {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static bool isPlay();
  static void postUpdate(const fw::UpdateInfo &info);
  static bool isInnerState(GF_STATE state);
  static bool isInnerPause(u32 pauseBits);
};

} // namespace gf
