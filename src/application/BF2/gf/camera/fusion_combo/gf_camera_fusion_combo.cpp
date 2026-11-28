#include "gf/camera/fusion_combo/gf_camera_fusion_combo.h"

#include <math.h>

#include "framework/framework.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/camera/gf_camera_utilities.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "ml/rand.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace fw {
enum CAMERA_PRIO : int;
} // namespace fw

namespace gf {

static constexpr fw::CAMERA_PRIO CAMERA_PRIO_UNKNOWN_55 = static_cast<fw::CAMERA_PRIO>(55); // Inferred role: camera prio fusion combo; original name unknown.

void FusionComboCamera::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 17
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(unknown001));
#line 18
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("zoom_frame", offsetof(unknown001, zoom_frame), 0.0f, 1000.0f, 60.0f));
#line 19
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("zoom_start_distance", offsetof(unknown001, zoom_start_distance), -100.0f, 100.0f, 3.0f));
#line 20
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("zoom_end_distance", offsetof(unknown001, zoom_end_distance), -100.0f, 100.0f, 1.5f));
#line 21
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("zoom_base_width", offsetof(unknown001, zoom_base_width), 0.0f, 100.0f, 0.25f));
#line 22
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("zoom_add_width", offsetof(unknown001, zoom_add_width), 0.0f, 100.0f, 0.3f));
#line 23
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("zoom_base_height", offsetof(unknown001, zoom_base_height), 0.0f, 100.0f, 1.2f));
#line 24
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("zoom_add_height", offsetof(unknown001, zoom_add_height), 0.0f, 100.0f, 0.7f));
#line 25
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueS32("zoom_mode", offsetof(unknown001, zoom_mode), 0, 1, 0));
#line 27
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("around_frame", offsetof(unknown001, around_frame), 0.0f, 1000.0f, 210.0f));
#line 28
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("around_start_distance", offsetof(unknown001, around_start_distance), 0.0f, 1000.0f, 10.0f));
#line 29
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("around_end_distance", offsetof(unknown001, around_end_distance), 0.0f, 1000.0f, 2.0f));
#line 30
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("around_rotate", offsetof(unknown001, around_rotate), 0.0f, 1000.0f, 360.0f));
#line 31
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("around_add_yaw", offsetof(unknown001, around_add_yaw), 0.0f, 180.0f, 45.0f));
#line 32
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("around_add_pitch", offsetof(unknown001, around_add_pitch), 0.0f, 180.0f, 45.0f));
#line 33
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueS32("around_mode", offsetof(unknown001, around_mode), 0, 1, 0));
#line 35
  fw::ReflectionValueBitset32 *flags = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueBitset32("flags", offsetof(unknown001, flags));
#line 36
  flags->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueFlag("collision_enable", 1, false));
#line 37
  flags->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueFlag("speed_enable", 2, true));
  value->add(flags);
  reflection->setReflectionStruct(index, value);
}

// 1.0.0: 0x71001d53ac, 845 instructions (the C1 and C2 constructors share the address). Measured forms:
// - `switch (unknown12c)` with case 0 written first gives the game's `cmp #1; b.eq`, then `cbnz`, and the mode 0 block falling through; `if/else if` lays the blocks out the other way.
// - `m_nearClip`, `m_farClip`, then `m_fov`: the fov before the far clip merges it with the near clip into the wrong store.
// - the parameter record is `m_paramAdapter.get<unknown001>()` read after `unknown00` is set (the null branch of get<> folds to `mov x22, xzr`).
// - mode 0 reads the position into a local before the calls (the game loads x, y and z with `ldp`/`ldr` before `getCameraLookBonePosition`); the height offset is added after the width.
// - the zoom_mode != 0 arm reads the start and end distance between the distance and the normalisation (they stay in s15/s14 across the second sqrtf); after it: 842 instructions.
// - `GfBdatRsc::get()` before the `dataEnemy != nullptr && bdatRsc != nullptr` test removes a stack spill order difference; the mode 1 axis is negated by component (the Vec3
//   constructor swaps x and z).
// - mode 1 tests the type PC first and the enemy second (`cmp #5; b.eq` first in the game); `getAxis(axis, forward, axis)` is the inlined second call, `getAxis(Vec3::unitY, ...)`
//   the out of line first.
// - the enemy radius lookup (`DataParamAcc`, `getSDataEnemy`, `GfBdatRsc::get()`, `getRscEnEnRadius2`, the setup scale) is written out three times (ruling 8, genuine duplication). Measured
//   against the game's 845 instructions: a file-local helper `(target, radius)` returning the scaled radius for the two zoom arms gives 850 instructions and 217 differing lines (first difference
//   0x71001d5524), also with `inline`; a helper `(target, radius, scale)` used by the three arms gives 856 instructions and 327 differing lines. Mode 1 uses the unscaled radius with two formulas of
//   the scale, so the three blocks are not the same.
// - single-use locals kept because the inline form does not match: `heightOffset` and `yawOffset` hold a call of mtRandf1 (ruling 1: with the call inline the first differences are at 0x71001d55c4
//   and 0x71001d5790), `yaw` holds the getYaw call (844 instructions inline), `width` places the sum (100 differing lines inline) and `targetTransform` places the getWorldTransform call (844
//   instructions inline).
FusionComboCamera::FusionComboCamera(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *target, Mode mode)
    : fw::Camera(CAMERA_PRIO_UNKNOWN_55), unknownb0(mm::Vec3::zero), unknownc0(mm::Vec3::zero), unknownd0(45.0f), unknowne0(mm::Vec3::zero), unknownf0(mm::Vec3::zero), unknown100(mm::Vec3::zero),
      unknown110(mm::Vec3::zero), unknown120(0.0f), unknown124(0.0f), unknown128(0.0f), unknown12c(mode), unknown130(false), unknown131(false), m_paramAdapter(),
      m_coliCheckConfig{0xb, 0xffffffff, 0.0f, 0.0f, 2, false, false} {
  m_nearClip = 0.4f;
  m_farClip = 80000.0f;
  m_fov = 45.0f;
  const fw::ParamList *paramList = fw::ParamManager::get()->unknown408[19].operator->();
  m_paramAdapter.unknown00 = paramList->unknown0c > 1 ? &paramList->unknown10[1] : nullptr;
  const unknown001 *param = m_paramAdapter.get<unknown001>();
  unknown130 = param->flags & 1;
  unknown131 = (param->flags >> 1) & 1;
  switch (unknown12c) {
  case MODE_UNKNOWN_0: {
    GfObjAcc acc(handle);
    if (target == unknown020) {
      target = acc.getTarget();
    }
    GfObjAcc targetAcc(target);
    if (acc.isValid() && targetAcc.isValid()) {
      const fw::Transform &transform = acc.getWorldTransform();
      const fw::Transform &targetTransform = targetAcc.getWorldTransform();
      mm::Vec3 position = transform.unknown00;
      mm::Vec3 targetPosition = targetTransform.unknown00;
      position.y += param->zoom_base_height;
      CameraUtilities::getCameraLookBonePosition(target, targetPosition);
      f32 widthOffset = param->zoom_add_width * ml::mtRandf1(-1.0f, 1.0f);
      f32 heightOffset = param->zoom_add_height * ml::mtRandf1(-1.0f, 1.0f);
      f32 baseWidth = param->zoom_base_width;
      if (widthOffset < 0.0f) {
        baseWidth = -baseWidth;
      }
      f32 width = widthOffset + baseWidth;
      position.y += heightOffset;
      mm::Vec3 direction = targetPosition - position;
      direction.unknown001();
      mm::Quat rotation;
      rotation.unknown001(0.7853982f);
      direction.y = 0.0f;
      mm::Vec3 eye = position + rotation.rotate(direction * width);
      if (param->zoom_mode == 0) {
        mm::Vec3 offset = targetPosition - eye;
        f32 distance = sqrtf(offset.x * offset.x + offset.y * offset.y + offset.z * offset.z);
        offset.unknown001();
        f32 ratio = 1.0f;
        if (targetAcc.getType() == OBJECT_TYPE_ENEMY) {
          DataParamAcc dataParam(target);
          const SDataEnemy *dataEnemy = dataParam.getSDataEnemy();
          GfBdatRsc *bdatRsc = GfBdatRsc::get();
          if (dataEnemy != nullptr && bdatRsc != nullptr) {
            f32 radius = static_cast<f32>(bdatRsc->getRscEnEnRadius2(dataEnemy->unknown44));
            GfObjSetupEnemy *setup = GfObjUtil::getObjSetup<GfObjSetupEnemy>(target);
            if (setup != nullptr) {
              radius *= setup->unknown40;
            }
            ratio = (distance - (radius + -2.0f)) * 0.1f;
          }
        }
        // The start and end are the eye moved back along the negated direction. The negation matters: InstCombine puts a negated operand (complexity 1) on the right of the fmul, so the
        // game's `start * direction` (0x71001d5f74: `fmul s4, s3, s0`, the parameter first) only comes out of `eye + (-direction) * start`; `eye - direction * start` gives `direction * start`.
        mm::Vec3 back(-offset.x, -offset.y, -offset.z);
        unknowne0 = eye + back * param->zoom_start_distance;
        unknownf0 = eye + back * (ratio * param->zoom_end_distance);
      } else {
        mm::Vec3 offset = eye - targetPosition;
        f32 distance = sqrtf(offset.x * offset.x + offset.y * offset.y + offset.z * offset.z);
        f32 start = distance + param->zoom_start_distance;
        f32 end = distance + param->zoom_end_distance;
        offset.unknown001();
        if (targetAcc.getType() == OBJECT_TYPE_ENEMY) {
          DataParamAcc dataParam(target);
          const SDataEnemy *dataEnemy = dataParam.getSDataEnemy();
          GfBdatRsc *bdatRsc = GfBdatRsc::get();
          if (dataEnemy != nullptr && bdatRsc != nullptr) {
            f32 radius = static_cast<f32>(bdatRsc->getRscEnEnRadius2(dataEnemy->unknown44));
            GfObjSetupEnemy *setup = GfObjUtil::getObjSetup<GfObjSetupEnemy>(target);
            if (setup != nullptr) {
              radius *= setup->unknown40;
            }
            if (end < radius) {
              f32 shortage = radius - end;
              start += shortage;
              end += shortage;
            }
          }
        }
        unknowne0 = offset * start + targetPosition;
        unknownf0 = offset * end + targetPosition;
      }
      unknown110 = targetPosition;
      unknown120 = param->zoom_frame;
    }
    break;
  }
  case MODE_UNKNOWN_1: {
    GfObjAcc acc(handle);
    if (acc.isValid()) {
      const fw::Transform &transform = acc.getWorldTransform();
      mm::Vec3 position = transform.unknown00;
      CameraUtilities::getCameraLookBonePosition(handle, position);
      f32 yaw = getYaw(transform.unknown10);
      f32 yawOffset = param->around_add_yaw * mm::DEG_TO_RAD * ml::mtRandf1(-1.0f, 1.0f);
      mm::Quat rotation = unknown169(param->around_add_pitch * mm::DEG_TO_RAD * ml::mtRandf1(-1.0f, 1.0f), yaw + yawOffset, 0.0f);
      mm::Vec3 forward(-mm::Vec3::unitZ.x, -mm::Vec3::unitZ.y, -mm::Vec3::unitZ.z);
      mm::unknown010(rotation, forward);
      mm::Vec3 axis;
      getAxis(mm::Vec3::unitY, forward, axis);
      getAxis(axis, forward, axis);
      if (ml::mtRand() % 2 == 1) {
        axis.x = -axis.x;
        axis.y = -axis.y;
        axis.z = -axis.z;
      }
      f32 start = param->around_start_distance;
      f32 end = param->around_end_distance;
      u32 type = acc.getType();
      if (type == OBJECT_TYPE_PC) {
        start += 0.5f;
        end += 0.5f;
      } else if (type == OBJECT_TYPE_ENEMY) {
        DataParamAcc dataParam(handle);
        const SDataEnemy *dataEnemy = dataParam.getSDataEnemy();
        GfBdatRsc *bdatRsc = GfBdatRsc::get();
        if (dataEnemy != nullptr && bdatRsc != nullptr) {
          u32 radius = bdatRsc->getRscEnEnRadius2(dataEnemy->unknown44);
          GfObjSetupEnemy *setup = GfObjUtil::getObjSetup<GfObjSetupEnemy>(handle);
          f32 scale = setup != nullptr ? setup->unknown40 : 1.0f;
          if (param->around_mode == 0) {
            start += radius * scale;
            end += radius * scale;
          } else {
            start = (start + radius) * scale;
            end = (end + radius) * scale;
          }
        }
      }
      unknowne0 = forward * start + position;
      unknownf0 = forward * end + position;
      unknown100 = axis;
      unknown110 = position;
      unknown120 = param->around_frame;
      unknown128 = param->around_rotate * mm::DEG_TO_RAD;
    }
    break;
  }
  }
  m_coliCheckConfig.unknown00 = 9;
  m_coliCheckConfig.unknown10 = 1;
  m_coliCheckConfig.unknown04 = 0xfffffff7;
}

FusionComboCamera::~FusionComboCamera() {}

void FusionComboCamera::onActivate() {}

// __LINE__ must be 313 and 319 as in the original file: they are the line arguments of the allocations.
mm::mtl::IntrusivePtr<fw::Camera> FusionComboCamera::create(GF_OBJ_HANDLE *handle, Mode mode) {
#line 313
  return new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) FusionComboCamera(handle, unknown020, mode);
}

mm::mtl::IntrusivePtr<fw::Camera> FusionComboCamera::create(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *target, Mode mode) {
#line 319
  return new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) FusionComboCamera(handle, target, mode);
}

// 1.0.0: 0x71001d64ac, 234 instructions. The normalisation of the axis is written out (0x71001d6638 to 0x71001d66c4): `mm::Vec3 axis = unknown100; axis.unknown001();` and `unknown002()` both give
// 239 instructions (78 differing lines). The calcSpeedTypeSlowInSlowOut call is inlined with the temporary 0.0f as `start`; the inlined slowOut is the case of the `angle` local of slowOut. The
// single-use locals `center`, `position` and `c` stay: without `center` the first difference is at 0x71001d64b0 (234 instructions), without `position` at 0x71001d64b0 (236 instructions),
// without `c` at 0x71001d64e0 (233 instructions).
void FusionComboCamera::update(const fw::UpdateInfo &info) {
  if (unknown120 <= 0.0f) {
    return;
  }
  f32 progress = unknown124 / unknown120;
  f32 ratio = 1.0f;
  if (progress < 1.0f) {
    unknown124 += info.unknown00 / 0.033333335f;
    ratio = progress;
  }
  mm::Vec3 delta = unknownf0 - unknowne0;
  unknownb0 = delta * ratio;
  unknownb0 += unknowne0;
  mm::Vec3 position = unknownb0;
  if (unknown12c == MODE_UNKNOWN_1) {
    mm::Vec3 center = unknown110;
    f32 angle;
    if (!unknown131) {
      angle = ratio * unknown128;
    } else {
      calcSpeedTypeSlowInSlowOut(0.0f, unknown128, ratio, angle);
    }
    mm::Vec3 offset = position - center;
    f32 length = sqrtf(unknown100.x * unknown100.x + unknown100.y * unknown100.y + unknown100.z * unknown100.z);
    mm::Vec3 axis;
    if (length <= 0.000001f) {
      axis = mm::Vec3::zero;
    } else {
      axis.x = unknown100.x * (1.0f / length);
      axis.y = unknown100.y * (1.0f / length);
      axis.z = unknown100.z * (1.0f / length);
    }
    mm::Quat rotation;
    f32 half = angle * 0.5f;
    f32 s = sinf(half);
    f32 c = cosf(half);
    rotation.x = axis.x * s;
    rotation.y = axis.y * s;
    rotation.z = axis.z * s;
    rotation.w = c;
    unknownb0 = unknown110 + rotation.rotate(offset);
    delta = unknown110 - unknownb0;
  }
  if (unknown130) {
    // `fov` and `size` are copies: the game keeps both values in stack slots and passes their addresses; with the members passed directly the function has 230 instructions.
    f32 fov = m_fov;
    f32 size = m_nearClip;
    CameraUtilities::updateCollision(m_coliCheckConfig, unknownb0, unknown110, fov, size);
  }
  setLookAt(unknownb0, delta + unknownb0, 0.0f);
}

// 1.0.0: 0x71001d6854, 62 instructions. The single-use `speed` places the call of fastOut/slowOut before the loads of start and end (0x71001d689c, 0x71001d68b4: the game loads them after
// sinf; without it 58 instructions). `(end - start) * 0.5f` is written at each use: a local `half` gives 9 differing lines (x20 and x21 swapped, the product renamed to s3).
void FusionComboCamera::calcSpeedTypeSlowInSlowOut(const f32 &start, const f32 &end, f32 t, f32 &result) {
  if (t < 0.5f) {
    f32 speed = fastOut(t + t);
    result = start + (end - start) * 0.5f * speed;
  } else {
    f32 speed = slowOut((t - 0.5f) * 2.0f);
    result = start + (end - start) * 0.5f + (end - start) * 0.5f * speed;
  }
}

f32 FusionComboCamera::slowInSlowOut(f32 t) {
  if (t < 0.5f) {
    return fastOut(t * 2.0f);
  }
  return slowOut((t - 0.5f) * 2.0f);
}

bool FusionComboCamera::isPlayEnd() const { return unknown120 <= unknown124; }

// 1.0.0: 0x71001d60e0, 63 instructions. The game rotates the opposite direction (the negated unit axis, rotated in place by mm::unknown010) and passes it with a copy of the axis. `direction`
// is declared before `reference`: the game keeps the copy of the axis at sp and the direction above it. The other order has 12 lines of difference; `direction = rotation.rotate(...)`
// has 30 (axis first) or 78 (direction first).
f32 FusionComboCamera::getYaw(const mm::Quat &rotation) {
  mm::Vec3 direction;
  mm::Vec3 reference = mm::Vec3::unitZ;
  direction = mm::Vec3(-reference.x, -reference.y, -reference.z);
  mm::unknown010(rotation, direction);
  return getYaw(direction, reference);
}

void FusionComboCamera::getAxis(const mm::Vec3 &from, const mm::Vec3 &to, mm::Vec3 &axis) {
  mm::Vec3 first = from;
  mm::Vec3 second = to;
  if (!first.unknown003() && !second.unknown003()) {
    first.unknown002();
    second.unknown002();
    axis.unknown004(second, first);
  }
}

f32 FusionComboCamera::getYaw(const mm::Vec3 &direction, const mm::Vec3 &reference) {
  mm::Vec3 from(direction.x, 0.0f, direction.z);
  mm::Vec3 to(reference.x, 0.0f, reference.z);
  if ((fabsf(from.x) <= 0.000001f && fabsf(from.z) <= 0.000001f) || (fabsf(to.x) <= 0.000001f && fabsf(to.z) <= 0.000001f)) {
    return 0.0f;
  }
  from.unknown002();
  to.unknown002();
  f32 cosine = to.x * from.x + to.y * from.y + to.z * from.z;
  mm::clampRef(cosine, -1.0f, 1.0f);
  f32 angle = mm::acos(cosine);
  return from.x * to.z - from.z * to.x < 0.0f ? 6.2831855f - angle : angle;
}

f32 FusionComboCamera::getPitch(const mm::Vec3 &direction, const mm::Vec3 &reference) {
  f32 yaw = getYaw(direction, reference);
  mm::Vec3 from = direction;
  mm::Vec3 to = reference;
  mm::Quat rotation;
  rotation.x = 0.0f;
  rotation.y = sinf(yaw * -0.5f);
  rotation.z = 0.0f;
  rotation.w = cosf(yaw * -0.5f);
  from = rotation.rotate(from);
  from.unknown001();
  to.unknown001();
  f32 cosine = to.x * from.x + to.y * from.y + to.z * from.z;
  mm::clampRef(cosine, -1.0f, 1.0f);
  f32 angle = mm::acos(cosine);
  return from.z * to.y - from.y * to.z < 0.0f ? -angle : angle;
}

f32 FusionComboCamera::fastOut(f32 t) {
  f32 x = sinf(t * 1.5707964f + 4.712389f) + 1.0f;
  return x + (1.0f - x) * 0.0f;
}

// 1.0.0: 0x71001d6f14, 21 instructions. The single-use local `angle` is the case of decisions 44 and 57 (a named variable whose only effect comes from its DBG_VALUE under -g). Measured with
// -mllvm -print-after-all on the unit with and without it, ignoring debug values and locations: for update, calcSpeedTypeSlowInSlowOut and slowInSlowOut (which inline slowOut) the IR and every
// machine pass up to and including register allocation are identical; the first pass that differs is the A57 FP anti-dependency breaker, which renames the product of the inlined copy to s3
// (`fmul s3, s0, s1; fadd s0, s3, s1`) where the game has `fmul s0, s0, s1; fadd s0, s0, s1` in each inlined copy. Without the local update differs from 0x71001d65fc (234 instructions),
// calcSpeedTypeSlowInSlowOut from 0x71001d687c (64 instructions against 62) and slowInSlowOut from 0x71001d6e9c; slowOut itself matches either way.
f32 FusionComboCamera::slowOut(f32 t) {
  f32 angle = (1.0f - t) * 1.5707964f;
  f32 x = sinf(angle + 4.712389f) + 1.0f;
  return 1.0f - (x + (1.0f - x) * 0.0f);
}

f32 FusionComboCamera::curve(f32 a, f32 b, f32 t) {
  f32 x = sinf(t * 1.5707964f + 4.712389f) + 1.0f;
  return (1.0f - x) * a + x * b;
}

const mm::mtl::RTTI *FusionComboCamera::getRTTI() const { return &m_rtti; }

const char *FusionComboCamera::getName() const { return "FusionComboCamera"; }

} // namespace gf
