#pragma once
#include <stddef.h>

#include "framework/coli/coli_object.h"
#include "framework/sensor/sensor_manager.h"
#include "fw/fw_coli_check.h"
#include "fw/fw_param_manager.h"
#include "fw/fw_transform.h"
#include "gf/object/component/gf_component.h"
#include "gf/object/component/property/gf_env_property.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/unique_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
class MessageObject;
class Reflection;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;

// Name from the game symbol _ZNSt3__16__sortIRN2gf11ContactLessEPN2fw11ContactInfoEEEvT0_S7_T_ (1.0.0: 0x710051fe78): the comparison functor of the std::sort of the hits of a ray test
// (searchVertical, 0x710051e1e0, builds it from the address of the packet's direction at +0x10: `stur x21, [x29, #-88]` and passes its address to __sort). Layout evidence: __sort3 (0x71005209bc)
// loads the pointer at 0x00 of the functor and compares the dot products of that vector with the first three floats of the two elements (orders the hits by distance along the direction).
struct ContactLess {
  explicit ContactLess(const mm::Vec3 *direction) : unknown00(direction) {}

  bool operator()(const fw::ContactInfo &a, const fw::ContactInfo &b) const {
    return unknown00->x * a.position.x + unknown00->y * a.position.y + unknown00->z * a.position.z < unknown00->x * b.position.x + unknown00->y * b.position.y + unknown00->z * b.position.z;
  }

  const mm::Vec3 *unknown00; // Inferred role: direction the hits are ordered along; original member name unknown.
};

// Layout evidence: GfComEnvSensor::GfComEnvSensor() constructs the sensor at +0x10 and the next member at +0x2b0;
// EnviromentSensor::EnviromentSensor() clears +0x20, constructs VerticalData at +0x30 and a GroundInfo at +0x1f0 and
// stores 1.0f at +0x290; GroundInfo::GroundInfo() and VerticalData::VerticalData() store the fields below
// (VerticalData::VerticalData() runs the constructors of the water info at +0x70 and of the ceiling info at +0xe0 after the out-of-line GroundInfo::GroundInfo(); the dead plane info at +0xb0 is not
// initialised). check() (1.0.0: 0x710051dc98) copies its transform parameter to +0x00 (three words of the position, two doublewords of the rotation) and clears the state word at +0x24. The info
// offsets are the ones StateUtil::get*Info() add to the sensor, selected by a bit of the state word at +0x24.
class EnviromentSensor {
public:
  EnviromentSensor();

  enum Flag {};

  struct GroundInfo {
    // Inline: the game only has the base object constructor symbol (C2) of this one, called out of line by VerticalData::VerticalData() and EnviromentSensor::EnviromentSensor().
    GroundInfo() : unknown00(mm::Vec3::zero), unknown30(0), unknown34(0), m_GF_OBJ_HANDLE(unknown020), unknown40(mm::Vec3::zero), unknown50(mm::Col4::white), unknown60(0) {
      unknown10.set(mm::Vec3::zero, mm::Vec3::unitY);
    }

    mm::Vec3 unknown00;  // Inferred role: position; original member name unknown.
    mm::Plane unknown10; // Inferred role: plane; original member name unknown.
    // Two words, not one u64: EnviromentSensor::check() (1.0.0: 0x710051dc98) copies only the low word of the found plane flags into +0x220 (ldr w, str w) and writeBackProperty()
    // (0x710051fcb0) splits this doubleword into the two ints of GfEnvProperty::unknown002 (unknown30 and unknown34).
    u32 unknown30;                  // Inferred role: flags, bit 4 is tested by StateUtilField::isWallDetach, bit 5 is the slide flag; original member name unknown.
    u32 unknown34;                  // Inferred role: ground material; original member name unknown.
    GF_OBJ_HANDLE *m_GF_OBJ_HANDLE; // Inferred role: object handle; original member name unknown.
    mm::Vec3 unknown40;             // Inferred role: unknown vector; original member name unknown.
    mm::Col4 unknown50;             // Inferred role: color; original member name unknown.
    u32 unknown60;                  // Inferred role: unknown; original member name unknown.
  };

  // Inferred role: water info; original type name unknown.
  // The constructor is the one VerticalData::VerticalData() (1.0.0: 0x710051d95c) runs at +0x70; the game has no symbol for it (always inlined). Written inline in the body of
  // VerticalData::VerticalData() the plane distance gets its operands in the other order (normal * position; 126 instructions, the three fmul and two fadd operand pairs swapped):
  // clang optimises (and so Reassociates) a constructor on its own before inlining it, which gives the game's order (position * normal).
  struct unknown001 {
    unknown001() : unknown00(0.0f), unknown30(fw::COLI_INVALID_DAMAGE_ID), unknown34(0), unknown38(0) { unknown10.set(mm::Vec3::zero, mm::Vec3::unitY); }

    f32 unknown00;       // Inferred role: water height; original member name unknown.
    mm::Plane unknown10; // Inferred role: plane; original member name unknown.
    u32 unknown30;       // Inferred role: damage id; original member name unknown.
    u32 unknown34;       // Inferred role: unknown; original member name unknown.
    u32 unknown38;       // Inferred role: unknown; original member name unknown.
  };

  // Inferred role: dead plane info, written by searchVertical with the state bit 2; original type name unknown.
  struct unknown002 {
    mm::Vec3 unknown00;  // Inferred role: position; original member name unknown.
    mm::Plane unknown10; // Inferred role: plane; original member name unknown.
  };

  // Inferred role: horizontal wall info, written by searchHorizon (and copied from the descend wall packet by
  // StateUtilField::isWallAdsorptionUnderWall); original type name unknown.
  struct unknown003 {
    mm::Plane unknown00; // Inferred role: wall plane; original member name unknown.
    f32 unknown20;       // Inferred role: signed distance of the search position to the plane; original member name unknown.
    union {
      u32 unknown24; // Inferred role: flags; original member name unknown.
      struct {
        u32 : 4;
        u32 unknown24_4 : 1; // Inferred role: valid; original member name unknown.
        u32 : 1;
        u32 unknown24_6 : 1; // Inferred role: unknown; original member name unknown.
        u32 unknown24_7 : 1; // Inferred role: sent to the wall sound variable by StateFieldWall::flushWallType; original member name unknown.
        u32 : 24;
      };
    };
  };

  // Inferred role: ceiling info, written by searchVertical with the state bit 3; original type name unknown.
  // The constructor is the one VerticalData::VerticalData() (1.0.0: 0x710051d95c) runs at +0xe0, written like the one of unknown001 for the same reason.
  struct unknown005 {
    unknown005() : unknown00(0.0f), unknown30(0) { unknown10.set(mm::Vec3::zero, mm::Vec3::unitY); }

    f32 unknown00;       // Inferred role: height; original member name unknown.
    mm::Plane unknown10; // Inferred role: plane; original member name unknown.
    u32 unknown30;       // Inferred role: unknown; original member name unknown.
  };

  // Layout evidence: EnviromentSensor::check() passes +0x150 to searchHorizon as the result of the packet, and
  // searchHorizon writes the planes at +0x00 (bit 4), +0x30 (bit 5) and +0x60 (bit 6, climb wall) and the handle at +0x90;
  // original type name unknown.
  struct unknown006 {
    unknown003 unknown00;           // Inferred role: horizontal wall info (search bit 4); original member name unknown.
    unknown003 unknown30;           // Inferred role: horizontal info of the search bit 5; original member name unknown.
    unknown003 unknown60;           // Inferred role: climb wall info (search bit 6); original member name unknown.
    GF_OBJ_HANDLE *m_GF_OBJ_HANDLE; // Inferred role: climb wall object handle, unknown020 when none; original member name unknown.
  };

  // Field names and offsets from the reflection built by gf::EnviromentSensor::Parameter::createReflection; the names are
  // the reflection strings of the game.
  struct Parameter {
    static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

    f32 searchVertUp;
    f32 searchVertDown;
    f32 obstacleHeightBase;
    f32 obstacleHeightJump;
    f32 obstacleSearchLength;
    f32 wallEndHeight;
    f32 wallEndMoveDist;
    f32 wallEndSearchDown;
    f32 descendWallSearchFront;
    f32 descendWallSearchDown;
    f32 descendWallSearchDist;
  };

  // Layout evidence: StateUtilField::isWallAdsorption fills it and passes it to searchHorizon, whose accesses are the
  // offsets below.
  struct HorizonPacket {
    HorizonPacket() : unknown24(0.0f), unknown34(0), unknown38(nullptr) {}

    u32 unknown00; // Inferred role: requested searches (bits 4, 5 and 6); original member name unknown.
    u8 _04[0x10 - 0x04];
    mm::Vec3 unknown10;    // Inferred role: search direction; original member name unknown.
    f32 unknown20;         // Inferred role: start distance along the direction; original member name unknown.
    f32 unknown24;         // Inferred role: end distance along the direction; original member name unknown.
    f32 unknown28;         // Inferred role: height offset of the search bit 4; original member name unknown.
    f32 unknown2c;         // Inferred role: height offset of the search bit 5; original member name unknown.
    f32 unknown30;         // Inferred role: height offset of the search bit 6; original member name unknown.
    u32 unknown34;         // Inferred role: found searches, same bits as the request; original member name unknown.
    unknown006 *unknown38; // Inferred role: result; original member name unknown.
  };

  // Layout evidence: StateUtilField::isWallAdsorptionUnderWall fills it and passes it to searchWallUnderGround (and searchGroundWallEnd, 0x710051f448), whose
  // accesses are the offsets below (the request bits are read with byte loads, `ldrb w8, [x19]; tbz w8, #7` and `ldrb w8, [x19, #1]; tbz w8, #0`).
  struct WallPacket {
    WallPacket() : unknown40(0.0f), unknown44(0.0f), unknown48(0.0f), unknown4c(0.0f), unknown50(0) {}

    union {
      u32 unknown00; // Inferred role: requested searches; original member name unknown.
      struct {
        u32 : 7;
        u32 unknown00_7 : 1; // Inferred role: request of the descend wall search (searchWallUnderGround); original member name unknown.
        u32 unknown01_0 : 1; // Inferred role: request of the ground wall end search (searchGroundWallEnd); original member name unknown.
        u32 : 23;
      };
    };
    u8 _04[0x10 - 0x04];
    mm::Vec3 unknown10; // Inferred role: direction of the wall; original member name unknown.
    mm::Vec3 unknown20; // Inferred role: direction of the search; original member name unknown.
    mm::Vec3 unknown30; // Inferred role: search offset; original member name unknown.
    f32 unknown40;      // Inferred role: start distance of the first segment; original member name unknown.
    f32 unknown44;      // Inferred role: end distance of the first segment; original member name unknown.
    f32 unknown48;      // Inferred role: start distance of the second segment; original member name unknown.
    f32 unknown4c;      // Inferred role: end distance of the second segment; original member name unknown.
    u32 unknown50;      // Inferred role: found searches, bit 7 (descend wall) and bit 8 (ground wall end); original member name unknown.
    u8 _54[0x60 - 0x54];
    mm::Vec3 unknown60;  // Inferred role: position of the found hit; original member name unknown.
    mm::Plane unknown70; // Inferred role: found plane; original member name unknown.
    u32 unknown90;       // Inferred role: flags of the material of the found hit; original member name unknown.
    u8 _94[0xa0 - 0x94];
  };

  // Layout evidence: EnviromentSensor::check() (1.0.0: 0x710051dc98) fills it at 0x00, 0x10, 0x20, 0x24, 0x28 and 0x30, reads 0x28 back after searchVertical and zeroes the rest in the
  // constructor (stores of 0x20 to 0x34 before the other fields); original type name unknown.
  struct VerticalData;
  struct VerticalPacket {
    VerticalPacket() : unknown20(0.0f), unknown24(0.0f), unknown28(0), unknown30(nullptr) {}

    u32 unknown00; // Inferred role: requested searches (the check flags of the sensor); original member name unknown.
    u8 _04[0x10 - 0x04];
    mm::Vec3 unknown10; // Inferred role: search direction; original member name unknown.
    f32 unknown20;      // Inferred role: start distance along the direction, minus Parameter::searchVertUp; original member name unknown.
    f32 unknown24;      // Inferred role: end distance along the direction, Parameter::searchVertDown; original member name unknown.
    u32 unknown28;      // Inferred role: found searches, same bits as the request; original member name unknown.
    u8 _2c[0x30 - 0x2c];
    VerticalData *unknown30; // Inferred role: result; original member name unknown.
  };

  static void searchVertical(const mm::Vec3 &position, VerticalPacket *packet);
  static void searchHorizon(const mm::Vec3 &position, HorizonPacket *packet);
  void check(const fw::Transform &transform, fw::ParamAdapter param);
  void writeBackProperty(bool isEnable, GfEnvProperty *property) const;
  static void searchWallUnderGround(const mm::Vec3 &position, WallPacket *packet);
  static void searchGroundWallEnd(const mm::Vec3 &position, WallPacket *packet);

  // Layout evidence: VerticalData::VerticalData() initializes the water info at +0x70 and the ceiling info at +0xe0.
  struct VerticalData : GroundInfo {
    // Inline: the game only has the base object constructor symbol (C2) of this one (0x710051d95c), called out of line by EnviromentSensor::EnviromentSensor(); out of line here the
    // complete object constructor C1 is emitted as a global symbol too, which the game does not have.
    VerticalData() {}

    unknown001 unknown70; // Inferred role: water info; original member name unknown.
    unknown002 unknownb0; // Inferred role: dead plane info; original member name unknown.
    unknown005 unknowne0; // Inferred role: ceiling info; original member name unknown.
  };

  fw::Transform m_transform; // Inferred role: transform of the last check; named after the type (AGENTS.md), check() (1.0.0: 0x710051dc98) copies its parameter here and the water depth reads its y.
  u32 m_envSensorCheckFlags;
  union {
    u32 unknown24; // Inferred role: state flags; original member name unknown.
    struct {
      u32 unknown24_0 : 1; // Inferred role: ground found; original member name unknown.
      u32 unknown24_1 : 1; // Inferred role: water found; original member name unknown.
      u32 unknown24_2 : 1; // Inferred role: dead plane found; original member name unknown.
      u32 unknown24_3 : 1; // Inferred role: ceiling found; original member name unknown.
      u32 unknown24_4 : 1; // Inferred role: horizontal wall found; original member name unknown.
      u32 unknown24_5 : 1; // Inferred role: horizontal info of +0x180 found; original member name unknown.
      u32 unknown24_6 : 1; // Inferred role: climb wall found; original member name unknown.
      u32 unknown24_7 : 1; // Inferred role: descend wall found; original member name unknown.
      u32 unknown25_0 : 1; // Inferred role: climb end ground found; original member name unknown.
      u32 : 23;
    };
  };
  VerticalData m_verticalData; // Inferred role: vertical ground data; original member name unknown.
  unknown006 unknown150;       // Inferred role: horizontal wall info; original member name unknown.
  GroundInfo m_groundInfo;     // Inferred role: climb end ground; original member name unknown.
  unknown003 unknown260;       // Inferred role: descend wall info; original member name unknown.
  f32 unknown290;              // Inferred role: unknown scale; original member name unknown.
  u8 _294[0x2a0 - 0x294];
};

static_assert(sizeof(EnviromentSensor::GroundInfo) == 0x70, "");
static_assert(offsetof(EnviromentSensor::GroundInfo, m_GF_OBJ_HANDLE) == 0x38, "");
static_assert(sizeof(EnviromentSensor::unknown001) == 0x40, "");
static_assert(sizeof(EnviromentSensor::unknown002) == 0x30, "");
static_assert(sizeof(EnviromentSensor::unknown003) == 0x30, "");
static_assert(sizeof(EnviromentSensor::unknown005) == 0x40, "");
static_assert(sizeof(EnviromentSensor::unknown006) == 0xa0, "");
static_assert(offsetof(EnviromentSensor::unknown006, m_GF_OBJ_HANDLE) == 0x90, "");
static_assert(sizeof(EnviromentSensor::Parameter) == 0x2c, "");
static_assert(offsetof(EnviromentSensor::Parameter, obstacleSearchLength) == 0x10, "");
static_assert(offsetof(EnviromentSensor::Parameter, descendWallSearchDist) == 0x28, "");
static_assert(offsetof(EnviromentSensor::HorizonPacket, unknown10) == 0x10, "");
static_assert(offsetof(EnviromentSensor::HorizonPacket, unknown30) == 0x30, "");
static_assert(offsetof(EnviromentSensor::HorizonPacket, unknown38) == 0x38, "");
static_assert(sizeof(EnviromentSensor::HorizonPacket) == 0x40, "");
static_assert(offsetof(EnviromentSensor::WallPacket, unknown30) == 0x30, "");
static_assert(offsetof(EnviromentSensor::WallPacket, unknown50) == 0x50, "");
static_assert(offsetof(EnviromentSensor::WallPacket, unknown60) == 0x60, "");
static_assert(offsetof(EnviromentSensor::WallPacket, unknown70) == 0x70, "");
static_assert(offsetof(EnviromentSensor::WallPacket, unknown90) == 0x90, "");
static_assert(offsetof(EnviromentSensor::VerticalPacket, unknown10) == 0x10, "");
static_assert(offsetof(EnviromentSensor::VerticalPacket, unknown28) == 0x28, "");
static_assert(offsetof(EnviromentSensor::VerticalPacket, unknown30) == 0x30, "");
static_assert(sizeof(EnviromentSensor::VerticalData) == 0x120, "");
static_assert(offsetof(EnviromentSensor, m_envSensorCheckFlags) == 0x20, "");
static_assert(offsetof(EnviromentSensor, m_transform) == 0x00, "");
static_assert(offsetof(EnviromentSensor, m_verticalData) == 0x30, "");
static_assert(offsetof(EnviromentSensor, unknown150) == 0x150, "");
static_assert(offsetof(EnviromentSensor, m_groundInfo) == 0x1f0, "");
static_assert(offsetof(EnviromentSensor, unknown260) == 0x260, "");
static_assert(offsetof(EnviromentSensor, unknown290) == 0x290, "");
static_assert(sizeof(EnviromentSensor) == 0x2a0, "");

// Inferred role: sensor of the enemies around the object, created by GfComEnvSensor::setup() as a one byte object; original member name unknown.
class GfEnemySensor {
public:
  u8 unknown00;
  void update(GF_OBJ_HANDLE *handle);
};

class GfComEnvSensor : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 11;

  // Layout evidence: flushFoot (0x710051b9a4) reads a scale at 0x00 and the heights of the ground search at 0x04 and 0x08 of the param entry at 0x2e8, flushFakeFoot (0x710051bdb0) the same
  // two heights, flushRootAfterMovement (0x710051c58c) the heights at 0x0c and 0x10; the size is not known. Original type name unknown.
  struct unknown001 {
    f32 unknown00; // Inferred role: scale of the foot offset; original member name unknown.
    f32 unknown04; // Inferred role: height above the foot of the ground search; original member name unknown.
    f32 unknown08; // Inferred role: depth below the foot of the ground search; original member name unknown.
    f32 unknown0c; // Inferred role: height above the root of the ground search; original member name unknown.
    f32 unknown10; // Inferred role: depth below the root of the ground search; original member name unknown.
  };

  class EnvListener {
  public:
    virtual void onWkStandbyLogout() { m_comEnvSensor->unknown368 = nullptr; }

    GfComEnvSensor *m_comEnvSensor; // Inferred role: owner; original member name unknown.
  };

  GfComEnvSensor();
  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  ~GfComEnvSensor() override;
  void cleanup();
  void changeLayer(u32 oldLayer, u32 newLayer) override;
  void flushRoot();
  void setEnableSensor(bool isEnable);
  void flushEnv(const fw::Transform &transform);
  void resolveTransform();
  void flushRootAfterMovement();
  void flushFoot();
  void flushFakeFoot();
  bool flushGroundSingle(GfEnvProperty *property, const mm::Vec3 &position, f32 up, f32 down, GfEnvProperty::GROUND_INDEX index);
  const fw::Transform &getTransform();
  const mm::mtl::RTTI *getRTTI() const override;

  EnviromentSensor m_envSensor; // Inferred role: sensor; named after the game accessor gf::GfComPropertyPc::getEnvSensor.
  u16 unknown2b0[6];            // Inferred role: bone indices; original member name unknown.
  s16 unknown2bc;               // Inferred role: root bone index, -1 when unset; original member name unknown. Signed: flushRootAfterMovement tests it with ldrsh (1.0.0: 0x710051c5a4).
  u32 unknown2c0[6];            // Inferred role: foot flags; original member name unknown.
  mm::mtl::IntrusivePtr<fw::ParamList> unknown2d8; // Inferred role: param list; original member name unknown.
  fw::ParamAdapter unknown2e0;                     // Inferred role: param entry of the environment sensor (EnviromentSensor::Parameter); original member name unknown.
  fw::ParamAdapter unknown2e8;                     // Inferred role: param entry of the foot search (unknown001); original member name unknown.
  fw::SensorUpdater unknown2f0;                    // Inferred role: updater before the game; original member name unknown.
  fw::SensorUpdater unknown328;                    // Inferred role: updater after the animation; original member name unknown.
  mm::mtl::UniquePtr<GfEnemySensor> unknown360;    // Inferred role: enemy sensor; original member name unknown.
  void *unknown368;                                // Inferred role: viewer; original member name unknown.
  EnvListener m_envListener;                       // Inferred role: viewer listener; original member name unknown.
};

static_assert(offsetof(GfComEnvSensor, m_envSensor) == 0x10, "");
static_assert(offsetof(GfComEnvSensor, unknown2b0) == 0x2b0, "");
static_assert(offsetof(GfComEnvSensor, unknown2c0) == 0x2c0, "");
static_assert(offsetof(GfComEnvSensor, unknown2d8) == 0x2d8, "");
static_assert(offsetof(GfComEnvSensor, unknown2f0) == 0x2f0, "");
static_assert(offsetof(GfComEnvSensor, unknown328) == 0x328, "");
static_assert(offsetof(GfComEnvSensor, unknown360) == 0x360, "");
static_assert(offsetof(GfComEnvSensor, unknown368) == 0x368, "");
static_assert(offsetof(GfComEnvSensor, m_envListener) == 0x370, "");
static_assert(sizeof(GfComEnvSensor) == 0x380, "");

} // namespace gf
