#pragma once
#include <stddef.h>

#include "event/attach_actor_base.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {
enum ATTACH_TYPE : int;

class AttachActorCS : public AttachActorBase {
public:
  static constexpr u32 EFFECT_COUNT = 128;

  struct Mount {
    Mount(u32 effect, const char *bone, mm::Vec3 offset, bool isRotate, ATTACH_TYPE type) : unknown0(effect), unknown8(bone), unknown30(offset), unknown40(isRotate), unknown44(type) {}

    // Inferred record layout; original type and member names are unknown.
    u32 unknown0;                 // Effect identifier.
    mm::mtl::FixStr<32> unknown8; // Bone name.
    mm::Vec3 unknown30;           // Offset.
    bool unknown40;               // Rotation enabled.
    ATTACH_TYPE unknown44;        // Attachment type.
  };

  AttachActorCS(const char *name);
  virtual ~AttachActorCS();
  void setActor(gf::GF_OBJ_HANDLE *actor);
  void render();
  virtual void setEffectCaster(bool isSet, u32 effect);
  virtual void setEffectMount(bool isSet, u32 effect, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type);
  virtual bool getMtpMat(mm::Mat44 &mat, const char *name) const;
  virtual bool getEfpMat(mm::Mat44 &mat, const char *name) const;
  virtual bool getBoneMat(mm::Mat44 &mat, const char *name) const;
  void setTransform(const mm::Mat44 &transform);

private:
  // Inferred roles from access offsets; original member names are unknown.
  gf::GF_OBJ_HANDLE *unknowna0;                           // Owner handle.
  mm::mtl::FixedVector<u32 *, EFFECT_COUNT> unknowna8;    // Caster identifiers.
  mm::mtl::FixedVector<Mount *, EFFECT_COUNT> unknown4b0; // Mount records.
};

static_assert(offsetof(AttachActorCS::Mount, unknown30) == 0x30, "");
static_assert(offsetof(AttachActorCS::Mount, unknown44) == 0x44, "");
static_assert(sizeof(AttachActorCS) == 0x8c0, "");

} // namespace event
