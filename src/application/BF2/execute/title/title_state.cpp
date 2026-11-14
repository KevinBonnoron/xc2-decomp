#include "execute/title/title_main.h"
#include "execute/title/title_menu.h"
#include "execute/title/title_state_debug_save_continue.h"
#include "execute/title/title_state_load.h"
#include "execute/title/title_state_main_screen.h"
#include "execute/title/title_state_play_event.h"
#include "execute/title/title_state_play_game.h"
#include "execute/title/title_state_select_event.h"
#include "execute/title/title_state_select_option.h"
#include "execute/title/title_state_to_title.h"
#include "framework/render/render_param.h"
#include "gf/data/gf_data_event.h"
#include "gf/data/gf_data_save.h"
#include "gf/event/gf_event.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/game/sequential_play/gf_sequential_play.h"
#include "gf/gf_manager.h"
#include "gf/map/gf_map_manager.h"
#include "gf/menu/object/gf_menu_obj_ev_theater.h"
#include "gf/request/gf_req_manager.h"
#include "gf/scom/gf_scom_fade.h"
#include "ml/time_count.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace ai {
class State;
} // namespace ai
namespace fw {
struct UpdateInfo;
} // namespace fw

namespace tl {

// Inferred role: event played by the title for each chapter; original name unknown.
static const u16 unknown001[12] = {0x2711, 0x2908, 0x2909, 0x290a, 0x290b, 0x290c, 0x290d, 0x290e, 0x290f, 0x2910, 0x2911, 0};

void TitleStateLoad::update(TitleMain *main, const fw::UpdateInfo &info) {
  unknown18.reset();
  main->unknown158.unknown00 = 0;
  reqState(1);
  main->unknowna4 = gf::SAVESLOT_UNKNOWN_FFFFFFFF;
}

void TitleStateMainScreen::gevPlayEvent(gf::GEV event, u32 value) {
  if (event == gf::GEV_UNKNOWN_13) {
    unknown20 = 1;
  }
}

bool TitleStateMainScreen::checkReturnEvent(TitleMain *main) {
  if (main->unknown140.size() == 0) {
    return false;
  }
  reqState(3);
  return true;
}

void TitleStateMainScreen::playTitleEvent(TitleMain *main) {
  u32 chapter = main->getChapterIdFromSaveData();
  if (chapter > 11) {
    chapter = 11;
  }
  unknown20 = 0;
  gf::SCOM_FADE::create(0, 0, mm::Col4::black);
  gf::SCOM_FADE::create(1, 0, mm::Col4::black);
  gf::SCOM_FADE::create(2, 0, mm::Col4::black);
  main->playTitleEvent(unknown001[chapter]);
  while (unknown20 != 1) {
    TitleMain::sleep(1);
  }
  fw::RenderParam::resetScene();
  gf::SCOM_FADE::create(0, 15, mm::Col4::zero);
  gf::SCOM_FADE::create(1, 15, mm::Col4::zero);
  gf::SCOM_FADE::create(2, 15, mm::Col4::zero);
}

bool TitleStateMainScreen::dispTitleMenu(TitleMain *main, bool isPlayEvent) {
  TitleMenu &menu = main->unknown158;
  main->playTitleBGM();
  menu.openTitle(isPlayEvent);
  while (!menu.isOpenTitle()) {
    if (main->unknown94) {
      reqState(8);
      return true;
    }
    TitleMain::sleep(1);
  }
  menu.setupTitle();
  return false;
}

bool TitleStateMainScreen::checkMenuResult(TitleMain *main) {
  while (!main->unknown158.hasResultSelect()) {
    if (main->unknown95) {
      main->unknown158.closeTitle(true, true);
      main->unknown95 = false;
      reqState(7);
      return true;
    }
    if (main->unknown94) {
      main->unknown158.closeTitle(true, true);
      reqState(8);
      return true;
    }
    TitleMain::sleep(1);
  }
  main->unknown158.unknown00 = main->unknown158.getResult();
  return false;
}

void TitleStateMainScreen::enter(TitleMain *main, ai::State *previous) { gf::GfEvent::addEventCallback(this); }

void TitleStateMainScreen::leave(TitleMain *main, ai::State *next) { gf::GfEvent::removeEventCallback(this); }

void TitleStatePlayGame::gevPlayEvent(gf::GEV event, u32 value) {
  if (event == gf::GEV_UNKNOWN_13) {
    unknown20 = 2;
  } else if (event == gf::GEV_UNKNOWN_12) {
    unknown20 = 0;
  }
}

void TitleStatePlayGame::leave(TitleMain *main, ai::State *next) { gf::GfEvent::removeEventCallback(this); }

void TitleStatePlayGame::update(TitleMain *main, const fw::UpdateInfo &info) {
  while (true) {
    if (main->unknown95) {
      main->unknown95 = false;
      reqState(7);
      return;
    }
    if (main->unknown94) {
      reqState(8);
      return;
    }
    TitleMain::sleep(1);
  }
}

bool TitleStateDebugSaveContinue::updateCheck(TitleMain *main) {
  if (!main->unknown95) {
    if (!main->unknown94) {
      return false;
    }
    reqState(8);
  } else {
    main->unknown95 = false;
    reqState(7);
  }
  return true;
}

void TitleStatePlayEvent::enter(TitleMain *main, ai::State *previous) {
  unknown18 = gf::GfDataEvent::isBladeCreateEvent(main->unknown140[0]);
  main->stopTitleBGM(2.0f);
  gf::GfManager::setupEventTheater();
  gf::SCOM_FADE::create(0, 15, mm::Col4::black);
  gf::SCOM_FADE::create(1, 15, mm::Col4::black);
  gf::SCOM_FADE::create(2, 15, mm::Col4::black);
  TitleMain::sleep(15);
  main->setMaskVolume(1.0f, 0.5f);
  gf::GfManager::startEventTheater(main->unknown140);
  if (unknown18) {
    gf::GfMenuObjEvTheater::dispOffScreen(true);
  }
}

void TitleStatePlayEvent::leave(TitleMain *main, ai::State *next) {
  if (unknown18) {
    gf::GfMenuObjEvTheater::dispOffScreen(false);
  }
}

void TitleStatePlayEvent::update(TitleMain *main, const fw::UpdateInfo &info) {
  while (true) {
    if (main->unknown95) {
      main->unknown95 = false;
      reqState(7);
      return;
    }
    if (main->unknown94) {
      reqState(8);
      return;
    }
    TitleMain::sleep(1);
  }
}

void TitleStateToTitle::update(TitleMain *main, const fw::UpdateInfo &info) {
  gf::GfManager::execToAdvertize();
  main->unknown158.unknown00 = 0;
  while (gf::GfSequentialPlay::isPlay()) {
    TitleMain::sleep(1);
  }
  while (gf::GfReqManager::isExistCommand(nullptr)) {
    TitleMain::sleep(1);
  }
  while (!gf::GfMapManager::isMapReady()) {
    TitleMain::sleep(1);
  }
  gf::GfManager::setupReturnTitle();
  gf::GfManager::setExec(gf::EXEC_STATE_UNKNOWN_2);
  if (!main->unknown94) {
    reqState(1);
  } else {
    reqState(8);
  }
}

void TitleStateSelectEvent::enter(TitleMain *main, ai::State *previous) { gf::GfGameEvent::stop(); }

void TitleStateSelectEvent::update(TitleMain *main, const fw::UpdateInfo &info) {
  if (eventMenuDisp(main)) {
    return;
  }
  if (eventMenuResult(main)) {
    return;
  }
  eventMenuWaitFadeout(main);
}

bool TitleStateSelectEvent::eventMenuDisp(TitleMain *main) {
  main->unknown158.openEventTheater();
  while (!main->unknown158.isOpenEventTheater()) {
    if (main->unknown94) {
      reqState(8);
      return true;
    }
    TitleMain::sleep(1);
  }
  main->unknown158.setupEventTheater();
  return false;
}

bool TitleStateSelectEvent::eventMenuResult(TitleMain *main) {
  while (!main->unknown158.hasResultEventTheater()) {
    if (main->unknown158.isExitEventTheater()) {
      main->unknown158.exitEventTheater();
      main->unknown95 = false;
      reqState(1);
      return true;
    }
    TitleMain::sleep(1);
  }
  if (main->unknown158.getPlayEventID() == 0) {
    return true;
  }
  mm::mtl::FixedVector<u16, 8> events;
  events.push_back(main->unknown158.getPlayEventID());
  main->unknown140 = events;
  return false;
}

bool TitleStateSelectEvent::eventMenuWaitFadeout(TitleMain *main) {
  main->unknown158.fadeoutEventTheater();
  reqState(6);
  return true;
}

void TitleStateSelectOption::enter(TitleMain *main, ai::State *previous) {}

void TitleStateSelectOption::update(TitleMain *main, const fw::UpdateInfo &info) {
  if (optionMenuDisp(main)) {
    return;
  }
  if (optionMenuResult(main)) {
    return;
  }
  optionMenuWaitFadeout(main);
}

bool TitleStateSelectOption::optionMenuDisp(TitleMain *main) {
  main->unknown158.openOption();
  while (!main->unknown158.isOpenOption()) {
    if (main->unknown94) {
      reqState(8);
      return true;
    }
    TitleMain::sleep(1);
  }
  main->unknown158.setupOption();
  return false;
}

bool TitleStateSelectOption::optionMenuResult(TitleMain *main) {
  while (!main->unknown158.isExitOption()) {
    TitleMain::sleep(1);
  }
  main->unknown158.exitOption();
  return false;
}

bool TitleStateSelectOption::optionMenuWaitFadeout(TitleMain *main) {
  while (!main->unknown158.isCloseTitle()) {
    TitleMain::sleep(1);
  }
  main->unknown95 = false;
  reqState(1);
  return true;
}

} // namespace tl
