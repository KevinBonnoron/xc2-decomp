#pragma once
#include "ai/ai_state.h"
#include "gf/gf_state.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace tl {

class TitleMain;

class TitleStateToTitle : public ai::State {
  GF_STATE_CLASS(TitleStateToTitle, TitleMain)
  void enter(TitleMain *, ai::State *) {}
  void leave(TitleMain *, ai::State *) {}
  void update(TitleMain *main, const fw::UpdateInfo &info);
};

static_assert(sizeof(TitleStateToTitle) == 0x18, "");

} // namespace tl
