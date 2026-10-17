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
  virtual void contact(const EnterInfo &info) = 0;
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

  Type type;
  f32 radius;
  f32 height;
  u8 _0c[0x10 - 0x0c];
  mm::Vec3 size;
};

static_assert(offsetof(ColiShape, size) == 0x10, "");

class ColiUserData {
public:
  static mm::mtl::RTTI m_rtti;

  virtual const mm::mtl::RTTI *getRTTI() const { return &m_rtti; }
  virtual ~ColiUserData() {}
};

class ColiObjUserData {
public:
  static mm::mtl::RTTI m_rtti;

  ColiObjUserData() : handle(0) {}
  virtual const mm::mtl::RTTI *getRTTI() const { return &m_rtti; }

  u32 handle;
};

class ColiObject : public mm::mtl::ReferenceObject, public mm::mtl::IntrusiveListNode<ColiObject> {
public:
  static const u16 FLAG_MATRIX_DIRTY = 1 << 0;
  static const u32 EVENT_ENTER = 0;
  static const u32 EVENT_CONTACT = 1;
  static const u32 EVENT_LEAVE = 2;

  static mm::mtl::RTTI m_rtti;

  static ColiObject *createColiCharacter(const ColiCharacterInfo &info, const mm::mtl::IntrusivePtr<ReferenceFrame> &frame);
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

  void setColiUserData(ColiUserData *data) { coliUserData = data; }

  void setListener(IColiEventListener *listener) {
    eventFlags.clear();
    this->listener = listener;
  }

  idcoli::IDColiObj *coliObject;
  mm::mtl::IntrusivePtr<ReferenceFrame> referenceFrame;
  ColiType type;
  u16 flags;
  HandlePtr<UpdatableObject> owner;
  mm::mtl::BitFlag<32> eventFlags;
  IColiEventListener *listener;
  ColiUserData *coliUserData;
  mm::Mat44 offsetMatrix;
  mm::Mat44 matrix;
  f32 scale;
  ColiShape *shape;
  ColiObjUserData userData;
};

static_assert(offsetof(ColiObject, coliObject) == 0x20, "");
static_assert(offsetof(ColiObject, type) == 0x30, "");
static_assert(offsetof(ColiObject, owner) == 0x38, "");
static_assert(offsetof(ColiObject, listener) == 0x50, "");
static_assert(offsetof(ColiObject, coliUserData) == 0x58, "");
static_assert(offsetof(ColiObject, offsetMatrix) == 0x60, "");
static_assert(offsetof(ColiObject, matrix) == 0xa0, "");
static_assert(offsetof(ColiObject, scale) == 0xe0, "");
static_assert(offsetof(ColiObject, shape) == 0xe8, "");
static_assert(offsetof(ColiObject, userData) == 0xf0, "");
static_assert(sizeof(ColiObject) == 0x100, "");

class ColiMoveObject : public ColiObject {
public:
  static ColiObject *createColiCharacter(const ColiCharacterInfo &info, const mm::mtl::IntrusivePtr<ReferenceFrame> &frame);
  static ColiObject *createColiPhantom(const ColiPhantomInfo &info, const mm::mtl::IntrusivePtr<ReferenceFrame> &frame);
};

} // namespace fw
