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
    mm::Vec3 position;
    mm::Quat rotation;
    u32 frame_max;
    bool isUseChildFrame;
  };

  class Listener {
  public:
    virtual void onWkStandbyLogout() { owner->viewer = nullptr; }

    GfComTransform *owner;
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

  mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame;
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> childFrame;
  fw::TransformUpdater updater;
  void *viewer;
  Listener listener;
};

static_assert(offsetof(GfComTransform::SetupInfo, rotation) == 0x10, "");
static_assert(offsetof(GfComTransform::SetupInfo, frame_max) == 0x20, "");
static_assert(offsetof(GfComTransform::SetupInfo, isUseChildFrame) == 0x24, "");
static_assert(offsetof(GfComTransform, frame) == 0x10, "");
static_assert(offsetof(GfComTransform, childFrame) == 0x18, "");
static_assert(offsetof(GfComTransform, updater) == 0x20, "");
static_assert(offsetof(GfComTransform, viewer) == 0x80, "");
static_assert(offsetof(GfComTransform, listener) == 0x88, "");

} // namespace gf
