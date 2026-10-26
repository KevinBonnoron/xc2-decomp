#pragma once
#include <stddef.h>

#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_phantom.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkAreaBgmGob;

class GmkBgmCondInfo {
public:
  bool isCondMatched() const;

  u8 unknown00[0x18]; // Role and original member name unknown.
  u16 unknown18;      // Inferred role: bgm condition; original member name unknown.
  u8 _1a[0x20 - 0x1a];
};

static_assert(sizeof(GmkBgmCondInfo) == 0x20, "");
static_assert(offsetof(GmkBgmCondInfo, unknown18) == 0x18, "");

class GmkAreaBgm : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    void dispose() { unknown00 = 0; }

    u16 unknown00; // Inferred role: bgm condition; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_AREA_BGM;

  ~GmkAreaBgm() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void createBgmCondInfos();
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onEnterPhantom(const IGmkPhantomEventListener::OnEnterInfo &info);
  GmkBgmCondInfo *findCondMatched();

  u8 _48[0xe0 - 0x48];
  GmkBgmCondInfo unknownE0;  // Inferred role: bgm condition info; original member name unknown.
  GmkBgmCondInfo unknown100; // Inferred role: bgm condition info; original member name unknown.
  GmkBgmCondInfo unknown120; // Inferred role: bgm condition info; original member name unknown.
  GmkBgmCondInfo unknown140; // Inferred role: bgm condition info; original member name unknown.
  u8 _160[0x170 - 0x160];
};

static_assert(sizeof(GmkAreaBgm::BdatInfo) == 0x2, "");
static_assert(offsetof(GmkAreaBgm, unknownE0) == 0xe0, "");
static_assert(offsetof(GmkAreaBgm, unknown100) == 0x100, "");
static_assert(offsetof(GmkAreaBgm, unknown120) == 0x120, "");
static_assert(offsetof(GmkAreaBgm, unknown140) == 0x140, "");
static_assert(sizeof(GmkAreaBgm) == 0x170, "");

typedef TGmkList<GmkAreaBgm, GmkAreaBgm::BdatInfo, 0x52414742, 2, GmkAreaBgmGob> GmkAreaBgmList;

} // namespace gmk
