#pragma once
#include <stddef.h>

#include "framework/reference_frame.h"
#include "gf/object/component/gf_component.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
struct Quat;
struct Vec3;
} // namespace mm

namespace gf {

class GfComTransform : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 0;

  class Listener {
  public:
    virtual void onWkStandbyLogout();

    GfComTransform *owner;
  };

  void setPosition(const mm::Vec3 &position);
  const mm::Vec3 &getPosition() const;
  void setRotation(const mm::Quat &rotation);
  const mm::Quat &getRotation() const;

  mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame;
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> childFrame;
  fw::TransformUpdater updater;
  void *viewer;
  Listener listener;
};

static_assert(offsetof(GfComTransform, frame) == 0x10, "");
static_assert(offsetof(GfComTransform, childFrame) == 0x18, "");
static_assert(offsetof(GfComTransform, updater) == 0x20, "");
static_assert(offsetof(GfComTransform, viewer) == 0x80, "");
static_assert(offsetof(GfComTransform, listener) == 0x88, "");

} // namespace gf
