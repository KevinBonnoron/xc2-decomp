#include "gf/menu/call/gf_menu_call_manager.h"

#include "gf/gf_allocator.h"
#include "gf/menu/call/gf_menu_call_context.h"

namespace gf {

GfMenuCallManager::GfMenuCallManager(const GfSetupParam &param) : calls(), strLinker(getAllocator(ALLOCATOR_DEFAULT)), contexts() { reset(); }

void GfMenuCallManager::reset() {
  for (u32 i = 0; i < CALL_MAX; i++) {
    calls[i] = 0;
  }
}

GfMenuCallManager::~GfMenuCallManager() {
  for (CallInfo *info = contexts.begin(); info != contexts.end(); ++info) {
    if (info->context != nullptr) {
      info->context->release();
      info->context = nullptr;
    }
  }
  contexts.clear();
}

bool GfMenuCallManager::canCall(u32 call) const {
  if (call < CALL_MAX) {
    return calls[call] != 0;
  }
  return false;
}

void GfMenuCallManager::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfMenuCallManager(param); }

void GfMenuCallManager::destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

bool GfMenuCallManager::isInitialized() { return true; }

void GfMenuCallManager::attachCall(u32 call, u32 object) { calls[call] = object; }

void GfMenuCallManager::detachCall(u32 call) {
  if (call < CALL_MAX && calls[call] != 0) {
    calls[call] = 0;
  }
}

u32 GfMenuCallManager::getAttachedObject(u32 call) {
  if (call < CALL_MAX) {
    return calls[call];
  }
  return 0;
}

u16 GfMenuCallManager::registString(const ui::UIStr &string) { return strLinker.addString(string); }

void GfMenuCallManager::releaseString(u16 id) { strLinker.delString(id); }

const ui::UIStr &GfMenuCallManager::getString(u16 id) { return strLinker.getString(id); }

void GfMenuCallManager::startCallContext(GfMenuCallContext *context, u32 menu, u32 object) {
  if (contexts.size() == contexts.capacity()) {
    return;
  }
  if (context->isActive() && !context->isTerm()) {
    return;
  }
  for (CallInfo *info = contexts.begin(); info != contexts.end(); ++info) {
    if (info->context->id == context->id) {
      context->setup(object, menu);
      return;
    }
  }
  context->setup(object, menu);
  context->addRef();
  CallInfo info;
  info.context = context;
  info.handler = 0;
  contexts.push_back(info);
}

void GfMenuCallManager::nextCallContext(GfMenuCallContext *context, u32 menu) {
  if (context->isActive()) {
    context->callNext(menu);
  }
}

void GfMenuCallManager::setCallContextEventHandler(GfMenuCallContext *context, u32 handler) {
  for (CallInfo *info = contexts.begin(); info != contexts.end(); ++info) {
    if (info->context->id == context->id) {
      info->handler = handler;
      return;
    }
  }
}

} // namespace gf
