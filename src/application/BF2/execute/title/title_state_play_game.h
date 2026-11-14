#pragma once
#include <stddef.h>

#include "ai/ai_state.h"
#include "gf/event/gf_event.h"
#include "gf/gf_state.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace tl {

class TitleMain;

class TitleStatePlayGame : public ai::State, public gf::IGfEvent {
  GF_STATE_CLASS(TitleStatePlayGame, TitleMain)
  void gevPlayEvent(gf::GEV event, u32 value) override;
  void enter(TitleMain *main, ai::State *previous);
  void leave(TitleMain *main, ai::State *next);
  void update(TitleMain *main, const fw::UpdateInfo &info);

  int unknown20; // Inferred role: event state, set by gevPlayEvent; original member name unknown.
};

static_assert(offsetof(TitleStatePlayGame, unknown20) == 0x20, "");
static_assert(sizeof(TitleStatePlayGame) == 0x28, "");

} // namespace tl
