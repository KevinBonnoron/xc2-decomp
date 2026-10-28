#include "gmk/gmk_battle_lock.h"
#include "framework/effect/effect_manager.h"
#include "gf/data/gf_data_util.h"
#include "gf/game/gf_game_manager.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep

namespace gmk {

template bool TGmkList<GmkBattleLock, GmkBattleLock::BdatInfo, 1129075778u, 3u, GmkBattleLockGob>::initGmkBdatInfo(GmkBattleLock::BdatInfo &, int &, const AGmkBase &);

GmkType GmkBattleLock::getGmkType() const { return GMK_TYPE; }

bool GmkBattleLock::isValid() const { return unknown08.unknown00 != nullptr && unknown20.unknown08 != nullptr; }

void GmkBattleLock::create(const CreateInfo &info) { AGmkBase::create(info); }

void GmkBattleLock::debugDraw() const { isValid(); }

void GmkBattleLock::dispose() {
  disposeEffect(false);
  unknown50.dispose();
  AGmkBase::dispose();
}

void GmkBattleLock::disposeEffect(bool isFadeOut) {
  if (unknownc0 != 0) {
    if (isFadeOut) {
      int deadFlag = fw::EffectManager::get()->getDeadFlag(unknownc0);
      if (deadFlag == 0) {
        fw::EffectManager::get()->fadeOutDead(unknownc0, 5);
      } else {
        fw::EffectManager::get()->dead(unknownc0);
      }
    } else {
      fw::EffectManager::get()->remove(unknownc0);
    }
    unknownc0 = 0;
  }
}

void GmkBattleLock::update(f32 deltaTime) {
  debugUpdateMmf();
  if (isValid()) {
    if (unknownc4 > 0) {
      if (unknown50.unknown58 == nullptr && gf::GfGameManager::isEnableCreateBattleLock()) {
        createGmkCollision();
        createEffect();
      }
    } else if (unknown50.unknown58 != nullptr && (gf::GfDataUtil::getScenarioFlag() != SCENARIO_FLAG_KEEP_BATTLE_LOCK_IN_BATTLE || !gf::GfGameManager::isBattle())) {
      unknown50.dispose();
      disposeEffect(true);
    }
    if (unknownc0 != 0) {
      bool isDisp = !gf::GfGameManager::isPlayEvent();
      fw::EffectManager::get()->setDisp(unknownc0, isDisp);
    }
  }
}

} // namespace gmk
