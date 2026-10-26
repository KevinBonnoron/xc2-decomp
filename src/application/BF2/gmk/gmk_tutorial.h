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

namespace gmk {

class GmkTutorialGob;

class GmkTutorial : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isCondMatched() const;

    u8 unknown00;               // Inferred role: sys multi flag; original member name unknown.
    ScenarioFlagCond unknown02; // Inferred role: scenario flag; original member name unknown.
    QuestFlagCond unknown06;    // Inferred role: quest flag; original member name unknown.
  };

  struct Data {
    const char *unknown00; // Inferred role: tutorial name; original member name unknown.
    int unknown08;         // Role and original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_TUTORIAL;

  GmkTutorial();
  ~GmkTutorial() override;
  GmkType getGmkType() const override;
  int getGameFlagId() const;
  bool isBooted() const;
  void setBooted() const;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void updateInActiveList(f32 deltaTime);
  void beginTutorial();
  void debugDraw() const override;
  void disposeGmkPhantom();

  const Data *getData() const { return static_cast<const Data *>(unknown20.unknown08); }

  mm::mtl::IntrusiveListNode<GmkTutorial> unknown48; // Role and original member name unknown.
  u8 _58[0x60 - 0x58];
  GmkPhantom unknown60; // Inferred role: phantom; original member name unknown.
  bool unknownF0;       // Role and original member name unknown.
  u8 _f1[0x100 - 0xf1];
};

static_assert(sizeof(GmkTutorial::BdatInfo) == 0xa, "");
static_assert(offsetof(GmkTutorial::Data, unknown08) == 0x08, "");
static_assert(offsetof(GmkTutorial, unknown48) == 0x48, "");
static_assert(offsetof(GmkTutorial, unknown60) == 0x60, "");
static_assert(offsetof(GmkTutorial, unknownF0) == 0xf0, "");
static_assert(sizeof(GmkTutorial) == 0x100, "");

class GmkTutorialList : public TGmkList<GmkTutorial, GmkTutorial::BdatInfo, 0x4f545554, 4, GmkTutorialGob> {
public:
  explicit GmkTutorialList(u32 updateGmkNumPerFrame);
  ~GmkTutorialList() override { dispose(); }
  void setBootedOthers(const GmkTutorial &gmk) const;
};

} // namespace gmk
