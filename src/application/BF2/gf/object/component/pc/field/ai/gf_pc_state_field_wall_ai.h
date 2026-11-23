#pragma once
#include "gf/gf_state.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"

namespace ai {
class State;
} // namespace ai

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {
namespace pc {

class BlackBoardField;

// Layout evidence: TaskFieldWallPrepare::onCreate (0x71005450dc) passes the member at 0x40 of the task as the owner of the
// state machine, and the StateFieldWallAi* states read the black board through its first member.
struct WallAiContextField {
  BlackBoardField *m_blackBoardField; // Inferred role: black board during a state change or an update; original member name unknown.
};

static_assert(sizeof(WallAiContextField) == 0x08, "");

// The game emits the vtables and the inline virtuals of the StateFieldWallAi* states in gf_pc_ai_wall_task_field.cpp
// (0x7100545c0c), and their enter, update and setNavi bodies in another file (0x7100546800), just before the
// AgentUtilField functions.
class StateFieldWallAiWait : public GfStateBase {
  GF_STATE_CLASS(StateFieldWallAiWait, WallAiContextField)
  void enter(WallAiContextField *context, ai::State *previous) {}
  void leave(WallAiContextField *context, ai::State *next) {}
  void update(WallAiContextField *context, const fw::UpdateInfo &info);
};

static_assert(sizeof(StateFieldWallAiWait) == 0x18, "");

class StateFieldWallAiPrepare : public GfStateBase {
  GF_STATE_CLASS(StateFieldWallAiPrepare, WallAiContextField)
  void enter(WallAiContextField *context, ai::State *previous);
  void leave(WallAiContextField *context, ai::State *next) {}
  void update(WallAiContextField *context, const fw::UpdateInfo &info);
  void setNavi(WallAiContextField *context);
};

static_assert(sizeof(StateFieldWallAiPrepare) == 0x18, "");

class StateFieldWallAiAdsorption : public GfStateBase {
  GF_STATE_CLASS(StateFieldWallAiAdsorption, WallAiContextField)
  void enter(WallAiContextField *context, ai::State *previous);
  void leave(WallAiContextField *context, ai::State *next);
  void update(WallAiContextField *context, const fw::UpdateInfo &info);
  void setNavi(WallAiContextField *context);
};

static_assert(sizeof(StateFieldWallAiAdsorption) == 0x18, "");

} // namespace pc
} // namespace gf
