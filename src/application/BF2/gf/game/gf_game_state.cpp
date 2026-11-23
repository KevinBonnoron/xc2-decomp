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

void GfGameState::setStateFlg(u32 flags) { get()->m_stateFlg = flags; }

void StateGfInitialize::leave(GfGameManager *, ai::State *) {}

void StateGfInitialize::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateGfDestroy::enter(GfGameManager *, ai::State *previous) {
  GfGameState::setStateFlg(0);
  GfEvent::callGameState(GF_STATE(previous->m_state), GF_STATE(m_state));
}

void StateGfDestroy::leave(GfGameManager *, ai::State *) {}

void StateGfDestroy::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateControl::enter(GfGameManager *, ai::State *previous) {
  GfGameState::setStateFlg(GF_STATE_FLAG_UNKNOWN_0);
  GfGameUtil::execDevelopLevelUp();
  GfEvent::callGameState(GF_STATE(previous->m_state), GF_STATE(m_state));
}

void StateControl::leave(GfGameManager *, ai::State *) {}

void StateControl::update(GfGameManager *, const fw::UpdateInfo &) {
  GfComTransform *transform = GfGameParty::getLeaderTransform();
  if (transform != nullptr) {
    GfGameEnv::sendPlayerPositionToRender(transform->getPosition());
  }
}

void StateMapjump::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_UNKNOWN_2); }

void StateMapjump::leave(GfGameManager *, ai::State *) {}

void StateMapjump::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateMapjumpSkipTravel::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_UNKNOWN_2); }

void StateMapjumpSkipTravel::leave(GfGameManager *, ai::State *) {}

void StateMapjumpSkipTravel::update(GfGameManager *, const fw::UpdateInfo &) {}

void StatePlayerDead::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(0); }

void StatePlayerDead::leave(GfGameManager *, ai::State *) { GfGameState::setStateFlg(0); }

void StatePlayerDead::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateMenu::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_UNKNOWN_3 | GF_STATE_FLAG_UNKNOWN_0); }

void StateMenu::leave(GfGameManager *, ai::State *) {}

void StateMenu::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateSalvage::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(0); }

void StateSalvage::leave(GfGameManager *, ai::State *) {}

void StateSalvage::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateCollect::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_UNKNOWN_6 | GF_STATE_FLAG_UNKNOWN_0); }

void StateCollect::leave(GfGameManager *, ai::State *) {}

void StateCollect::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateFieldTbox::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_UNKNOWN_7 | GF_STATE_FLAG_UNKNOWN_0); }

void StateFieldTbox::leave(GfGameManager *, ai::State *) {}

void StateFieldTbox::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateMapGimmick::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_UNKNOWN_9 | GF_STATE_FLAG_UNKNOWN_0); }

void StateMapGimmick::leave(GfGameManager *, ai::State *) {}

void StateGrave::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_UNKNOWN_9 | GF_STATE_FLAG_UNKNOWN_0); }

void StateGrave::leave(GfGameManager *, ai::State *) {}

void StateJump::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_UNKNOWN_10 | GF_STATE_FLAG_UNKNOWN_0); }

void StateJump::leave(GfGameManager *, ai::State *) {}

void StateWarp::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_UNKNOWN_11 | GF_STATE_FLAG_UNKNOWN_0); }

void StateWarp::leave(GfGameManager *, ai::State *) {}

void StateGmkTutorial::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_UNKNOWN_13 | GF_STATE_FLAG_UNKNOWN_0); }

void StateGmkTutorial::leave(GfGameManager *, ai::State *) {}

void StateGmkCamera::enter(GfGameManager *, ai::State *) { GfGameState::setStateFlg(GF_STATE_FLAG_UNKNOWN_14 | GF_STATE_FLAG_UNKNOWN_0); }

void StateGmkCamera::leave(GfGameManager *, ai::State *) {}

void StateEvent::enter(GfGameManager *, ai::State *previous) {
  GfGameState::setStateFlg(GF_STATE_FLAG_UNKNOWN_1);
  GfEvent::callGameState(GF_STATE(previous->m_state), GF_STATE(m_state));
}

void StateEvent::leave(GfGameManager *, ai::State *) {}

void StateEvent::update(GfGameManager *, const fw::UpdateInfo &) {}

void StateTalk::enter(GfGameManager *, ai::State *previous) {
  GfGameState::setStateFlg(GF_STATE_FLAG_UNKNOWN_5 | GF_STATE_FLAG_UNKNOWN_0);
  GfEvent::callGameState(GF_STATE(previous->m_state), GF_STATE(m_state));
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

GfGameState::GfGameState() : m_fsm(getAllocator(ALLOCATOR_UNKNOWN_0)), m_stateFlg(0), m_stateReserve(GF_STATE_UNKNOWN_3), m_countStateReserve(0), unknown8c(0.0f) {}

GfGameState::~GfGameState() {}

void GfGameState::build(const GfSetupParam &) {
  // __LINE__ must be 434 as in the original file: its value changes the instruction order.
#line 434
  GfGameState *gameState = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameState();
  gameState->m_fsm.beginSetup(gameState, GF_STATE_UNKNOWN_25);
  gameState->m_fsm.registerState<StateGfInitialize>(GF_STATE_UNKNOWN_1);
  gameState->m_fsm.registerState<StateGfDestroy>(GF_STATE_UNKNOWN_2);
  gameState->m_fsm.registerState<StateControl>(GF_STATE_UNKNOWN_3);
  gameState->m_fsm.registerState<StateMapjump>(GF_STATE_UNKNOWN_8);
  gameState->m_fsm.registerState<StateMapjump>(GF_STATE_UNKNOWN_9);
  gameState->m_fsm.registerState<StatePlayerDead>(GF_STATE_UNKNOWN_10);
  gameState->m_fsm.registerState<StateMenu>(GF_STATE_UNKNOWN_6);
  gameState->m_fsm.registerState<StateWaitEvent>(GF_STATE_UNKNOWN_7);
  gameState->m_fsm.registerState<StateSalvage>(GF_STATE_UNKNOWN_11);
  gameState->m_fsm.registerState<StateCollect>(GF_STATE_UNKNOWN_12);
  gameState->m_fsm.registerState<StateFieldTbox>(GF_STATE_UNKNOWN_13);
  gameState->m_fsm.registerState<StateMapGimmick>(GF_STATE_UNKNOWN_14);
  gameState->m_fsm.registerState<StateGrave>(GF_STATE_UNKNOWN_15);
  gameState->m_fsm.registerState<StateJump>(GF_STATE_UNKNOWN_16);
  gameState->m_fsm.registerState<StateWarp>(GF_STATE_UNKNOWN_17);
  gameState->m_fsm.registerState<StateGmkTutorial>(GF_STATE_UNKNOWN_18);
  gameState->m_fsm.registerState<StateGmkCamera>(GF_STATE_UNKNOWN_19);
  gameState->m_fsm.registerState<StateEvent>(GF_STATE_UNKNOWN_20);
  gameState->m_fsm.registerState<StateTalk>(GF_STATE_UNKNOWN_4);
  gameState->m_fsm.registerState<StateGimmickTask>(GF_STATE_UNKNOWN_21);
  gameState->m_fsm.registerState<StateChainAttack>(GF_STATE_UNKNOWN_22);
  gameState->m_fsm.registerState<StateArtsMovie>(GF_STATE_UNKNOWN_23);
  gameState->m_fsm.registerState<StateResetBlade>(GF_STATE_UNKNOWN_24);
  gameState->m_fsm.endSetup();
  gameState->m_fsm.setState(GF_STATE_UNKNOWN_1);
}

void GfGameState::destroy() {
  GfGameState *gameState = get();
  gameState->m_fsm.cleanup();
  delete gameState;
}

void GfGameState::update(const fw::UpdateInfo &info) {
  GfGameState *gameState = get();
  if (gameState != nullptr) {
    gameState->unknown8c += info.unknown04;
    gameState->m_fsm.update(&info);
  }
}

void GfGameState::clear() {
  if (get() != nullptr) {
    get()->unknown8c = 0.0f;
  }
}

bool GfGameState::test(u32 flags) { return (get()->m_stateFlg & flags) != 0; }

GF_STATE GfGameState::getState() { return GF_STATE(get()->m_fsm.getState()->m_state); }

const char *GfGameState::getStateName() {
  if (get() != nullptr) {
    return get()->m_fsm.getState()->getName();
  }
  return "";
}

GF_STATE GfGameState::getStateReserve() { return get()->m_stateReserve; }

u32 GfGameState::getCountStateReserve() { return get()->m_countStateReserve; }

void GfGameState::setStateReserve(GF_STATE state) {
  if (state != 0) {
    GfGameState *gameState = get();
    gameState->m_stateReserve = state;
    gameState->m_countStateReserve = GfInfo::getFrameCount32();
  }
}

void GfGameState::setState(GF_STATE state, bool isForce) {
  GfGameState *gameState = get();
  if (!isForce) {
    gameState->m_stateReserve = GF_STATE_UNKNOWN_3;
    gameState->m_countStateReserve = GfInfo::getFrameCount32();
  }
  gameState->m_fsm.setState(state);
  gameState->unknown8c = 0.0f;
}

} // namespace gf
