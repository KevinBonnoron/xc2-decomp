#include "gf/menu/call/gf_menu_call_context.h"

#include "gf/gf_allocator.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

static u32 nextId;

GfMenuCallContext::GfMenuCallContext() : unknown10(0), unknown14(0), unknown40(false) {
  unknown0c = nextId;
  nextId++;
}

GfMenuCallContext::~GfMenuCallContext() {}

GfMenuCallContext *GfMenuCallContext::create() {
  GfMenuCallContext *context = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuCallContext();
  context->addRef();
  return context;
}

GfMenuCallContext::STATE GfMenuCallContext::getState() {
  if (unknown14 != 0 && ui::UIObjectAcc(unknown14).isTerm()) {
    return STATE_TERM;
  }
  if (unknown40) {
    return STATE_TERM;
  }
  return unknown14 != 0 ? STATE_ACTIVE : STATE_IDLE;
}

bool GfMenuCallContext::isTerm() const {
  if (unknown14 != 0 && ui::UIObjectAcc(unknown14).isTerm()) {
    return true;
  }
  return unknown40;
}

bool GfMenuCallContext::isActive() const { return unknown14 != 0; }

void GfMenuCallContext::reset() {
  if (!unknown40) {
    terminate();
  }
  unknown40 = false;
  unknown10 = 0;
  unknown18.clear();
}

void GfMenuCallContext::terminate() {
  unknown40 = true;
  unknown14 = 0;
}

void GfMenuCallContext::abort() {
  if (unknown14 != 0) {
    ui::EventData event;
    event.type = 2;
    ui::UIManager::get()->requestObjectEvent(unknown14, event, 0.0f);
    return;
  }
  unknown40 = true;
}

bool GfMenuCallContext::popResult(GfMenuResult &result) {
  if (unknown18.empty()) {
    return false;
  }
  result = unknown18.front();
  unknown18.erase(unknown18.begin());
  return true;
}

void GfMenuCallContext::addResult(const GfMenuResult &result) {
  if (unknown18.size() < unknown18.capacity()) {
    unknown18.push_back(result);
  }
}

void GfMenuCallContext::setup(u32 object, u32 menu) {
  if (this->unknown14 == 0) {
    unknown40 = false;
    this->unknown10 = menu;
    this->unknown14 = object;
  }
}

void GfMenuCallContext::callNext(u32 menu) {
  if (unknown14 != 0) {
    this->unknown10 = menu;
  }
}

} // namespace gf
