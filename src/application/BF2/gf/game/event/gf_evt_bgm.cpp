#include "gf/game/event/gf_evt_bgm.h"

namespace gf {

void GfEvtBgm::destroy() {
  GfEvtBgm *bgm = get();
  bgm->finalize();
  delete bgm;
}

void GfEvtBgm::initialize(const GfSetupParam &) { m_initialized = true; }

void GfEvtBgm::update(const fw::UpdateInfo &info) { updateBgmTask(info); }

void GfEvtBgm::finalize() { m_initialized = false; }

bool GfEvtBgm::isInitialized() { return m_initialized; }

void GfEvtBgm::setPlayBgmVolume(f32 volume) { m_playBgmVolume = volume; }

void GfEvtBgm::setPlayState(PLAY_STATE playState) { m_playState = playState; }

bool GfEvtBgm::isEnableEventBgm() const { return m_playState >= PLAY_STATE_UNKNOWN_2 && m_playState <= PLAY_STATE_UNKNOWN_4; }

void GfEvtBgm::setFadeoutVolume() {
  if (m_playState == PLAY_STATE_UNKNOWN_3 && unknown478 == nullptr) {
    m_playState = PLAY_STATE_UNKNOWN_0;
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfEvtBgm>::~PtrSingleton();
