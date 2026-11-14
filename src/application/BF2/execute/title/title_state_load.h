#pragma once
#include <stddef.h>

#include "ai/ai_state.h"
#include "gf/gf_state.h"
#include "ml/time_count.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace tl {

class TitleMain;

class TitleStateLoad : public ai::State {
  GF_STATE_CLASS(TitleStateLoad, TitleMain)
  TitleStateLoad() { unknown18.start(); }
  void enter(TitleMain *, ai::State *) {}
  void leave(TitleMain *, ai::State *) {}
  void update(TitleMain *main, const fw::UpdateInfo &info);

  ml::TimeCount unknown18; // Inferred role: time since the state started; original member name unknown.
};

static_assert(offsetof(TitleStateLoad, unknown18) == 0x18, "");
static_assert(sizeof(TitleStateLoad) == 0x20, "");

} // namespace tl
