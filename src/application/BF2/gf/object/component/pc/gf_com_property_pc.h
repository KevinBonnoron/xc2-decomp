#pragma once
#include <stddef.h>

#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/property/gf_com_property.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "types.h"

namespace anm {
struct QsTransform;
} // namespace anm

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

namespace pc {

enum InputID {
  INPUT_ID_DECIDE = 0,
  INPUT_ID_LOCK = 1,
  INPUT_ID_JUMP = 2,
  INPUT_ID_WALL_RELEASE = 3,
  INPUT_ID_LURE = 4,
  INPUT_ID_BATTLE_START = 5,
  INPUT_ID_BATTLE_END = 6,
  INPUT_ID_ART_01 = 7,
  INPUT_ID_ART_02 = 8,
  INPUT_ID_ART_03 = 9,
  INPUT_ID_BLADE_CHANGE_00 = 10,
  INPUT_ID_BLADE_CHANGE_01 = 11,
  INPUT_ID_BLADE_CHANGE_02 = 12,
  INPUT_ID_KAKUSEI = 13,
  INPUT_ID_REQUEST_PERMIT_01 = 14,
  INPUT_ID_REQUEST_PERMIT_02 = 15,
  INPUT_ID_SP_ATTACK = 16,
  INPUT_ID_CHAIN_ATTACK = 17,
  INPUT_ID_BATTLE_RESCUE = 18,
  INPUT_ID_CHANGE_CAMERA_MODE = 19,
  INPUT_ID_ORDER_RALLY = 20,
  INPUT_ID_CHANGE_TARGET_R = 21,
  INPUT_ID_CHANGE_TARGET_L = 22,
};

} // namespace pc

class GfComPropertyPc : public GfComProperty {
public:
  struct Input {
    f32 x;
    f32 y;
    mm::mtl::BitFlag<32> flags;
  };

  static mm::mtl::RTTI m_rtti;

  bool existInputXY() const;
  void setLocomotion(const anm::QsTransform &locomotion);
  void setEnvSensorCheckFlags(u32 flags, bool isEnable);

  u8 _38[0x60 - 0x38];
  Input input;
  Input previousInput;
  u8 _78[0x80 - 0x78];
  mm::Vec3 velocity;
  f32 verticalSpeed;
  f32 horizontalSpeed;
  u8 _98[0x110 - 0x98];
  u32 isFieldControl : 1;
  u32 isBattleControl : 1;
  u32 : 1;
  u32 isEnableGravity : 1;
  u32 : 6;
  u32 isPadControl : 1;
  u32 : 21;
  u8 _114[0x160 - 0x114];
  mm::Vec3 position;
  u8 _170[0x310 - 0x170];
  pc::GfPropertyField field;
};

static_assert(offsetof(GfComPropertyPc, input) == 0x60, "");
static_assert(offsetof(GfComPropertyPc, previousInput) == 0x6c, "");
static_assert(offsetof(GfComPropertyPc, velocity) == 0x80, "");
static_assert(offsetof(GfComPropertyPc, verticalSpeed) == 0x90, "");
static_assert(offsetof(GfComPropertyPc, horizontalSpeed) == 0x94, "");
static_assert(offsetof(GfComPropertyPc, position) == 0x160, "");
static_assert(offsetof(GfComPropertyPc, field) == 0x310, "");

} // namespace gf
