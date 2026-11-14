#include "gf/menu/object/gf_menu_obj_common_jog.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_object.h"
#include "ui/ctrl/ui_ctrl_revolve_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: call id; original name unknown.
constexpr u32 unknown001 = 0x4a;

GfMenuObjCommonJog::GfMenuObjCommonJog(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(0), unknown48(nullptr), unknown50(nullptr), unknown58(0), unknown5c(false), unknown5e(0),
      unknown60(0), unknown64(-1) {}

GfMenuObjCommonJog::~GfMenuObjCommonJog() { ; }

void GfMenuObjCommonJog::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
#line 74
    MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
    if (listener != nullptr) {
      listener->release();
    }
    attachExternalCall(unknown001, main.unknown10);
    main.setDisp(false);
    disableInput(main.unknown10);
    ui::UISelectObjList::CreateParam param;
    param.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
    unknown28 = ui::UISelectObjList::create(param);
    unknown30 = ui::UISelectObjList::create(param);
    GfMenuObject::initialize();
  }
}

void GfMenuObjCommonJog::finalize() {
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  GfMenuObject::finalize();
}

void GfMenuObjCommonJog::update() { GfMenuObject::update(); }

void GfMenuObjCommonJog::open(GfMenuCallContext *context, const OpenParam &param) {
  ui::UIObjectAcc acc(getAttachedObject(unknown001));
  if (acc.isValid() && GfMenuObjUtil::checkCCStart(context)) {
    ui::EventData event;
    event.unknown00 = 0x21;
    event.unknown08 = param.unknown00;
    event.unknown0c = param.unknown04;
    sendEvent(acc.unknown10, event, 0.0f);
    if (context != nullptr) {
      startCallContext(context, unknown001, acc.unknown10);
    }
  }
}

void GfMenuObjCommonJog::close(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown00 = 0x22;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjCommonJog::disable(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown00 = 0x102;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjCommonJog::enable(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown00 = 0x101;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjCommonJog::pop(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown00 = 0x103;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjCommonJog::startJogChange(u16 menu, int select) {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  unknown60 = menu;
  unknown64 = select;
  ui::EventData event;
  event.unknown00 = 0x22;
  sendEvent(main.unknown10, event, 0.0f);
  addResultCallContext(main.unknown10, 4, static_cast<u16>(unknown68.size()));
}

void GfMenuObjCommonJog::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    u32 object = unknown20->unknown28->getSelectObject();
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x80000;
    param.unknown00 = 0.25f;
    param.unknown2c = 1.0f;
    GfMenuObjUtil::startCtrl(object, param, nullptr);
    unknown20->unknown5c = false;
    break;
  }
  case 6: {
    u32 index = event.unknown08;
    int previous = event.unknown0c;
    unknown20->unknown40 = unknown20->unknown28->getSelectObject();
    unknown20->unknown28->setIndex(index);
    if (previous != -1) {
      bool isUp;
      if (previous < static_cast<int>(index)) {
        if (previous == 0 && index == unknown20->unknown28->getSize() - 1) {
          isUp = true;
        } else {
          isUp = false;
        }
      } else if (index == 0) {
        isUp = previous != static_cast<int>(unknown20->unknown28->getSize()) - 1;
      } else {
        isUp = true;
      }
      GfMenuObjUtil::CtrlParam param;
      param.unknown20 = 0x20;
      param.unknown00 = 0.25f;
      param.unknown0c = 3;
      if (isUp) {
        param.unknown08 = 0x20;
        u32 ring = acc.searchChild("IMG_ring_roll_up");
        acc.setLayout(ring, "roll_up");
        GfMenuObjUtil::startCtrl(ring, param, nullptr);
      } else {
        param.unknown08 = 0x40;
        u32 ring = acc.searchChild("IMG_ring_roll_down");
        acc.setLayout(ring, "roll_down");
        GfMenuObjUtil::startCtrl(ring, param, nullptr);
      }
    }
    ui::UIObjectAcc text(acc.unknown10, "TXT_item");
    if (unknown20->unknown48 != nullptr) {
      int top = Bdat::getIdTop(unknown20->unknown48);
      u32 textId = Bdat::getVal(unknown20->unknown48, "txt", top + index).valueU16;
      ui::UIStr str(GfDataBdat::getFP(BDAT_MENU_JOG_MS), textId);
      text.setText(str);
    }
    text.setDisp(false);
    break;
  }
  case 0x21:
    if (!unknown20->unknown5c) {
      u64 param = event.unknown08_u64;
      if (unknown20->setup(param, param >> 32)) {
        unknown20->unknown38->moveCenterOffset(mm::Pnt<s16>(0, 0), true);
        unknown20->unknown5e = param;
        unknown20->unknown5c = true;
      }
    }
    break;
  case 0x22:
    if (unknown20->unknown5c && unknown20->unknown38 != nullptr) {
      ui::UIObjectAcc(acc.unknown10, "TXT_item").setDisp(false);
      unknown20->unknown38->moveCenterOffset(mm::Pnt<s16>(unknown20->unknown58, 0), true);
      unknown20->unknown5c = false;
    }
    break;
  case 8: {
    u32 index = event.unknown08;
    u16 input = event.unknown0c_u16;
    if (input == 1) {
      if (!ui::UIObjectAcc(unknown20->unknown28->getSelectObject(), "IMG_item_icon").isDisp()) {
        GfMenuObjUtil::playSECommon(2);
      } else {
        u16 menu = Bdat::getVal(unknown20->unknown48, "fs_menu_id", (index & 0xffff) + 1).valueU16;
        if (menu != 0) {
          u16 next = Bdat::getVal(unknown20->unknown50, "next_jog", menu).valueU16;
          if (next == 0) {
            u16 layer = Bdat::getVal(unknown20->unknown50, "layer_id", menu).valueU16;
            if (layer != 0) {
              GfMenuObject::addResultCallContext(acc.unknown10, 3, layer);
            }
          } else {
            unknown20->startJogChange(next, -1);
          }
        }
        GfMenuObject::addResultCallContext(acc.unknown10, 2, index & 0xffff);
      }
    }
    GfMenuObjUtil::playSECommonFromInput(input);
    break;
  }
  case 0xe:
    if (ui::UICtrlObject::getEventCtrlObjID(event) == 1) {
      unknown20->listenerItemRevlover(event);
    }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 0x101:
    GfMenuObject::enableInput(acc.unknown10);
    break;
  case 0x102:
    GfMenuObject::disableInput(acc.unknown10);
    break;
  case 0x103:
    if (!unknown20->unknown68.empty()) {
      const GfMenuObjCommonJog::unknown002 &last = unknown20->unknown68.back();
      unknown20->startJogChange(last.unknown00, last.unknown02);
    }
    break;
  }
}

} // namespace gf
