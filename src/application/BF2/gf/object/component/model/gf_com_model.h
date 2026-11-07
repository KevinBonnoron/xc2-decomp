#pragma once
#include <stddef.h>

#include "framework/anim/anim_pose_modifier.h"
#include "framework/anim/anim_volume_fade_modifier.h"
#include "framework/reference_frame.h"
#include "gf/object/component/gf_component.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace anm {
class ExtraTruckBuffer;
class Pose;
class Skeleton;
} // namespace anm
namespace fw {
class ModelObject;
class MessageObject;
} // namespace fw
namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct MsgObjectNotifyDamage;
struct MsgObjectNotifyDead;

// Layout evidence: constructor (0x71005300cc) places AnimPoseModifier at 0x40, AnimVolumeFadeModifier at 0x10c8, two
// Vector<BoneFrameInfo> at 0x1140 and 0x1168, the scale 1.0f at 0x1190 and the ViewerListener vtable and owner at 0x1198
// and 0x11a0; ViewerListener::onWkStandbyLogout (0x7100532db0) clears 0x11a8.
class GfComModel : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 1;

  // Layout evidence: createBoneReferenceFrame (0x7100530db0) pushes the new frame, the index as a halfword at 0x08 (findBoneFrameInfo
  // compares it with ldrsh) and a count of 1 at 0x0c (and increments the count of an existing entry); the default constructor zeroes
  // the count before the fields are assigned (str wzr at 0x0c in every push); the copy in Vector<BoneFrameInfo>::push_back
  // (0x7100531814) takes a reference on the frame and copies the 8 bytes at 0x08.
  struct BoneFrameInfo {
    BoneFrameInfo() : unknown08(0), unknown0c(0) {}

    mm::mtl::IntrusivePtr<fw::ReferenceFrame> unknown00; // Inferred role: bone reference frame; original member name unknown.
    s16 unknown08;                                       // Inferred role: bone index; original member name unknown.
    s32 unknown0c;                                       // Inferred role: reference count; original member name unknown.
  };

  // Inferred helper: adds an entry for a frame with a reference count of 1; original name unknown.
  static void unknown001(mm::mtl::Vector<BoneFrameInfo> &frames, mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame, u16 index) {
    BoneFrameInfo info;
    info.unknown08 = index;
    info.unknown00 = frame;
    info.unknown0c = 1;
    frames.push_back(info);
  }

  class ViewerListener {
  public:
    virtual void onWkStandbyLogout() {
      if (unknown08 != nullptr) {
        unknown08->unknown11a8 = nullptr;
      }
    }

    GfComModel *unknown08; // Inferred role: owner; original member name unknown.
  };

  bool hasBone(const char *name) const;
  bool isRender() const;
  bool isVolumeFadeForUser() const;
  void procMsgObjectNotifyDead(fw::MessageObject *sender, MsgObjectNotifyDead &message);
  void procMsgObjectNotifyDamage(fw::MessageObject *sender, MsgObjectNotifyDamage &message);
  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  void setModelScale(f32 scale);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> createBoneReferenceFrame(const char *name);
  BoneFrameInfo *findBoneFrameInfo(u16 bone);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> createBoneReferenceFrameImpl(u16 bone);
  BoneFrameInfo *findMountFrameInfo(u16 mount);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> createMountReferenceFrameImpl(u16 mount);
  void destroyBoneReferenceFrame(const char *name);
  void destroyBoneReferenceFrameImpl(mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame);
  void destroyMountReferenceFrameImpl(mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame);
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> getBoneReferenceFrame(const char *name);
  bool addBoneReferenceFrame(const char *name, mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame);
  void removeBoneReferenceFrame(const char *name, mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame);
  void bindReferenceFrameToBone(u16 bone, mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame);
  void unbindReferenceFrameToBone(mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame);

  u8 _10[0x18 - 0x10];
  fw::ModelObject *unknown18;                          // Inferred role: model object; original member name unknown.
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> unknown20; // Inferred role: reference frame; original member name unknown.
  const anm::Skeleton *unknown28;                      // Inferred role: skeleton; original member name unknown.
  anm::Pose *unknown30;                                // Inferred role: pose; original member name unknown.
  anm::ExtraTruckBuffer *unknown38;                    // Inferred role: extra truck buffer; original member name unknown.
  fw::AnimPoseModifier unknown40;                      // Inferred role: pose modifier; original member name unknown.
  fw::AnimVolumeFadeModifier unknown10c8;              // Inferred role: volume fade modifier; original member name unknown.
  mm::mtl::Vector<BoneFrameInfo> unknown1140;          // Inferred role: bone frames; original member name unknown.
  mm::mtl::Vector<BoneFrameInfo> unknown1168;          // Inferred role: mount frames; original member name unknown.
  f32 m_modelScale;
  ViewerListener unknown1198; // Inferred role: viewer listener; original member name unknown.
  void *unknown11a8;          // Inferred role: viewer; original member name unknown.
};

static_assert(offsetof(GfComModel, unknown18) == 0x18, "");
static_assert(offsetof(GfComModel, unknown20) == 0x20, "");
static_assert(offsetof(GfComModel, unknown28) == 0x28, "");
static_assert(offsetof(GfComModel, unknown30) == 0x30, "");
static_assert(offsetof(GfComModel, unknown38) == 0x38, "");
static_assert(offsetof(GfComModel, unknown40) == 0x40, "");
static_assert(offsetof(GfComModel, unknown10c8) == 0x10c8, "");
static_assert(offsetof(GfComModel, unknown1140) == 0x1140, "");
static_assert(offsetof(GfComModel, unknown1168) == 0x1168, "");
static_assert(offsetof(GfComModel, m_modelScale) == 0x1190, "");
static_assert(offsetof(GfComModel, unknown1198) == 0x1198, "");
static_assert(offsetof(GfComModel, unknown11a8) == 0x11a8, "");
static_assert(sizeof(GfComModel) == 0x11b0, "");

} // namespace gf
