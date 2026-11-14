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
    : unknown08(fw::FrameworkMemory::getAllocator(5)), unknown80(nullptr), unknown94(false), unknown95(false), unknown98(0), unknowna0(false), unknowna4(gf::SAVESLOT_UNKNOWN_FFFFFFFF),
      unknown130(nullptr), unknown138(nullptr), unknown168(0), unknown170(gf::unknown019), unknown178(false) {}

TitleMain::~TitleMain() {}

TitleMain *TitleMain::create() {
#line 94
  TitleMain *main = new (fw::FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) TitleMain();
  main->initialize();
  return main;
}

void TitleMain::initialize() {
  createSaveBuffer();
  unknown08.beginSetup(this, 9);
  unknown08.registerState<TitleStateLoad>(0);
  unknown08.registerState<TitleStateMainScreen>(1);
  unknown08.registerState<TitleStatePlayGame>(5);
  unknown08.registerState<TitleStatePlayEvent>(6);
  unknown08.registerState<TitleStateToTitle>(7);
  unknown08.registerState<TitleStateDebugSaveContinue>(2);
  unknown08.registerState<TitleStateSelectEvent>(3);
  unknown08.registerState<TitleStateSelectOption>(4);
  unknown08.registerState<TitleStateDebugSaveContinue>(8);
  unknown08.endSetup();
  unknown08.setState(0);
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

void TitleMain::destroy() {
  TitleMain *main = get();
  main->finalize();
  delete main;
}

void TitleMain::createSaveBuffer() {
  if (unknown130 == nullptr) {
    unknown130 = new (ml::WorkRootMem::getMemTMP(), nullptr, 0, 4, false) gf::SDataSave;
  } else {
    new (unknown130) gf::SDataSave;
  }
  if (unknown138 == nullptr) {
    unknown138 = new (ml::WorkRootMem::getMemTMP(), nullptr, 0, 4, false) gf::SDataOption;
  } else {
    new (unknown138) gf::SDataOption;
  }
  gf::GfMenuManager::initOptionData(*unknown138);
}

void TitleMain::fnUpdate(TitleMain *main) {
  main->unknown08.update(&main->unknown88);
  while (main->unknown08.getState()->unknown08 != 8) {
    ml::MicroThread::get()->sleep(1, true);
    main->unknown08.update(&main->unknown88);
  }
}

void TitleMain::destroyMaskVolume() {
  if (gf::GfSound::get() != nullptr) {
    gf::GfSound::get()->releaseCategoryHandle(unknown170);
  }
}

void TitleMain::stopTitleBGM(f32 fadeTime) {
  if (unknown98.isValid()) {
    if (gf::GfSound::get() != nullptr) {
      gf::GfSound::get()->stopBgm(unknown98, fadeTime);
    }
    unknown98.clear();
    unknowna0 = false;
  }
}

void TitleMain::destroySaveBuffer() {
  if (unknown130 != nullptr) {
    delete unknown130;
    unknown130 = nullptr;
  }
  if (unknown138 != nullptr) {
    delete unknown138;
    unknown138 = nullptr;
  }
}

void TitleMain::update(const fw::UpdateInfo &info) {
  TitleMain *main = get();
  if (main != nullptr) {
    if (main->unknowna0) {
      gf::GfSound *sound = gf::GfSound::get();
      if (sound != nullptr && !sound->isPlaying(main->unknown98)) {
        main->unknown98 = sound->playBgm("stream/bgm/m02.wav", 1.0f, false, -1, gf::CATEGORY_EVT_BGM);
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
    u32 state = main->unknown08.getState()->unknown08;
    if (state == 1 || state == 5 || state == 6) {
      main->unknown95 = true;
    }
    main->setMaskVolume(0.0f, 2.0f);
  }
}

bool TitleMain::isStateGame() const {
  if (get() != nullptr) {
    return get()->unknown08.getState()->unknown08 == 5;
  }
  return false;
}

bool TitleMain::isStateEvent() const {
  if (get() != nullptr) {
    return get()->unknown08.getState()->unknown08 == 6;
  }
  return false;
}

bool TitleMain::isStateSelect() const {
  if (get() != nullptr) {
    return get()->unknown08.getState()->unknown08 == 1;
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
    return get()->unknown08.getState()->unknown08 == 7;
  }
  return false;
}

void TitleMain::playTitleBGM() {
  if (!unknown98.isValid()) {
    stopTitleBGM(0.0f);
    unknowna0 = true;
  }
}

bool TitleMain::isStateReturnTitle() const {
  if (get() != nullptr) {
    return get()->unknown08.getState()->unknown08 == 7;
  }
  return false;
}

gf::SDataSave *TitleMain::getSaveBuffer() { return unknown130; }

gf::SDataOption *TitleMain::getOptionBuffer() { return unknown138; }

void TitleMain::clearSaveBuffer() {
  if (unknown130 != nullptr) {
    new (unknown130) gf::SDataSave;
  }
}

void TitleMain::setupTitleOptionToGameOption() {
  if (unknown138 != nullptr) {
    gf::GfManager::setupOptionData(*unknown138);
  }
}

void TitleMain::playTitleEvent(u32 event) {
  unknown168 = event;
  if (event != 0) {
    gf::GfPlayFactory::createOneEvent(event);
  }
}

u32 TitleMain::getPlayTitleEvent() { return unknown168; }

void TitleMain::getGameClearFlagFromSaveData() {
  if (unknown130->unknown00 == gf::SAVE_UNKNOWN_237915 && gf::GfGameFlag::getLocal(unknown130->unknown10.unknownfbbc4, 1, 0xd77e) != 0) {
    unknown178 = true;
  }
}

} // namespace tl

template mm::mtl::PtrSingleton<tl::TitleMain>::~PtrSingleton();
template void mm::mtl::Delegate<void(tl::TitleMain *)>::staticFuncInvoker(const mm::mtl::Delegate<void(tl::TitleMain *)> *, tl::TitleMain *);
template nn::os::FiberType *MicroUpdater<tl::TitleMain>::fnMicroUpdate(void *);
