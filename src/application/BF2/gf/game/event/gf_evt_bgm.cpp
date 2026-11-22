#include "gf/game/event/gf_evt_bgm.h"

#include <string.h>

#include "fw/fw_update_info.h"
#include "gf/field/gf_field_bgm.h"
#include "gf/game/event/gf_evt_bgm_task.h"
#include "gf/game/gf_game_scene.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/fixstr.h"

namespace gf {

GfEvtBgm::GfEvtBgm(const GfSetupParam &param) : m_eventBgmSetup(), m_playState(PLAY_STATE_UNKNOWN_0), unknown78(), unknown488(nullptr) { initialize(param); }

GfEvtBgm::~GfEvtBgm() { ; }

void GfEvtBgm::destroy() {
  GfEvtBgm *bgm = get();
  bgm->finalize();
  delete bgm;
}

void GfEvtBgm::initialize(const GfSetupParam &) { m_initialized = true; }

void GfEvtBgm::update(const fw::UpdateInfo &info) { updateBgmTask(info); }

void GfEvtBgm::finalize() { m_initialized = false; }

bool GfEvtBgm::isInitialized() { return m_initialized; }

void GfEvtBgm::setPlayBgmVolume(f32 volume) { m_eventBgmSetup.m_playBgmVolume = volume; }

void GfEvtBgm::setPlayState(PLAY_STATE playState) { m_playState = playState; }

bool GfEvtBgm::isEnableEventBgm() const { return m_playState >= PLAY_STATE_UNKNOWN_2 && m_playState <= PLAY_STATE_UNKNOWN_4; }

void GfEvtBgm::setFadeoutVolume() {
  if (m_playState == PLAY_STATE_UNKNOWN_3 && unknown78.empty()) {
    m_playState = PLAY_STATE_UNKNOWN_0;
  }
}

void GfEvtBgm::clear() {
  for (EvtBgmTask *task : unknown78) {
    delete task;
  }
  unknown78.clear();
}

void GfEvtBgm::changeBgmVolume(const EventBgmSetup &setup) { unknown78.push(EvtBgmTaskVolume::create(setup)); }

void GfEvtBgm::build(const GfSetupParam &param) {
  // __LINE__ must be 64 as in the original file: it is an argument of the allocation.
#line 64
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfEvtBgm(param);
}

void GfEvtBgm::stopBgm(const EventBgmSetup &setup) {
  if (m_eventBgmSetup.unknown5c == 0.0f) {
    unknown78.push(EvtBgmTaskDelayStop::create(setup));
  }
}

void GfEvtBgm::playBgm(const EventBgmSetup &setup) {
  if (isPlayBgm() && m_eventBgmSetup.unknown58 > 0.0f) {
    unknown78.push(EvtBgmTaskDelayStop::create(m_eventBgmSetup));
  }
  while (!unknown78.empty() && unknown78.back()->isVolumeTask()) {
    if (unknown78.back() != nullptr) {
      delete unknown78.back();
      unknown78.back() = nullptr;
    }
    unknown78.pop_back();
  }
  unknown78.push(EvtBgmTaskDelay::create(setup));
}

bool GfEvtBgm::isPlayBgm() const {
  if (BgmEvent::get()->isPlaying() || m_playState != PLAY_STATE_UNKNOWN_0) {
    return true;
  }
  for (EvtBgmTask *task : unknown78) {
    if (task->isPlayTask()) {
      return true;
    }
  }
  return false;
}

bool GfEvtBgm::isPlaySilent() const {
  if (isPlayBgm()) {
    return strcmp(m_eventBgmSetup.unknown00.c_str(), "SilentBgm") == 0;
  }
  return false;
}

void GfEvtBgm::cancelOverTime() {
  m_eventBgmSetup.unknown5c = 0.0f;
  if (BgmEvent::get() != nullptr) {
    BgmEvent::get()->cancelOverTime();
  }
}

f32 GfEvtBgm::getPlayBgmTime() const {
  if (BgmEvent::get() != nullptr) {
    return BgmEvent::get()->getPlayTime();
  }
  return 0.0f;
}

f32 GfEvtBgm::getTotalBgmTime() const {
  if (BgmEvent::get() != nullptr) {
    return BgmEvent::get()->getTotalTime();
  }
  return 0.0f;
}

void GfEvtBgm::setPlayBgmTakeOver(const char *name) { m_eventBgmSetup.unknown00 = name; }

void GfEvtBgm::setPlayParam(const EventBgmSetup &setup) {
  m_eventBgmSetup = setup;
  if (m_eventBgmSetup.unknown00.empty() && !setup.unknown60 && setup.unknown65) {
    m_eventBgmSetup.unknown00 = "SilentBgm";
  }
}

EvtBgmTaskDelayStop::EvtBgmTaskDelayStop(const EventBgmSetup &setup) : m_eventBgmSetup(setup), unknown70(setup.unknown58), unknown74(false) {}

void EvtBgmTaskDelayStop::start(GfEvtBgm *bgm) { bgm->m_playState = GfEvtBgm::PLAY_STATE_UNKNOWN_4; }

bool EvtBgmTaskDelayStop::update(GfEvtBgm *bgm, const fw::UpdateInfo &info) {
  if (!unknown74) {
    unknown70 -= info.unknown04;
    if (unknown70 > 0.0f) {
      return false;
    }
    bgm->setPlayParam(m_eventBgmSetup);
    bgm->m_playState = GfEvtBgm::PLAY_STATE_UNKNOWN_0;
    if (GfGameScene::get() != nullptr) {
      GfGameScene::get()->setForceEventBgm(0.0f);
    }
  }
  return true;
}

void EvtBgmTaskDelayStop::cancel(GfEvtBgm *) { unknown74 = true; }

EvtBgmTaskDelayStop *EvtBgmTaskDelayStop::create(const EventBgmSetup &setup) {
  // __LINE__ must be 392 as in the original file: it is an argument of the allocation.
#line 392
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) EvtBgmTaskDelayStop(setup);
}

EvtBgmTaskDelay::EvtBgmTaskDelay(const EventBgmSetup &setup) : m_eventBgmSetup(setup), unknown70(false) {}

bool EvtBgmTaskDelay::isPlayTask() const { return true; }

void EvtBgmTaskDelay::start(GfEvtBgm *bgm) {
  if (bgm->m_eventBgmSetup.unknown60) {
    bgm->m_playState = GfEvtBgm::PLAY_STATE_UNKNOWN_2;
    bgm->m_eventBgmSetup.unknown00 = "";
  } else {
    bgm->m_playState = GfEvtBgm::PLAY_STATE_UNKNOWN_1;
  }
}

bool EvtBgmTaskDelay::update(GfEvtBgm *bgm, const fw::UpdateInfo &info) {
  if (!unknown70) {
    m_eventBgmSetup.unknown54 -= info.unknown04;
    if (m_eventBgmSetup.unknown54 > 0.0f) {
      return false;
    }
    bgm->m_playState = GfEvtBgm::PLAY_STATE_UNKNOWN_3;
    bgm->setPlayParam(m_eventBgmSetup);
    if (m_eventBgmSetup.unknown58 > 0.0f && GfGameScene::get() != nullptr) {
      GfGameScene::get()->setForceEventBgm(m_eventBgmSetup.unknown58);
    }
  }
  return true;
}

void EvtBgmTaskDelay::cancel(GfEvtBgm *) { unknown70 = true; }

EvtBgmTaskDelay *EvtBgmTaskDelay::create(const EventBgmSetup &setup) {
  // __LINE__ must be 347 as in the original file: it is an argument of the allocation.
#line 347
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) EvtBgmTaskDelay(setup);
}

EvtBgmTaskVolume::EvtBgmTaskVolume(const EventBgmSetup &setup) : unknown08(setup.unknown48), unknown0c(setup.m_playBgmVolume), unknown10(false) {}

bool EvtBgmTaskVolume::isVolumeTask() const { return true; }

void EvtBgmTaskVolume::start(GfEvtBgm *) {}

bool EvtBgmTaskVolume::update(GfEvtBgm *bgm, const fw::UpdateInfo &info) {
  if (unknown10) {
    return true;
  }
  if (info.unknown04 < 1e-06f) {
    return false;
  }
  f32 remain = unknown08 - info.unknown04;
  unknown08 = remain <= 0.0f ? 0.0f : remain;
  f32 diff = unknown0c - bgm->m_eventBgmSetup.m_playBgmVolume;
  if (__builtin_fabsf(diff) <= 1e-06f) {
    return true;
  }
  f32 ratio = unknown08 == 0.0f ? 1.0f : info.unknown04 / unknown08;
  bgm->m_eventBgmSetup.m_playBgmVolume += diff * ratio;
  return unknown08 <= 0.0f;
}

void EvtBgmTaskVolume::cancel(GfEvtBgm *) { unknown10 = true; }

EvtBgmTaskVolume *EvtBgmTaskVolume::create(const EventBgmSetup &setup) {
  // __LINE__ must be 437 as in the original file: it is an argument of the allocation.
#line 437
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) EvtBgmTaskVolume(setup);
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfEvtBgm>::~PtrSingleton();
