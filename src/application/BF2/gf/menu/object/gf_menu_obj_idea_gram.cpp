#include "gf/menu/object/gf_menu_obj_idea_gram.h"

#include "gf/data/gf_data_idea.h"
#include "gf/gf_allocator.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id of the idea gram layout; original name unknown.
constexpr u32 CALL_UNKNOWN_57 = 57;

// Inferred role: call id the idea gram moves to when it closes; original name unknown.
constexpr u32 CALL_UNKNOWN_58 = 58;

GfMenuObjIdeaGram::GfMenuObjIdeaGram(u32 handle) : GfMenuObject(handle) {}

GfMenuObjIdeaGram::~GfMenuObjIdeaGram() { ; }

void GfMenuObjIdeaGram::initialize() {
  ui::UIObjectAcc root(unknown18);
  attachExternalCall(CALL_UNKNOWN_57, ui::UIObjectAcc(unknown18, "LAY_driver").unknown10);
  GfMenuObject::initialize();
}

void GfMenuObjIdeaGram::finalize() { GfMenuObject::finalize(); }

void GfMenuObjIdeaGram::update() { GfMenuObject::update(); }

void GfMenuObjIdeaGram::open(GfMenuCallContext *context, const OpenParam &param) {
  ui::UIObjectAcc acc(getAttachedObject(CALL_UNKNOWN_57));
  if (acc.isValid() && !acc.isTerm() && GfMenuObjUtil::checkCCStart(context)) {
    ui::UIObjectAcc main(acc.duplicateChild("LAY_main"));
    if (main.isValid()) {
      ui::UIObjectAcc layout(param.unknown00);
      if (layout.isValid()) {
        layout.setLayout(main.unknown10, param.unknown08);
      }
// __LINE__ must be 397 as in the original file: it is the line argument of operator new.
#line 397
      MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener();
      listener->addRef();
      ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
      if (listener != nullptr) {
        listener->release();
      }
      ui::EventData event;
      event.unknown0c = 0;
      event.unknown00 = 0x21;
      event.unknown08 = param.unknown10;
      ui::UIManager::get()->requestObjectEvent(main.unknown10, event, 0.0f);
      startCallContext(context, CALL_UNKNOWN_57, main.unknown10);
    }
  }
}

void GfMenuObjIdeaGram::close(GfMenuCallContext *context, f32 time) {
  if (GfMenuObjUtil::checkCCNext(context, CALL_UNKNOWN_57)) {
    ui::EventData event;
    event.unknown0c = 0;
    event.unknown00 = 0x22;
    event.unknown08_f32 = time;
    ui::UIManager::get()->requestObjectEvent(context->unknown14, event, 0.0f);
    nextCallContext(context, CALL_UNKNOWN_58);
  }
}

void GfMenuObjIdeaGram::setIdeaPoint(GfMenuCallContext *context, u8 type, u32 point) {
  if (context != nullptr && context->unknown10 == CALL_UNKNOWN_57) {
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
  for (u32 i = 0; i < SDataIdea::IDEA_UNKNOWN_4; i++) {
    setIdeaPoint(context, i, data.unknown00[i].unknown00);
  }
}

void GfMenuObjIdeaGram::setIdeaPointFromBlade(GfMenuCallContext *context, u32 blade) {
  SDataIdea data = {};
  GfMenuObjUtil::getIdeagramBlade(blade, data);
  setIdeaPointFromData(context, data);
}

void GfMenuObjIdeaGram::addIdeaPoint(GfMenuCallContext *context, u8 type, int value, bool flag) {
  if (context != nullptr && context->unknown10 == CALL_UNKNOWN_57) {
    ui::EventData event;
    event.unknown00 = 0x101;
    event.unknown08_u16 = type;
    event.unknown0a = flag;
    event.unknown0c = value;
    ui::UIManager::get()->requestObjectEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjIdeaGram::addIdeaLevel(GfMenuCallContext *context, u8 type, int value, bool flag) {
  if (context != nullptr && context->unknown10 == CALL_UNKNOWN_57) {
    ui::EventData event;
    event.unknown00 = 0x102;
    event.unknown08_u16 = type;
    event.unknown0a = flag;
    event.unknown0c = value;
    ui::UIManager::get()->requestObjectEvent(context->unknown14, event, 0.0f);
  }
}

} // namespace gf
