#include "gf/menu/object/gf_menu_obj_mercenary_root.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "types.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x4d;

GfMenuObjMercenaryRoot::GfMenuObjMercenaryRoot(u32 handle) : GfMenuObject(handle), unknown24(-1), unknown28(this), unknown188(0) {}

GfMenuObjMercenaryRoot::~GfMenuObjMercenaryRoot() {}

void GfMenuObjMercenaryRoot::openBg(int bg) { unknown149(unknown001, GfMenuTypes::unknown003_33, bg); }

void GfMenuObjMercenaryRoot::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMercenaryRoot::update() {
  unknown28.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjMercenaryRoot::seqWaitBGStream() {
  ui::UIObjectAcc bg(unknown18, "IMG_bg");
  if (bg.isStreaming()) {
    return false;
  }
  ui::UIObjectAcc(unknown18, "IMG_bg_front").setDisp(false);
  return true;
}

void GfMenuObjMercenaryRoot::closeBg() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjMercenaryRoot::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  attachExternalCall(unknown001, main.unknown10);
// __LINE__ must be 88 as in the original file: it is the line argument of operator new.
#line 88
  MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
  if (listener != nullptr) {
    listener->release();
  }
  GfMenuObjMainMenu2::setCloseKeyEnable(false);
  GfMenuObject::initialize();
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjMercenaryRoot>(const mm::mtl::Delegate<bool()> *);
