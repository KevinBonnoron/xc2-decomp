#include "gf/menu/object/gf_menu_obj_party_status2.h"

#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/adapter/gf_menu_battle_adapter.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_gfobj_adapter.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/sound/gf_sound.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x5d;

GfMenuObjPartyStatus2::GfMenuObjPartyStatus2(u32 handle) : GfMenuObject(handle), unknown24(false), unknown28(nullptr), unknown30{-1, -1, -1} {}

GfMenuObjPartyStatus2::~GfMenuObjPartyStatus2() { mm::mtl::safeRelease(unknown28); }

void GfMenuObjPartyStatus2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPartyStatus2::update() { GfMenuObject::update(); }

void GfMenuObjPartyStatus2::setupPartyStatus(ui::UIObjectAcc &acc, GfMenuRewriteNumber *number) {
  mm::mtl::FixStr<32> name;
  for (u32 index = 0; index < 3; index++) {
    name.format("TXT_dr_name@%02d", index + 1);
    GfMenuCharDataAdapter *driverName = GfMenuCharDataAdapter::createFromPartyDriver(acc.searchChild(name.c_str()), 2, index, true);
    name.format("LAY_dr@%02d", index + 1);
    driverName->unknown24 = acc.searchChild(name.c_str());
    name.format("TXT_dr_lv_num@%02d", index + 1);
    GfMenuCharDataAdapter::createFromPartyDriver(acc.searchChild(name.c_str()), 1, index, true);
    name.format("TXT_dr_hp_num@%02d", index + 1);
    GfMenuGfObjAdapter *hpNumber = GfMenuGfObjAdapter::createFromPartyDriver(acc.searchChild(name.c_str()), 0, index, true);
    if (hpNumber != nullptr) {
      hpNumber->setNumberInterpolateMode(0.2f);
      hpNumber->setRewriteNumber(number);
    }
    name.format("LAY_dr_hp@%02d", index + 1);
    ui::UIObjectAcc layout(acc.unknown10, name.c_str());
    name.format("IMG_dr_hp_bar@%02d", index + 1);
    u32 handle = acc.searchChild(name.c_str());
    ui::UIObjectAcc bar(handle);
    GfMenuGfObjAdapter *hpBar = GfMenuGfObjAdapter::createFromPartyDriver(handle, 0, index, true);
    if (hpBar != nullptr) {
      hpBar->setNumberInterpolateMode(0.2f);
      hpBar->setRewriteNumber(number);
    }
    bar.setExtType(1);
    bar.setAddColor("dr_hp_normal");
    addNumberEventCondition(acc.unknown10, name.c_str(), 0, index + 1, 0.2f);
    u32 duplicate = layout.duplicateChild(name.c_str());
    ui::UIObjectAcc damageBar(duplicate);
    if (damageBar.isValid()) {
      GfMenuGfObjAdapter *damage = GfMenuGfObjAdapter::createFromPartyDriver(duplicate, 0, index, true);
      if (damage != nullptr) {
        damage->setNumberInterpolateMode(0.6f);
        damage->setRewriteNumber(number);
      }
      damageBar.setExtType(1);
      damageBar.setAddColor("red");
      damageBar.setAlpha(0.5f);
      damageBar.setDispPriority(bar.getDispPriority() - 1);
    }
    name.format("IMG_dr_exp_bar@%02d", index + 1);
    u32 expHandle = acc.searchChild(name.c_str());
    ui::UIObjectAcc exp(expHandle);
    GfMenuCharDataAdapter *expAdapter = GfMenuCharDataAdapter::createFromPartyDriver(expHandle, 0x16, index, true);
    if (expAdapter != nullptr) {
      expAdapter->setNumberInterpolateMode(0.2f);
      expAdapter->setRewriteNumber(number);
    }
    exp.setExtType(1);
  }
}

void GfMenuObjPartyStatus2::sendEvent(u32 handle, u32 type, u32 param) {
  if (handle != 0) {
    unknown140(handle, type, param, 0.0f);
  }
}

void GfMenuObjPartyStatus2::initialize() {
  ui::UIObjectAcc root(unknown18);
  u32 main = root.searchChild("LAY_main");
// __LINE__ must be 109 as in the original file: it is the line argument of operator new.
#line 109
  MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, listener);
  if (listener != nullptr) {
    listener->release();
  }
  attachExternalCall(unknown001, main);
  {
    ui::UIObjectAcc icon(root.unknown10, "IMG_buff_icon");
    ui::UIObjectAcc gauge(root.unknown10, "IMG_buff_gauge");
    GfMenuBattleAdapter::create(icon.unknown10, 0x15)->unknown30 = 0;
    icon.setExtType(4);
    GfMenuBattleAdapter::create(gauge.unknown10, 0x15)->unknown30 = 0;
    gauge.setExtType(4);
  }
  GfMenuObject::initialize();
}

void GfMenuObjPartyStatus2::close() { GF_MENU_REQUEST_EVENT(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjPartyStatus2::disp(bool isDisp) { unknown154(unknown001, isDisp); }

void GfMenuObjPartyStatus2::open() { GF_MENU_REQUEST_EVENT(unknown001, GfMenuTypes::unknown003_33); }

void GfMenuObjPartyStatus2::levelup(u32 member) { GF_MENU_REQUEST_EVENT_WITH(unknown001, GfMenuTypes::unknown003_257, event_.unknown0c = 0; event_.unknown08 = member;); }

void GfMenuObjPartyStatus2::movePartyFrameIn(ui::UIObjectAcc &acc, u32 index, int &ctrl) {
  mm::mtl::FixStr<32> name;
  GfObjAcc driver(GfGameParty::getHandleDriver(index));
  if (driver.getBdatId() != 0) {
    name.format("LAY_dr@%02d", index + 1);
    ui::UIObjectAcc frame(acc.searchChild(name.c_str()));
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x201;
    param.unknown0c = 1;
    param.unknown11 = true;
    param.unknown04 = index + 7;
    param.unknown00 = 0.3f;
    param.unknown1c = index * 0.1f;
    ctrl = GfMenuObjUtil::startCtrl(frame.unknown10, param, nullptr);
    GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
  }
}

void GfMenuObjPartyStatus2::movePartyFrameOut(ui::UIObjectAcc &acc, u32 index, int &ctrl) {
  mm::mtl::FixStr<32> name;
  GfObjAcc driver(GfGameParty::getHandleDriver(index));
  int bdatId = driver.getBdatId();
  name.format("LAY_dr@%02d", index + 1);
  ui::UIObjectAcc frame(acc.searchChild(name.c_str()));
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 0x2002;
  param.unknown0c = 1;
  param.unknown04 = index + 10;
  param.unknown00 = bdatId == 0 ? 0.0f : 0.3f;
  param.unknown1c = bdatId == 0 ? 0.0f : index * 0.1f;
  ctrl = GfMenuObjUtil::startCtrl(frame.unknown10, param, nullptr);
  GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
}

void GfMenuObjPartyStatus2::movePartyFrameInEnd(ui::UIObjectAcc &acc, u32 index) {
  mm::mtl::FixStr<32> name;
  GfMenuObjUtil::CtrlParam param;
  name.format("TXT_dr_name@%02d", index + 1);
  {
    ui::UIObjectAcc text(acc.unknown10, name.c_str());
    param.unknown08 = 1;
    param.unknown00 = 0.2f;
    GfMenuObjUtil::startCtrl(text.unknown10, param, nullptr);
  }
  name.format("TXT_dr_hp_num@%02d", index + 1);
  {
    ui::UIObjectAcc text(acc.unknown10, name.c_str());
    param.unknown08 = 1;
    param.unknown00 = 0.2f;
    GfMenuObjUtil::startCtrl(text.unknown10, param, nullptr);
  }
}

void GfMenuObjPartyStatus2::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown20->unknown28 = unknown168();
    setupPartyStatus(acc, unknown20->unknown28);
    GfMenuObjUtil::setChildDisp(handle, "LAY_dr_list", true);
    acc.setDisp(false);
    break;
  case 3: {
    u32 state = event.unknown08;
    switch (state) {
    case 1:
      movePartyFrameIn(acc, 0, unknown20->unknown30[0]);
      movePartyFrameIn(acc, 1, unknown20->unknown30[1]);
      movePartyFrameIn(acc, 2, unknown20->unknown30[2]);
      break;
    case 4:
      movePartyFrameOut(acc, 0, unknown20->unknown30[0]);
      movePartyFrameOut(acc, 1, unknown20->unknown30[1]);
      movePartyFrameOut(acc, 2, unknown20->unknown30[2]);
      break;
    case 7:
    case 8:
    case 9:
      movePartyFrameInEnd(acc, state - 7);
      unknown20->unknown30[state - 7] = -1;
      break;
    case 10:
    case 11:
    case 12:
      unknown20->unknown30[state - 10] = -1;
      break;
    }
    break;
  }
  case 0xd:
    if (event.unknown0c == 0) {
      u32 index = event.unknown10;
      u32 state = event.unknown08;
      mm::mtl::FixStr<32> name;
      name.format("IMG_dr_dmg_eff@%02d", index);
      ui::UIObjectAcc effect(acc.searchChild(name.c_str()));
      if (state == 1 || state == 2) {
        effect.setDisp(true);
        effect.startAnimation("pinch", false);
      } else {
        effect.setDisp(false);
      }
    }
    break;
  case GfMenuTypes::unknown003_33:
    if (!unknown20->unknown24) {
      for (u32 i = 0; i < 3; i++) {
        if (unknown20->unknown30[i] != -1) {
          GfMenuObjUtil::stopCtrl(unknown20->unknown30[i]);
          unknown20->unknown30[i] = -1;
        }
      }
      acc.setDisp(true);
      mm::mtl::FixStr<32> name;
      for (u32 i = 1; i < 4; i++) {
        name.format("LAY_dr@%02d", i);
        ui::UIObjectAcc frame(handle, name.c_str());
        frame.setAlpha(0.0f);
        name.format("dr_position%02d", i);
        mm::Rect<s16> rect;
        frame.getLayoutRect(name.c_str(), rect);
        mm::Pnt<s16> pos;
        frame.getPos(pos);
        pos.x = rect.x;
        frame.setPos(pos);
        name.format("TXT_dr_name@%02d", i);
        ui::UIObjectAcc driverName(handle, name.c_str());
        driverName.setAlpha(0.0f);
        name.format("TXT_dr_hp_num@%02d", i);
        ui::UIObjectAcc driverHp(handle, name.c_str());
        driverHp.setAlpha(0.0f);
      }
      if (unknown20->unknown28 != nullptr) {
        unknown20->unknown28->unknown10 = false;
      }
      unknown20->unknown24 = true;
      if (handle != 0) {
        unknown140(handle, 3, 1, 0.0f);
      }
    }
    break;
  case GfMenuTypes::unknown003_34:
    if (unknown20->unknown24) {
      unknown20->unknown24 = false;
      for (u32 i = 0; i < 3; i++) {
        if (unknown20->unknown30[i] != -1) {
          GfMenuObjUtil::stopCtrl(unknown20->unknown30[i]);
          unknown20->unknown30[i] = -1;
        }
      }
      if (handle != 0) {
        unknown158(handle, 3, 4, 0.0f);
      }
    }
    break;
  case GfMenuTypes::unknown003_257: {
    u32 number = event.unknown08 + 1;
    mm::mtl::FixStr<32> name;
    name.format("IMG_dr_exp_eff@%02d", number);
    ui::UIObjectAcc effect(acc.searchChild(name.c_str()));
    effect.startAnimation("label", false);
    name.format("TXT_dr_levelup@%02d", number);
    ui::UIObjectAcc levelup(acc.searchChild(name.c_str()));
    if (levelup.isValid()) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x10000000;
      param.unknown50 = "mnu034_levelup_move";
      param.unknown58 = "level_up";
      param.unknown11 = true;
      param.unknown14 = 8;
      GfMenuObjUtil::startCtrl(levelup.unknown10, param, nullptr);
    }
    name.format("TXT_dr_levelup2@%02d", number);
    ui::UIObjectAcc levelup2(acc.searchChild(name.c_str()));
    if (levelup2.isValid()) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x10000000;
      param.unknown50 = "mnu034_levelup_scale";
      param.unknown58 = "level_up";
      param.unknown11 = true;
      param.unknown14 = 8;
      GfMenuObjUtil::startCtrl(levelup2.unknown10, param, nullptr);
    }
    GfMenuObjUtil::playJingle(5);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
