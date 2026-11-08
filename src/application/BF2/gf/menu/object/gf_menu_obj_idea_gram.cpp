#include "gf/menu/object/gf_menu_obj_idea_gram.h"

#include "gf/data/gf_data_idea.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

constexpr u32 CALL_IDEA_GRAM = 57;

GfMenuObjIdeaGram::GfMenuObjIdeaGram(u32 handle) : GfMenuObject(handle) {}

GfMenuObjIdeaGram::~GfMenuObjIdeaGram() { ; }

void GfMenuObjIdeaGram::initialize() {
  ui::UIObjectAcc root(unknown18);
  attachExternalCall(CALL_IDEA_GRAM, ui::UIObjectAcc(unknown18, "LAY_driver").unknown10);
  GfMenuObject::initialize();
}

void GfMenuObjIdeaGram::finalize() { GfMenuObject::finalize(); }

void GfMenuObjIdeaGram::update() { GfMenuObject::update(); }

void GfMenuObjIdeaGram::setIdeaPoint(GfMenuCallContext *context, u8 type, u32 point) {
  if (context != nullptr && context->unknown10 == CALL_IDEA_GRAM) {
    ui::EventData event;
    event.unknown08 = 0;
    event.unknown00 = 0x100;
    event.unknown0c = point;
    event.unknown08_u16 = type;
    ui::UIManager::get()->requestObjectEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjIdeaGram::setIdeaPointFromDriver(GfMenuCallContext *context, u32 driver) {
  SDataIdea data = {};
  GfMenuObjUtil::getIdeagramDriver(driver, data);
  setIdeaPointFromData(context, data);
}

void GfMenuObjIdeaGram::setIdeaPointFromData(GfMenuCallContext *context, const SDataIdea &data) {
  for (u32 i = 0; i < SDataIdea::IDEA_MAX; i++) {
    setIdeaPoint(context, i, data.unknown00[i].unknown00);
  }
}

void GfMenuObjIdeaGram::setIdeaPointFromBlade(GfMenuCallContext *context, u32 blade) {
  SDataIdea data = {};
  GfMenuObjUtil::getIdeagramBlade(blade, data);
  setIdeaPointFromData(context, data);
}

void GfMenuObjIdeaGram::addIdeaPoint(GfMenuCallContext *context, u8 type, int value, bool flag) {
  if (context != nullptr && context->unknown10 == CALL_IDEA_GRAM) {
    ui::EventData event;
    event.unknown00 = 0x101;
    event.unknown08_u16 = type;
    event.unknown0a = flag;
    event.unknown0c = value;
    ui::UIManager::get()->requestObjectEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjIdeaGram::addIdeaLevel(GfMenuCallContext *context, u8 type, int value, bool flag) {
  if (context != nullptr && context->unknown10 == CALL_IDEA_GRAM) {
    ui::EventData event;
    event.unknown00 = 0x102;
    event.unknown08_u16 = type;
    event.unknown0a = flag;
    event.unknown0c = value;
    ui::UIManager::get()->requestObjectEvent(context->unknown14, event, 0.0f);
  }
}

} // namespace gf
