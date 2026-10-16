#include "event/shaker_res.h"

#include "event/memory_manager.h"
#include "fw/fw_render_resource.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "rcha/rcha_cam.h"

namespace event {

ShakerRes::ShakerRes() : resource(nullptr), rcha(nullptr) {}

ShakerRes::~ShakerRes() { destroy(); }

void ShakerRes::destroy() {
  if (rcha != nullptr) {
    delete rcha;
    rcha = nullptr;
  }
  mm::mtl::safeRelease(resource);
  name = "";
}

void ShakerRes::create(const char *name) {
  destroy();
  this->name = name;
  resource = fw::CommonResource::request(mm::mtl::Singleton<MemoryManager>::get().getStaticHandle(), name, 0, false);
}

void ShakerRes::update() {
  if (resource == nullptr || !resource->valid() || rcha != nullptr) {
    return;
  }
  const void *data = resource->getAssetData();
  rcha = new (mm::mtl::Singleton<MemoryManager>::get().getStaticHandle(), nullptr, 0, 4, false) RchaCam;
  rcha->setup(mm::mtl::Singleton<MemoryManager>::get().getStaticHandle(), data);
}

} // namespace event
