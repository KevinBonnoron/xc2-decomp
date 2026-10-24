#include "gf/object/component/gf_com_visible.h"

#include "framework/object/updatable_object.h"
#include "framework/object/visible_object.h"
#include "framework/reference_frame.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/gf_com_transform.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"

namespace gf {

GfComVisible::GfComVisible() : unknown10(nullptr) {}

void GfComVisible::setup(const SetupInfo &info) {
  fw::VisibleObject::SetupInfo visibleInfo;
  visibleInfo.layer = getLayer();
  unknown10 = fw::VisibleObject::create(visibleInfo, getAllocator(ALLOCATOR_DEFAULT));
  GfComTransform *transform = owner->getComponent<GfComTransform>();
  if (transform != nullptr) {
    unknown10->referenceFrame = transform->unknown18.get() == nullptr ? transform->unknown10 : transform->unknown18;
  }
}

void GfComVisible::cleanup() { mm::mtl::safeRelease(unknown10); }

void GfComVisible::changeLayer(u32 oldLayer, u32 newLayer) {
  if (oldLayer != newLayer && unknown10 != nullptr) {
    unknown10->changeLayer(newLayer);
  }
}

bool GfComVisible::isRender() const { return unknown10 != nullptr && unknown10->isRender(); }

const mm::mtl::RTTI *GfComVisible::getRTTI() const { return &m_rtti; }

} // namespace gf
