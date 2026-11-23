#include "gf/menu/object/gf_menu_obj_operation_info.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
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

bool GfMenuObjOperationInfo::setupIconTable(mm::mtl::FixedVector<DupItem, 16> &table, u32 index, u32 key, u32 value, u32 isSecond) {
  if (index >= table.size()) {
    return false;
  }

  for (u32 i = 0; i < index; i++) {
    if (table[i].unknown04 == key && table[i].unknown0e) {
      return false;
    }
  }

  table[index].unknown04 = key;
  table[index].unknown08 = value;
  // The game picks the column name (csel) before the call of getFP; written inside the getVal call the function has 132 instructions instead of 133.
  const char *order = isSecond == 0 ? "order" : "order2";
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_KEY_ORDER);
  u16 sortKey = 0;
  for (int id = Bdat::getIdTop(bdat); id <= Bdat::getIdEnd(bdat); id++) {
    if (Bdat::getVal(bdat, "key", id).valueU16 == key) {
      sortKey = Bdat::getVal(bdat, order, id).valueU16;
      break;
    }
  }
  table[index].unknown0c = sortKey;
  table[index].unknown0e = 1;
  return true;
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
