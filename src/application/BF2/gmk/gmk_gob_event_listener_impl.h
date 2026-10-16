#pragma once
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_gob_event_listener.h"
#include "types.h"

namespace gmk {

static GmkGobEventListener *s_instance = nullptr;

GmkGobEventListener::GmkGobEventListener() : refCount(0) { gf::GfObjManager::addListener(this, OBJEVT_ALL); }

GmkGobEventListener::~GmkGobEventListener() { gf::GfObjManager::removeListener(this); }

void GmkGobEventListener::createInstance() {
  if (s_instance == nullptr) {
    s_instance = new (gf::getAllocator(gf::ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GmkGobEventListener();
  }
  s_instance->refCount++;
}

void GmkGobEventListener::disposeInstance() {
  s_instance->refCount--;
  if (s_instance != nullptr && s_instance->refCount <= 0) {
    delete s_instance;
    s_instance = nullptr;
  }
}

void GmkGobEventListener::listenerGfObj(OBJEVT event, gf::GF_OBJ_HANDLE *handle, u32) {
  gf::GfObjAcc acc(handle);
  AGmkBase *gmk = reinterpret_cast<AGmkBase *>(acc.getUserData(gf::OBJ_USER_DATA_GMK));
  if (gmk != nullptr) {
    gmk->onGobEvent(event, handle);
  }
}

} // namespace gmk
