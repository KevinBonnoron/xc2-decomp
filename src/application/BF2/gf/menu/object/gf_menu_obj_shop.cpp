#include "gf/menu/object/gf_menu_obj_shop.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_util.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/sequential_play/gf_sequential_play.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_bl_weapon2.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "gf/scom/gf_scom_achiev.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x77;
// Inferred role: active adapter category; original name unknown.
constexpr u32 unknown002 = 1;
// Inferred role: common window shown for orb error 1; original name unknown.
constexpr u16 unknown003 = 0xaf;
// Inferred role: common window shown for orb error 2; original name unknown.
constexpr u16 unknown004 = 0xb0;
// Inferred role: pause bits requested while sleeping at the inn; original name unknown.
constexpr u32 unknown005 = 0x59;
// Inferred role: achievement statistics id counting inn stays; original name unknown.
constexpr u32 unknown006 = 0x23;

u32 GfMenuObjShop::getSellItemTypeMax() { return 0xd; }

void GfMenuObjShop::close(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::UIObjectAcc acc(context->unknown14);
    if (acc.isValid()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_34;
      GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
      GfMenuAdapterManager::delActiveCategory(unknown002);
    }
  }
}

void GfMenuObjShop::dispBlade(bool isDisp) { unknown150(unknown001, 0x46, isDisp); }

void GfMenuObjShop::openOrbError(u32 error) {
  switch (error) {
  case 1:
    GfMenuManager::openCommonWindow(unknown003);
    break;
  case 2:
    GfMenuManager::openCommonWindow(unknown004);
    break;
  }
}

bool GfMenuObjShop::seqWaitFSClose() { return !GfMenuManager::isOpenFullScreen(); }

void GfMenuObjShop::sendEnableEvent(u32 handle) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown00 = 0x40;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjShop::sendExitEvent(u32 handle) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown00 = 0x41;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjShop::sendCloseEvent(u32 handle) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown00 = 0x22;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjShop::sendOpenEvent(u32 handle, int value) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = value;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_33;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjShop::sendReturnEvent(u32 handle, int value) {
  if (handle != 0) {
    ui::EventData event;
    event.unknown08 = value;
    event.unknown0c = 0;
    event.unknown00 = 0x42;
    GfMenuObject::sendEvent(handle, event, 0.0f);
  }
}

void GfMenuObjShop::addCallContextResult(u32 type, u32 value) {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  GfMenuObject::addResultCallContext(main.unknown10, type, value);
}

void GfMenuObjShop::reqRefreshItemList() { unknown59 = true; }

void GfMenuObjShop::update() {
  unknown248.unknown003();
  if (unknown59) {
    refreshItemList();
    unknown59 = false;
  }
  GfMenuObject::update();
}

bool GfMenuObjShop::seqEndDialog() {
  if (unknown4f8 != 0) {
    ui::EventData event;
    event.unknown00 = 0x42;
    GfMenuObject::sendEvent(unknown4f8, event, 0.0f);
  }
  return true;
}

bool GfMenuObjShop::seqIntervalSleep() {
  if (unknown4d8 == 0) {
    unknown4d8 = 1;
  }
  return --unknown4d8 == 0;
}

bool GfMenuObjShop::seqWaitLoadBlWeapon() {
  unknown570->reset();
  if (GfMenuObjBlWeapon2::attach(unknown570)) {
    unknown248.unknown002(&GfMenuObjShop::seqWaitEndBlWeapon);
    return true;
  }
  return false;
}

bool GfMenuObjShop::seqWaitEndBlWeapon() {
  if (!unknown570->isTerm()) {
    return false;
  }
  ui::UIObjectAcc main(unknown18, "LAY_main");
  sendEnableEvent(main.searchChild("LAY_store_action"));
  return true;
}

u32 GfMenuObjShop::getShopSubLayer(u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (unknown28) {
  case 0:
    return acc.searchChild("LAY_store");
  case 1:
    return acc.searchChild("LAY_exchange");
  case 2:
    return acc.searchChild("LAY_inn");
  case 3:
    return acc.searchChild("LAY_orb");
  }
  return 0;
}

u32 GfMenuObjShop::getShopSubActLayer(u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (unknown28) {
  case 0:
    return acc.searchChild("LAY_store_action");
  case 1:
    return acc.searchChild("LAY_exc_task_list");
  case 2:
    return acc.searchChild("LAY_inn_action");
  case 3:
    return acc.searchChild("LAY_orb_item_list");
  }
  return 0;
}

int GfMenuObjShop::getSpecialShop(u32 shop) {
  if (shop != 0) {
    u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SPECIAL_SHOP);
    if (bdat != nullptr) {
      u16 scenarioFlag = GfDataUtil::getScenarioFlag();
      int top = Bdat::getIdTop(bdat);
      for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
        int id = top + i;
        u16 flag = Bdat::getVal(bdat, "scenario_flag", id).valueU16;
        if (flag == 0 || scenarioFlag == flag) {
          u16 shopId = Bdat::getVal(bdat, "shop_id", id).valueU16;
          if (shopId != 0 && shopId == shop) {
            return id;
          }
        }
      }
    }
  }
  return 0;
}

bool GfMenuObjShop::isShopWeapon(u32 shop) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SHOP_LIST);
  if (Bdat::getVal(bdat, "ShopType", shop).valueS8 == 0 && Bdat::getVal(bdat, "ShopIcon", shop).valueU16 == 0x1ae) {
    return true;
  }
  return false;
}

bool GfMenuObjShop::seqStartSleepFade() {
  GfSequentialPlay::pauseOn(unknown005);
  SCOM_ACHIEV_INC::addTotalCount(unknown006, 1);
  SCOM_ACHIEV_INC::create(unknown006, 1, 0);
  SCOM_FIELD_VOICE::createExitInn();
  SCOM_RANDOM_INN::setRandom();
  unknown248.unknown002(&GfMenuObjShop::seqWaitSleepFade);
  unknown248.unknown002(&GfMenuObjShop::seqIntervalSleep);
  unknown248.unknown002(&GfMenuObjShop::seqStartLevelUp);
  unknown4d8 = 0;
  unknown4dc = false;
  return true;
}

void GfMenuObjShop::openNumSelect(u32 owner, u32 value, bool isFlag) {
  ui::UIObjectAcc acc(unknown18, "LAY_num_select");
  unknownd0 = owner;
  ui::EventData event;
  event.unknown00 = 0x21;
  event.unknown08 = value;
  event.unknown0c = 0x280;
  event.unknown10 = 0x1e0;
  event.unknown14 = isFlag;
  GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
}

bool GfMenuObjShop::seqStartLevelUp() {
  if (unknown240) {
    GfGameUtilCloudSea::setInnCloudSea(static_cast<CLOUD_SEA>(GfGameUtilCloudSea::getCloudSea() == 0));
    unknown240 = false;
  }
  GfMenuManager::openFullScreen(5, true, true);
  unknown248.unknown002(&GfMenuObjShop::seqWaitFSClose);
  unknown248.unknown002(&GfMenuObjShop::seqEnd);
  return true;
}

bool GfMenuObjShop::seqEnd() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  GfSequentialPlay::pauseOff();
  if (unknown4e0 != 0) {
    addCallContextResult(unknown4e0, unknown4e4);
  }
  GfMenuObject::termCallContext(main.unknown10);
  return true;
}

bool GfMenuObjShop::getExcTaskQuestAdditionalValue(u32 id, u32 &value) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SHOP_CHANGE_TASK);
  if (bdat != nullptr && GfMenuBdat::isValidBdatID(bdat, id)) {
    value = Bdat::getVal(bdat, "AddFlagValue", id).valueU8;
    return true;
  }
  return false;
}

void GfMenuObjShop::setFilterIndex() {
  u32 filter = unknown60[unknownc0];
  ui::UIObjectAcc acc(unknown18, "TXT_store_sell_index");
  if (acc.isValid()) {
    u8 *bdat = GfDataBdat::getFP(BDAT_MENU_FILTER_CATEGORY);
    ui::UIStr text(bdat, GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_ITEM_LIST_FILTER, filter + 1));
    acc.setText(text);
  }
}

bool GfMenuObjShop::seqEndRecipeIndexOpen() {
  ui::UIObjectAcc acc(unknown18, "LAY_orb_rcp");
  switch (unknownfc) {
  case 0:
    acc.setDispChild(true, "TXT_orb_rcp_type_rare_index");
    break;
  case 1:
    acc.setDispChild(true, "TXT_orb_rcp_type_cate_index");
    break;
  default:
    acc.setDispChild(false, "TXT_orb_rcp_type_rare_index");
    acc.setDispChild(false, "TXT_orb_rcp_type_cate_index");
    break;
  }
  return true;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjShop, 8>>(const mm::mtl::Delegate<bool()> *);
