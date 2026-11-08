#include "gf/menu/object/gf_menu_obj_chain_icon.h"

#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id passed to getAttachedObject in close(); taken from the game disassembly, original name unknown.
constexpr u32 unknown001 = 0x41;

GfMenuObjChainIcon::GfMenuObjChainIcon(u32 handle) : GfMenuObject(handle) {}

GfMenuObjChainIcon::~GfMenuObjChainIcon() { GfMenuManyObjects::destroy<ChainIconInfo>(GfMenuManyObjects::unknown001_2); }

void GfMenuObjChainIcon::finalize() { GfMenuObject::finalize(); }

void GfMenuObjChainIcon::update() { GfMenuObject::update(); }

void GfMenuObjChainIcon::removeObject(ui::UIObjectAcc acc) {
  GfMenuManyObjects::remove<ChainIconInfo>(GfMenuManyObjects::unknown001_2, acc.unknown10);
  acc.setDisp(false);
  acc.setTerm();
}

void GfMenuObjChainIcon::close(u32 handle) {
  ui::UIObjectAcc root(getAttachedObject(unknown001));
  if (!root.isValid()) {
    return;
  }
  if (root.isTerm()) {
    return;
  }
  ui::UIObjectAcc acc(handle);
  if (!acc.isValid()) {
    return;
  }
  if (!acc.isDuplicate()) {
    return;
  }
  // The game builds a third temporary here and destroys it before sendEvent; using acc moves the destructor after the call.
  ui::EventData event;
  event.unknown00 = GfMenuTypes::unknown003_34;
  event.unknown08_u16 = ui::UIObjectAcc(handle).getDuplicateIndex();
  sendEvent(root.unknown10, event, 0.0f);
}

void GfMenuObjChainIcon::closeAll() {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      GfMenuManyObjects::closeAll<ChainIconInfo>(GfMenuManyObjects::unknown001_2, close);
    }
  }
}

void GfMenuObjChainIcon::setupScreen(u32 handle, int, int, int, int) { GfMenuObjUtil::setChildDisp(handle, "LAY_main", true); }

} // namespace gf

template void gf::GfMenuManyObjects::remove<gf::GfMenuObjChainIcon::ChainIconInfo>(u32, u32);
template void mm::mtl::Queue<gf::GfMenuObjChainIcon::ChainIconInfo>::push_back(const gf::GfMenuObjChainIcon::ChainIconInfo &);
template void mm::mtl::Queue<gf::GfMenuObjChainIcon::ChainIconInfo>::expand(size_t, size_t);
