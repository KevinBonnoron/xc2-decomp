#include "gf/menu/object/gf_menu_obj_opening_telop.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
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

// Inferred role: layer names of the three telop positions; original name unknown.
static const char *const unknown004[] = {"LAY_center", "LAY_left", "LAY_right"};
// Inferred role: image names of the three telop positions; original name unknown.
static const char *const unknown005[] = {"IMG_center@%02d", "IMG_left@%02d", "IMG_right@%02d"};

GfMenuObjOpeningTelop::GfMenuObjOpeningTelop(u32 handle) : GfMenuObject(handle), unknown24(), unknown30(nullptr) {
  ui::UISelectObjList::CreateParam param;
  param.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
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
  MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
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

int GfMenuObjOpeningTelop::ctrlFadeOut(u32 handle, u32 type) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 2;
  param.unknown00 = 0.5f;
  param.unknown04 = type;
  return GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

void GfMenuObjOpeningTelop::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 0x21: {
    int telop = event.unknown08_u64;
    u32 image = event.unknown08_u64 >> 32;
    {
      ui::UIObjectAcc layer(acc.unknown10, unknown004[telop]);
      int ctrl = GfMenuObjUtil::getCtrlID(layer.unknown10);
      if (ctrl != -1) {
        GfMenuObjUtil::stopCtrl(ctrl);
      }
      layer.setDisp(true);
      layer.setAlpha(1.0f);
    }
    u32 count = unknown20->unknown24[telop];
    mm::mtl::FixStr<32> name;
    name.format(unknown005[telop], count + 1);
    ui::UIObjectAcc img(acc.unknown10, name.c_str());
    img.setImageIndex(image);
    if (img.isStreaming()) {
      unknown20->unknown30->addObject(img.unknown10);
    }
    unknown20->unknown24[telop]++;
    break;
  }
  case 0x22: {
    int telop = event.unknown08;
    ui::UIObjectAcc layer(acc.unknown10, unknown004[telop]);
    int ctrl = ctrlFadeOut(layer.unknown10, telop + 1);
    hookCtrlEvent(acc.unknown10, ctrl);
    break;
  }
  case 3: {
    if (event.unknown08 == 0) {
      return;
    }
    int telop = event.unknown08 - 1;
    u32 count = unknown20->unknown24[telop];
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < count; i++) {
      name.format(unknown005[telop], i + 1);
      ui::UIObjectAcc img(acc.unknown10, name.c_str());
      if (img.isValid()) {
        img.setImageIndex(0);
        img.setDisp(false);
      }
    }
    unknown20->unknown24[telop] = 0;
    break;
  }
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}
} // namespace gf
