#pragma once
#include <stddef.h>

#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkLandmarkGob;

class GmkLandmark : public AGmkBase {
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

  ~GmkLandmark() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;

  u8 _48[0x100 - 0x48];
};

static_assert(sizeof(GmkLandmark::BdatInfo) == 0x10, "");
static_assert(sizeof(GmkLandmark) == 0x100, "");

typedef TGmkList<GmkLandmark, GmkLandmark::BdatInfo, 0x4b4d444c, 2, GmkLandmarkGob> GmkLandmarkList;

class GmkLandmarkManager : public mm::mtl::PtrSingleton<GmkLandmarkManager> {
public:
  u8 _08[0x20 - 0x08];
  GmkLandmark *unknown20; // Inferred role: front landmark; original member name unknown.
};

static_assert(offsetof(GmkLandmarkManager, unknown20) == 0x20, "");

} // namespace gmk
