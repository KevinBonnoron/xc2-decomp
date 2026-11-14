#include "gf/menu/object/gf_menu_obj_cylinder_select.h"

#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_item.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/list/gf_menu_sort_type.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/util/gf_item_util.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x46;
// Inferred role: active adapter category; original name unknown.
constexpr u32 unknown002 = 2;
// Inferred role: common text window opened when the list is empty; original name unknown.
constexpr u32 unknown003 = 0x47;

GfMenuObjCylinderSelect::GfMenuObjCylinderSelect(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr) {
  unknown40 = GfMenuCallContext::create();
}

GfMenuObjCylinderSelect::~GfMenuObjCylinderSelect() {
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
}

void GfMenuObjCylinderSelect::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCylinderSelect::update() { GfMenuObject::update(); }

void GfMenuObjCylinderSelect::open(GfMenuCallContext *context, u32 cylinder) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && GfMenuObjUtil::checkCCStart(context)) {
    ui::EventData event;
    event.unknown08 = cylinder;
    event.unknown0c = 0;
    event.unknown00 = GfMenuTypes::unknown003_33;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
    GfMenuObject::startCallContext(context, unknown001, acc.unknown10);
    acc.setSuspend(false);
    GfMenuAdapterManager::addActiveCategory(unknown002);
  }
}

void GfMenuObjCylinderSelect::close(GfMenuCallContext *context) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (!GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
    GfMenuAdapterManager::delActiveCategory(unknown002);
  }
}

void GfMenuObjCylinderSelect::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    acc.setDisp(false);
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::resetInputSelection(acc.unknown10);
      GfMenuObject::setupInputSelectionFromList(acc.unknown10, *unknown20->unknown28);
      GfMenuObject::enableInput(acc.unknown10);
    } else if (event.unknown08 == 2) {
      GfMenuObject::termCallContext(acc.unknown10);
      acc.setSuspend(true);
    }
    return;
  case 6: {
    u32 index = event.unknown08;
    if (index != 0xffffffff) {
      u32 previous = event.unknown0c;
      unknown20->unknown28->setIndex(index);
      unknown20->unknown30->setIndex(index);
      if (previous != 0xffffffff && index != previous) {
        GfMenuObjUtil::playSECommonCursor();
      }
      unknown20->unknown38->setDisp(true);
    }
    return;
  }
  case 8: {
    if (event.unknown0c == 1) {
      GfMenuObject::addResultCallContext(acc.unknown10, unknown20->unknown28->getContents(unknown20->unknown28->getIndex(false)).unknown04, 0);
      GfMenuObjUtil::playSECommonDecide();
    } else if (event.unknown0c == 2) {
      GfMenuObject::addResultCallContext(acc.unknown10, 0, 1);
      GfMenuObjUtil::playSECommonCancel();
    } else {
      return;
    }
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown04 = 1;
    param.unknown00 = 6;
    param.unknown10 = 2;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    GfMenuObject::disableInput(acc.unknown10);
    return;
  }
  case GfMenuTypes::unknown003_33: {
    u32 item = event.unknown08;
    GfMenuItemList::ItemBoxSetup setup;
    GfDataBdat::getFP(BDAT_ITM_SALVAGE_LIST);
    setup.unknown00.unknown08 = 10;
    setup.unknown00.unknown10 = true;
    setup.unknown14 = ItemType::ITEM_TYPE_UNKNOWN_5;
    unknown20->unknown28->setupFromBox(setup);
    if (unknown20->unknown28->getSize() == 0) {
      unknown20->unknown40->reset();
      GfMenuObjCommonText::open(unknown20->unknown40, unknown003, 0);
      GfMenuObject::setCallContextEventHandler(unknown20->unknown40, acc.unknown10);
    } else {
      u32 i = 0;
      while (i < unknown20->unknown28->getSize()) {
        MenuItemInfo info = unknown20->unknown28->getContents(i);
        ItemProperty property;
        GfItemUtil::getProperty(property, info.unknown04, 0);
        if (property.unknown00.test(ItemProperty::FLAG_UNKNOWN_4) && info.unknown04 != item) {
          unknown20->unknown28->decItem(info, false);
        } else {
          i++;
        }
      }
      unknown20->unknown28->sort(unknown093_13, true);
      GfMenuObjUtil::unknown002(acc.unknown10);
    }
    unknown20->unknown38->setDisp(false);
    break;
  }
  case 0x42:
    GfMenuObject::addResultCallContext(acc.unknown10, 0, 1);
    GfMenuObject::termCallContext(acc.unknown10);
    acc.setSuspend(true);
    return;
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

} // namespace gf
