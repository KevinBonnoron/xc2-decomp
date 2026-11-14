#pragma once
#include "ai/ai_state.h"
#include "gf/gf_state.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace tl {

class TitleMain;

class TitleStateSelectEvent : public ai::State {
  GF_STATE_CLASS(TitleStateSelectEvent, TitleMain)
  void enter(TitleMain *main, ai::State *previous);
  void leave(TitleMain *, ai::State *) {}
  void update(TitleMain *main, const fw::UpdateInfo &info);
  bool eventMenuDisp(TitleMain *main);
  bool eventMenuResult(TitleMain *main);
  bool eventMenuWaitFadeout(TitleMain *main);
};

static_assert(sizeof(TitleStateSelectEvent) == 0x18, "");

} // namespace tl
