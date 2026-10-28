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

class GmkLandmarkGob;

class GmkLandmark : public AGmkBase, public IGmkPhantomEventListener, public mm::mtl::IntrusiveListNode<GmkLandmark> {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isCondMatched() const;

    u16 unknown00;         // Inferred role: msg id; original member name unknown.
    u8 unknown02;          // Inferred role: category; original member name unknown.
    u16 unknown04;         // Inferred role: condition; original member name unknown.
    bool unknown06;        // Inferred role: no telop; original member name unknown.
    const char *unknown08; // Inferred role: name; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_LANDMARK;

  GmkLandmark();
  ~GmkLandmark() override;
  GmkType getGmkType() const override;
  int getGameFlagId() const;
  bool isFound() const;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onEnterPhantom(const IGmkPhantomEventListener::OnEnterInfo &info) override;
  void onLeavePhantom(const IGmkPhantomEventListener::OnLeaveInfo &info) override { endEvent(); }
  void createGmkPhantom();
  void disposeGmkPhantom();
  void beginEvent();
  void endEvent();

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(unknown20.unknown10); }

  GmkPhantom unknown60; // Inferred role: phantom; original member name unknown.
  bool unknownF0;       // Inferred role: condition matched; original member name unknown.
  bool unknownF1;       // Inferred role: event started; original member name unknown.
};

static_assert(offsetof(GmkLandmark, unknown60) == 0x60, "");
static_assert(offsetof(GmkLandmark, unknownF0) == 0xf0, "");
static_assert(offsetof(GmkLandmark, unknownF1) == 0xf1, "");

static_assert(sizeof(GmkLandmark::BdatInfo) == 0x10, "");
static_assert(sizeof(GmkLandmark) == 0x100, "");

typedef TGmkList<GmkLandmark, GmkLandmark::BdatInfo, 0x4b4d444c, 2, GmkLandmarkGob> GmkLandmarkList;

class GmkLandmarkManager : public mm::mtl::PtrSingleton<GmkLandmarkManager> {
public:
  static void removeGmkLandmark(GmkLandmark *landmark);
  const GmkLandmark *findFirstAddedGmkLandmarkByCategory(u8 category) const;

  mm::mtl::IntrusiveList<GmkLandmark> unknown08; // Inferred role: landmarks sorted by category; original member name unknown.
  GmkLandmark *unknown20;                        // Inferred role: front landmark; original member name unknown.
};

static_assert(offsetof(GmkLandmarkManager, unknown20) == 0x20, "");

} // namespace gmk
