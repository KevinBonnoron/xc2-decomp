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

// Inferred role: object collision enter message; original type name unknown.
struct unknown095 : fw::Message {
  unknown095() : fw::Message(MSG_OBJECT_COLI_ENTER, 0x40), unknown08(reinterpret_cast<GF_OBJ_HANDLE *>(-1)), unknown10(nullptr) {}

  GF_OBJ_HANDLE *unknown08;                           // Inferred role: handle; original member name unknown.
  const fw::IColiEventListener::EnterInfo *unknown10; // Inferred role: info; original member name unknown.
};

// Inferred role: object collision leave message; original type name unknown.
struct unknown096 : fw::Message {
  unknown096() : fw::Message(MSG_OBJECT_COLI_LEAVE, 0x40), unknown08(reinterpret_cast<GF_OBJ_HANDLE *>(-1)), unknown10(nullptr) {}

  GF_OBJ_HANDLE *unknown08;                           // Inferred role: handle; original member name unknown.
  const fw::IColiEventListener::LeaveInfo *unknown10; // Inferred role: info; original member name unknown.
};

// Inferred role: object collision contact message; original type name unknown.
struct unknown097 : fw::Message {
  unknown097() : fw::Message(MSG_OBJECT_COLI_CONTACT, 0x40), unknown08(reinterpret_cast<GF_OBJ_HANDLE *>(-1)), unknown10(nullptr) {}

  GF_OBJ_HANDLE *unknown08;                           // Inferred role: handle; original member name unknown.
  const fw::IColiEventListener::EnterInfo *unknown10; // Inferred role: info; original member name unknown.
};

static_assert(offsetof(unknown095, unknown08) == 0x08, "");
static_assert(offsetof(unknown095, unknown10) == 0x10, "");

class GfComCollider : public GfComponent, public fw::IColiEventListener {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 4;

  class UserData : public fw::ColiUserData {
  public:
    static mm::mtl::RTTI m_rtti;

    UserData() : unknown08(nullptr) {}
    const mm::mtl::RTTI *getRTTI() const override;

    GfComCollider *unknown08; // Inferred role: owner; original member name unknown.
  };

  GfComCollider();
  ~GfComCollider() override;
  void cleanup();
  void createColiCharacter(u32 index, const fw::ColiCharacterInfo &info, mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame);
  template <typename Info, typename Creator> void createColi(const Creator &creator, u32 index, const Info &info, mm::mtl::IntrusivePtr<fw::ReferenceFrame> &frame);
  void createColiMoveCharacter(u32 index, const fw::ColiCharacterInfo &info, mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame);
  void createColiPhantom(u32 index, const fw::ColiPhantomInfo &info, mm::mtl::IntrusivePtr<fw::ReferenceFrame> frame);
  void enter(const EnterInfo &info) override;
  void leave(const LeaveInfo &info) override;
  void contact(const EnterInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;
  void changeLayer(u32 oldLayer, u32 newLayer) override;

  mm::mtl::Vector<fw::ColiObject *> unknown18; // Inferred role: colis; original member name unknown.
  UserData unknown40;                          // Inferred role: user data; original member name unknown.
  fw::AnimColPoseModifier unknown50;           // Inferred role: pose modifier; original member name unknown.
};

static_assert(offsetof(GfComCollider, unknown18) == 0x18, "");
static_assert(offsetof(GfComCollider, unknown40) == 0x40, "");
static_assert(offsetof(GfComCollider, unknown50) == 0x50, "");

} // namespace gf
