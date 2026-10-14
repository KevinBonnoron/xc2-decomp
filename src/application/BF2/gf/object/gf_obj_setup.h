#pragma once
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "mm_mtl/rtti.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct SDataBlade;
struct SDataEnemy;

class GfObjSetup {
public:
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual ~GfObjSetup();
  virtual u32 getFootStep() const;
  virtual u32 getFootStepEffect() const;

  u32 objType;
  u8 _0c[0x10 - 0x0c];
  u32 id;
  int partyMember;
  u8 _18[0x1c - 0x18];
  u32 characterType;
  u8 _20[0x40 - 0x20];
  f32 scale;
  u8 _44[0x54 - 0x44];
  bool hasFixedBlade;
  u8 _55[0x58 - 0x55];
  u32 fixedBlade;
};

static_assert(offsetof(GfObjSetup, objType) == 0x08, "");
static_assert(offsetof(GfObjSetup, id) == 0x10, "");
static_assert(offsetof(GfObjSetup, partyMember) == 0x14, "");
static_assert(offsetof(GfObjSetup, characterType) == 0x1c, "");
static_assert(offsetof(GfObjSetup, scale) == 0x40, "");
static_assert(offsetof(GfObjSetup, hasFixedBlade) == 0x54, "");
static_assert(offsetof(GfObjSetup, fixedBlade) == 0x58, "");

class GfObjSetupMap : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  u8 _5c[0x6c - 0x5c];
  u32 bdatId;
};

static_assert(offsetof(GfObjSetupMap, bdatId) == 0x6c, "");

class GfObjSetupMob : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;
};

class GfObjSetupNpc : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;
};

class GfObjSetupGimmick : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;

  GimmickType gimmickType;
};

static_assert(offsetof(GfObjSetupGimmick, gimmickType) == 0x5c, "");

class GfObjSetupEnemy : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 OBJECT_TYPE = OBJECT_TYPE_ENEMY;

  virtual u32 getEnArrangeID() const;

  u8 _5c[0x6c - 0x5c];
  u32 enParamId;
  u32 enArrangeId;
  u8 _74[0xa0 - 0x74];
  SDataEnemy *dataEnemy;
  u8 _a8[0xb8 - 0xa8];
  u32 blade;
  u8 _bc[0xc0 - 0xbc];
  SDataBlade *dataBlade;
};

static_assert(offsetof(GfObjSetupEnemy, enParamId) == 0x6c, "");
static_assert(offsetof(GfObjSetupEnemy, enArrangeId) == 0x70, "");
static_assert(offsetof(GfObjSetupEnemy, dataEnemy) == 0xa0, "");
static_assert(offsetof(GfObjSetupEnemy, blade) == 0xb8, "");
static_assert(offsetof(GfObjSetupEnemy, dataBlade) == 0xc0, "");

class GfObjSetupBelonging : public GfObjSetup {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 OBJECT_TYPE = OBJECT_TYPE_BELONGING;
};

} // namespace gf
