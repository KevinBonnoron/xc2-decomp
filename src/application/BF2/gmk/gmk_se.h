#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

struct CBdatWrapper;

namespace fw {
class SoundPack;
}

namespace gmk {

class GmkSeGob;
class GmkSeLineGobCustom;
class GmkSeLinePointGobCustom;

class GmkSe : public AGmkBase {
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

  u8 _48[0x110 - 0x48];
};

static_assert(sizeof(GmkSe::BdatInfo) == 0x40, "");
static_assert(sizeof(GmkSe) == 0x110, "");

typedef TGmkList<GmkSe, GmkSe::BdatInfo, 0x45444e53, 2, GmkSeGob> GmkSeList;

class GmkSeLine : public AGmkBase {
public:
  static const GmkType GMK_TYPE = GMK_TYPE_SE_LINE;

  ~GmkSeLine() override;
  GmkType getGmkType() const override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;

  u8 _48[0x70 - 0x48];
};

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
