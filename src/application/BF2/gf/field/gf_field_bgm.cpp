#include "gf/field/gf_field_bgm.h"

#include <string.h>

#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_bgm.h"
#include "gf/data/gf_bdat_maplist.h"
#include "gf/event/gf_event.h"
#include "gf/game/event/gf_evt_bgm.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_scene.h"
#include "gf/gf_manager.h"
#include "gf/gf_pause.h"
#include "gf/util/gf_util.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/delegate.h" // IWYU pragma: keep

namespace fw {
enum SoundCategory : int;
} // namespace fw

namespace gf {

class BgmEvent; // IWYU pragma: keep

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
const char *s_szStreamPath = "/stream/";
const char *s_szBgmPath = "/bgm/";

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

void BgmTrack::destroy() {
  stopBGM(2.0f);
  unknown610 = 1.0f;
  unknown614 = 1.0f;
  unknown618 = 1.0f;
  m_categoryApply = CATEGORY_GAME_BGM;
}

void BgmTrack::setPause(bool pause) {
  m_pause = pause;
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    for (u32 i = 0; i < 4; i++) {
      if (unknown08[i].unknown04.isValid()) {
        sound->setPause(unknown08[i].unknown04, pause, 0.0f);
      }
    }
  }
}

f32 BgmTrack::getVolume() const {
  const BGMCOND *cond = unknown003();
  if (cond == nullptr) {
    return 0.0f;
  }
  return cond->unknown00;
}

void BgmTrack::play(u32 bgmCondID) {
  if (m_bgmCondID != 0) {
    u32 i = 0;
    while (i < 4 && unknown08[i].unknown00 <= 0.0f) {
      i++;
    }
    if (i < 4) {
      return;
    }
    stopBGM(0.0f);
  }
  m_bgmCondID = bgmCondID;
}

void BgmTrack::stopBGM(f32 fadeTime) {
  for (u32 i = 0; i < 4; i++) {
    GfSound *sound = GfSound::get();
    if (sound != nullptr && unknown08[i].unknown04.isValid()) {
      sound->stopBgm(unknown08[i].unknown04, fadeTime);
    }
    unknown08[i].clear();
  }
  unknown614 = 0.0f;
  unknown618 = 1.0f;
  if (!unknown60e) {
    m_bgmCondID = 0;
  }
  unknown08[0].unknown14 = "";
}

void BgmTrack::destroyFader() {
  unknown178.clear();
  unknown3c0.clear();
}

void BgmTrack::play(const char *name) { unknown08[0].unknown14 = name; }

bool BgmTrack::isPlaying() const {
  for (u32 i = 0; i < 4; i++) {
    if (!unknown08[i].unknown14.empty() || unknown08[i].unknown04.isValid()) {
      return true;
    }
  }
  return false;
}

const char *BgmTrack::getPlayingBgmFileName() const { return unknown08[0].unknown14.c_str(); }

void BgmTrack::setCategoryApply(u8 category) {
  m_categoryApply = category;
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    for (u32 i = 0; i < 4; i++) {
      if (unknown08[i].unknown04.isValid()) {
        sound->setCategory(unknown08[i].unknown04, static_cast<fw::SoundCategory>(category));
      }
    }
  }
}

void BgmTrack::playWithFadeout(u32 bgmCondID) {
  if (m_bgmCondID != 0) {
    stopBGM(4.0f);
  }
  m_bgmCondID = bgmCondID;
}

void BgmTrack::setPlayingBgmFileName(const char *name) { unknown08[0].unknown14 = name; }

f32 BgmTrack::getPlayTime() const {
  f32 result = 0.0f;
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    const SoundHandle *handle = unknown004();
    if (handle != nullptr) {
      f32 time;
      if (sound->getPlayTime(*handle, time)) {
        result = time;
      }
    }
  }
  return result;
}

f32 BgmTrack::getTotalTime() const {
  f32 result = 0.0f;
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    const SoundHandle *handle = unknown004();
    if (handle != nullptr) {
      f32 time;
      if (sound->getTotalTime(*handle, time)) {
        result = time;
      }
    }
  }
  return result;
}

bool BgmTrack::isLoop() const {
  GfSound *sound = GfSound::get();
  if (sound == nullptr) {
    return false;
  }
  const SoundHandle *handle = unknown004();
  if (handle == nullptr) {
    return false;
  }
  return sound->isLoop(*handle);
}

bool BgmTrack::isEnablePlayBgmData(const BGMCOND &cond) const {
  if (!cond.unknown14.empty()) {
    return true;
  }
  if (m_bgmCondID != 0 && getBgmConditionBgmID(m_bgmCondID, cond.unknown58) != 0) {
    return true;
  }
  return false;
}

void BgmTrack::streamVolume(const BGMCOND &cond) {
  unknown614 = cond.unknown00 * unknown610 * unknown618;
  if (unknown614 < 0.0f) {
    unknown614 = 0.0f;
  } else if (unknown614 > 1.0f) {
    unknown614 = 1.0f;
  }
  if (cond.unknown04.isValid() && GfSound::get() != nullptr) {
    GfSound::get()->setVolume(cond.unknown04, unknown614, 0.0f);
  }
}

bool BgmTrack::streamIsPlay(const BGMCOND &cond) const {
  GfSound *sound = nullptr;
  if (cond.unknown04.isValid() && (sound = GfSound::get()) != nullptr) {
    return sound->isPlaying(cond.unknown04) || sound->isPreparing(cond.unknown04);
  }
  return false;
}

void BgmTrack::stopCondBGM(f32 fadeTime, BGMCOND &cond) {
  GfSound *sound = GfSound::get();
  if (sound != nullptr && cond.unknown04.isValid()) {
    sound->stopBgm(cond.unknown04, fadeTime);
  }
  cond.clear();
}

void BgmTrack::addVolumeFade(f32 (*function)(ExecFadeParam &), f32 fadeOutTime, f32 fadeInTime, bool flag) {
  unknown001 entry;
  entry.unknown00.bind(function);
  entry.unknown20 = fadeOutTime;
  entry.unknown24 = fadeInTime;
  entry.unknown28 = flag;
  unknown178.push_back(entry);
}

void BgmTrack::addVolumeMulti(f32 (*function)(f32, f32, f32), f32 arg0, f32 arg1, f32 arg2) {
  unknown002 entry;
  entry.unknown00.bind(function);
  entry.unknown20 = arg0;
  entry.unknown24 = arg1;
  entry.unknown28 = arg2;
  unknown3c0.push_back(entry);
}

void BgmTrack::calcMultiplyVolume(const fw::UpdateInfo &info) {
  f32 volume = 1.0f;
  f32 fadeOutTime = 5.0f;
  f32 fadeInTime = 5.0f;
  for (const unknown002 &entry : unknown3c0) {
    volume *= entry.unknown00(entry.unknown20, entry.unknown24, entry.unknown28);
    if (fadeOutTime > entry.unknown20) {
      fadeOutTime = entry.unknown20;
    }
    if (fadeInTime > entry.unknown24) {
      fadeInTime = entry.unknown24;
    }
  }
  if (volume < unknown610) {
    unknown610 -= info.unknown04 / fadeOutTime;
    mm::clampRef(unknown610, volume, 1.0f);
  } else if (volume > unknown610) {
    unknown610 += info.unknown04 / fadeInTime;
    mm::clampRef(unknown610, 0.0f, volume);
  }
}

bool BgmTrack::getPlayVolume(f32 &volume, const fw::UpdateInfo &info, const BGMCOND &cond, bool isFadeOut) {
  ExecFadeParam param;
  param.unknown18 = &cond;
  param.unknown00 = this;
  param.unknown08 = &info;
  volume = cond.unknown00;
  f32 minVolume = 0.0f;
  bool flag = false;
  for (const unknown001 &entry : unknown178) {
    param.unknown10 = &entry;
    f32 fade = entry.unknown00(param);
    if (isFadeOut && fade > 0.0f) {
      fade = -fade;
    }
    if (minVolume > fade) {
      flag = entry.unknown28;
      minVolume = fade;
    }
  }
  if (minVolume < 0.0f) {
    volume += minVolume;
    mm::clampRef(volume, 0.0f, 1.0f);
    return flag || isFadeOut;
  }
  f32 maxVolume = 0.0f;
  for (const unknown001 &entry : unknown178) {
    param.unknown10 = &entry;
    f32 fade = entry.unknown00(param);
    if (maxVolume < fade) {
      maxVolume = fade;
    }
  }
  if (maxVolume > 0.0f) {
    volume += maxVolume;
    mm::clampRef(volume, 0.0f, 1.0f);
  }
  return false;
}

void BgmTrack::copyPlayParam(BgmTrack *src) {
  m_bgmCondID = src->m_bgmCondID;
  unknown614 = src->unknown614;
  unknown610 = src->unknown610;
  unknown08 = src->unknown08;
  unknown629 = true;
  if (!unknown08[0].unknown04.isValid() && unknown08[1].unknown04.isValid()) {
    unknown08[0].copyPlayInfo(unknown08[1]);
    unknown08[1].clear();
  }
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    for (BGMCOND *cond = src->unknown08.begin(); cond != src->unknown08.end(); cond++) {
      if (cond->unknown04.isValid()) {
        sound->setCategory(cond->unknown04, static_cast<fw::SoundCategory>(m_categoryApply));
      }
    }
  }
  src->m_bgmCondID = 0;
  src->unknown610 = 0.0f;
  src->unknown614 = 0.0f;
  for (BGMCOND *cond = src->unknown08.begin(); cond != src->unknown08.end(); cond++) {
    cond->clear();
  }
}

void BgmTrack::copyPlayParam(BgmTrack *src, const BgmFileInfo &info) {
  m_bgmCondID = info.unknown00;
  unknown614 = src->unknown614;
  unknown610 = src->unknown610;
  unknown60d = true;
  for (u32 i = 0; i < 4; i++) {
    unknown08[i].clear();
  }
  SoundHandle handle;
  f32 volume = 0.0f;
  for (BGMCOND *cond = src->unknown08.begin(); cond != src->unknown08.end(); cond++) {
    if (cond->unknown04.isValid()) {
      handle = cond->unknown04;
      volume = cond->unknown00;
      cond->unknown04.clear();
      break;
    }
  }
  if (handle.isValid()) {
    unknown08[info.unknown08].unknown0c = info.unknown04;
    unknown08[info.unknown08].unknown04 = handle;
    unknown08[info.unknown08].unknown00 = volume;
  }
  GfSound *sound = GfSound::get();
  if (sound != nullptr) {
    for (BGMCOND *cond = src->unknown08.begin(); cond != src->unknown08.end(); cond++) {
      if (cond->unknown04.isValid()) {
        sound->setCategory(cond->unknown04, static_cast<fw::SoundCategory>(m_categoryApply));
      }
    }
  }
  src->m_bgmCondID = 0;
  src->unknown610 = 0.0f;
  src->unknown614 = 0.0f;
  for (BGMCOND *cond = src->unknown08.begin(); cond != src->unknown08.end(); cond++) {
    cond->clear();
  }
}

bool BgmTrack::makeBgmFile(mm::mtl::FixStr<64> &name, u32 &bgmID, u32 bgmCondID, u32 index) const {
  if (bgmCondID != 0) {
    bgmID = getBgmConditionBgmID(bgmCondID, index);
    if (bgmID != 0) {
      const char *file = GfBdatBgm::get()->getBgmListfilename(bgmID);
      if (util::getFilePtrFromPath(file) == file) {
        name.format("%s%s%s", _gffsn::s_szStreamPath, _gffsn::s_szBgmPath, file);
      } else {
        name.format("%s%s", _gffsn::s_szStreamPath, file);
      }
      return true;
    }
  }
  return false;
}

BgmTrack::BgmTrack(GfFieldBgm *owner, bool unknown)
    : m_bgmCondID(0), unknown60c(unknown), unknown60e(false), unknown610(1.0f), unknown614(1.0f), unknown618(1.0f), unknown61c(0.0f), unknown620(owner), unknown629(false),
      m_categoryApply(CATEGORY_GAME_BGM) {
  BGMCOND cond;
  unknown08.assign(cond);
  for (u32 i = 0; i < 4; i++) {
    unknown08[i].unknown58 = i;
  }
}

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

void GfFieldBgm::setRscBattleBgmID(u32 id) {
  if (id == 0) {
    m_rscBossBattleBgmID = 0;
  } else if (GfBdatBgm::get()->getBgmConditionPriority(id) < 2) {
    m_rscBossBattleBgmID = 0;
    m_rscBattleBgmID = id;
  } else if (BgmBattle::get()->m_bgmCondID == id) {
    m_rscBossBattleBgmID = 0;
  } else {
    m_rscBossBattleBgmID = id;
    unknown94 = 0;
  }
}

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

void GfFieldBgm::destroy() {
  for (BgmTrack *track : unknown08) {
    track->stopBGM(2.0f);
    track->unknown610 = 1.0f;
    track->unknown614 = 1.0f;
    track->unknown618 = 1.0f;
    track->m_categoryApply = 1;
  }
}

void GfFieldBgm::update(const fw::UpdateInfo &info) {
  updateBattleBgm(info);
  updateGimmickBgm(info);
  if (!m_disableFieldBgmChange) {
    for (BgmTrack *track : unknown08) {
      track->update(info);
    }
  }
}

void GfFieldBgm::updateBattleBgm(const fw::UpdateInfo &) {
  if (m_rscBossBattleBgmID != 0 && m_rscBossBattleBgmID != 0xff && !BgmBattleBoss::get()->isPlaying()) {
    if (unknown94++ > 0x12a) {
      m_rscBossBattleBgmID = 0;
      unknown94 = 0;
    }
  }
}

void GfFieldBgm::updateGimmickBgm(const fw::UpdateInfo &) {
  unknowna4--;
  if (unknowna4 <= 0 && m_gimmickBgmID != static_cast<u32>(-1)) {
    m_rscGimmickBgmID = m_gimmickBgmID;
    m_gimmickBgmID = -1;
  }
}

void GfFieldBgm::gevPause(u32 resumeBits, u32 pauseBits) {
  if (!(resumeBits >> 2 & 1) && (pauseBits & 4)) {
    for (BgmTrack *track : unknown08) {
      track->setPause(true);
    }
  } else if ((resumeBits >> 2 & 1) && !(pauseBits & 4)) {
    for (BgmTrack *track : unknown08) {
      track->setPause(false);
    }
  }
}

bool GfFieldBgm::isBossBgmCopied() const {
  if (BgmBattleBoss::get() != nullptr) {
    return BgmBattleBoss::get()->unknown629;
  }
  return false;
}

void GfFieldBgm::transferSoundParam(BgmTrack *track) {
  for (BgmTrack *&source : unknown08) {
    if (source != track && source->isPlaying()) {
      track->copyPlayParam(source);
      return;
    }
  }
}

void GfFieldBgm::setPause(bool isPause) {
  for (BgmTrack *track : unknown08) {
    track->setPause(isPause);
  }
}

GfFieldBgm::~GfFieldBgm() {
  for (BgmTrack **it = unknown08.begin(); it != unknown08.end(); ++it) {
    if (*it != nullptr) {
      delete *it;
      *it = nullptr;
    }
  }
}

void GfFieldBgm::stopBgmForDebug(bool stop) { _gffsn::s_bStopBGM = stop; }

bool GfFieldBgm::isStopBgmForDebug() { return _gffsn::s_bStopBGM; }

BgmEvent::BgmEvent(GfFieldBgm *owner) : BgmTrack(owner, false) {}

void BgmEvent::gevPlayEvent(GEV gev, u32) {
  if (gev == GEV_EVENT_SEQUENCE_END) {
    unknown6a0.clear();
  }
}

bool BgmEvent::isPlaying() const { return BgmTrack::isPlaying(); }

void BgmEvent::cancelOverTime() { unknown638.unknown5c = 0.0f; }

const char *BgmEvent::getTrackName() const { return "EventBGM"; }

const char *BgmBattle::getTrackName() const { return "BattleBGM"; }

void BgmBattle::update(const fw::UpdateInfo &info) {
  if (m_bgmCondID != unknown620->m_rscBattleBgmID) {
    play(unknown620->m_rscBattleBgmID);
  }
  BgmTrack::update(info);
}

const char *BgmBattleBoss::getTrackName() const { return "BossBGM"; }

void BgmBattleBoss::update(const fw::UpdateInfo &info) {
  u32 id = unknown620->m_rscBossBattleBgmID;
  if (id != 0 && m_bgmCondID != id) {
    play(id);
  }
  BgmTrack::update(info);
  GfGameScene *scene = GfGameScene::get();
  if (scene != nullptr && scene->isForceBossBattleBgm() && !isPlaying()) {
    scene->setForceBossBattleBgm(false);
  }
}

const char *BgmField::getTrackName() const { return "FieldBGM"; }

void BgmField::update(const fw::UpdateInfo &info) {
  u32 map = GfGameManager::getMapID();
  u32 id = 0;
  if (map != 0) {
    id = GfBdatMaplist::get()->getMaplistbgm_cndID(map);
  }
  if (m_bgmCondID != id) {
    playWithFadeout(id);
  }
  BgmTrack::update(info);
}

const char *BgmGimmick::getTrackName() const { return "GimmickBGM"; }

void BgmGimmick::update(const fw::UpdateInfo &info) {
  u32 id = unknown620->m_rscGimmickBgmID;
  if (m_bgmCondID != id) {
    playWithFadeout(id);
  }
  BgmTrack::update(info);
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfFieldBgm>::~PtrSingleton();
template float mm::mtl::Delegate<float(gf::ExecFadeParam &)>::staticFuncInvoker(const mm::mtl::Delegate<float(gf::ExecFadeParam &)> *, gf::ExecFadeParam &);
template mm::mtl::PtrSingleton<gf::BgmGimmick>::~PtrSingleton();
template mm::mtl::PtrSingleton<gf::BgmBattle>::~PtrSingleton();
template mm::mtl::PtrSingleton<gf::BgmBattleBoss>::~PtrSingleton();
template mm::mtl::PtrSingleton<gf::BgmEvent>::~PtrSingleton();
template mm::mtl::PtrSingleton<gf::BgmField>::~PtrSingleton();
template void mm::mtl::FixedArray<gf::BGMCOND, 4>::assign(const gf::BGMCOND &value);
