#include "gf/menu/object/gf_menu_obj_save_load2.h"

#include "gf/data/gf_data_save.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_reference_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/object/gf_menu_obj_fade.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/plugin/ui_object_number_plugin.h"
#include "ui/plugin/ui_object_text_plugin.h"
#include "ui/plugin/ui_object_time_plugin.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: menu id; original name unknown.
constexpr u32 unknown001 = 0x35;
// Inferred role: call id of the save/load layout; original name unknown.
constexpr u32 CALL_UNKNOWN_117 = 0x75;

GfMenuObjSaveLoad2::GfMenuObjSaveLoad2(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(this), unknown2c0(-1), unknown2c4(0), unknown2c8(nullptr), unknown2d0(nullptr), unknown2d8(nullptr), unknown2e0(nullptr), unknown2e8(nullptr),
      unknown2f0(nullptr), unknown2f8(nullptr), unknown300(nullptr) {
  for (int i = 0; i < 3; i++) {
    unknown308[i] = nullptr;
  }
}

void GfMenuObjSaveLoad2::initialize() {
  {
    GfMenuTypes::Param layerParam;
    if (getFSLayerParam(unknown20, layerParam)) {
      unknown2c4 = layerParam.get<OpenParam>().unknown00;
      removeFSLayerParam(unknown20);
    }
  }
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 157 as in the original file: it is the line argument of operator new.
#line 157
  MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, listener);
  if (listener != nullptr) {
    listener->release();
  }
  attachExternalCall(CALL_UNKNOWN_117, main);
  unknown28 = GfMenuCallContext::create();
  // The braces end the CreateParam lifetime: the game (0x71004c86f4) reuses its stack slot for the layer param, the team setup and this one.
  {
    ui::UISelectObjList::CreateParam param;
    param.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
    unknown2c8 = ui::UISelectObjList::create(param);
  }
  unknown2f8 = GfMenuDriverList::create();
  GfMenuDriverList::PartySetup partySetup;
  // PartySetup has no constructor past its SetupParam: the game stores the list type and the option one by one (str wzr 0x71004c884c, strb wzr 0x71004c8850).
  partySetup.unknown14 = GfPartySelect::LIST_TYPE_UNKNOWN_0;
  partySetup.unknown18 = false;
  unknown2f8->setupFromParty(partySetup);
  unknown300 = GfMenuBladeList::create();
  GfMenuBladeList::TeamSetup teamSetup;
  // The game stores the list source and then the flag (stp w27, wzr for the source and the constructor's zero team, then strb w27) in address order. The flag repeats the
  // constructor's value: with the source alone the byte store comes before the pair and the function does not match.
  teamSetup.unknown14 = 1;
  teamSetup.unknown1c = true;
  unknown300->setupFromTeam(teamSetup);
  for (int i = 0; i < 3; i++) {
    unknown308[i] = unknown160();
    unknown308[i]->unknown162(1);
  }
  acc.setDispChild(GfMenuManager::isClearCheck(), "IMG_clear_mark");
  GfMenuObject::initialize();
}

GfMenuObjSaveLoad2::~GfMenuObjSaveLoad2() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown2c8);
  mm::mtl::safeRelease(unknown2d0);
  mm::mtl::safeRelease(unknown2d8);
  mm::mtl::safeRelease(unknown2e0);
  mm::mtl::safeRelease(unknown2e8);
  mm::mtl::safeRelease(unknown2f0);
  mm::mtl::safeRelease(unknown2f8);
  mm::mtl::safeRelease(unknown300);
  for (int i = 0; i < 3; i++) {
    unknown308[i] = nullptr;
  }
}

void GfMenuObjSaveLoad2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjSaveLoad2::update() {
  unknown30.unknown003();
  GfMenuObject::update();
}

void GfMenuObjSaveLoad2::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown001), layerParam);
}

void GfMenuObjSaveLoad2::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

void GfMenuObjSaveLoad2::setupSave(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> *numbers) {
  mm::mtl::FixStr<32> name;
  int blade = 0;
  for (int i = 0; i < 3; i++) {
    name.format("IMG_driver@%02d", i + 1);
    GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 3, unknown2f8, i, false);
    name.format("TXT_char_name@%02d", i + 1);
    GfMenuCharDataAdapter::createFromDriverList(acc.searchChild(name.c_str()), 2, unknown2f8, i, false);
    name.format("TXT_lv_num@%02d", i + 1);
    GfMenuReferenceAdapter::create(acc.searchChild(name.c_str()), numbers[i], false);
    name.format("IMG_blade%d@%02d", 1, i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 3, unknown300, blade, false);
    name.format("IMG_blade%d@%02d", 2, i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 3, unknown300, blade + 1, false);
    name.format("IMG_blade%d@%02d", 3, i + 1);
    GfMenuCharDataAdapter::createFromBladeList(acc.searchChild(name.c_str()), 3, unknown300, blade + 2, false);
    blade += 3;
  }
  unknown2d0 = ui::UIObjectTimePlugin::create(acc.searchChild("TXT_year_num"), 1);
  unknown2d8 = ui::UIObjectTimePlugin::create(acc.searchChild("TXT_time_num"), 6);
  unknown2e0 = ui::UIObjectNumberPlugin::create(acc.searchChild("TXT_progress"));
  unknown2e8 = ui::UIObjectTimePlugin::create(acc.searchChild("TXT_game_time"), 7);
  unknown2f0 = ui::UIObjectTextPlugin::create(acc.searchChild("TXT_area"));
}

bool GfMenuObjSaveLoad2::seqSave() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  disableInput(main.unknown10);
  GfMenuObjMainMenu2::setCloseKeyEnable(false);
  unknown2c0 = GfReqCommand::reqSave(SAVESLOT_UNKNOWN_22);
  GfMenuObjFade::dispSaving(true, 0);
  return true;
}

bool GfMenuObjSaveLoad2::seqSaveWait() {
  if (GfReqManager::isValid(unknown2c0)) {
    return false;
  }
  GfMenuObjUtil::playSE(8);
  GfMenuObjFade::dispSaving(false, 0);
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc main(acc.searchChild("LAY_main"));
  refreshSave(main, 1);
  GfMenuObjMainMenu2::setCloseKeyEnable(true);
  ui::UIObjectAcc input(unknown18, "LAY_main");
  enableInput(input.unknown10);
  unknown2c0 = -1;
  return true;
}

bool GfMenuObjSaveLoad2::seqSaveWaitToClose() {
  if (GfReqManager::isValid(unknown2c0)) {
    return false;
  }
  GfMenuObjUtil::playSE(8);
  GfMenuObjFade::dispSaving(false, 0);
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc main(acc.searchChild("LAY_main"));
  refreshSave(main, 1);
  GfMenuObjMainMenu2::setCloseKeyEnable(true);
  unknown140(main.unknown10, GfMenuTypes::unknown003_34, 0, 0.0f);
  unknown2c0 = -1;
  return true;
}

int GfMenuObjSaveLoad2::setFadeIn(u32 handle, u32 type) {
  int ctrl = -1;
  switch (type) {
  case 0:
    ctrl = GfMenuObjUtil::unknown002(handle);
    break;
  case 1: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_l_early");
    param.unknown04 = 1;
    param.unknown11 = true;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_r_early");
    param.unknown04 = 1;
    param.unknown11 = true;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  }
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjSaveLoad2::setFadeOut(u32 handle, u32 type) {
  int ctrl = -1;
  switch (type) {
  case 0:
    ctrl = GfMenuObjUtil::unknown003(handle);
    break;
  case 1: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_l_early");
    param.unknown14 = 10;
    param.unknown04 = 2;
    param.unknown11 = true;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_r_early");
    param.unknown14 = 10;
    param.unknown04 = 2;
    param.unknown11 = true;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  }
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjSaveLoad2>(const mm::mtl::Delegate<bool()> *);
