#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "anm/anm_reference_object.h"
#include "anm/anm_skeleton.h"
#include "mm_mtl/reserved_bitflag.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
struct Mat44;
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

struct QsTransform;

class Pose : public ReferenceObject {
public:
  enum PROPAGATE_TYPE : int {
    PROPAGATE_TYPE_UNKNOWN_0 = 0,
    PROPAGATE_TYPE_UNKNOWN_1 = 1,
  };

  // Inferred role: bone flags; original name unknown (the asserts only name its values).
  enum unknown003 {
    BONE_LOCAL_SPACE_DIRTY,
    BONE_MODEL_SPACE_DIRTY,
    BONE_UNKNOWN_2,
  };

  Pose(const Skeleton *skeleton, mm::mtl::IAllocator *allocator);
  ~Pose() override;
  void syncLocalSpace();
  void syncModelSpace();
  void setReferencePose();
  Array<QsTransform> &accessSyncedPoseLocalSpace();
  Array<QsTransform> &accessSyncedPoseModelSpace();
  const QsTransform &getBoneModelSpace(u16 bone);
  const QsTransform &getBoneLocalSpace(u16 bone);
  QsTransform &accessBoneLocalSpace(u16 bone);
  QsTransform &accessBoneModelSpace(u16 bone, PROPAGATE_TYPE propagate);
  QsTransform &calcBoneModelSpace(u16 bone);
  void setBoneLocalSpace(u16 bone, const QsTransform &transform);
  void setBoneModelSpace(u16 bone, const QsTransform &transform, PROPAGATE_TYPE propagate);
  void makeAllChildrenLocalSpace(u16 bone);
  void makeAllChildrenModelSpace(u16 bone);
  void validateBone();
  void calcMatrixModelSpace(u16 bone, mm::Mat44 *matrix);

  bool testBoneFlag(u16 boneID, unknown003 flag) const {
    u32 index = flag * unknown18->unknown30.size() + boneID;
    return unknown70.getLocal(index);
  }

  // Inferred helper: sets or clears one flag of a bone; original name unknown.
  void unknown002(u16 boneID, unknown003 flag, bool value) {
    u32 index = flag * unknown18->unknown30.size() + boneID;
    unknown70.setLocal(index, value);
  }

  const Skeleton *unknown18;              // Inferred role: skeleton (the game asserts on a member it names m_pSkeleton); original member name unknown.
  mm::mtl::Vector<QsTransform> unknown20; // Inferred role: local pose; original member name unknown.
  mm::mtl::Vector<QsTransform> unknown48; // Inferred role: model pose; original member name unknown.
  mm::mtl::ReservedBitflag unknown70;     // Inferred role: bone flags (local dirty, model dirty, unknown) per bone; original member name unknown.
  u32 unknown88;                          // Inferred role: synced flags (bit 0 local, bit 1 model); original member name unknown.
};

static_assert(offsetof(Pose, unknown18) == 0x18, "");
static_assert(offsetof(Pose, unknown20) == 0x20, "");
static_assert(offsetof(Pose, unknown48) == 0x48, "");
static_assert(offsetof(Pose, unknown70) == 0x70, "");
static_assert(offsetof(Pose, unknown88) == 0x88, "");
static_assert(sizeof(Pose) == 0x90, "");

} // namespace anm
