#include "gf/menu/call/gf_menu_call_manager.h"

#include "gf/gf_allocator.h"
#include "gf/menu/call/gf_menu_call_context.h"

namespace gf {

GfMenuCallManager::GfMenuCallManager(const GfSetupParam &param) : unknown08(), unknown228(getAllocator(ALLOCATOR_DEFAULT)), unknown1108() { reset(); }

void GfMenuCallManager::reset() {
  for (u32 i = 0; i < CALL_MAX; i++) {
    unknown08[i] = 0;
  }
}

GfMenuCallManager::~GfMenuCallManager() {
  for (CallInfo *info = unknown1108.begin(); info != unknown1108.end(); ++info) {
    if (info->unknown00 != nullptr) {
      info->unknown00->release();
      info->unknown00 = nullptr;
    }
  }
  unknown1108.clear();
}

bool GfMenuCallManager::canCall(u32 call) const {
  if (call < CALL_MAX) {
    return unknown08[call] != 0;
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

void GfMenuCallManager::attachCall(u32 call, u32 object) { unknown08[call] = object; }

void GfMenuCallManager::detachCall(u32 call) {
  if (call < CALL_MAX && unknown08[call] != 0) {
    unknown08[call] = 0;
  }
}

u32 GfMenuCallManager::getAttachedObject(u32 call) {
  if (call < CALL_MAX) {
    return unknown08[call];
  }
  return 0;
}

u16 GfMenuCallManager::registString(const ui::UIStr &string) { return unknown228.addString(string); }

void GfMenuCallManager::releaseString(u16 id) { unknown228.delString(id); }

const ui::UIStr &GfMenuCallManager::getString(u16 id) { return unknown228.getString(id); }

void GfMenuCallManager::startCallContext(GfMenuCallContext *context, u32 menu, u32 object) {
  if (unknown1108.size() == unknown1108.capacity()) {
    return;
  }
  if (context->isActive() && !context->isTerm()) {
    return;
  }
  for (CallInfo *info = unknown1108.begin(); info != unknown1108.end(); ++info) {
    if (info->unknown00->unknown0c == context->unknown0c) {
      context->setup(object, menu);
      return;
    }
  }
  context->setup(object, menu);
  context->addRef();
  CallInfo info;
  info.unknown00 = context;
  info.unknown08 = 0;
  unknown1108.push_back(info);
}

void GfMenuCallManager::nextCallContext(GfMenuCallContext *context, u32 menu) {
  if (context->isActive()) {
    context->callNext(menu);
  }
}

void GfMenuCallManager::setCallContextEventHandler(GfMenuCallContext *context, u32 handler) {
  for (CallInfo *info = unknown1108.begin(); info != unknown1108.end(); ++info) {
    if (info->unknown00->unknown0c == context->unknown0c) {
      info->unknown08 = handler;
      return;
    }
  }
}

} // namespace gf
