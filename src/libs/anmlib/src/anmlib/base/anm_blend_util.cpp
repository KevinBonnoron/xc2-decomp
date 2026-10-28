#include "anm/anm_blend_util.h"

#include <math.h>

#include "anm/anm_array-inl.h"
#include "anm/anm_qs_transform.h"
#include "anm/anm_skeleton.h"
#include "anm/anm_transform_util.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec4.h"

namespace anm {

void BlendUtil::blendNormal(const BlendSrc &src, BlendNormalDst *dst) {
  for (u32 i = 0; i < src.unknown00; i++) {
    f32 weight = src.unknown18 * src.unknown10[i];
    if (weight > 0.0f) {
      const QsTransform &source = src.unknown08[i];
      QsTransform &destination = dst->unknown00[i];
      mm::Vec4 translation = source.unknown00;
      destination.unknown00.x = weight * translation.x + destination.unknown00.x;
      destination.unknown00.y = weight * translation.y + destination.unknown00.y;
      destination.unknown00.z = weight * translation.z + destination.unknown00.z;
      destination.unknown00.w = weight * translation.w + destination.unknown00.w;
      mm::Vec4 scale = source.unknown20;
      destination.unknown20.x = weight * scale.x + destination.unknown20.x;
      destination.unknown20.y = weight * scale.y + destination.unknown20.y;
      destination.unknown20.z = weight * scale.z + destination.unknown20.z;
      destination.unknown20.w = weight * scale.w + destination.unknown20.w;
      mm::Quat rotation = source.unknown10;
      f32 dot = rotation.x * destination.unknown10.x + rotation.y * destination.unknown10.y + rotation.z * destination.unknown10.z + rotation.w * destination.unknown10.w;
      f32 sign = dot >= 0.0f ? 1.0f : -1.0f;
      f32 x = rotation.x * sign;
      f32 y = rotation.y * sign;
      f32 z = rotation.z * sign;
      f32 w = rotation.w * sign;
      x = weight * x;
      y = weight * y;
      z = weight * z;
      w = weight * w;
      destination.unknown10.x = destination.unknown10.x + x;
      destination.unknown10.y = destination.unknown10.y + y;
      destination.unknown10.z = destination.unknown10.z + z;
      destination.unknown10.w = destination.unknown10.w + w;
    }
    dst->unknown08[i] = weight + dst->unknown08[i];
  }
}

void BlendUtil::normalizePose(const NormalizeSrc &src, QsTransform *poses) {
  for (u32 i = 0; i < src.unknown00; i++) {
    f32 weight = src.unknown10[i];
    if (weight == 0.0f) {
      poses[i] = src.unknown08[i];
    } else {
      f32 inverse = 1.0f / weight;
      QsTransform &pose = poses[i];
      pose.unknown00.x = inverse * pose.unknown00.x;
      pose.unknown00.y = inverse * pose.unknown00.y;
      pose.unknown00.z = inverse * pose.unknown00.z;
      pose.unknown00.w = inverse * pose.unknown00.w;
      pose.unknown20.x = inverse * pose.unknown20.x;
      pose.unknown20.y = inverse * pose.unknown20.y;
      pose.unknown20.z = inverse * pose.unknown20.z;
      pose.unknown20.w = inverse * pose.unknown20.w;
      f32 x = inverse * pose.unknown10.x;
      pose.unknown10.x = x;
      f32 y = inverse * pose.unknown10.y;
      pose.unknown10.y = y;
      f32 z = inverse * pose.unknown10.z;
      pose.unknown10.z = z;
      f32 w = inverse * pose.unknown10.w;
      f32 lengthSquared = x * x + y * y + z * z + w * w;
      pose.unknown10.w = w;
      f32 length = sqrtf(lengthSquared);
      f32 inverseLength = 1.0f / length;
      pose.unknown10.x = pose.unknown10.x * inverseLength;
      pose.unknown10.y = inverseLength * pose.unknown10.y;
      pose.unknown10.z = inverseLength * pose.unknown10.z;
      pose.unknown10.w = inverseLength * pose.unknown10.w;
    }
  }
}

void BlendUtil::normalizePoseMS(const NormalizeMSSrc &src, QsTransform *poses) {
  const Skeleton *skeleton = src.unknown00;
  u32 boneCount = skeleton->getBoneCount();
  for (u32 i = 0; i < boneCount; i++) {
    f32 weight = src.unknown08[i];
    if (weight == 0.0f) {
      s16 parent = skeleton->unknown003(i);
      if (parent == -1) {
        poses[i] = skeleton->unknown40[i];
      } else {
        TransformUtil::mul(poses[parent], skeleton->unknown40[i], &poses[i]);
      }
    } else {
      f32 inverse = 1.0f / weight;
      QsTransform &pose = poses[i];
      pose.unknown00.x = inverse * pose.unknown00.x;
      pose.unknown00.y = inverse * pose.unknown00.y;
      pose.unknown00.z = inverse * pose.unknown00.z;
      pose.unknown00.w = inverse * pose.unknown00.w;
      pose.unknown20.x = inverse * pose.unknown20.x;
      pose.unknown20.y = inverse * pose.unknown20.y;
      pose.unknown20.z = inverse * pose.unknown20.z;
      pose.unknown20.w = inverse * pose.unknown20.w;
      f32 x = inverse * pose.unknown10.x;
      f32 y = inverse * pose.unknown10.y;
      f32 z = inverse * pose.unknown10.z;
      f32 w = inverse * pose.unknown10.w;
      pose.unknown10.x = x;
      pose.unknown10.y = y;
      pose.unknown10.z = z;
      pose.unknown10.w = w;
      f32 length = sqrtf(x * x + y * y + z * z + w * w);
      f32 inverseLength = 1.0f / length;
      pose.unknown10.x = pose.unknown10.x * inverseLength;
      pose.unknown10.y = inverseLength * pose.unknown10.y;
      pose.unknown10.z = inverseLength * pose.unknown10.z;
      pose.unknown10.w = inverseLength * pose.unknown10.w;
    }
  }
}

void BlendUtil::blendNormalExtraTruck(const BlendExtraTruckSrc &src, BlendNormalExtraTruckDst *dst) {
  for (u32 i = 0; i < src.unknown00; i++) {
    if ((*src.unknown10)[i] != -1) {
      dst->unknown00[i] += src.unknown18 * src.unknown08[i];
      dst->unknown08[i] += src.unknown18;
    }
  }
}

void BlendUtil::blendAddExtraTruck(const BlendExtraTruckSrc &src, BlendAddExtraTruckDst *dst) {
  for (u32 i = 0; i < src.unknown00; i++) {
    if ((*src.unknown10)[i] != -1) {
      dst->unknown00[i] += src.unknown18 * src.unknown08[i];
    }
  }
}

void BlendUtil::normalizeExtraTruck(const NormalizeExtraTruckSrc &src, f32 *values) {
  MM_ASSERT(src.pSlot);
  for (u32 i = 0; i < src.unknown00; i++) {
    f32 weight = src.unknown10[i];
    if (weight <= 0.0f) {
      values[i] = (*src.unknown08)[i];
    } else if (weight > 1.0f) {
      values[i] = values[i] / weight;
    }
  }
}

} // namespace anm
