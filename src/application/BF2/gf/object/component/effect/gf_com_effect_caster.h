#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "framework/reference_frame.h"
#include "gf/object/component/effect/gf_effect_ground.h"
#include "gf/object/component/gf_component.h"
#include "gf/object/component/property/gf_env_property.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace anm {
class ResASM;
}

namespace fw {
class EffectCasterBase;
class EffectPack;
class EffectPoint;
struct EffectResData;
} // namespace fw

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ml {
class WinProc;
} // namespace ml

namespace gf {

struct GF_OBJ_HANDLE;
struct GF_ASSET_HANDLE;
struct MsgFxRimBloomEnd;
struct MsgFxRimBloomTarget : fw::Message {
  MsgFxRimBloomTarget() : fw::Message(0x1000054, 0x80) {}
};

// Layout evidence: GfComEffectCaster::procMsgFxRimBloom reads the member at 0x08 and the flag at 0x0c and sets the flag at 0x0d.
struct MsgFxRimBloom : fw::Message {
  u32 unknown08;  // Inferred role: rim bloom state; original member name unknown.
  bool unknown0c; // Inferred role: force; original member name unknown.
  bool unknown0d; // Inferred role: accepted; original member name unknown.
};

struct MsgObjectNotifyDamage;
struct MsgObjectNotifyDead;

struct EffectMountSetupEv {
  EffectMountSetupEv() : unknown30(mm::Vec3::zero), _40(), unknown41(false), unknown42(false) {}

  // Inferred roles from access offsets; original member names are unknown.
  u32 unknown0;                 // Effect identifier.
  mm::mtl::FixStr<32> unknown8; // Bone name.
  mm::Vec3 unknown30;           // Offset.
  u8 _40[0x41 - 0x40];
  bool unknown41; // Rotation enabled.
  bool unknown42; // Follow enabled.
};

static_assert(offsetof(EffectMountSetupEv, unknown30) == 0x30, "");
static_assert(offsetof(EffectMountSetupEv, unknown41) == 0x41, "");

struct MsgFxFootPrint : fw::Message {
  MsgFxFootPrint(GfEnvProperty::GROUND_INDEX ground) : fw::Message(0x1000049, 0x80), unknown08(ground) {}

  GfEnvProperty::GROUND_INDEX unknown08; // Inferred role: foot ground index; original member name unknown.
  bool unknown0c;                        // Inferred role: rapid step; original member name unknown.
};

static_assert(offsetof(MsgFxFootPrint, unknown08) == 0x08, "");
static_assert(offsetof(MsgFxFootPrint, unknown0c) == 0x0c, "");

// Message id from GfComEffectCaster::recieveMessage (0x7100503300), whose case 0x100004c is procMsgFxCombo inlined.
struct MsgFxCombo : fw::Message {
  MsgFxCombo() : fw::Message(0x100004c, 0x80), unknown08(0) {}

  u32 unknown08;         // Role and original member name unknown.
  const char *unknown10; // Inferred role: effect name; original member name unknown.
  u32 unknown18;         // Inferred role: started effect handle; original member name unknown.
};

static_assert(offsetof(MsgFxCombo, unknown08) == 0x08, "");
static_assert(offsetof(MsgFxCombo, unknown10) == 0x10, "");
static_assert(offsetof(MsgFxCombo, unknown18) == 0x18, "");

// Message id from GfComEffectCaster::recieveMessage (0x7100503300), whose case 0x100004d is procMsgFxComboBuff inlined.
struct MsgFxComboBuff : fw::Message {
  MsgFxComboBuff() : fw::Message(0x100004d, 0x80), unknown08(0) {}

  u32 unknown08;         // Role and original member name unknown.
  const char *unknown10; // Inferred role: effect name; original member name unknown.
};

static_assert(offsetof(MsgFxComboBuff, unknown08) == 0x08, "");
static_assert(offsetof(MsgFxComboBuff, unknown10) == 0x10, "");

class GfComEffectCaster : public GfComponent {
public:
  // Layout evidence: effectStart (0x7100506604) builds it before its copy ctor (0x710050b090); the copy ctor and
  // operator= (0x710050af14) copy the two FixStr, the IntrusivePtr at 0x60 and the Vec3 members one by one and the other
  // members by blocks (0x24-0x34, 0x58, 0x68-0x74, 0xa0-0xc0).
  struct Param {
    mm::mtl::FixStr<32> unknown00;                       // Inferred role: effect name; original member name unknown.
    f32 unknown24;                                       // Inferred role: timer state, -1 without a life time; original member name unknown.
    f32 unknown28;                                       // Inferred role: elapsed second; original member name unknown.
    f32 unknown2c;                                       // Inferred role: life time; original member name unknown.
    f32 unknown30;                                       // Inferred role: speed; original member name unknown.
    mm::mtl::FixStr<32> unknown34;                       // Inferred role: point name; original member name unknown.
    u32 unknown58;                                       // Inferred role: effect identifier; original member name unknown.
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> unknown60; // Inferred role: point reference frame; original member name unknown.
    u16 unknown68;                                       // Inferred role: caster type; original member name unknown.
    u16 unknown6a;                                       // Inferred role: setup value; original member name unknown.
    u8 unknown6c;                                        // Inferred role: setup flag; original member name unknown.
    u8 unknown6d;                                        // Inferred role: setup flag; original member name unknown.
    bool unknown6e;                                      // Inferred role: point name bound; original member name unknown.
    u8 unknown6f;                                        // Inferred role: setup flag; original member name unknown.
    f32 unknown70;                                       // Inferred role: scale; original member name unknown.
    mm::Vec3 unknown80;                                  // Inferred role: offset; original member name unknown.
    mm::Vec3 unknown90;                                  // Inferred role: second setup vector; original member name unknown.
    u8 unknowna0;                                        // Inferred role: setup flag; original member name unknown.
    u8 unknowna1;                                        // Inferred role: setup flag; original member name unknown.
    u8 unknowna2;                                        // Inferred role: setup flag; original member name unknown.
    u8 unknowna3;                                        // Inferred role: setup flag; original member name unknown.
    GF_OBJ_HANDLE *unknowna8;                            // Inferred role: target handle; original member name unknown.
    GF_OBJ_HANDLE *unknownb0;                            // Inferred role: weapon handle; original member name unknown.
    bool unknownb8;                                      // Inferred role: follow the caster; original member name unknown.
    u8 unknownb9;                                        // Inferred role: ground type; original member name unknown.
    bool unknownba;                                      // Inferred role: effect ended; original member name unknown.
    bool unknownbb;                                      // Inferred role: state flag; original member name unknown.
    bool unknownbc;                                      // Inferred role: state flag; original member name unknown.
    bool unknownbd;                                      // Inferred role: state flag; original member name unknown.
    bool unknownbe;                                      // Inferred role: state flag; original member name unknown.
    bool unknownbf;                                      // Inferred role: state flag; original member name unknown.
  };

  // Layout evidence: getWeaponEffectPack (0x710050a6ac) reads the effect pack at 0x00 and the type at 0x08 of each entry.
  struct unknown001 {
    fw::EffectPack *unknown00; // Inferred role: weapon effect pack; original member name unknown.
    s32 unknown08;             // Inferred role: weapon effect type; original member name unknown.
  };

  // Layout evidence: addMountEffectEv (0x7100509768) builds it from an EffectMountSetupEv before pushing it into the
  // FixedVector at 0xc3b0; operator= (0x710050b1bc) copies the FixStr, the u32 at 0x24, the IntrusivePtr at 0x28, the
  // Vec3 and the three bytes at 0x40.
  struct EventEfHandleTbl {
    mm::mtl::FixStr<32> unknown00;                       // Inferred role: bone name; original member name unknown.
    u32 unknown24;                                       // Inferred role: effect identifier; original member name unknown.
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> unknown28; // Inferred role: bone reference frame; original member name unknown.
    mm::Vec3 unknown30;                                  // Inferred role: offset; original member name unknown.
    u8 unknown40;                                        // Inferred role: setup byte; original member name unknown.
    bool unknown41;                                      // Inferred role: rotation enabled; original member name unknown.
    bool unknown42;                                      // Inferred role: follow enabled; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 7;

  static void registerAsmCallbackEffect(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm, fw::EffectResData *effectData);
  bool getEfpMatrix(const char *name, mm::Mat44 &matrix);
  void addMountEffectEv(const EffectMountSetupEv &setup);
  void removeMountEffectEv(u32 effect);
  u32 calcWeaponID() const;
  void setCaster(u32 effect);
  bool setSpeed(u32 effect, f32 speed);
  f32 getElapsedSecond(u32 effect);
  bool startTimer(u32 effect);
  bool stopTimer(u32 effect);
  bool addCasterEffectEv(u32 effect);
  void effectEnd(u32 effect);
  void procMsgObjectNotifyDamage(fw::MessageObject *object, MsgObjectNotifyDamage &message);
  void procMsgObjectNotifyDead(fw::MessageObject *object, MsgObjectNotifyDead &message);
  void procMsgFxRimBloomEnd(fw::MessageObject *object, MsgFxRimBloomEnd &message);
  void procMsgFxRimBloomTarget(fw::MessageObject *object, MsgFxRimBloomTarget &message);
  void procMsgFxRimBloom(fw::MessageObject *object, MsgFxRimBloom &message);
  void openDebugWindow(ml::WinProc *window);
  fw::EffectPack *getEffectPack(GF_ASSET_HANDLE *handle);
  const char *getEfpData(const char *name, mm::Mat44 &matrix);
  bool getWeaponEffectPack(mm::mtl::FixedVector<fw::EffectPack *, 8> &packs, int type, int);
  fw::EffectPoint *getEffectPoint();
  bool getValidEffectName(const char *name) const;
  bool isDynamicAnnotationEffect(u8 type) const;
  bool getDynamicAnnotationEffectFileName(u8 type, const char *&fileName) const;
  u32 convertSwimEffectState(GfEffectGround::SwimEffectState state);
  Param *findEffectCasterParam(u32 effect);
  GF_OBJ_HANDLE *getWeaponHandle(u16 weapon);
  void getWpnMatOld1(mm::Mat44 &matrix);
  void getWpnMatOld2(mm::Mat44 &matrix);

  u8 _10[0x14 - 0x10];
  bool unknown14; // Inferred role: rim bloom active; original member name unknown.
  u8 _15[0x18 - 0x15];
  u32 unknown18; // Inferred role: rim bloom state; original member name unknown.
  f32 unknown1c; // Inferred role: rim bloom time; original member name unknown.
  f32 unknown20; // Inferred role: rim bloom duration; original member name unknown.
  f32 unknown24; // Inferred role: water depth threshold of the first swim state; original member name unknown.
  f32 unknown28; // Inferred role: water depth threshold of the second swim state; original member name unknown.
  u8 _2c[0x40 - 0x2c];
  mm::mtl::FixedVector<unknown001, 52> unknown40; // Inferred role: weapon effect packs; original member name unknown.
  fw::EffectCasterBase *unknown388;               // Inferred role: effect caster; original member name unknown.
  fw::EffectPoint *unknown390;                    // Inferred role: effect point; original member name unknown.
  u8 _398[0x3a0 - 0x398];
  mm::mtl::FixedVector<Param, 256> unknown3a0;             // Inferred role: caster params; original member name unknown.
  mm::mtl::FixedVector<EventEfHandleTbl, 256> unknownc3b0; // Inferred role: mount effects; original member name unknown.
  u8 _113c0[0x113d0 - 0x113c0];
  mm::Mat44 unknown113d0; // Inferred role: weapon matrix of the previous frame; original member name unknown.
  mm::Mat44 unknown11410; // Inferred role: second weapon matrix of the previous frame; original member name unknown.
};

static_assert(offsetof(GfComEffectCaster, unknown14) == 0x14, "");
static_assert(offsetof(GfComEffectCaster, unknown18) == 0x18, "");
static_assert(offsetof(GfComEffectCaster, unknown1c) == 0x1c, "");
static_assert(offsetof(GfComEffectCaster, unknown20) == 0x20, "");
static_assert(offsetof(GfComEffectCaster, unknown24) == 0x24, "");
static_assert(offsetof(GfComEffectCaster, unknown28) == 0x28, "");
static_assert(offsetof(GfComEffectCaster, unknown40) == 0x40, "");
static_assert(offsetof(GfComEffectCaster, unknown388) == 0x388, "");
static_assert(offsetof(GfComEffectCaster, unknown390) == 0x390, "");
static_assert(offsetof(GfComEffectCaster, unknown3a0) == 0x3a0, "");
static_assert(offsetof(GfComEffectCaster, unknownc3b0) == 0xc3b0, "");
static_assert(offsetof(GfComEffectCaster, unknown113d0) == 0x113d0, "");
static_assert(offsetof(GfComEffectCaster, unknown11410) == 0x11410, "");
static_assert(offsetof(GfComEffectCaster::Param, unknown24) == 0x24, "");
static_assert(offsetof(GfComEffectCaster::Param, unknown28) == 0x28, "");
static_assert(offsetof(GfComEffectCaster::Param, unknown30) == 0x30, "");
static_assert(offsetof(GfComEffectCaster::Param, unknown34) == 0x34, "");
static_assert(offsetof(GfComEffectCaster::Param, unknown58) == 0x58, "");
static_assert(offsetof(GfComEffectCaster::Param, unknown60) == 0x60, "");
static_assert(offsetof(GfComEffectCaster::Param, unknown68) == 0x68, "");
static_assert(offsetof(GfComEffectCaster::Param, unknown6a) == 0x6a, "");
static_assert(offsetof(GfComEffectCaster::Param, unknown6e) == 0x6e, "");
static_assert(offsetof(GfComEffectCaster::Param, unknown70) == 0x70, "");
static_assert(offsetof(GfComEffectCaster::Param, unknown80) == 0x80, "");
static_assert(offsetof(GfComEffectCaster::Param, unknown90) == 0x90, "");
static_assert(offsetof(GfComEffectCaster::Param, unknowna0) == 0xa0, "");
static_assert(offsetof(GfComEffectCaster::Param, unknowna8) == 0xa8, "");
static_assert(offsetof(GfComEffectCaster::Param, unknownb0) == 0xb0, "");
static_assert(offsetof(GfComEffectCaster::Param, unknownb8) == 0xb8, "");
static_assert(offsetof(GfComEffectCaster::Param, unknownba) == 0xba, "");
static_assert(offsetof(GfComEffectCaster::Param, unknownbf) == 0xbf, "");
static_assert(sizeof(GfComEffectCaster::Param) == 0xc0, "");
static_assert(offsetof(GfComEffectCaster::EventEfHandleTbl, unknown24) == 0x24, "");
static_assert(offsetof(GfComEffectCaster::EventEfHandleTbl, unknown28) == 0x28, "");
static_assert(offsetof(GfComEffectCaster::EventEfHandleTbl, unknown30) == 0x30, "");
static_assert(offsetof(GfComEffectCaster::EventEfHandleTbl, unknown40) == 0x40, "");
static_assert(offsetof(GfComEffectCaster::EventEfHandleTbl, unknown42) == 0x42, "");
static_assert(sizeof(GfComEffectCaster::EventEfHandleTbl) == 0x50, "");

} // namespace gf
