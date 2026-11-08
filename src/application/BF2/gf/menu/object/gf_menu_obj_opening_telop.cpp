#include "gf/menu/object/gf_menu_obj_opening_telop.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x82;
// Inferred role: telop position; original name unknown.
constexpr u32 unknown002_0 = 0;
constexpr u32 unknown002_1 = 1;
constexpr u32 unknown002_2 = 2;

GfMenuObjOpeningTelop::GfMenuObjOpeningTelop(u32 handle) : GfMenuObject(handle), unknown24(0), unknown28(0), unknown2c(0), unknown30(nullptr) {
  ui::UISelectObjList::CreateParam param;
  param.allocator = getAllocator(ALLOCATOR_DEFAULT);
  unknown30 = ui::UISelectObjList::create(param);
}

GfMenuObjOpeningTelop::~GfMenuObjOpeningTelop() { mm::mtl::safeRelease(unknown30); }

void GfMenuObjOpeningTelop::openCenter(u32 telop) { unknown141(unknown001, GfMenuTypes::unknown003_33, unknown002_0, telop); }

void GfMenuObjOpeningTelop::closeCenter() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjOpeningTelop::openLeft(u32 telop) { unknown141(unknown001, GfMenuTypes::unknown003_33, unknown002_1, telop); }

void GfMenuObjOpeningTelop::closeLeft() { unknown157(unknown001, GfMenuTypes::unknown003_34, unknown002_1); }

void GfMenuObjOpeningTelop::openRight(u32 telop) { unknown141(unknown001, GfMenuTypes::unknown003_33, unknown002_2, telop); }

void GfMenuObjOpeningTelop::closeRight() { unknown157(unknown001, GfMenuTypes::unknown003_34, unknown002_2); }

void GfMenuObjOpeningTelop::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
// __LINE__ must be 158 as in the original file: it is the line argument of operator new.
#line 158
  MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
  if (listener != nullptr) {
    listener->release();
  }
  attachExternalCall(unknown001, main.unknown10);
  GfMenuObject::initialize();
}

void GfMenuObjOpeningTelop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjOpeningTelop::update() {
  for (u32 i = 0; i < unknown30->getSize(); i++) {
    ui::UIObjectAcc acc(unknown30->getObject(i));
    if (!acc.isStreaming()) {
      ctrlFadeIn(acc.unknown10, 0);
      unknown30->delObject(acc.unknown10);
    }
  }
  GfMenuObject::update();
}

void GfMenuObjOpeningTelop::ctrlFadeIn(u32 handle, u32 type) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 1;
  param.unknown00 = 0.5f;
  param.unknown04 = type;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

void GfMenuObjOpeningTelop::ctrlFadeOut(u32 handle, u32 type) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 2;
  param.unknown00 = 0.5f;
  param.unknown04 = type;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

} // namespace gf
