#pragma once
#include "ai/ai_state.h"
#include "ai/ai_state_fsm.h"
#include "gf/event/gf_event.h"
#include "gf/gf_state.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

class GfGameManager;
struct GfSetupParam;

enum {
  GF_STATE_FLAG_CONTROL = 0x1,
  GF_STATE_FLAG_EVENT = 0x2,
  GF_STATE_FLAG_MAPJUMP = 0x4,
  GF_STATE_FLAG_MENU = 0x8,
  GF_STATE_FLAG_TALK = 0x20,
  GF_STATE_FLAG_COLLECT = 0x40,
  GF_STATE_FLAG_FIELD_TBOX = 0x80,
  GF_STATE_FLAG_MAP_GIMMICK = 0x200,
  GF_STATE_FLAG_JUMP = 0x400,
  GF_STATE_FLAG_WARP = 0x800,
  GF_STATE_FLAG_GMK_TUTORIAL = 0x2000,
  GF_STATE_FLAG_GMK_CAMERA = 0x4000,
};

class StateGfInitialize : public ai::State {
  GF_STATE_CLASS(StateGfInitialize, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateGfDestroy : public ai::State {
  GF_STATE_CLASS(StateGfDestroy, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateControl : public ai::State {
  GF_STATE_CLASS(StateControl, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateMapjump : public ai::State {
  GF_STATE_CLASS(StateMapjump, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateMapjumpSkipTravel : public ai::State {
  GF_STATE_CLASS(StateMapjumpSkipTravel, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StatePlayerDead : public ai::State {
  GF_STATE_CLASS(StatePlayerDead, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateMenu : public ai::State {
  GF_STATE_CLASS(StateMenu, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateWaitEvent : public ai::State {
  GF_STATE_CLASS(StateWaitEvent, GfGameManager)
  void enter(GfGameManager *, ai::State *) {}
  void leave(GfGameManager *, ai::State *) {}
  void update(GfGameManager *, const fw::UpdateInfo &) {}
};

class StateSalvage : public ai::State {
  GF_STATE_CLASS(StateSalvage, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateCollect : public ai::State {
  GF_STATE_CLASS(StateCollect, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateFieldTbox : public ai::State {
  GF_STATE_CLASS(StateFieldTbox, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateMapGimmick : public ai::State {
  GF_STATE_CLASS(StateMapGimmick, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *, const fw::UpdateInfo &) {}
};

class StateGrave : public ai::State {
  GF_STATE_CLASS(StateGrave, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *, const fw::UpdateInfo &) {}
};

class StateJump : public ai::State {
  GF_STATE_CLASS(StateJump, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *, const fw::UpdateInfo &) {}
};

class StateWarp : public ai::State {
  GF_STATE_CLASS(StateWarp, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *, const fw::UpdateInfo &) {}
};

class StateGmkTutorial : public ai::State {
  GF_STATE_CLASS(StateGmkTutorial, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *, const fw::UpdateInfo &) {}
};

class StateGmkCamera : public ai::State {
  GF_STATE_CLASS(StateGmkCamera, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *, const fw::UpdateInfo &) {}
};

class StateEvent : public ai::State {
  GF_STATE_CLASS(StateEvent, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateTalk : public ai::State {
  GF_STATE_CLASS(StateTalk, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateLeaveBattle : public ai::State {
  GF_STATE_CLASS(StateLeaveBattle, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateGimmickTask : public ai::State {
  GF_STATE_CLASS(StateGimmickTask, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateChainAttack : public ai::State {
  GF_STATE_CLASS(StateChainAttack, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateArtsMovie : public ai::State {
  GF_STATE_CLASS(StateArtsMovie, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateResetBlade : public ai::State {
  GF_STATE_CLASS(StateResetBlade, GfGameManager)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class GfGameState : public mm::mtl::PtrSingleton<GfGameState> {
public:
  static void setStateFlg(u32 flags);
  GfGameState();
  ~GfGameState();
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  static void clear();
  static bool test(u32 flags);
  static GF_STATE getState();
  static const char *getStateName();
  static GF_STATE getStateReserve();
  static u32 getCountStateReserve();
  static void setStateReserve(GF_STATE state);
  static void setState(GF_STATE state, bool isForce);

private:
  ai::Fsm fsm;
  u32 stateFlg;
  GF_STATE stateReserve;
  u32 countStateReserve;
  f32 stateTime;
};

static_assert(sizeof(GfGameState) == 0x90, "");

} // namespace gf
