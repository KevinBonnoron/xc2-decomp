#pragma once
#include <stddef.h>

#include "framework/coli/coli_object.h"
#include "gf/event/gf_event.h"
#include "gmk/gmk_cond.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
struct Mat44;

namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ml {
class ScnObjAccPartsPos;
class ScnObjModel;
} // namespace ml

namespace idcoli {
class IDColiObj;
} // namespace idcoli

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

enum GfFieldLodState {
  FIELD_LOD_STATE_UNKNOWN_0 = 0, // Inferred role: normal animation ("effect_anime_normal"); original enumerator name unknown.
  FIELD_LOD_STATE_UNKNOWN_1 = 1, // Inferred role: reverse animation ("effect_anime_reverse"); original enumerator name unknown.
  FIELD_LOD_STATE_UNKNOWN_2 = 2, // Inferred role: fade in ("effect_visibleON"); original enumerator name unknown.
  FIELD_LOD_STATE_UNKNOWN_3 = 3, // Inferred role: hidden ("effect_visibleOFF"); original enumerator name unknown.
  FIELD_LOD_STATE_UNKNOWN_4 = 4, // Inferred role: fade out ("effect_fadeOUT"); original enumerator name unknown.
  FIELD_LOD_STATE_UNKNOWN_5 = 5, // Inferred role: no lod state, one past the five effect data; original enumerator name unknown.
};

// Layout evidence: ctor (0x71002e1c3c), createAsset (0x71002e1cd0) and disposeAsset (0x71002e1ec0); getAsset
// (0x71002e1c58) indexes the five effect data by GfFieldLodState.
class GfFieldLodEffect {
public:
  GfFieldLodEffect();
  ~GfFieldLodEffect() { disposeAsset(); }
  void *getAsset(GfFieldLodState state) const;
  bool isAssetExists() const;
  bool isAssetLoop(GfFieldLodState state) const;
  void createAsset(int bdatId);
  void disposeAsset();
  void disposeInst(bool isDead);
  void update(const ml::ScnObjAccPartsPos &partsPos);

  // Inferred role: effect data per lod state ("effect_anime_normal", "effect_anime_reverse", "effect_visibleON",
  // "effect_visibleOFF", "effect_fadeOUT"); original member name unknown.
  void *unknown00[5];
  u16 unknown28;             // Inferred role: skip frame ("effect_skipframe"); original member name unknown.
  bool unknown2a;            // Inferred role: assets created; original member name unknown.
  u32 unknown2c;             // Inferred role: effect instance handle; original member name unknown.
  GfFieldLodState unknown30; // Inferred role: lod state of the instance; original member name unknown.
};

static_assert(offsetof(GfFieldLodEffect, unknown28) == 0x28, "");
static_assert(offsetof(GfFieldLodEffect, unknown2a) == 0x2a, "");
static_assert(offsetof(GfFieldLodEffect, unknown2c) == 0x2c, "");
static_assert(offsetof(GfFieldLodEffect, unknown30) == 0x30, "");
static_assert(sizeof(GfFieldLodEffect) == 0x38, "");

class GfFieldLod;

class GfFieldLodColiAnim {
public:
  // Layout evidence: the vtable (0x7101188678) has the getRTTI slot of fw::ColiUserData; createPosInfos (0x71002e2a94)
  // sets the object handle at 0x08 (PosInfo 0x60).
  class ColiUserData : public fw::ColiUserData {
  public:
    static mm::mtl::RTTI m_rtti;

    const mm::mtl::RTTI *getRTTI() const override;

    GF_OBJ_HANDLE *unknown08; // Inferred role: lod anim object; original member name unknown.
  };

  // Layout evidence: createPosInfos (0x71002e2a94) initializes it before Vector<PosInfo>::push_back (0x71002e4670),
  // whose copy moves 0x00-0x58 raw, the ColiUserData and the bytes from 0x68 to 0x82 raw; the element destructor in
  // Vector<PosInfo>::expand (0x71002e6e18) is the inlined GfFieldLodEffect::disposeAsset of the member at 0x08; the
  // PosInfo methods (0x71002e2120 to 0x71002e2728) read the other members.
  struct PosInfo {
    void update(const fw::UpdateInfo &info);
    void updateColiOff(ml::ScnObjAccPartsPos &partsPos);

    GfFieldLodColiAnim *unknown00; // Inferred role: owner; original member name unknown.
    GfFieldLodEffect unknown08;    // Inferred role: pop/depop effects; original member name unknown.
    u32 unknown40;                 // Inferred role: parts id; original member name unknown.
    int unknown44;                 // Inferred role: parts index; original member name unknown.
    int unknown48;                 // Inferred role: collision move object index; original member name unknown.
    GF_OBJ_HANDLE *unknown50;      // Inferred role: lod anim object; original member name unknown.
    ColiUserData unknown58;        // Inferred role: collision user data; original member name unknown.
    bool unknown68;                // Inferred role: anim playing; original member name unknown.
    bool unknown69;                // Inferred role: anim reversed; original member name unknown.
    f32 unknown6c;                 // Inferred role: play speed; original member name unknown.
    bool unknown70;                // Inferred role: fade in; original member name unknown.
    f32 unknown74;                 // Inferred role: fade time; original member name unknown.
    f32 unknown78;                 // Inferred role: fade elapsed time; original member name unknown.
    f32 unknown7c;                 // Inferred role: squared distance of the pop/depop effect; original member name unknown.
    bool unknown80;                // Inferred role: collision waits for the end of the fade in; original member name unknown.
    bool unknown81;                // Inferred role: collision kept until the end of the fade out; original member name unknown.
  };

  // Layout evidence: the constructor (0x71002e29a0), create (0x71002e2a1c) and dispose (0x71002e2a68).
  struct CreateInfo {
    CreateInfo() : unknown00(nullptr), unknown08(nullptr), unknown10(nullptr), unknown18(false) {}

    ml::ScnObjModel *unknown00;   // Inferred role: map model; original member name unknown.
    idcoli::IDColiObj *unknown08; // Inferred role: map collision; original member name unknown.
    GfFieldLod *unknown10;        // Inferred role: lod; original member name unknown.
    bool unknown18;               // Inferred role: created for the debug draw; original member name unknown.
  };

  explicit GfFieldLodColiAnim(const CreateInfo *info = nullptr);
  ~GfFieldLodColiAnim() { dispose(); }
  void create(const CreateInfo &info);
  void dispose();
  void createPosInfos(bool isDebugDraw);
  void disposePosInfos();
  void update(const fw::UpdateInfo &info);
  void validateVeSe(const GfFieldLod &lod);
  void stop(u16 lodId);
  bool isLodIdExist(u16 lodId) const;
  void setPlaySpeed(u16 lodId, f32 speed);
  f32 getPlaySpeed(u16 lodId) const;
  bool isPlayEnd(u16 lodId) const;
  f32 getAnimEndTime(u16 lodId) const;
  void clearEffectInsts();
  void debugDraw() const;
  static GfFieldLodState findStateOfAnimReverse(bool isReverse);
  static GfFieldLodState findStateOfFade(bool isFadeIn, bool isImmediate);
  static void bindPosInfoToGfObj(const PosInfo &posInfo);
  static void unbindPosInfoToGfObj(const PosInfo &posInfo);

  CreateInfo unknown00;               // Inferred role: create info the animation was created with; original member name unknown.
  mm::mtl::Vector<PosInfo> unknown20; // Inferred role: infos of the parts positions of the model; original member name unknown.
};

static_assert(offsetof(GfFieldLodColiAnim::ColiUserData, unknown08) == 0x08, "");
static_assert(sizeof(GfFieldLodColiAnim::ColiUserData) == 0x10, "");
static_assert(offsetof(GfFieldLodColiAnim::PosInfo, unknown08) == 0x08, "");
static_assert(offsetof(GfFieldLodColiAnim::PosInfo, unknown40) == 0x40, "");
static_assert(offsetof(GfFieldLodColiAnim::PosInfo, unknown48) == 0x48, "");
static_assert(offsetof(GfFieldLodColiAnim::PosInfo, unknown50) == 0x50, "");
static_assert(offsetof(GfFieldLodColiAnim::PosInfo, unknown58) == 0x58, "");
static_assert(offsetof(GfFieldLodColiAnim::PosInfo, unknown68) == 0x68, "");
static_assert(offsetof(GfFieldLodColiAnim::PosInfo, unknown6c) == 0x6c, "");
static_assert(offsetof(GfFieldLodColiAnim::PosInfo, unknown70) == 0x70, "");
static_assert(offsetof(GfFieldLodColiAnim::PosInfo, unknown7c) == 0x7c, "");
static_assert(offsetof(GfFieldLodColiAnim::PosInfo, unknown80) == 0x80, "");
static_assert(sizeof(GfFieldLodColiAnim::PosInfo) == 0x88, "");
static_assert(offsetof(GfFieldLodColiAnim::CreateInfo, unknown10) == 0x10, "");
static_assert(offsetof(GfFieldLodColiAnim::CreateInfo, unknown18) == 0x18, "");
static_assert(sizeof(GfFieldLodColiAnim::CreateInfo) == 0x20, "");
static_assert(offsetof(GfFieldLodColiAnim, unknown20) == 0x20, "");
static_assert(sizeof(GfFieldLodColiAnim) == 0x48, "");

class GfFieldLod : public mm::mtl::PtrSingleton<GfFieldLod> {
public:
  // Layout evidence: create (0x71002e49b4) reads the bdat columns, update (0x71002e4bc4) and dirtyCache (0x71002e51a4) the
  // three condition infos; the element size 0x34 is the stride of the vector of the destroy (0x71002e6afc) loop.
  struct BdatInfo {
    struct CondInfo {
      CondInfo() : unknown08(0), unknown0a(false) {}

      gmk::ScenarioFlagCond unknown00; // Inferred role: scenario flag; original member name unknown.
      gmk::QuestFlagCond unknown04;    // Inferred role: quest flag; original member name unknown.
      u16 unknown08;                   // Inferred role: condition; original member name unknown.
      bool unknown0a;                  // Inferred role: condition matched on the last update; original member name unknown.
    };

    BdatInfo(u16 bdatId);
    ~BdatInfo() { dispose(); }
    void create(u16 bdatId);
    void dispose();
    void dirtyCache();

    u16 unknown00;         // Inferred role: lod id; original member name unknown.
    f32 unknown04;         // Inferred role: fade in time; original member name unknown.
    f32 unknown08;         // Inferred role: fade out time; original member name unknown.
    u16 unknown0c;         // Inferred role: bdat id; original member name unknown.
    CondInfo unknown0e[3]; // Inferred role: change conditions; original member name unknown.
  };

  GfFieldLod(const GfSetupParam &param);
  ~GfFieldLod();
  void initialize(const GfSetupParam &param);
  int findBdatIdByLodId(u16 lodId) const;
  const BdatInfo *findBdatInfo(int bdatId) const;
  bool isAnimReverse(int bdatId) const;
  bool isPlayAnimEnd(int bdatId) const;
  f32 getAnimEndTime(int bdatId) const;
  void setFade(int bdatId, bool isFadeIn, bool isImmediate);
  void setLodSwitchId(int bdatId, u32 switchId);
  void setPlaySpeed(int bdatId, f32 speed);
  f32 getPlaySpeed(int bdatId) const;
  bool setAnimReverse(int bdatId, bool isReverse, bool isSkip);
  bool isFadeOut(int bdatId) const;
  bool findTransform(mm::Mat44 &matrix, int bdatId) const;
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  void gevPlayEvent(GEV event, u32 value);
  static bool isAnimReverseOfInit(int bdatId);
  static bool isVisibleOfInit(int bdatId);
  static void validateByInitData();
  static void debugDraw();
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);

  u16 unknown08[0x400]; // Inferred role: lod id of each bdat entry; original member name unknown.
  int unknown808;       // Inferred role: first bdat id; original member name unknown.
  bool unknown80c;      // Inferred role: lod data ready; original member name unknown.
  u8 _80d[0x810 - 0x80d];
  mm::mtl::Vector<BdatInfo> unknown810; // Inferred role: bdat infos of the current map; original member name unknown.
  u32 unknown838;                       // Inferred role: unknown; original member name unknown.
  GfFieldLodColiAnim unknown840;        // Inferred role: lod animation of the map model; original member name unknown.
  bool unknown888;                      // Inferred role: unknown; original member name unknown.
  bool unknown889;                      // Inferred role: unknown; original member name unknown.
  u8 _88a[0x890 - 0x88a];
};

static_assert(sizeof(GfFieldLod::BdatInfo::CondInfo) == 0xc, "");
static_assert(offsetof(GfFieldLod::BdatInfo, unknown0c) == 0x0c, "");
static_assert(offsetof(GfFieldLod::BdatInfo, unknown0e) == 0x0e, "");
static_assert(sizeof(GfFieldLod::BdatInfo) == 0x34, "");
static_assert(offsetof(GfFieldLod, unknown808) == 0x808, "");
static_assert(offsetof(GfFieldLod, unknown80c) == 0x80c, "");
static_assert(offsetof(GfFieldLod, unknown810) == 0x810, "");
static_assert(offsetof(GfFieldLod, unknown840) == 0x840, "");
static_assert(offsetof(GfFieldLod, unknown888) == 0x888, "");
static_assert(sizeof(GfFieldLod) == 0x890, "");

} // namespace gf
