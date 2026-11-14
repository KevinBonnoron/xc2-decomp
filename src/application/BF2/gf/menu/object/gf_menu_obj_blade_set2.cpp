#include "gf/menu/object/gf_menu_obj_blade_set2.h"

#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/object/gf_menu_obj_char_select.h"
#include "gf/menu/object/gf_menu_obj_cmn_status.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_sort.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_scom.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: layer close destination parameter; original name unknown.
struct unknown001 {
  u32 unknown00; // Inferred role: destination; original member name unknown.
};

// Inferred role: menu id; original name unknown.
constexpr u32 unknown002 = 0x1e;

// Inferred helper: requests an event with its type and first two parameters on a UI object; original name unknown.
static inline void unknown003(u32 handle, u16 type, u32 param0, u32 param1) {
  ui::EventData event;
  event.unknown10_u64 = 0;
  event.unknown0c = param1;
  event.unknown00 = type;
  event.unknown08 = param0;
  ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

GfMenuObjBladeSet2::GfMenuObjBladeSet2(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(0), unknown60(nullptr), unknown68(0),
      unknown78(false), unknown80(nullptr), unknown88(false), unknown8c(0), unknown90(0), unknown94(0), unknown98(0), unknowna0(this), unknown338(this) {}

GfMenuObjBladeSet2::~GfMenuObjBladeSet2() {
  mm::mtl::safeRelease(unknown80);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown60);
}

void GfMenuObjBladeSet2::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 173 as in the original file: it is the line argument of operator new.
#line 173
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(0x67, main);
  u32 team = acc.searchChild("LAY_dr_team");
// __LINE__ must be 178 as in the original file: it is the line argument of operator new.
#line 178
  BladeSlotListener *bladeSlotListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) BladeSlotListener(this);
  bladeSlotListener->addRef();
  ui::UIEventManager::get()->registObjectListener(team, bladeSlotListener);
  if (bladeSlotListener != nullptr) {
    bladeSlotListener->release();
  }
  u32 list = acc.searchChild("LAY_bl_list");
// __LINE__ must be 182 as in the original file: it is the line argument of operator new.
#line 182
  BladeListListener *bladeListListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) BladeListListener(this);
  bladeListListener->addRef();
  ui::UIEventManager::get()->registObjectListener(list, bladeListListener);
  if (bladeListListener != nullptr) {
    bladeListListener->release();
  }
  unknown28 = GfMenuBladeList::create();
  unknown38 = GfMenuBladeList::create();
  unknown48 = GfMenuDriverList::create();
  unknown60 = GfMenuCallContext::create();
  unknown80 = GfMenuCallContext::create();
  unknown98 = 0;
  GfMenuTypes::Param param;
  if (getFSLayerParam(unknown20, param)) {
    unknown98 = param.get<unknown001>().unknown00;
    removeFSLayerParam(unknown20);
  }
  GfMenuObjCmnStatus::openDrStatus(0, 0);
  GfMenuObjCmnStatus::openBlStatus(1, -1);
  GfMenuObjUtil::createVScrollBarPlugin(acc.searchChild("IMG_scroll_bar"), unknown38, "IMG_scroll_base", true);
  unknown9c = acc.countChild("LAY_bl_facelayout@%02d", 1);
  GfMenuObject::initialize();
}

void GfMenuObjBladeSet2::refreshBladeInfo(ui::UIObjectAcc &acc, u32 type) {
  {
    ui::UIObjectAcc list(acc.unknown10, "LAY_bl_list");
    u32 count = list.countChild("LAY_bl_info@%02d", 1);
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < count; i++) {
      name.format("LAY_elemicon@%02d", i + 1);
      list.setDispChild(type == 1, name.c_str());
      name.format("LAY_wpnicon@%02d", i + 1);
      list.setDispChild(type == 0, name.c_str());
      name.format("LAY_role_icon@%02d", i + 1);
      list.setDispChild(type == 2, name.c_str());
    }
  }
  {
    ui::UIObjectAcc team(acc.unknown10, "LAY_dr_team_info");
    u32 count = team.countChild("LAY_dr_team_info@%02d", 1);
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < count; i++) {
      name.format("LAY_telemicon@%02d", i + 1);
      team.setDispChild(type == 1, name.c_str());
      name.format("LAY_twpnicon@%02d", i + 1);
      team.setDispChild(type == 0, name.c_str());
      name.format("LAY_trole_icon@%02d", i + 1);
      team.setDispChild(type == 2, name.c_str());
    }
  }
}

void GfMenuObjBladeSet2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBladeSet2::update() {
  unknowna0.unknown003();
  unknown338.unknown003();
  GfMenuObject::update();
}

void GfMenuObjBladeSet2::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupMain(acc);
    acc.setDisp(true);
    setFadeIn(handle);
    refreshBladeInfo(acc, 0);
    break;
  case 3:
    if (event.unknown08 == 2) {
      acc.setDisp(false);
      acc.setTerm();
      switch (unknown20->unknown98) {
      case 1:
        GfMenuObjMainMenu2::closeCharChange();
        break;
      case 0:
        GfMenuObjCharSelect::returnSubMenu();
        break;
      default:
        GfMenuObject::closeFSLayer(acc.unknown10, true, true);
        return;
      }
      GfMenuObject::returnFSSubLayer(unknown20);
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    GfMenuObjCmnStatus::closeDrStatus();
    GfMenuObjCmnStatus::closeBlStatus();
    setFadeOut(handle);
    break;
  case 0x41:
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjBladeSet2::sendEvent(u32 handle, u32 type, u32 param, f32 delay) { unknown140(handle, type, param, delay); }

int GfMenuObjBladeSet2::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::unknown002(handle);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjBladeSet2::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::unknown003(handle);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjBladeSet2::setupBldeSlot(ui::UIObjectAcc &acc, const GfMenuBladeList *list) {
  mm::mtl::FixStr<32> name;
  GfMenuAdapterManager::beginAddAfter();
  for (int i = 0; i < 3; i++) {
    name.format("IMG_tface@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 3, list, i, false);
    name.format("IMG_twpnicon@%02d", i + 1);
    GfMenuCharDataAdapter *weapon = GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x29, list, i, false);
    if (weapon != nullptr) {
      name.format("IMG_twpnicon_base@%02d", i + 1);
      weapon->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("IMG_telemicon@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x2a, list, i, false);
    name.format("IMG_trole_icon@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x42, list, i, false);
  }
  for (int i = 0; i < 3; i++) {
    name.format("TXT_dr_class_name@%02d", i + 1);
    ui::UIObjectAcc className(acc.unknown10, name.c_str());
    GfMenuCharDataAdapter *driver = GfMenuCharDataAdapter::createFromReferenceDriver(className.unknown10, 0x25, 0, true);
    if (driver != nullptr) {
      driver->unknown80 = i;
      driver->unknown79 = true;
    }
    name.format("IMG_dr_class_eff_lv@%02d", i + 1);
    driver = GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild(name.c_str()), 0x27, 0, true);
    if (driver != nullptr) {
      driver->unknown80 = i;
      driver->unknown79 = true;
    }
    name.format("IMG_dr_class_empty@%02d", i + 1);
    GfMenuObjUtil::createSyncPlugin(acc.searchChild(name.c_str()), className.unknown10, 0x40);
  }
  GfMenuAdapterManager::endAddAfter();
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_drimg01"), 0x1c, 0, false);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_blimg01"), 0x36, 0, false);
  {
    ui::UIObjectAcc image(acc.searchChild("IMG_blimg01"));
    image.setStreamImage2nd();
  }
  GfMenuObject::addNumberEventCondition(acc.unknown10, "IMG_blimg01", 0, 0);
}

void GfMenuObjBladeSet2::setupBldeList(ui::UIObjectAcc &acc, const GfMenuBladeList *list, GfMenuBladeList *slotList) {
  GfMenuAdapterManager::beginAddAfter();
  mm::mtl::FixStr<32> name;
  for (int i = 0; i < 15; i++) {
    name.format("IMG_face@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 3, list, i, false);
    name.format("IMG_wpnicon@%02d", i + 1);
    GfMenuCharDataAdapter *weapon = GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x29, list, i, false);
    if (weapon != nullptr) {
      name.format("IMG_wpnicon_base@%02d", i + 1);
      weapon->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("IMG_elemicon@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x2a, list, i, false);
    name.format("IMG_role_icon@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x42, list, i, false);
    name.format("LAY_mericon@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x53, list, i, true);
    name.format("IMG_face@%02d", i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 0x4a, list, i, true)->setSlotList(slotList);
  }
  GfMenuAdapterManager::endAddAfter();
}

void GfMenuObjBladeSet2::setupDriverList(ui::UIObjectAcc &acc, const GfMenuDriverList *list) {
  mm::mtl::FixStr<32> name;
  for (int i = 0; i < 5; i++) {
    name.format("IMG_dr_sface@%02d", i + 1);
    GfMenuCharDataAdapter *face = GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 3, list, i, false);
    name.format("LAY_dr_slface@%02d", i + 1);
    if (face != nullptr) {
      face->unknown24 = acc.searchChild(name.c_str());
    }
  }
}

bool GfMenuObjBladeSet2::checkBladeSet(u32 blade, GfMenuBladeList *list) {
  u32 index = list->getIndex(false);
  if (list->getContents(list->getIndex(false)).unknown00 != 0) {
    for (u32 i = 0; i < list->getSize(); i++) {
      if (list->getContents(i).unknown00 == blade && index != i) {
        return true;
      }
    }
  }
  for (u32 i = 0; i < list->getSize(); i++) {
    if (list->getContents(i).unknown00 == blade) {
      return false;
    }
  }
  return true;
}

bool GfMenuObjBladeSet2::seqOpenImage() {
  ui::UIObjectAcc image(unknown18, "IMG_blimg01");
  bool isEnd;
  if (!image.isStreaming()) {
    {
      ui::UIObjectAcc list(unknown18, "LAY_bl_list");
      u32 blade = GfMenuReference::getReferenceBladeID(0);
      list.setLayout(image.unknown10, "blade");
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

void GfMenuObjBladeSet2::makeSetupBlade_Remove(RQ_SETUP_BLADE &info, u32 driver, u32 blade) {
  GfMenuObjUtil::getDriverPartyID(driver);
  bool hasHomura = GfMenuObjUtil::hasHomura(driver);
  DataParamAcc acc(OBJECT_TYPE_PC, driver, GIMMICK_TYPE_UNKNOWN_0);
  int set = acc.getBladeSet(false);
  if (set == 3) {
    set = GfDataBlade::getDriverSetID(BLADE_HOMURA);
  }
  if (acc.getBlade(-1, false) == blade) {
    do {
      if (set + 1 < static_cast<int>(GfMenuObjUtil::getBladeSlotMax())) {
        set = set + 1;
      } else {
        set = 0;
      }
    } while (acc.getBlade(set, false) == 0);
  }
  int slot = set;
  if (acc.getBlade(set, false) == BLADE_HOMURA) {
    if (GfDataBlade::isHikariCurrent()) {
      slot = 3;
    }
  }
  u32 removed = blade;
  if (blade == BLADE_HIKARI && hasHomura) {
    removed = BLADE_HOMURA;
  }
  for (u32 i = 0; i < 5; i++) {
    if (acc.getBlade(i, false) != removed) {
      info.unknown04[i] = acc.getBlade(i, false);
    } else {
      info.unknown04[i] = 0;
    }
  }
  info.unknown00 = driver;
  info.unknown02 = info.unknown04[slot];
}

void GfMenuObjBladeSet2::setCloseToFSClose() {
  unknown001 value;
  value.unknown00 = 2;
  GfMenuTypes::Param layerParam;
  layerParam.set(value);
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown002), layerParam);
}

void GfMenuObjBladeSet2::setCloseToReturn() {
  unknown001 value;
  value.unknown00 = 1;
  GfMenuTypes::Param layerParam;
  layerParam.set(value);
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown002), layerParam);
}

void GfMenuObjBladeSet2::setupMain(ui::UIObjectAcc &acc) {
  GfMenuObjUtil::setChildIcon(acc.unknown10, "IMG_l_button", 0x14);
  GfMenuObjUtil::setChildIcon(acc.unknown10, "IMG_r_button", 0x15);
  GfMenuObjUtil::setChildIcon(acc.unknown10, "IMG_release_button", 10);
}

void GfMenuObjBladeSet2::createDriverList(u32, GfMenuDriverList *list) {
  GfMenuDriverList::PartySetup setup;
  setup.unknown18 = false;
  setup.unknown14 = GfPartySelect::LIST_TYPE_UNKNOWN_0;
  setup.unknown00.unknown08 = 5;
  list->setupFromParty(setup);
}

bool GfMenuObjBladeSet2::checkInSlot(u32 blade, GfMenuBladeList *list) {
  for (u32 i = 0; i < list->getSize(); i++) {
    if (list->getContents(i).unknown00 == blade) {
      return true;
    }
  }
  return false;
}

void GfMenuObjBladeSet2::refreshBladeSlot(GfMenuBladeList *list) {
  u32 driver = GfMenuReference::getReferenceDriverID(0);
  GfMenuBladeList::DriverSetup setup;
  setup.unknown1c = true;
  setup.unknown1d = false;
  setup.unknown1e = false;
  setup.unknown14 = 1;
  setup.unknown18 = driver;
  setup.unknown00.unknown08 = GfMenuObjUtil::getBladeSlotMax();
  list->setupFromDriver(setup);
  while (list->getSize() < 3) {
    MenuBladeInfo info = {};
    info.unknown04 = driver;
    list->addContents(info);
  }
}

void GfMenuObjBladeSet2::createBladeList(u32 driver, GfMenuBladeList *list) {
  list->clear();
  GfMenuBladeList::DriverSetup setup;
  setup.unknown14 = 0;
  setup.unknown18 = driver;
  setup.unknown1d = true;
  setup.unknown00.unknown08 = 3;
  setup.unknown00.unknown0c = 5;
  list->setupFromDriver(setup);
  u32 sortId = GfMenuObjSort::getSortID(1, unknown90);
  if (sortId == 4 || sortId == 5) {
    list->sort(sortId, true);
  } else {
    list->sort(sortId, false);
  }
}

void GfMenuObjBladeSet2::refreshBladeList() {
  if (unknown9c != 0) {
    unknown38->updateOwner();
    ui::UIObjectAcc acc(unknown18, "LAY_bl_facelayout");
    mm::mtl::FixStr<32> name;
    int driver = GfMenuReference::getReferenceDriverID(0);
    for (u32 i = 0; i < unknown9c; i++) {
      int blade = unknown38->getContents(unknown38->getPageIndex(i)).unknown00;
      name.format("IMG_fadeselect@%02d", i + 1);
      int setDriver = GfDataBlade::getSetDriver(unknown38->getContents(unknown38->getPageIndex(i)).unknown00);
      bool isDisp = setDriver == driver;
      if (isDisp && blade == BLADE_HIKARI) {
        if (GfDataBlade::isActivateDriver(BLADE_HOMURA)) {
          isDisp = GfDataBlade::getDriverSetID(BLADE_HOMURA) != -1;
        }
      }
      acc.setDispChild(isDisp, name.c_str());
    }
  }
}

bool GfMenuObjBladeSet2::seqWaitCommand() { return !GfReqSmallCom::get()->isValid(unknown330); }

bool GfMenuObjBladeSet2::seqReturnBlSlot() {
  ui::UIObjectAcc acc(unknown18, "LAY_dr_team");
  unknown003(acc.unknown10, 0x101, 1, 0);
  refreshBladeList();
  return true;
}

} // namespace gf

template bool gf::GfMenuSequence<gf::GfMenuObjBladeSet2, 8>::wait();
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjBladeSet2, 8>>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBladeSet2>(const mm::mtl::Delegate<bool()> *);
