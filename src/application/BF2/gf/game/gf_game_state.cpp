#include "gf/game/gf_game_state.h"

#include "fw/fw_update_info.h"
#include "gf/game/gf_game_env.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/gf_info.h"
#include "gf/object/component/gf_com_transform.h"

namespace gf {

void StateGfInitialize::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(0); }

void GfGameState::setStateFlg(u32 flags) { get()->unknown80 = flags; }

void StateGfInitialize::leave(GfGameManager *, ai::State *) {}

void StateGfInitialize::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateGfDestroy::enter(GfGameManager *, ai::State *previous) {
  GfGameState::setStateFlg(0);
  GfEvent::callGameState(GF_STATE(previous->stateID), GF_STATE(stateID));
}

void StateGfDestroy::leave(GfGameManager *, ai::State *) {}

void StateGfDestroy::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateControl::enter(GfGameManager *, ai::State *previous) {
  GfGameState::setStateFlg(GF_STATE_FLAG_CONTROL);
  GfGameUtil::execDevelopLevelUp();
  GfEvent::callGameState(GF_STATE(previous->stateID), GF_STATE(stateID));
}

void StateControl::leave(GfGameManager *, ai::State *) {}

void StateControl::update(GfGameManager *, const fw::UpdateInfo &) {
  GfComTransform *transform = GfGameParty::getLeaderTransform();
  if (transform != nullptr) {
    GfGameEnv::sendPlayerPositionToRender(transform->getPosition());
  }
}

void StateMapjump::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_MAPJUMP); }

void StateMapjump::leave(GfGameManager *, ai::State *) {}

void StateMapjump::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateMapjumpSkipTravel::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_MAPJUMP); }

void StateMapjumpSkipTravel::leave(GfGameManager *, ai::State *) {}

void StateMapjumpSkipTravel::update(GfGameManager *, const fw::UpdateInfo &) {}

void StatePlayerDead::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(0); }

void StatePlayerDead::leave(GfGameManager *, ai::State *) { GfGameState::setStateFlg(0); }

void StatePlayerDead::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateMenu::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_MENU | GF_STATE_FLAG_CONTROL); }

void StateMenu::leave(GfGameManager *, ai::State *) {}

void StateMenu::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateSalvage::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(0); }

void StateSalvage::leave(GfGameManager *, ai::State *) {}

void StateSalvage::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateCollect::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_COLLECT | GF_STATE_FLAG_CONTROL); }

void StateCollect::leave(GfGameManager *, ai::State *) {}

void StateCollect::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateFieldTbox::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_FIELD_TBOX | GF_STATE_FLAG_CONTROL); }

void StateFieldTbox::leave(GfGameManager *, ai::State *) {}

void StateFieldTbox::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateMapGimmick::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_MAP_GIMMICK | GF_STATE_FLAG_CONTROL); }

void StateMapGimmick::leave(GfGameManager *, ai::State *) {}

void StateGrave::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_MAP_GIMMICK | GF_STATE_FLAG_CONTROL); }

void StateGrave::leave(GfGameManager *, ai::State *) {}

void StateJump::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_JUMP | GF_STATE_FLAG_CONTROL); }

void StateJump::leave(GfGameManager *, ai::State *) {}

void StateWarp::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_WARP | GF_STATE_FLAG_CONTROL); }

void StateWarp::leave(GfGameManager *, ai::State *) {}

void StateGmkTutorial::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_GMK_TUTORIAL | GF_STATE_FLAG_CONTROL); }

void StateGmkTutorial::leave(GfGameManager *, ai::State *) {}

void StateGmkCamera::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_GMK_CAMERA | GF_STATE_FLAG_CONTROL); }

void StateGmkCamera::leave(GfGameManager *, ai::State *) {}

void StateEvent::enter(GfGameManager *, ai::State *previous) {
  GfGameState::setStateFlg(GF_STATE_FLAG_EVENT);
  GfEvent::callGameState(GF_STATE(previous->stateID), GF_STATE(stateID));
}

void StateEvent::leave(GfGameManager *, ai::State *) {}

void StateEvent::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateTalk::enter(GfGameManager *, ai::State *previous) {
  GfGameState::setStateFlg(GF_STATE_FLAG_TALK | GF_STATE_FLAG_CONTROL);
  GfEvent::callGameState(GF_STATE(previous->stateID), GF_STATE(stateID));
}

void StateTalk::leave(GfGameManager *, ai::State *) {}

void StateTalk::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateLeaveBattle::enter(GfGameManager *, ai::State *) { GfGameManager::enterBattle(false); }

void StateLeaveBattle::leave(GfGameManager *, ai::State *) {}

void StateLeaveBattle::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateGimmickTask::enter(GfGameManager *, ai::State *) { GfGameManager::enterBattle(false); }

void StateGimmickTask::leave(GfGameManager *, ai::State *) {}

void StateGimmickTask::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateChainAttack::enter(GfGameManager *, ai::State *) {}

void StateChainAttack::leave(GfGameManager *, ai::State *) {}

void StateChainAttack::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateArtsMovie::enter(GfGameManager *, ai::State *) {}

void StateArtsMovie::leave(GfGameManager *, ai::State *) {}

void StateArtsMovie::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateResetBlade::enter(GfGameManager *, ai::State *) {}

void StateResetBlade::leave(GfGameManager *, ai::State *) {}

void StateResetBlade::update(GfGameManager *, const fw::UpdateInfo &) {}

GfGameState::GfGameState() : unknown08(getAllocator(ALLOCATOR_DEFAULT)), unknown80(0), unknown84(GF_STATE_CONTROL), unknown88(0), unknown8c(0.0f) {}

GfGameState::~GfGameState() {}

void GfGameState::build(const GfSetupParam &) {
  // __LINE__ must be 434 as in the original file: its value changes the instruction order.
#line 434
  GfGameState *gameState = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameState();
  gameState->unknown08.beginSetup(gameState, GF_STATE_MAX);
  gameState->unknown08.registerState<StateGfInitialize>(GF_STATE_INITIALIZE);
  gameState->unknown08.registerState<StateGfDestroy>(GF_STATE_DESTROY);
  gameState->unknown08.registerState<StateControl>(GF_STATE_CONTROL);
  gameState->unknown08.registerState<StateMapjump>(GF_STATE_MAPJUMP);
  gameState->unknown08.registerState<StateMapjump>(GF_STATE_MAPJUMP_SKIP_TRAVEL);
  gameState->unknown08.registerState<StatePlayerDead>(GF_STATE_PLAYER_DEAD);
  gameState->unknown08.registerState<StateMenu>(GF_STATE_MENU);
  gameState->unknown08.registerState<StateWaitEvent>(GF_STATE_WAIT_EVENT);
  gameState->unknown08.registerState<StateSalvage>(GF_STATE_SALVAGE);
  gameState->unknown08.registerState<StateCollect>(GF_STATE_COLLECT);
  gameState->unknown08.registerState<StateFieldTbox>(GF_STATE_FIELD_TBOX);
  gameState->unknown08.registerState<StateMapGimmick>(GF_STATE_MAP_GIMMICK);
  gameState->unknown08.registerState<StateGrave>(GF_STATE_GRAVE);
  gameState->unknown08.registerState<StateJump>(GF_STATE_JUMP);
  gameState->unknown08.registerState<StateWarp>(GF_STATE_WARP);
  gameState->unknown08.registerState<StateGmkTutorial>(GF_STATE_GMK_TUTORIAL);
  gameState->unknown08.registerState<StateGmkCamera>(GF_STATE_GMK_CAMERA);
  gameState->unknown08.registerState<StateEvent>(GF_STATE_EVENT);
  gameState->unknown08.registerState<StateTalk>(GF_STATE_TALK);
  gameState->unknown08.registerState<StateGimmickTask>(GF_STATE_GIMMICK_TASK);
  gameState->unknown08.registerState<StateChainAttack>(GF_STATE_CHAIN_ATTACK);
  gameState->unknown08.registerState<StateArtsMovie>(GF_STATE_ARTS_MOVIE);
  gameState->unknown08.registerState<StateResetBlade>(GF_STATE_RESET_BLADE);
  gameState->unknown08.endSetup();
  gameState->unknown08.setState(GF_STATE_INITIALIZE);
}

void GfGameState::destroy() {
  GfGameState *gameState = get();
  gameState->unknown08.cleanup();
  delete gameState;
}

void GfGameState::update(const fw::UpdateInfo &info) {
  GfGameState *gameState = get();
  if (gameState != nullptr) {
    gameState->unknown8c += info.deltaTime;
    gameState->unknown08.update(&info);
  }
}

void GfGameState::clear() {
  if (get() != nullptr) {
    get()->unknown8c = 0.0f;
  }
}

bool GfGameState::test(u32 flags) { return (get()->unknown80 & flags) != 0; }

GF_STATE GfGameState::getState() { return GF_STATE(get()->unknown08.getState()->stateID); }

const char *GfGameState::getStateName() {
  if (get() != nullptr) {
    return get()->unknown08.getState()->getName();
  }
  return "";
}

GF_STATE GfGameState::getStateReserve() { return get()->unknown84; }

u32 GfGameState::getCountStateReserve() { return get()->unknown88; }

void GfGameState::setStateReserve(GF_STATE state) {
  if (state != 0) {
    GfGameState *gameState = get();
    gameState->unknown84 = state;
    gameState->unknown88 = GfInfo::getFrameCount32();
  }
}

void GfGameState::setState(GF_STATE state, bool isForce) {
  GfGameState *gameState = get();
  if (!isForce) {
    gameState->unknown84 = GF_STATE_CONTROL;
    gameState->unknown88 = GfInfo::getFrameCount32();
  }
  gameState->unknown08.setState(state);
  gameState->unknown8c = 0.0f;
}

} // namespace gf
