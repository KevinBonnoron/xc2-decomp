#include "gf/object/component/pc/gf_pc_move_util_field.h"

#include <math.h>

#include "fw/fw_param_manager.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/behavior/movement/gf_move_brake.h"
#include "gf/object/component/behavior/movement/gf_move_fall.h"
#include "gf/object/component/behavior/movement/gf_move_jump_back.h"
#include "gf/object/component/behavior/movement/gf_move_turn.h"
#include "gf/object/component/behavior/movement/gf_move_water_rise.h"
#include "gf/object/component/behavior/movement/gf_move_water_sink.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/component/pc/param/gf_pc_param.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {
namespace pc {

f32 MoveUtilField::getSpeedEffect(GfComPropertyPc &property) {
  f32 bonus = static_cast<f32>(GfGameManager::getOwnerBonus()->unknown00[OWNER_BONUS_UNKNOWN_1]) * 0.01f + 1.0f;
  mm::clampRef(bonus, 1.0f, 1.5f);
  f32 speed = 0.0f;
  speed += bonus - 1.0f;
  if (property.unknown114 == 2) {
    const FieldParam *param = property.m_propertyField.unknown004(0).get<FieldParam>();
    const f32 &slow = property.unknown111_5 ? param->poisonSlow : param->waterSlow;
    speed -= slow;
  }
  return speed;
}

void MoveUtilField::enterMoveWalk(GfComPropertyPc &property) {
  GfMoveWalkControler::Packet packet;
  setMoveWalkPacket(property, &packet);
  GfMoveWalkControler controler;
  controler.enter(packet);
  property.unknown80 = packet.unknown00;
  property.unknown94 = packet.unknown10;
}

void setMoveWalkPacket(GfComPropertyPc &property, GfMoveWalkControler::Packet *packet) {
  packet->unknown00 = property.unknown80;
  packet->unknown10 = property.unknown94;
  packet->m_paramAdapter = property.m_propertyField.unknown004(2);
  packet->unknown20 = property.unknown2b0 * property.unknown60.unknown04 + property.unknown2d0 * property.unknown60.unknown00;
  if (!(fabsf(packet->unknown20.x) <= 0.000001f) || !(fabsf(packet->unknown20.y) <= 0.000001f) || !(fabsf(packet->unknown20.z) <= 0.000001f)) {
    packet->unknown20.unknown001();
  } else {
    packet->unknown20 = property.unknown1e0;
  }
  packet->unknown30 = property.unknown1e0;
  packet->unknown40 = MoveUtilField::getSpeedEffect(property) + 1.0f;
}

void MoveUtilField::updateMoveWalk(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  GfMoveWalkControler controler;
  GfMoveWalkControler::Packet packet;
  setMoveWalkPacket(property, &packet);
  controler.update(info, packet);
  property.unknown80 = packet.unknown00;
  property.unknown94 = packet.unknown10;
}

bool IsBuddy(GfComPropertyPc &property) { return property.unknown38 & 1; }

void setMoveRunPacket(GfComPropertyPc &property, GfMoveRunControler::Packet *packet) {
  packet->unknown00 = property.unknown80;
  packet->unknown10 = property.unknown94;
  packet->m_paramAdapter = property.m_propertyField.unknown004(3);
  const FieldParam *fieldParam = property.m_propertyField.unknown006();
  // The game reads both input components (0x60, 0x64) into callee-saved registers before the assertions below.
  f32 inputX = property.unknown60.unknown00;
  f32 inputY = property.unknown60.unknown04;
  // Ruling 5 (P3): the game (0x7100547ed0) evaluates the sqrtf of isUnit() on both input axes and drops the results
  // (two sqrtf with the NaN call): the operands of two compiled-out assertions. The original expression cannot be
  // checked. Same as setMoveSlidePacket (0x71005496ac).
  // The clamp/power block below repeats the one of setMoveSwimPacket and setMoveSlidePacket. A shared template helper
  // matches slide and swim but not run (222 against 216 instructions: the game forms the addresses of unknown1e0
  // before the join, 0x7100547ed0), so the block stays written out in all three (ruling 8, P4).
  property.unknown2b0.isUnit();
  property.unknown2d0.isUnit();
  packet->unknown30 = property.unknown2b0 * inputY + property.unknown2d0 * inputX;
  if (!(fabsf(packet->unknown30.x) <= 0.000001f) || !(fabsf(packet->unknown30.y) <= 0.000001f) || !(fabsf(packet->unknown30.z) <= 0.000001f)) {
    f32 length = sqrtf(packet->unknown30.x * packet->unknown30.x + packet->unknown30.y * packet->unknown30.y + packet->unknown30.z * packet->unknown30.z);
    f32 power = mm::clamp(length, 0.0f, 1.0f);
    packet->unknown20 = __builtin_fmaxf(power - fieldParam->accelThreshold, 0.0f) / __builtin_fmaxf(1.0f - fieldParam->accelThreshold, 0.0001f);
    packet->unknown30 = packet->unknown30 * (1.0f / power);
  } else {
    packet->unknown20 = 0.0f;
    packet->unknown30 = property.unknown1e0;
  }
  packet->unknown40 = property.unknown1e0;
  packet->unknown50 = MoveUtilField::getSpeedEffect(property) + 1.0f;
  if (IsBuddy(property)) {
    packet->unknown54 = static_cast<const MoveParam *>(property.unknown300->unknown10[1].param)->addMaxSpeedBuddy;
  }
}

void MoveUtilField::enterMoveRun(GfComPropertyPc &property, bool isInherit) {
  GfMoveRunControler controler;
  GfMoveRunControler::Packet packet;
  setMoveRunPacket(property, &packet);
  controler.enter(packet, isInherit);
  property.unknown80 = packet.unknown00;
  property.unknown94 = packet.unknown10;
}

void MoveUtilField::updateMoveRun(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  GfMoveRunControler controler;
  GfMoveRunControler::Packet packet;
  setMoveRunPacket(property, &packet);
  controler.update(info, packet);
  property.unknown80 = packet.unknown00;
  property.unknown94 = packet.unknown10;
}

void MoveUtilField::updateBrake(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  GfMoveBrakeControler controler;
  GfMoveBrakeControler::Packet packet;
  packet.unknown00 = property.unknown80;
  packet.m_paramAdapter = property.m_propertyField.unknown004(1);
  controler.update(info, packet);
  property.unknown80 = packet.unknown00;
}

void MoveUtilField::updateMoveTurn(const fw::UpdateInfo &info, GfComPropertyPc &property, const mm::Vec3 &direction) {
  GfMoveTurnControler::Packet packet;
  packet.unknown00 = property.unknown94;
  packet.m_paramAdapter = property.m_propertyField.unknown004(4);
  packet.unknown10 = direction;
  packet.unknown20 = property.unknown1e0;
  GfMoveTurnControler controler;
  controler.update(info, packet);
  property.unknown94 = packet.unknown00;
}

void MoveUtilField::updateMoveWalkTurn(const fw::UpdateInfo &info, GfComPropertyPc &property, const mm::Vec3 &direction) {
  GfMoveTurnControler::Packet packet;
  packet.unknown00 = property.unknown94;
  packet.m_paramAdapter = property.m_propertyField.unknown004(5);
  packet.unknown10 = direction;
  packet.unknown20 = property.unknown1e0;
  GfMoveTurnControler controler;
  controler.update(info, packet);
  property.unknown94 = packet.unknown00;
}

void MoveUtilField::updateMoveJump(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  GfMoveJumpControler controler;
  GfMoveJumpControler::Packet packet;
  setMoveJumpPacket(property, &packet);
  controler.update(info, packet);
  property.unknown80 = packet.unknown00;
  property.unknown94 = packet.unknown10;
}

void setMoveJumpPacket(GfComPropertyPc &property, GfMoveJumpControler::Packet *packet) {
  packet->unknown00 = property.unknown80;
  packet->unknown10 = property.unknown94;
  packet->m_paramAdapter = property.m_propertyField.unknown004(6);
  packet->unknown30 = property.unknown2b0 * property.unknown60.unknown04 + property.unknown2d0 * property.unknown60.unknown00;
  if (!(fabsf(packet->unknown30.x) <= 0.000001f) || !(fabsf(packet->unknown30.y) <= 0.000001f) || !(fabsf(packet->unknown30.z) <= 0.000001f)) {
    f32 length = sqrtf(packet->unknown30.x * packet->unknown30.x + packet->unknown30.y * packet->unknown30.y + packet->unknown30.z * packet->unknown30.z);
    f32 inverse = 1.0f / length;
    packet->unknown20 = mm::clamp(length, 0.0f, 1.0f);
    packet->unknown30 *= inverse;
  } else {
    packet->unknown20 = 0.0f;
    packet->unknown30 = property.unknown1e0;
  }
  packet->unknown40 = property.unknown1e0;
}

void MoveUtilField::updateMoveJumpBack(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  GfMoveJumpBackControler controler;
  GfMoveJumpBackControler::Packet packet;
  packet.unknown00 = property.unknown80;
  packet.m_paramAdapter = property.m_propertyField.unknown004(7);
  mm::Vec3 input = property.unknown2b0 * property.unknown60.unknown04 + property.unknown2d0 * property.unknown60.unknown00;
  if (fabsf(input.x) <= 0.000001f && fabsf(input.y) <= 0.000001f && fabsf(input.z) <= 0.000001f) {
    packet.unknown18 = 0.0f;
  } else {
    f32 length = sqrtf(input.x * input.x + input.y * input.y + input.z * input.z);
    packet.unknown18 = mm::clamp(length, 0.0f, 1.0f);
  }
  packet.unknown20 = property.unknown1e0;
  controler.update(info, packet);
  property.unknown80 = packet.unknown00;
  property.unknown94 = 0.0f;
}

void MoveUtilField::updateLandBrake(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  const GfMoveRunControler::Param *param = static_cast<const GfMoveRunControler::Param *>(property.m_propertyField.unknown08->unknown10[3].param);
  mm::Vec3 input = property.unknown2b0 * property.unknown60.unknown04 + property.unknown2d0 * property.unknown60.unknown00;
  f32 ratio = __builtin_fmaxf(input.x * property.unknown1e0.x + input.y * property.unknown1e0.y + input.z * property.unknown1e0.z, 0.0f);
  f32 limit = param->velocityMin + (param->velocityMax - param->velocityMin) * ratio;
  f32 speed = sqrtf(property.unknown80.x * property.unknown80.x + property.unknown80.y * property.unknown80.y + property.unknown80.z * property.unknown80.z);
  if (speed > limit) {
    speed = limit;
  }
  mm::Vec3 direction = property.unknown1e0;
  property.unknown80 = direction * speed;
}

void MoveUtilField::updateFallDown(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  GfMoveFallControler controler;
  GfMoveFallControler::Packet packet;
  packet.unknown00 = property.unknown90;
  packet.m_paramAdapter = property.m_propertyField.unknown004(8);
  controler.update(info, packet);
  property.unknown90 = packet.unknown00;
}

void MoveUtilField::enterMoveSwim(GfComPropertyPc &property) {
  GfMoveRunControler::Packet packet;
  setMoveSwimPacket(property, &packet);
  GfMoveRunControler controler;
  controler.enter(packet, true);
  property.unknown80 = packet.unknown00;
  property.unknown94 = packet.unknown10;
}

void setMoveSwimPacket(GfComPropertyPc &property, GfMoveRunControler::Packet *packet) {
  packet->unknown00 = property.unknown80;
  packet->unknown10 = property.unknown94;
  packet->m_paramAdapter = property.m_propertyField.unknown004(10);
  const FieldParam *param = property.m_propertyField.unknown006();
  packet->unknown30 = property.unknown2b0 * property.unknown60.unknown04 + property.unknown2d0 * property.unknown60.unknown00;
  if (!(fabsf(packet->unknown30.x) <= 0.000001f) || !(fabsf(packet->unknown30.y) <= 0.000001f) || !(fabsf(packet->unknown30.z) <= 0.000001f)) {
    f32 length = sqrtf(packet->unknown30.x * packet->unknown30.x + packet->unknown30.y * packet->unknown30.y + packet->unknown30.z * packet->unknown30.z);
    f32 power = mm::clamp(length, 0.0f, 1.0f);
    packet->unknown20 = __builtin_fmaxf(power - param->accelThreshold, 0.0f) / __builtin_fmaxf(1.0f - param->accelThreshold, 0.0001f);
    packet->unknown30 = packet->unknown30 * (1.0f / power);
  } else {
    packet->unknown20 = 0.0f;
    packet->unknown30 = property.unknown1e0;
  }
  packet->unknown40 = property.unknown1e0;
  if (property.unknown111_5) {
    packet->unknown50 = 1.0f - property.m_propertyField.unknown001()->poisonSlow;
  }
  if (IsBuddy(property)) {
    packet->unknown54 = static_cast<const MoveParam *>(property.unknown300->unknown10[1].param)->addMaxSpeedBuddySwim;
  }
}

void MoveUtilField::updateMoveSwim(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  GfMoveRunControler controler;
  GfMoveRunControler::Packet packet;
  setMoveSwimPacket(property, &packet);
  controler.update(info, packet);
  property.unknown80 = packet.unknown00;
  property.unknown94 = packet.unknown10;
}

void MoveUtilField::updateMoveWaterTurn(const fw::UpdateInfo &info, GfComPropertyPc &property, const mm::Vec3 &direction) {
  GfMoveTurnControler::Packet packet;
  packet.unknown00 = property.unknown94;
  packet.m_paramAdapter = property.m_propertyField.unknown004(11);
  packet.unknown10 = direction;
  packet.unknown20 = property.unknown1e0;
  GfMoveTurnControler controler;
  controler.update(info, packet);
  property.unknown94 = packet.unknown00;
}

void MoveUtilField::updateMoveWaterSink(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  GfMoveWaterSinkControler controler;
  GfMoveWaterSinkControler::Packet packet;
  packet.unknown00 = property.unknown90;
  packet.m_paramAdapter = property.m_propertyField.unknown004(12);
  controler.update(info, packet);
  property.unknown90 = packet.unknown00;
}

void MoveUtilField::updateMoveWaterRise(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  GfMoveWaterRiseControler controler;
  GfMoveWaterRiseControler::Packet packet;
  packet.unknown00 = property.unknown90;
  packet.m_paramAdapter = property.m_propertyField.unknown004(13);
  const WaterCommonParam *param = property.m_propertyField.unknown005();
  packet.unknown10 = fabsf(StateUtilField::getChildFrameHeight(property)) <= param->riseBrakeHeight;
  controler.update(info, packet);
  property.unknown90 = packet.unknown00;
}

void MoveUtilField::updateMoveWaterHoleRise(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  GfMoveWaterRiseControler controler;
  GfMoveWaterRiseControler::Packet packet;
  packet.unknown00 = property.unknown90;
  packet.m_paramAdapter = property.m_propertyField.unknown004(14);
  const WaterCommonParam *param = property.m_propertyField.unknown005();
  packet.unknown10 = fabsf(StateUtilField::getChildFrameHeight(property)) <= param->riseBrakeHeight;
  controler.update(info, packet);
  property.unknown90 = packet.unknown00;
}

void setMoveSlidePacket(GfComPropertyPc &property, const SlideParam &param, GfMoveSlideControler::Packet *packet) {
  packet->unknown00 = property.unknown80;
  packet->unknown10 = property.unknown94;
  packet->unknown14 = property.unknownc0;
  packet->m_paramAdapter = property.m_propertyField.unknown004(17);
  const FieldParam *fieldParam = property.m_propertyField.unknown006();
  // The game reads both input components (0x60, 0x64) into callee-saved registers before the assertions below.
  f32 inputX = property.unknown60.unknown00;
  f32 inputY = property.unknown60.unknown04;
  // Ruling 5 (P3): the game (0x71005496ac) evaluates the sqrtf of isUnit() on both input axes and drops the results
  // (two sqrtf with the NaN call at +0x58 and +0x84): the operands of two compiled-out assertions. The original
  // expression cannot be checked.
  // The clamp/power block below repeats the one of setMoveSwimPacket and setMoveRunPacket. A shared template helper
  // matches slide and swim but not run (222 against 216 instructions in run, 0x7100547ed0), so the block stays
  // written out in all three (ruling 8, P4).
  property.unknown2b0.isUnit();
  property.unknown2d0.isUnit();
  packet->unknown30 = property.unknown2b0 * inputY + property.unknown2d0 * inputX;
  if (!(fabsf(packet->unknown30.x) <= 0.000001f) || !(fabsf(packet->unknown30.y) <= 0.000001f) || !(fabsf(packet->unknown30.z) <= 0.000001f)) {
    f32 length = sqrtf(packet->unknown30.x * packet->unknown30.x + packet->unknown30.y * packet->unknown30.y + packet->unknown30.z * packet->unknown30.z);
    f32 power = mm::clamp(length, 0.0f, 1.0f);
    packet->unknown20 = __builtin_fmaxf(power - fieldParam->accelThreshold, 0.0f) / __builtin_fmaxf(1.0f - fieldParam->accelThreshold, 0.0001f);
    packet->unknown30 = packet->unknown30 * (1.0f / power);
  } else {
    packet->unknown20 = 0.0f;
    packet->unknown30 = mm::Vec3::zero;
  }
  packet->unknown40 = property.unknown1e0;
  packet->unknown50 = property.unknownd0;
  packet->unknown60 = param.startVel;
}

void MoveUtilField::updateMoveSlide(const fw::UpdateInfo &info, GfComPropertyPc &property) {
  GfMoveSlideControler controler;
  const fw::ParamList *paramList = property.unknown300.operator->();
  const SlideParam *param = paramList->unknown0c > 4 ? static_cast<const SlideParam *>(paramList->unknown10[4].param) : nullptr;
  GfMoveSlideControler::Packet packet;
  setMoveSlidePacket(property, *param, &packet);
  controler.update(info, packet);
  property.unknown80 = packet.unknown00;
  property.unknown94 = packet.unknown10;
}

} // namespace pc
} // namespace gf
