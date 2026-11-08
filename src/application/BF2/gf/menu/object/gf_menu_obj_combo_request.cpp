#include "gf/menu/object/gf_menu_obj_combo_request.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x5c;

GfMenuObjComboRequest::GfMenuObjComboRequest(u32 handle) : GfMenuObject(handle) {}

GfMenuObjComboRequest::~GfMenuObjComboRequest() { ; }

void GfMenuObjComboRequest::finalize() { GfMenuObject::finalize(); }

void GfMenuObjComboRequest::update() {
  ui::UIObjectAcc(unknown18).setAlpha(0.0f);
  GfMenuObject::update();
}

void GfMenuObjComboRequest::attachComboRequest(GfMenuCallContext *context) { unknown152(context, unknown001); }

void GfMenuObjComboRequest::closeComboRequest(u16 index, bool isImmediate) {
  ui::UIObjectAcc acc(getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown0c = 0;
    event.unknown00 = 0x102;
    event.unknown08_u16 = index;
    event.unknown0a = isImmediate;
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjComboRequest::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 81 as in the original file: it is the line argument of operator new.
#line 81
  MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, listener);
  if (listener != nullptr) {
    listener->release();
  }
  attachExternalCall(unknown001, main);
  GfMenuObject::initialize();
}

// Inferred role: default button of each combo request slot; original name unknown.
static const u32 unknown002[] = {4, 0x40, 0x80};

void GfMenuObjComboRequest::setupComboReq(const ui::UIObjectAcc &acc, u16 index, u16 combo, bool isEnable, u32 button) {
  mm::mtl::FixStr<32> name;
  u32 number = index + 1;
  name.format("TXT_combo_name@%02d", number);
  ui::UIObjectAcc text(acc.unknown10, name.c_str());
  if (text.isValid()) {
    text.setText(GfMenuObjUtil::getElementComboName(combo));
  }
  name.format("IMG_combo_btn_disable@%02d", number);
  ui::UIObjectAcc disable(acc.unknown10, name.c_str());
  if (disable.isValid()) {
    disable.setDisp(!isEnable);
  }
  if (button == 0) {
    button = unknown002[index];
  }
  name.format("IMG_combo_btn@%02d", number);
  int icon = GfMenuObjUtil::getBtnIconNumber(button);
  ui::UIObjectAcc image(acc.unknown10, name.c_str());
  image.setImageIndex(GfMenuBdat::getIconImageIndex(icon));
}

} // namespace gf
