#include "ml/attr_transform.h"

namespace ml {

void AttrTransform::clear() {
  unknown00 = mm::Vec3::zero;
  unknown20 = mm::Vec3(1.0f, 1.0f, 1.0f);
  unknown30 = mm::Mat44::identity;
  unknown70 = mm::Mat44::identity;
  _b0 = mm::Mat44::identity;
  _10 = mm::Vec3::zero;
  unknown130 = 0;
  unknownf0 = mm::Vec3::zero;
  _120 = mm::Quat::identity;
  _100 = mm::Vec3::zero;
}

} // namespace ml
