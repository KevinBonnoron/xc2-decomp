#include "gf/menu/object/gf_menu_obj_item_list.h"

#include "gf/data/gf_data_item.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/gf_menu_reference_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/ctrl/ui_ctrl_slide_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjItemList::GfMenuObjItemList(u32 handle) : GfMenuObject(handle) {}

GfMenuObjItemList::~GfMenuObjItemList() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  for (int i = 0; i < 21; i++) {
    mm::mtl::safeRelease(unknown48[i]);
  }
  unknownf0 = nullptr;
}

void GfMenuObjItemList::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
// __LINE__ must be 63 as in the original file: it is the line argument of operator new.
#line 63
    MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
    mainListener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.unknown10, mainListener);
    if (mainListener != nullptr) {
      mainListener->release();
    }
    unknownf0 = GfMenuReferenceList<GfMenuItemList>::unknown002();
    {
      ui::UIObjectAcc list(main.unknown10, "LAY_item_list");
// __LINE__ must be 72 as in the original file: it is the line argument of operator new.
#line 72
      ListListener *listListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
      listListener->addRef();
      ui::UIEventManager::get()->registObjectListener(list.unknown10, listListener);
      if (listListener != nullptr) {
        listListener->release();
      }
      mm::mtl::FixStr<32> name;
      ui::UISelectObjList::CreateParam createParam = {};
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      unknown28 = ui::UISelectObjList::create(createParam);
      if (unknown28 != nullptr) {
        unknown28->pickupObject(list.unknown10, "LAY_item@%02d", 1);
        for (u32 i = 0; i < unknown28->getSize(); i++) {
          name.format("TXT_item_name@%02d", i + 1);
          GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromRefernceList(list.searchChild(name.c_str()), 0, unknownf0, i, false);
          adapter->unknown24 = unknown28->getObject(i);
          name.format("TXT_item_num@%02d", i + 1);
          GfMenuItemAdapter::createFromRefernceList(list.searchChild(name.c_str()), 3, unknownf0, i, false);
        }
        ui::UICtrlCursorSelect::CursorSetting setting;
        setting.unknown18 = 1;
        setting.setType(0);
        setting.unknown1a = -8;
        unknown30 = ui::UICtrlCursorSelect::create(list.searchChild("IMG_item_cursor"), setting, unknown28);
      }
    }
    {
      ui::UIObjectAcc category(main.unknown10, "LAY_item_category");
// __LINE__ must be 111 as in the original file: it is the line argument of operator new.
#line 111
      TypeListener *typeListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) TypeListener(this);
      typeListener->addRef();
      ui::UIEventManager::get()->registObjectListener(category.unknown10, typeListener);
      if (typeListener != nullptr) {
        typeListener->release();
      }
      GfMenuObject::setupInputSelection(category.unknown10, 0, 20);
      ui::UISelectObjList::CreateParam createParam;
      createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
      unknown38 = ui::UISelectObjList::create(createParam);
      if (unknown38 != nullptr) {
        ui::UICtrlSlideSelect::SlideSetting setting;
        for (u32 i = 0; i < 20; i++) {
          ui::UIObjectAcc icon(category.duplicateChild("IMG_item_cate_icon"));
          icon.setImageIndex((i + 18) % 20);
          icon.setDisp(true);
          unknown38->addObject(icon.unknown10);
          if (i == 0) {
            icon.getPosCenter(setting.unknown0c);
            s16 width;
            s16 height;
            icon.getSize(true, width, height);
            setting.unknown10.x = width + 8;
            setting.unknown10.y = 0;
          }
        }
        setting.unknown08 = 5;
        setting.unknown00 = 0.25f;
        unknown40 = ui::UICtrlSlideSelect::create(category.unknown10, setting, unknown38);
      }
    }
    GfMenuItemList::ItemBoxSetup setup;
    setup.unknown00.unknown08 = unknown28->getSize();
    for (int i = 0; i < 21; i++) {
      GfMenuItemList *list = GfMenuItemList::create();
      setup.unknown14 = static_cast<ItemType::Type>(i + 1);
      list->setupFromBox(setup);
      unknown48[i] = list;
    }
    unknownf0->unknown001(unknown48[0]);
    GfMenuObject::initialize();
  }
}

void GfMenuObjItemList::finalize() { GfMenuObject::finalize(); }

void GfMenuObjItemList::update() { GfMenuObject::update(); }

void GfMenuObjItemList::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    GfMenuObject::disableInput(acc.searchChild("LAY_item_category"));
    GfMenuObject::disableInput(acc.searchChild("LAY_item_list"));
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    param.unknown04 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  case 2: {
    GfMenuObject::disableInput(acc.searchChild("LAY_item_category"));
    GfMenuObject::disableInput(acc.searchChild("LAY_item_list"));
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = 0.25f;
    param.unknown04 = 2;
    param.unknown14 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.searchChild("LAY_item_category"));
      GfMenuObject::enableInput(acc.searchChild("LAY_item_list"));
    }
    break;
  case 8:
    if (event.unknown0c == 2) {
      GfMenuObject::returnFSSubLayer(acc.unknown10, 1);
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjItemList::ListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case 6: {
    u32 index = event.unknown08;
    unknown20->unknown28->setIndex(index);
    break;
  }
  case 0x100:
    if (unknown20->unknownf0->unknown10->getSize() == 0) {
      GfMenuObject::disableInput(acc.unknown10);
      acc.setDispChild(false, "IMG_item_cursor");
    } else {
      GfMenuObject::enableInput(acc.unknown10);
      acc.setDispChild(true, "IMG_item_cursor");
      GfMenuObject::setupInputSelectionFromList(acc.unknown10, *unknown20->unknownf0->unknown10);
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template class gf::GfMenuReferenceList<gf::GfMenuItemList>;
