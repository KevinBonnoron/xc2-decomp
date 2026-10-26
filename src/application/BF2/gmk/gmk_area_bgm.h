#pragma once
#include <stddef.h>

#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_phantom.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkAreaBgmGob;
class GmkAreaBgm;

class GmkBgmCondInfo : public mm::mtl::IntrusiveListNode<GmkBgmCondInfo> {
public:
  GmkBgmCondInfo() : unknown10(nullptr), unknown18(0), unknown1A(0) {}
  ~GmkBgmCondInfo() { dispose(); }
  bool isCondMatched() const;
  void dispose();

  GmkAreaBgm *unknown10; // Inferred role: owner; original member name unknown.
  u16 unknown18;         // Inferred role: bgm condition; original member name unknown.
  u16 unknown1A;         // Inferred role: bgm id; original member name unknown.
  u8 _1c[0x20 - 0x1c];
};

static_assert(offsetof(GmkBgmCondInfo, unknown10) == 0x10, "");
static_assert(offsetof(GmkBgmCondInfo, unknown18) == 0x18, "");
static_assert(offsetof(GmkBgmCondInfo, unknown1A) == 0x1a, "");
static_assert(sizeof(GmkBgmCondInfo) == 0x20, "");

class GmkBgmCondInfoManager : public mm::mtl::PtrSingleton<GmkBgmCondInfoManager> {
public:
  ~GmkBgmCondInfoManager() override { dispose(); }
  void dispose();
  static void addGmkBgmCondInfo(GmkBgmCondInfo *info);
  static void removeGmkBgmCondInfo(GmkBgmCondInfo *info);
  void applyFieldBgm() const;

  mm::mtl::IntrusiveList<GmkBgmCondInfo> unknown08; // Inferred role: active condition infos; original member name unknown.
  GmkBgmCondInfo *unknown20;                        // Inferred role: front condition info; original member name unknown.
};

static_assert(offsetof(GmkBgmCondInfoManager, unknown08) == 0x08, "");
static_assert(offsetof(GmkBgmCondInfoManager, unknown20) == 0x20, "");

class GmkAreaBgm : public AGmkBase, public IGmkPhantomEventListener {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    void dispose() { unknown00 = 0; }

    u16 unknown00; // Inferred role: bgm condition; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_AREA_BGM;

  GmkAreaBgm() : unknown50(nullptr), unknown160(nullptr) {}
  ~GmkAreaBgm() override { dispose(); }
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void createBgmCondInfos();
  void disposeBgmCondInfos();
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onEnterPhantom(const IGmkPhantomEventListener::OnEnterInfo &info) override;
  void onLeavePhantom(const IGmkPhantomEventListener::OnLeaveInfo &info) override;
  void createGmkPhantom();
  GmkBgmCondInfo *findCondMatched();

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(unknown20.unknown10); }

  GmkPhantom unknown50;        // Inferred role: phantom; original member name unknown.
  GmkBgmCondInfo unknownE0[4]; // Inferred role: bgm condition infos A to D; original member name unknown.
  GmkBgmCondInfo *unknown160;  // Inferred role: matched condition info; original member name unknown.
  u8 _168[0x170 - 0x168];
};

static_assert(sizeof(GmkAreaBgm::BdatInfo) == 0x2, "");
static_assert(offsetof(GmkAreaBgm, unknown50) == 0x50, "");
static_assert(offsetof(GmkAreaBgm, unknownE0) == 0xe0, "");
static_assert(offsetof(GmkAreaBgm, unknown160) == 0x160, "");
static_assert(sizeof(GmkAreaBgm) == 0x170, "");

typedef TGmkList<GmkAreaBgm, GmkAreaBgm::BdatInfo, 0x52414742, 2, GmkAreaBgmGob> GmkAreaBgmList;

} // namespace gmk
