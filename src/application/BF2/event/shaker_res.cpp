#include "event/shaker_res.h"

#include "event/memory_manager.h"
#include "framework/resource/common_resource.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "rcha/rcha_cam.h"

namespace event {

ShakerRes::ShakerRes() : unknown50(nullptr), m_rchaCam(nullptr) {}

ShakerRes::~ShakerRes() { destroy(); }

void ShakerRes::destroy() {
  if (m_rchaCam != nullptr) {
    delete m_rchaCam;
    m_rchaCam = nullptr;
  }
  mm::mtl::safeRelease(unknown50);
  unknown08 = "";
}

void ShakerRes::create(const char *name) {
  destroy();
  this->unknown08 = name;
  unknown50 = fw::CommonResource::request(mm::mtl::Singleton<MemoryManager>::get().getStaticHandle(), name, 0, false);
}

void ShakerRes::update() {
  if (unknown50 == nullptr || !unknown50->valid() || m_rchaCam != nullptr) {
    return;
  }
  const void *data = unknown50->getAssetData();
  m_rchaCam = new (mm::mtl::Singleton<MemoryManager>::get().getStaticHandle(), nullptr, 0, 4, false) RchaCam;
  m_rchaCam->setup(mm::mtl::Singleton<MemoryManager>::get().getStaticHandle(), data);
}

} // namespace event
