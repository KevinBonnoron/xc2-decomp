#pragma once
#include <stddef.h>

#include "framework/pointer_map.h"
#include "framework/reference_frame.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/unique_ptr.h"
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

extern const u32 COLI_INVALID_DAMAGE_ID;

enum ColiType : int {
  COLI_TYPE_STATIC = 0,
  COLI_TYPE_UNKNOWN_1 = 1, // Inferred role: set by GfComBehaviorNpc::init while the npc moves on its own; original name unknown.
};

enum ColiState : int {
  COLI_STATE_UNKNOWN_0 = 0,
  COLI_STATE_ENABLE = 1,
  COLI_STATE_INACTIVE = 2,
};

enum ColiAtrr : int {
  COLI_ATRR_UNKNOWN_0 = 0, // Inferred role: tested by GfBehaviorEnemyField::update before applying gravity; original name unknown.
  COLI_ATRR_UNKNOWN_3 = 3, // Inferred role: tested by GfPropertyField::flush on the first collision of the pc; original name unknown.
};

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

// Inferred role: coli shape, the base of the sphere, capsule, box and character shapes; original type name unknown.
struct unknown031 {
  enum Type {
    TYPE_SPHERE = 0,
    TYPE_CAPSULE = 1,
    TYPE_BOX = 2,
    TYPE_CHARACTER = 3,
    TYPE_UNKNOWN_4 = 4,
    TYPE_UNKNOWN_5 = 5,
  };

  explicit unknown031(Type type) : unknown00(type) {}

  Type unknown00; // Inferred role: type; original member name unknown.
};

// Layout evidence for the shapes: ColiObject::setupColiCharacter (1.0.0: 0x710015cd90) allocates 8 bytes for a sphere,
// 0x10 for a capsule, 0x30 for a box and 0xc for a character, and GmkCollision::create reads the sizes before it
// stores the type.

// Inferred role: sphere coli shape; original type name unknown.
struct unknown131 : unknown031 {
  explicit unknown131(f32 radius) : unknown031(TYPE_SPHERE), unknown04(radius) {}

  f32 unknown04; // Inferred role: radius; original member name unknown.
};

// Inferred role: capsule coli shape; original type name unknown.
struct unknown132 : unknown031 {
  unknown132(f32 radius, f32 height) : unknown031(TYPE_CAPSULE), unknown04(radius), unknown08(height) {}

  f32 unknown04;  // Inferred role: radius; original member name unknown.
  f32 unknown08;  // Inferred role: height; original member name unknown.
  bool unknown0c; // Inferred role: flag passed to IDColiParmsCharacter::createCapsule; original member name unknown.
};

// Inferred role: size and flag of a box coli shape, copied as one member (setupColiCharacter reads the flag 0x10 bytes
// after the size); original type name unknown.
struct unknown137 {
  mm::Vec3 unknown00; // Inferred role: size; original member name unknown.
  bool unknown10;     // Inferred role: flag passed to IDColiParmsCharacter::createBox; original member name unknown.
};

// Inferred role: box coli shape; original type name unknown.
struct unknown133 : unknown031 {
  explicit unknown133(const mm::Vec3 &size) : unknown031(TYPE_BOX) { unknown10.unknown00 = size; }

  unknown137 unknown10; // Inferred role: size and flag; original member name unknown.
};

// Inferred role: character coli shape; original type name unknown.
struct unknown134 : unknown031 {
  f32 unknown04; // Inferred role: radius; original member name unknown.
  f32 unknown08; // Inferred role: height; original member name unknown.
};

// Inferred role: coli shape built from collision binary data; original type name unknown.
struct unknown135 : unknown031 {
  unknown135(Type type, const void *binary) : unknown031(type), unknown08(binary) {}

  const void *unknown08; // Inferred role: binary data; original member name unknown.
};

static_assert(offsetof(unknown131, unknown04) == 0x04, "");
static_assert(sizeof(unknown131) == 0x8, "");
static_assert(offsetof(unknown132, unknown0c) == 0x0c, "");
static_assert(sizeof(unknown132) == 0x10, "");
static_assert(offsetof(unknown133, unknown10) == 0x10, "");
static_assert(offsetof(unknown137, unknown10) == 0x10, "");
static_assert(sizeof(unknown137) == 0x20, "");
static_assert(sizeof(unknown133) == 0x30, "");
static_assert(offsetof(unknown134, unknown08) == 0x08, "");
static_assert(sizeof(unknown134) == 0xc, "");
static_assert(offsetof(unknown135, unknown08) == 0x08, "");
static_assert(sizeof(unknown135) == 0x10, "");

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

// Inferred role: event flags and listener of a coli object; setupColiCharacter and setupColiPhantom copy it from the
// create info as one 16-byte block. Original type name unknown.
struct unknown136 {
  unknown136() : unknown00(0), unknown08(nullptr) {}

  // Inferred role: tests one event bit; original name unknown.
  bool unknown001(u32 event) const { return ((1 << event) & unknown00) != 0; }

  u32 unknown00;                 // Inferred role: event flags, one bit per ColiObject::EVENT_*; original member name unknown.
  IColiEventListener *unknown08; // Inferred role: listener; original member name unknown.
};

static_assert(offsetof(unknown136, unknown08) == 0x08, "");
static_assert(sizeof(unknown136) == 0x10, "");

// Layout evidence: ColiObject::setupColiCharacter (1.0.0: 0x710015cd90) reads the coli type at 0x04, the priority at
// 0x08, the state bits at 0x0c, the material masks at 0x10 and 0x14, the scale at 0x18, the user data at 0x20, the
// event flags and listener at 0x28, the offset matrix at 0x40 and the shape at 0x80.
struct ColiCharacterInfo {
  ColiCharacterInfo() : unknown00(0), unknown10(0xfffffffa), unknown18(1.0f), unknown80(nullptr) { unknown40 = mm::Mat44::identity; }

  u32 unknown00;               // Role and original member name unknown.
  ColiType unknown04;          // Inferred role: coli type; original member name unknown.
  int unknown08;               // Inferred role: priority; original member name unknown.
  u32 unknown0c;               // Inferred role: state bits; original member name unknown.
  u32 unknown10;               // Inferred role: hit material mask; original member name unknown.
  u32 unknown14;               // Inferred role: material mask; original member name unknown.
  f32 unknown18;               // Inferred role: scale; original member name unknown.
  ColiUserData *unknown20;     // Inferred role: user data; original member name unknown.
  unknown136 unknown28;        // Inferred role: event flags and listener; original member name unknown.
  mm::Mat44 unknown40;         // Inferred role: offset matrix; original member name unknown.
  const unknown031 *unknown80; // Inferred role: shape; original member name unknown.
};

static_assert(offsetof(ColiCharacterInfo, unknown04) == 0x04, "");
static_assert(offsetof(ColiCharacterInfo, unknown10) == 0x10, "");
static_assert(offsetof(ColiCharacterInfo, unknown18) == 0x18, "");
static_assert(offsetof(ColiCharacterInfo, unknown20) == 0x20, "");
static_assert(offsetof(ColiCharacterInfo, unknown28) == 0x28, "");
static_assert(offsetof(ColiCharacterInfo, unknown40) == 0x40, "");
static_assert(offsetof(ColiCharacterInfo, unknown80) == 0x80, "");

// Layout evidence: ColiObject::setupColiPhantom (1.0.0: 0x710015d66c) reads the same offsets as setupColiCharacter.
struct ColiPhantomInfo {
  ColiPhantomInfo() : unknown00(1), unknown08(100), unknown0c(3), unknown10(0xfffffffa), unknown18(1.0f), unknown20(nullptr), unknown80(nullptr) { unknown40 = mm::Mat44::identity; }

  u32 unknown00;               // Role and original member name unknown.
  ColiType unknown04;          // Inferred role: coli type; original member name unknown.
  int unknown08;               // Inferred role: priority; original member name unknown.
  u32 unknown0c;               // Inferred role: state bits; original member name unknown.
  u32 unknown10;               // Inferred role: hit material mask; original member name unknown.
  u32 unknown14;               // Inferred role: material mask; original member name unknown.
  f32 unknown18;               // Inferred role: scale; original member name unknown.
  ColiUserData *unknown20;     // Inferred role: user data; original member name unknown.
  unknown136 unknown28;        // Inferred role: event flags and listener; original member name unknown.
  mm::Mat44 unknown40;         // Inferred role: offset matrix; original member name unknown.
  const unknown031 *unknown80; // Inferred role: shape; original member name unknown.
};

static_assert(offsetof(ColiPhantomInfo, unknown20) == 0x20, "");
static_assert(offsetof(ColiPhantomInfo, unknown40) == 0x40, "");
static_assert(offsetof(ColiPhantomInfo, unknown80) == 0x80, "");

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
  static void setupColiCharacter(ColiObject *object, const ColiCharacterInfo &info, const mm::mtl::IntrusivePtr<ReferenceFrame> &frame);
  static void setupColiPhantom(ColiObject *object, const ColiPhantomInfo &info, const mm::mtl::IntrusivePtr<ReferenceFrame> &frame);
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
    unknown48.unknown00 = 0;
    unknown48.unknown08 = listener;
  }

  idcoli::IDColiObj *m_coliObject;
  mm::mtl::IntrusivePtr<ReferenceFrame> unknown28; // Inferred role: reference frame; original member name unknown.
  ColiType unknown30;                              // Inferred role: type; original member name unknown.
  u16 unknown34;                                   // Inferred role: flags; original member name unknown.
  HandlePtr<UpdatableObject> unknown38;            // Inferred role: owner; original member name unknown.
  unknown136 unknown48;                            // Inferred role: event flags and listener; original member name unknown.
  ColiUserData *unknown58;                         // Inferred role: coli user data; original member name unknown.
  mm::Mat44 unknown60;                             // Inferred role: offset matrix; original member name unknown.
  mm::Mat44 m_matrix;
  f32 unknowne0;                            // Inferred role: scale; original member name unknown.
  mm::mtl::UniquePtr<unknown031> unknowne8; // Inferred role: shape; original member name unknown.
  ColiObjUserData unknownf0;                // Inferred role: user data; original member name unknown.
};

static_assert(offsetof(ColiObject, m_coliObject) == 0x20, "");
static_assert(offsetof(ColiObject, unknown30) == 0x30, "");
static_assert(offsetof(ColiObject, unknown38) == 0x38, "");
static_assert(offsetof(ColiObject, unknown48) == 0x48, "");
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
