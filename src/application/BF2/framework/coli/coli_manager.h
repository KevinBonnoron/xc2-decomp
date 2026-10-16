#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "framework/pointer_map.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/unique_ptr.h"
#include "types.h"

namespace idcoli {
class IDColiManager;
} // namespace idcoli

namespace fw {

class ColiObject;

class ColiManager : public ManagerObject, public mm::mtl::PtrSingleton<ColiManager> {
public:
  class Impl {
  public:
    ~Impl();
    void updateContact();
    void sendContactEvent();
    void postUpdate();
    void sendRemoveEvent(u32 handle);
    void registObject(ColiObject *object);
    void removeObject(ColiObject *object);

    mm::mtl::IntrusiveList<ColiObject> objects;
    ColiObject *groundObject;
    idcoli::IDColiManager *manager;
    u32 frameCount;
    u8 _2c[0x38 - 0x2c];
    PointerMap objectMap;
  };

  bool initialize() override;
  bool finalize() override;
  void update();
  void postUpdate();
  void tail();
  void registObject(ColiObject *object);
  void removeObject(ColiObject *object);
  void cleanupObject(ColiObject *object);
  const idcoli::IDColiManager *getInterface() const;
  idcoli::IDColiManager *getInterface();
  void openDebugWindow();
  ColiObject *getGroundObject();
  ColiObject *getObject(u32 handle) const;
  bool isGblId(u32 id);
  void setGblId(u32 id, bool isGlobal);
  void *getGblIdTbl();

  mm::mtl::UniquePtr<Impl> impl;
};

static_assert(offsetof(ColiManager::Impl, groundObject) == 0x18, "");
static_assert(offsetof(ColiManager::Impl, manager) == 0x20, "");
static_assert(offsetof(ColiManager::Impl, objectMap) == 0x38, "");
static_assert(offsetof(ColiManager, impl) == 0x18, "");

} // namespace fw
