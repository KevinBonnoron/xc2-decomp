#include "gf/menu/object/gf_menu_obj_operation_info.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x47;

GfMenuObjOperationInfo::GfMenuObjOperationInfo(u32 handle) : GfMenuObject(handle) {}

GfMenuObjOperationInfo::~GfMenuObjOperationInfo() { ; }

void GfMenuObjOperationInfo::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
// __LINE__ must be 107 as in the original file: it is the line argument of operator new.
#line 107
    MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
    attachExternalCall(unknown001, main);
  }
  GfMenuObject::initialize();
}

void GfMenuObjOperationInfo::dupClose(mm::mtl::FixedVector<DupItem, 16> &) {}

void GfMenuObjOperationInfo::setupScreen(u32, mm::mtl::FixedVector<DupItem, 16> &) {}

void GfMenuObjOperationInfo::dispOffIconTable(mm::mtl::FixedVector<DupItem, 16> &table, u32 index) {
  if (index < table.size()) {
    ui::UIObjectAcc acc(table[index].unknown00);
    if (acc.isValid()) {
      table[index].unknown0e = 0;
      acc.setDisp(false);
    }
  }
}

void GfMenuObjOperationInfo::finalize() { GfMenuObject::finalize(); }

void GfMenuObjOperationInfo::open(u32 handle, u32 unknown0, u32 unknown1, u32 unknown2) { GF_MENU_REQUEST_EVENT4(unknown001, GfMenuTypes::unknown003_33, handle, unknown0, unknown1, unknown2); }

void GfMenuObjOperationInfo::update() { GfMenuObject::update(); }

void GfMenuObjOperationInfo::close() { GF_MENU_REQUEST_EVENT(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjOperationInfo::setDisp(bool isDisp) { unknown154(unknown001, isDisp); }

void GfMenuObjOperationInfo::setGuideText(u32 param0, u32 param1) { GF_MENU_REQUEST_EVENT2(unknown001, 0x101, param0, param1); }

void GfMenuObjOperationInfo::setGuideDisp(bool param0) { GF_MENU_REQUEST_EVENT1(unknown001, 0x106, param0); }

void GfMenuObjOperationInfo::add(u32 param0, u32 param1, u32 param2, u32 param3) { GF_MENU_REQUEST_EVENT4(unknown001, 0x102, param0, param1, param2, param3); }

void GfMenuObjOperationInfo::remove(u32 param0, u32 param1, u32 param2, u32 param3) { GF_MENU_REQUEST_EVENT4(unknown001, 0x103, param0, param1, param2, param3); }

void GfMenuObjOperationInfo::changeText(u32 param0, u32 param1, bool param2) { GF_MENU_REQUEST_EVENT3(unknown001, 0x104, param0, param1, param2); }

void GfMenuObjOperationInfo::changeText(u32 param0, u32 param1, u32 param2) { GF_MENU_REQUEST_EVENT3(unknown001, 0x104, param0, param1, param2); }

void GfMenuObjOperationInfo::setActionEnable(u32 param0, u32 param1, bool param2) { GF_MENU_REQUEST_EVENT3(unknown001, 0x105, param0, param1, param2); }

void GfMenuObjOperationInfo::moveGuide(u32 param0, bool param1) { GF_MENU_REQUEST_EVENT2(unknown001, 0x107, param0, param1); }

void GfMenuObjOperationInfo::fadeGuide(bool param0) { GF_MENU_REQUEST_EVENT1(unknown001, 0x108, param0); }

bool GfMenuObjOperationInfo::exchangeTextRemove(u32 layer, mm::mtl::FixedVector<InputObj, 16> &inputs, mm::mtl::FixedVector<DupItem, 16> &dups, u32 list, u32 action) {
  bool removed = false;
  for (InputObj *input = inputs.begin(); input != inputs.end(); input++) {
    if (input->unknown00 == layer) {
      InputObj::unknown001 *text = input->unknown08.begin();
      while (text != input->unknown08.end()) {
        if (text->unknown00 == action) {
          input->unknown08.erase(text);
          removed = true;
        } else {
          text++;
        }
      }
    }
  }
  if (removed) {
    setupList(list, inputs, dups);
    return true;
  }
  return false;
}

} // namespace gf
