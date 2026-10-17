#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

enum {
  PAUSE_BIT_SYSTEM = 1 << 0,
  PAUSE_BIT_GAME = 1 << 1,
  PAUSE_BIT_EVENT_SOUND = 1 << 2,
  PAUSE_BIT_GAME_SOUND = 1 << 3,
  PAUSE_BIT_FIELD_TIME = 1 << 4,
  PAUSE_BIT_EVENT_SKIP = 1 << 9,
};

struct GfSetupParam;

class GfPause : public mm::mtl::PtrSingleton<GfPause> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update();
  static bool isPause(u32 pauseBits);
};

} // namespace gf
