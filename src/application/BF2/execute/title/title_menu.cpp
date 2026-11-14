#include "execute/title/title_menu.h"

#include "gf/gf_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/object/gf_menu_obj_ev_theater.h"
#include "gf/menu/object/gf_menu_obj_option.h"
#include "gf/menu/object/gf_menu_obj_title.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/reference_object.h"

namespace tl {

gf::GfMenuCallContext *TitleMenu::getMenuCallContext() {
  if (unknown08 == nullptr) {
    unknown08 = gf::GfMenuCallContext::create();
  }
  return unknown08;
}

void TitleMenu::destroyMenuCallContext() {
  if (unknown08 != nullptr) {
    while (!unknown08->isTerm()) {
      gf::GfSleep(1);
    }
    mm::mtl::safeRelease(unknown08);
  }
}

void TitleMenu::openTitle(bool isFadeOut) { gf::GfMenuManager::openFullScreen(3, isFadeOut, true); }

bool TitleMenu::isOpenTitle() const { return !gf::GfMenuManager::isSwitchingFullScreen(); }

void TitleMenu::setupTitle() { gf::GfMenuObjTitle::attach(getMenuCallContext()); }

bool TitleMenu::hasResultSelect() const { return !unknown08->unknown18.empty(); }

void TitleMenu::closeTitle(bool isFadeOut, bool isFadeIn) {
  gf::GfMenuManager::closeFullScreen(isFadeOut, isFadeIn);
  destroyMenuCallContext();
}

bool TitleMenu::isCloseTitle() const { return !gf::GfMenuManager::isOpenFullScreen(); }

bool TitleMenu::isCloseOption() const { return !gf::GfMenuManager::isOpenFullScreen(); }

void TitleMenu::openEventTheater() {
  if (getMenuCallContext()->isActive()) {
    gf::GfMenuObjEvTheater::fadein(getMenuCallContext());
  } else {
    gf::GfMenuManager::openFullScreen(6, true, true);
  }
}

bool TitleMenu::isOpenEventTheater() const { return !gf::GfMenuManager::isSwitchingFullScreen(); }

void TitleMenu::setupEventTheater() { gf::GfMenuObjEvTheater::attach(getMenuCallContext()); }

bool TitleMenu::hasResultEventTheater() const { return !unknown08->unknown18.empty(); }

bool TitleMenu::isExitEventTheater() const { return unknown08->isTerm(); }

void TitleMenu::openOption() { gf::GfMenuManager::openFullScreen(7, false, true); }

bool TitleMenu::isOpenOption() const { return !gf::GfMenuManager::isSwitchingFullScreen(); }

void TitleMenu::setupOption() { gf::GfMenuObjOption::attach(getMenuCallContext()); }

bool TitleMenu::hasResultOption() const { return !unknown08->unknown18.empty(); }

bool TitleMenu::isExitOption() const { return unknown08->isTerm(); }

void TitleMenu::exitOption() { destroyMenuCallContext(); }

void TitleMenu::exitEventTheater() { destroyMenuCallContext(); }

void TitleMenu::fadeoutEventTheater() { gf::GfMenuObjEvTheater::fadeout(getMenuCallContext()); }

void TitleMenu::fadeinEventTheater() { gf::GfMenuObjEvTheater::fadein(getMenuCallContext()); }

} // namespace tl
