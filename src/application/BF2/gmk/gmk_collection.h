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

    u16 nameRadius;
    u16 condition;
    TimeCond timeCond;
    WeatherCond weatherCond;
    DistCond distCond;
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
    BdatInfo() : mapId(-1), repopTime(1) {}

    bool create();

    int mapId;
    u8 repopTime;
  };

  explicit GmkCollectionList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame) {}
  ~GmkCollectionList() override;

  void create(const CreateInfo &info) override;

private:
  BdatInfo bdatInfo;
};

static_assert(sizeof(GmkCollectionList::BdatInfo) == 0x8, "");
static_assert(sizeof(GmkCollectionList) == 0x230, "");

} // namespace gmk
