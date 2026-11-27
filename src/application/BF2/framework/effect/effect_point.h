#pragma once
#include <stddef.h>

#include "framework/reference_frame.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
}
} // namespace mm

namespace fw {

class ModelObject;
struct UpdateInfo;

// The vtable of two destructor slots and a reference count at 0x08. EffectPoint does not derive from
// mm::mtl::ReferenceObject: EffectCasterBase::~EffectCasterBase asserts "m_RefCount >= 0" at effect_point.h line 0x66
// (102) when it releases its point, not reference_object.h's "m_RefCount > 0" at line 0x3c. The ctor zeroes the u32 at
// 0x08 before the vtable store (1.0.0: 0x7100178128). The members from 0x60 are copied by the ctor from its EfpInitData
// argument, whose caller GfComEffectCaster binds the delegates.
// Layout evidence: GfComEffectCaster::setupEfp (0x7100506134) builds it at sp+8 and passes it to the
// EffectPoint constructor at 0x7100506298. The type is in namespace fw: the mangled constructor symbol
// _ZN2fw11EffectPointC2ERKNS_11EfpInitDataE names it there. Original member names unknown.
struct EfpInitData {
  EfpInitData() : unknown08(0), unknown10(nullptr), unknown18(nullptr), unknown20(nullptr) {}

  u32 unknown00;                                                                    // Inferred role: layer, copied from SetupInfo::unknown10; original member name unknown.
  f32 unknown04;                                                                    // Inferred role: set to 1.0 by setupEfp, role unknown; original member name unknown.
  u32 unknown08;                                                                    // Inferred role: asset data size; original member name unknown.
  u32 unknown0c;                                                                    // Inferred role: not written by setupEfp; original member name unknown.
  const void *unknown10;                                                            // Inferred role: asset data; original member name unknown.
  mm::mtl::IAllocator *unknown18;                                                   // Inferred role: allocator; original member name unknown.
  ModelObject *unknown20;                                                           // Inferred role: model object; original member name unknown.
  mm::mtl::Delegate<mm::mtl::IntrusivePtr<ReferenceFrame>(const char *)> unknown28; // Inferred role: bone frame getter; original member name unknown.
  mm::mtl::Delegate<void(const char *)> unknown48;                                  // Inferred role: bone frame releaser; original member name unknown.
};

class EffectPoint {
public:
  explicit EffectPoint(const EfpInitData &init);

  struct Param {
    mm::Mat44 unknown00;                             // Inferred role: offset matrix; original member name unknown.
    mm::Vec3 unknown40;                              // Inferred role: scale; original member name unknown.
    mm::mtl::IntrusivePtr<ReferenceFrame> unknown50; // Inferred role: parent reference frame; original member name unknown.
    mm::mtl::FixStr<32> unknown58;                   // Inferred role: name; original member name unknown.
    u32 unknown7c;                                   // Inferred role: name hash; original member name unknown.
    mm::mtl::FixStr<32> unknown80;                   // Inferred role: parent name; original member name unknown.
    s32 unknowna4;                                   // Inferred role: parent bone index; original member name unknown.
    bool unknowna8;                                  // Inferred role: dirty; original member name unknown.
  };

  virtual ~EffectPoint();
  // Inferred role: reference count helpers; original names unknown (only m_RefCount and the assert text are given by the game).
  void unknown001() { m_RefCount++; }

  // __LINE__ must be 102 as in the original header: the #line below makes the MM_ASSERT in the body line 102.
#line 101
  void unknown002() {
    MM_ASSERT(m_RefCount >= 0);
    if (--m_RefCount == 0) {
      delete this;
    }
  }

  int getPointCount() const;
  int getPointIndex(const char *name) const;
  const char *getPointName(int index) const;
  const mm::Mat44 &getPointTransform(int index) const;
  const mm::Vec3 &getScale(int index) const;
  bool isDirty(u32 index);
  void setDirty(u32 index, bool isDirty);
  const char *getParentName(const char *name);
  mm::Mat44 getOffset(const char *name);
  void update(const UpdateInfo &info);
  void calcPoint(Param &param, mm::Mat44 &matrix) const;

  int m_RefCount;
  u32 unknown0c;                        // Inferred role: layer; original member name unknown.
  mm::mtl::Vector<Param> unknown10;     // Inferred role: points; original member name unknown.
  mm::mtl::Vector<mm::Mat44> unknown38; // Inferred role: point transforms; original member name unknown.
  ModelObject *unknown60;               // Inferred role: model; original member name unknown.
  // Inferred role: returns the reference frame of a parent name; original member name unknown.
  mm::mtl::Delegate<mm::mtl::IntrusivePtr<ReferenceFrame>(const char *)> unknown68;
  // Inferred role: releases the reference frame of a parent name; original member name unknown.
  mm::mtl::Delegate<void(const char *)> unknown88;
};

static_assert(offsetof(EfpInitData, unknown08) == 0x08, "");
static_assert(offsetof(EfpInitData, unknown10) == 0x10, "");
static_assert(offsetof(EfpInitData, unknown18) == 0x18, "");
static_assert(offsetof(EfpInitData, unknown20) == 0x20, "");
static_assert(offsetof(EfpInitData, unknown28) == 0x28, "");
static_assert(offsetof(EfpInitData, unknown48) == 0x48, "");
static_assert(sizeof(EfpInitData) == 0x68, "");
static_assert(sizeof(EffectPoint::Param) == 0xb0, "");
static_assert(offsetof(EffectPoint::Param, unknown50) == 0x50, "");
static_assert(offsetof(EffectPoint::Param, unknown58) == 0x58, "");
static_assert(offsetof(EffectPoint::Param, unknown7c) == 0x7c, "");
static_assert(offsetof(EffectPoint::Param, unknown80) == 0x80, "");
static_assert(offsetof(EffectPoint::Param, unknowna4) == 0xa4, "");
static_assert(offsetof(EffectPoint::Param, unknowna8) == 0xa8, "");
static_assert(offsetof(EffectPoint, m_RefCount) == 0x08, "");
static_assert(offsetof(EffectPoint, unknown0c) == 0x0c, "");
static_assert(offsetof(EffectPoint, unknown10) == 0x10, "");
static_assert(offsetof(EffectPoint, unknown38) == 0x38, "");
static_assert(offsetof(EffectPoint, unknown60) == 0x60, "");
static_assert(offsetof(EffectPoint, unknown68) == 0x68, "");
static_assert(offsetof(EffectPoint, unknown88) == 0x88, "");
static_assert(sizeof(EffectPoint) == 0xa8, "");

} // namespace fw
