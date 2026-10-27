#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

enum {
  PAUSE_BIT_SYSTEM = 1 << 0,
  PAUSE_BIT_GAME = 1 << 1,
  PAUSE_BIT_EVENT_SOUND = 1 << 2,
  PAUSE_BIT_GAME_SOUND = 1 << 3,
  PAUSE_BIT_FIELD_TIME = 1 << 4,
  PAUSE_BIT_EVENT = 1 << 5,
  PAUSE_BIT_MAIN_MENU = 1 << 6,
  PAUSE_BIT_EVENT_SKIP = 1 << 9,
};

struct GF_PAUSE_HANDLE;
struct GfSetupParam;

class GfPause : public mm::mtl::PtrSingleton<GfPause> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static GF_PAUSE_HANDLE *reqPause(u32 pauseBits);
  static void destroyHandle(GF_PAUSE_HANDLE *handle);
  static void update();
  static bool isPause(u32 pauseBits);
  static bool isInitialized();
  u64 createPauseHandleByIndex(u32 index);

  u8 _08[0xe58 - 0x08];
  u32 unknowne58; // Inferred role: current pause bits; original member name unknown.
  u8 _e5c[0xe60 - 0xe5c];
  u32 unknowne60;  // Inferred role: pause handle serial; original member name unknown.
  bool unknowne64; // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(GfPause, unknowne58) == 0xe58, "");
static_assert(offsetof(GfPause, unknowne60) == 0xe60, "");
static_assert(offsetof(GfPause, unknowne64) == 0xe64, "");

} // namespace gf
