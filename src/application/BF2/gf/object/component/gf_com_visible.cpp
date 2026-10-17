#include "gf/object/component/gf_com_visible.h"

#include "framework/object/updatable_object.h"
#include "framework/object/visible_object.h"
#include "framework/reference_frame.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/gf_com_transform.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"

namespace gf {

GfComVisible::GfComVisible() : visible(nullptr) {}

void GfComVisible::setup(const SetupInfo &info) {
  fw::VisibleObject::SetupInfo visibleInfo;
  visibleInfo.layer = getLayer();
  visible = fw::VisibleObject::create(visibleInfo, getAllocator(ALLOCATOR_DEFAULT));
  GfComTransform *transform = owner->getComponent<GfComTransform>();
  if (transform != nullptr) {
    visible->referenceFrame = transform->childFrame.get() == nullptr ? transform->frame : transform->childFrame;
  }
}

void GfComVisible::cleanup() { mm::mtl::safeRelease(visible); }

void GfComVisible::changeLayer(u32 oldLayer, u32 newLayer) {
  if (oldLayer != newLayer && visible != nullptr) {
    visible->changeLayer(newLayer);
  }
}

bool GfComVisible::isRender() const { return visible != nullptr && visible->isRender(); }

const mm::mtl::RTTI *GfComVisible::getRTTI() const { return &m_rtti; }

} // namespace gf
