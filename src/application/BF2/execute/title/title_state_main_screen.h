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

class TitleStateMainScreen : public ai::State, public gf::IGfEvent {
  GF_STATE_CLASS(TitleStateMainScreen, TitleMain)
  void gevPlayEvent(gf::GEV event, u32 value) override;
  bool checkLoadSlotForDebug(TitleMain *main);
  bool checkLoadFileForDebug(TitleMain *main);
  bool loadSaveDataForTitle(TitleMain *main);
  bool checkReturnEvent(TitleMain *main);
  void playTitleEvent(TitleMain *main);
  bool dispTitleMenu(TitleMain *main, bool isPlayEvent);
  bool checkMenuResult(TitleMain *main);
  bool waitTitleMenuDestroy(TitleMain *main);
  void enter(TitleMain *main, ai::State *previous);
  void leave(TitleMain *main, ai::State *next);
  void update(TitleMain *main, const fw::UpdateInfo &info);

  int unknown20; // Inferred role: event state, set by gevPlayEvent; original member name unknown.
};

static_assert(offsetof(TitleStateMainScreen, unknown20) == 0x20, "");
static_assert(sizeof(TitleStateMainScreen) == 0x28, "");

} // namespace tl
