#pragma once
#include "gf/event/gf_event.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

enum {
  GF_STATE_FLAG_CONTROL = 0x1,
  GF_STATE_FLAG_EVENT = 0x2,
  GF_STATE_FLAG_TALK = 0x20,
};

class GfGameState {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  static void clear();
  static bool test(u32 flags);
  static GF_STATE getState();
  static GF_STATE getStateReserve();
  static void setState(GF_STATE state, bool isForce);
};

} // namespace gf
