#pragma once
#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkCollectionGob;

class GmkCollection : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isPopCondMatchedExceptDist() const;
    bool isPopCondMatched(const AGmkBase &gmk) const;
    void debugDraw(const AGmkBase &gmk) const;

    u16 unknown00;         // Inferred role: name radius; original member name unknown.
    u16 unknown02;         // Inferred role: condition; original member name unknown.
    TimeCond unknown08;    // Inferred role: time cond; original member name unknown.
    WeatherCond unknown18; // Inferred role: weather cond; original member name unknown.
    DistCond unknown28;    // Inferred role: dist cond; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_COLLECTION;

  ~GmkCollection() override;
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;

  u8 _48[0x70 - 0x48];
};

static_assert(sizeof(GmkCollection::BdatInfo) == 0x30, "");
static_assert(sizeof(GmkCollection) == 0x70, "");

class GmkCollectionList : public TGmkList<GmkCollection, GmkCollection::BdatInfo, 0x54434c43, 5, GmkCollectionGob> {
public:
  struct BdatInfo {
    BdatInfo() : unknown00(-1), unknown04(1) {}

    bool create();

    int unknown00; // Inferred role: map id; original member name unknown.
    u8 unknown04;  // Inferred role: repop time; original member name unknown.
  };

  explicit GmkCollectionList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}
  ~GmkCollectionList() override;

  void create(const CreateInfo &info) override;

private:
  BdatInfo unknown228; // Inferred role: bdat info; original member name unknown.
};

static_assert(sizeof(GmkCollectionList::BdatInfo) == 0x8, "");
static_assert(sizeof(GmkCollectionList) == 0x230, "");

} // namespace gmk
