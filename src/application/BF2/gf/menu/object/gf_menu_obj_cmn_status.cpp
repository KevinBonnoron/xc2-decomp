#include "gf/menu/object/gf_menu_obj_cmn_status.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_radar_graph.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x52;

bool GfMenuObjCmnStatus::s_DispFlag[2];

GfMenuObjCmnStatus::GfMenuObjCmnStatus(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr) {
  ui::UISelectObjList::CreateParam param;
  param.allocator = getAllocator(ALLOCATOR_DEFAULT);
  unknown28 = ui::UISelectObjList::create(param);
  param = ui::UISelectObjList::CreateParam();
  param.allocator = getAllocator(ALLOCATOR_DEFAULT);
  unknown30 = ui::UISelectObjList::create(param);
}

GfMenuObjCmnStatus::~GfMenuObjCmnStatus() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
}

bool GfMenuObjCmnStatus::isOpenDrStatus() { return s_DispFlag[0]; }

bool GfMenuObjCmnStatus::isOpenBlStatus() { return s_DispFlag[1]; }

void GfMenuObjCmnStatus::finalize() {
  GfMenuReference::resetDriverVirtual();
  GfMenuReference::resetBladeVirtual();
  GfMenuObject::finalize();
}

void GfMenuObjCmnStatus::update() { GfMenuObject::update(); }

void GfMenuObjCmnStatus::setInputDisable() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    GfMenuObject::disableInput(acc.unknown10);
  }
}

void GfMenuObjCmnStatus::setInputEnable() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    GfMenuObject::enableInput(acc.unknown10);
  }
}

void GfMenuObjCmnStatus::openDrStatus(u32 driver, int page) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08 = driver;
    event.unknown0c = page;
    GfMenuObject::sendEvent(acc.searchChild("LAY_status_dr"), event, 0.0f);
    s_DispFlag[0] = true;
  }
}

void GfMenuObjCmnStatus::closeDrStatus() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(acc.searchChild("LAY_status_dr"), event, 0.0f);
    s_DispFlag[0] = false;
  }
}

bool GfMenuObjCmnStatus::swapDrStatus() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::UIObjectAcc status(acc.unknown10, "LAY_status_dr");
    ui::EventData event;
    event.unknown00 = 0x102;
    GfMenuObject::sendEvent(status.unknown10, event, 0.0f);
    s_DispFlag[0] = !s_DispFlag[0];
    return s_DispFlag[0];
  }
  return false;
}

void GfMenuObjCmnStatus::openBlStatus(u32 blade, int page) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08 = blade;
    event.unknown0c = page;
    GfMenuObject::sendEvent(acc.searchChild("LAY_status_bl"), event, 0.0f);
    s_DispFlag[1] = true;
  }
}

void GfMenuObjCmnStatus::closeBlStatus() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(acc.searchChild("LAY_status_bl"), event, 0.0f);
    s_DispFlag[1] = false;
  }
}

bool GfMenuObjCmnStatus::swapBlStatus() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::UIObjectAcc status(acc.unknown10, "LAY_status_bl");
    ui::EventData event;
    event.unknown00 = 0x102;
    GfMenuObject::sendEvent(status.unknown10, event, 0.0f);
    s_DispFlag[1] = !s_DispFlag[1];
    return s_DispFlag[1];
  }
  return false;
}

void GfMenuObjCmnStatus::updateBladeBase(u32 page) {
  u32 type = page - 2;
  bool isSkill = type < 5;
  ui::UIObjectAcc index(unknown18, "LAY_status_bl_index");
  ui::UIObjectAcc indexSkill(unknown18, "LAY_status_bl_index_sk");
  ui::UIObjectAcc base(unknown18, "IMG_status_bl_base");
  ui::UIObjectAcc baseSkill(unknown18, "IMG_status_bl_base_sk");
  index.setDisp(!isSkill);
  base.setDisp(!isSkill);
  indexSkill.setDisp(isSkill);
  baseSkill.setDisp(isSkill);
}
} // namespace gf
