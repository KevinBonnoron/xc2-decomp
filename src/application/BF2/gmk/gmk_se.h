#pragma once
#include <stddef.h>

#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_phantom.h"
#include "mm_mtl/intrusive_list.h"
#include "types.h"

struct CBdatWrapper;
namespace mm {
struct Vec3;
} // namespace mm

namespace fw {
class SoundPack;
}

namespace gmk {

class GmkSeGob;
class GmkSeLineGobCustom;
class GmkSeLinePointGobCustom;

class GmkSe : public AGmkBase, public mm::mtl::IntrusiveListNode<GmkSe> {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isPopCondMatched() const;
    fw::SoundPack *getSoundPack() const;

    bool unknown00;             // Inferred role: map pack; original member name unknown.
    bool unknown01;             // Inferred role: play once; original member name unknown.
    u16 unknown02;              // Inferred role: se name; original member name unknown.
    u8 unknown04;               // Inferred role: volume max; original member name unknown.
    u8 unknown05;               // Inferred role: volume min; original member name unknown.
    u16 unknown06;              // Inferred role: condition; original member name unknown.
    u8 unknown08;               // Inferred role: in room volume; original member name unknown.
    ScenarioFlagCond unknown0a; // Inferred role: scenario flag; original member name unknown.
    QuestFlagCond unknown0e;    // Inferred role: quest flag; original member name unknown.
    TimeCond unknown18;         // Inferred role: time cond; original member name unknown.
    WeatherCond unknown28;      // Inferred role: weather cond; original member name unknown.
    BootedGmkCond unknown38;    // Inferred role: booted gmk; original member name unknown.
    BootedGmkCond unknown3c;    // Inferred role: op booted gmk; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_SE;

  ~GmkSe() override;
  GmkType getGmkType() const override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void createGmkPhantom();
  bool canPopInst() const;
  bool canDepopInst() const;

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(unknown20.unknown10); }

  u8 _58[0x60 - 0x58];
  GmkPhantom unknown60; // Inferred role: phantom; original member name unknown.
  bool unknownF0;       // Role and original member name unknown.
  u8 _f1[0xf4 - 0xf1];
  int unknownF4; // Role and original member name unknown.
  u8 _f8[0x100 - 0xf8];
  bool unknown100; // Role and original member name unknown.
  u8 _101[0x110 - 0x101];
};

static_assert(sizeof(GmkSe::BdatInfo) == 0x40, "");
static_assert(offsetof(GmkSe, unknown60) == 0x60, "");
static_assert(offsetof(GmkSe, unknownF0) == 0xf0, "");
static_assert(offsetof(GmkSe, unknownF4) == 0xf4, "");
static_assert(offsetof(GmkSe, unknown100) == 0x100, "");
static_assert(sizeof(GmkSe) == 0x110, "");

typedef TGmkList<GmkSe, GmkSe::BdatInfo, 0x45444e53, 2, GmkSeGob> GmkSeList;

class GmkSeLine : public AGmkBase, public mm::mtl::IntrusiveListNode<GmkSeLine> {
public:
  struct Data {
    f32 unknown00; // Inferred role: AABB minimum x; original member name unknown.
    f32 unknown04; // Inferred role: AABB minimum y; original member name unknown.
    f32 unknown08; // Inferred role: AABB minimum z; original member name unknown.
    int unknown0c; // Inferred role: first point index; original member name unknown.
    f32 unknown10; // Inferred role: AABB maximum x; original member name unknown.
    f32 unknown14; // Inferred role: AABB maximum y; original member name unknown.
    f32 unknown18; // Inferred role: AABB maximum z; original member name unknown.
    int unknown1c; // Inferred role: point index end; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_SE_LINE;

  GmkSeLine();
  ~GmkSeLine() override;
  GmkType getGmkType() const override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  int getPointNum() const;
  const AGmkBase *getPoint(u32 index) const;
  bool getPointPos(mm::Vec3 &position, u32 index) const;
  bool canPopInst() const;
  bool canDepopInst() const;
  bool isPlayerInsideAabb() const;

  const Data *getData() const { return static_cast<const Data *>(unknown20.unknown08); }

  bool unknown58; // Role and original member name unknown.
  bool unknown59; // Role and original member name unknown.
  u8 _5a[0x5c - 0x5a];
  int unknown5C;  // Role and original member name unknown.
  f32 unknown60;  // Role and original member name unknown.
  u32 unknown64;  // Role and original member name unknown.
  bool unknown68; // Role and original member name unknown.
  u8 _69[0x70 - 0x69];
};

static_assert(offsetof(GmkSeLine, unknown58) == 0x58, "");
static_assert(offsetof(GmkSeLine, unknown59) == 0x59, "");
static_assert(offsetof(GmkSeLine, unknown5C) == 0x5c, "");
static_assert(offsetof(GmkSeLine, unknown60) == 0x60, "");
static_assert(offsetof(GmkSeLine, unknown64) == 0x64, "");
static_assert(offsetof(GmkSeLine, unknown68) == 0x68, "");
static_assert(sizeof(GmkSeLine) == 0x70, "");

typedef TGmkList<GmkSeLine, GmkSe::BdatInfo, 0x4e4c4553, 2, GmkSeLineGobCustom> GmkSeLineList;

class GmkSeLinePoint : public AGmkBase {
public:
  struct BdatInfo {};

  static const GmkType GMK_TYPE = GMK_TYPE_SE_LINE_POINT;

  GmkType getGmkType() const override;
  bool isValid() const override;
};

static_assert(sizeof(GmkSeLinePoint) == 0x48, "");

typedef TGmkList<GmkSeLinePoint, GmkSeLinePoint::BdatInfo, 0x54504c53, 1, GmkSeLinePointGobCustom> GmkSeLinePointList;

} // namespace gmk
