#include "anm/anm_reference_pose_animation.h"

#include "anm/anm_array-inl.h"
#include "anm/anm_binding.h"
#include "anm/anm_qs_transform.h"
#include "anm/anm_reference_object.h"
#include "anm/anm_skeleton.h"

namespace anm {

ReferencePoseAnimation::ReferencePoseAnimation(const Skeleton *skeleton, mm::mtl::IAllocator *pAllocator) : Animation(pAllocator), unknown48(skeleton) {
  skeleton->addRef();
  unknown20 = -4;
  unknown18 = "reference_pose";
  unknown22 = 1;
  unknown23 = 0;
  unknown24 = 30.0f;
  unknown28 = 0.033333335f;
  unknown2c = 1;
  unknown30 = nullptr;
  unknown38 = 0;
  unknown40 = nullptr;
}

ReferencePoseAnimation::~ReferencePoseAnimation() { unknown001(unknown48); }

void ReferencePoseAnimation::sampleTrucks(f32 time, const Binding &binding, QsTransform *transforms) const {
  u32 count = binding.m_indexTable.size();
  if (count != 0) {
    const Array<QsTransform> referencePose = unknown48->unknown40;
    for (u32 i = 0; i < count; i++) {
      s16 index = binding.m_indexTable[i];
      if (index >= 0) {
        transforms[i] = referencePose[index];
      }
    }
  }
}

s32 ReferencePoseAnimation::getImplType() const { return -4; }

} // namespace anm
