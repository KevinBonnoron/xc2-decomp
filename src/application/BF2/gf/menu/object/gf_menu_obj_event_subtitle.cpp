#include "gf/menu/object/gf_menu_obj_event_subtitle.h"

#include "framework/lang_util.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_option.h"
#include "gf/gf_allocator.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "layer/layer_acc_font_obj.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/text/ui_tag_parser.h"
#include "ui/ui_manager.h"
#include "ui/ui_object.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"
#include "ui/ui_util.h"

namespace gf {

enum CALL {
  CALL_EVENT_SUBTITLE = 1,
};

enum EVENT {
  EVENT_TERM = 2,
  EVENT_END_TEXT = 0x45,
  EVENT_DISP_TEXT = 0x100,
  EVENT_HIDE_TEXT = 0x101,
};

GfMenuObjEventSubtitle::GfMenuObjEventSubtitle(u32 handle) : GfMenuObject(handle) {}

GfMenuObjEventSubtitle::~GfMenuObjEventSubtitle() {
  // A body that is not empty keeps the vtable pointer store that the game does.
  ;
}

void GfMenuObjEventSubtitle::initialize() {
  ui::UIObjectAcc main(handle, "LAY_main");
// __LINE__ must be 71 as in the original file: its value changes the instruction order.
#line 71
  MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.handle, listener);
  if (listener != nullptr) {
    listener->release();
  }
  attachExternalCall(CALL_EVENT_SUBTITLE, main.handle);
  if (fw::LangUtil::getLangType() == 0) {
    ui::UIObjectAcc vertical(main.searchChild("TXT_str_v"));
    if (vertical.isValid()) {
      layer::LayerAccFontObj font(ui::UIUtil::getObject(vertical.handle)->layer);
      font.setDispSetting(layer::LAYER_FONT_SETTING_VERTICAL);
      GfMenuObjUtil::addPos(vertical.handle, 92, 0);
    }
  }
  ui::UIObjectAcc(handle).setTerm();
  GfMenuObject::initialize();
}

void GfMenuObjEventSubtitle::finalize() {
  detachExternalCall(CALL_EVENT_SUBTITLE);
  GfMenuObject::finalize();
}

void GfMenuObjEventSubtitle::update() { GfMenuObject::update(); }

void GfMenuObjEventSubtitle::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.type) {
  case 1:
    break;
  case EVENT_TERM:
    acc.setTerm();
    break;
  case EVENT_END_TEXT: {
    ui::UIObjectAcc text(acc.handle, "TXT_str00");
    ui::UIObjectAcc vertical(acc.handle, "TXT_str_v");
    text.setDisp(false);
    text.setText(ui::UIStr(" ", false));
    vertical.setDisp(false);
    vertical.setText(ui::UIStr(" ", false));
    break;
  }
  case EVENT_DISP_TEXT: {
    u32 position = event.param1;
    const ui::UIStr &string = getString(event.param0);
    if (ui::UITagParser::get()->parseTag(string.c_str(), "ML:undisp")) {
      releaseString(event.param0);
      ui::EventData hide;
      hide.type = EVENT_HIDE_TEXT;
      sendEvent(acc.handle, hide, 0.0f);
      break;
    }
    bool isVertical = ui::UITagParser::get()->parseTag(string.c_str(), "ML:Vertical");
    u32 child;
    switch (position) {
    case 0:
      if (isVertical) {
        child = acc.searchChild("TXT_str_v");
      } else if (GfDataManager::getDataOption()->_68) {
        child = acc.searchChild("TXT_str00");
      } else {
        releaseString(event.param0);
        return;
      }
      break;
    case 1:
      child = acc.searchChild("TXT_str01");
      break;
    case 2:
      child = acc.searchChild("TXT_str02");
      break;
    default:
      child = 0;
      break;
    }
    ui::UIObjectAcc text(child);
    if (text.isValid()) {
      if (isVertical) {
        text.setSlopeRot(-12.0f);
      }
      text.setDisp(true);
      setText(text.handle, event.param0);
    }
    break;
  }
  case EVENT_HIDE_TEXT: {
    ui::UIObjectAcc text(acc.handle, "TXT_str00");
    ui::UIObjectAcc vertical(acc.handle, "TXT_str_v");
    ui::UIObjectAcc text1(acc.handle, "TXT_str01");
    ui::UIObjectAcc text2(acc.handle, "TXT_str02");
    text.setDisp(false);
    vertical.setDisp(false);
    text1.setDisp(false);
    text2.setDisp(false);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjEventSubtitle::dispText(u8 *bdat, u32 textId, u32 position) {
  u32 object = getAttachedObject(CALL_EVENT_SUBTITLE);
  if (!ui::UIObjectAcc(object).isValid()) {
    return;
  }
  if (ui::UIObjectAcc(object).isTerm()) {
    return;
  }
  u16 id = registString(ui::UIStr(bdat, textId));
  ui::EventData event;
  event.type = EVENT_DISP_TEXT;
  event.param0 = id;
  event.param1 = position;
  ui::UIManager::get()->requestObjectEvent(object, event, 0.0f);
}

void GfMenuObjEventSubtitle::hideText() {
  u32 object = getAttachedObject(CALL_EVENT_SUBTITLE);
  ui::EventData event;
  event.type = EVENT_HIDE_TEXT;
  ui::UIManager::get()->requestObjectEvent(object, event, 0.0f);
}

void GfMenuObjEventSubtitle::endText() {
  u32 object = getAttachedObject(CALL_EVENT_SUBTITLE);
  ui::EventData event;
  event.type = EVENT_END_TEXT;
  ui::UIManager::get()->requestObjectEvent(object, event, 0.0f);
}

} // namespace gf
