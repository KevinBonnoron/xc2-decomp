#include "anm/anm_transform_util.h"

#include "anm/anm_qs_transform.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec4.h"
#include "types.h"

namespace anm {

void TransformUtil::mul(const QsTransform &lhs, const QsTransform &rhs, QsTransform *result) {
  const mm::Quat &q = lhs.unknown10;
  const mm::Vec4 &v = rhs.unknown00;
  f32 tx = (q.y * v.z - q.z * v.y) + q.w * v.x;
  f32 ty = (q.z * v.x - v.z * q.x) + v.y * q.w;
  f32 tz = (v.y * q.x - q.y * v.x) + v.z * q.w;
  f32 tw = (-(v.x * q.x) - q.y * v.y) - v.z * q.z;
  f32 rx = -(q.z * ty) + q.y * tz - q.x * tw + q.w * tx;
  f32 ry = -(q.x * tz) + q.z * tx - q.y * tw + q.w * ty;
  f32 rz = -(q.y * tx) + q.x * ty - q.z * tw + q.w * tz;
  mm::Vec4 translation;
  translation.x = lhs.unknown00.x + rx;
  translation.y = lhs.unknown00.y + ry;
  translation.z = lhs.unknown00.z + rz;
  translation.w = rhs.unknown00.w + lhs.unknown00.w;
  result->unknown00 = translation;
  result->unknown10 = mm::Quat::mul(rhs.unknown10, lhs.unknown10);
  mm::Vec4 scale;
  scale.x = lhs.unknown20.x * rhs.unknown20.x;
  scale.y = lhs.unknown20.y * rhs.unknown20.y;
  scale.z = lhs.unknown20.z * rhs.unknown20.z;
  scale.w = lhs.unknown20.w * rhs.unknown20.w;
  result->unknown20 = scale;
}

} // namespace anm
