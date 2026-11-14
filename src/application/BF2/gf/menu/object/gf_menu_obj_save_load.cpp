#include "gf/menu/object/gf_menu_obj_save_load.h"

#include "gf/data/gf_data_save.h"
#include "gf/game/gf_game_save.h"
#include "gf/gf_allocator.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/fixstr.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/input/ui_input_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjSaveLoad::GfMenuObjSaveLoad(u32 handle) : GfMenuObject(handle), unknown24(0) {}

GfMenuObjSaveLoad::~GfMenuObjSaveLoad() { ; }

void GfMenuObjSaveLoad::initialize() {
  ui::UIObjectAcc acc(unknown18);
  {
    ui::UIObjectAcc main(acc.unknown10, "LAY_main");
    if (main.isValid()) {
// __LINE__ must be 52 as in the original file: it is the line argument of operator new.
#line 52
      ListListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
      listener->addRef();
      ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
      if (listener != nullptr) {
        listener->release();
      }
      setupInputSelection(main.unknown10, 0, 10);
    }
  }
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 10; i++) {
    name.format("TXT_slot%d", i);
    ui::UIObjectAcc slot(acc.unknown10, name.c_str());
    if (slot.isValid()) {
      mm::mtl::FixStr<32> text;
      text.format("save %d", i);
      slot.applyText(text.c_str());
    }
  }
  ui::UIInputManager *inputManager = ui::UIInputManager::get();
  inputManager->unknown20 = acc.getDispPriority();
  GfMenuObjOperationInfo::setDisp(false);
  GfMenuObject::initialize();
}

void GfMenuObjSaveLoad::finalize() { GfMenuObject::finalize(); }

void GfMenuObjSaveLoad::update() { GfMenuObject::update(); }

void GfMenuObjSaveLoad::ListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    acc.setDispChild(false, "IMG_cursor");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.5f;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown14 = 1;
    param.unknown00 = 0.5f;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    GfMenuObjOperationInfo::setDisp(true);
    break;
  }
  case 8: {
    u64 param = event.unknown08_u64;
    GfMenuObjUtil::playSECommonFromInput(param >> 32);
    u32 type = (param >> 32) & 0xffff;
    if (type != 2) {
      if (type == 1) {
        u32 slot = param & 0xffff;
        GfGameSave save(static_cast<SAVESLOT>(slot));
        save.execGameSaveBlockForDebug();
        mm::mtl::FixStr<32> name;
        name.format("TXT_slot%d", slot);
        ui::UIObjectAcc slotAcc(acc.unknown10, name.c_str());
        if (slotAcc.isValid()) {
          slotAcc.setAddColor("cyan");
          slotAcc.setScale(mm::Vec2(1.5f, 1.5f));
        }
        registTimer(acc.unknown10, 0, 1.0f, false);
        disableInput(acc.unknown10);
      }
      break;
    }
  }
  case 0xb:
    returnFSSubLayer(unknown20);
    break;
  case 6: {
    u32 index = event.unknown08;
    ui::UIObjectAcc cursor(acc.unknown10, "IMG_cursor");
    if (!cursor.isValid()) {
      break;
    }
    if (index == 0xffffffff) {
      cursor.setDisp(false);
    } else {
      cursor.setDisp(true);
      mm::mtl::FixStr<32> name;
      name.format("TXT_slot%d", index);
      ui::UIObjectAcc slot(acc.unknown10, name.c_str());
      if (slot.isValid()) {
        GfMenuObjUtil::setDockPos(cursor.unknown10, slot.unknown10, 1, true);
        GfMenuObjUtil::addPos(cursor.unknown10, -16, 0);
      }
    }
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
