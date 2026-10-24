#include "gf/menu/object/gf_menu_obj_field_icon.h"

#include "gf/menu/adapter/gf_menu_pos_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/ui_object_acc.h"

namespace gf {

constexpr u32 CALL_FIELD_ICON = 120;

GfMenuObjFieldIcon::GfMenuObjFieldIcon(u32 handle) : GfMenuObject(handle) {}

GfMenuObjFieldIcon::~GfMenuObjFieldIcon() { ; }

void GfMenuObjFieldIcon::open(GfMenuCallContext *context, const OpenParam &param) {
  if (context == nullptr || param.unknown00 == 0) {
    return;
  }
  ui::UIObjectAcc root(getAttachedObject(CALL_FIELD_ICON));
  if (GfMenuObjUtil::checkCCStart(context) && root.isValid()) {
    ui::UIObjectAcc icon(root.duplicateChild("LAY_icon"));
    if (icon.isValid()) {
      u32 imageIndex = GfMenuBdat::getIconImageIndex(param.unknown00);
      ui::UIObjectAcc(icon.handle, "IMG_icon").setImageIndex(imageIndex);
      icon.setDisp(true);
      mm::Vec3 position = param.unknown10;
      position += param.unknown20;
      GfMenuPosAdapter::createFixedPoint(icon.handle, position, false);
      startCallContext(context, CALL_FIELD_ICON, icon.handle);
    }
  }
}

void GfMenuObjFieldIcon::close(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, CALL_FIELD_ICON)) {
    ui::UIObjectAcc icon(context->unknown14);
    if (icon.isValid()) {
      icon.setTerm();
    }
  }
}

void GfMenuObjFieldIcon::disp(GfMenuCallContext *context, bool isDisp) {
  if (GfMenuObjUtil::checkCCNext(context, CALL_FIELD_ICON)) {
    ui::UIObjectAcc icon(context->unknown14);
    if (icon.isValid()) {
      icon.setDispChild(isDisp, "IMG_icon");
    }
  }
}

void GfMenuObjFieldIcon::dispAll(bool isDisp) { ui::UIObjectAcc(getAttachedObject(CALL_FIELD_ICON)).setDisp(isDisp); }

void GfMenuObjFieldIcon::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    attachExternalCall(CALL_FIELD_ICON, main.handle);
    GfMenuObject::initialize();
  }
}

void GfMenuObjFieldIcon::finalize() { GfMenuObject::finalize(); }

void GfMenuObjFieldIcon::update() { GfMenuObject::update(); }

} // namespace gf
