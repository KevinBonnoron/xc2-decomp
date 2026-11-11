#include "gf/menu/object/gf_menu_obj_common_info.h"

#include "gf/gf_allocator.h"
#include "ui/event/ui_event_data.h"

namespace gf {

GfMenuObjCommonInfo::ParamBase *GfMenuObjCommonInfo::createParamAchivement(u32 param0, u32 param1, u32 param2) {
#line 53
  ParamAchivement *param = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ParamAchivement();
  if (param != nullptr) {
    param->addRef();
    param->unknown0c = param0;
    param->unknown10 = param1;
    param->unknown14 = param2;
  }
  return param;
}

ui::UIStr GfMenuObjCommonInfo::ParamAchivement::getTitleString() const { return ui::UIStr("Title", false); }

ui::UIStr GfMenuObjCommonInfo::ParamAchivement::getContentsString() const { return ui::UIStr("Contents", false); }

GfMenuObjCommonInfo::GfMenuObjCommonInfo(u32 handle) : GfMenuObject(handle) {}

GfMenuObjCommonInfo::~GfMenuObjCommonInfo() { GfMenuManyObjects::destroy<CommonInfo>(GfMenuManyObjects::unknown001_6); }

void GfMenuObjCommonInfo::finalize() {}

void GfMenuObjCommonInfo::update() {}

void GfMenuObjCommonInfo::removeObject(ui::UIObjectAcc acc) {
  GfMenuManyObjects::remove<CommonInfo>(GfMenuManyObjects::unknown001_6, acc.unknown10);
  acc.setDisp(false);
}

void GfMenuObjCommonInfo::sendOpen(u32 handle, const CommonInfo &info) {
  ui::EventData event;
  event.unknown00 = 0x21;
  event.unknown08 = registString(info.unknown10->getTitleString());
  event.unknown0c = registString(info.unknown10->getContentsString());
  sendEvent(handle, event, 0.0f);
}

u32 GfMenuObjCommonInfo::open(GfMenuCallContext *context, ParamBase *param) {
  delete param;
  return 0;
}

void GfMenuObjCommonInfo::close(u32) {}

void GfMenuObjCommonInfo::closeAll() {}

void GfMenuObjCommonInfo::pausePickup() {}

void GfMenuObjCommonInfo::continuePickup() {}

} // namespace gf

template void gf::GfMenuManyObjects::remove<gf::GfMenuObjCommonInfo::CommonInfo>(u32, u32);
