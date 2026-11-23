#include <algorithm> // IWYU pragma: keep
#include <float.h>
#include <stddef.h>

#include "framework/coli/coli_object.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "fw/fw_coli_check.h"
#include "fw/fw_param_manager.h"
#include "fw/fw_transform.h"
#include "gf/field/gf_field_lod.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/property/gf_env_property.h"
#include "gf/object/gf_obj_handle.h"
#include "idcoli/idcoli_util_coli.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/rtti.h"
#include "types.h"

namespace gf {

void EnviromentSensor::Parameter::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 17
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(Parameter));
#line 18
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("searchVertUp", offsetof(Parameter, searchVertUp), 0.0f, 1000.0f, 10.0f));
#line 19
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("searchVertDown", offsetof(Parameter, searchVertDown), 0.0f, 1000.0f, 100.0f));
#line 20
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("obstacleHeightBase", offsetof(Parameter, obstacleHeightBase), 0.0f, 1000.0f, 0.05f));
#line 21
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("obstacleHeightJump", offsetof(Parameter, obstacleHeightJump), 0.0f, 1000.0f, 0.5f));
#line 22
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("obstacleSearchLength", offsetof(Parameter, obstacleSearchLength), 0.0f, 1000.0f, 1.0f));
#line 23
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("wallEndHeight", offsetof(Parameter, wallEndHeight), 0.0f, 1000.0f, 2.0f));
#line 24
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("wallEndMoveDist", offsetof(Parameter, wallEndMoveDist), 0.0f, 1000.0f, 2.0f));
#line 25
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("wallEndSearchDown", offsetof(Parameter, wallEndSearchDown), 0.0f, 1000.0f, 2.0f));
#line 26
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("descendWallSearchFront", offsetof(Parameter, descendWallSearchFront), 0.0f, 1000.0f, 2.0f));
#line 27
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("descendWallSearchDown", offsetof(Parameter, descendWallSearchDown), 0.0f, 1000.0f, 1.05f));
#line 28
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("descendWallSearchDist", offsetof(Parameter, descendWallSearchDist), 0.0f, 1000.0f, 10.0f));
  reflection->setReflectionStruct(index, value);
}

// Placed here, not in gf_com_env_sensor.cpp (where clang would inline it into GfComEnvSensor::GfComEnvSensor()): the game puts it right after
// Parameter::createReflection (1.0.0: 0x710051cfe8 + 0x93c = 0x710051d924), a function this unit already defines, and GfComEnvSensor::GfComEnvSensor()
// calls it out of line (0x710051b1ec).
EnviromentSensor::EnviromentSensor() : m_envSensorCheckFlags(0), unknown24(0), m_verticalData(), m_groundInfo(), unknown290(1.0f) {}

// 1.0.0: 0x710051dc98.
void EnviromentSensor::check(const fw::Transform &transform, fw::ParamAdapter param) {
  const Parameter *parameter = param.get<Parameter>();
  m_transform = transform;
  unknown24 = 0;
  const mm::Vec3 up = mm::Vec3::unitY;
  const mm::Vec3 forward = transform.unknown10.rotate(mm::Vec3::unitX);
  // Measured: the cross product as a Vec3 constructor, as three member assignments in any of the six orders, or in a temporary gave 17 to 30 differing lines (the phi of the
  // normalisation, 1.0.0: 0x710051de8c to 0x710051de94, takes its registers from the order of the stores); only the shared helper that stores z, y, x matches.
  mm::Vec3 front;
  front.unknown004(forward, up);
  if (!front.unknown003()) {
    front.unknown001();
  }
  // The negated up vector is built at each use (as in StateUtilField::isWallAdsorption): a local `down` declared after `front` gives the registers of `up` and `front` another order
  // (measured), and a Vec3 declared after `front` also reverses the order of the phi nodes of the normalisation.
  {
    VerticalPacket packet;
    packet.unknown00 = m_envSensorCheckFlags;
    packet.unknown10 = mm::Vec3(-up.x, -up.y, -up.z);
    packet.unknown20 = -parameter->searchVertUp;
    packet.unknown24 = parameter->searchVertDown;
    packet.unknown28 = 0;
    packet.unknown30 = &m_verticalData;
    searchVertical(transform.unknown00, &packet);
    unknown24 |= packet.unknown28;
  }
  // The stores of the packet constructors (unknown24, unknown38 here, the zeroes of WallPacket) are the game's: searchVertical lets its packet escape, so the zeroes of its constructor
  // stay between the loads; the other three search functions, defined in this unit in the game, only read and write through their packet (clang infers nocapture), so that the dead stores
  // of the constructor of HorizonPacket go away. With the search functions only declared the packet escapes in every call and these stores stay (342 instructions against 338).
  {
    HorizonPacket packet;
    packet.unknown00 = m_envSensorCheckFlags;
    packet.unknown10 = front;
    packet.unknown20 = 0.0f;
    packet.unknown24 = parameter->obstacleSearchLength;
    packet.unknown28 = parameter->obstacleHeightBase;
    packet.unknown2c = parameter->obstacleHeightJump;
    packet.unknown30 = unknown290;
    packet.unknown34 = 0;
    packet.unknown38 = &unknown150;
    searchHorizon(transform.unknown00, &packet);
    unknown24 |= packet.unknown34;
  }
  if (!(unknown24_3 && m_verticalData.unknowne0.unknown00 - transform.unknown00.y <= parameter->wallEndHeight)) {
    WallPacket packet;
    packet.unknown00 = m_envSensorCheckFlags;
    packet.unknown10 = front;
    packet.unknown20 = mm::Vec3(-up.x, -up.y, -up.z);
    packet.unknown30 = mm::Vec3(0.0f, parameter->wallEndHeight, 0.0f);
    packet.unknown40 = 0.0f;
    packet.unknown44 = parameter->wallEndMoveDist;
    packet.unknown48 = 0.0f;
    packet.unknown4c = parameter->wallEndSearchDown;
    packet.unknown50 = 0;
    searchGroundWallEnd(transform.unknown00, &packet);
    unknown24 |= packet.unknown50;
    if ((packet.unknown50 >> 8) & 1) {
      m_groundInfo.unknown00 = packet.unknown60;
      m_groundInfo.unknown10 = packet.unknown70;
      m_groundInfo.unknown30 = packet.unknown90;
    }
  }
  const mm::Plane &wallPlane = unknown150.unknown00.unknown00;
  f32 wallDot = transform.unknown00.x * wallPlane.normal.x + transform.unknown00.y * wallPlane.normal.y + transform.unknown00.z * wallPlane.normal.z;
  if (!(unknown24_4 && wallPlane.distance + wallDot <= parameter->descendWallSearchFront)) {
    WallPacket packet;
    packet.unknown00 = m_envSensorCheckFlags;
    packet.unknown10 = front;
    packet.unknown20 = mm::Vec3(-up.x, -up.y, -up.z);
    // Ruling 8: the statements of mm::unknown010 (the rotation of the offset by the rotation of the transform) are written out, each component stored into the packet as soon as it is
    // computed (1.0.0: 0x710051e07c to 0x710051e13c, the three stores of the offset). Measured on check() (the game has 338 instructions): `mm::unknown010(transform.unknown10,
    // packet.unknown30)` after assigning the offset to the packet has the same stores but the operands of two products swapped (338 instructions, 2 lines differ); the same call on a
    // local offset copied to the packet stores the three components together (337 instructions, 22 lines differ); `packet.unknown30 = transform.unknown10.rotate(offset)` gives paired
    // stores (337 instructions, 22 lines differ).
    const mm::Vec3 offset(0.0f, parameter->obstacleHeightBase, parameter->descendWallSearchFront);
    const mm::Quat &rotation = transform.unknown10;
    f32 tx = rotation.y * offset.z - rotation.z * offset.y + rotation.w * offset.x;
    f32 ty = rotation.z * offset.x - offset.z * rotation.x + offset.y * rotation.w;
    f32 tz = offset.y * rotation.x - rotation.y * offset.x + offset.z * rotation.w;
    f32 tw = -offset.x * rotation.x - rotation.y * offset.y - offset.z * rotation.z;
    packet.unknown30.x = -(rotation.z * ty) + rotation.y * tz - rotation.x * tw + rotation.w * tx;
    packet.unknown30.y = -(rotation.x * tz) + rotation.z * tx - rotation.y * tw + rotation.w * ty;
    packet.unknown30.z = -(rotation.y * tx) + rotation.x * ty - rotation.z * tw + rotation.w * tz;
    packet.unknown40 = 0.0f;
    packet.unknown44 = parameter->descendWallSearchDown;
    packet.unknown48 = 0.0f;
    packet.unknown4c = parameter->descendWallSearchDist;
    packet.unknown50 = 0;
    searchWallUnderGround(transform.unknown00, &packet);
    unknown24 |= packet.unknown50;
    if ((packet.unknown50 >> 7) & 1) {
      f32 dot = transform.unknown00.x * packet.unknown70.normal.x + transform.unknown00.y * packet.unknown70.normal.y + transform.unknown00.z * packet.unknown70.normal.z;
      unknown260.unknown20 = packet.unknown70.distance + dot;
      unknown260.unknown00 = packet.unknown70;
      unknown260.unknown24 = packet.unknown90;
    }
  }
}

// Evidence (1.0.0: 0x710051eb80, 562 instructions): three line tests of the same shape, in the order bit 6 (0x710051eb80+0x064), bit 4 (+0x35c) and bit 5 (+0x608, only when the bit 4 test
// found a wall, `ldrb [packet + 0x34]; tbz #4`). Each starts a fresh TColiCheckResult<256> (the zeroed count at +0x5000, hit count +0x5010 and flag +0x5014) and shares one ColiCheckConfig
// (flags 9, attribute mask 0x800000da, result mode 1). The line goes from position + direction * unknown20 to position + direction * unknown24, both raised by the height of the bit
// (x and z get no `+ 0.0f`: the game adds the height to y only). A hit sets the wall plane from the first position and normal (mm::Plane::set, as GfComEnvSensor::flushGroundSingle),
// the flags from the material word at +0x04, and the signed distance of `position` to the plane. The game reloads packet->unknown38 for every one of those stores (a local pointer to the
// result measured: the `stp` of the normalized normal is split and the pointer lives in another register), so each store goes through the packet; the distance reads the plane through
// one load of the plane info. Only the bit 6 test also reads the user data of the first hit (hit offset 0x38, tested for null, getRTTI, isKindOf) and takes the object handle of a
// gf::GfFieldLodColiAnim::ColiUserData (+0x08) when it is one. The three blocks are written out (ruling 8): a file-local helper doing the start/end computation and the testLine call
// (the result declared by the caller) gives the same 562 instructions but constructs the result before the start/end arithmetic and schedules the config and the line stores differently
// (first difference at +0x2c, the frame offsets of the config and the line); the game builds the result after computing the line. The bit 6 block also differs (handle) and the bit 5
// block has its extra condition.
void EnviromentSensor::searchHorizon(const mm::Vec3 &position, HorizonPacket *packet) {
  packet->unknown34 = 0;
  packet->unknown38->m_GF_OBJ_HANDLE = unknown020;
  fw::ColiCheckConfig config;
  config.unknown08 = 0.0f;
  config.unknown0c = 0.0f;
  config.unknown14 = false;
  config.unknown15 = false;
  config.unknown10 = 1;
  config.unknown04 = 0x800000da;
  config.unknown00 = 9;
  if (packet->unknown00 & 0x40) {
    mm::Vec3 origin = position;
    origin.y += packet->unknown30;
    mm::Vec3 start = origin + packet->unknown10 * packet->unknown20;
    mm::Vec3 end = origin + packet->unknown10 * packet->unknown24;
    fw::TColiCheckResult<256> result;
    fw::ColiCheck::testLine(result, start, end, config);
    if (result.getCount() != 0) {
      packet->unknown38->unknown60.unknown00.set(result.getPosition(0), result.getNormal(0));
      packet->unknown38->unknown60.unknown24 = result.getMaterial(0).unknown04;
      unknown003 &wall = packet->unknown38->unknown60;
      wall.unknown20 = position.x * wall.unknown00.normal.x + position.y * wall.unknown00.normal.y + position.z * wall.unknown00.normal.z + wall.unknown00.distance;
      packet->unknown34 |= 0x40;
      fw::ColiUserData *userData = static_cast<fw::ColiUserData *>(result.unknown003(0));
      if (userData != nullptr) {
        GfFieldLodColiAnim::ColiUserData *lodUserData = mm::mtl::dynamicCast<GfFieldLodColiAnim::ColiUserData>(userData);
        if (lodUserData != nullptr) {
          packet->unknown38->m_GF_OBJ_HANDLE = lodUserData->m_GF_OBJ_HANDLE;
        }
      }
    }
  }
  if (packet->unknown00 & 0x10) {
    mm::Vec3 origin = position;
    origin.y += packet->unknown28;
    mm::Vec3 start = origin + packet->unknown10 * packet->unknown20;
    mm::Vec3 end = origin + packet->unknown10 * packet->unknown24;
    fw::TColiCheckResult<256> result;
    fw::ColiCheck::testLine(result, start, end, config);
    if (result.getCount() != 0) {
      packet->unknown38->unknown00.unknown00.set(result.getPosition(0), result.getNormal(0));
      packet->unknown38->unknown00.unknown24 = result.getMaterial(0).unknown04;
      unknown003 &wall = packet->unknown38->unknown00;
      wall.unknown20 = position.x * wall.unknown00.normal.x + position.y * wall.unknown00.normal.y + position.z * wall.unknown00.normal.z + wall.unknown00.distance;
      packet->unknown34 |= 0x10;
    }
  }
  if ((packet->unknown00 & 0x20) && (packet->unknown34 & 0x10)) {
    mm::Vec3 origin = position;
    origin.y += packet->unknown2c;
    mm::Vec3 start = origin + packet->unknown10 * packet->unknown20;
    mm::Vec3 end = origin + packet->unknown10 * packet->unknown24;
    fw::TColiCheckResult<256> result;
    fw::ColiCheck::testLine(result, start, end, config);
    if (result.getCount() != 0) {
      packet->unknown38->unknown30.unknown00.set(result.getPosition(0), result.getNormal(0));
      packet->unknown38->unknown30.unknown24 = result.getMaterial(0).unknown04;
      unknown003 &wall = packet->unknown38->unknown30;
      wall.unknown20 = position.x * wall.unknown00.normal.x + position.y * wall.unknown00.normal.y + position.z * wall.unknown00.normal.z + wall.unknown00.distance;
      packet->unknown34 |= 0x20;
    }
  }
}

// 1.0.0: 0x710051f448. Looks for the ground at the end of a wall: a first segment along unknown10 (distances unknown40 and unknown44 from position + unknown30) must hit nothing, then a second segment
// along unknown20 (unknown48 to unknown4c from the end of the first) must hit a point not below the search position; the hit goes to the packet (unknown60 position, unknown70 plane, unknown90
// material flags) and bit 8 of the found searches is set. Both segments go through one result (testLine clears it). The config values and the stores order are those of searchWallUnderGround
// (flushGroundSingle holds the same idiom). Forms measured: `start` and `end` declared first and assigned with `position + unknown30 + dir * distance` (no `origin` local, no initialisers) matches;
// with initialisers or an `origin` local the A57 FP load balancing (AArch64A57FPLoadBalancing) renames the multiply registers of the first segment differently (4 lines differ, 245 instructions both
// ways).
void EnviromentSensor::searchGroundWallEnd(const mm::Vec3 &position, WallPacket *packet) {
  packet->unknown50 = 0;
  fw::ColiCheckConfig config;
  config.unknown08 = 0.0f;
  config.unknown0c = 0.0f;
  config.unknown14 = false;
  config.unknown15 = false;
  config.unknown10 = 1;
  config.unknown04 = 0x800000d2;
  config.unknown00 = 9;
  if (!packet->unknown01_0) {
    return;
  }
  mm::Vec3 start;
  mm::Vec3 end;
  start = position + packet->unknown30 + packet->unknown10 * packet->unknown40;
  end = position + packet->unknown30 + packet->unknown10 * packet->unknown44;
  fw::TColiCheckResult<256> result;
  fw::ColiCheck::testLine(result, start, end, config);
  if (result.getCount() != 0) {
    return;
  }
  start = end + packet->unknown20 * packet->unknown48;
  end += packet->unknown20 * packet->unknown4c;
  fw::ColiCheck::testLine(result, start, end, config);
  if (result.getCount() == 0) {
    return;
  }
  if (result.getPosition(0).y >= position.y) {
    packet->unknown60 = result.getPosition(0);
    packet->unknown70.set(result.getPosition(0), result.getNormal(0));
    packet->unknown90 = result.getMaterial(0).unknown04;
    packet->unknown50 |= 0x100;
  }
}

// 1.0.0: 0x710051f81c. Looks for a wall with ground under it: the first segment (along unknown20, distances unknown40 and unknown44 from position + unknown30) must hit nothing, then a second segment
// from its end along -unknown10 (unknown48 to unknown4c) must hit a surface whose material flags have bit 4 or bit 7 (0x90); the hit goes to the packet and bit 7 of the found searches is set. The two
// results are separate (the game keeps the TColiCheckResult objects at sp + 0x5030 and at sp, the second constructed only after the first segment found nothing), and so are `groundStart` (sp +
// 0x5020, between them) and `end`, which the second segment overwrites. Forms measured (check, 293 instructions): the old end copied to `groundOrigin`, with both new points computed from it, matches;
// `groundStart = end - ...; end -= ...` gives the right code with the loads of the direction and the distance of the second segment in the other order (18 lines differ). The material flags are read
// into `flags` before a call whose result is discarded: the game (0x710051f9d0..0x710051fa5c) loads the flags into w22, then runs the `index < getCount()` guard and the `0 < size()` assertion of an
// accessor of hit 0 whose value is dead (no load survives), then tests `flags & 0x90`. Without that discarded call the code is 282 instructions; which accessor it was cannot be told (getPosition and
// getNormal give the same bytes), ruling 5.
void EnviromentSensor::searchWallUnderGround(const mm::Vec3 &position, WallPacket *packet) {
  packet->unknown50 = 0;
  fw::ColiCheckConfig config;
  config.unknown08 = 0.0f;
  config.unknown0c = 0.0f;
  config.unknown14 = false;
  config.unknown15 = false;
  config.unknown10 = 1;
  config.unknown04 = 0x8000009a;
  config.unknown00 = 9;
  if (!packet->unknown00_7) {
    return;
  }
  mm::Vec3 origin = position + packet->unknown30;
  mm::Vec3 start = origin + packet->unknown20 * packet->unknown40;
  mm::Vec3 end = origin + packet->unknown20 * packet->unknown44;
  fw::TColiCheckResult<256> wall;
  fw::ColiCheck::testLine(wall, start, end, config);
  if (wall.getCount() != 0) {
    return;
  }
  mm::Vec3 groundOrigin = end;
  mm::Vec3 groundStart = groundOrigin - packet->unknown10 * packet->unknown48;
  end = groundOrigin - packet->unknown10 * packet->unknown4c;
  fw::TColiCheckResult<256> ground;
  fw::ColiCheck::testLine(ground, groundStart, end, config);
  if (ground.getCount() == 0) {
    return;
  }
  u32 flags = ground.getMaterial(0).unknown04;
  ground.getPosition(0);
  if (!(flags & 0x90)) {
    return;
  }
  packet->unknown60 = ground.getPosition(0);
  packet->unknown70.set(ground.getPosition(0), ground.getNormal(0));
  packet->unknown90 = ground.getMaterial(0).unknown04;
  packet->unknown50 |= 0x80;
}

// 1.0.0: 0x710051fcb0.
void EnviromentSensor::writeBackProperty(bool isEnable, GfEnvProperty *property) const {
  if (property == nullptr) {
    return;
  }
  property->unknown2d4 = isEnable;
  const bool hasGround = unknown24_0;
  const GroundInfo *ground = hasGround ? &m_verticalData : nullptr;
  if (hasGround) {
    GfEnvProperty::unknown002 sample;
    sample.unknown10 = ground->unknown10;
    sample.unknown00 = ground->unknown00;
    sample.unknown30 = ground->unknown30;
    sample.unknown34 = ground->unknown34;
    sample.unknown38 = ground->unknown50;
    sample.unknown48 = ground->unknown60;
    property->unknown2d0 |= 1 << (GfEnvProperty::GROUND_INDEX_UNKNOWN_0 + 1);
    property->unknown00[GfEnvProperty::GROUND_INDEX_UNKNOWN_0] = sample;
  } else {
    property->unknown2d0 &= ~(1 << (GfEnvProperty::GROUND_INDEX_UNKNOWN_0 + 1));
  }
  if (unknown24_1) {
    GfCharaWaterInfo water;
    water.unknown00 = m_verticalData.unknown70.unknown00;
    water.unknown10 = m_verticalData.unknown70.unknown10;
    water.unknown30 = water.unknown00 - m_transform.unknown00.y;
    water.unknown34 = hasGround ? water.unknown00 - ground->unknown00.y : FLT_MAX;
    water.unknown38 = m_verticalData.unknown70.unknown34;
    water.unknown3c = m_verticalData.unknown70.unknown38;
    water.unknown40 = m_verticalData.unknown70.unknown30;
    property->unknown280 = water;
    property->unknown2d0 |= 1;
  } else {
    property->unknown2d0 &= ~1;
  }
}

} // namespace gf

// Temporary device: the game emits these instantiations in this unit, from the std::sort(hits.begin(), hits.end(), ContactLess(...)) of searchVertical (1.0.0: 0x710051e1e0, `bl` to
// 0x710051fe78 at +0x118). That call instantiates __sort (0x710051fe78) and, through it, __sort3 (0x71005209bc), __sort4 (0x7100521058), __sort5 (0x71005214c0), __insertion_sort_3
// (0x7100521a8c) and __insertion_sort_incomplete (0x7100521ce0). Measured: the call form (a draft of searchVertical, which still has two register swaps and is not landed) gives the same
// bodies as this explicit instantiation (__sort 721, __sort3 423, __sort4 282, __sort5 371, __insertion_sort_3 149 and __insertion_sort_incomplete 293 instructions, all MATCH). Replace it
// with the std::sort call when searchVertical is reconstructed in this file, and delete this line.
template void std::__sort<gf::ContactLess &, fw::ContactInfo *>(fw::ContactInfo *, fw::ContactInfo *, gf::ContactLess &);
