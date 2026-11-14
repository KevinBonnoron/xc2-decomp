#pragma once
#include "gf/object/component/behavior/movement/gf_move_jump.h"
#include "gf/object/component/behavior/movement/gf_move_run.h"
#include "gf/object/component/behavior/movement/gf_move_slide.h"
#include "gf/object/component/behavior/movement/gf_move_walk.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

class GfComPropertyPc;

namespace pc {

struct SlideParam;

bool IsBuddy(GfComPropertyPc &property);
void setMoveWalkPacket(GfComPropertyPc &property, GfMoveWalkControler::Packet *packet);
void setMoveRunPacket(GfComPropertyPc &property, GfMoveRunControler::Packet *packet);
void setMoveJumpPacket(GfComPropertyPc &property, GfMoveJumpControler::Packet *packet);
void setMoveSwimPacket(GfComPropertyPc &property, GfMoveRunControler::Packet *packet);
void setMoveSlidePacket(GfComPropertyPc &property, const SlideParam &param, GfMoveSlideControler::Packet *packet);

class MoveUtilField {
public:
  static f32 getSpeedEffect(GfComPropertyPc &property);
  static void enterMoveWalk(GfComPropertyPc &property);
  static void updateMoveWalk(const fw::UpdateInfo &info, GfComPropertyPc &property);
  static void enterMoveRun(GfComPropertyPc &property, bool isInherit);
  static void updateMoveRun(const fw::UpdateInfo &info, GfComPropertyPc &property);
  static void updateBrake(const fw::UpdateInfo &info, GfComPropertyPc &property);
  static void updateMoveTurn(const fw::UpdateInfo &info, GfComPropertyPc &property, const mm::Vec3 &direction);
  static void updateMoveWalkTurn(const fw::UpdateInfo &info, GfComPropertyPc &property, const mm::Vec3 &direction);
  static void updateMoveJump(const fw::UpdateInfo &info, GfComPropertyPc &property);
  static void updateMoveJumpBack(const fw::UpdateInfo &info, GfComPropertyPc &property);
  static void updateLandBrake(const fw::UpdateInfo &info, GfComPropertyPc &property);
  static void updateFallDown(const fw::UpdateInfo &info, GfComPropertyPc &property);
  static void enterMoveSwim(GfComPropertyPc &property);
  static void updateMoveSwim(const fw::UpdateInfo &info, GfComPropertyPc &property);
  static void updateMoveWaterTurn(const fw::UpdateInfo &info, GfComPropertyPc &property, const mm::Vec3 &direction);
  static void updateMoveWaterSink(const fw::UpdateInfo &info, GfComPropertyPc &property);
  static void updateMoveWaterRise(const fw::UpdateInfo &info, GfComPropertyPc &property);
  static void updateMoveWaterHoleRise(const fw::UpdateInfo &info, GfComPropertyPc &property);
  static void updateMoveWall(const fw::UpdateInfo &info, GfComPropertyPc &property);
  static void updateMoveSlide(const fw::UpdateInfo &info, GfComPropertyPc &property);
};

} // namespace pc
} // namespace gf
