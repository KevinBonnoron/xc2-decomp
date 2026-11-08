#include "gf/menu/object/gf_menu_obj_blade_release.h"

#include "gf/game/gf_game_voice.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_char_select.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjBladeRelease::GfMenuObjBladeRelease(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(this), unknown2e8(false),
      unknown2f0(this), unknown450(nullptr), unknown458(false), unknown460(nullptr), unknown468(false), unknown46c(-1), unknown470(nullptr), unknown4a0(false), unknown4a4(0), unknown4a8(0),
      unknown4b0(nullptr) {
  unknown450 = GfMenuItemList::create();
  unknown460 = GfMenuIDList::create();
  unknown470 = GfMenuDriverList::create();
  unknown48 = GfMenuCallContext::create();
  unknown50 = GfMenuCallContext::create();
}

GfMenuObjBladeRelease::~GfMenuObjBladeRelease() {
  mm::mtl::safeRelease(unknown470);
  mm::mtl::safeRelease(unknown460);
  mm::mtl::safeRelease(unknown450);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
}

void GfMenuObjBladeRelease::finalize() {
  if (unknown4b0 != nullptr) {
    GfGameVoice::playStop(unknown4b0);
    unknown4b0 = nullptr;
  }
  GfMenuObject::finalize();
}

void GfMenuObjBladeRelease::update() {
  unknown58.unknown003();
  unknown2f0.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjBladeRelease::seqOpenImage() {
  ui::UIObjectAcc image(unknown18, "IMG_bl_img");
  bool isEnd;
  if (!image.isStreaming()) {
    ui::UIObjectAcc main(unknown18, "LAY_main");
    u32 blade = GfMenuReference::getReferenceBladeID(0);
    main.setLayout(image.unknown10, "bl_img01");
    isEnd = true;
    GfMenuObjUtil::ImageParam param;
    if (GfMenuObjUtil::getImageParam(1, blade, param, 1)) {
      alignas(16) mm::Vec2 scale;
      image.getScale(scale);
      scale.x = param.unknown04 * scale.x;
      scale.y = param.unknown04 * scale.y;
      image.setScale(scale);
      GfMenuObjUtil::addPos(image.unknown10, param.unknown00, param.unknown02);
    }
    image.setAlpha(1.0f);
    GfMenuObjUtil::CtrlParam ctrl;
    ctrl.unknown004("fade_in_r");
    ctrl.unknown14 = 8;
    ctrl.unknown11 = true;
    GfMenuObjUtil::startCtrl(image.unknown10, ctrl, nullptr);
    image.setAlpha(0.0f);
  } else {
    image.setAlpha(0.0f);
    isEnd = false;
  }
  return isEnd;
}

void GfMenuObjBladeRelease::refreshBladeInfo(ui::UIObjectAcc &acc, u32 type) {
  u32 count = acc.countChild("LAY_list_bl_info@%02d", 1);
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < count; i++) {
    name.format("LAY_list_bl_info_wpn@%02d", i + 1);
    acc.setDispChild(type == 1, name.c_str());
    name.format("LAY_list_bl_info_elem@%02d", i + 1);
    acc.setDispChild(type == 0, name.c_str());
    name.format("LAY_list_bl_info_role@%02d", i + 1);
    acc.setDispChild(type == 2, name.c_str());
  }
}

bool GfMenuObjBladeRelease::seqEffReleaseA() {
  ui::UIObjectAcc acc(unknown18, "IMG_bl_img");
  int ctrl = GfMenuObjUtil::getCtrlID(acc.unknown10);
  bool isEnd;
  if (!unknown2e8) {
    u32 blade = unknown30->getContents(unknown30->getIndex(false)).unknown00;
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x40000000;
    param.unknown38 = 1.0f;
    param.unknown00 = 1.0f;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    unknown4b0 = SCOM_FIELD_VOICE::createReleaseBlade(blade);
    isEnd = false;
    unknown2e8 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(ctrl) && static_cast<int>(GfGameVoice::getResult(unknown4b0)) > VOICE_RESULT_PLAY) {
    isEnd = true;
    unknown4b0 = nullptr;
    unknown2e8 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjBladeRelease::seqEffReleaseB() {
  ui::UIObjectAcc acc(unknown18, "LAY_bl_img");
  int ctrl = GfMenuObjUtil::getCtrlID(acc.unknown10);
  bool isEnd;
  if (!unknown2e8) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = 1.0f;
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    isEnd = false;
    unknown2e8 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(ctrl)) {
    ui::UIObjectAcc image(unknown18, "IMG_bl_img");
    image.setAddColor("black");
    unknown2e8 = false;
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjBladeRelease::seqConfirmBoosterGet() {
  if (unknown450->getSize() != 0) {
    if (!unknown2e8) {
      unknown48->reset();
      GfMenuObjCommonText::openGetItem(unknown48, unknown450);
      unknown2e8 = true;
      return false;
    }
    if (!unknown48->isTerm()) {
      return false;
    }
    unknown2e8 = false;
  }
  return true;
}

bool GfMenuObjBladeRelease::seqResumeRelease() {
  ui::UIObjectAcc list(unknown18, "LAY_list_bl");
  sendOpenEvent(list.unknown10, 0, 0.0f);
  GfMenuObjMainMenu2::setCloseKeyEnable(true);
  ui::UIObjectAcc image(unknown18, "LAY_bl_img");
  image.setDisp(true);
  image.setAlpha(1.0f);
  return true;
}

bool GfMenuObjBladeRelease::seqEffReleaseC() {
  ui::UIObjectAcc acc(unknown18, "IMG_bl_img_booster");
  int ctrl = GfMenuObjUtil::getCtrlID(acc.unknown10);
  bool isEnd;
  if (!unknown2e8) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x40000000;
    param.unknown00 = 1.0f;
    param.unknown14 = 4;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    isEnd = false;
    unknown2e8 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(ctrl)) {
    isEnd = true;
    unknown2e8 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjBladeRelease::seqEffReleaseD() {
  ui::UIObjectAcc acc(unknown18, "IMG_bl_img_booster");
  int ctrl = GfMenuObjUtil::getCtrlID(acc.unknown10);
  bool isEnd;
  if (!unknown2e8) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = 1.0f;
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    isEnd = false;
    unknown2e8 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(ctrl)) {
    isEnd = true;
    unknown2e8 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjBladeRelease::seqSubMenuEnd() {
  ui::UIObjectAcc list(unknown18, "LAY_list_bl");
  sendOpenEvent(list.unknown10, 1, 0.0f);
  GfMenuObjMainMenu2::setCloseKeyEnable(true);
  unknown2e8 = false;
  return true;
}

bool GfMenuObjBladeRelease::seqSubMenuOpenCustomize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  GfMenuObjUtil::setCommonFadeOut(main.searchChild("LAY_list_bl"), 0, 0);
  GfMenuObjUtil::setCommonFadeOut(main.searchChild("LAY_index"), 0, 0);
  const MenuBladeInfo &info = unknown30->getContents(unknown30->getIndex(false));
  GfMenuObjCharSelect::openBladeCustomize(main.unknown10, info.unknown00, GfMenuFullScreen::getLayerGroup(unknown20) + 1);
  unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuWaitLoadCustomize);
  return true;
}

bool GfMenuObjBladeRelease::seqSubMenuErrorOvdOnly() {
  bool isEnd;
  if (!unknown2e8) {
    GfMenuManager::openCommonWindow(0xdd);
    isEnd = false;
    unknown2e8 = true;
  } else if (!GfMenuManager::isOpenCommonWindow()) {
    unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuOpen);
    isEnd = true;
    unknown2e8 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjBladeRelease::seqSubMenuErrorOvdLastOne() {
  bool isEnd;
  if (!unknown2e8) {
    GfMenuManager::openCommonWindow(0xde);
    isEnd = false;
    unknown2e8 = true;
  } else if (!GfMenuManager::isOpenCommonWindow()) {
    unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuOpen);
    isEnd = true;
    unknown2e8 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjBladeRelease::seqSubMenuWaitLoadCustomize() {
  if (!GfMenuManager::isSwitchingFullScreen()) {
    unknown50->reset();
    if (GfMenuObjCharSelect::attach(unknown50)) {
      unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuWaitEndCustomize);
      ui::UIObjectAcc main(unknown18, "LAY_main");
      main.setDispChild(false, "LAY_bl_img");
      return true;
    }
  }
  return false;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBladeRelease>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjBladeRelease, 8>>(const mm::mtl::Delegate<bool()> *);
