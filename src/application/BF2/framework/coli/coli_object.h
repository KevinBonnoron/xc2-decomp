#pragma once
#include <stddef.h>

#include "framework/pointer_map.h"
#include "framework/reference_frame.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace idcoli {
class IDColiObj;
} // namespace idcoli

namespace fw {

class ColiObject;
class UpdatableObject;
struct ColiCharacterInfo;
struct ColiPhantomInfo;

extern const u32 COLI_INVALID_DAMAGE_ID;

enum ColiType : int {
  COLI_TYPE_STATIC = 0,
};

enum ColiState : int {
  COLI_STATE_ENABLE = 1,
  COLI_STATE_INACTIVE = 2,
};

enum ColiAtrr : int;

class IColiEventListener {
public:
  struct EnterInfo;
  struct LeaveInfo;

  virtual void enter(const EnterInfo &info) = 0;
  virtual void leave(const LeaveInfo &info) = 0;
  virtual void contact(const EnterInfo &info);
};

struct IColiEventListener::EnterInfo {
  ColiObject *object;
  ColiObject *other;
  mm::Vec3 position;
  mm::Vec3 normal;
};

static_assert(offsetof(IColiEventListener::EnterInfo, position) == 0x10, "");
static_assert(sizeof(IColiEventListener::EnterInfo) == 0x30, "");

struct IColiEventListener::LeaveInfo {
  ColiObject *object;
  ColiObject *other;
};

struct ColiShape {
  enum Type {
    TYPE_SPHERE = 0,
    TYPE_CAPSULE = 1,
    TYPE_BOX = 2,
    TYPE_CHARACTER = 3,
  };

  Type unknown00; // Inferred role: type; original member name unknown.
  f32 unknown04;  // Inferred role: radius; original member name unknown.
  f32 unknown08;  // Inferred role: height; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  mm::Vec3 unknown10; // Inferred role: size; original member name unknown.
};

static_assert(offsetof(ColiShape, unknown10) == 0x10, "");

class ColiUserData {
public:
  static mm::mtl::RTTI m_rtti;

  virtual const mm::mtl::RTTI *getRTTI() const { return &m_rtti; }
  virtual ~ColiUserData() {}
};

class ColiObjUserData {
public:
  static mm::mtl::RTTI m_rtti;

  ColiObjUserData() : unknown08(0) {}
  virtual const mm::mtl::RTTI *getRTTI() const { return &m_rtti; }

  u32 unknown08; // Inferred role: handle; original member name unknown.
};

class ColiObject : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNode<ColiObject> {
public:
  static const u16 FLAG_MATRIX_DIRTY = 1 << 0;
  static const u32 EVENT_ENTER = 0;
  static const u32 EVENT_CONTACT = 1;
  static const u32 EVENT_LEAVE = 2;

  static mm::mtl::RTTI m_rtti;

  static ColiObject *createColiCharacter(const ColiCharacterInfo &info, const mm::mtl::IntrusivePtr<ReferenceFrame> &frame);
  static ColiObject *createColiGrand(const void *binary);
  static ColiObject *createColiPhantom(const ColiPhantomInfo &info, const mm::mtl::IntrusivePtr<ReferenceFrame> &frame);
  ColiObject();
  ~ColiObject();
  virtual const mm::mtl::RTTI *getRTTI() const { return &m_rtti; }
  virtual void update();
  virtual void postUpdate();
  virtual void setDir(const mm::Vec3 &direction) {}

  void setColiObject(idcoli::IDColiObj *object);
  void setHitMaterialFlag(u32 flag);
  void setColiType(ColiType type);
  void setPriority(int priority);
  void setMaterialFlag(u32 flag);
  void setState(ColiState state);
  void clearState(ColiState state);
  void bindReferenceFrame(const mm::mtl::IntrusivePtr<ReferenceFrame> &frame);
  void resetSphere(f32 radius);
  void resetCapsule(f32 radius, f32 height, bool flag);
  void resetBox(const mm::Vec3 &size, bool flag);
  void resetCharacter(f32 radius, f32 height);
  void setOwner(UpdatableObject *owner);
  UpdatableObject *getOwner() const;
  void setHandle(u32 handle);
  bool isChar() const;
  bool isPhantom() const;
  void setMatrix(const mm::Mat44 &matrix);
  void setInstantlyMatrix(const mm::Mat44 &matrix);
  const mm::Mat44 &getMatrix() const;
  int getPriority() const;
  bool isGrand() const;
  bool testAttribute(ColiAtrr attribute) const;
  bool testState(ColiState state) const;
  void setActivate(bool isActivate);
  bool isActivate() const;
  u32 getHitMaterialFlag() const;
  bool testHitMaterialFlag(u32 flag) const;
  u32 getMaterialFlag() const;
  void setAdsorption(f32 adsorption);
  f32 getAdsorption() const;
  bool isLanding() const;
  bool isContactWall() const;
  bool isOutRange() const;
  bool getAABB(mm::Vec3 &min, mm::Vec3 &max) const;
  void enter(const IColiEventListener::EnterInfo &info);
  void leave(const IColiEventListener::LeaveInfo &info);
  void contact(const IColiEventListener::EnterInfo &info);

  void setColiUserData(ColiUserData *data) { unknown58 = data; }

  void setListener(IColiEventListener *listener) {
    unknown48.clear();
    this->unknown50 = listener;
  }

  idcoli::IDColiObj *m_coliObject;
  mm::mtl::IntrusivePtr<ReferenceFrame> unknown28; // Inferred role: reference frame; original member name unknown.
  ColiType unknown30;                              // Inferred role: type; original member name unknown.
  u16 unknown34;                                   // Inferred role: flags; original member name unknown.
  HandlePtr<UpdatableObject> unknown38;            // Inferred role: owner; original member name unknown.
  mm::mtl::BitFlag<32> unknown48;                  // Inferred role: event flags; original member name unknown.
  IColiEventListener *unknown50;                   // Inferred role: listener; original member name unknown.
  ColiUserData *unknown58;                         // Inferred role: coli user data; original member name unknown.
  mm::Mat44 unknown60;                             // Inferred role: offset matrix; original member name unknown.
  mm::Mat44 m_matrix;
  f32 unknowne0;             // Inferred role: scale; original member name unknown.
  ColiShape *unknowne8;      // Inferred role: shape; original member name unknown.
  ColiObjUserData unknownf0; // Inferred role: user data; original member name unknown.
};

static_assert(offsetof(ColiObject, m_coliObject) == 0x20, "");
static_assert(offsetof(ColiObject, unknown30) == 0x30, "");
static_assert(offsetof(ColiObject, unknown38) == 0x38, "");
static_assert(offsetof(ColiObject, unknown50) == 0x50, "");
static_assert(offsetof(ColiObject, unknown58) == 0x58, "");
static_assert(offsetof(ColiObject, unknown60) == 0x60, "");
static_assert(offsetof(ColiObject, m_matrix) == 0xa0, "");
static_assert(offsetof(ColiObject, unknowne0) == 0xe0, "");
static_assert(offsetof(ColiObject, unknowne8) == 0xe8, "");
static_assert(offsetof(ColiObject, unknownf0) == 0xf0, "");
static_assert(sizeof(ColiObject) == 0x100, "");

class ColiMoveObject : public ColiObject {
public:
  static const u32 FLAG_ACCURACY = 1 << 1;

  static mm::mtl::RTTI m_rtti;

  static ColiObject *createColiCharacter(const ColiCharacterInfo &info, const mm::mtl::IntrusivePtr<ReferenceFrame> &frame);
  static ColiObject *createColiPhantom(const ColiPhantomInfo &info, const mm::mtl::IntrusivePtr<ReferenceFrame> &frame);
  ColiMoveObject();
  ~ColiMoveObject() {}
  const mm::mtl::RTTI *getRTTI() const override;
  void postUpdate() override;
  void setDir(const mm::Vec3 &direction) override;

  mm::Vec3 unknown100; // Inferred role: move direction; original member name unknown.
  u32 unknown110;      // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(ColiMoveObject, unknown100) == 0x100, "");
static_assert(offsetof(ColiMoveObject, unknown110) == 0x110, "");
static_assert(sizeof(ColiMoveObject) == 0x120, "");

} // namespace fw
