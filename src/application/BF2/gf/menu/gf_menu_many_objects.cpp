// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/menu/gf_menu_many_objects.cpp.
#include "gf/menu/gf_menu_many_objects.h"

#include "gf/gf_allocator.h"
#include "types.h"

namespace gf {

GfMenuManyObjects::GfMenuManyObjects(const GfSetupParam &param) { initialize(param); }

void GfMenuManyObjects::initialize(const GfSetupParam &) {
  unknown08 = true;
  for (u32 i = 0; i < 8; i++) {
    unknown10[i] = nullptr;
  }
  for (u32 i = 0; i < 8; i++) {
    unknown50[i] = false;
  }
}

GfMenuManyObjects::~GfMenuManyObjects() {}

void GfMenuManyObjects::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfMenuManyObjects(param); }

void GfMenuManyObjects::destroy() {
  GfMenuManyObjects *manyObjects = get();
  manyObjects->finalize();
  delete manyObjects;
}

void GfMenuManyObjects::finalize() { unknown08 = false; }

bool GfMenuManyObjects::isInitialized() {
  GfMenuManyObjects *manyObjects = get();
  if (manyObjects != nullptr) {
    return manyObjects->unknown08;
  }
  return false;
}

void GfMenuManyObjects::postUpdate(const fw::UpdateInfo &) {}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfMenuManyObjects>::~PtrSingleton();
