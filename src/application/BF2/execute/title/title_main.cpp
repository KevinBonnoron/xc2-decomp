// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/execute/title/title_main.cpp.
#include "execute/title/title_main.h"

#include <new>

#include "ai/ai_state.h"
#include "execute/title/title_state_debug_save_continue.h"
#include "execute/title/title_state_load.h"
#include "execute/title/title_state_main_screen.h"
#include "execute/title/title_state_play_event.h"
#include "execute/title/title_state_play_game.h"
#include "execute/title/title_state_select_event.h"
#include "execute/title/title_state_select_option.h"
#include "execute/title/title_state_to_title.h"
#include "framework/memory/framework_memory.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_option.h"
#include "gf/data/gf_data_system.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/gf_manager.h"
#include "gf/menu/gf_menu_manager.h"
#include "ml/micro_thread.h"
#include "ml/work_root.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/delegate.h"
#include "mtl/alloc_handle.h"

namespace ml {
class MLTHG;
} // namespace ml
namespace nn {
namespace os {
struct FiberType;
} // namespace os
} // namespace nn

template <typename T> nn::os::FiberType *MicroUpdater<T>::fnMicroUpdate(void *) {
  MicroUpdater *updater = static_cast<MicroUpdater *>(ml::MicroThread::get()->getCurrentUserData());
  updater->unknown18(updater->unknown10);
  updater->unknown08 = -1;
  ml::MicroThread::get()->exit();
  return nullptr;
}

namespace tl {

TitleMain::TitleMain()
    : m_fsm(fw::FrameworkMemory::getAllocator(5)), unknown80(nullptr), unknown94(false), unknown95(false), m_soundHandle(0), unknowna0(false), unknowna4(gf::SAVESLOT_UNKNOWN_FFFFFFFF),
      m_saveBuffer(nullptr), m_optionBuffer(nullptr), m_playTitleEvent(0), unknown170(gf::unknown019), unknown178(false) {}

TitleMain::~TitleMain() {}

TitleMain *TitleMain::create() {
#line 94
  TitleMain *main = new (fw::FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) TitleMain();
  main->initialize();
  return main;
}

void TitleMain::initialize() {
  createSaveBuffer();
  m_fsm.beginSetup(this, 9);
  m_fsm.registerState<TitleStateLoad>(0);
  m_fsm.registerState<TitleStateMainScreen>(1);
  m_fsm.registerState<TitleStatePlayGame>(5);
  m_fsm.registerState<TitleStatePlayEvent>(6);
  m_fsm.registerState<TitleStateToTitle>(7);
  m_fsm.registerState<TitleStateDebugSaveContinue>(2);
  m_fsm.registerState<TitleStateSelectEvent>(3);
  m_fsm.registerState<TitleStateSelectOption>(4);
  m_fsm.registerState<TitleStateDebugSaveContinue>(8);
  m_fsm.endSetup();
  m_fsm.setState(0);
#line 127
  MicroUpdater<TitleMain> *updater = new (fw::FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) MicroUpdater<TitleMain>();
  unknown80 = updater;
  if (updater->unknown00 == reinterpret_cast<ml::MLTHG *>(-1)) {
    ml::MLTHG *group = ml::MicroThread::get()->createGroup();
    updater->unknown00 = group;
    updater->unknown08 = ml::MicroThread::get()->createThread(group, &MicroUpdater<TitleMain>::fnMicroUpdate, updater);
    updater->unknown18.bind(&TitleMain::fnUpdate);
    updater->unknown10 = this;
  }
}

void TitleMain::finalize() {
  destroyMaskVolume();
  unknown94 = true;
  while (m_fsm.getState()->m_state != 8) {
    ml::MicroThread::get()->sleep(1, true);
  }
  stopTitleBGM(0.0f);
  m_titleMenu.destroyMenuCallContext();
  if (unknown80 != nullptr) {
    delete unknown80;
    unknown80 = nullptr;
  }
  m_fsm.cleanup();
  destroySaveBuffer();
}

void TitleMain::destroy() {
  TitleMain *main = get();
  main->finalize();
  delete main;
}

void TitleMain::createSaveBuffer() {
  if (m_saveBuffer == nullptr) {
    m_saveBuffer = new (ml::WorkRootMem::getMemTMP(), nullptr, 0, 4, false) gf::SDataSave;
  } else {
    new (m_saveBuffer) gf::SDataSave;
  }
  if (m_optionBuffer == nullptr) {
    m_optionBuffer = new (ml::WorkRootMem::getMemTMP(), nullptr, 0, 4, false) gf::SDataOption;
  } else {
    new (m_optionBuffer) gf::SDataOption;
  }
  gf::GfMenuManager::initOptionData(*m_optionBuffer);
}

void TitleMain::fnUpdate(TitleMain *main) {
  main->m_fsm.update(&main->m_updateInfo);
  while (main->m_fsm.getState()->m_state != 8) {
    ml::MicroThread::get()->sleep(1, true);
    main->m_fsm.update(&main->m_updateInfo);
  }
}

void TitleMain::destroyMaskVolume() {
  if (gf::GfSound::get() != nullptr) {
    gf::GfSound::get()->releaseCategoryHandle(unknown170);
  }
}

void TitleMain::stopTitleBGM(f32 fadeTime) {
  if (m_soundHandle.isValid()) {
    if (gf::GfSound::get() != nullptr) {
      gf::GfSound::get()->stopBgm(m_soundHandle, fadeTime);
    }
    m_soundHandle.clear();
    unknowna0 = false;
  }
}

void TitleMain::destroySaveBuffer() {
  if (m_saveBuffer != nullptr) {
    delete m_saveBuffer;
    m_saveBuffer = nullptr;
  }
  if (m_optionBuffer != nullptr) {
    delete m_optionBuffer;
    m_optionBuffer = nullptr;
  }
}

void TitleMain::update(const fw::UpdateInfo &info) {
  TitleMain *main = get();
  if (main != nullptr) {
    if (main->unknowna0) {
      gf::GfSound *sound = gf::GfSound::get();
      if (sound != nullptr && !sound->isPlaying(main->m_soundHandle)) {
        main->m_soundHandle = sound->playBgm("stream/bgm/m02.wav", 1.0f, false, -1, gf::CATEGORY_EVT_BGM);
      }
    }
    MicroUpdater<TitleMain> *updater = main->unknown80;
    if (updater->unknown00 != reinterpret_cast<ml::MLTHG *>(-1)) {
      ml::MicroThread::get()->update(updater->unknown00);
      if (updater->unknown08 == static_cast<u64>(-1)) {
        ml::MicroThread::get()->releaseGroup(updater->unknown00);
        updater->unknown00 = reinterpret_cast<ml::MLTHG *>(-1);
      }
    }
  }
}

void TitleMain::sleep(u32 frame) { ml::MicroThread::get()->sleep(frame, true); }

void TitleMain::returnTitle(gf::SAVESLOT slot) {
  TitleMain *main = get();
  if (main != nullptr) {
    main->unknowna4 = slot;
    u32 state = main->m_fsm.getState()->m_state;
    if (state == 1 || state == 5 || state == 6) {
      main->unknown95 = true;
    }
    main->setMaskVolume(0.0f, 2.0f);
  }
}

bool TitleMain::isStateGame() const {
  if (get() != nullptr) {
    return get()->m_fsm.getState()->m_state == 5;
  }
  return false;
}

bool TitleMain::isStateEvent() const {
  if (get() != nullptr) {
    return get()->m_fsm.getState()->m_state == 6;
  }
  return false;
}

bool TitleMain::isStateSelect() const {
  if (get() != nullptr) {
    return get()->m_fsm.getState()->m_state == 1;
  }
  return false;
}

void TitleMain::setMaskVolume(f32 volume, f32 fadeTime) {
  gf::GfSound *sound = gf::GfSound::get();
  if (sound != nullptr) {
    if (unknown170 == gf::unknown019) {
      unknown170 = sound->createCategoryHandle();
      if (unknown170 == gf::unknown019) {
        return;
      }
    }
    sound->setCategoryVolume(unknown170, gf::CATEGORY_BGM, volume, fadeTime);
  }
}

bool TitleMain::isReturnTitle() {
  if (get() != nullptr) {
    return get()->m_fsm.getState()->m_state == 7;
  }
  return false;
}

void TitleMain::playTitleBGM() {
  if (!m_soundHandle.isValid()) {
    stopTitleBGM(0.0f);
    unknowna0 = true;
  }
}

bool TitleMain::isStateReturnTitle() const {
  if (get() != nullptr) {
    return get()->m_fsm.getState()->m_state == 7;
  }
  return false;
}

gf::SDataSave *TitleMain::getSaveBuffer() { return m_saveBuffer; }

gf::SDataOption *TitleMain::getOptionBuffer() { return m_optionBuffer; }

void TitleMain::clearSaveBuffer() {
  if (m_saveBuffer != nullptr) {
    new (m_saveBuffer) gf::SDataSave;
  }
}

void TitleMain::setupTitleOptionToGameOption() {
  if (m_optionBuffer != nullptr) {
    gf::GfManager::setupOptionData(*m_optionBuffer);
  }
}

void TitleMain::playTitleEvent(u32 event) {
  m_playTitleEvent = event;
  if (event != 0) {
    gf::GfPlayFactory::createOneEvent(event);
  }
}

u32 TitleMain::getPlayTitleEvent() { return m_playTitleEvent; }

void TitleMain::getGameClearFlagFromSaveData() {
  if (m_saveBuffer->unknown00 == gf::SAVE_UNKNOWN_237915 && gf::GfGameFlag::getLocal(m_saveBuffer->m_game.m_gameFlag, 1, 0xd77e) != 0) {
    unknown178 = true;
  }
}

u32 TitleMain::getChapterIdFromSaveData() {
  if (m_saveBuffer->unknown00 != gf::SAVE_UNKNOWN_237915) {
    return 0;
  }
  // The game reads the u16 at SDataSave + 0x104bd6 (ldrh at 0x7100143e6c), which is unknown9000[1], a short flag, of the game flags.
  u32 flag = m_saveBuffer->m_game.m_gameFlag.unknown9000[1];
  if (flag == 0) {
    return 0;
  }
  u32 chapter = flag / 1000;
  if (chapter == 0) {
    return 1;
  }
  return mm::min(10u, chapter);
}

} // namespace tl

template mm::mtl::PtrSingleton<tl::TitleMain>::~PtrSingleton();
template void mm::mtl::Delegate<void(tl::TitleMain *)>::staticFuncInvoker(const mm::mtl::Delegate<void(tl::TitleMain *)> *, tl::TitleMain *);
template nn::os::FiberType *MicroUpdater<tl::TitleMain>::fnMicroUpdate(void *);
