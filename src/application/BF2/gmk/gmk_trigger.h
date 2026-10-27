#pragma once
#include <stddef.h>

#include "gf/data/gf_bdat_wrapper.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_phantom.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace gmk {

class GmkTriggerGob;

class GmkTrigger : public AGmkBase {
public:
  struct BdatInfo {
    void create(CBdatWrapper, int, const AGmkBase &) {}
  };

  struct Data {
    int unknown00; // Role and original member name unknown.
    int unknown04; // Role and original member name unknown.
    int unknown08; // Role and original member name unknown.
    int unknown0c; // Role and original member name unknown.
    int unknown10; // Role and original member name unknown.
    int unknown14; // Role and original member name unknown.
    int unknown18; // Role and original member name unknown.
    int unknown1c; // Role and original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_TRIGGER;

  ~GmkTrigger() override { dispose(); }
  GmkType getGmkType() const override;
  bool isValid() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void createGmkPhantom();
  void seqUpdate(f32 deltaTime);
  void seqWaitToValidLinkGmkList(f32 deltaTime);
  void applyPopCondMatched(bool matched);
  int getBindedMapGimmickNum() const;
  int getBindedEnemyNum() const;
  int getBindedRoutedEnemyNum() const;
  AGmkBase *getBindedMapGimmick(u32 index) const;
  AGmkBase *getBindedEnemy(u32 index) const;
  AGmkBase *getBindedRoutedEnemy(u32 index) const;

  const Data *getData() const { return static_cast<const Data *>(unknown20.unknown08); }

  u8 _48[0x50 - 0x48];
  GmkPhantom unknown50;               // Inferred role: phantom; original member name unknown.
  void (GmkTrigger::*unknownE0)(f32); // Inferred role: sequence; original member name unknown.
};

static_assert(offsetof(GmkTrigger, unknown50) == 0x50, "");
static_assert(offsetof(GmkTrigger, unknownE0) == 0xe0, "");
static_assert(sizeof(GmkTrigger) == 0xf0, "");

typedef TGmkList<GmkTrigger, GmkTrigger::BdatInfo, 0x52475254, 2, GmkTriggerGob> GmkTriggerList;

// Inferred helper: creates the trigger list of a gmk list from the create info of that list without its bdat; original name unknown.
inline void unknown001(GmkTriggerList &triggers, IGmkList::CreateInfo info) {
  if (info.unknown00.isValid() && info.unknown10.length() != 0) {
    info.unknown114.clear();
    triggers.GmkTriggerList::create(info);
  }
}

} // namespace gmk
