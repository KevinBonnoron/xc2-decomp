#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "framework/reference_frame.h"
#include "gf/object/component/effect/gf_effect_caster.h" // IWYU pragma: export
#include "gf/object/component/effect/gf_effect_ground.h"
#include "gf/object/component/gf_component.h"
#include "gf/object/component/property/gf_env_property.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace effect {
struct SendParam;
} // namespace effect

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

class GfObj;
struct CallBackCache;
struct GF_OBJ_HANDLE;
struct GF_ASSET_HANDLE;
struct MsgObjectNotifyAsmCallback;
// Layout evidence: CharaEffectPlayer::stopRimBloom (0x71000bbb04) stores id 0x1000053 and mask 0x80 as one 64-bit constant; the message has no other member.
struct MsgFxRimBloomEnd : fw::Message {
  MsgFxRimBloomEnd() : fw::Message(0x1000053, 0x80) {}
};

struct MsgFxRimBloomTarget : fw::Message {
  MsgFxRimBloomTarget() : fw::Message(0x1000054, 0x80) {}
};

// Layout evidence: WaterInPlugin::onEvent (0x710057cf0c) builds it on the stack: id 0x1000055, mask 0x80 and the flag at 0x08.
struct MsgFxSplashdown : fw::Message {
  explicit MsgFxSplashdown(bool isBig) : fw::Message(0x1000055, 0x80), unknown08(isBig) {}

  bool unknown08; // Inferred role: big splash; original member name unknown.
};

static_assert(offsetof(MsgFxSplashdown, unknown08) == 0x08, "");

// Layout evidence: GfComEffectCaster::procMsgFxRimBloom reads the member at 0x08 and the flag at 0x0c and sets the flag at 0x0d.
struct MsgFxRimBloom : fw::Message {
  // CharaEffectPlayer::playRimBloom (0x71000bc4a8) stores id 0x1000052 and mask 0x80, then the three members one by one before the component tests.
  MsgFxRimBloom() : fw::Message(0x1000052, 0x80) {}

  u32 unknown08;  // Inferred role: rim bloom state; original member name unknown.
  bool unknown0c; // Inferred role: force; original member name unknown.
  bool unknown0d; // Inferred role: accepted; original member name unknown.
};

struct MsgObjectNotifyDamage;
struct MsgObjectNotifyDead;

// Layout evidence: GfComEffectCaster::procMsgFxForceCancel (0x7100503888) reads only the annotation
// table; no member of this message is read.
struct MsgFxForceCancel : fw::Message {};

struct EffectMountSetupEv {
  EffectMountSetupEv() : unknown30(mm::Vec3::zero), unknown40(0), unknown41(false), unknown42(false) {}

  // Inferred roles from access offsets; original member names are unknown.
  u32 unknown0;                 // Effect identifier.
  mm::mtl::FixStr<32> unknown8; // Bone name.
  mm::Vec3 unknown30;           // Offset.
  u8 unknown40;                 // Setup byte, copied into GfComEffectCaster::EventEfHandleTbl by addMountEffectEv.
  bool unknown41;               // Rotation enabled.
  bool unknown42;               // Follow enabled.
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

// Layout evidence: CharaEvaPlayer::playFoot (0x71000cb06c) builds it on the stack: id 0x1000056, mask 0x80, the foot at 0x08 (0 for the right foot, 1 for the left) and the word at 0x0c zeroed;
// GfComEffectCaster::procMsgFxFootPrintEv (0x7100505088) reads the foot and stores the started effect handle at 0x0c.
struct MsgFxFootPrintEv : fw::Message {
  explicit MsgFxFootPrintEv(u32 foot) : fw::Message(0x1000056, 0x80), unknown08(foot), unknown0c(0) {}

  u32 unknown08; // Inferred role: foot (0 right, 1 left); original member name unknown.
  u32 unknown0c; // Inferred role: started effect handle; original member name unknown.
};

static_assert(offsetof(MsgFxFootPrintEv, unknown08) == 0x08, "");
static_assert(offsetof(MsgFxFootPrintEv, unknown0c) == 0x0c, "");

// Layout evidence: GfComBehavior::callbackAnim (0x71004fbc6c) builds it on the stack: id 0x1000050, mask 0x80, the flag at 0x08 (0 for weaponAttach, 1 for weaponDetach; the game zeroes the
// word at 0x0c with it), then the right and left option handles at 0x10 and 0x18.
struct MsgFxWeapon : fw::Message {
  MsgFxWeapon() : fw::Message(0x1000050, 0x80), unknown08(0), unknown0c(0) {}

  u32 unknown08;            // Inferred role: weapon detached; original member name unknown.
  u32 unknown0c;            // Role and original member name unknown.
  GF_OBJ_HANDLE *unknown10; // Inferred role: right option handle; original member name unknown.
  GF_OBJ_HANDLE *unknown18; // Inferred role: left option handle; original member name unknown.
};

static_assert(offsetof(MsgFxWeapon, unknown08) == 0x08, "");
static_assert(offsetof(MsgFxWeapon, unknown10) == 0x10, "");
static_assert(offsetof(MsgFxWeapon, unknown18) == 0x18, "");

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
  // Layout evidence: effectStart (0x7100506604) reads it, and procMessageAsmCallback (0x710050354c) and callbackImpl
  // (0x7100508db8) build it on the stack. The constructor inlined in callbackImpl (0x7100508e34-0x7100508e84) stores both
  // vectors from mm::Vec3::zero, the three pointers null, the scale 1.0 and the life time -1.0 (the callers overwrite
  // them, procMessageAsmCallback's block drops the dead stores), the speed 1.0, the type and flag bytes zero and the byte
  // at 0x4e true. The name comes from the mangled symbol of effectStart.
  struct EffectSetUp {
    EffectSetUp()
        : m_obj(nullptr), unknown28(nullptr), unknown30(nullptr), unknown38(1.0f), unknown3c(-1.0f), unknown40(1.0f), unknown44(0), unknown46(0), unknown48(0), unknown49(0), unknown4a(0),
          unknown4b(0), unknown4c(0), unknown4d(0), unknown4e(true), unknown4f(0) {
      unknown00 = mm::Vec3::zero;
      unknown10 = mm::Vec3::zero;
    }

    mm::Vec3 unknown00;              // Inferred role: offset; original member name unknown.
    mm::Vec3 unknown10;              // Inferred role: second vector; original member name unknown.
    GfObj *m_obj;                    // Inferred role: target object; original member name unknown.
    const char *unknown28;           // Inferred role: effect name; original member name unknown.
    fw::EffectCasterBase *unknown30; // Inferred role: effect caster; original member name unknown.
    f32 unknown38;                   // Inferred role: scale; original member name unknown.
    f32 unknown3c;                   // Inferred role: life time; original member name unknown.
    f32 unknown40;                   // Inferred role: speed; original member name unknown.
    u16 unknown44;                   // Inferred role: caster type; original member name unknown.
    u16 unknown46;                   // Inferred role: setup value; original member name unknown.
    u8 unknown48;                    // Inferred role: setup flag; original member name unknown.
    u8 unknown49;                    // Inferred role: setup flag; original member name unknown.
    u8 unknown4a;                    // Inferred role: setup flag; original member name unknown.
    u8 unknown4b;                    // Inferred role: setup flag; original member name unknown.
    u8 unknown4c;                    // Inferred role: setup flag; original member name unknown.
    u8 unknown4d;                    // Inferred role: scale is absolute; original member name unknown.
    bool unknown4e;                  // Inferred role: state flag; original member name unknown.
    u8 unknown4f;                    // Inferred role: ground type; original member name unknown.
  };

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
    EventEfHandleTbl() : unknown24(0), unknown30(mm::Vec3::zero), unknown40(0), unknown41(false), unknown42(false) {}

    mm::mtl::FixStr<32> unknown00;                       // Inferred role: bone name; original member name unknown.
    u32 unknown24;                                       // Inferred role: effect identifier; original member name unknown.
    mm::mtl::IntrusivePtr<fw::ReferenceFrame> unknown28; // Inferred role: bone reference frame; original member name unknown.
    mm::Vec3 unknown30;                                  // Inferred role: offset; original member name unknown.
    u8 unknown40;                                        // Inferred role: setup byte; original member name unknown.
    bool unknown41;                                      // Inferred role: rotation enabled; original member name unknown.
    bool unknown42;                                      // Inferred role: follow enabled; original member name unknown.
  };

  // Layout evidence: setupEfp (0x7100506134) reads the asset handle at 0x08 and the layer at 0x10.
  struct SetupInfo {
    u8 unknown00[0x08];
    GF_ASSET_HANDLE *unknown08; // Inferred role: asset handle; original member name unknown.
    u32 unknown10;              // Inferred role: layer; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 7;
  static void registerAsmCallbackEffect(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm, fw::EffectResData *effectData);
  void cleanup();
  void procMessageAsmCallback(fw::MessageObject *object, MsgObjectNotifyAsmCallback &message);
  void callbackImpl(const CallBackCache &cache);
  void setupEfp(const SetupInfo &info);
  bool getEfpMatrix(const char *name, mm::Mat44 &matrix);
  void calcMtxAndScale(GfComEffectCaster *caster, Param *param, f32 time, bool unknown, effect::SendParam &sendParam);
  u32 effectStart(const EffectSetUp &setup, const char *pointName);
  void updateParam(GfComEffectCaster *caster, Param *param, f32 time, bool unknown);
  void getWpnMat(mm::Mat44 &matrix);
  u32 calcFollowAnnotetionTag(Param *param, effect::SendParam &sendParam);
  void addMountEffectEv(const EffectMountSetupEv &setup);
  bool removeMountEffectEv(u32 effect);
  u32 calcWeaponID() const;
  void setCaster(u32 effect);
  bool setSpeed(u32 effect, f32 speed);
  f32 getElapsedSecond(u32 effect);
  bool startTimer(u32 effect);
  bool stopTimer(u32 effect);
  bool addCasterEffectEv(u32 effect);
  void effectEnd(u32 effect);
  void setupEfTail(u32 effect);
  void setupCaster(const fw::EffectPoint *point);
  void procMsgObjectNotifyDamage(fw::MessageObject *object, MsgObjectNotifyDamage &message);
  void procMsgObjectNotifyDead(fw::MessageObject *object, MsgObjectNotifyDead &message);
  void procMsgFxRimBloomEnd(fw::MessageObject *object, MsgFxRimBloomEnd &message);
  void procMsgFxRimBloomTarget(fw::MessageObject *object, MsgFxRimBloomTarget &message);
  void procMsgFxRimBloom(fw::MessageObject *object, MsgFxRimBloom &message);
  void procMsgFxFootPrint(fw::MessageObject *object, MsgFxFootPrint &message);
  void procMsgFxSplashdown(fw::MessageObject *object, MsgFxSplashdown &message);
  void procMsgFxCombo(fw::MessageObject *object, MsgFxCombo &message);
  void procMsgFxComboBuff(fw::MessageObject *object, MsgFxComboBuff &message);
  void procMsgFxForceCancel(fw::MessageObject *object, MsgFxForceCancel &message);
  void openDebugWindow(ml::WinProc *window);
  fw::EffectPack *getEffectPack(GF_ASSET_HANDLE *handle);
  const char *getEfpData(const char *name, mm::Mat44 &matrix);
  bool getWeaponEffectPack(mm::mtl::FixedVector<fw::EffectPack *, 8> &packs, int type, int);
  fw::EffectPack *getWeaponEffectPack(const char *name);
  fw::EffectPoint *getEffectPoint();
  f32 getHeightAboveGround() const;
  bool getValidEffectName(const char *name) const;
  bool isDynamicAnnotationEffect(u8 type) const;
  bool getDynamicAnnotationEffectFileName(u8 type, const char *&fileName) const;
  u32 convertSwimEffectState(GfEffectGround::SwimEffectState state);
  Param *findEffectCasterParam(u32 effect);
  GF_OBJ_HANDLE *getWeaponHandle(u16 weapon);
  void getWpnMatOld1(mm::Mat44 &matrix);
  void getWpnMatOld2(mm::Mat44 &matrix);

  u32 unknown10;  // Inferred role: setup value; original member name unknown.
  bool unknown14; // Inferred role: rim bloom active; original member name unknown.
  u8 _15[0x18 - 0x15];
  u32 unknown18; // Inferred role: rim bloom state; original member name unknown.
  f32 unknown1c; // Inferred role: rim bloom time; original member name unknown.
  f32 unknown20; // Inferred role: rim bloom duration; original member name unknown.
  f32 unknown24; // Inferred role: water depth threshold of the first swim state; original member name unknown.
  f32 unknown28; // Inferred role: water depth threshold of the second swim state; original member name unknown.
  u8 _2c[0x30 - 0x2c];
  fw::EffectResData *unknown30;                   // Inferred role: effect annotations of the weapon effect pack; original member name unknown.
  fw::EffectPack *unknown38;                      // Inferred role: effect pack; original member name unknown.
  mm::mtl::FixedVector<unknown001, 52> unknown40; // Inferred role: weapon effect packs; original member name unknown.
  EffectCaster *m_effectCaster;                   // Inferred role: effect caster; original member name unknown.
  fw::EffectPoint *m_effectPoint;                 // Inferred role: effect point; named after the game accessor gf::GfComEffectCaster::getEffectPoint.
  u8 _398[0x3a0 - 0x398];
  mm::mtl::FixedVector<Param, 256> unknown3a0;             // Inferred role: caster params; original member name unknown.
  mm::mtl::FixedVector<EventEfHandleTbl, 256> unknownc3b0; // Inferred role: mount effects; original member name unknown.
  u32 unknown113c0;                                        // Inferred role: effect layer; original member name unknown.
  u8 _113c4[0x113d0 - 0x113c4];
  mm::Mat44 unknown113d0;           // Inferred role: weapon matrix of the previous frame; original member name unknown.
  mm::Mat44 unknown11410;           // Inferred role: second weapon matrix of the previous frame; original member name unknown.
  mm::mtl::FixStr<16> unknown11450; // Inferred role: name set by the constructor; original member name unknown.
  mm::mtl::FixStr<16> unknown11464; // Inferred role: second name set by the constructor; original member name unknown.
  mm::mtl::FixStr<32> unknown11478; // Inferred role: current asm state name; original member name unknown.
  u32 unknown1149c;                 // Inferred role: caster type; original member name unknown.
  f32 unknown114a0;                 // Inferred role: previous asm local time; original member name unknown.
  u32 unknown114a4;                 // Inferred role: asm loop restarted; original member name unknown.
  f32 unknown114a8;                 // Inferred role: effect scale; original member name unknown.
  s32 unknown114ac;                 // Inferred role: current weapon switch; original member name unknown.
};

static_assert(offsetof(GfComEffectCaster, unknown14) == 0x14, "");
static_assert(offsetof(GfComEffectCaster, unknown18) == 0x18, "");
static_assert(offsetof(GfComEffectCaster, unknown1c) == 0x1c, "");
static_assert(offsetof(GfComEffectCaster, unknown20) == 0x20, "");
static_assert(offsetof(GfComEffectCaster, unknown24) == 0x24, "");
static_assert(offsetof(GfComEffectCaster, unknown28) == 0x28, "");
static_assert(offsetof(GfComEffectCaster, unknown40) == 0x40, "");
static_assert(offsetof(GfComEffectCaster, m_effectCaster) == 0x388, "");
static_assert(offsetof(GfComEffectCaster, m_effectPoint) == 0x390, "");
static_assert(offsetof(GfComEffectCaster, unknown3a0) == 0x3a0, "");
static_assert(offsetof(GfComEffectCaster, unknownc3b0) == 0xc3b0, "");
static_assert(offsetof(GfComEffectCaster, unknown113d0) == 0x113d0, "");
static_assert(offsetof(GfComEffectCaster, unknown11410) == 0x11410, "");
static_assert(offsetof(GfComEffectCaster, unknown10) == 0x10, "");
static_assert(offsetof(GfComEffectCaster, unknown30) == 0x30, "");
static_assert(offsetof(GfComEffectCaster, unknown38) == 0x38, "");
static_assert(offsetof(GfComEffectCaster, unknown113c0) == 0x113c0, "");
static_assert(offsetof(GfComEffectCaster, unknown11450) == 0x11450, "");
static_assert(offsetof(GfComEffectCaster, unknown11464) == 0x11464, "");
static_assert(offsetof(GfComEffectCaster, unknown11478) == 0x11478, "");
static_assert(offsetof(GfComEffectCaster, unknown1149c) == 0x1149c, "");
static_assert(offsetof(GfComEffectCaster, unknown114a0) == 0x114a0, "");
static_assert(offsetof(GfComEffectCaster, unknown114a4) == 0x114a4, "");
static_assert(offsetof(GfComEffectCaster, unknown114a8) == 0x114a8, "");
static_assert(offsetof(GfComEffectCaster, unknown114ac) == 0x114ac, "");
static_assert(sizeof(GfComEffectCaster) == 0x114b0, "");
static_assert(offsetof(GfComEffectCaster::SetupInfo, unknown08) == 0x08, "");
static_assert(offsetof(GfComEffectCaster::SetupInfo, unknown10) == 0x10, "");
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
static_assert(offsetof(GfComEffectCaster::EffectSetUp, unknown10) == 0x10, "");
static_assert(offsetof(GfComEffectCaster::EffectSetUp, m_obj) == 0x20, "");
static_assert(offsetof(GfComEffectCaster::EffectSetUp, unknown28) == 0x28, "");
static_assert(offsetof(GfComEffectCaster::EffectSetUp, unknown30) == 0x30, "");
static_assert(offsetof(GfComEffectCaster::EffectSetUp, unknown38) == 0x38, "");
static_assert(offsetof(GfComEffectCaster::EffectSetUp, unknown3c) == 0x3c, "");
static_assert(offsetof(GfComEffectCaster::EffectSetUp, unknown40) == 0x40, "");
static_assert(offsetof(GfComEffectCaster::EffectSetUp, unknown44) == 0x44, "");
static_assert(offsetof(GfComEffectCaster::EffectSetUp, unknown46) == 0x46, "");
static_assert(offsetof(GfComEffectCaster::EffectSetUp, unknown48) == 0x48, "");
static_assert(offsetof(GfComEffectCaster::EffectSetUp, unknown4e) == 0x4e, "");
static_assert(offsetof(GfComEffectCaster::EffectSetUp, unknown4f) == 0x4f, "");
static_assert(offsetof(GfComEffectCaster::SetupInfo, unknown08) == 0x08, "");
static_assert(offsetof(GfComEffectCaster::SetupInfo, unknown10) == 0x10, "");

} // namespace gf
