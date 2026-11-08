#include "gf/menu/object/gf_menu_obj_party_status2.h"

#include <string.h>

#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/adapter/gf_menu_battle_adapter.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_acc.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x5d;

GfMenuObjPartyStatus2::GfMenuObjPartyStatus2(u32 handle) : GfMenuObject(handle), unknown24(false), unknown28(nullptr), unknown30(-1) { memset(unknown34, 0xff, sizeof(unknown34)); }

GfMenuObjPartyStatus2::~GfMenuObjPartyStatus2() { mm::mtl::safeRelease(unknown28); }

void GfMenuObjPartyStatus2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPartyStatus2::update() { GfMenuObject::update(); }

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
  MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
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

} // namespace gf
