#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace anm {
class ResASM;
} // namespace anm

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

struct EffectAnnotationData {
  EffectAnnotationData(const EffectAnnotationData &other)
      : unknown00(other.unknown00), unknown24(other.unknown24), unknown28(other.unknown28), unknown4c(other.unknown4c), unknown54(other.unknown54), unknown78(other.unknown78),
        unknown9c(other.unknown9c), unknownc0(other.unknownc0), unknownd0(other.unknownd0), unknowne0(other.unknowne0), unknownf0(other.unknownf0) {}

  // Inferred helper types: the copy constructor copies these members as plain blocks; original names unknown.
  // The members are named by their offset in the block; their roles come from the readers (see the comments).
  struct unknown001 {
    u32 unknown00;
    f32 unknown04; // Inferred role: life time (GfComEffectCaster::callbackImpl 0x7100508db8 reads it at 0x50); original member name unknown.
  };

  struct unknown002 {
    u32 unknown00;
    f32 unknown04; // Inferred role: scale (GfComEffectCaster::callbackImpl reads it at 0xc4); original member name unknown.
    u32 unknown08;
  };

  // Layout from GfComEffectCaster::procMessageAsmCallback (0x710050354c), callbackImpl (0x7100508db8) and
  // procMsgFxForceCancel (0x7100503888), which read it at 0xf4-0x114 of the annotation.
  struct unknown003 {
    u32 unknown00;
    u8 unknown04; // Inferred role: setup flag; original member name unknown.
    u8 unknown05; // Inferred role: setup flag; original member name unknown.
    u8 _06[0x08 - 0x06];
    u8 unknown08;  // Inferred role: flag procMsgFxForceCancel tests (ldrb at 0x7100503934) with the effect handle before it ends the effect; original member name unknown.
    u8 unknown09;  // Inferred role: setup flag; original member name unknown.
    u16 unknown0a; // Inferred role: two setup flags (the scale is absolute when the high byte is set); original member name unknown.
    u8 _0c[0x14 - 0x0c];
    s32 unknown14; // Inferred role: caster type; original member name unknown.
    u16 unknown18; // Inferred role: caster type of the effect; original member name unknown.
    u16 unknown1a; // Inferred role: setup value; original member name unknown.
    u32 unknown1c; // Inferred role: started effect handle; original member name unknown.
    u8 _20[0x24 - 0x20];
    u32 unknown24; // Inferred role: setup value read as 32 bits, its low byte goes to EffectSetUp::unknown4f (callbackImpl 0x7100508fb8); original member name unknown.
  };

  // Inferred layout from the copy constructor at 0x7100169b84; original member names unknown.
  mm::mtl::FixStr<32> unknown00;
  u32 unknown24;
  mm::mtl::FixStr<32> unknown28;
  unknown001 unknown4c;
  mm::mtl::FixStr<32> unknown54;
  mm::mtl::FixStr<32> unknown78;
  mm::mtl::FixStr<32> unknown9c;
  unknown002 unknownc0;
  u32 unknowncc;      // Inferred role: not copied by the copy constructor; original member name unknown.
  mm::Vec3 unknownd0; // Inferred role: offset; the fourth component is not copied by the copy constructor; original member name unknown.
  mm::Vec3 unknowne0; // Inferred role: second vector; the fourth component is not copied by the copy constructor; original member name unknown.
  unknown003 unknownf0;
  u8 unknown118[0x120 - 0x118]; // Inferred role: not copied by the copy constructor; original member names unknown.
};

struct EffectAnnotationTbl {
  u8 unknown00[0x118]; // Inferred role: annotation table record of 0x118 bytes; original member names unknown.
};

class EffectResData : public mm::mtl::ReferenceObject {
public:
  // Inferred role: setup tbl; original type name unknown.
  struct unknown004 {
    EffectAnnotationTbl *unknown00; // Inferred role: annotation tables; original member name unknown.
    u32 unknown08;                  // Inferred role: tables size in bytes; original member name unknown.
  };

  struct SetupInfo {
    mm::mtl::IAllocator *unknown00;                 // Inferred role: allocator; original member name unknown.
    mm::mtl::FixedVector<unknown004, 53> unknown08; // Inferred role: annotation tables; original member name unknown.
  };

  explicit EffectResData(mm::mtl::IAllocator *allocator);
  ~EffectResData() override;
  static EffectResData *createEffectResData(const SetupInfo &info);
  void init(const SetupInfo &info);
  void term();
  void registerAsmAnnotation(anm::ResASM *resAsm, u32 type, const char *name);

  mm::mtl::Vector<EffectAnnotationData> unknown10; // Inferred role: annotations; original member name unknown.
};

static_assert(offsetof(EffectAnnotationData, unknown24) == 0x24, "");
static_assert(offsetof(EffectAnnotationData, unknown28) == 0x28, "");
static_assert(offsetof(EffectAnnotationData, unknown4c) == 0x4c, "");
static_assert(offsetof(EffectAnnotationData, unknown54) == 0x54, "");
static_assert(offsetof(EffectAnnotationData, unknown78) == 0x78, "");
static_assert(offsetof(EffectAnnotationData, unknown9c) == 0x9c, "");
static_assert(offsetof(EffectAnnotationData, unknownc0) == 0xc0, "");
static_assert(offsetof(EffectAnnotationData, unknownd0) == 0xd0, "");
static_assert(offsetof(EffectAnnotationData, unknowne0) == 0xe0, "");
static_assert(offsetof(EffectAnnotationData, unknownf0) == 0xf0, "");
static_assert(offsetof(EffectAnnotationData::unknown003, unknown05) == 0x05, "");
static_assert(offsetof(EffectAnnotationData::unknown003, unknown08) == 0x08, "");
static_assert(offsetof(EffectAnnotationData::unknown003, unknown0a) == 0x0a, "");
static_assert(offsetof(EffectAnnotationData::unknown003, unknown14) == 0x14, "");
static_assert(offsetof(EffectAnnotationData::unknown003, unknown1c) == 0x1c, "");
static_assert(offsetof(EffectAnnotationData::unknown003, unknown24) == 0x24, "");
static_assert(sizeof(EffectAnnotationData::unknown003) == 0x28, "");
static_assert(sizeof(EffectAnnotationData) == 0x120, "");
static_assert(sizeof(EffectAnnotationTbl) == 0x118, "");
static_assert(sizeof(EffectResData::unknown004) == 0x10, "");
static_assert(offsetof(EffectResData::SetupInfo, unknown08) == 0x08, "");
static_assert(sizeof(EffectResData::SetupInfo) == 0x360, "");
static_assert(offsetof(EffectResData, unknown10) == 0x10, "");
static_assert(sizeof(EffectResData) == 0x38, "");

} // namespace fw
