#include "gf/menu/object/gf_menu_obj_chain_icon.h"

#include "bdat.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_object_type.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_field_pos_adapter.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_acc.h"
#include "mm_math/mm_vec3.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id passed to getAttachedObject in close(); taken from the game disassembly, original name unknown.
constexpr u32 unknown001 = 0x41;

GfMenuObjChainIcon::GfMenuObjChainIcon(u32 handle) : GfMenuObject(handle) {}

GfMenuObjChainIcon::~GfMenuObjChainIcon() { GfMenuManyObjects::destroy<ChainIconInfo>(GfMenuManyObjects::unknown001_2); }

void GfMenuObjChainIcon::finalize() { GfMenuObject::finalize(); }

void GfMenuObjChainIcon::update() { GfMenuObject::update(); }

void GfMenuObjChainIcon::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
    attachExternalCall(unknown001, main);
// __LINE__ must be 78 as in the original file: it is the line argument of operator new.
#line 78
    ListListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
  }
  ui::UIObjectAcc(unknown18).setTerm();
  GfMenuObject::initialize();
  GfMenuManyObjects::unknown002<ChainIconInfo>(GfMenuManyObjects::unknown001_2, 32);
}

void GfMenuObjChainIcon::removeObject(ui::UIObjectAcc acc) {
  GfMenuManyObjects::remove<ChainIconInfo>(GfMenuManyObjects::unknown001_2, acc.unknown10);
  acc.setDisp(false);
  acc.setTerm();
}

u32 GfMenuObjChainIcon::open(const OpenParam &param) {
  if (GfMenuObjUtil::isMenuObjectFull()) {
    return 0;
  }
  u32 object = getAttachedObject(unknown001);
  if (!ui::UIObjectAcc(object).isValid()) {
    return 0;
  }
  if (ui::UIObjectAcc(object).isTerm()) {
    return 0;
  }
  u32 handle = ui::UIObjectAcc(object).duplicateChild("LAY_chain_icon_root");
  if (!ui::UIObjectAcc(handle).isValid()) {
    return 0;
  }
  {
    GfObjAcc objAcc(param.unknown00);
    if (!objAcc.isValid()) {
      return 0;
    }
    if (objAcc.getType() != OBJECT_TYPE_PC) {
      return 0;
    }
    // The id is normalised before the offset is declared: with the select inside the call (`offsetId == 0 ? 1 : offsetId`, u16 or int) the offset's x and y
    // zeroing stores sit together and merge into one 64-bit store, whereas the game (0x71004282d8) stores x alone before the `tst` and pairs y and z after it.
    int offsetId = Bdat::getVal(GfDataBdat::getFP(BDAT_CHR_DR), "OffsetID", objAcc.getBdatId()).valueU16;
    if (offsetId == 0) {
      offsetId = 1;
    }
    MenuOffset offset;
    GfMenuBdat::getMenuOffset(offsetId, offset);
    mm::Vec3 position = objAcc.getWorldTransform().unknown00;
    position.y += offset.unknown00.y - 1.0f;
    GfMenuFieldPosAdapter::create(ui::UIObjectAcc(handle).searchChild("LAY_chain_icon"), position);
  }
  ui::EventData event;
  event.unknown00 = GfMenuTypes::unknown003_33;
  event.unknown08_u16 = ui::UIObjectAcc(handle).getDuplicateIndex();
  sendEvent(object, event, 0.0f);
  GfMenuManyObjects::unknown003(GfMenuManyObjects::unknown001_2, ChainIconInfo(handle), close);
  return handle;
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

void GfMenuObjChainIcon::ListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case 0x21: {
    ui::UIObjectAcc icon(acc.searchDuplicatedChild("LAY_chain_icon_root", event.unknown08_u16));
    if (icon.isValid()) {
      acc.setDisp(true);
      icon.setDisp(true);
      GfMenuObjUtil::setChildDisp(icon.unknown10, "LAY_main", true);
      GfMenuObjUtil::CtrlParam ctrl;
      ctrl.unknown00 = 1.0f;
      ctrl.unknown08 = 0x20;
      ctrl.unknown20 = 60;
      ctrl.unknown04 = (event.unknown08_u16 << 8) | 1;
      int id = GfMenuObjUtil::startCtrl(icon.unknown10, ctrl, nullptr);
      hookCtrlEvent(acc.unknown10, id);
      ui::UIObjectAcc image(icon.unknown10, "IMG_icon");
      image.startAnimation("fadein", false);
    }
    break;
  }
  case 0x22: {
    ui::UIObjectAcc icon(acc.searchDuplicatedChild("LAY_chain_icon_root", event.unknown08_u16));
    if (icon.isValid()) {
      removeObject(icon);
    }
    break;
  }
  case 3: {
    u32 param = event.unknown08;
    if (param == 0) {
      break;
    }
    ui::UIObjectAcc icon(acc.searchDuplicatedChild("LAY_chain_icon_root", param >> 8));
    if (icon.isValid()) {
      if ((param & 0xff) == 1) {
        GfMenuObjUtil::CtrlParam ctrl;
        ctrl.unknown00 = 0.25f;
        ctrl.unknown08 = 0x22;
        ctrl.unknown20 = 15;
        ctrl.unknown04 = (param & 0xffff00) | 2;
        int id = GfMenuObjUtil::startCtrl(icon.unknown10, ctrl, nullptr);
        hookCtrlEvent(acc.unknown10, id);
      } else if ((param & 0xff) == 2) {
        removeObject(icon);
      }
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjChainIcon::setupScreen(u32 handle, int, int, int, int) { GfMenuObjUtil::setChildDisp(handle, "LAY_main", true); }

} // namespace gf

template void gf::GfMenuManyObjects::remove<gf::GfMenuObjChainIcon::ChainIconInfo>(u32, u32);
template void mm::mtl::Queue<gf::GfMenuObjChainIcon::ChainIconInfo>::push_back(const gf::GfMenuObjChainIcon::ChainIconInfo &);
template void mm::mtl::Queue<gf::GfMenuObjChainIcon::ChainIconInfo>::expand(size_t, size_t);
