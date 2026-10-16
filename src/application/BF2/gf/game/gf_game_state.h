#pragma once
#include <new>

#include "ai/ai_state.h"
#include "ai/ai_state_fsm.h"
#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

class GfGameManager;
struct GfSetupParam;
class StateArtsMovie;
class StateChainAttack;
class StateCollect;
class StateControl;
class StateEvent;
class StateFieldTbox;
class StateGfDestroy;
class StateGfInitialize;
class StateGimmickTask;
class StateGmkCamera;
class StateGmkTutorial;
class StateGrave;
class StateJump;
class StateLeaveBattle;
class StateMapGimmick;
class StateMapjump;
class StateMapjumpSkipTravel;
class StateMenu;
class StatePlayerDead;
class StateResetBlade;
class StateSalvage;
class StateTalk;
class StateWaitEvent;
class StateWarp;

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

#define GF_GAME_STATE(name)                                                                                                                          \
public:                                                                                                                                              \
  static ai::State *create(void *buffer) { return new (buffer) name(); }                                                                             \
  const char *getName() const override { return #name; }                                                                                             \
  void onEnter(void *owner, ai::State *previous) override { enter(static_cast<GfGameManager *>(owner), previous); }                                  \
  void onLeave(void *owner, ai::State *next) override { leave(static_cast<GfGameManager *>(owner), next); }                                          \
  void onStep(void *owner, const void *param) override { update(static_cast<GfGameManager *>(owner), *static_cast<const fw::UpdateInfo *>(param)); }

class StateGfInitialize : public ai::State {
  GF_GAME_STATE(StateGfInitialize)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateGfDestroy : public ai::State {
  GF_GAME_STATE(StateGfDestroy)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateControl : public ai::State {
  GF_GAME_STATE(StateControl)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateMapjump : public ai::State {
  GF_GAME_STATE(StateMapjump)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateMapjumpSkipTravel : public ai::State {
  GF_GAME_STATE(StateMapjumpSkipTravel)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StatePlayerDead : public ai::State {
  GF_GAME_STATE(StatePlayerDead)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateMenu : public ai::State {
  GF_GAME_STATE(StateMenu)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateWaitEvent : public ai::State {
  GF_GAME_STATE(StateWaitEvent)
  void enter(GfGameManager *, ai::State *) {}
  void leave(GfGameManager *, ai::State *) {}
  void update(GfGameManager *, const fw::UpdateInfo &) {}
};

class StateSalvage : public ai::State {
  GF_GAME_STATE(StateSalvage)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateCollect : public ai::State {
  GF_GAME_STATE(StateCollect)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateFieldTbox : public ai::State {
  GF_GAME_STATE(StateFieldTbox)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateMapGimmick : public ai::State {
  GF_GAME_STATE(StateMapGimmick)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *, const fw::UpdateInfo &) {}
};

class StateGrave : public ai::State {
  GF_GAME_STATE(StateGrave)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *, const fw::UpdateInfo &) {}
};

class StateJump : public ai::State {
  GF_GAME_STATE(StateJump)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *, const fw::UpdateInfo &) {}
};

class StateWarp : public ai::State {
  GF_GAME_STATE(StateWarp)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *, const fw::UpdateInfo &) {}
};

class StateGmkTutorial : public ai::State {
  GF_GAME_STATE(StateGmkTutorial)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *, const fw::UpdateInfo &) {}
};

class StateGmkCamera : public ai::State {
  GF_GAME_STATE(StateGmkCamera)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *, const fw::UpdateInfo &) {}
};

class StateEvent : public ai::State {
  GF_GAME_STATE(StateEvent)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateTalk : public ai::State {
  GF_GAME_STATE(StateTalk)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateLeaveBattle : public ai::State {
  GF_GAME_STATE(StateLeaveBattle)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateGimmickTask : public ai::State {
  GF_GAME_STATE(StateGimmickTask)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateChainAttack : public ai::State {
  GF_GAME_STATE(StateChainAttack)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateArtsMovie : public ai::State {
  GF_GAME_STATE(StateArtsMovie)
  void enter(GfGameManager *manager, ai::State *previous);
  void leave(GfGameManager *manager, ai::State *next);
  void update(GfGameManager *manager, const fw::UpdateInfo &info);
};

class StateResetBlade : public ai::State {
  GF_GAME_STATE(StateResetBlade)
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
