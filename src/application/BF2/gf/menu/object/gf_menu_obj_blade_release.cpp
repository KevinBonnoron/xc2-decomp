#include "gf/menu/object/gf_menu_obj_blade_release.h"

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_item_id.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/gf_game_voice.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_char_select.h"
#include "gf/menu/object/gf_menu_obj_cmn_status.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_sort.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "gf/util/gf_item_util.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/vector.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: identifiers of the entries of the sub menu; original names unknown.
enum unknown001 {
  unknown001_1 = 1,
  unknown001_2 = 2,
  unknown001_3 = 3,
  unknown001_4 = 4,
};

// Inferred role: adds an entry to the identifier list of the sub menu; original name unknown.
static void unknown002(GfMenuIDList *list, u32 id) {
  MenuID item = {id};
  list->addContents(item);
}

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

void GfMenuObjBladeRelease::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  mm::mtl::FixStr<32> name;
// __LINE__ must be 131 as in the original file: it is the line argument of operator new.
#line 131
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  unknown30 = GfMenuBladeList::create();
  {
    GfMenuBladeList::ReleasbleSetup releasbleSetup;
    releasbleSetup.unknown00.unknown08 = 3;
    releasbleSetup.unknown00.unknown0c = 5;
    unknown30->clear();
    unknown30->setupFromReleasble(releasbleSetup);
  }
  GfMenuReference::setReferenceBladeID(0, 0);
  {
    ui::UIObjectAcc list(main.unknown10, "LAY_list_bl");
    {
      ui::UISelectObjList::CreateParam createParam = {};
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      unknown38 = ui::UISelectObjList::create(createParam);
    }
    unknown38->pickupObject(list.unknown10, "LAY_list_bl@%02d", 1);
    ui::UICtrlCursorSelect::CursorSetting setting;
    setting.setType(0);
    setting.unknown18 = 0;
    setting.unknown08 = "loop";
    unknown40 = ui::UICtrlCursorSelect::create(list.searchChild("IMG_list_bl_cursor"), setting, unknown38);
    // Ruling 8 (P4): the five blocks below (face, element, weapon, role, mercenary: format the child name, then createFromBladeList on it; the weapon block adds the base lookup) are written out as in
    // the game (0x7100400f24), like the same format/searchChild blocks of GfMenuObjBlOrb::initialize and GfMenuObjBlEquip::setupItemList. A file-local helper taking the format and the type (the name
    // buffer passed by reference, as the frame holds a single FixStr) gives 398 instructions against the game's 393.
    for (u32 i = 0; i < unknown38->getSize(); i++) {
      name.format("IMG_list_bl_face@%02d", i + 1);
      GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.c_str()), 3, unknown30, i, false);
      name.format("IMG_list_bl_info_elem@%02d", i + 1);
      GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.c_str()), 0x2a, unknown30, i, false);
      name.format("IMG_list_bl_info_wpn@%02d", i + 1);
      GfMenuCharDataAdapter *weapon = GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.c_str()), 0x29, unknown30, i, false);
      if (weapon != nullptr) {
        name.format("IMG_list_bl_info_wpn_base@%02d", i + 1);
        weapon->unknown24 = list.searchChild(name.c_str());
      }
      name.format("IMG_list_bl_info_role@%02d", i + 1);
      GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.c_str()), 0x42, unknown30, i, false);
      name.format("IMG_list_bl_info_mer@%02d", i + 1);
      GfMenuCharDataAdapter::createFromBladeList(list.searchChild(name.c_str()), 0x53, unknown30, i, false);
    }
    GfMenuObjUtil::createVScrollBarPlugin(list.searchChild("IMG_list_bl_scroll_bar"), unknown30, "IMG_list_bl_scroll_bar_base", true);
// __LINE__ must be 204 as in the original file: it is the line argument of operator new.
#line 204
    ListListener *listListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
    listListener->addRef();
    ui::UIEventManager::get()->registObjectListener(list.unknown10, listListener);
    if (listListener != nullptr) {
      listListener->release();
    }
    setFSInputObject(1, list.unknown10);
    sendOpenEvent(list.unknown10, 0, 0.0f);
  }
  {
    ui::UIObjectAcc layout(main.unknown10, "LAY_bl_img");
    ui::UIObjectAcc image(layout.unknown10, "IMG_bl_img");
    GfMenuCharDataAdapter::createFromReferenceBlade(layout.searchChild("IMG_bl_img"), 0x36, 0, false);
    image.setAlpha(0.0f);
    image.setStreamImage2nd();
  }
  {
    ui::UIListInfoBase::SetupParam param;
    param.unknown08 = 3;
    unknown460->setup(getAllocator(ALLOCATOR_UNKNOWN_0), param);
  }
  GfPartySelect::getDriverList(unknown478, GfPartySelect::LIST_TYPE_UNKNOWN_2, 0);
  u16 *driver = unknown478.begin();
  while (driver != unknown478.end()) {
    if (*driver == 1) {
      if (GfGameManager::isRexAwakening()) {
        unknown4a0 = true;
        driver = unknown478.erase(driver);
        continue;
      }
      // The game tests the driver a second time here (the loop is peeled around the erase; initialize 0x7100400f24, the second `cmp #1` after isRexAwakening); the statement is kept as written in the
      // game (P3).
      if (*driver == 1) {
        unknown4a0 = true;
      }
      driver++;
    } else if (*driver == 2 || *driver == 3 || *driver == 6) {
      driver++;
    } else {
      driver = unknown478.erase(driver);
    }
  }
  ui::UIListInfoBase::SetupParam driverParam;
  driverParam.unknown08 = unknown478.size();
  unknown470->setup(getAllocator(ALLOCATOR_UNKNOWN_0), driverParam);
  GfMenuObject::initialize();
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
      mm::Vec2 scale;
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

void GfMenuObjBladeRelease::ListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    {
      ui::UIObjectAcc sort(unknown20->unknown18, "LAY_sort");
      u16 sortId = GfMenuObjSort::getSortID(1, 0);
      GfMenuObjSort::setSortLabelText(sortId, sort.searchChild("TXT_sort_label"));
      unknown20->unknown4a4 = 0;
      unknown20->unknown30->sort(sortId, false);
    }
    GfMenuObjCmnStatus::openBlStatus(1, -1);
    unknown20->refreshBladeInfo(acc, unknown20->unknown4a8);
    unknown0c = 0;
    break;
  }
  case 6: {
    u64 param = event.unknown08_u64;
    u32 index = param;
    if (index != 0xffffffff) {
      u32 previous = param >> 32;
      unknown20->unknown30->setIndex(index);
      int rowOffset = unknown20->unknown30->getRowOffset();
      int columnSize = unknown20->unknown30->getColumnSize();
      u32 pageIndex = index - columnSize * rowOffset;
      unknown20->unknown38->setIndex(pageIndex);
      u32 blade = unknown20->unknown30->getContents(index).unknown00;
      bool isDifferentImage = GfMenuObjUtil::isBladeDifferentImage(blade, GfMenuReference::getReferenceBladeID(0));
      GfMenuReference::setReferenceBladeID(0, blade);
      if (isDifferentImage) {
        ui::UIObjectAcc image(unknown20->unknown18, "IMG_bl_img");
        int ctrl = GfMenuObjUtil::getCtrlID(image.unknown10);
        if (ctrl != -1) {
          GfMenuObjUtil::stopCtrl(ctrl);
        }
        image.setAlpha(0.0f);
        ui::UIObjectAcc main(unknown20->unknown18, "LAY_main");
        ui::EventData sendData;
        sendData.unknown00 = 0x101;
        GfMenuObject::sendEvent(main.unknown10, sendData, 0.0f);
      }
      if (previous != 0xffffffff && index != previous) {
        GfMenuObjUtil::playSECommonCursor();
      }
    }
    unknown0c = index;
    break;
  }
  case 8: {
    u32 type = event.unknown0c;
    u32 item = event.unknown08;
    switch (type) {
    case 1:
      if (item < unknown20->unknown30->getSize() && !GfDataBlade::isActivateMercenaryTeam(unknown20->unknown30->getContents(unknown20->unknown30->getIndex(false)).unknown00)) {
        GfMenuObjMainMenu2::setCloseKeyEnable(false);
        GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
        unknown20->unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuOpen);
        GfMenuObject::disableFSInput();
        unknown20->unknown40->setDisp(false);
      } else {
        GfMenuObjUtil::playSECommon(2);
      }
      break;
    case 2:
      GfMenuObjCmnStatus::closeBlStatus();
      GfMenuObject::returnFSSubLayer(unknown20);
      GfMenuObject::disableFSInput();
      GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
      GfMenuObjUtil::playSECommonCancel();
      break;
    case 0xd:
      unknown20->unknown4a8++;
      if (unknown20->unknown4a8 > 2) {
        unknown20->unknown4a8 = 0;
      }
      unknown20->refreshBladeInfo(acc, unknown20->unknown4a8);
      GfMenuObjUtil::playSE(0x1c);
      break;
    case 0x10:
      if (item < unknown20->unknown30->getSize()) {
        u32 blade = unknown20->unknown30->getContents(unknown20->unknown30->getIndex(false)).unknown00;
        if (GfMenuObjUtil::isBladeReleasable(blade, nullptr)) {
          GfMenuObjMainMenu2::setCloseKeyEnable(false);
          GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
          unknown20->unknown2e8 = false;
          unknown20->unknown58.unknown005();
          unknown20->unknown58.unknown002(&GfMenuObjBladeRelease::seqConfirmRelease);
          GfMenuObject::disableFSInput();
          unknown20->unknown40->setDisp(false);
          break;
        }
        if (GfDataBlade::isActivateDriver(blade)) {
          GfMenuManager::openCommonWindow(0xae);
          break;
        }
        if (GfDataBlade::isReleaseLock(blade) || GfMenuObjUtil::isBladeLastOne(blade, nullptr) || blade == GfDataBlade::getStartCommonBlade()) {
          GfMenuManager::openCommonWindow(0xad);
          break;
        }
      }
      GfMenuObjUtil::playSECommon(2);
      break;
    case 0x11: {
      ui::UIObjectAcc label(unknown20->unknown18, "TXT_sort_label");
      GfMenuObjSort::open(acc.unknown10, label.unknown10, 1, unknown20->unknown4a4);
      GfMenuObject::disableInput(handle);
      GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
      break;
    }
    case 0x12:
      GfMenuObjOperationInfo::changeText(handle, 0x12, !GfMenuObjCmnStatus::swapBlStatus());
      break;
    }
    break;
  }
  case 0x21: {
    int param = event.unknown08;
    GfMenuObject::resetInputSelection(acc.unknown10);
    u32 size = unknown20->unknown30->getSize();
    u32 padding = 0;
    if (size % 5 != 0) {
      padding = 5 - size % 5;
    }
    size += padding;
    GfMenuObject::setupInputSelection(acc.unknown10, unknown20->unknown30->getIndex(false), size);
    unknown0c = unknown20->unknown30->getIndex(false);
    GfMenuObject::setupPadLineSelection(acc.unknown10, 5);
    GfMenuObject::enableFSInput(1);
    GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    if (param != 1) {
      GfMenuObjOperationInfo::setGuideText(0x21, 0);
      GfMenuObjMainMenu2::setSubIndexText(0x14);
    }
    GfMenuObjOperationInfo::changeText(handle, 0x12, false);
    unknown20->unknown40->setDisp(true);
    break;
  }
  case 0x22:
    break;
  default:
    if (event.unknown00 == 0x148) {
      GfMenuObject::enableInput(handle);
      GfMenuObjOperationInfo::add(handle, 0, 0, 0);
      if (unknown20->unknown4a4 == event.unknown08) {
        break;
      }
      u16 sortId = GfMenuObjSort::getSortID(1, event.unknown08);
      if ((sortId & 0xfffe) == 4) {
        unknown20->unknown30->sort(sortId, true);
      } else {
        unknown20->unknown30->sort(sortId, false);
      }
      unknown20->unknown4a4 = event.unknown08;
      u32 blade = unknown20->unknown30->getContents(unknown0c).unknown00;
      bool isDifferentImage = GfMenuObjUtil::isBladeDifferentImage(blade, GfMenuReference::getReferenceBladeID(0));
      GfMenuReference::setReferenceBladeID(0, blade);
      if (!isDifferentImage) {
        break;
      }
      ui::UIObjectAcc image(unknown20->unknown18, "IMG_bl_img");
      int ctrl = GfMenuObjUtil::getCtrlID(image.unknown10);
      if (ctrl != -1) {
        GfMenuObjUtil::stopCtrl(ctrl);
      }
      image.setAlpha(0.0f);
      ui::UIObjectAcc main(unknown20->unknown18, "LAY_main");
      ui::EventData sendData;
      sendData.unknown00 = 0x101;
      GfMenuObject::sendEvent(main.unknown10, sendData, 0.0f);
    } else {
      ui::UIObjectListener::reciveEvent(event, handle);
    }
    break;
  }
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
  } else if (!GfMenuObjUtil::isBusyCtrl(ctrl) && static_cast<int>(GfGameVoice::getResult(unknown4b0)) > CV_RESULT_UNKNOWN_2) {
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

bool GfMenuObjBladeRelease::seqSubMenuWaitEndCustomize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (!unknown50->unknown18.empty()) {
    GfMenuCallContext::GfMenuResult result;
    unknown50->popResult(result);
  }
  if (!unknown50->isTerm()) {
    return false;
  }
  GfMenuObjUtil::setCommonFadeIn(main.searchChild("LAY_bl_img"), 0, 0);
  GfMenuObjUtil::setCommonFadeIn(main.searchChild("LAY_list_bl"), 0, 0);
  GfMenuObjUtil::setCommonFadeIn(main.searchChild("LAY_index"), 0, 0);
  unknown58.unknown004(5);
  unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuEnd);
  GfMenuObjOperationInfo::setGuideText(0x21, 0);
  GfMenuObjMainMenu2::setSubIndexText(0x14);
  return true;
}

bool GfMenuObjBladeRelease::seqConfirmRelease() {
  if (!unknown2e8) {
    GfMenuManager::openCommonWindow(0x11);
    unknown2e8 = true;
    return false;
  }
  if (GfMenuManager::isOpenCommonWindow()) {
    return false;
  }
  s16 result = GfMenuManager::getCommonWindowResult();
  if (result == 0) {
    unknown58.unknown002(&GfMenuObjBladeRelease::seqEffReleaseA);
    unknown58.unknown002(&GfMenuObjBladeRelease::seqEffReleaseB);
    unknown58.unknown002(&GfMenuObjBladeRelease::seqExecRelease);
    unknown58.unknown002(&GfMenuObjBladeRelease::seqConfirmBoosterGet);
    unknown58.unknown002(&GfMenuObjBladeRelease::seqResumeRelease);
  } else {
    unknown58.unknown002(&GfMenuObjBladeRelease::seqResumeRelease);
  }
  unknown2e8 = false;
  return true;
}

bool GfMenuObjBladeRelease::seqExecRelease() {
  static mm::mtl::FixedVector<GfItem, 1024> items;
  u32 blade = unknown30->getContents(unknown30->getIndex(false)).unknown00;
  items.clear();
  GfGameUtil::execBoosterAddForReleaseBlade(items, blade);
  {
    ui::UIListInfoBase::SetupParam param;
    param.unknown08 = items.size();
    if (param.unknown08 == 0) {
      param.unknown08 = 1;
    }
    unknown450->setup(getAllocator(ALLOCATOR_UNKNOWN_0), param);
  }
  MenuItemInfo info;
  for (u32 i = 0; i < items.size(); i++) {
    info.unknown04 = items.at(i)->unknown00;
    info.unknown00 = GfItemUtil::getType(items.at(i)->unknown00);
    info.unknown08 = 1;
    unknown450->addItem(info, false);
  }
  GfGameUtil::execActivateUnuseForBlade(blade, true);
  for (u32 i = 0; i < unknown30->getSize(); i++) {
    if (unknown30->getContents(i).unknown00 == blade) {
      GfMenuBladeList *list = unknown30;
      list->contents.erase(list->contents.begin() + i);
      list->subSize(1);
      list->contentsChanged = true;
      break;
    }
  }
  GfMenuReference::setReferenceBladeID(0, 0);
  return true;
}

bool GfMenuObjBladeRelease::seqSubMenuOpen() {
  if (!unknown2e8) {
    const MenuBladeInfo &blade = unknown30->getContents(unknown30->getIndex(false));
    unknown460->clear();
    unknown002(unknown460, unknown001_1);
    if (!GfMenuObjUtil::isScenarioBlade(blade.unknown00) && blade.unknown00 != GfDataBlade::getStartCommonBlade() && !unknown478.empty() && GfItemUtil::getItemBoxCount(ITEM_UNKNOWN_25408) != 0 &&
        (unknown478.size() != 1 || unknown478.front() != blade.unknown04)) {
      unknown002(unknown460, unknown001_2);
    }
    unknown48->reset();
    GfMenuObjCommonText::openSubMenu(unknown48, unknown460);
    unknown2e8 = true;
    unknown46c = -1;
    return false;
  }
  if (!unknown48->unknown18.empty()) {
    GfMenuCallContext::GfMenuResult result;
    if (unknown48->popResult(result) && result.unknown00 == 0) {
      unknown46c = result.unknown04;
    }
  }
  if (!unknown48->isTerm()) {
    return false;
  }
  if (unknown46c == -1) {
    unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuEnd);
    return true;
  }
  switch (unknown460->getContents(unknown46c).unknown00) {
  case unknown001_1:
    unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuOpenCustomize);
    break;
  case unknown001_2: {
    const MenuBladeInfo &blade = unknown30->getContents(unknown30->getIndex(false));
    if (GfMenuObjUtil::isBladeLastOneInSlot(blade.unknown00, nullptr)) {
      unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuErrorOvdOnly);
    } else if (GfDataBlade::getCreator(blade.unknown00) == 1 && GfMenuObjUtil::isBladeLastOne(blade.unknown00, nullptr)) {
      unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuErrorOvdLastOne);
    } else {
      unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuDrChange);
    }
    break;
  }
  case unknown001_3:
    unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuConfSetRex);
    break;
  case unknown001_4:
    unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuConfRemoveRex);
    break;
  default:
    unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuEnd);
    break;
  }
  unknown2e8 = false;
  return true;
}

bool GfMenuObjBladeRelease::seqSubMenuDrChange() {
  if (!unknown2e8) {
    const MenuBladeInfo &blade = unknown30->getContents(unknown30->getIndex(false));
    MenuDriverInfo driver = {};
    u32 creator = blade.unknown04;
    unknown470->clear();
    for (u32 i = 0; i < unknown478.size(); i++) {
      if (unknown478[i] != creator) {
        driver.unknown00 = unknown478[i];
        unknown470->addContents(driver);
      }
    }
    unknown48->reset();
    GfMenuObjCommonText::openDrChange(unknown48, creator, unknown470);
    unknown2e8 = true;
    return false;
  }
  if (!unknown48->isTerm()) {
    return false;
  }
  GfMenuCallContext::GfMenuResult result;
  if (!unknown48->unknown18.empty() && unknown48->popResult(result) && result.unknown00 == 0) {
    const MenuBladeInfo &blade = unknown30->getContents(unknown30->getIndex(false));
    if (GfDataBlade::isActivateDriver(blade.unknown00)) {
      int slot = GfDataBlade::getDriverSetID(blade.unknown00);
      if (slot != -1) {
        SCOM_PARTY_ADD::removeBlade(blade.unknown04, slot, true);
      }
    }
    unknown470->setIndex(result.unknown04);
    u32 target = blade.unknown00;
    GfDataBlade::setCreator(target, unknown470->getContents(unknown470->getIndex(false)).unknown00);
    GfItemUtil::addItemBox(ITEM_UNKNOWN_25408, -1);
    unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuOwnerChange);
  } else {
    unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuOpen);
  }
  unknown2e8 = false;
  return true;
}

bool GfMenuObjBladeRelease::seqSubMenuConfSetRex() {
  if (!unknown2e8) {
    unknown48->reset();
    GfMenuObjCommonText::open(unknown48, 0xc5, 0);
    unknown2e8 = true;
    return false;
  }
  if (!unknown48->isTerm()) {
    return false;
  }
  GfMenuCallContext::GfMenuResult result;
  if (!unknown48->unknown18.empty() && unknown48->popResult(result) && result.unknown00 == 0 && result.unknown04 == 0) {
    const MenuBladeInfo &info = unknown30->getContents(unknown30->getIndex(false));
    if (GfDataBlade::isActivateDriver(info.unknown00)) {
      int slot = GfDataBlade::getDriverSetID(info.unknown00);
      if (slot != -1) {
        SCOM_PARTY_ADD::removeBlade(info.unknown04, slot, true);
      }
    }
    unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuOwnerChange);
  } else {
    unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuOpen);
  }
  unknown2e8 = false;
  return true;
}

bool GfMenuObjBladeRelease::seqSubMenuConfRemoveRex() {
  if (!unknown2e8) {
    unknown48->reset();
    GfMenuObjCommonText::open(unknown48, 0xc6, 0);
    unknown2e8 = true;
    return false;
  }
  if (!unknown48->isTerm()) {
    return false;
  }
  GfMenuCallContext::GfMenuResult result;
  if (!unknown48->unknown18.empty() && unknown48->popResult(result) && result.unknown00 == 0 && result.unknown04 == 0) {
    const MenuBladeInfo &info = unknown30->getContents(unknown30->getIndex(false));
    if (GfDataBlade::getSetDriver(info.unknown00) == 1) {
      int slot = GfDataBlade::getDriverSetID(info.unknown00);
      if (slot != -1) {
        SCOM_PARTY_ADD::removeBlade(1, slot, true);
      }
    }
    unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuOwnerChange);
  } else {
    unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuOpen);
  }
  unknown2e8 = false;
  return true;
}

bool GfMenuObjBladeRelease::seqSubMenuOwnerChange() {
  if (!unknown2e8) {
    const MenuBladeInfo &info = unknown30->getContents(unknown30->getIndex(false));
    unknown460->getContents(unknown46c);
    u32 creator = info.unknown04;
    u32 driver = unknown470->getContents(unknown470->getIndex(false)).unknown00;
    unknown48->reset();
    GfMenuObjCommonText::openOwnerChange(unknown48, creator, driver);
    unknown2e8 = true;
    return false;
  }
  if (!unknown48->isTerm()) {
    return false;
  }
  unknown30->updateOwner();
  unknown58.unknown002(&GfMenuObjBladeRelease::seqSubMenuEnd);
  unknown2e8 = false;
  return true;
}

void GfMenuObjBladeRelease::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 0;
    param.unknown00 = 6;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  case 2: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 1;
    param.unknown00 = 6;
    param.unknown0c = true;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  case GfMenuTypes::unknown003_257:
    if (GfMenuReference::getReferenceBladeID(0) != 0) {
      unknown20->unknown2f0.unknown005();
      unknown20->unknown2f0.unknown002(&GfMenuObjBladeRelease::seqOpenImage);
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBladeRelease>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjBladeRelease, 8>>(const mm::mtl::Delegate<bool()> *);
