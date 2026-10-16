#include "gf/menu/call/gf_menu_call_context.h"

#include "gf/gf_allocator.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

static u32 nextId;

GfMenuCallContext::GfMenuCallContext() : menu(0), object(0), isTerminated(false) {
  id = nextId;
  nextId++;
}

GfMenuCallContext::~GfMenuCallContext() {}

GfMenuCallContext *GfMenuCallContext::create() {
  GfMenuCallContext *context = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuCallContext();
  context->addRef();
  return context;
}

GfMenuCallContext::STATE GfMenuCallContext::getState() {
  if (object != 0 && ui::UIObjectAcc(object).isTerm()) {
    return STATE_TERM;
  }
  if (isTerminated) {
    return STATE_TERM;
  }
  return object != 0 ? STATE_ACTIVE : STATE_IDLE;
}

bool GfMenuCallContext::isTerm() const {
  if (object != 0 && ui::UIObjectAcc(object).isTerm()) {
    return true;
  }
  return isTerminated;
}

bool GfMenuCallContext::isActive() const { return object != 0; }

void GfMenuCallContext::reset() {
  if (!isTerminated) {
    terminate();
  }
  isTerminated = false;
  menu = 0;
  results.clear();
}

void GfMenuCallContext::terminate() {
  isTerminated = true;
  object = 0;
}

void GfMenuCallContext::abort() {
  if (object != 0) {
    ui::EventData event;
    event.type = 2;
    ui::UIManager::get()->requestObjectEvent(object, event, 0.0f);
    return;
  }
  isTerminated = true;
}

bool GfMenuCallContext::popResult(GfMenuResult &result) {
  if (results.empty()) {
    return false;
  }
  result = results.front();
  results.erase(results.begin());
  return true;
}

void GfMenuCallContext::addResult(const GfMenuResult &result) {
  if (results.size() < results.capacity()) {
    results.push_back(result);
  }
}

void GfMenuCallContext::setup(u32 object, u32 menu) {
  if (this->object == 0) {
    isTerminated = false;
    this->menu = menu;
    this->object = object;
  }
}

void GfMenuCallContext::callNext(u32 menu) {
  if (object != 0) {
    this->menu = menu;
  }
}

} // namespace gf
