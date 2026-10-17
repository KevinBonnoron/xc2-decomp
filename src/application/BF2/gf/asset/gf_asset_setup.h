#pragma once
#include <stddef.h>

#include "gf/asset/gf_asset_def.h"
#include "gf/asset/gf_asset_path.h"
#include "gf/object/gf_append.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

struct CBdatWrapper;

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_ASSET_HANDLE;
struct GfAssetFilesInfo;
class GfAssetPack;
class GfInitParam;
class GfInitParamBelonging;
class GfInitParamBlade;
class GfInitParamDriver;
class GfInitParamEnWeapon;
class GfInitParamEnemy;
class GfInitParamExtra;
class GfInitParamFobj;
class GfInitParamGimmick;
class GfInitParamMapObj;
class GfInitParamMob;
class GfInitParamNpc;
class GfInitParamWeapon;

class GfAssetSetup {
public:
  static mm::mtl::RTTI m_rtti;

  struct RefResource {
    RefResource() : data(nullptr), size(0), index(0) {}

    mm::mtl::FixStr<128> name;
    void *data;
    u32 size;
    u32 index;
  };

  static const u32 REF_RESOURCE_MAX = 24;

  GfAssetSetup();
  virtual const mm::mtl::RTTI *getRTTI() const { return &m_rtti; }

  virtual ~GfAssetSetup();

  virtual const char *getAssetCategoryName() const { return nullptr; }
  virtual const char *getMdlFile(GfAssetType type) { return nullptr; }
  virtual const char *getArcFile(GfAssetType type) { return nullptr; }
  virtual const char *getMotFile(GfAssetType type) { return nullptr; }
  virtual const char *getRetargetMotFile(GfAssetType type) { return nullptr; }
  virtual const char *getEvtMotFile(GfAssetType type) { return nullptr; }
  virtual const char *getSalvageMotFile(GfAssetType type) { return nullptr; }
  virtual const char *getUiMotFile(GfAssetType type) { return nullptr; }
  virtual const char *getEfpFile(GfAssetType type) { return nullptr; }
  virtual const char *getEabFile(GfAssetType type) { return nullptr; }
  virtual const char *getEfbFile(GfAssetType type) { return nullptr; }
  virtual const char *getEfTailFile(GfAssetType type) { return nullptr; }
  virtual const char *getStpFile(GfAssetType type) { return nullptr; }
  virtual const char *getEvtStpFile(GfAssetType type) { return nullptr; }
  virtual const char *getUiStpFile(GfAssetType type) { return nullptr; }
  virtual const char *getSalvageStpFile(GfAssetType type) { return nullptr; }
  virtual GfFileIdx getMdlSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getArcSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getMotSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getRetargetMotSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getEvtMotSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getSalvageMotSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getUiMotSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getEfpSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getEabSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getEfbSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getStpSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getEvtStpSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getUiStpSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getSalvageStpSlot() const { return FILE_IDX_NONE; }
  virtual const char *getPath() const { return ""; }
  virtual const char *getEvtPath() const { return ""; }
  virtual const char *getEffPath() const { return GfAssetPath::getEff(); }
  virtual const char *getStpPath() const { return GfAssetPath::getStp(); }
  virtual const char *getSePackPath() const { return GfAssetPath::getSePack(); }
  virtual void requestCoreResource(GfAssetPack *pack, GF_ASSET_HANDLE *handle);
  virtual GfAssetType getAssetType() const { return ASSET_TYPE_BASE; }

  void setupParam(GF_ASSET_HANDLE *handle, const GfInitParam &param);
  bool setupReference(GfAssetPack *pack, const char *name, GfFileIdx index);
  static void makeAssetNamePrefix(mm::mtl::FixStr<128> &name, GfAssetType type, const char *file, const char *suffix);
  bool checkValidResource();
  RefResource *getRefResource(u32 index);
  void setRefResource(u32 index, const char *name, void *data, u32 size);
  static void makeAssetName(mm::mtl::FixStr<128> &name, GfAssetType type, const char *file);
  static void requestFootStepSePackFile(GfAssetFilesInfo &info, u32 footStep, GfFileIdx firstIndex, GfFileIdx secondIndex);
  static void requestWpnSePackFile(GfAssetFilesInfo &info, u32 weaponType, GfFileIdx index);

  u32 id;
  GF_ASSET_HANDLE *handle;
  CBdatWrapper *bdat;
  mm::mtl::FixedVector<RefResource *, REF_RESOURCE_MAX> refResources;
  const GfInitParam *initParam;
  bool hasRefResource;
  mm::mtl::FixStr<128> debugModelName;
  mm::mtl::FixStr<128> debugMotionName;
};

static_assert(sizeof(GfAssetSetup::RefResource) == 0x98, "");
static_assert(offsetof(GfAssetSetup, id) == 0x08, "");
static_assert(offsetof(GfAssetSetup, handle) == 0x10, "");
static_assert(offsetof(GfAssetSetup, bdat) == 0x18, "");
static_assert(offsetof(GfAssetSetup, refResources) == 0x20, "");
static_assert(offsetof(GfAssetSetup, initParam) == 0xe8, "");
static_assert(offsetof(GfAssetSetup, hasRefResource) == 0xf0, "");
static_assert(offsetof(GfAssetSetup, debugModelName) == 0xf4, "");

class GfAssetSetupDriver : public GfAssetSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfAssetSetupDriver();
  static bool makeAssetNameWpnType(mm::mtl::FixStr<128> &name, GfAssetType type, u32 driver, u32 weaponType, u32 blade);
  static bool makeAssetNameWpnTypeEff(mm::mtl::FixStr<128> &name, GfAssetType type, u32 driver, u32 weaponType, u32 blade, u32 attribute);
  u32 getFootStepId() const;
  const char *getMdlFile(GfAssetType type) override;
  const char *getArcFile(GfAssetType type) override;
  const char *getMotFile(GfAssetType type) override;
  const char *getEfpFile(GfAssetType type) override;
  const char *getEabFile(GfAssetType type) override;
  const char *getEfbFile(GfAssetType type) override;
  const char *getEfTailFile(GfAssetType type) override;
  const char *getStpFile(GfAssetType type) override;
  const char *getPath() const override;
  static void changeResoueceEffName(mm::mtl::FixStr<128> &name);
  virtual void setup(GF_ASSET_HANDLE *handle, const GfInitParamDriver &param);
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  GfFileIdx getMdlSlot() const override { return static_cast<GfFileIdx>(30); }
  GfFileIdx getArcSlot() const override { return static_cast<GfFileIdx>(33); }
  GfFileIdx getMotSlot() const override { return static_cast<GfFileIdx>(34); }
  GfFileIdx getEfpSlot() const override { return static_cast<GfFileIdx>(35); }
  GfFileIdx getEabSlot() const override { return static_cast<GfFileIdx>(36); }
  GfFileIdx getEfbSlot() const override { return static_cast<GfFileIdx>(37); }
  GfFileIdx getStpSlot() const override { return static_cast<GfFileIdx>(44); }
  GfAssetType getAssetType() const override { return ASSET_TYPE_PC; }
  virtual GfAssetType getAssetTypeMot() const { return ASSET_TYPE_PC_MOTION; }
  virtual GfAssetType getAssetTypeEvtMot() const { return ASSET_TYPE_TEMPORARY; }

  GfFileIdx reservedFileIndex;
};

static_assert(offsetof(GfAssetSetupDriver, reservedFileIndex) == 0x1fc, "");

class GfAssetSetupEventDriver : public GfAssetSetupDriver {
public:
  static mm::mtl::RTTI m_rtti;

  const char *getEvtMotFile(GfAssetType type) override;
  const char *getEvtStpFile(GfAssetType type) override;
  const char *getEvtPath() const override;
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  const char *getAssetCategoryName() const override { return "Evt"; }
  GfFileIdx getEvtMotSlot() const override { return static_cast<GfFileIdx>(38); }
  GfFileIdx getEvtStpSlot() const override { return static_cast<GfFileIdx>(45); }
};

class GfAssetSetupSalvage : public GfAssetSetupDriver {
public:
  static mm::mtl::RTTI m_rtti;

  const char *getMdlFile(GfAssetType type) override;
  const char *getArcFile(GfAssetType type) override;
  const char *getSalvageMotFile(GfAssetType type) override;
  const char *getSalvageStpFile(GfAssetType type) override;
  void setup(GF_ASSET_HANDLE *handle, const GfInitParamDriver &param) override;
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  const char *getAssetCategoryName() const override { return "Sal"; }
  GfFileIdx getSalvageMotSlot() const override { return static_cast<GfFileIdx>(41); }
  GfFileIdx getSalvageStpSlot() const override { return static_cast<GfFileIdx>(47); }
};

class GfAssetSetupDriverForUi : public GfAssetSetupDriver {
public:
  static mm::mtl::RTTI m_rtti;

  const char *getUiMotFile(GfAssetType type) override;
  const char *getUiStpFile(GfAssetType type) override;
  void setup(GF_ASSET_HANDLE *handle, const GfInitParamDriver &param) override;
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  GfFileIdx getUiMotSlot() const override { return static_cast<GfFileIdx>(40); }
  GfFileIdx getUiStpSlot() const override { return static_cast<GfFileIdx>(46); }
  GfAssetType getAssetTypeEvtMot() const override { return ASSET_TYPE_TEMPORARY; }
};

class GfAssetSetupBlade : public GfAssetSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfAssetSetupBlade();
  void setup(GF_ASSET_HANDLE *handle, const GfInitParamBlade &param);
  const char *getSwtFile(GfAssetType type);
  const char *getSePackFile() const;
  u32 getFootStepId() const;
  const char *getMdlFile(GfAssetType type) override;
  const char *getArcFile(GfAssetType type) override;
  const char *getRetargetMotFile(GfAssetType type) override;
  const char *getEfpFile(GfAssetType type) override;
  const char *getEabFile(GfAssetType type) override;
  const char *getEfbFile(GfAssetType type) override;
  const char *getStpFile(GfAssetType type) override;
  const char *getPath() const override;
  static bool makeAssetNameWpnType(mm::mtl::FixStr<128> &name, u32 blade, u32 weaponType);
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  GfFileIdx getMdlSlot() const override { return static_cast<GfFileIdx>(30); }
  GfFileIdx getArcSlot() const override { return static_cast<GfFileIdx>(33); }
  GfFileIdx getMotSlot() const override { return static_cast<GfFileIdx>(34); }
  GfFileIdx getRetargetMotSlot() const override { return static_cast<GfFileIdx>(43); }
  GfFileIdx getEfpSlot() const override { return static_cast<GfFileIdx>(35); }
  GfFileIdx getEabSlot() const override { return static_cast<GfFileIdx>(36); }
  GfFileIdx getEfbSlot() const override { return static_cast<GfFileIdx>(37); }
  GfFileIdx getStpSlot() const override { return static_cast<GfFileIdx>(44); }
  GfAssetType getAssetType() const override { return ASSET_TYPE_BLADE; }
  virtual GfAssetType getAssetTypeMot() const { return ASSET_TYPE_BLADE_MOTION; }
  virtual GfAssetType getAssetTypeEventMot() const { return ASSET_TYPE_TEMPORARY; }
  virtual GfAssetType getAssetTypeEfb() const { return ASSET_TYPE_WEAPON_EFFECT; }

  bool useCondModel;
};

static_assert(offsetof(GfAssetSetupBlade, useCondModel) == 0x1fc, "");

class GfAssetSetupEventBlade : public GfAssetSetupBlade {
public:
  static mm::mtl::RTTI m_rtti;

  const char *getEvtMotFile(GfAssetType type) override;
  const char *getEvtStpFile(GfAssetType type) override;
  const char *getEvtPath() const override;
  const char *getMdlFile(GfAssetType type) override;
  const char *getArcFile(GfAssetType type) override;
  const char *getRetargetMotFile(GfAssetType type) override;
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  const char *getAssetCategoryName() const override { return "Evt"; }
  GfFileIdx getEvtMotSlot() const override { return static_cast<GfFileIdx>(38); }
  GfFileIdx getEvtStpSlot() const override { return static_cast<GfFileIdx>(45); }
};

class GfAssetSetupBladeForUi : public GfAssetSetupBlade {
public:
  static mm::mtl::RTTI m_rtti;

  const char *getUiMotFile(GfAssetType type) override;
  const char *getUiStpFile(GfAssetType type) override;
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  GfFileIdx getUiMotSlot() const override { return static_cast<GfFileIdx>(40); }
  GfFileIdx getUiStpSlot() const override { return static_cast<GfFileIdx>(46); }
  GfAssetType getAssetType() const override { return ASSET_TYPE_TEMPORARY; }
  GfAssetType getAssetTypeMot() const override { return ASSET_TYPE_TEMPORARY; }
  GfAssetType getAssetTypeEventMot() const override { return ASSET_TYPE_TEMPORARY; }
  GfAssetType getAssetTypeEfb() const override { return ASSET_TYPE_TEMPORARY; }
};

class GfAssetSetupEnemy : public GfAssetSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfAssetSetupEnemy();
  void makeEnemyEffectAssetName(mm::mtl::FixStr<128> &name, const GfInitParamEnemy &param, u32 attribute);
  u32 getEnemyAttribute(const GfInitParamEnemy &param);
  void getEnemyEabFileName(mm::mtl::FixStr<128> &name, const GfInitParamEnemy &param, GfAssetType type);
  void getEnemyEfbFileName(mm::mtl::FixStr<128> &name, const GfInitParamEnemy &param, GfAssetType type, u32 attribute);
  const char *getSwtFile(GfAssetType type);
  static bool makeAssetNameWpnType(mm::mtl::FixStr<128> &name, u32 driver, u32 number);
  const char *getSePackFile() const;
  u32 getFootStepId() const;
  const char *getMdlFile(GfAssetType type) override;
  const char *getArcFile(GfAssetType type) override;
  const char *getMotFile(GfAssetType type) override;
  const char *getRetargetMotFile(GfAssetType type) override;
  const char *getEfpFile(GfAssetType type) override;
  const char *getEabFile(GfAssetType type) override;
  const char *getEfbFile(GfAssetType type) override;
  const char *getStpFile(GfAssetType type) override;
  const char *getPath() const override;
  virtual void setup(GF_ASSET_HANDLE *handle, const GfInitParamEnemy &param);
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  GfFileIdx getMdlSlot() const override { return static_cast<GfFileIdx>(6); }
  GfFileIdx getArcSlot() const override { return static_cast<GfFileIdx>(7); }
  GfFileIdx getMotSlot() const override { return static_cast<GfFileIdx>(8); }
  GfFileIdx getRetargetMotSlot() const override { return static_cast<GfFileIdx>(14); }
  GfFileIdx getEfpSlot() const override { return static_cast<GfFileIdx>(9); }
  GfFileIdx getEabSlot() const override { return static_cast<GfFileIdx>(10); }
  GfFileIdx getEfbSlot() const override { return static_cast<GfFileIdx>(11); }
  GfFileIdx getStpSlot() const override { return static_cast<GfFileIdx>(4); }
  GfAssetType getAssetType() const override { return ASSET_TYPE_ENEMY; }
  virtual GfFileIdx getAddMotSlot() const { return static_cast<GfFileIdx>(15); }
  virtual GfAssetType getAssetTypeMot() const { return ASSET_TYPE_ENEMY_MOTION; }
  virtual GfAssetType getAssetTypeArc() const { return ASSET_TYPE_ENEMY_ARC; }

  const GfInitParamEnemy *initParamEnemy;
};

static_assert(offsetof(GfAssetSetupEnemy, initParamEnemy) == 0x200, "");

class GfAssetSetupEnemyBlade : public GfAssetSetupEnemy {
public:
  static mm::mtl::RTTI m_rtti;

  GfAssetSetupEnemyBlade();
  const char *getMdlFile(GfAssetType type) override;
  const char *getMotFile(GfAssetType type) override;
  const char *getRetargetMotFile(GfAssetType type) override;
  const char *getPath() const override;
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
};

class GfAssetSetupEventEnemy : public GfAssetSetupEnemy {
public:
  static mm::mtl::RTTI m_rtti;

  const char *getEvtMotFile(GfAssetType type) override;
  const char *getEvtStpFile(GfAssetType type) override;
  const char *getEvtPath() const override;
  void setup(GF_ASSET_HANDLE *handle, const GfInitParamEnemy &param) override;
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  const char *getAssetCategoryName() const override { return "Evt"; }
  GfFileIdx getEvtMotSlot() const override { return static_cast<GfFileIdx>(12); }
  GfFileIdx getEvtStpSlot() const override { return static_cast<GfFileIdx>(5); }
};

class GfAssetSetupNpc : public GfAssetSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfAssetSetupNpc();
  u32 getFootStepId() const;
  const char *getMdlFile(GfAssetType type) override;
  const char *getArcFile(GfAssetType type) override;
  const char *getMotFile(GfAssetType type) override;
  const char *getEfpFile(GfAssetType type) override;
  const char *getRetargetMotFile(GfAssetType type) override;
  const char *getStpFile(GfAssetType type) override;
  const char *getPath() const override;
  const char *getEvtMotFile(GfAssetType type) override;
  const char *getEabFile(GfAssetType type) override;
  const char *getEfbFile(GfAssetType type) override;
  const char *getEvtPath() const override;
  virtual void setup(GF_ASSET_HANDLE *handle, const GfInitParamNpc &param);
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  GfFileIdx getMdlSlot() const override { return static_cast<GfFileIdx>(6); }
  GfFileIdx getArcSlot() const override { return static_cast<GfFileIdx>(7); }
  GfFileIdx getMotSlot() const override { return static_cast<GfFileIdx>(8); }
  GfFileIdx getRetargetMotSlot() const override { return static_cast<GfFileIdx>(14); }
  GfFileIdx getEvtMotSlot() const override { return static_cast<GfFileIdx>(12); }
  GfFileIdx getEfpSlot() const override { return static_cast<GfFileIdx>(9); }
  GfFileIdx getEabSlot() const override { return static_cast<GfFileIdx>(10); }
  GfFileIdx getEfbSlot() const override { return static_cast<GfFileIdx>(11); }
  GfFileIdx getStpSlot() const override { return static_cast<GfFileIdx>(4); }
  GfAssetType getAssetType() const override { return ASSET_TYPE_ENEMY; }
  virtual GfAssetType getAssetTypeMot() const { return ASSET_TYPE_ENEMY_MOTION; }
  virtual GfAssetType getAssetTypeArc() const { return ASSET_TYPE_ENEMY_ARC; }
};

class GfAssetSetupEventNpc : public GfAssetSetupNpc {
public:
  static mm::mtl::RTTI m_rtti;

  const char *getMotFile(GfAssetType type) override;
  const char *getEvtMotFile(GfAssetType type) override;
  const char *getEvtStpFile(GfAssetType type) override;
  void setup(GF_ASSET_HANDLE *handle, const GfInitParamNpc &param) override;
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  const char *getAssetCategoryName() const override { return "Evt"; }
  GfFileIdx getEvtStpSlot() const override { return static_cast<GfFileIdx>(5); }
  GfAssetType getAssetType() const override { return ASSET_TYPE_ENEMY; }
  GfAssetType getAssetTypeMot() const override { return ASSET_TYPE_TEMPORARY; }
};

class GfAssetSetupMob : public GfAssetSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfAssetSetupMob();
  u32 getFootStepId() const;
  const char *getMdlFile(GfAssetType type) override;
  const char *getArcFile(GfAssetType type) override;
  const char *getMotFile(GfAssetType type) override;
  const char *getRetargetMotFile(GfAssetType type) override;
  const char *getStpFile(GfAssetType type) override;
  const char *getPath() const override;
  const char *getEfpFile(GfAssetType type) override;
  const char *getEabFile(GfAssetType type) override;
  const char *getEfbFile(GfAssetType type) override;
  virtual void setup(GF_ASSET_HANDLE *handle, const GfInitParamMob &param);
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  GfFileIdx getMdlSlot() const override { return static_cast<GfFileIdx>(6); }
  GfFileIdx getArcSlot() const override { return static_cast<GfFileIdx>(7); }
  GfFileIdx getMotSlot() const override { return static_cast<GfFileIdx>(8); }
  GfFileIdx getRetargetMotSlot() const override { return static_cast<GfFileIdx>(14); }
  GfFileIdx getEfpSlot() const override { return static_cast<GfFileIdx>(9); }
  GfFileIdx getEabSlot() const override { return static_cast<GfFileIdx>(10); }
  GfFileIdx getEfbSlot() const override { return static_cast<GfFileIdx>(11); }
  GfFileIdx getStpSlot() const override { return static_cast<GfFileIdx>(4); }
  GfAssetType getAssetType() const override { return ASSET_TYPE_MAP_OBJECT; }
};

class GfAssetSetupEventMob : public GfAssetSetupMob {
public:
  static mm::mtl::RTTI m_rtti;

  const char *getEvtStpFile(GfAssetType type) override;
  const char *getEvtPath() const override;
  void setup(GF_ASSET_HANDLE *handle, const GfInitParamMob &param) override;
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  const char *getAssetCategoryName() const override { return "Evt"; }
  GfFileIdx getEvtStpSlot() const override { return static_cast<GfFileIdx>(5); }
};

class GfAssetSetupGimmick : public GfAssetSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfAssetSetupGimmick();
  void setup(GF_ASSET_HANDLE *handle, const GfInitParamGimmick &param);
  const char *getMdlFile(GfAssetType type) override;
  const char *getArcFile(GfAssetType type) override;
  const char *getMotFile(GfAssetType type) override;
  const char *getEfpFile(GfAssetType type) override;
  const char *getEabFile(GfAssetType type) override;
  const char *getEfbFile(GfAssetType type) override;
  const char *getStpFile(GfAssetType type) override;
  const char *getPath() const override;
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  GfFileIdx getMdlSlot() const override { return static_cast<GfFileIdx>(0); }
  GfFileIdx getArcSlot() const override { return static_cast<GfFileIdx>(1); }
  GfFileIdx getMotSlot() const override { return static_cast<GfFileIdx>(2); }
  GfFileIdx getEfpSlot() const override { return static_cast<GfFileIdx>(3); }
  GfFileIdx getEabSlot() const override { return static_cast<GfFileIdx>(4); }
  GfFileIdx getEfbSlot() const override { return static_cast<GfFileIdx>(5); }
  GfFileIdx getStpSlot() const override { return static_cast<GfFileIdx>(6); }
  GfAssetType getAssetType() const override { return ASSET_TYPE_MAP_OBJECT; }

  u32 gimmickType;
};

static_assert(offsetof(GfAssetSetupGimmick, gimmickType) == 0x1fc, "");

class GfAssetSetupMapObj : public GfAssetSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfAssetSetupMapObj();
  void setup(GF_ASSET_HANDLE *handle, const GfInitParamMapObj &param);
  const char *getMdlFile(GfAssetType type) override;
  const char *getArcFile(GfAssetType type) override;
  const char *getMotFile(GfAssetType type) override;
  const char *getEabFile(GfAssetType type) override;
  const char *getPath() const override;
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  GfFileIdx getMdlSlot() const override { return static_cast<GfFileIdx>(0); }
  GfFileIdx getArcSlot() const override { return static_cast<GfFileIdx>(1); }
  GfFileIdx getMotSlot() const override { return static_cast<GfFileIdx>(2); }
  GfFileIdx getEabSlot() const override { return static_cast<GfFileIdx>(4); }
  GfAssetType getAssetType() const override { return ASSET_TYPE_MAP_OBJECT; }
};

class GfAssetSetupFobj : public GfAssetSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfAssetSetupFobj();
  void setup(GF_ASSET_HANDLE *handle, const GfInitParamFobj &param);
  const char *getMdlFile(GfAssetType type) override;
  const char *getEabFile(GfAssetType type) override;
  const char *getPath() const override;
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  GfFileIdx getMdlSlot() const override { return static_cast<GfFileIdx>(0); }
  GfFileIdx getEabSlot() const override { return static_cast<GfFileIdx>(4); }
  GfAssetType getAssetType() const override { return ASSET_TYPE_FIELD_OBJECT; }
};

class GfAssetSetupWeapon : public GfAssetSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfAssetSetupWeapon();
  void setup(GF_ASSET_HANDLE *handle, const GfInitParamWeapon &param);
  const char *getMdlFile(GfAssetType type) override;
  const char *getArcFile(GfAssetType type) override;
  const char *getMotFile(GfAssetType type) override;
  const char *getEfpFile(GfAssetType type) override;
  const char *getStpFile(GfAssetType type) override;
  const char *getPath() const override;
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  GfFileIdx getMdlSlot() const override { return static_cast<GfFileIdx>(0); }
  GfFileIdx getArcSlot() const override { return static_cast<GfFileIdx>(1); }
  GfFileIdx getMotSlot() const override { return static_cast<GfFileIdx>(2); }
  GfFileIdx getEfpSlot() const override { return static_cast<GfFileIdx>(3); }
  GfFileIdx getStpSlot() const override { return static_cast<GfFileIdx>(5); }
  GfAssetType getAssetType() const override { return ASSET_TYPE_WEAPON; }

  GfAppend append;
};

static_assert(offsetof(GfAssetSetupWeapon, append) == 0x200, "");

class GfAssetSetupWeaponEventCS : public GfAssetSetupWeapon {
public:
  static mm::mtl::RTTI m_rtti;

  GfAssetSetupWeaponEventCS();
  void setup(GF_ASSET_HANDLE *handle, const GfInitParamWeapon &param);
  const char *getEvtMotFile(GfAssetType type) override;
  const char *getEvtPath() const override;
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  GfFileIdx getEvtMotSlot() const override { return static_cast<GfFileIdx>(4); }
};

class GfAssetSetupEnWeapon : public GfAssetSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfAssetSetupEnWeapon();
  void setup(GF_ASSET_HANDLE *handle, const GfInitParamEnWeapon &param);
  const char *getMdlFile(GfAssetType type) override;
  const char *getArcFile(GfAssetType type) override;
  const char *getMotFile(GfAssetType type) override;
  const char *getEfpFile(GfAssetType type) override;
  const char *getStpFile(GfAssetType type) override;
  const char *getPath() const override;
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  GfFileIdx getMdlSlot() const override { return static_cast<GfFileIdx>(0); }
  GfFileIdx getArcSlot() const override { return static_cast<GfFileIdx>(1); }
  GfFileIdx getMotSlot() const override { return static_cast<GfFileIdx>(6); }
  GfFileIdx getEfpSlot() const override { return static_cast<GfFileIdx>(2); }
  GfFileIdx getStpSlot() const override { return static_cast<GfFileIdx>(5); }
  GfAssetType getAssetType() const override { return ASSET_TYPE_OPTION; }

  GfAppend append;
};

static_assert(offsetof(GfAssetSetupEnWeapon, append) == 0x200, "");

class GfAssetSetupBelonging : public GfAssetSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfAssetSetupBelonging();
  void setup(GF_ASSET_HANDLE *handle, const GfInitParamBelonging &param);
  const char *getMdlFile(GfAssetType type) override;
  const char *getArcFile(GfAssetType type) override;
  const char *getMotFile(GfAssetType type) override;
  const char *getPath() const override;
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  GfFileIdx getMdlSlot() const override { return static_cast<GfFileIdx>(0); }
  GfFileIdx getArcSlot() const override { return static_cast<GfFileIdx>(1); }
  GfAssetType getAssetType() const override { return ASSET_TYPE_OPTION; }

  GfAppend append;
};

static_assert(offsetof(GfAssetSetupBelonging, append) == 0x200, "");

class GfAssetSetupExtra : public GfAssetSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GfAssetSetupExtra();
  void setup(GF_ASSET_HANDLE *handle, const GfInitParamExtra &param);
  const char *getMdlFile(GfAssetType type) override;
  const char *getArcFile(GfAssetType type) override;
  const char *getMotFile(GfAssetType type) override;
  const char *getStpFile(GfAssetType type) override;
  const char *getPath() const override;
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }
  GfFileIdx getMdlSlot() const override { return static_cast<GfFileIdx>(0); }
  GfFileIdx getArcSlot() const override { return static_cast<GfFileIdx>(1); }
  GfFileIdx getMotSlot() const override { return static_cast<GfFileIdx>(6); }
  GfFileIdx getStpSlot() const override { return static_cast<GfFileIdx>(5); }
  GfAssetType getAssetType() const override { return ASSET_TYPE_OPTION; }

  GfAppend append;
};

static_assert(offsetof(GfAssetSetupExtra, append) == 0x200, "");

} // namespace gf
