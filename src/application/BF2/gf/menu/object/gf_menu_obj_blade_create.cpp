#include "gf/menu/object/gf_menu_obj_blade_create.h"

#include <string.h>

#include "bdat.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_save.h"
#include "gf/data/gf_item_id.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_model_view.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_sound_manager.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_blade_name.h"
#include "gf/menu/object/gf_menu_obj_fade.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_manager.h"
#include "gf/util/gf_item_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "scn/scn_render_dr_sys_parm_acc.h"
#include "ui/list/ui_list_info.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

#include "gf/object/gf_obj_acc.h"

namespace gf {
struct GF_OBJ_HANDLE;

// Inferred role: full screen layer id; original name unknown.
constexpr u32 unknown001 = 0x14;

// Inferred role: names of the pages of the creation screen; original name unknown.
const char *const unknown002[6] = {"LAY_dr_select", "LAY_core_select", "LAY_bst_select", "LAY_confirm", "LAY_create", "LAY_result"};

// Inferred role: object type of the drivers in the model view; original name unknown.
constexpr u32 unknown003 = 3;

// Inferred role: driver of each camera of the driver select page; original name unknown.
const u32 unknown004[16] = {1, 2, 6, 3, 0x15, 0x13, 0x15, 0x15, 0xb9, 0xba, 0xbb, 0xbc, 0x154, 0x151, 0xffffffff, 0x150};

// Inferred role: sets the weapon type of a driver in the model view; original name unknown.
static void unknown006(GfMenuModelView *view, u32 driver, int weaponType) { view->setObjectCommandValue(view->findGfObj(unknown003, driver), "V_weaponselect", weaponType); }

// Inferred role: starts the blade arts animation of a driver in the model view; original name unknown.
static void unknown007(GfMenuModelView *view, u32 driver) { view->sendObjectCommand(view->findGfObj(unknown003, driver), "C_bladearts_01"); }

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

void GfMenuObjBladeCreate::update() {
  unknownaf8.unknown003();
  if (unknown28.unknownac8 != nullptr) {
    unknown28.unknownac8->update();
  }
  GfMenuObject::update();
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
  unknown11b0 = GfReqCommand::reqSave(SAVESLOT_DEFAULT);
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

bool GfMenuObjBladeCreate::seqCreateWaitEvent() {
  if (*unknown1118) {
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
  return GfItemUtil::isValidCrystal(item) && (item != ITEM_CRYSTAL_WADATSUMI || driver == 6);
}

u32 GfMenuObjBladeCreate::getInvalidCrystalMsgID(u32 item) {
  int driver = unknown28.unknown40->getContents(unknown28.unknown40->getIndex(false));
  u32 message;
  if (item == ITEM_CRYSTAL_WADATSUMI && driver != 6) {
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
    GfObjAcc(unknown28.unknownac8->findGfObj(unknown003, id)).setDisp(OBJDISP_UNKNOWN_1, true);
  }
  return true;
}

} // namespace gf
