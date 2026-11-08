#include "gf/menu/object/gf_menu_obj_mercenary_root.h"

#include "gf/data/gf_data_mercenaries.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_sound_manager.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/sound/gf_sound.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x4d;

GfMenuObjMercenaryRoot::GfMenuObjMercenaryRoot(u32 handle) : GfMenuObject(handle), unknown24(-1), unknown28(this), unknown188(0) {}

GfMenuObjMercenaryRoot::~GfMenuObjMercenaryRoot() {}

void GfMenuObjMercenaryRoot::openBg(int bg) { unknown149(unknown001, GfMenuTypes::unknown003_33, bg); }

void GfMenuObjMercenaryRoot::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMercenaryRoot::update() {
  unknown28.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjMercenaryRoot::seqWaitBGStream() {
  ui::UIObjectAcc bg(unknown18, "IMG_bg");
  if (bg.isStreaming()) {
    return false;
  }
  ui::UIObjectAcc(unknown18, "IMG_bg_front").setDisp(false);
  return true;
}

void GfMenuObjMercenaryRoot::closeBg() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjMercenaryRoot::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  attachExternalCall(unknown001, main.unknown10);
// __LINE__ must be 88 as in the original file: it is the line argument of operator new.
#line 88
  MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
  if (listener != nullptr) {
    listener->release();
  }
  GfMenuObjMainMenu2::setCloseKeyEnable(false);
  GfMenuObject::initialize();
}

void GfMenuObjMercenaryRoot::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    bool found = false;
    for (u32 i = 0; i < GfDataMercenaries::getTeamNum(); i++) {
      unknown120 *team = GfDataMercenaries::getTeamByIndex(i);
      if (team != nullptr && GfDataMercenaries::isTeamStateReward(team->unknown10)) {
        GfMenuObject::changeFSSubLayer(acc.unknown10, 2, 0x37, true);
        found = true;
        break;
      }
    }
    if (!found) {
      GfMenuObject::changeFSSubLayer(acc.unknown10, 2, 0x34, true);
    }
    acc.setDispChild(false, "IMG_bg");
    acc.setDispChild(false, "IMG_bg_front");
    if (GfSound::get() != nullptr) {
      GfMenuSoundManager::fadeOutFieldBgm(0.5f);
      unknown20->unknown188 = GfMenuObjUtil::playBGM(0x16, false, CATEGORY_MENU_BGM);
    } else {
      unknown20->unknown188 = 0;
    }
    break;
  }
  case 2:
    if (GfSound::get() != nullptr) {
      GfMenuSoundManager::fadeFieldBgm(1.0f, 0.5f);
      GfMenuObjUtil::stopBGM(unknown20->unknown188, 1.0f);
      unknown20->unknown188 = 0;
    }
    acc.setTerm();
    break;
  case 3:
    if (event.unknown08 == 1) {
      ui::UIObjectAcc bg(acc.unknown10, "IMG_bg");
      bg.setImageIndex(unknown20->unknown24);
      unknown20->unknown28.unknown002(&GfMenuObjMercenaryRoot::seqWaitBGStream);
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case GfMenuTypes::unknown003_33: {
    u32 image = event.unknown08;
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    param.unknown04 = 1;
    if (unknown20->unknown24 == -1) {
      ui::UIObjectAcc bg(acc.unknown10, "IMG_bg");
      bg.setImageIndex(image);
      GfMenuObjUtil::startCtrl(acc.unknown10, param, "IMG_bg");
    } else {
      ui::UIObjectAcc bg(acc.unknown10, "IMG_bg_front");
      bg.setImageIndex(image);
      int ctrl = GfMenuObjUtil::startCtrl(acc.unknown10, param, "IMG_bg_front");
      GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
    }
    unknown20->unknown24 = image;
    unknown20->unknown28.unknown005();
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = 0.25f;
    param.unknown04 = 2;
    int ctrl = GfMenuObjUtil::startCtrl(acc.unknown10, param, "IMG_bg");
    GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
    acc.setDispChild(false, "IMG_bg_front");
    break;
  }
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjMercenaryRoot>(const mm::mtl::Delegate<bool()> *);
