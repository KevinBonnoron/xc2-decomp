#include "gf/menu/object/gf_menu_obj_item_list2.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/menu/gf_menu_item_util.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

GfMenuObjItemList2::GfMenuObjItemList2(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown98(0), unknowna0(true) {}

GfMenuObjItemList2::~GfMenuObjItemList2() {
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
}

void GfMenuObjItemList2::refreshItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *selectList) {
  if (list != nullptr && selectList != nullptr) {
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < selectList->getSize(); i++) {
      MenuItemInfo &info = list->getContents(list->getPageIndex(i));
      name.format("IMG_tagsellect@%02d", i + 1);
      GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), list->getIndex(true) == i);
      name.format("LAY_stock@%02d", i + 1);
      GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), GfMenuItemUtil::canCountStack(info.unknown00));
    }
  }
}

void GfMenuObjItemList2::setupFilter(ui::UIObjectAcc &acc, u32 index) {
  ui::UIStr text;
  getFilterText(index, text);
  ui::UIObjectAcc label(acc.searchChild("TXT_filterlabel"));
  label.setText(text);
}

void GfMenuObjItemList2::getFilterText(u32 index, ui::UIStr &text) {
  text.copy(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_FILTER_CATEGORY), GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_ITEM_LIST_FILTER, index + 1)));
}

void GfMenuObjItemList2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjItemList2::update() { GfMenuObject::update(); }

void GfMenuObjItemList2::setFadeOutSub(u32 handle) { GfMenuObjUtil::setCommonFadeOut(handle, 2, 0); }

void GfMenuObjItemList2::sendEvent(u32 handle, u32 type, u32 param, u32 delay) {
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = type;
  ui::UIManager::get()->requestObjectEvent(handle, event, static_cast<f32>(delay) * 0.033333335f);
}

int GfMenuObjItemList2::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjItemList2::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

} // namespace gf
