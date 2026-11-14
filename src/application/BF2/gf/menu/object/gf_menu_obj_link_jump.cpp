#include "gf/menu/object/gf_menu_obj_link_jump.h"

#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_enemy_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h" // IWYU pragma: keep
#include "ui/ctrl/ui_ctrl_object.h"
#include "ui/ctrl/ui_ctrl_revolve_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x49;

GfMenuObjLinkJump::GfMenuObjLinkJump(u32 handle) : GfMenuObject(handle), unknown28(), unknown68(nullptr), unknown70(nullptr), unknown78(false) {}

GfMenuObjLinkJump::~GfMenuObjLinkJump() {
  for (int i = 0; i < 2; i++) {
    mm::mtl::safeRelease(unknown28[i].unknown18);
    mm::mtl::safeRelease(unknown28[i].unknown08);
    mm::mtl::safeRelease(unknown28[i].unknown10);
  }
  mm::mtl::safeRelease(unknown70);
  mm::mtl::safeRelease(unknown68);
}

void GfMenuObjLinkJump::finalize() {
  GfMenuReference::clearLinkList();
  GfMenuObject::finalize();
}

void GfMenuObjLinkJump::update() { GfMenuObject::update(); }

void GfMenuObjLinkJump::close() {}

void GfMenuObjLinkJump::initialize() {
  ui::UIObjectAcc root(unknown18, "LAY_root");
  if (root.isValid()) {
// __LINE__ must be 72 as in the original file: it is the line argument of operator new.
#line 72
    RootListener *rootListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) RootListener(this);
    rootListener->addRef();
    ui::UIEventManager::get()->registObjectListener(root.unknown10, rootListener);
    if (rootListener != nullptr) {
      rootListener->release();
    }
// __LINE__ must be 73 as in the original file: it is the line argument of operator new.
#line 73
    CategoryListener *categoryListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) CategoryListener(this);
    categoryListener->addRef();
    ui::UIEventManager::get()->registObjectListener(root.searchChild("LAY_category_list"), categoryListener);
    if (categoryListener != nullptr) {
      categoryListener->release();
    }
// __LINE__ must be 74 as in the original file: it is the line argument of operator new.
#line 74
    NotifyListener *notifyListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) NotifyListener(this);
    notifyListener->addRef();
    ui::UIEventManager::get()->registObjectListener(root.searchChild("LAY_notify"), notifyListener);
    if (notifyListener != nullptr) {
      notifyListener->release();
    }
    setupListObject(0);
    setupListObject(1);
    ui::UIObjectAcc(unknown18, "IMG_bg").setAlpha(0.5f);
    GfMenuObject::initialize();
  }
}
void GfMenuObjLinkJump::changeCategory(int index) {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    unknown68->setIndex(index);
    u32 selected = unknown68->getSelectObject();
    for (int i = 0; i < 2; i++) {
      if (unknown28[i].unknown08 != nullptr && unknown28[i].unknown00 == selected) {
        unknown28[i].unknown08->setIndex(0);
        setupInputSelectionFromList(main.unknown10, *unknown28[i].unknown08);
      }
    }
    migrateInput(main.unknown10, selected);
  }
}

void GfMenuObjLinkJump::listenerCategorySelect(const ui::EventData &event) {
  switch (ui::UICtrlObject::getEventType(event)) {
  case 2:
    if (unknown78) {
      ui::UIObjectAcc notify(unknown18, "LAY_notify");
      ui::EventData notifyEvent;
      notifyEvent.unknown00 = 0x22;
      sendEvent(notify.unknown10, notifyEvent, 0.0f);
    }
    break;
  case 3:
    if (!unknown78) {
      ui::UIObjectAcc notify(unknown18, "LAY_notify");
      ui::EventData notifyEvent;
      notifyEvent.unknown00 = 0x21;
      sendEvent(notify.unknown10, notifyEvent, 0.0f);
      ui::UIObjectAcc(unknown18).setDispChild(false, "LAY_main");
      ui::UIObjectAcc(unknown18).setDispChild(false, "IMG_bg");
    } else {
      ui::UIObjectAcc categoryList(unknown18, "LAY_category_list");
      if (categoryList.isValid()) {
        ui::UIObjectAcc main(unknown18, "LAY_main");
        if (main.isValid()) {
          enableInput(categoryList.unknown10);
          enableInput(main.unknown10);
        }
      }
    }
    break;
  }
}

void GfMenuObjLinkJump::setupListObject(u32 index) {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    ui::UIObjectAcc list(main.duplicateChild("LAY_list"));
    if (list.isValid()) {
      u32 handle = list.unknown10;
      list.setDisp(true);
      ui::UISelectObjList *objects;
      {
        ui::UISelectObjList::CreateParam param;
        param.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
        objects = ui::UISelectObjList::create(param);
      }
      if (objects != nullptr) {
        objects->pickupObject(list.unknown10, "TXT_item%02d", 1);
        objects->getSize();
      }
      ui::UICtrlCursorSelect *cursor;
      {
        ui::UICtrlCursorSelect::CursorSetting setting;
        setting.unknown18 = 4;
        cursor = ui::UICtrlCursorSelect::create(list.searchChild("IMG_cursor"), setting, objects);
      }
      ui::UIListInfoBase *info = nullptr;
      if (index == 0) {
        for (u32 i = 0; i < objects->getSize(); i++) {
          GfMenuCharDataAdapter::createFromEnemyList(objects->getObject(i), 2, GfMenuReference::getEnemyLinkList(), i, false);
        }
        info = GfMenuReference::getEnemyLinkList();
        info->addRef();
      } else if (index == 1) {
        for (u32 i = 0; i < objects->getSize(); i++) {
          GfMenuItemAdapter::createFromList(objects->getObject(i), 0, GfMenuReference::getItemLinkList(), i, false);
        }
        info = GfMenuReference::getItemLinkList();
        info->addRef();
      }
      {
        ui::UIObjectAcc scrollBar(list.searchChild("IMG_scroll_bar"));
        GfMenuObjUtil::createVScrollBarPlugin(scrollBar.unknown10, info, "IMG_scroll_base", true);
      }
      mm::mtl::FixStr<32> name;
      name.format("TXT_title%02d", index + 1);
      list.setDispChild(true, name.c_str());
      unknown28[index].unknown00 = handle;
      unknown28[index].unknown08 = info;
      unknown28[index].unknown10 = objects;
      unknown28[index].unknown18 = cursor;
// __LINE__ must be 680 as in the original file: it is the line argument of operator new.
#line 680
      ListListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this, &unknown28[index]);
      listener->addRef();
      ui::UIEventManager::get()->registObjectListener(list.unknown10, listener);
      if (listener != nullptr) {
        listener->release();
      }
    }
  }
}

void GfMenuObjLinkJump::open() { unknown143(unknown001, GfMenuTypes::unknown003_33); }

void GfMenuObjLinkJump::RootListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    ui::EventData sendData;
    sendData.unknown00 = GfMenuTypes::unknown003_33;
    GfMenuObject::sendEvent(acc.searchChild("LAY_notify"), sendData, 0.0f);
    unknown20->unknown78 = false;
    break;
  }
  case 8:
    if (event.unknown0c == 9 && !unknown20->unknown78) {
      ui::EventData sendData;
      sendData.unknown00 = GfMenuTypes::unknown003_33;
      GfMenuObject::sendEvent(acc.searchChild("LAY_category_list"), sendData, 0.0f);
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjLinkJump::NotifyListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    ui::UIObjectAcc button(acc.unknown10, "IMG_notify_btn");
    if (button.isValid()) {
      s16 icon = GfMenuObjUtil::getBtnIconNumber(8);
      if (icon != -1) {
        button.setImageIndex(GfMenuBdat::getIconImageIndex(icon));
      }
    }
    acc.setDisp(false);
    unknown0c = -1;
    break;
  }
  case GfMenuTypes::unknown003_33: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown00 = 2;
    param.unknown0d = true;
    param.unknown08 = unknown0c;
    unknown0c = GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  case GfMenuTypes::unknown003_34: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 1;
    param.unknown00 = 2;
    param.unknown0d = true;
    param.unknown08 = unknown0c;
    unknown0c = GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjLinkJump::ListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
  case 0x21:
    break;
  case 6: {
    u32 index = event.unknown08;
    unknown28->unknown08->setIndex(index);
    unknown28->unknown10->setIndex(unknown28->unknown08->getIndex(true));
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}
} // namespace gf
