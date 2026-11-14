#pragma once
#include <stddef.h>

#include "gmk/gmk_base.h"
#include "gmk/gmk_collision.h"
#include "gmk/gmk_cond.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "types.h"

struct CBdatWrapper;

namespace gmk {

class GmkFieldLockGob;

class GmkFieldLock : public AGmkBase {
public:
  struct BdatInfo {
    BdatInfo() : unknown00(0), unknown02(0), unknown04(0) {}
    void create(CBdatWrapper bdat, int id, const AGmkBase &gmk);
    bool isCondMatched() const;

    u16 unknown00;              // Inferred role: condition; original member name unknown.
    u8 unknown02;               // Inferred role: lock type; original member name unknown.
    u16 unknown04;              // Inferred role: text id; original member name unknown.
    ScenarioFlagCond unknown06; // Inferred role: scenario flag; original member name unknown.
    QuestFlagCond unknown0a;    // Inferred role: quest flag; original member name unknown.
  };

  static const GmkType GMK_TYPE = GMK_TYPE_FIELD_LOCK; // Inferred name; shared by every gimmick class for the TGmkList templates.

  GmkFieldLock();
  ~GmkFieldLock() override { dispose(); }
  GmkType getGmkType() const override;
  void create(const CreateInfo &info) override;
  void dispose() override;
  void update(f32 deltaTime) override;
  void debugDraw() const override;
  void createGmkCollision();

  const BdatInfo *getBdatInfo() const { return reinterpret_cast<const BdatInfo *>(unknown20.unknown10); }

  GmkCollision unknown50; // Inferred role: collision; original member name unknown.
  f32 unknownc0;          // Inferred role: time since the party leader entered the lock; original member name unknown.
};

static_assert(sizeof(GmkFieldLock::BdatInfo) == 0xe, "");
static_assert(offsetof(GmkFieldLock, unknown50) == 0x50, "");
static_assert(offsetof(GmkFieldLock, unknownc0) == 0xc0, "");
static_assert(sizeof(GmkFieldLock) == 0xd0, "");

typedef TGmkList<GmkFieldLock, GmkFieldLock::BdatInfo, 0x434c4446, 2, GmkFieldLockGob> GmkFieldLockList;

} // namespace gmk
