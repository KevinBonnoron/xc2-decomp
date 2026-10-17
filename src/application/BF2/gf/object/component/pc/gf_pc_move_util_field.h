#pragma once

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

class GfComPropertyPc;

namespace pc {

class MoveUtilField {
public:
  static void enterMoveRun(GfComPropertyPc &property, bool isInherit);
  static void updateMoveTurn(const fw::UpdateInfo &info, GfComPropertyPc &property, const mm::Vec3 &direction);
  static void updateMoveWalkTurn(const fw::UpdateInfo &info, GfComPropertyPc &property, const mm::Vec3 &direction);
  static void enterMoveSwim(GfComPropertyPc &property);
  static void updateMoveSwim(const fw::UpdateInfo &info, GfComPropertyPc &property);
  static void updateMoveWaterRise(const fw::UpdateInfo &info, GfComPropertyPc &property);
  static void updateMoveWaterHoleRise(const fw::UpdateInfo &info, GfComPropertyPc &property);
};

} // namespace pc
} // namespace gf
