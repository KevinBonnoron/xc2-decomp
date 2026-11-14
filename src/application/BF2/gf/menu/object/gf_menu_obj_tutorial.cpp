#include "gf/menu/object/gf_menu_obj_tutorial.h"

#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/sound/gf_sound.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

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
    MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
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

void GfMenuObjTutorial::openText(u32 param, const TextParam &text) {
  if (GfMenuObjUtil::checkCCStart(unknown002)) {
    ui::UIObjectAcc acc(getAttachedObject(unknown001));
    if (acc.isValid()) {
      u16 id = registString(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_TUTORIAL), text.unknown00));
      ui::EventData event;
      event.unknown0c = 0;
      event.unknown00 = 0x101;
      event.unknown08_u16 = param;
      event.unknown0a = 1;
      event.unknown0c_u16 = id;
      sendEvent(acc.unknown10, event, 0.0f);
      startCallContext(unknown002, unknown001, acc.unknown10);
    }
  }
}

void GfMenuObjTutorial::closeText(u32 param) { unknown156(unknown001, 0x101, param); }

void GfMenuObjTutorial::openFocus(u32 param, const FocusParam &focus) {
  ui::UIObjectAcc acc(getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = 0x102;
    event.unknown08_u16 = param;
    event.unknown0a = 1;
    event.unknown0c_u16 = focus.unknown04;
    event.unknown0e = focus.unknown00;
    event.unknown10_u16 = focus.unknown02;
    sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjTutorial::closeFocus(u32 param) { unknown156(unknown001, 0x102, param); }

void GfMenuObjTutorial::openIcon(u32 param, const IconParam &icon) {
  ui::UIObjectAcc acc(getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown0c = 0;
    event.unknown00 = 0x103;
    event.unknown08_u16 = param;
    event.unknown0a = 1;
    event.unknown0e = icon.unknown00;
    event.unknown10_u16 = icon.unknown02;
    sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjTutorial::closeIcon(u32 param) { unknown156(unknown001, 0x103, param); }

void GfMenuObjTutorial::start() {
  if (GfMenuObjUtil::checkCCStart(unknown002)) {
    ui::UIObjectAcc acc(getAttachedObject(unknown001));
    if (acc.isValid()) {
      ui::EventData event;
      event.unknown00 = 0x104;
      sendEvent(acc.unknown10, event, 0.0f);
      startCallContext(unknown002, unknown001, acc.unknown10);
    }
  }
}

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

void GfMenuObjTutorial::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 0x101: {
    u32 param = event.unknown08;
    u32 index = (param & 0xffff) + 1;
    mm::mtl::FixStr<32> name;
    name.format("LAY_info@%02d", index);
    ui::UIObjectAcc info(acc.unknown10, name.c_str());
    if (info.isValid()) {
      if ((param & 0xffff0000) == 0x10000) {
        info.setDisp(true);
        name.format("TXT_info@%02d", index);
        u16 text = event.unknown0c_u16;
        {
          ui::UIObjectAcc label(info.unknown10, name.c_str());
          if (label.isValid()) {
            GfMenuObject::setText(label.unknown10, text);
          }
        }
        GfMenuObject::enableInput(acc.unknown10);
        GfMenuObject::registTimer(acc.unknown10, 0, 0.5f, true);
        acc.setDispChild(true, "IMG_info_arrow@01");
        acc.setDispChild(true, "IMG_info_arrow@02");
      } else {
        info.setDisp(false);
        GfMenuObject::disableInput(acc.unknown10);
        GfMenuObject::releaseTimer(acc.unknown10);
        acc.setDispChild(false, "IMG_info_arrow@01");
        acc.setDispChild(false, "IMG_info_arrow@02");
      }
    }
    break;
  }
  case 0x102: {
    u32 param = event.unknown08;
    u32 index = (param & 0xffff) + 1;
    mm::mtl::FixStr<32> name;
    name.format("LAY_focus@%02d", index);
    ui::UIObjectAcc focus(acc.unknown10, name.c_str());
    if (focus.isValid()) {
      if ((param & 0xffff0000) == 0x10000) {
        u16 direction = event.unknown0c_u16;
        focus.setDisp(true);
        s16 width;
        s16 height;
        focus.getSize(true, width, height);
        mm::Pnt<s16> pos;
        pos.x = event.unknown0e;
        pos.y = event.unknown10_u16;
        f32 rot = 0.0f;
        switch (direction) {
        case 0:
          pos.y += height / 2;
          break;
        case 1:
          pos.y -= height / 2;
          rot = 3.1415927f;
          break;
        case 2:
          pos.x += width / 2;
          rot = 1.5707964f;
          break;
        case 3:
          pos.x -= width / 2;
          rot = 4.712389f;
          break;
        }
        focus.setRot(rot);
        focus.setPosCenter(pos);
        name.format("IMG_focus_icon@%02d", index);
        ui::UIObjectAcc(acc.unknown10, name.c_str()).startAnimation("loop", false);
      } else {
        focus.setDisp(false);
        name.format("IMG_focus_icon@%02d", index);
        ui::UIObjectAcc(acc.unknown10, name.c_str()).stopAnimation();
      }
    }
    break;
  }
  case 0x103: {
    u32 param = event.unknown08;
    mm::mtl::FixStr<32> name;
    name.format("LAY_icon@%02d", (param & 0xffff) + 1);
    ui::UIObjectAcc icon(acc.unknown10, name.c_str());
    if (icon.isValid()) {
      if ((param & 0xffff0000) == 0x10000) {
        icon.setDisp(true);
        mm::Pnt<s16> pos;
        pos.x = event.unknown0e;
        pos.y = event.unknown10_u16;
        icon.setPosCenter(pos);
        GfMenuObjUtil::CtrlParam ctrl;
        ctrl.unknown08 = 0x80000;
        ctrl.unknown0c = 1;
        ctrl.unknown2c = 1.2f;
        ctrl.unknown10 = true;
        ctrl.unknown11 = true;
        ctrl.unknown00 = 0.5f;
        GfMenuObjUtil::startCtrl(icon.unknown10, ctrl, nullptr);
      } else {
        int id = GfMenuObjUtil::getCtrlID(icon.unknown10);
        if (id != -1) {
          GfMenuObjUtil::stopCtrl(id);
        }
        icon.setDisp(false);
      }
    }
    break;
  }
  case 0x104:
    unknown20->unknown2b8 = false;
    unknown20->unknown28.unknown002(&GfMenuObjTutorial::seqTelopStart);
    unknown20->unknown28.unknown004(30);
    unknown20->unknown28.unknown002(&GfMenuObjTutorial::seqTelopEnd);
    unknown20->unknown28.unknown002(&GfMenuObjTutorial::seqEnd);
    break;
  case 0x105:
    break;
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    acc.setDisp(true);
    break;
  case 8:
    if (event.unknown0c == 1) {
      GfMenuObject::termCallContext(acc.unknown10);
      GfMenuObject::disableInput(acc.unknown10);
      GfMenuObject::releaseTimer(acc.unknown10);
      acc.setDispChild(false, "IMG_info_arrow@01");
      acc.setDispChild(false, "IMG_info_arrow@02");
    }
    break;
  case 0xb: {
    bool isDisp = (event.unknown0c & 1) == 0;
    acc.setDispChild(isDisp, "IMG_info_arrow@01");
    acc.setDispChild(isDisp, "IMG_info_arrow@02");
    break;
  }
  case 0x22:
    closeText(0);
    closeText(1);
    closeFocus(0);
    closeFocus(1);
    closeFocus(2);
    closeFocus(3);
    closeIcon(0);
    closeIcon(1);
    closeIcon(2);
    closeIcon(3);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjTutorial, 8>>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjTutorial>(const mm::mtl::Delegate<bool()> *);
