#pragma once
#include "ai/ai_state.h"
#include "gf/gf_state.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace tl {

class TitleMain;

class TitleStateSelectOption : public ai::State {
  GF_STATE_CLASS(TitleStateSelectOption, TitleMain)
  void enter(TitleMain *main, ai::State *previous);
  void leave(TitleMain *, ai::State *) {}
  void update(TitleMain *main, const fw::UpdateInfo &info);
  bool optionMenuDisp(TitleMain *main);
  bool optionMenuResult(TitleMain *main);
  bool optionMenuWaitFadeout(TitleMain *main);
};

static_assert(sizeof(TitleStateSelectOption) == 0x18, "");

} // namespace tl
