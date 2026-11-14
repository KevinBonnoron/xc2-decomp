#include "gf/menu/object/gf_menu_obj_sort.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x83;

GfMenuObjSort::GfMenuObjSort(u32 handle) : GfMenuObject(handle), unknown24(0), unknown28(0), unknown2c(0), unknown30(0) {}

GfMenuObjSort::~GfMenuObjSort() { ; }

void GfMenuObjSort::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  attachExternalCall(unknown001, main.unknown10);
// __LINE__ must be 51 as in the original file: it is the line argument of operator new.
#line 51
  MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
  if (listener != nullptr) {
    listener->release();
  }
  {
    ui::UIObjectAcc list(main.unknown10, "LAY_list");
    ui::UIObjectAcc name(main.unknown10, "TXT_cur_name");
    GfMenuObjUtil::createDockPlugin(list.unknown10, name.unknown10, 3, mm::Pnt<s16>(0, 16), 0);
  }
  {
    ui::UIObjectAcc list(main.unknown10, "LAY_list");
    ui::UIObjectAcc base(main.unknown10, "IMG_base");
    GfMenuObjUtil::createFitPlugin(base.unknown10, list.unknown10, 16, 16, GfMenuObjUtil::FitOption());
  }
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SORT_TABLE);
  if (bdat != nullptr) {
    mm::mtl::FixStr<32> name;
    for (unknown30 = 0;; unknown30++) {
      name.format("sort_type%d", unknown30 + 1);
      if (Bdat::getMember(bdat, name.c_str()) == nullptr) {
        break;
      }
    }
  }
  GfMenuObject::initialize();
}

void GfMenuObjSort::finalize() { GfMenuObject::finalize(); }

void GfMenuObjSort::update() {
  if (unknown24 != 0) {
    ui::UIObjectAcc acc(unknown24);
    if (!acc.isValid() || acc.isTerm()) {
      unknown155(unknown001, GfMenuTypes::unknown003_34);
    }
  }
  GfMenuObject::update();
}

void GfMenuObjSort::close() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjSort::open(u32 object, u32 label, u16 type, u16 index) {
  ui::UIObjectAcc acc(getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = 0x21;
    event.unknown08 = object;
    event.unknown0c = label;
    event.unknown10_u16 = type;
    event.unknown12 = index;
    sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjSort::refreshItem(u32 selected, u32 count) {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < count; i++) {
    name.format("TXT_list_name@%02d", i + 1);
    ui::UIObjectAcc(main.unknown10, name.c_str()).setAlpha(selected == i ? 0.0f : 1.0f);
    name.format("TXT_list_select@%02d", i + 1);
    ui::UIObjectAcc(main.unknown10, name.c_str()).setAlpha(selected == i ? 1.0f : 0.0f);
  }
}

u16 GfMenuObjSort::getSortID(u16 id, u16 index) {
  u32 sortID = 0;
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SORT_TABLE);
  if (GfMenuBdat::isValidBdatID(bdat, id)) {
    mm::mtl::FixStr<32> name;
    name.format("sort_type%d", index + 1);
    if (Bdat::getMember(bdat, name.c_str()) != nullptr) {
      sortID = Bdat::getVal(bdat, name.c_str(), id).valueU32;
    }
  }
  return sortID;
}

void GfMenuObjSort::setSortLabelText(u16 id, u32 handle) {
  ui::UIObjectAcc acc(handle);
  if (GfMenuBdat::isValidBdatID(GfDataBdat::getFP(BDAT_MNU_MSG_ITEM_SORT), id)) {
    u16 textId = GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_ITEM_SORT, id);
    acc.setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_SORT_CATEGORY), textId));
  }
}

void GfMenuObjSort::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown0c = 0;
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
    }
    break;
  case 6: {
    u32 index = event.unknown08;
    if (index != 0xffffffff) {
      u32 previous = event.unknown0c;
      unknown20->refreshItem(index, unknown0c);
      if (previous != 0xffffffff && index != previous) {
        GfMenuObjUtil::playSECommonCursor();
      }
    }
    break;
  }
  case GfMenuTypes::unknown003_33: {
    u32 object = event.unknown08;
    u32 labelObject = event.unknown0c;
    u32 table = event.unknown10;
    u32 selectedIndex = table >> 16;
    ui::UIObjectAcc label(labelObject);
    {
      ui::UIObjectAcc name(acc.unknown10, "TXT_cur_name");
      ui::UIStr text;
      label.getText(text);
      name.setText(text);
    }
    {
      ui::UIObjectAcc name(acc.unknown10, "TXT_cur_name");
      mm::Rect<s16> rect;
      label.getRect(rect, ui::UIObjectAcc::RECT_GLOBAL | ui::UIObjectAcc::RECT_SCALED);
      mm::Pnt<s16> center(rect.x + rect.width / 2, rect.y + rect.height / 2);
      name.setPosCenter(center);
    }
    {
      ui::UIObjectAcc cursor(acc.unknown10, "LAY_cur");
      cursor.setAlpha(1.0f);
    }
    u32 count = 0;
    {
      // The game calls getFP here and discards the result.
      GfDataBdat::getFP(BDAT_MNU_SORT_TABLE);
      mm::mtl::FixStr<32> name;
      for (u32 i = 0; i < unknown20->unknown30; i++) {
        u16 sortID = getSortID(table, i);
        bool isListed = sortID != 0;
        name.format("LAY_list_item@%02d", i + 1);
        ui::UIObjectAcc item(acc.unknown10, name.c_str());
        item.setDisp(isListed);
        if (isListed) {
          name.format("TXT_list_name@%02d", i + 1);
          setSortLabelText(sortID, acc.searchChild(name.c_str()));
          name.format("TXT_list_select@%02d", i + 1);
          setSortLabelText(sortID, acc.searchChild(name.c_str()));
          count++;
        }
      }
    }
    if (selectedIndex >= count) {
      selectedIndex = count - 1;
    }
    label.setDisp(false);
    int ctrl = GfMenuObjUtil::getCtrlID(acc.unknown10);
    if (ctrl != -1) {
      GfMenuObjUtil::stopCtrl(ctrl);
    }
    acc.setDisp(true);
    acc.setAlpha(1.0f);
    ui::UIObjectAcc list(acc.unknown10, "LAY_list");
    ui::UIObjectAcc base(acc.unknown10, "IMG_base");
    list.setAlpha(1.0f);
    base.setAlpha(1.0f);
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.2f;
    param.unknown04 = 1;
    GfMenuObjUtil::startCtrl(list.unknown10, param, nullptr);
    ctrl = GfMenuObjUtil::startCtrl(base.unknown10, param, nullptr);
    if (ctrl == -1) {
      GfMenuObject::enableInput(acc.unknown10);
    } else {
      GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
    }
    unknown20->unknown24 = object;
    unknown20->unknown28 = labelObject;
    unknown20->unknown2c = table & 0xffff;
    unknown0c = count;
    unknown10 = selectedIndex & 0xffff;
    GfMenuObject::resetInputSelection(acc.unknown10);
    GfMenuObject::setupInputSelection(acc.unknown10, unknown10, unknown0c);
    unknown20->refreshItem(selectedIndex & 0xffff, unknown0c);
    GfMenuObjOperationInfo::add(handle, 0, 0, 0);
    GfMenuObjUtil::playSECommonSort();
    break;
  }
  case GfMenuTypes::unknown003_34: {
    {
      ui::UIObjectAcc base(acc.unknown10, "IMG_base");
      int ctrl = GfMenuObjUtil::getCtrlID(base.unknown10);
      if (ctrl != 0) {
        GfMenuObjUtil::stopCtrl(ctrl);
      }
    }
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = 0.2f;
    param.unknown04 = 2;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    GfMenuObject::disableInput(acc.unknown10);
    unknown20->unknown24 = 0;
    unknown20->unknown28 = 0;
    unknown20->unknown2c = 0;
    GfMenuObjOperationInfo::remove(handle, 0, 0, 0);
    break;
  }
  case 8: {
    u32 index = event.unknown08;
    int type = event.unknown0c;
    ui::UIObjectAcc label(unknown20->unknown28);
    if (type == 1) {
      if (unknown10 != index) {
        setSortLabelText(getSortID(unknown20->unknown2c, index), label.unknown10);
      }
      GfMenuObjUtil::playSECommonDecide();
    } else if (type == 2) {
      index = unknown10;
      GfMenuObjUtil::playSECommonCancel();
    } else {
      break;
    }
    ui::EventData selected;
    selected.unknown08 = index;
    selected.unknown0c = 0;
    selected.unknown00 = 0x148;
    GfMenuObject::sendEvent(unknown20->unknown24, selected, 0.0f);
    {
      ui::UIObjectAcc cursor(acc.unknown10, "LAY_cur");
      cursor.setAlpha(0.0f);
      label.setDisp(true);
    }
    unknown155(unknown001, GfMenuTypes::unknown003_34);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
