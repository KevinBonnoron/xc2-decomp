#pragma once
#include <stddef.h>

#include "framework/anim/anim_col_pose_modifier.h"
#include "framework/coli/coli_object.h"
#include "framework/message/message_object.h"
#include "gf/object/component/gf_component.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace fw {
class ReferenceFrame;
struct ColiCharacterInfo;
struct ColiPhantomInfo;
} // namespace fw
namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;

enum {
  MSG_OBJECT_COLI_ENTER = 0x100003c,
  MSG_OBJECT_COLI_LEAVE = 0x100003d,
  MSG_OBJECT_COLI_CONTACT = 0x100003e,
};

struct MsgObjectColiEnter : fw::Message {
  MsgObjectColiEnter() : fw::Message(MSG_OBJECT_COLI_ENTER, 0x40), handle(reinterpret_cast<GF_OBJ_HANDLE *>(-1)), info(nullptr) {}

  GF_OBJ_HANDLE *handle;
  const fw::IColiEventListener::EnterInfo *info;
};

struct MsgObjectColiLeave : fw::Message {
  MsgObjectColiLeave() : fw::Message(MSG_OBJECT_COLI_LEAVE, 0x40), handle(reinterpret_cast<GF_OBJ_HANDLE *>(-1)), info(nullptr) {}

  GF_OBJ_HANDLE *handle;
  const fw::IColiEventListener::LeaveInfo *info;
};

struct MsgObjectColiContact : fw::Message {
  MsgObjectColiContact() : fw::Message(MSG_OBJECT_COLI_CONTACT, 0x40), handle(reinterpret_cast<GF_OBJ_HANDLE *>(-1)), info(nullptr) {}

  GF_OBJ_HANDLE *handle;
  const fw::IColiEventListener::EnterInfo *info;
};

static_assert(offsetof(MsgObjectColiEnter, handle) == 0x08, "");
static_assert(offsetof(MsgObjectColiEnter, info) == 0x10, "");

class GfComCollider : public GfComponent, public fw::IColiEventListener {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 4;

  class UserData : public fw::ColiUserData {
  public:
    static mm::mtl::RTTI m_rtti;

    UserData() : owner(nullptr) {}
    const mm::mtl::RTTI *getRTTI() const override;

    GfComCollider *owner;
  };

  GfComCollider();
  ~GfComCollider() override;
  void cleanup();
  void createColiCharacter(u32 index, const fw::ColiCharacterInfo &info, mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame);
  template <typename Info, typename Creator>
  void createColi(const Creator &creator, u32 index, const Info &info, mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame);
  void createColiMoveCharacter(u32 index, const fw::ColiCharacterInfo &info, mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame);
  void createColiPhantom(u32 index, const fw::ColiPhantomInfo &info, mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame);
  void enter(const EnterInfo &info) override;
  void leave(const LeaveInfo &info) override;
  void contact(const EnterInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;
  void changeLayer(u32 oldLayer, u32 newLayer) override;

  mm::mtl::Vector<fw::ColiObject *> colis;
  UserData userData;
  fw::AnimColPoseModifier poseModifier;
};

static_assert(offsetof(GfComCollider, colis) == 0x18, "");
static_assert(offsetof(GfComCollider, userData) == 0x40, "");
static_assert(offsetof(GfComCollider, poseModifier) == 0x50, "");

} // namespace gf
