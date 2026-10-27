#pragma once

namespace mm {
struct Mat44;
} // namespace mm

namespace anm {

struct QsTransform;

class TransformUtil {
public:
  static void mul(const QsTransform &lhs, const QsTransform &rhs, QsTransform *result);
  static void invert(const QsTransform &transform, QsTransform *result);
  static void calcMatrix(const QsTransform &transform, mm::Mat44 *matrix);
};

} // namespace anm
