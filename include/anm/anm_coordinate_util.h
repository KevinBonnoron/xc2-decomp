#pragma once

namespace mm {
struct Vec3;
} // namespace mm

namespace anm {

class CoordinateUtil {
public:
  static void convertRCSToSPC(mm::Vec3 *pVec);
  static void convertSPCToRCS(mm::Vec3 *pVec);
};

} // namespace anm
