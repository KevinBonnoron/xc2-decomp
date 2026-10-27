#pragma once
#include <stddef.h>

#include "gmk/gmk_base.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

struct CBdatWrapper;
namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

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

  GmkCollection();
  ~GmkCollection() override { dispose(); }
  GmkType getGmkType() const override;
  int getGameFlagId() const;
  bool isWaitRepop() const;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void onPlayerAccessed(gf::GF_OBJ_HANDLE *handle) override;
  bool canPopGobInst() const;
  bool canDepopGobInst() const;
  void createGfObjHandle();
  void disposeGfObjHandle();
  void disposeIcon(bool isFadeOut);
  void validateDisp() const;
  void seqUpdateRepopCounter(f32 deltaTime);
  void setTargetable(bool isTargetable);

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(unknown20.unknown10); }

  gf::GF_OBJ_HANDLE *unknown48;          // Inferred role: gob instance handle; original member name unknown.
  u32 unknown50;                         // Role and original member name unknown.
  f32 unknown54;                         // Role and original member name unknown.
  void (GmkCollection::*unknown58)(f32); // Inferred role: sequence; original member name unknown.
  f32 unknown68;                         // Role and original member name unknown.
  bool unknown6c;                        // Role and original member name unknown.
};

static_assert(sizeof(GmkCollection::BdatInfo) == 0x30, "");
static_assert(offsetof(GmkCollection, unknown48) == 0x48, "");
static_assert(offsetof(GmkCollection, unknown50) == 0x50, "");
static_assert(offsetof(GmkCollection, unknown54) == 0x54, "");
static_assert(offsetof(GmkCollection, unknown58) == 0x58, "");
static_assert(offsetof(GmkCollection, unknown68) == 0x68, "");
static_assert(offsetof(GmkCollection, unknown6c) == 0x6c, "");
static_assert(sizeof(GmkCollection) == 0x70, "");

class GmkCollectionList : public TGmkList<GmkCollection, GmkCollection::BdatInfo, 0x54434c43, 5, GmkCollectionGob> {
public:
  struct BdatInfo {
    BdatInfo() : unknown00(-1), unknown04(1) {}

    bool create();

    int unknown00; // Inferred role: map id; original member name unknown.
    u8 unknown04;  // Inferred role: repop time; original member name unknown.
  };

  explicit GmkCollectionList(u32 updateGmkNumPerFrame);
  ~GmkCollectionList() override { dispose(); }

  void create(const CreateInfo &info) override;

private:
  BdatInfo unknown228; // Inferred role: bdat info; original member name unknown.
};

static_assert(sizeof(GmkCollectionList::BdatInfo) == 0x8, "");
static_assert(sizeof(GmkCollectionList) == 0x230, "");

} // namespace gmk
