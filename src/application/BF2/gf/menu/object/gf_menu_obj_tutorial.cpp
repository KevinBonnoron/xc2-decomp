#include "gf/menu/object/gf_menu_obj_tutorial.h"

#include "gf/gf_allocator.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/sound/gf_sound.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x7a;

// Inferred role: call context of the tutorial telop; original name unknown.
static GfMenuCallContext *unknown002;

GfMenuObjTutorial::GfMenuObjTutorial(u32 handle) : GfMenuObject(handle), unknown28(this), unknown2bc(0) {
  unknown002 = GfMenuCallContext::create();
  unknown002->reset();
}

GfMenuObjTutorial::~GfMenuObjTutorial() { mm::mtl::safeRelease(unknown002); }

bool GfMenuObjTutorial::isWaiting() { return unknown002 != nullptr && unknown002->isActive(); }

void GfMenuObjTutorial::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    attachExternalCall(unknown001, main.unknown10);
// __LINE__ must be 239 as in the original file: it is the line argument of operator new.
#line 239
    MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
    if (listener != nullptr) {
      listener->release();
    }
    GfMenuObject::initialize();
  }
}

void GfMenuObjTutorial::finalize() { GfMenuObject::finalize(); }

void GfMenuObjTutorial::update() {
  unknown28.unknown003();
  GfMenuObject::update();
}

void GfMenuObjTutorial::closeAll() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjTutorial::closeText(u32 param) { unknown156(unknown001, 0x101, param); }

void GfMenuObjTutorial::closeFocus(u32 param) { unknown156(unknown001, 0x102, param); }

void GfMenuObjTutorial::closeIcon(u32 param) { unknown156(unknown001, 0x103, param); }

bool GfMenuObjTutorial::seqTelopStart() {
  ui::UIObjectAcc image(unknown18, "IMG_start");
  bool isEnd;
  if (!unknown2b8) {
    ui::UIObjectAcc start(unknown18, "LAY_start");
    start.setDisp(true);
    image.startAnimation("start", false);
    {
      ui::UIObjectAcc text(unknown18, "TXT_start");
      text.setDisp(true);
      GfMenuObjUtil::CtrlParam param;
      param.unknown004("fade_in_l");
      param.unknown11 = true;
      param.unknown14 = 8;
      GfMenuObjUtil::startCtrl(text.unknown10, param, nullptr);
    }
    unknown2b8 = true;
    unknown2bc = 5;
    GfMenuObjUtil::playJingle(11);
    isEnd = false;
  } else {
    if (unknown2bc != 0 && --unknown2bc == 0) {
      ui::UIObjectAcc main(unknown18, "LAY_main");
      termCallContext(main.unknown10);
    }
    if (!image.isPlayingAnimation()) {
      unknown2b8 = false;
      isEnd = true;
    } else {
      isEnd = false;
    }
  }
  return isEnd;
}

bool GfMenuObjTutorial::seqTelopEnd() {
  ui::UIObjectAcc image(unknown18, "IMG_start");
  bool isEnd;
  if (!unknown2b8) {
    image.startAnimation("end", false);
    {
      ui::UIObjectAcc text(unknown18, "TXT_start");
      text.setDisp(true);
      GfMenuObjUtil::CtrlParam param;
      param.unknown004("fade_out_l");
      param.unknown11 = true;
      param.unknown14 = 10;
      GfMenuObjUtil::startCtrl(text.unknown10, param, nullptr);
    }
    isEnd = false;
    unknown2b8 = true;
  } else if (!image.isPlayingAnimation()) {
    ui::UIObjectAcc start(unknown18, "LAY_start");
    start.setDisp(false);
    unknown2b8 = false;
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjTutorial::seqEnd() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  ui::EventData event;
  event.unknown00 = 0x105;
  sendEvent(main.unknown10, event, 0.0f);
  return true;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjTutorial, 8>>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjTutorial>(const mm::mtl::Delegate<bool()> *);
