#pragma once
#include <stddef.h>

#include "ai/ai_state.h"
#include "gf/field/gf_real_time.h"
#include "gf/gf_state.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace tl {

class TitleMain;

class TitleStateDebugSaveContinue : public ai::State {
  GF_STATE_CLASS(TitleStateDebugSaveContinue, TitleMain)
  static const int SLOT_UNKNOWN_21 = 21; // Inferred role: number of save slots, signed as the game compares it with the selected slot (updateButton: cmp w9, #19 and b.gt); original name unknown.

  // Inferred role: bits of the control pad read by updateButton; original names unknown.
  enum {
    PAD_BUTTON_UNKNOWN_1 = 1 << 1,
    PAD_BUTTON_UNKNOWN_2 = 1 << 2,
    PAD_BUTTON_UNKNOWN_12 = 1 << 12,
    PAD_BUTTON_UNKNOWN_14 = 1 << 14,
  };

  // Inferred role: a save slot of the debug menu; original type name unknown.
  struct unknown001 {
    unknown001() : m_realTime() {}

    gf::RealTime m_realTime; // Inferred role: time the slot was saved; original member name unknown.
    bool unknown08;          // Inferred role: the slot exists; original member name unknown.
  };

  void enter(TitleMain *main, ai::State *previous);
  void leave(TitleMain *, ai::State *) {}
  bool updateCheck(TitleMain *main);
  bool updateButton(TitleMain *main);
  void renderSelectInfo(TitleMain *main);
  void update(TitleMain *main, const fw::UpdateInfo &info);

  unknown001 unknown18[SLOT_UNKNOWN_21]; // Inferred role: save slots; original member name unknown.
  int unknown168;                        // Inferred role: selected slot; original member name unknown.
  u32 unknown16c;                        // Inferred role: frames the confirm button is held; original member name unknown.
};

static_assert(sizeof(TitleStateDebugSaveContinue::unknown001) == 0x10, "");
static_assert(offsetof(TitleStateDebugSaveContinue, unknown18) == 0x18, "");
static_assert(offsetof(TitleStateDebugSaveContinue, unknown168) == 0x168, "");
static_assert(sizeof(TitleStateDebugSaveContinue) == 0x170, "");

} // namespace tl
