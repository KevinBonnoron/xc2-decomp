#include "gf/menu/object/gf_menu_obj_target_info.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjTargetInfo::GfMenuObjTargetInfo(u32 handle) : GfMenuObject(handle) {}

GfMenuObjTargetInfo::~GfMenuObjTargetInfo() { ; }

void GfMenuObjTargetInfo::finalize() { GfMenuObject::finalize(); }

void GfMenuObjTargetInfo::update() { GfMenuObject::update(); }

void GfMenuObjTargetInfo::disp(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x11));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjTargetInfo::dispAllEnemy(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0xc));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjTargetInfo::dispAllOther(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0xd));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjTargetInfo::dispAllSymbol(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0xe));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjTargetInfo::startOpen(u32 handle, u32 object, int param0, int param1) {
  ui::UIObjectAcc acc(object);
  if (acc.isDuplicate()) {
    ui::EventData event;
    event.unknown00 = 0x100;
    event.unknown08 = param0;
    event.unknown0c = param1;
    event.unknown10 = acc.getDuplicateIndex();
    ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
  }
}

} // namespace gf
