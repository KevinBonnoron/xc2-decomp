#pragma once
#include <stddef.h>

#include "framework/reference_frame.h"
#include "gf/object/component/gf_component.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace fw {
class MessageObject;
} // namespace fw

namespace ml {
class WinProc;
} // namespace ml
namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComTransform : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 0;

  struct SetupInfo {
    mm::Vec3 unknown00; // Inferred role: position; original member name unknown.
    mm::Quat unknown10; // Inferred role: rotation; original member name unknown.
    u32 frame_max;
    bool unknown24; // Inferred role: use child frame; original member name unknown.
  };

  class Listener {
  public:
    virtual void onWkStandbyLogout() { unknown08->unknown80 = nullptr; }

    GfComTransform *unknown08; // Inferred role: owner; original member name unknown.
  };

  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  GfComTransform();
  ~GfComTransform() override;
  void setup(const SetupInfo &setup_info);
  void cleanup();
  void addReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame);
  void removeReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame);
  void addAfterReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame);
  void removeAfterReferenceFrame(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame);
  void setPosition(const mm::Vec3 &position);
  const mm::Vec3 &getPosition() const;
  void setRotation(const mm::Quat &rotation);
  const mm::Quat &getRotation() const;
  void syncFrame();
  void openDebugWindow(ml::WinProc *window);
  void changeLayer(u32 oldLayer, u32 newLayer) override;
  const mm::mtl::RTTI *getRTTI() const override;

  mm::mtl::IntrusivePtr<fw::ReferenceFrame> unknown10; // Inferred role: frame; original member name unknown.
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> unknown18; // Inferred role: child frame; original member name unknown.
  fw::TransformUpdater unknown20;                      // Inferred role: updater; original member name unknown.
  void *unknown80;                                     // Inferred role: viewer; original member name unknown.
  Listener unknown88;                                  // Inferred role: listener; original member name unknown.
};

static_assert(offsetof(GfComTransform::SetupInfo, unknown10) == 0x10, "");
static_assert(offsetof(GfComTransform::SetupInfo, frame_max) == 0x20, "");
static_assert(offsetof(GfComTransform::SetupInfo, unknown24) == 0x24, "");
static_assert(offsetof(GfComTransform, unknown10) == 0x10, "");
static_assert(offsetof(GfComTransform, unknown18) == 0x18, "");
static_assert(offsetof(GfComTransform, unknown20) == 0x20, "");
static_assert(offsetof(GfComTransform, unknown80) == 0x80, "");
static_assert(offsetof(GfComTransform, unknown88) == 0x88, "");

} // namespace gf
