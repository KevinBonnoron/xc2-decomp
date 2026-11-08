#include "gf/menu/object/gf_menu_obj_ev_theater.h"

#include "bdat.h"
#include "gf/gf_allocator.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_msg_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id; original name unknown.
constexpr u32 unknown001 = 0x19;

// Inferred role: off screen call id; original name unknown.
constexpr u32 unknown002 = 0x1a;

GfMenuObjEvTheater::GfMenuObjEvTheater(u32 handle) : GfMenuObject(handle), unknown24(1), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr) {
  unknown28 = GfMenuMsgList::create();
  unknown38 = GfMenuIDList::create();
}

GfMenuObjEvTheater::~GfMenuObjEvTheater() {
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown38);
}

void GfMenuObjEvTheater::finalize() { GfMenuObject::finalize(); }

void GfMenuObjEvTheater::update() { GfMenuObject::update(); }

void GfMenuObjEvTheater::refreshSelctList() {
  u32 index = unknown38->getIndex(true);
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < unknown40->getSize(); i++) {
    name.format("IMG_select_frame@%02d", i + 1);
    ui::UIObjectAcc frame(unknown40->getObject(i), name.c_str());
    frame.startAnimation(index == i ? "select" : "non", false);
  }
}

void GfMenuObjEvTheater::updateSubMsgList() {
  if (unknown28 != nullptr) {
    switch (unknown24) {
    case 1: {
      unknown28->setBdat(0x127, 0x102);
      u8 *bdat = unknown28->unknown68;
      {
        ui::UIListInfoBase::SetupParam param;
        param.unknown08 = unknown30->getSize();
        unknown28->setup(getAllocator(ALLOCATOR_DEFAULT), param);
      }
      for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
        MsgID id = {};
        id.unknown00 = Bdat::getIdTop(bdat) + i;
        unknown28->addContents(id);
      }
      break;
    }
    case 2: {
      unknown28->setBdat(0x126, 0x102);
      u8 *bdat = unknown28->unknown68;
      {
        ui::UIListInfoBase::SetupParam param;
        param.unknown08 = unknown30->getSize();
        unknown28->setup(getAllocator(ALLOCATOR_DEFAULT), param);
      }
      for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
        MsgID id = {};
        id.unknown00 = Bdat::getIdTop(bdat) + i;
        unknown28->addContents(id);
      }
      break;
    }
    }
    unknown28->setIndex(0);
  }
}

bool GfMenuObjEvTheater::attach(GfMenuCallContext *context) { return unknown151(context, unknown001); }

void GfMenuObjEvTheater::fadein(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown00 = 0x102;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjEvTheater::fadeout(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown00 = 0x101;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjEvTheater::dispOffScreen(bool isDisp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = isDisp ? GfMenuTypes::unknown003_33 : GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjEvTheater::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    ui::UIObjectAcc bg(acc.unknown10, "IMG_bg");
    bg.startAnimation("start", false);
    GfMenuObject::hookAnimationEvent(acc.unknown10, bg.unknown10);
    break;
  }
  case 2:
    GfMenuObject::termCallContext(acc.unknown10);
    acc.setTerm();
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(2);
    }
    break;
  case 0xc: {
    ui::UIObjectAcc bg(acc.unknown10, "IMG_bg");
    bg.startAnimation("loop", false);
    break;
  }
  case 0x100: {
    u32 result = event.unknown08;
    GfMenuObject::addResultCallContext(acc.unknown10, result, 0);
    break;
  }
  case GfMenuTypes::unknown003_257: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 1;
    param.unknown10 = 3;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  case GfMenuTypes::unknown003_258: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 0;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    if (unknown20->unknown24 == 3) {
      ui::UIObjectAcc view(acc.searchSibiling("LAY_mdl_view"));
      view.setDisp(false);
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
