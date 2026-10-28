#include "gf/field/gf_field_bgm.h"

#include <string.h>

#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_maplist.h"
#include "gf/event/gf_event.h"
#include "gf/game/event/gf_evt_bgm.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_scene.h"
#include "gf/gf_manager.h"
#include "gf/gf_pause.h"
#include "mm_mtl/delegate.h" // IWYU pragma: keep

namespace gf {

BGMCOND::BGMCOND() : unknown00(0), unknown0c(0), unknown10(0), unknown11(0), unknown58(0) {}

void BGMCOND::clear() {
  if (!unknown14.empty()) {
    unknown14 = "";
  }
  if (unknown04.isValid()) {
    unknown04.clear();
  }
  unknown00 = 0;
  unknown10 = 0;
  unknown11 = 0;
  unknown0c = 0;
}

void BGMCOND::copyPlayInfo(const BGMCOND &src) {
  unknown11 = src.unknown11;
  unknown0c = src.unknown0c;
  unknown10 = src.unknown10;
  unknown04 = src.unknown04;
  unknown14 = src.unknown14;
  unknown00 = src.unknown00;
}

bool BGMCOND::isInvalidBgm() const { return !unknown04.isValid(); }

bool BGMCOND::isInvalidPlay() const { return !unknown04.isValid() && unknown11 == 0; }

bool BGMCOND::isSilentPlay() const { return strcmp(unknown14.c_str(), "SilentBgm") == 0; }

namespace _gffsn {
bool s_bStopBGM;

// Inferred role: bgm condition ids of the field bgm; original name unknown.
static const u16 unknown001[] = {2, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 45, 46, 47, 48};

bool isFieldBgmList(u32 id) {
  for (u32 i = 0; i < sizeof(unknown001) / sizeof(unknown001[0]); i++) {
    if (unknown001[i] == id) {
      return true;
    }
  }
  return false;
}

f32 bgmvolControlFade(const fw::UpdateInfo &info, f32 time, bool isFadeOut) {
  if (time < 1e-6f) {
    if (isFadeOut) {
      return -1.0f;
    }
    return 1.0f;
  }
  if (isFadeOut) {
    return -(info.unknown04 / time);
  }
  return info.unknown04 / time;
}

f32 bgmvolControlMulti(f32 volume, bool isEnable) {
  if (!isEnable) {
    volume = 1.0f;
  }
  return volume;
}

f32 bgmvolMultiWeather(f32, f32, f32 volume) { return bgmvolControlMulti(volume, GfGameManager::isWeatherSE()); }

f32 bgmvolMultiMenuPause(f32, f32, f32 volume) { return bgmvolControlMulti(volume, GfPause::isPause(4) && GfGameManager::isFullScreenMenu()); }

f32 bgmvolMultiTalkPause(f32, f32, f32 volume) { return bgmvolControlMulti(volume, GfPause::isPause(4) && GfGameManager::isTalking()); }

f32 bgmvolFadeDeadSequence(ExecFadeParam &param) {
  bool isFadeOut = param.unknown00->unknown620->unknowna9;
  return bgmvolControlFade(*param.unknown08, isFadeOut ? param.unknown10->unknown20 : param.unknown10->unknown24, isFadeOut);
}

f32 bgmvolFadeGimmick(ExecFadeParam &param) {
  bool isFadeOut = param.unknown00->unknown620->m_rscGimmickBgmID != 0;
  return bgmvolControlFade(*param.unknown08, isFadeOut ? param.unknown10->unknown20 : param.unknown10->unknown24, isFadeOut);
}

f32 bgmvolAdvertize(ExecFadeParam &param) {
  const fw::UpdateInfo &info = *param.unknown08;
  f32 time = GfManager::isExecModeAdvertize() ? param.unknown10->unknown20 : param.unknown10->unknown24;
  return bgmvolControlFade(info, time, GfManager::isExecModeAdvertize());
}

f32 bgmvolBattleBoss(ExecFadeParam &param) {
  bool isFadeOut = param.unknown00->unknown620->m_rscBossBattleBgmID != 0 || GfGameManager::isForceBossBattleBgm();
  return bgmvolControlFade(*param.unknown08, isFadeOut ? param.unknown10->unknown20 : param.unknown10->unknown24, isFadeOut);
}

f32 bgmvolNotBattleBoss(ExecFadeParam &param) {
  bool isFadeOut = !(param.unknown00->unknown620->m_rscBossBattleBgmID != 0 || GfGameManager::isForceBossBattleBgm());
  return bgmvolControlFade(*param.unknown08, isFadeOut ? param.unknown10->unknown20 : param.unknown10->unknown24, isFadeOut);
}

f32 bgmvolFadeBattle(ExecFadeParam &param) {
  bool isFadeOut = GfGameManager::isBattle() || GfGameManager::isForceBossBattleBgm();
  return bgmvolControlFade(*param.unknown08, isFadeOut ? param.unknown10->unknown20 : param.unknown10->unknown24, isFadeOut);
}

f32 bgmvolFadeNotBattle(ExecFadeParam &param) {
  bool isFadeOut = !(GfGameManager::isBattle() || GfGameManager::isForceBossBattleBgm());
  return bgmvolControlFade(*param.unknown08, isFadeOut ? param.unknown10->unknown20 : param.unknown10->unknown24, isFadeOut);
}

f32 bgmvolFadeField(ExecFadeParam &param) {
  bool isFadeOut = !(GfGameManager::isBattle() || GfGameManager::isForceBossBattleBgm());
  return bgmvolControlFade(*param.unknown08, isFadeOut ? param.unknown10->unknown20 : param.unknown10->unknown24, isFadeOut);
}

f32 bgmvolFadeLeaveGame(ExecFadeParam &param) {
  bool isFadeOut = GfGameManager::isLeaveGameForDebug();
  return bgmvolControlFade(*param.unknown08, isFadeOut ? param.unknown10->unknown20 : param.unknown10->unknown24, isFadeOut);
}

f32 bgmvolFadeEnableEventBgm(ExecFadeParam &param) {
  bool isFadeOut = GfEvtBgm::get()->isEnableEventBgm() || GfGameManager::isForceEventBgm();
  return bgmvolControlFade(*param.unknown08, isFadeOut ? param.unknown10->unknown20 : param.unknown10->unknown24, isFadeOut);
}

f32 bgmvolFadeDisableEventBgm(ExecFadeParam &param) {
  bool isFadeOut = !(GfEvtBgm::get()->isEnableEventBgm() || GfGameManager::isForceEventBgm());
  return bgmvolControlFade(*param.unknown08, isFadeOut ? param.unknown10->unknown20 : param.unknown10->unknown24, isFadeOut);
}

f32 bgmvolFadeBattleEvent(ExecFadeParam &param) {
  bool isFadeOut = GfGameScene::get()->unknown648;
  return bgmvolControlFade(*param.unknown08, isFadeOut ? param.unknown10->unknown20 : param.unknown10->unknown24, isFadeOut);
}

f32 bgmvolFadeNotBattleEvent(ExecFadeParam &param) {
  bool isFadeOut = GfGameScene::get()->unknown648;
  return bgmvolControlFade(*param.unknown08, isFadeOut ? param.unknown10->unknown20 : param.unknown10->unknown24, isFadeOut);
}

f32 bgmvolFadeEvent(ExecFadeParam &param) {
  bool isFadeOut = GfGameManager::isInnerState(GF_STATE_EVENT) || GfGameManager::isForceEventBgm();
  return bgmvolControlFade(*param.unknown08, isFadeOut ? param.unknown10->unknown20 : param.unknown10->unknown24, isFadeOut);
}

f32 bgmvolIsBattleDead(ExecFadeParam &param) {
  bool isFadeOut = GfGameManager::getDeadType() == 1;
  return bgmvolControlFade(*param.unknown08, isFadeOut ? param.unknown10->unknown20 : param.unknown10->unknown24, isFadeOut);
}

f32 bgmvolMapMatch(ExecFadeParam &param) {
  u32 map = GfGameManager::getMapID();
  u32 bgmCond = 0;
  if (map != 0) {
    bgmCond = GfBdatMaplist::get()->getMaplistbgm_cndID(map);
  }
  bool isFadeOut = bgmCond != param.unknown00->m_bgmCondID;
  return bgmvolControlFade(*param.unknown08, isFadeOut ? param.unknown10->unknown20 : param.unknown10->unknown24, isFadeOut);
}

f32 bgmvolGimmickMatch(ExecFadeParam &param) {
  bool isFadeOut = param.unknown00->unknown620->m_rscGimmickBgmID != param.unknown00->m_bgmCondID;
  return bgmvolControlFade(*param.unknown08, isFadeOut ? param.unknown10->unknown20 : param.unknown10->unknown24, isFadeOut);
}
} // namespace _gffsn

u32 BgmTrack::getBgmCondID() const { return m_bgmCondID; }

enum {
  MAPJUMP_TYPE_FIELD_DESTROY = 2,
};

u32 GfFieldBgm::getRscFieldBgmID() const {
  u32 map = GfGameManager::getMapID();
  if (map != 0) {
    return GfBdatMaplist::get()->getMaplistbgm_cndID(map);
  }
  return 0;
}

u32 GfFieldBgm::getRscBossBattleBgmID() const { return m_rscBossBattleBgmID; }

u32 GfFieldBgm::getRscBattleBgmID() const { return m_rscBattleBgmID; }

u32 GfFieldBgm::getRscGimmickBgmID() const { return m_rscGimmickBgmID; }

bool GfFieldBgm::isDisableFieldBgmChange() const { return m_disableFieldBgmChange; }

void GfFieldBgm::setGimmickBgmID(u32 id) {
  if (id == 0 && m_gimmickBgmID != 0) {
    unknowna4 = 30;
  }
  m_gimmickBgmID = id;
}

void GfFieldBgm::gevBattleEnd() { m_rscBossBattleBgmID = 0; }

void GfFieldBgm::gevMapjump(GEV gev, const MapjumpCallbackInfo &info) {
  switch (gev) {
  case GEV_MAPJUMP_START:
    applyMapJumpStart(info);
    break;
  case GEV_MAPJUMP_FADEIN:
    applyMapJumpFadein(info);
    break;
  default:
    break;
  }
}

void GfFieldBgm::applyMapJumpStart(const MapjumpCallbackInfo &info) {
  if (info.unknown10 == MAPJUMP_TYPE_FIELD_DESTROY) {
    unknowna9 = true;
  }
  m_disableFieldBgmChange = true;
}

void GfFieldBgm::applyMapJumpCleanup(const MapjumpCallbackInfo &) {}

void GfFieldBgm::applyMapJumpFadein(const MapjumpCallbackInfo &info) {
  if (info.unknown10 == MAPJUMP_TYPE_FIELD_DESTROY) {
    unknowna9 = false;
  }
  m_disableFieldBgmChange = false;
}

void GfFieldBgm::updateGimmickBgm(const fw::UpdateInfo &) {
  unknowna4--;
  if (unknowna4 <= 0 && m_gimmickBgmID != static_cast<u32>(-1)) {
    m_rscGimmickBgmID = m_gimmickBgmID;
    m_gimmickBgmID = -1;
  }
}

void GfFieldBgm::stopBgmForDebug(bool stop) { _gffsn::s_bStopBGM = stop; }

bool GfFieldBgm::isStopBgmForDebug() { return _gffsn::s_bStopBGM; }

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfFieldBgm>::~PtrSingleton();
template float mm::mtl::Delegate<float(gf::ExecFadeParam &)>::staticFuncInvoker(const mm::mtl::Delegate<float(gf::ExecFadeParam &)> *, gf::ExecFadeParam &);
