#include "gf/menu/object/gf_menu_obj_blade_create.h"

#include <string.h>

#include "bdat.h"
#include "fw/fw_pad.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_save.h"
#include "gf/data/gf_item_id.h"
#include "gf/game/sequential_play/gf_play_command.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_model_view.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_sound_manager.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_blade_name.h"
#include "gf/menu/object/gf_menu_obj_blade_set2.h"
#include "gf/menu/object/gf_menu_obj_cmn_status.h"
#include "gf/menu/object/gf_menu_obj_fade.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_manager.h"
#include "gf/request/gf_req_scom.h"
#include "gf/sound/gf_sound.h"
#include "gf/util/gf_item_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "scn/scn_render_dr_sys_parm_acc.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {
struct GF_OBJ_HANDLE;

// Inferred role: full screen layer id; original name unknown.
constexpr u32 unknown001 = 0x14;

// Inferred role: names of the pages of the creation screen; original name unknown.
const char *const unknown002[6] = {"LAY_dr_select", "LAY_core_select", "LAY_bst_select", "LAY_confirm", "LAY_create", "LAY_result"};

// Inferred role: object type of the drivers in the model view; original name unknown.
constexpr u32 unknown003 = 3;

// Inferred role: object type of the crystals in the model view; original name unknown.
constexpr u32 unknown009 = 0xf;

// Inferred role: driver of each camera of the driver select page; original name unknown.
const u32 unknown004[16] = {1, 2, 6, 3, 0x15, 0x13, 0x15, 0x15, 0xb9, 0xba, 0xbb, 0xbc, 0x154, 0x151, 0xffffffff, 0x150};

// Inferred role: camera offset of each page of the creation screen; original name unknown.
const int unknown008[6] = {0, 1, 2, 3, 4, 4};

// Inferred role: camera motion of each driver of the creation screen, null for the drivers without one; original name unknown.
const char *const unknown012[6] = {"mnu_blade_create_rex_01", "mnu_blade_create_nia_01", "mnu_blade_create_sieg_01", nullptr, nullptr, "mnu_blade_create_melef_01"};

// Inferred role: sets the weapon type of a driver in the model view; original name unknown.
static void unknown006(GfMenuModelView *view, u32 driver, int weaponType) { view->setObjectCommandValue(view->findGfObj(unknown003, driver), "V_weaponselect", weaponType); }

// Inferred role: starts the blade arts animation of a driver in the model view; original name unknown.
static void unknown007(GfMenuModelView *view, u32 driver) { view->sendObjectCommand(view->findGfObj(unknown003, driver), "C_bladearts_01"); }

// Inferred role: gets a crystal object of the model view; original name unknown.
static GF_OBJ_HANDLE *unknown011(GfMenuModelView *view, u32 index) { return view->findGfObj(unknown009, view->getMapObjID(index)); }

// Inferred role: attaches a crystal object of the model view to the right hand of a driver; original name unknown.
static void unknown010(GfMenuModelView *view, u32 driver, u32 index) {
  GF_OBJ_HANDLE *driverObj = view->findGfObj(unknown003, driver);
  view->attachObject(unknown011(view, index), driverObj, "EX_wp_R");
}

// Inferred role: checks that a crystal object of the model view exists; original name unknown.
static bool unknown013(GfMenuModelView *view, u32 index) { return view->checkGfObj(unknown009, view->getMapObjID(index)); }

// Inferred role: starts the opening control of a page of the creation screen; original name unknown.
static void unknown014(u32 handle) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 1;
  param.unknown00 = 0.5f;
  param.unknown04 = 1;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

// Inferred role: starts the closing control of a page of the creation screen; original name unknown.
static void unknown015(u32 handle) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 2;
  param.unknown14 = 2;
  param.unknown00 = 0.25f;
  param.unknown04 = 2;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

void GfMenuObjBladeCreate::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(unknown001, layerParam);
}

void GfMenuObjBladeCreate::openCreatedBladeName(GfMenuCallContext *context) { GfMenuObjBladeName::open(context); }

u32 GfMenuObjBladeCreate::getPageObject(u32 handle, u32 page, bool isSibling) {
  u32 object = 0;
  if (handle != 0 && page < 6) {
    ui::UIObjectAcc acc(handle);
    if (isSibling) {
      object = acc.searchSibiling(unknown002[page]);
    } else {
      object = acc.searchChild(unknown002[page]);
    }
  }
  return object;
}

void GfMenuObjBladeCreate::changePage(u32 handle, PageContext *context, u32 page, bool isSibling, bool isReturn) {
  ui::UIObjectAcc oldPage(getPageObject(handle, context->unknown00, isSibling));
  ui::UIObjectAcc newPage(getPageObject(handle, page, isSibling));
  ui::EventData event;
  if (newPage.isValid()) {
    event.unknown00 = 0x22;
    ui::UIManager::get()->requestObjectEvent(oldPage.unknown10, event, 0.0f);
    if (newPage.isValid()) {
      event.unknown00 = 0x21;
      ui::UIManager::get()->requestObjectEvent(newPage.unknown10, event, 0.0f);
    }
    context->unknown04 = context->unknown00;
    context->unknown00 = page;
    disableFSInput();
    if (isReturn) {
      context->unknownac8->popCamera(0.5f);
    }
    if (page == 0) {
      context->unknownac8->resetCamera(unknown1198, 0.0f);
    } else {
      context->unknownac8->pushCamera(unknown008[page] + unknown11a0, 0.5f);
    }
  }
}

u32 GfMenuObjBladeCreate::getDriverCameraIndex(u32 driver) {
  u32 index = 0;
  while (unknown004[index] != driver) {
    index++;
  }
  return index;
}

void GfMenuObjBladeCreate::nextPage(u32 handle, PageContext *context, bool isSibling) {
  u32 page = 0;
  switch (context->unknown00) {
  case 0:
    page = 1;
    break;
  case 1:
    page = 2;
    if (context->unknown2c) {
      page = 3;
    }
    break;
  case 2:
    page = 3;
    break;
  case 3:
    page = 4;
    break;
  case 4:
    page = 5;
    break;
  case 5:
    break;
  default:
    if (context->unknown00 != 0xff) {
      return;
    }
    break;
  }
  changePage(handle, context, page, isSibling, false);
}

void GfMenuObjBladeCreate::returnPage(u32 handle, PageContext *context, bool isSibling) {
  u32 page = 0;
  switch (context->unknown00) {
  case 1:
    break;
  case 2:
    page = 1;
    break;
  case 3:
    page = 1;
    if (!context->unknown2c) {
      page = 2;
    }
    break;
  case 4:
    page = 3;
    break;
  default:
    return;
  }
  changePage(handle, context, page, true, true);
}

void GfMenuObjBladeCreate::finalize() {
  if (unknown28.unknownac8 != nullptr) {
    delete unknown28.unknownac8;
    unknown28.unknownac8 = nullptr;
  }
  mm::mtl::safeRelease(unknown28.unknown40);
  mm::mtl::safeRelease(unknown28.unknown50);
  mm::mtl::safeRelease(unknown28.unknown48);
  mm::mtl::safeRelease(unknown28.unknown30);
  mm::mtl::safeRelease(unknown28.unknown38);
  GfMenuObject::finalize();
}

void GfMenuObjBladeCreate::update() {
  unknownaf8.unknown003();
  if (unknown28.unknownac8 != nullptr) {
    unknown28.unknownac8->update();
  }
  GfMenuObject::update();
}

bool GfMenuObjBladeCreate::seqSetupCrystal() {
  u32 driver = unknown28.unknown40->getContents(unknown28.unknown40->getIndex(false));
  unknown010(unknown28.unknownac8, driver, 1);
  unknown010(unknown28.unknownac8, driver, 2);
  mm::Vec3 scale;
  scale.z = 0.7f;
  scale.y = 0.7f;
  scale.x = 0.7f;
  GfMenuModelView::setObjectScale(unknown011(unknown28.unknownac8, 1), scale);
  GfMenuModelView::setObjectScale(unknown011(unknown28.unknownac8, 2), scale);
  GfMenuModelView::setObjectDisp(unknown011(unknown28.unknownac8, 2), false);
  unknown11c4[1] = GfMenuObjUtil::playSE("se_fld_allmap_706");
  refreshCrystalList();
  return true;
}

void GfMenuObjBladeCreate::refreshCrystalList() {
  if (unknown1150 != nullptr) {
    GfMenuItemList *crystals = unknown28.unknown48;
    if (crystals != nullptr) {
      for (u32 i = 0; i < unknown1150->getSize(); i++) {
        u32 item = crystals->getContents(crystals->getPageIndex(i)).unknown04;
        if (item != 0) {
          mm::mtl::FixStr<32> name;
          name.format("TXT_core_sel_item_name@%02d", i + 1);
          ui::UIObjectAcc acc(unknown18, name.c_str());
          if (!isValidCrystal(item)) {
            GfMenuObjUtil::setColMulandAdd(acc.unknown10, "txt_disable");
            acc.setBorderWeight(1.0f);
            name.format("TXT_core_sel_item_num@%02d", i + 1);
            ui::UIObjectAcc(unknown18, name.c_str()).setBorderWeight(1.0f);
            name.format("TXT_core_sel_item_max@%02d", i + 1);
            ui::UIObjectAcc(unknown18, name.c_str()).setBorderWeight(1.0f);
            name.format("TXT_core_sel_item_slash@%02d", i + 1);
            ui::UIObjectAcc(unknown18, name.c_str()).setBorderWeight(1.0f);
          } else {
            GfMenuObjUtil::setColDefault(acc.unknown10);
            acc.setBorderWeight(-0.5f);
            name.format("TXT_core_sel_item_num@%02d", i + 1);
            ui::UIObjectAcc(unknown18, name.c_str()).setBorderWeight(-0.5f);
            name.format("TXT_core_sel_item_max@%02d", i + 1);
            ui::UIObjectAcc(unknown18, name.c_str()).setBorderWeight(-0.5f);
            name.format("TXT_core_sel_item_slash@%02d", i + 1);
            ui::UIObjectAcc(unknown18, name.c_str()).setBorderWeight(-0.5f);
          }
        }
      }
      if (unknown013(unknown28.unknownac8, 1) && unknown013(unknown28.unknownac8, 2)) {
        if (!isValidCrystal(crystals->getContents(crystals->getIndex(false)).unknown04)) {
          {
            GfMenuModelView::CtrlParam param(unknown011(unknown28.unknownac8, 1), 0.1f, false);
            param.setMoveAlpha(0.0f);
            unknown28.unknownac8->startObjectCtrl(param);
          }
          {
            GfMenuModelView::CtrlParam param(unknown011(unknown28.unknownac8, 2), 0.1f, false);
            param.setMoveAlpha(1.0f);
            unknown28.unknownac8->startObjectCtrl(param);
          }
        } else {
          {
            GfMenuModelView::CtrlParam param(unknown011(unknown28.unknownac8, 1), 0.1f, false);
            param.setMoveAlpha(1.0f);
            unknown28.unknownac8->startObjectCtrl(param);
          }
          {
            GfMenuModelView::CtrlParam param(unknown011(unknown28.unknownac8, 2), 0.1f, false);
            param.setMoveAlpha(0.0f);
            unknown28.unknownac8->startObjectCtrl(param);
          }
        }
      }
    }
  }
}

void GfMenuObjBladeCreate::stopAllSound() {
  for (int i = 0; i < 3; i++) {
    if (unknown11c4[i] != 0) {
      GfMenuObjUtil::stopSE(unknown11c4[i], 0.0f);
    }
  }
}

bool GfMenuObjBladeCreate::seqStart() {
  ml::ScnRenderDrSysParmAcc acc;
  if (!acc.isSeamMapRead()) {
    unknown1120 = false;
    GfMenuSoundManager::fadeOutFieldBgm(0.5f);
    return true;
  }
  return false;
}

bool GfMenuObjBladeCreate::seqWaitLoading() { return !unknown28.unknownac8->isLoading(); }

bool GfMenuObjBladeCreate::seqEnd() {
  enableFSInput(unknown28.unknown00);
  return true;
}

bool GfMenuObjBladeCreate::seqSave() {
  unknown11b0 = GfReqCommand::reqSave(SAVESLOT_UNKNOWN_22);
  GfMenuObjFade::dispSaving(true, 0);
  return true;
}

bool GfMenuObjBladeCreate::seqSaveWait() {
  if (!GfReqManager::isValid(unknown11b0)) {
    GfMenuObjFade::dispSaving(false, 0);
    unknown11b0 = -1;
    return true;
  }
  return false;
}

bool GfMenuObjBladeCreate::seqResultStart() {
  unknown1120 = false;
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqResultConfirm);
  return true;
}

bool GfMenuObjBladeCreate::seqCreateStartSE() {
  if (unknown11c4[1] != 0) {
    GfMenuObjUtil::stopSE(unknown11c4[1], 0.0f);
    unknown11c4[1] = 0;
  }
  unknown11c4[2] = GfMenuObjUtil::playSE("se_fld_allmap_715");
  return true;
}

bool GfMenuObjBladeCreate::seqCreatePlayJingle() {
  GfMenuObjUtil::stopBGM(unknown11c0, 1.0f);
  unknown11c0 = 0;
  return true;
}

bool GfMenuObjBladeCreate::seqSetupDriverObj() {
  {
    ui::UIObjectAcc main(unknown18, "LAY_main");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    GfMenuObjUtil::startCtrl(main.unknown10, param, nullptr);
  }
  changePage(unknown18, &unknown28, 0, false, false);
  unknown28.unknownac8->playEffect(8, "bc_30_000", mm::Vec3(0.0f, 0.0f, 0.0f), reinterpret_cast<GF_OBJ_HANDLE *>(-1));
  unknown11c4[0] = GfMenuObjUtil::playSE("se_fld_allmap_701");
  return true;
}

bool GfMenuObjBladeCreate::seqResultBladeFull() {
  if (!unknown1120) {
    GfMenuManager::openCommonWindow(8);
    unknown1120 = true;
  }
  if (!GfMenuManager::isOpenCommonWindow()) {
    unknownaf8.unknown002(&GfMenuObjBladeCreate::seqResultEnd);
    if (unknown28.unknown38 != nullptr) {
      unknown28.unknown38->release();
      unknown28.unknown38 = nullptr;
    }
    return true;
  }
  return false;
}
bool GfMenuObjBladeCreate::seqResultConfirm() {
  if (!unknown1120) {
    if (unknown11b4 && unknown11bc) {
      u32 driver = unknown28.unknown40->getContents(unknown28.unknown40->getIndex(false));
      SCOM_PARTY_ADD::addBlade(unknown28.unknown28, driver, 1);
      if (!unknown11b4) {
        GfMenuObjMainMenu2::setCloseKeyEnable(true);
      }
      GfMenuObjOperationInfo::close();
      GfMenuObject::returnFSSubLayer(this);
      return true;
    }
    GfMenuManager::openCommonWindow(7);
    unknown1120 = true;
  }
  if (GfMenuManager::isOpenCommonWindow()) {
    return false;
  }
  s16 result = GfMenuManager::getCommonWindowResult();
  if (result != 0) {
    if (!unknown11b4) {
      unknownaf8.unknown002(&GfMenuObjBladeCreate::seqResultEnd);
    } else {
      GfMenuObjMainMenu2::setCloseKeyEnable(true);
      GfMenuObjOperationInfo::close();
      GfMenuObject::returnFSSubLayer(this);
    }
    unknown1120 = false;
    return true;
  }
  if (!unknown11b4 || unknown11b8 == 0) {
    GfMenuObjBladeSet2::setCloseToReturn();
  } else {
    GfMenuObjBladeSet2::setCloseToFSClose();
  }
  if (unknown11b4) {
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
  }
  GfMenuObject::changeFSSubLayer(unknown18, GfMenuFullScreen::getLayerGroup(unknown20), GfMenuObject::getMenuLayerID(0x1e), true);
  return true;
}

bool GfMenuObjBladeCreate::seqCreateCtrlBlade() {
  u32 blade = unknown1128.front();
  switch (unknown1144) {
  case 0: {
    unknown28.unknownac8->setObjectVanishRatio(unknown28.unknownac8->findGfObj(4, blade), 1.0f);
    unknown28.unknownac8->setObjectVanishParam(unknown28.unknownac8->findGfObj(4, blade), 9);
    GfMenuModelView::CtrlParam param(unknown28.unknownac8->findGfObj(4, blade), 0.3f, false);
    param.setAddPosY(0.2f);
    if (unknown1128.size() == 1) {
      param.setMoveVanish(0.5f);
    } else {
      param.setMoveVanish(0.7f);
    }
    unknown28.unknownac8->startObjectCtrl(param);
    GF_OBJ_HANDLE *driver = unknown28.unknownac8->findGfObj(unknown003, unknown28.unknown40->getContents(unknown28.unknown40->getIndex(false)));
    if (unknown1148 == 0) {
      unknown28.unknownac8->playEffectFromCAS(1, "bc_20_010", driver);
      unknown1148++;
    } else if (unknown1128.size() > 1) {
      unknown28.unknownac8->playEffectFromCAS(unknown1148 + 1, "bc_20_010", driver);
      unknown1148++;
    } else {
      GF_OBJ_HANDLE *bladeObj = unknown28.unknownac8->findGfObj(4, blade);
      unknown28.unknownac8->playEffectFromCAS(5, "bc_20_020", driver);
      unknown28.unknownac8->playEffectFromCAS(7, "bc_20_040", bladeObj);
    }
    GfMenuObjUtil::playVibration(fw::VIBRATION_ID_UNKNOWN_16, 1.0f);
    GfMenuObjUtil::playSE("se_fld_allmap_712");
    unknown114c = 15;
    break;
  }
  case 1: {
    GfMenuModelView::CtrlParam param(unknown28.unknownac8->findGfObj(4, blade), 0.4f, false);
    param.setAddPosY(0.2f);
    unknown28.unknownac8->startObjectCtrl(param);
    break;
  }
  case 2: {
    GfMenuModelView::CtrlParam param(unknown28.unknownac8->findGfObj(4, blade), 0.3f, false);
    if (unknown1128.size() == 1) {
      param.setAddPosY(-0.5f);
      param.setMoveSclX(0.001f);
      param.setMoveSclZ(0.001f);
    } else {
      param.setAddPosY(0.2f);
      param.setMoveVanish(1.0f);
      GfMenuObjUtil::playSE("se_fld_allmap_713");
    }
    unknown28.unknownac8->startObjectCtrl(param);
    break;
  }
  }
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateWaitBlade);
  return true;
}

bool GfMenuObjBladeCreate::seqCreateWaitBlade() {
  u32 blade = unknown1128.front();
  GfMenuModelView *view = unknown28.unknownac8;
  if (view->isObjectCtrlBusy(view->findGfObj(4, blade))) {
    return false;
  }
  if (unknown1144 < 2) {
    unknown1144++;
    unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateCtrlBlade);
  } else {
    unknown28.unknownac8->delGfObj(4, blade);
    unknown1128.erase(unknown1128.begin());
    if (!unknown1128.empty()) {
      unknown1144 = 0;
      unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateBuildBlade);
    } else {
      GfMenuFade::setFade(2, 60, mm::Col4::white);
      GfMenuObjUtil::playSE("se_fld_allmap_714");
      unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateWaitFade);
      unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreatePlayJingle);
      unknownaf8.unknown004(30);
      unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreatePlayBgmAfter);
      unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateStartEvent);
      unknown1128.clear();
    }
  }
  return true;
}

bool GfMenuObjBladeCreate::seqCreateStart() {
  GF_OBJ_HANDLE *driverObj = unknown28.unknownac8->findGfObj(unknown003, unknown28.unknown40->getContents(unknown28.unknown40->getIndex(false)));
  GfMenuModelView *view = unknown28.unknownac8;
  {
    mm::Vec3 position(0.0f, 0.0f, 0.0f);
    view->playEffect(6, "bc_20_030", position, unknown011(view, 1));
  }
  unknown28.unknownac8->playEffectFromCAS(0, "bc_20_000", driverObj);
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateSetup);
  int driver = unknown28.unknown40->getContents(unknown28.unknown40->getIndex(false));
  for (u32 i = 0; i < unknown28.unknown40->getSize(); i++) {
    if (driver != unknown28.unknown40->getContents(i)) {
      GfObjAcc acc(unknown28.unknownac8->findGfObj(unknown003, unknown28.unknown40->getContents(i)));
      acc.setDisp(OBJDISP_UNKNOWN_0, false);
    }
  }
  const char *motion = nullptr;
  if (driver >= 1 && driver <= 6) {
    motion = unknown012[driver - 1];
  }
  if (motion != nullptr) {
    fw::Transform &transform = GfMenuModelView::getObjectTransform(unknown28.unknownac8->findGfObj(unknown003, driver));
    mm::Vec3 rotation = mm::quatToEuler(transform.unknown10);
    unknown28.unknownac8->playCameraMotion(motion, transform.unknown00, rotation.y);
  }
  return true;
}

bool GfMenuObjBladeCreate::seqCreateStartEvent() {
  for (u32 i = 0; i < unknown28.unknown40->getSize(); i++) {
    u32 id = unknown28.unknown40->getContents(i);
    GfObjAcc(unknown28.unknownac8->findGfObj(unknown003, id)).setDisp(OBJDISP_UNKNOWN_0, false);
  }
  u32 event = GfDataBlade::getCreateEvent(unknown28.unknown28);
#line 2938
  unknown1118 = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfSequentialPlaySignal();
  GfPlayFactory::createBlEvent(event, 1, unknown28.unknown28, unknown1118);
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateWaitEvent);
  unknown28.unknownac8->delGfObj(unknown009, unknown28.unknownac8->getMapObjID(1));
  unknown28.unknownac8->delGfObj(unknown009, unknown28.unknownac8->getMapObjID(2));
  unknown28.unknownac8->stopEffect(6);
  unknown28.unknownac8->stopEffect(7);
  unknown28.unknownac8->stopEffect(0);
  unknown28.unknownac8->stopEffect(unknown1148 + 1);
  if (unknown11c4[2] != 0) {
    GfMenuObjUtil::stopSE(unknown11c4[2], 0.0f);
    unknown11c4[2] = 0;
  }
  return true;
}

bool GfMenuObjBladeCreate::seqCreateWaitEvent() {
  if (unknown1118->isActive) {
    return false;
  }
  if (unknown1118 != nullptr) {
    delete unknown1118;
    unknown1118 = nullptr;
  }
  GfMenuObjBladeName::close();
  nextPage(unknown18, &unknown28, false);
  return true;
}

void GfMenuObjBladeCreate::setGuideText(u32 id) {
  ui::UIObjectAcc acc(unknown18, "TXT_guide");
  {
    u32 name = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_MSG_OPERATION_GUIDE), "name", id).valueU16;
    ui::UIStr text(GfDataBdat::getFP(BDAT_MENU_OPERATION_GUIDE), name);
    acc.setText(text);
  }
  acc.setDisp(true);
  GfMenuObjUtil::CtrlParam param;
  param.unknown004("fade_in_l");
  param.unknown14 = 8;
  param.unknown11 = true;
  param.unknown00 = 0.2f;
  GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
}

bool GfMenuObjBladeCreate::seqCreatePlayBgmAfter() { return true; }

bool GfMenuObjBladeCreate::isValidCrystal(u32 item) {
  int driver = unknown28.unknown40->getContents(unknown28.unknown40->getIndex(false));
  return GfItemUtil::isValidCrystal(item) && (item != ITEM_UNKNOWN_45005 || driver == 6);
}

u32 GfMenuObjBladeCreate::getInvalidCrystalMsgID(u32 item) {
  int driver = unknown28.unknown40->getContents(unknown28.unknown40->getIndex(false));
  u32 message;
  if (item == ITEM_UNKNOWN_45005 && driver != 6) {
    message = 0xd4;
  } else {
    message = 0;
    if (!GfItemUtil::isValidCrystal(item)) {
      message = 0xa9;
    }
  }
  return message;
}

void GfMenuObjBladeCreate::dispGuideText(bool isDisp) {
  ui::UIObjectAcc acc(unknown18, "LAY_guide");
  acc.setDisp(isDisp);
}

bool GfMenuObjBladeCreate::seqCreateSetup() {
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateStartDriver);
  unknownaf8.unknown004(120);
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateStartSE);
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateWaitDriver);
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateWaitFade);
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqCreateBuildBlade);
  unknown1148 = 0;
  return true;
}

bool GfMenuObjBladeCreate::seqCreateStartDriver() {
  GfMenuModelView *view = unknown28.unknownac8;
  GF_OBJ_HANDLE *driver = view->findGfObj(unknown003, unknown28.unknown40->getContents(unknown28.unknown40->getIndex(false)));
  view->sendObjectCommand(driver, "C_hold_00");
  GfMenuObjUtil::playSE("se_fld_allmap_711");
  return true;
}

bool GfMenuObjBladeCreate::seqCreateWaitDriver() {
  u32 id = unknown28.unknown40->getContents(unknown28.unknown40->getIndex(false));
  GfMenuModelView *view = unknown28.unknownac8;
  GF_OBJ_HANDLE *driver = view->findGfObj(unknown003, id);
  if (strcmp(view->getObjectAnimationState(driver), "S_hold_01") == 0) {
    GfMenuFade::setFade(2, 30, mm::Col4(0.0f, 0.0f, 0.0f, 0.0f));
    return true;
  }
  return false;
}

bool GfMenuObjBladeCreate::seqCreateWaitFade() { return !GfMenuManager::isFading(); }

void GfMenuObjBladeCreate::updateIdea(bool isSave) {
  int levels[4] = {};
  GfMenuReference::resetDriverAddIdeaLv();
  if (unknown28.unknown00 > 1 && unknown1188->unknown0c > 0) {
    int idea = unknown28.unknown50->getContents(unknown28.unknown50->getIndex(false)).unknown04;
    int index = idea - Bdat::getIdTop(GfDataBdat::getFP(BDAT_ITM_BOOSTER_LIST));
    int level = unknown1188->unknown0c;
    levels[index] = level;
    if (isSave) {
      int slot = unknown28.unknown50->getIndex(false);
      unknown1174[slot] = level;
    }
  }
  for (u32 i = 0; i < 4; i++) {
    GfMenuReference::setDriverAddIdeaLv(i, levels[i]);
  }
}

bool GfMenuObjBladeCreate::seqResultAppearBlade() {
  u32 driver = unknown28.unknown40->getContents(unknown28.unknown40->getIndex(false));
  u32 blade = unknown28.unknown28;
  GfMenuModelView::getObjectTransform(unknown28.unknownac8->findGfObj(4, blade)).unknown00.z = -1.0f;
  GfMenuModelView::CtrlParam param(unknown28.unknownac8->findGfObj(4, blade), 0.5f, false);
  param.setMovePosX(-1.0f, 1.0f);
  unknown28.unknownac8->startObjectCtrl(param);
  unknown006(unknown28.unknownac8, driver, GfDataBlade::getBladeWpnType(blade));
  unknown007(unknown28.unknownac8, driver);
  return true;
}

bool GfMenuObjBladeCreate::seqResultEnd() {
  u32 blade = unknown28.unknown28;
  unknown28.unknownac8->delGfObj(4, blade);
  unknown28.unknownac8->stopCameraMotion();
  nextPage(unknown18, &unknown28, false);
  for (u32 i = 0; i < unknown28.unknown40->getSize(); i++) {
    u32 id = unknown28.unknown40->getContents(i);
    GfObjAcc(unknown28.unknownac8->findGfObj(unknown003, id)).setDisp(OBJDISP_UNKNOWN_0, true);
  }
  return true;
}

void GfMenuObjBladeCreate::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObjOperationInfo::setGuideDisp(false);
    acc.setDisp(false);
    break;
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown14 = 1;
    param.unknown00 = 0.5f;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    GfMenuObjOperationInfo::setGuideDisp(true);
    GfMenuObjMainMenu2::dispCloseButton();
    if (GfSound::get() != nullptr) {
      GfMenuSoundManager::fadeFieldBgm(1.0f, 0.5f);
      GfMenuObjUtil::stopBGM(unknown20->unknown11c0, 1.0f);
      unknown20->unknown11c0 = 0;
      unknown20->stopAllSound();
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjBladeCreate::ResultListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(5);
      GfMenuObjOperationInfo::open(acc.unknown10, 0, 0, 0);
      GfMenuObjOperationInfo::setGuideDisp(false);
      unknown20->unknown11c0 = GfMenuObjUtil::playBGM(0x14, false, CATEGORY_MENU_BGM);
    }
    break;
  case 8:
    if (event.unknown0c == 1) {
      unknown20->unknownaf8.unknown002(&GfMenuObjBladeCreate::seqResultStart);
      GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
      GfMenuObject::disableFSInput();
    }
    break;
  case GfMenuTypes::unknown003_33:
    unknown014(acc.unknown10);
    GfMenuObjCmnStatus::openBlStatus(2, -1);
    {
      ui::UIObjectAcc image(acc.unknown10, "IMG_result_bl_img");
      u32 blade = GfMenuReference::getReferenceBladeID(0);
      acc.setLayout(image.unknown10, "blade");
      GfMenuObjUtil::ImageParam imageParam;
      if (GfMenuObjUtil::getImageParam(1, blade, imageParam, 1)) {
        mm::Vec2 scale;
        image.getScale(scale);
        scale.x = imageParam.unknown04 * scale.x;
        scale.y = imageParam.unknown04 * scale.y;
        image.setScale(scale);
        GfMenuObjUtil::addPos(image.unknown10, imageParam.unknown00, imageParam.unknown02);
      }
      GfMenuObjUtil::CtrlParam param;
      param.unknown004("fade_in_r");
      param.unknown04 = 1;
      param.unknown14 = 8;
      GfMenuObjUtil::startCtrl(image.unknown10, param, nullptr);
    }
    GfMenuObjUtil::playJingle(GfDataBlade::isCommonBlade(GfMenuReference::getReferenceBladeID(0)) ? 0xd : 0xc);
    break;
  case GfMenuTypes::unknown003_34:
    GfMenuObjCmnStatus::closeBlStatus();
    unknown015(acc.unknown10);
    break;
  }
}

void GfMenuObjBladeCreate::BoosterNumListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown0c = 0;
    unknown10 = 1;
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(6);
      GfMenuObjOperationInfo::add(acc.unknown10, 0, 0, 0);
    } else if (event.unknown08 == 2) {
      ui::EventData end;
      end.unknown0c = 0;
      end.unknown00 = GfMenuTypes::unknown003_259;
      end.unknown08 = unknown10;
      GfMenuObject::sendEvent(acc.getParentHandle(), end, 0.0f);
    }
    break;
  case 6: {
    int index = event.unknown08;
    int prev = event.unknown0c;
    if (index != -1) {
      unknown20->unknown1188->unknown162(index + 1);
      unknown20->updateIdea(false);
    }
    if (prev != -1 && index != prev) {
      GfMenuObjUtil::playSE(0x19);
    }
    break;
  }
  case 8:
    if (event.unknown0c == 1) {
      unknown20->updateIdea(true);
      unknown10 = 1;
      GfMenuObject::sendCloseEvent(acc.unknown10, 0, 0.0f);
    } else if (event.unknown0c == 2) {
      GfMenuObject::sendCloseEvent(acc.unknown10, 0, 0.0f);
      unknown20->unknown1188->unknown162(0);
      unknown20->updateIdea(false);
    }
    GfMenuObjUtil::playSECommonFromInput(event.unknown0c);
    break;
  case GfMenuTypes::unknown003_33:
    if (unknown0c == 0) {
      unknown014(acc.unknown10);
      unknown0c = 1;
      unknown10 = 0;
      const unknown005 &idea = unknown20->unknown28.unknown50->getContents(unknown20->unknown28.unknown50->getIndex(false));
      u32 level = idea.unknown08;
      if (level > 5) {
        level = 5;
      }
      unknown20->unknown1188->unknown10 = 1;
      unknown20->unknown1188->unknown14 = level;
      unknown20->unknown1188->unknown162(1);
      GfMenuObject::resetInputSelection(acc.unknown10);
      GfMenuObject::setupInputSelection(acc.unknown10, 0, level);
    }
    unknown20->setGuideText(0x39);
    break;
  case GfMenuTypes::unknown003_34:
    if (unknown0c == 1) {
      GfMenuObject::disableFSInput();
      GfMenuObjOperationInfo::remove(acc.unknown10, 0, 0, 0);
      unknown015(acc.unknown10);
      unknown0c = 0;
    }
    break;
  }
}

void GfMenuObjBladeCreate::IdeagramListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown0c = 0;
    break;
  case GfMenuTypes::unknown003_33:
    if (unknown0c == 0) {
      unknown014(acc.unknown10);
      unknown0c = 1;
    }
    break;
  case GfMenuTypes::unknown003_34:
    if (unknown0c == 1) {
      unknown015(acc.unknown10);
      unknown0c = 0;
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
