#pragma once
#include <stddef.h>

#include "ai/ai_state.h"
#include "gf/gf_state.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace tl {

class TitleMain;

class TitleStatePlayEvent : public ai::State {
  GF_STATE_CLASS(TitleStatePlayEvent, TitleMain)
  void enter(TitleMain *main, ai::State *previous);
  void leave(TitleMain *main, ai::State *next);
  void update(TitleMain *main, const fw::UpdateInfo &info);

  bool unknown18; // Inferred role: the event creates a blade; original member name unknown.
};

static_assert(offsetof(TitleStatePlayEvent, unknown18) == 0x18, "");
static_assert(sizeof(TitleStatePlayEvent) == 0x20, "");

} // namespace tl
